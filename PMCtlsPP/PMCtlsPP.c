/***************************************************************************
 *
 * PROGRAM NAME: PMCTLSPP
 * -------------
 *
 * MODULE NAME:  PMCTLSPP
 * ------------
 *
 * VERSION:      2.70
 * --------
 *
 * DESCRIPTION:
 * ------------
 *      Initialisation module
 *
 * FUNCTIONS:
 * ----------
 *      _DLL_InitTerm
 *      _PM_Init
 *      registerPublicWindowClasses
 *      _System InitUpdateThread
 *      _System UpdateThread
 *
 * COMPILER:
 * ---------
 *      IBM Visual Age C++ 3.0
 *
 * LIBRARIES:
 * ----------
 *      Subsystem libraries (static)
 *
 * CHANGE LOG:
 * -----------
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.10    05-12-02  Handling of shift-keys
 *  2.20    10-03-02  USB support added
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *
 *  Copyright (C) noller & breining software 2001...2004
 *
 ******************************************************************************/
#define  INCL_DOS
#define  INCL_WIN
#define  INCL_GPI
#define  INCL_ERRORS
#include <os2.h>

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <Log.h>
#include "AMouseGlobal.h"
#include "PmCtlsPP.h"
#include "PMCtlsData.h"
#include "PMCtlsIni.h"

/*******************************************************************\
  type definitions an function prototypes
\*******************************************************************/
int _rmem_init (void);
int _rmem_term (void);
unsigned long _System _DLL_InitTerm (unsigned long hModule, unsigned long ulFlag);

BOOL _System InitUpdateThread (VOID);
VOID _System UpdateThread (ULONG ulParm);
VOID registerPublicWindowClasses (VOID);
VOID LoadModule (VOID);

/*******************************************************************\
  global data segment
\*******************************************************************/
#pragma data_seg(GLOBAL_SEG)

BOOL  bIsRegistered = FALSE;

STRUCTCLASS arClasses[] =
    {
        {WC_ENTRYFIELD, NULL,                       EntryFieldDialogProc, &pfnwpOldEntryFieldWndProc},
        {WC_COMBOBOX,   (PFN)ComboBoxRegisterClass, ComboBoxDialogProc,   &pfnwpOldComboBoxWndProc},
        {NULL,          NULL,                       NULL,                 NULL}
    };

/*******************************************************************\
    _DLL_InitTerm is the function that gets called by the operating
    system loader when it loads and frees this DLL for each process
    that accesses this DLL.  However, it only gets called the first
    time the DLL is loaded and the last time it is freed for a
    particular process.  The system linkage convention must be used
    because the operating system loader is calling this function.
    Input:  hModule: module handle of this dll
            ulFlag:  initialization / termination
    Return: 0:       unsuccessul
            other:   successul
\*******************************************************************/
#pragma linkage (_DLL_InitTerm, system)
unsigned long _DLL_InitTerm (unsigned long hModule, unsigned long ulFlag)
    {
    static BOOL bIsInitialized = FALSE;

    switch (ulFlag)
        {
        case 0:         // initialization
            /* The C run-time environment initialization function must   */
            /* be called before any calls to C run-time functions that   */
            /* are not inlined.                                          */
            if (!bIsInitialized)
                {
                bIsInitialized = TRUE;
                _rmem_init ();

                TraceInit ("d:\\$$PMC$$.dbg");
                DebugE ("_DLL_InitTerm", "Trace was initialized");

                return InitUpdateThread ();
                }
            break;

        case 1:         // termination
            _rmem_term ();
            break;

        default:
            return 0;
        }

    /* A nonzero value must be returned to indicate success. */
    return 1;
    }

ULONG EXPENTRY _PM_Init (VOID)
    {
    DebugE ("_PM_Init", "called");

    if (!bIsRegistered)
        {
        bIsRegistered = TRUE;

        // initialize instance data and register all classes in class array if successful
        if (clsInitData ())
            registerPublicWindowClasses ();
        }

    DebugE ("_PM_INIT", "finished");
    return 1;
    }

VOID registerPublicWindowClasses (VOID)
    {
    BOOL      rc;
    HAB       hab;
    LONG      lIndex;
    CLASSINFO ci;

    hab = WinQueryAnchorBlock (HWND_DESKTOP);

    for (lIndex = 0; arClasses[lIndex].pszClassName != NULL; lIndex++)
        {
        WinQueryClassInfo (hab, arClasses[lIndex].pszClassName, &ci);
        DebugUL ("Register", "flClassStyle: ", ci.flClassStyle);
        Debug2UL ("Register", "pfnWndProc:   ", ci.pfnWindowProc, "; new: ", arClasses[lIndex].pWndProc);
        DebugUL ("Register", "cbWindowData: ", ci.cbWindowData);

        *(arClasses[lIndex].ppOldWndProc) = ci.pfnWindowProc;

        if (arClasses[lIndex].pPrivRegisterClass)
            rc = arClasses[lIndex].pPrivRegisterClass (hab,
                                                       arClasses[lIndex].pszClassName,
                                                       arClasses[lIndex].pWndProc,
                                                       ci.flClassStyle,
                                                       ci.cbWindowData);
        else
            rc = WinRegisterClass (hab,
                                   arClasses[lIndex].pszClassName,
                                   arClasses[lIndex].pWndProc,
                                   ci.flClassStyle,
                                   ci.cbWindowData);

        DebugUL ("Register", "return of WinRegisterClass: ", rc);
        }

    return;
    }

/*******************************************************************\
    Starts the UpdateThread after setting up the shared memory and
    needed semaphores for communication with WPS class
    Return: TRUE:  successul
\*******************************************************************/
BOOL _System InitUpdateThread (VOID)
    {
    TID  tid;

    // Mechanism for determination of parameters:
    // 1. Define default values
    // 2. Read parameters from OS2.INI file
    // 3. Open/Create shared memory area; parameters are read, as soon as bInitialized == TRUE

    /* initialize data structure */
    if (clsInitData ())
        {
        DosCreateThread (&tid, (PFNTHREAD)UpdateThread, (ULONG)0, 0L, 0x8000);
        DebugE ("InitUpdateThread", "Thread started");
        return TRUE;
        }
    else
        {
        DebugE ("InitUpdateThread", "problem with semaphore: no Thread started");
        return FALSE;
        }
    }

/*******************************************************************\
    Thread that updates the settings data, if changes
    have been made to the respective data in the ini-file.
    The thread never terminates
    Input: ulParm: unused
\*******************************************************************/
VOID _System UpdateThread (ULONG ulParm)
    {
    ULONG ulPostCount;

    for (;;)
        {
        DosWaitEventSem (hevWheelThreadUpdate, SEM_INDEFINITE_WAIT);
        queryData ();
        DosResetEventSem (hevWheelThreadUpdate, &ulPostCount);
        }
    }

