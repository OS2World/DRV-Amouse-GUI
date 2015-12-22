/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUDLL
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMOUDLL
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   This DLL is registered at the OS/2 Presentation Manager. It starts
 *   the WheelThread after establishing the semaphores and shared memory
 *   necessary for communication with the WPS class
 *
 * FUNKTIONEN:
 * -----------
 *   _DLL_InitTerm
 *   initWheelThread
 *   WheelThread
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.10    05-12-02  Handling of shift-keys
 *  2.20    10-03-02  USB support added
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added; memory leak removed
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define  INCL_DOS
#define  INCL_KBD
#define  INCL_DOSERRORS
#define  INCL_DOSDEVIOCTL
#define  INCL_MOU
#define  INCL_WINSHELLDATA
#define  INCL_WINFRAMEMGR
#define  INCL_WINSCROLLBARS
#define  INCL_WINSTDSPIN
#define  INCL_WINSYS
#define  INCL_WINWINDOWMGR
#define  INCL_WININPUT
#define  INCL_WINMESSAGEMGR
#define  INCL_WINPOINTERS
#define  INCL_WINRECTANGLES
#define  INCL_WINSTDSLIDER
#define  INCL_WINCIRCULARSLIDER
#define  INCL_WINSTDVALSET
#define  INCL_GPIPATHS
#include <os2.h>

#define  INCL_MCIOS2
#include <os2me.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <Log.h>
#include "pmwinmou.h"

#include "AMouseGlobal.h"
#include "AMouRes.h"
#include "AMouHook.h"
#include "AMouData.h"
#include "AMouIni.h"
#include "AMouHwnd.h"
#include "dosqss.h"

int _rmem_init (void);
int _rmem_term (void);
VOID initWheelThread (VOID);
VOID _System WheelThread (ULONG ulParm);
VOID _System UpdateThread (ULONG ulParm);
VOID _System PaintVolumeThread (ULONG ulParm);

#define CCHMAXCLASSNAME         32
#define CCHMAXSYSSTATEBUFFER_S  sizeof (QTOPLEVEL) + sizeof (QGLOBAL) + sizeof (QPROCESS) +   64*sizeof (QTHREAD)
#define CCHMAXSYSSTATEBUFFER_L  sizeof (QTOPLEVEL) + sizeof (QGLOBAL) + sizeof (QPROCESS) + 4096*sizeof (QTHREAD)
#define RESERVED                0

#define ACCEL_THRESHOLD         500             // acceleration threshold in ms

#define BTNSTATE_4              0x0001
#define BTNSTATE_4CHG           0x0002
#define BTNSTATE_5              0x0004
#define BTNSTATE_5CHG           0x0008
#define BTNSTATE_6              0x0010
#define BTNSTATE_6CHG           0x0020
#define BTNSTATE_7              0x0040
#define BTNSTATE_7CHG           0x0080
#define BTNSTATE_8              0x0100
#define BTNSTATE_8CHG           0x0200
#define BTNSTATE_9              0x0400
#define BTNSTATE_9CHG           0x0800
#define BTNSTATE_10             0x1000
#define BTNSTATE_10CHG          0x2000
#define BTNSTATE_RESERVED       0x4000
#define BTNSTATE_SCREENGROUP_PM 0x8000          // screen group is 1 (PM)

#define BTNSTATE_CHANGE         (BTNSTATE_4CHG|BTNSTATE_5CHG|BTNSTATE_6CHG|BTNSTATE_7CHG|BTNSTATE_8CHG|BTNSTATE_9CHG|BTNSTATE_10CHG)


#define MOU_GETEXTDATA          0x77

#pragma pack (1)
typedef struct                                  // parameter package for MOU_GETEXTDATA
    {
    SHORT   sWheelTurns;
    USHORT  usBtnState;                         // see BTNSTATE_BTN* flags
    SHORT   sWheel2Turns;
    } EMOUEXTDATA, *PEMOUEXTDATA;

typedef struct                                  // parameter package for MOU_VER
    {
    USHORT  usMagic;                            // magic code
    USHORT  usParmNum;                          // number of parameters following
    BYTE    bScrollMode;                        // FSSCROLL_MODE_* - value
    BYTE    bScrollNum;                         // repeat number (0...15)
    BYTE    bPollingRate;                       // PS/2 polling rate (40, 60, 80, 100, 200; default: 80)
    BYTE    bWheelCount;                        // number of wheels (0 = 0 wheels,  1 = 1 wheel, 2 = 2 wheels)
    BYTE    bSmartCruise;                       // SmartCruise (0 = no SMC, 1 = ver, 2 = hor, 3 (default) = hor+ver)
    } EMOUVERDATA, *PEMOUVERDATA;

typedef struct
    {
    USHORT  uscRepeat;
    USHORT  usMakeCode;
    USHORT  usBreakCode;
    } KBDEVENT, *PKBDEVENT;
#pragma pack ()

typedef enum
    {
    drvMode_Std,
    drvMode_Ext1,
    drvMode_Ext2
    } DriverMode;

/*******************************************************************\
  local data segment (process specific)
\*******************************************************************/
HFILE       hFileDriver             = NULLHANDLE;

HMODULE     hModAudio               = NULLHANDLE;       // module handle of nbaudio.dll
HMODULE     hModHookDll             = NULLHANDLE;       // module handle of amouhook.dll
BOOL        bFirstInstance          = FALSE;            // termination of first instance releases hooks

PFN         pfnAddWindowHandle      = NULL;             // entry to AddWindowHandle
PFN         pfnFindWindowHandle     = NULL;             // entry to FindWindowHandle

PFN         pfnMciGetMasterVolume   = NULL;
PFN         pfnMciSetMasterVolume   = NULL;
PFN         pfnMciSaveMasterVolume  = NULL;

HEV         hevPaintVolume          = NULLHANDLE;       // semaphore for volume scroll bar

/*******************************************************************\
  global data segment
\*******************************************************************/
#pragma data_seg(GLOBAL_SEG)
PSZ         szHookDllName          = "AMouHook.dll";
PSZ         szAudioDllName         = "nbaudio.dll";

DriverMode  driverMode             = drvMode_Std;

ULONG       ulProcessCount         = 0;                 // number of processes with access to DLL

const ULONG ulThreshold            = ACCEL_THRESHOLD;   // threshold value for acceleration

LONG        lVolume                = -1;                // Master-Volume setting
TID         tidVolumePaint         = NULLHANDLE;        // tid of Master-Volume paint thread
PID         pidVolumePaint         = NULLHANDLE;        // pid of Master-Volume paint thread
RECTL       rcl_BackGnd            = {0, 0, 0, 0};      // rectangle of volume slider relative to screen

// global static variables for setShiftKeys
USHORT      usShiftState;
SHIFTSTATE  shiftState;
BYTE        bKeyShift, bKeyAlt, bKeyCtrl;
BYTE        keyState[256];                      // This is a 256 byte table indexed by virtual key value. For any
                                                // virtual key, the 0x80 bit is set if the key is down, and zero
                                                // if it is up. The 0x01 bit is set if the key is toggled,
                                                // (pressed an odd number of times), otherwise it is zero.

/*******************************************************************\
    Dummy-entry to the dll to enforce the _DLL_InitTerm being called
\*******************************************************************/
void ManualCall (void)
    {
    DebugE ("ManualCall", "was called");
    return;
    }

BOOL WinRegisterForWheelMsg (HWND hwnd, ULONG flWindow)
    {
    if (pfnAddWindowHandle)
        return pfnAddWindowHandle (hwnd, flWindow);
    else
        return FALSE;
    }

VOID insertHook (VOID)
    {
    PFN pfnInitHookDll = NULL;
    PFN pfnInsertHook  = NULL;
    APIRET rc;

    bFirstInstance = TRUE;

    rc = DosLoadModule (NULL, 0, szHookDllName, &hModHookDll);
    if (rc != NO_ERROR)
        return;

    rc = DosQueryProcAddr (hModHookDll, 2L, NULL, &pfnInitHookDll);
    if (rc != NO_ERROR)
        return;

    rc = DosQueryProcAddr (hModHookDll, 3L, NULL, &pfnInsertHook);
    if (rc != NO_ERROR)
        return;

    pfnInitHookDll (hab);
    pfnInsertHook ();

    return;
    }

VOID releaseHook (VOID)
    {
    PFN    pfnReleaseInputHook = NULL;
    APIRET rc;

    if (bFirstInstance)
        {
        rc = DosQueryProcAddr (hModHookDll, 4L, NULL, &pfnReleaseInputHook);
        if (rc == NO_ERROR)
            pfnReleaseInputHook ();
        bFirstInstance = FALSE;
        }

    DosFreeModule (hModHookDll);

    return;
    }

VOID loadMMOS2 (VOID)
    {
    APIRET rc;
    ULONG  ulType;
    BOOL   bError = FALSE;

    if (pfnMciGetMasterVolume && pfnMciSetMasterVolume && pfnMciSaveMasterVolume)
        return;

    DebugE ("loadMMOS2: load module ", szAudioDllName);
    rc = DosLoadModule (NULL, 0, szAudioDllName, &hModAudio);
    if (rc == NO_ERROR)
        {
        rc = DosQueryProcAddr (hModAudio, 0, "MciGetMasterVolume", &pfnMciGetMasterVolume);
        if (rc != NO_ERROR)
            bError = TRUE;

        rc = DosQueryProcAddr (hModAudio, 0, "MciSetMasterVolume", &pfnMciSetMasterVolume);
        if (rc != NO_ERROR)
            bError = TRUE;

        rc = DosQueryProcAddr (hModAudio, 0, "MciSaveMasterVolume", &pfnMciSaveMasterVolume);
        if (rc != NO_ERROR)
            bError = TRUE;

        if (bError)
            pfnMciGetMasterVolume = pfnMciSetMasterVolume = pfnMciSaveMasterVolume = NULL;
        else
            {
            if (!hevPaintVolume)
                if (DosOpenEventSem (SEMNAMEEVT_PAINT, &hevPaintVolume))
                    {
                    DebugE ("loadMMOS2", "Create event semaphore");
                    if (DosCreateEventSem (SEMNAMEEVT_PAINT, &hevPaintVolume, DC_SEM_SHARED, TRUE))
                        bError = TRUE;
                    }
            }
        }

    if (bError)
        {
        DebugE ("loadMMOS2", "error occurred during DLL load");
        DosFreeModule (hModAudio);
        hModAudio = NULLHANDLE;
        }

    return;
    }

VOID initDLLEntries (VOID)
    {
    DosLoadModule (NULL, 0, szHookDllName, &hModHookDll);
    DebugUL ("WinRegisterForWheelMsg", "hmod = ", hModHookDll);

    if (hModHookDll)
        {
        DosQueryProcAddr (hModHookDll, 10L, NULL, &pfnAddWindowHandle);
        DebugUL ("initDLLEntries", "pfn1 = ", pfnAddWindowHandle);
        DosQueryProcAddr (hModHookDll, 11L, NULL, &pfnFindWindowHandle);
        DebugUL ("initDLLEntries", "pfn2 = ", pfnFindWindowHandle);
        }
    }

/*******************************************************************\
    _DLL_InitTerm is the function that gets called by the operating
    system loader when it loads and frees this DLL for each process
    that accesses this DLL.  However, it only gets called the first
    time the DLL is loaded and the last time it is freed for a
    particular process.  The system linkage convention must be used
    because the operating system loader is calling this function.
    Input:  modhandle: module handle of this dll
            flag:      initialization / termination
    Return: 0:     unsuccessul
            other: successul
\*******************************************************************/
#pragma linkage (_DLL_InitTerm, system)
unsigned long _DLL_InitTerm (unsigned long modhandle, unsigned long flag)
    {
    switch (flag)
        {
        case 0:         // initialization
            if (_rmem_init () == -1)
                return 0;

            initDLLEntries ();
            loadMMOS2 ();
            TraceInit ("E:\\$$AMD$$.dbg");

            if (ulProcessCount++ == 0)
                {
                hModule = modhandle;
                hab     = WinQueryAnchorBlock (HWND_DESKTOP);

                DebugE ("INIT", "Now start WheelThread");
                if (clsInitData ())
                    {
                    insertHook ();
                    initWheelThread ();
                    return 1;
                    }

                return 0;
                }
            DebugE ("INIT", "Again called => load rejeced");
            break;

        case 1:         // termination
            if (--ulProcessCount == 0)
                {
                releaseHook ();
                DebugE ("INIT", "hook released");
                }

            DebugE ("INIT", "terminate DLL");
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

    return 1;
    }

/*******************************************************************\
    Cleans up resources needed in the paint-volume thread
    Input:  ulTermCode: termination reason
\*******************************************************************/
VOID APIENTRY exitList (ULONG ulTermCode)
    {
    PTIB    ptib;
    PPIB    ppib;

    /* query the pid of the terminating process */
    DosGetInfoBlocks (&ptib, &ppib);

    DebugUL ("exitList", "termCode = ", ulTermCode);

    switch (ulTermCode)
        {
        case TC_EXIT:
        case TC_KILLPROCESS:
            if (pidVolumePaint == ppib->pib_ulpid)
                if (tidVolumePaint)
                    {
                    DosKillThread (tidVolumePaint);
                    if (rcl_BackGnd.xRight != 0)
                        WinInvalidateRect (HWND_DESKTOP, &rcl_BackGnd, TRUE);
                    }
            break;

        default:
            break;
        }

    if (pidVolumePaint == ppib->pib_ulpid)
        {
        if (tidVolumePaint)
            {
            DosCloseEventSem (hevPaintVolume);
            tidVolumePaint = NULLHANDLE;
            }
        }

    return;
    }

/*******************************************************************\
    Evaluates next window in z-order below hwnd, which contains
    *pptl
    Input:  hwnd: window to be evaluated
            pptl: pointer to POINTL containing position on screen
    Return: NULLHANDLE, if no window
            other, if window found
\*******************************************************************/
HWND NextWindowBelow (HWND hwnd, PPOINTL pptl)
    {
    RECTL  rctl;
    POINTL ptl;

    while ((hwnd = WinQueryWindow (hwnd, QW_NEXT)) != NULLHANDLE)
        {
        if (!WinIsWindow (hab, hwnd))
            continue;

        ptl = *pptl;
        WinQueryWindowRect (hwnd, &rctl);
        WinMapWindowPoints (HWND_DESKTOP, hwnd, &ptl, 1);
        if (WinPtInRect (hab, &rctl, &ptl) == TRUE)
            break;
        }

    return hwnd;
    }

/*******************************************************************\
    Evaluates child window, which contains *pptl
    Input:  hwndParent: window to be evaluated
            pptl: pointer to POINTL containing position on screen
    Return: NULLHANDLE, if no window
            other, if window found
\*******************************************************************/
HWND NextChildBelow (HWND hwndParent, PPOINTL pptl)
    {
    RECTL  rctl;
    POINTL ptl;
    HENUM  henum;
    HWND   hwnd = NULLHANDLE;

    if ((henum = WinBeginEnumWindows (hwndParent)) != NULLHANDLE)
        {
        while ((hwnd = WinGetNextWindow (henum)) != NULLHANDLE)
            {
            if (!WinIsWindow (hab, hwnd))
                continue;

            ptl = *pptl;
            WinQueryWindowRect (hwnd, &rctl);
            WinMapWindowPoints (HWND_DESKTOP, hwnd, &ptl, 1);
            if (WinPtInRect (hab, &rctl, &ptl) == TRUE)
                break;
            }

        WinEndEnumWindows (henum);
        }

    return hwnd;
    }

BOOL CompareProcessName (PSZ pszProcessName, PSZ pszCompare)
    {
    CHAR c;

    while ((c = *pszProcessName) != '\0')
        {
        switch (c)
            {
            case '*':
                pszProcessName++;
                while (*pszCompare != *pszProcessName)
                    {
                    pszCompare++;
                    if (*pszCompare == '\0')
                        goto Exit;
                    }
                break;

            case '?':
                c = *(++pszProcessName);
                if (c == '*' || c == '?')
                    break;
                if ((*pszCompare != '\0') && (c == *(pszCompare+1)))
                    pszCompare++;
                if (c != *pszCompare)
                    goto Exit;
                break;

            default:
                if (*pszCompare == '\0')
                    goto Exit;
                if (c != *pszCompare)
                    goto Exit;
                else
                    {
                    pszProcessName++;
                    pszCompare++;
                    }
            }
        }

Exit:
    return (*pszProcessName == '\0' && *pszCompare == '\0') ? TRUE : FALSE;
    }

/*******************************************************************\
    Executes DosQuerySysState and determines the process name for
    pid without path specification
    Input:  pid         : pid of process to be examined
            cbBuffer    : size of buffer
    Output: pProcessName: name of process excluding path specification
    Return: return value of last API call
\*******************************************************************/
APIRET QuerySysState (PID pid, ULONG cbBuffer, PCHAR pszProcessName)
    {
    static CHAR szModuleName[CCHMAXPATH];
    PSZ         pszProcess;
    PVOID       pBuffer;
    PQTOPLEVEL  pTop;
    PQPROCESS   pP;
    APIRET rc;

    /* Allocate memory for evaluation */
    DebugUL ("QuerySysState", "allocate buffer with size: ", cbBuffer);
    rc = DosAllocMem (&pBuffer, cbBuffer, PAG_COMMIT | PAG_READ | PAG_WRITE);
    if (rc != NO_ERROR)
        return rc;

    /* Query system state */
    rc = DosQuerySysState (0x1, RESERVED, pid, RESERVED, pBuffer, cbBuffer);
    if (rc == NO_ERROR)
        {
        pTop = (PQTOPLEVEL)pBuffer;
        pP   = pTop->procdata;
        if (pP && pP->rectype == 1 && pP->pid == pid)
            {
            DosQueryModuleName (pP->hndmod, CCHMAXPATH, szModuleName);
            DebugE ("QuerySysState => QueryModuleName", szModuleName);
            pszProcess = strrchr (szModuleName, '\\');
            if (pszProcess == NULL)
                pszProcess = szModuleName;
            else
                pszProcess++;
            strcpy (pszProcessName, pszProcess);
            }
        }

    DosFreeMem (pBuffer);
    return rc;
    }

BOOL CheckProcessName (HWND hwnd, PSZ pszProcessName)
    {
    static HWND hwndPrevious = NULLHANDLE;
    static CHAR szProcessPrevious[CCHMAXPATHCOMP];
    PID         pid;
    TID         tid;
    COUNTRYCODE cc;
    BOOL        bRC;
    APIRET      rc;

    /* Empty string always matches */
    if (*pszProcessName == '\0')
        return TRUE;

    /* Uppercase string */
    cc.country  = 0;
    cc.codepage = 0;
    DosMapCase (strlen (pszProcessName), &cc, pszProcessName);

    DebugE ("CheckProcessName => for process ", pszProcessName);
    /* Skip, if hwnd was already evaluated */
    if (hwndPrevious == hwnd)
        {
        DebugE ("CheckProcessName => (again)result = ",
            (strcmp (pszProcessName, szProcessPrevious) == 0 ? "TRUE" : "FALSE"));
        return CompareProcessName (pszProcessName, szProcessPrevious);
        }

    WinQueryWindowProcess (hwnd, &pid, &tid);

    /* Predefine values for error case */
    szProcessPrevious[0] = '\0';
    hwndPrevious         = hwnd;
    bRC                  = FALSE;

    /* Allocate memory for evaluation */
    rc = QuerySysState (pid, CCHMAXSYSSTATEBUFFER_S, szProcessPrevious);
    if (rc == ERROR_BUFFER_OVERFLOW)
        rc = QuerySysState (pid, CCHMAXSYSSTATEBUFFER_L, szProcessPrevious);

    if (rc == NO_ERROR)
        bRC = CompareProcessName (pszProcessName, szProcessPrevious);

    DebugE ("CheckProcessName => result", (bRC ? "TRUE" : "FALSE"));
    return bRC;
    }

HWND FindOwnedListbox (HWND hwndCombo)
    {
    CHAR  szBuffer[4];
    HENUM henum;
    HWND  hwndOwner;
    HWND  hwndEnum = NULLHANDLE;

    if ((henum = WinBeginEnumWindows (HWND_OBJECT)) != NULLHANDLE)
        {
        while ((hwndEnum = WinGetNextWindow (henum)) != NULLHANDLE)
            {
            if (!WinIsWindow (hab, hwndEnum))
                continue;

            hwndOwner = WinQueryWindow (hwndEnum, QW_OWNER);
            if (hwndOwner == hwndCombo)
                {
                WinQueryClassName (hwndEnum, 4, szBuffer);
                // check for listbox class
                if (szBuffer[0] == '#' && szBuffer[1] == '7')
                    break;
                }
            }

        WinEndEnumWindows (henum);
        }

    return hwndEnum;
    }

HWND FindWindowOfClass (HWND hwndParent, PSZ pszClassName)
    {
    CHAR  szBuffer[CCHMAXCLASSNAME];
    HENUM henum;
    HWND  hwnd = NULLHANDLE;

    if ((henum = WinBeginEnumWindows (hwndParent)) != NULLHANDLE)
        {
        while ((hwnd = WinGetNextWindow (henum)) != NULLHANDLE)
            {
            if (!WinIsWindow (hab, hwnd))
                continue;

            WinQueryClassName (hwnd, CCHMAXCLASSNAME, szBuffer);
            DebugE ("FindWindowOfClass => enumerated: ", szBuffer);
            if (strcmp (szBuffer, pszClassName) == 0)
                {
                DebugE ("FindWindowOfClass => class found: ", pszClassName);
                break;
                }
            }

        WinEndEnumWindows (henum);
        }

    return hwnd;
    }

/*******************************************************************\
    FindScrollbar searches all scrollbars being child of hwndParent
    that scroll ulDirection. If there is only one, its id is
    returned. If there are more (up to 16), the scrollbar next to
    the child of hwndParent that contains the mouse pointer
    will be returned
    Input:  hwndParent: window to be evaluated
            ulDirection: SCROLL_DIR_HORZ or SCROLL_DIR_VERT
            pptlPointer: pointer position on screen
    Return: id of scrollbar; NULLHANDLE if not found
\*******************************************************************/
USHORT FindScrollbar (HWND hwndParent, ULONG ulDirection, PPOINTL pptlPointer)
    {
    CHAR   szBuffer[10];   //3];
    SWP    swp;
    ULONG  ulWinStyle;
    HENUM  henum;
    HWND   hwndChild;
    HWND   hwnd;
    HWND   hwndSB[16];
    ULONG  ulcScrollbar = 0;
    USHORT usScrollbarID = 0;

    hwndChild = NextChildBelow (hwndParent, pptlPointer);

    if ((henum = WinBeginEnumWindows (hwndParent)) != NULLHANDLE)
        {
        while ((hwnd = WinGetNextWindow (henum)) != NULLHANDLE)
            {
            if (!WinIsWindow (hab, hwnd))
                continue;

            WinQueryClassName (hwnd, 3, szBuffer);
            WinQueryWindowPos (hwnd, &swp);
            // check for scrollbar class; non-empty
            if ((strcmp (szBuffer, "#8") == 0) && swp.cx && swp.cy)
                {
                // query style bits of this scroll bar window
                ulWinStyle = WinQueryWindowULong (hwnd, QWL_STYLE);

                // is scroll bar enabled and visible?
                if ((ulWinStyle & (WS_DISABLED | WS_VISIBLE)) == WS_VISIBLE)
                    {
                    // return window handle if it matches fHorizontal
                    if (((ulDirection == SCROLL_DIR_VERT) && (ulWinStyle & SBS_VERT)) ||
                        ((ulDirection == SCROLL_DIR_HORZ) && ((ulWinStyle & SBS_VERT) == 0)))
                        {
                        hwndSB[ulcScrollbar++] = hwnd;
                        if (ulcScrollbar >= 16)
                            break;
                        }
                    }
                }
            }

        WinEndEnumWindows (henum);
        }

    if ((ulcScrollbar > 1) && (hwndChild != NULLHANDLE))
        {
        SWP   swpChild;
        ULONG ul;

        WinQueryWindowPos (hwndChild, &swpChild);

        for (ul = 0; ul < ulcScrollbar; ul++)
            {
            WinQueryWindowPos (hwndSB[ul], &swp);
            if (ulDirection == SCROLL_DIR_HORZ)
                {
                if ((max (swp.x, swp.x+swp.cx) > swpChild.x) &&
                    (min (swp.x, swp.x+swp.cx) < swpChild.x+swpChild.cx))
                    {
                    hwnd = hwndSB[ul];
                    break;
                    }
                }
            else
                {
                if ((max (swp.y, swp.y+swp.cy) > swpChild.y) &&
                    (min (swp.y, swp.y+swp.cy) < swpChild.y+swpChild.cy))
                    {
                    hwnd = hwndSB[ul];
                    break;
                    }
                }
            }
        }
    else
        {
        if (ulcScrollbar == 0)
            hwnd = NULLHANDLE;
        else
            hwnd = hwndSB[0];
        }

    if (hwnd)
        usScrollbarID = WinQueryWindowUShort (hwnd, QWS_ID);

    return usScrollbarID;
    }

HWND findOwnerFrame (HWND hwnd)
    {
    HWND  hwndOwner;
    ULONG flFlags;
    CHAR  szClassname[4];

    hwndOwner = hwnd;
    while (hwndOwner != NULLHANDLE && hwndOwner != HWND_DESKTOP && hwndOwner != HWND_OBJECT)
        {
        flFlags = (ULONG)WinSendMsg (hwndOwner, WM_QUERYFRAMEINFO, MPVOID, MPVOID);
        WinQueryClassName (hwndOwner, 4, szClassname);
        hwnd = hwndOwner;
        if ((flFlags & FI_FRAME) || (strcmp (szClassname, "#1") == 0))
            break;
        hwndOwner = WinQueryWindow (hwnd, QW_OWNER);
        }

    return hwnd;
    }

VOID keyViaIOCTL (HWND hwnd, USHORT usRepeat, USHORT usMakeCode)
    {
    ULONG    ulParmLen;
    KBDEVENT kbdEvent;

    WinSetFocus (HWND_DESKTOP, hwnd);

    ulParmLen = sizeof (KBDEVENT);
    kbdEvent.uscRepeat   = usRepeat;
    kbdEvent.usMakeCode  = SHORT1FROMMP (usMakeCode);
    kbdEvent.usBreakCode = SHORT1FROMMP (usMakeCode) + 0x8000;

    DosDevIOCtl (hFileDriver,                   // Device handle
                 IOCTL_POINTINGDEVICE,          // Device category: Pointing-device control
                 MOU_SETKBDEVENT,               // Function code: send keyboard event
                 &kbdEvent,                     // Parameter packet: timeout value
                 sizeof (kbdEvent),             // Maximum size of parm packet
                 &ulParmLen,                    // Size of param packet on exit
                 NULL,                          // Buffer for data packet: not used
                 0,                             // Maximum size of data packet
                 NULL);                         // Size of data packet: not used

    return;
    }

/*******************************************************************\
    setMouseTimingValues: sets the acceleration parameters for
                          mouse movement via IOCTL call
    Eingang: ulLevel1:   acceleration threshold 1
             ulLevel2:   acceleration threshold 2
             ulLev1Mult: acceleration multiplier 1
             ulLev2Mult: acceleration multiplier 2
    Return:              TRUE: successful
\*******************************************************************/
BOOL setMouseTimingValues (HFILE hfMouse)
    {
    THRESHOLD strucThreshold;
    ULONG     ulParmLen;
    APIRET    rc;

    strucThreshold.Length   = sizeof (THRESHOLD);
    strucThreshold.Level1   = pShMemMouseData->ulAccelLevel1;
    strucThreshold.Lev1Mult = pShMemMouseData->ulAccelLvl1Mult;
    strucThreshold.Level2   = pShMemMouseData->ulAccelLevel2;
    strucThreshold.Lev2Mult = pShMemMouseData->ulAccelLvl2Mult;

    ulParmLen = sizeof (THRESHOLD);
    rc = DosDevIOCtl (hfMouse,                      // Device handle
                      IOCTL_POINTINGDEVICE,         // Device category: Pointing-device control
                      MOU_REASSIGNTHRESHOLDVALUES,  // Function code: reassign threshold values
                      &strucThreshold,              // Parameter packet
                      sizeof (strucThreshold),      // Maximum size of parm packet
                      &ulParmLen,                   // Size of param packet on exit: not used
                      NULL,                         // Buffer for data packet
                      0,                            // Maximum size of data packet
                      NULL);                        // Size of data packet

    return (rc == NO_ERROR ? TRUE : FALSE);
    }

PRESDATA FindApplicationDefinition (HWND hwnd, BOOL bRetDefault, PCHAR pResource, ULONG ulcResource, ULONG ulDirection, ULONG ulScrollMode, PSZ pszClass, PSZ pszParentClass, PSZ *ppszSpecClassName)
    {
    PRESDATA        pResData;
    PSZ             pszProcessName;
    PSZ             pszClassName;
    PSZ             pszParentClassName;

    /* Search for window class in resource data */
    pszProcessName = pResource;
    for (;;)
        {
        /* exit for security reasons */
        if ((ULONG)pszProcessName - (ULONG)pResource >= ulcResource)
            {
            // profile data don't contain default data; they
            // have to be taken from rc-file
            if (!bRetDefault)
                pResData = NULL;
            break;
            }

        pszClassName       = (PCHAR)pszProcessName                  + strlen (pszProcessName)     + 1;
        pszParentClassName = (PCHAR)pszClassName                    + strlen (pszClassName)       + 1;
        *ppszSpecClassName = (PCHAR)pszParentClassName              + strlen (pszParentClassName) + 1;
        pResData           = (PRESDATA)((PCHAR)(*ppszSpecClassName) + strlen (*ppszSpecClassName)  + 1);

        if (*pszProcessName     == '\0' &&
            *pszClassName       == '\0' &&
            *pszParentClassName == '\0' &&
            **ppszSpecClassName == '\0' &&
            (ulScrollMode == (ULONG)pResData->usScrollMode))
            break;

        if (*pszClassName == '\0' || strcmp (pszClassName, pszClass) == 0)
            {
            if (*pszParentClassName == '\0' || strcmp (pszParentClassName, pszParentClass) == 0)
                {
                if (CheckProcessName (hwnd, pszProcessName))
                    {
                    if (ulScrollMode & (ULONG)pResData->usScrollMode)
                        {
                        if ((ulDirection == SCROLL_DIR_VERT) &&
                            (pResData->usVRelation == REL_NONE) &&
                            (pResData->usMsgUp == WM_NULL))
                            DebugE ("HandleWheelEvent", "jump");
                        else
                            {
                            DebugUL ("HandleWheelEvent", "class found in resource table; message = ", pResData->usMsgUp);
                            break;
                            }
                        }
                    }
                }
            }
        pszProcessName = (PSZ)((PCHAR)pResData + sizeof (RESDATA));
        }

    return pResData;
    }

VOID setShiftKeys (VOID)
    {
    // set shift state
    WinSetKeyboardStateTable (HWND_DESKTOP, keyState, FALSE);   // get a copy of the keyboard state.

    bKeyShift = keyState[VK_SHIFT];
    bKeyAlt   = keyState[VK_ALT];
    bKeyCtrl  = keyState[VK_CTRL];

    keyState[VK_SHIFT] =
    keyState[VK_ALT]   =
    keyState[VK_CTRL]  = 0;

    WinSetKeyboardStateTable (HWND_DESKTOP, keyState, TRUE);    // set the keyboard state

    return;
    }

VOID restoreShiftKeys (VOID)
    {
    // restore previous shift state
    keyState[VK_SHIFT] = bKeyShift;
    keyState[VK_ALT]   = bKeyAlt;
    keyState[VK_CTRL]  = bKeyCtrl;

    WinSetKeyboardStateTable (HWND_DESKTOP, keyState, TRUE);    // set the keyboard state

    return;
    }

HWND HandleWheelEvent (HWND hwnd, PPOINTL pptlPointer, ULONG ulDirection, SHORT sWheelTurns, ULONG ulScrollNum, ULONG ulScrollMode)
    {
    static PVOID    pResource   = NULL;
    static ULONG    ulcResource = 0;
    PRESDATA        pResData;
    HWND            hwndRel;
    SHORT           i;
    CHAR            szClass[CCHMAXCLASSNAME];
    CHAR            szParentClass[CCHMAXCLASSNAME];
    PSZ             pszSpecClassName;
    USHORT          usRelation;
    USHORT          usOpt;
    USHORT          usMsg1;
    USHORT          usMsg2;

    if (pResource == NULL)
        {
        DosQueryResourceSize (hModule, RT_RCDATA, RCID_POSTDATA, &ulcResource);
        DosGetResource (hModule, RT_RCDATA, RCID_POSTDATA, (PPVOID)&pResource);
        }

    /* Determine window class of hwnd */
    WinQueryClassName (hwnd, CCHMAXCLASSNAME, szClass);
    DebugUL ("HandleWheelEvent", "hwnd = ", hwnd);
    DebugE ("HandleWheelEvent => class name: ", szClass);
    hwndRel = WinQueryWindow (hwnd, QW_PARENT);
    WinQueryClassName (hwndRel, CCHMAXCLASSNAME, szParentClass);
    DebugE ("HandleWheelEvent => parent class name: ", szParentClass);

    /* Search for window class in resource data */
    pResData = FindApplicationDefinition (hwnd, FALSE, pShMemMouseData->cApplications, pShMemMouseData->ulcApplications, ulDirection, ulScrollMode, szClass, szParentClass, &pszSpecClassName);
    if (pResData == NULL)
        pResData = FindApplicationDefinition (hwnd, TRUE, pResource, ulcResource, ulDirection, ulScrollMode, szClass, szParentClass, &pszSpecClassName);

    /* copy relevant parameters */
    switch (ulDirection)
        {
        case SCROLL_DIR_HORZ:
            usRelation = pResData->usHRelation;
            usOpt      = pResData->usHOpt;
            usMsg1     = pResData->usMsgLeft;
            usMsg2     = pResData->usMsgRight;
            break;

        default:
            usRelation = pResData->usVRelation;
            usOpt      = pResData->usVOpt;
            usMsg1     = pResData->usMsgUp;
            usMsg2     = pResData->usMsgDown;
            break;
        }

    /* Handle requested relation */
    switch (usRelation)
        {
        case REL_PARENT:
            hwndRel = WinQueryWindow (hwnd, QW_PARENT);
            DebugUL ("HandleWheelEvent", "parent window: ", hwndRel);
            break;

        case REL_OWNER:
            hwndRel = WinQueryWindow (hwnd, QW_OWNER);
            DebugUL ("HandleWheelEvent", "owner window: ", hwndRel);
            break;

        case REL_NEXT:
            hwndRel = NextWindowBelow (hwnd, pptlPointer);
            DebugUL ("HandleWheelEvent", "next window: ", hwndRel);
            break;

        case REL_IGLB:
            hwndRel = FindOwnedListbox (hwnd);
            if (hwndRel != NULLHANDLE)
                hwndRel = NextWindowBelow (hwnd, pptlPointer);
            DebugUL ("HandleWheelEvent", "iglb window: ", hwndRel);
            break;

        case REL_SPEC:
            hwndRel = WinQueryWindow (hwnd, QW_PARENT);
            hwndRel = FindWindowOfClass (hwndRel, pszSpecClassName);
            DebugUL ("HandleWheelEvent", "spec window: ", hwndRel);
            break;

        default:    // handles REL_NONE and resource errors
            if (usMsg1 == WM_NULL)
                hwndRel = NULLHANDLE;
            else
                hwndRel = hwnd;
            DebugUL ("HandleWheelEvent", "handle this window: ", hwndRel);
        }

    Debug2UL ("HandleWheelEvent", "up: ", (ULONG)usMsg1, " down: ", (ULONG)usMsg2);

    if (!WinIsWindowEnabled (hwndRel))
        hwndRel = NULLHANDLE;

    if (hwndRel != NULLHANDLE)
        {
        /* Perform requested action */
        if (sWheelTurns < 0)        // action: up
            {
            switch (usMsg1)
                {
                case WM_NULL:
                    break;

                case WM_VSCROLL:
                    sWheelTurns *= -ulScrollNum;

                case WM_VSCROLL1:
                    DebugE ("HandleWheelEvent", "WM_VSCROLL(1) up");
                    if (usOpt == 0)
                        usOpt = FindScrollbar (hwndRel, SCROLL_DIR_VERT, pptlPointer);
                    DebugUL ("HandleWheelEvent", "Scrollbar-ID = ", (ULONG)usOpt);
                    for (i = 1; i <= sWheelTurns; i++)
                        WinPostMsg (hwndRel,
                                    WM_VSCROLL,
                                    MPFROMSHORT (usOpt),
                                    MPFROM2SHORT (0, SB_LINEUP));
                    hwndRel = NULLHANDLE;
                    break;

                case WM_HSCROLL:
                    sWheelTurns *= ulScrollNum;

                case WM_HSCROLL1:
                    DebugE ("HandleWheelEvent", "WM_HSCROLL(1) left");
                    sWheelTurns *= -1;
                    if (usOpt == 0)
                        usOpt = FindScrollbar (hwndRel, SCROLL_DIR_HORZ, pptlPointer);
                    DebugUL ("HandleWheelEvent", "Scrollbar-ID = ", (ULONG)usOpt);
                    for (i = 0; i < sWheelTurns; i++)
                        WinPostMsg (hwndRel,
                                    WM_HSCROLL,
                                    MPFROMSHORT (usOpt),
                                    MPFROM2SHORT (0, SB_LINELEFT));
                    hwndRel = NULLHANDLE;
                    break;

                case WM_CHAR:
                    DebugE ("HandleWheelEvent", "WM_CHAR message");
                    switch (usOpt)
                        {
                        case VKP_PAGE:
                            DebugUL ("HandleWheelEvent", "WM_CHAR PgUp:", sWheelTurns);
                            for (i = 0; i < -sWheelTurns; i++)
                                {
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE, 1, 0x11),
                                            MPFROM2SHORT (0x49E0, VK_PAGEUP));
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_KEYUP | KC_LONEKEY, 1, 0x11),
                                            MPFROM2SHORT (0x49E0, VK_PAGEUP));
                                }
                            break;

                        case VKP_CLR:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SLR:
                            sWheelTurns *= -1;
                            DebugUL ("HandleWheelEvent", "WM_CHAR CsrLeft:", sWheelTurns);
                            for (i = 0; i < sWheelTurns; i++)
                                {
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE, 1, 0x15),
                                            MPFROM2SHORT (0x4BE0, VK_LEFT));
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_KEYUP | KC_LONEKEY, 1, 0x15),
                                            MPFROM2SHORT (0x4BE0, VK_LEFT));
                                }
                            break;

                        case VKP_CUD:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SUD:
                            sWheelTurns *= -1;
                            DebugUL ("HandleWheelEvent", "WM_CHAR CsrUp:", sWheelTurns);
                            for (i = 0; i < sWheelTurns; i++)
                                {
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE, 1, 0x61),
                                            MPFROM2SHORT (0x48E0, VK_UP));
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_KEYUP | KC_LONEKEY, 1, 0x61),
                                            MPFROM2SHORT (0x48E0, VK_UP));
                                }
                            break;
                        }
                    hwndRel = NULLHANDLE;
                    break;

                case SPBM_SPINUP:
                    DebugE ("HandleWheelEvent", "SPBM_SPINUP");
                    WinPostMsg (hwndRel, SPBM_SPINUP, (MPARAM)-sWheelTurns, MPVOID);
                    hwndRel = NULLHANDLE;
                    break;

                case SLM_SETSLIDERINFO:
                    DebugE ("HandleWheelEvent", "SLM_SETSLIDERINFO");
                    if (!(WinQueryWindowULong (hwndRel, QWL_STYLE) & SLS_READONLY))
                        {
                        ULONG ul;
                        ul = (ULONG)WinSendMsg (hwndRel, SLM_QUERYSLIDERINFO,
                                                MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                                MPFROMLONG (0));
                        WinPostMsg (hwndRel,
                                    SLM_SETSLIDERINFO,
                                    MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                    MPFROMLONG (ul+1));
                        }
                    hwndRel = NULLHANDLE;
                    break;

                case VM_SELECTITEM:
                    {
                    ULONG ul;
                    DebugE ("HandleWheelEvent", "VM_SELECTITEM");

                    ul = (ULONG)WinSendMsg (hwndRel, VM_QUERYSELECTEDITEM, MPVOID, MPVOID);
                    switch (usOpt)
                        {
                        case VS_VERT:
                            WinPostMsg (hwndRel, VM_SELECTITEM,
                                        MPFROM2SHORT ((USHORT)(ul&0xFFFF) + sWheelTurns, (USHORT)(ul>>16)),
                                        MPVOID);
                            break;

                        case VS_HORZ:
                            WinPostMsg (hwndRel, VM_SELECTITEM,
                                        MPFROM2SHORT ((USHORT)(ul&0xFFFF), (USHORT)((ul>>16) - sWheelTurns)),
                                        MPVOID);
                            break;
                        }
                    hwndRel = NULLHANDLE;

                    break;
                    }

                case CSM_SETVALUE:
                    {
                    PID    pid;
                    TID    tid;
                    PSHORT ps;
                    APIRET rc;
                    DebugE ("HandleWheelEvent", "CSM_SETVALUE");

                    WinQueryWindowProcess (hwndRel, &pid, &tid);
                    if (NO_ERROR == DosAllocSharedMem ((PPVOID)&ps, NULL, sizeof (SHORT), PAG_COMMIT | OBJ_GIVEABLE | OBJ_TILE | PAG_READ | PAG_WRITE))
                        {
                        if (NO_ERROR == DosGiveSharedMem ((PVOID)ps, pid, PAG_READ | PAG_WRITE))
                            {
                            WinSendMsg (hwndRel, CSM_QUERYVALUE, MPFROMP (ps), MPVOID);
                            WinPostMsg (hwndRel, CSM_SETVALUE, MPFROMSHORT ((*ps) + sWheelTurns), MPVOID);
                            }
                        DosFreeMem ((PVOID)ps);
                        }
                    hwndRel = NULLHANDLE;
                    break;
                    }

                case WM_CONTROL:
                    {
                    USHORT usKeyCode;

                    sWheelTurns *= -1;

                    switch (usOpt)
                        {
                        case VKP_PAGE:
                            usKeyCode = 0x49E0;
                            break;

                        case VKP_CLR:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SLR:
                            usKeyCode = 0x4BE0;
                            break;

                        case VKP_CUD:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SUD:
                            usKeyCode = 0x48E0;
                            break;
                        }

                    keyViaIOCTL (hwndRel, sWheelTurns, usKeyCode);
                    hwndRel = NULLHANDLE;
                    break;
                    }

                case WM_COMMAND:
                    sWheelTurns *= -1;

                    for (i = 1; i <= sWheelTurns; i++)
                        WinPostMsg (hwndRel, WM_COMMAND, MPFROMSHORT (usOpt + 1), MPVOID);

                    hwndRel = NULLHANDLE;
                    break;

                default:
                    hwndRel = NULLHANDLE;
                }
            }
        else if (sWheelTurns > 0)   // action: down
            {
            switch (usMsg2)
                {
                case WM_NULL:
                    break;

                case WM_VSCROLL:
                    sWheelTurns *= ulScrollNum;

                case WM_VSCROLL1:
                    DebugE ("HandleWheelEvent", "WM_VSCROLL(1) down");
                    if (usOpt == 0)
                        usOpt = FindScrollbar (hwndRel, SCROLL_DIR_VERT, pptlPointer);
                    DebugUL ("HandleWheelEvent", "Scrollbar-ID = ", (ULONG)usOpt);
                    for (i = 1; i <= sWheelTurns; i++)
                        WinPostMsg (hwndRel,
                                    WM_VSCROLL,
                                    MPFROMSHORT (usOpt),
                                    MPFROM2SHORT (0, SB_LINEDOWN));
                    hwndRel = NULLHANDLE;
                    break;

                case WM_HSCROLL:
                    sWheelTurns *= ulScrollNum;

                case WM_HSCROLL1:
                    DebugE ("HandleWheelEvent", "WM_HSCROLL(1) right");
                    if (usOpt == 0)
                        usOpt = FindScrollbar (hwndRel, SCROLL_DIR_HORZ, pptlPointer);
                    DebugUL ("HandleWheelEvent", "Scrollbar-ID = ", (ULONG)usOpt);
                    for (i = 0; i < sWheelTurns; i++)
                        WinPostMsg (hwndRel,
                                    WM_HSCROLL,
                                    MPFROMSHORT (usOpt),
                                    MPFROM2SHORT (0, SB_LINERIGHT));
                    hwndRel = NULLHANDLE;
                    break;

                case WM_CHAR:
                    DebugE ("HandleWheelEvent", "WM_CHAR message");
                    switch (usOpt)
                        {
                        case VKP_PAGE:
                            DebugUL ("HandleWheelEvent", "WM_CHAR PgDn:", sWheelTurns);
                            for (i = 0; i < sWheelTurns; i++)
                                {
                                WinPostMsg (hwndRel,
                                        WM_CHAR,
                                        MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE, 1, 0x12),
                                        MPFROM2SHORT (0x51E0, VK_PAGEDOWN));

                                WinPostMsg (hwndRel,
                                        WM_CHAR,
                                        MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_KEYUP | KC_LONEKEY, 1, 0x12),
                                        MPFROM2SHORT (0x51E0, VK_PAGEDOWN));
                                }
                            break;

                        case VKP_CLR:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SLR:
                            DebugUL ("HandleWheelEvent", "WM_CHAR CsrRight:", sWheelTurns);
                            for (i = 0; i < sWheelTurns; i++)
                                {
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE, 1, 0x17),
                                            MPFROM2SHORT (0x4DE0, VK_RIGHT));
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_KEYUP | KC_LONEKEY, 1, 0x17),
                                            MPFROM2SHORT (0x4DE0, VK_RIGHT));
                                }
                            break;

                        case VKP_CUD:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SUD:
                            DebugUL ("HandleWheelEvent", "WM_CHAR CsrDown:", sWheelTurns);
                            for (i = 0; i < sWheelTurns; i++)
                                {
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE, 1, 0x66),
                                            MPFROM2SHORT (0x50E0, VK_DOWN));
                                WinPostMsg (hwndRel,
                                            WM_CHAR,
                                            MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_KEYUP | KC_LONEKEY, 1, 0x66),
                                            MPFROM2SHORT (0x50E0, VK_DOWN));
                                }
                            break;
                        }
                    hwndRel = NULLHANDLE;
                    break;

                case SPBM_SPINDOWN:
                    DebugE ("HandleWheelEvent", "SPBM_SPINDOWN");
                    WinPostMsg (hwndRel, SPBM_SPINDOWN, (MPARAM)sWheelTurns, MPVOID);
                    hwndRel = NULLHANDLE;
                    break;

                case SLM_SETSLIDERINFO:
                    DebugE ("HandleWheelEvent", "SLM_SETSLIDERINFO");
                    if (!(WinQueryWindowULong (hwndRel, QWL_STYLE) & SLS_READONLY))
                        {
                        ULONG ul;
                        ul = (ULONG)WinSendMsg (hwndRel, SLM_QUERYSLIDERINFO,
                                                MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                                MPFROMLONG (0));
                        WinPostMsg (hwndRel,
                                    SLM_SETSLIDERINFO,
                                    MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                    MPFROMLONG (ul-1));
                        }
                    hwndRel = NULLHANDLE;
                    break;

                case VM_SELECTITEM:
                    {
                    ULONG ul;
                    DebugE ("HandleWheelEvent", "VM_SELECTITEM");

                    ul = (ULONG)WinSendMsg (hwndRel, VM_QUERYSELECTEDITEM, MPVOID, MPVOID);

                    switch (usOpt)
                        {
                        case VS_VERT:
                            WinPostMsg (hwndRel, VM_SELECTITEM,
                                        MPFROM2SHORT ((USHORT)(ul&0xFFFF) + sWheelTurns, (USHORT)(ul>>16)),
                                        MPVOID);
                            break;

                        case VS_HORZ:
                            WinPostMsg (hwndRel, VM_SELECTITEM,
                                        MPFROM2SHORT ((USHORT)(ul&0xFFFF), (USHORT)((ul>>16) - sWheelTurns)),
                                        MPVOID);
                            break;
                        }
                    hwndRel = NULLHANDLE;

                    break;
                    }

                case CSM_SETVALUE:
                    {
                    PID    pid;
                    TID    tid;
                    PSHORT ps;
                    APIRET rc;
                    DebugE ("HandleWheelEvent", "CSM_SETVALUE");

                    WinQueryWindowProcess (hwndRel, &pid, &tid);
                    if (NO_ERROR == DosAllocSharedMem ((PPVOID)&ps, NULL, sizeof (SHORT), PAG_COMMIT | OBJ_GIVEABLE | OBJ_TILE | PAG_READ | PAG_WRITE))
                        {
                        if (NO_ERROR == DosGiveSharedMem ((PVOID)ps, pid, PAG_READ | PAG_WRITE))
                            {
                            WinSendMsg (hwndRel, CSM_QUERYVALUE, MPFROMP (ps), MPVOID);
                            WinPostMsg (hwndRel, CSM_SETVALUE, MPFROMSHORT ((*ps) - sWheelTurns), MPVOID);
                            }
                        DosFreeMem ((PVOID)ps);
                        }
                    hwndRel = NULLHANDLE;
                    break;
                    }

                case WM_CONTROL:
                    {
                    USHORT usKeyCode;

                    switch (usOpt)
                        {
                        case VKP_PAGE:
                            usKeyCode = 0x51E0;
                            break;

                        case VKP_CLR:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SLR:
                            usKeyCode = 0x4DE0;
                            break;

                        case VKP_CUD:
                            sWheelTurns *= ulScrollNum;

                        case VKP_SUD:
                            usKeyCode = 0x50E0;
                            break;
                        }

                    keyViaIOCTL (hwndRel, sWheelTurns, usKeyCode);
                    hwndRel = NULLHANDLE;
                    break;
                    }

                case WM_COMMAND:
                    for (i = 1; i <= sWheelTurns; i++)
                        WinPostMsg (hwndRel, WM_COMMAND, MPFROMSHORT (usOpt), MPVOID);

                    hwndRel = NULLHANDLE;
                    break;

                default:
                    hwndRel = NULLHANDLE;
                }
            }
        else                        // no action
            hwndRel = NULLHANDLE;
        }

    return hwndRel;
    }

/*******************************************************************\
    Starts the WheelThread after setting up the shared memory and
    needed semaphores for communication with WPS class
    Return: TRUE:  successul
\*******************************************************************/
VOID initWheelThread (VOID)
    {
    TID  tid;

    /* initialize data structure */
    DosCreateThread (&tid, (PFNTHREAD)WheelThread,  (ULONG)0, 0L, 0x8000);
    DosCreateThread (&tid, (PFNTHREAD)UpdateThread, (ULONG)0, 0L, 0x8000);
    DebugE ("initWheelThread", "Thread started");

    return;
    }

/*******************************************************************\
    Detects mouse driver version. If AMouse driver and version
    is 2.0 or newer, extended mode is set.
    return: TRUE:  extended mode successfully set
            FALSE: otherwise
\*******************************************************************/
BOOL SetExtendedMode (VOID)
    {
    APIRET      rc;
    ULONG       ulDataLen;                          // Size of the Data packet
    USHORT      usMajor, usMinor;
    EMOUVERDATA usDataPkt;                          // Data packet

    if (hFileDriver == NULLHANDLE)
        return FALSE;

    // check version of driver; must be 2.0 or later
    usDataPkt.usMagic = 0x55AA;
    ulDataLen    = sizeof (usDataPkt.usMagic);
    rc = DosDevIOCtl (hFileDriver,              // Device handle
                      IOCTL_POINTINGDEVICE,     // Device category: pointing-device control
                      MOU_VER,                  // Function code: gets version number of driver
                      NULL,                     // No Parameter packet
                      0,                        // Maximum size of parm packet
                      NULL,                     // Size of param packet
                      &usDataPkt,               // Buffer for data packet
                      ulDataLen,                // Maximum size of data packet
                      &ulDataLen);              // Size of data packet

    usMajor = usDataPkt.usMagic >> 8;
    usMinor = usDataPkt.usMagic & 0xFF;

    DebugUL ("SetExtendedMode", "usMajor = ", (ULONG)usMajor);
    DebugUL ("SetExtendedMode", "usMinor = ", (ULONG)usMinor);

    if (usMajor < 2 || usMinor > 99)
        return FALSE;

    if (usMajor == 2 && usMinor == 0)
        driverMode = drvMode_Ext1;
    else
        driverMode = drvMode_Ext2;

    // switch to extended mode 1 by setting another magic (0x424E) and no additional bytes
    usDataPkt.usMagic   = 0x424E;               // magic ("NB")
    usDataPkt.usParmNum = 0;                    // no additional bytes
    ulDataLen = 2 * sizeof (USHORT);
    rc = DosDevIOCtl (hFileDriver,              // Device handle
                      IOCTL_POINTINGDEVICE,     // Device category: pointing-device control
                      MOU_VER,                  // Function code: gets version number of driver
                      NULL,                     // No Parameter packet
                      0,                        // Maximum size of parm packet
                      NULL,                     // Size of param packet
                      &usDataPkt,               // Buffer for data packet
                      ulDataLen,                // Maximum size of data packet
                      &ulDataLen);              // Size of data packet

    DebugE ("SetExtendedMode", "extended mode 1 set");

    return (rc == NO_ERROR) ? TRUE : FALSE;
    }

/*******************************************************************\
    Sets mode for fullscreen modes if allowed by driver version
    (2.1 or newer).
    return: TRUE:  extended mode successfully set
            FALSE: otherwise
\*******************************************************************/
BOOL SetFullScreenMode (VOID)
    {
    APIRET      rc;
    ULONG       ulDataLen;                          // Size of the Data packet
    EMOUVERDATA usDataPkt;                          // Data packet

    DebugE ("SetFullScreenMode", "entered");

    if (driverMode == drvMode_Ext2)
        {
        // switch to extended mode 2 by setting another magic (0x424E) and additional 2 bytes
        usDataPkt.usMagic   = 0x424E;           // magic ("NB")
        usDataPkt.usParmNum = 5;                // 5 parameters

        switch (pShMemMouseData->ulScrollMode)
            {
            case SCROLL_MODE_STD:
            case SCROLL_MODE_LINE:
                usDataPkt.bScrollMode = ((pShMemMouseData->ulCurrScrollDir == SCROLL_DIR_VERT) ?
                                         FSSCROLL_MODE_VERT : FSSCROLL_MODE_HORZ);
                usDataPkt.bScrollNum  = ((pShMemMouseData->ulScrollNum <= 15) ? pShMemMouseData->ulScrollNum : 15);
                break;

            case SCROLL_MODE_PAGE:
                usDataPkt.bScrollMode = FSSCROLL_MODE_PAGE;
                usDataPkt.bScrollNum  = ((pShMemMouseData->ulScrollNum <= 15) ? pShMemMouseData->ulScrollNum : 15);
                break;

            default:
                usDataPkt.bScrollMode = FSSCROLL_MODE_VERT;
                usDataPkt.bScrollNum  = 0;
            }
        usDataPkt.bPollingRate = pShMemMouseData->ulPollingRate;
        usDataPkt.bWheelCount  = pShMemMouseData->ulWheelCount;
        usDataPkt.bSmartCruise = (BYTE)(pShMemMouseData->ulSmartCruise);

        ulDataLen = 2 * sizeof (USHORT) + usDataPkt.usParmNum;

        Debug2UL ("SetFullScreenMode", "set mode, bScrollMode = ", (ULONG)usDataPkt.bScrollMode,
                                                " bScrollNum  = ", (ULONG)usDataPkt.bScrollNum);
        DebugUL ("SetFullScreenMode", "set mode, polling rate = ", (ULONG)usDataPkt.bPollingRate);

        rc = DosDevIOCtl (hFileDriver,          // Device handle
                          IOCTL_POINTINGDEVICE, // Device category: pointing-device control
                          MOU_VER,              // Function code: gets version number of driver
                          NULL,                 // No Parameter packet
                          0,                    // Maximum size of parm packet
                          NULL,                 // Size of param packet
                          &usDataPkt,           // Buffer for data packet
                          ulDataLen,            // Maximum size of data packet
                          &ulDataLen);          // Size of data packet
        return (rc == NO_ERROR) ? TRUE : FALSE;
        }

    return FALSE;
    }

USHORT getShiftKeyState (VOID)
    {
    USHORT us = 0;

    if (WinGetKeyState (HWND_DESKTOP, VK_SHIFT) & 0x8000)
        us |= KC_SHIFT;

    if (WinGetKeyState (HWND_DESKTOP, VK_CTRL)  & 0x8000)
        us |= KC_CTRL;

    if (WinGetKeyState (HWND_DESKTOP, VK_ALT)   & 0x8000)
        us |= KC_ALT;

    return us;
    }

USHORT getMouseButtonState (VOID)
    {
    USHORT us = 0;

    if (WinGetKeyState (HWND_DESKTOP, VK_BUTTON1) & 0x8000)
        us |= MK_BUTTON1;

    if (WinGetKeyState (HWND_DESKTOP, VK_BUTTON2) & 0x8000)
        us |= MK_BUTTON2;

    if (WinGetKeyState (HWND_DESKTOP, VK_BUTTON3) & 0x8000)
        us |= MK_BUTTON3;

    return us;
    }

VOID setMasterVolume (SHORT sIncrement)
    {
    APIRET rc;

    if (sIncrement)
        {
        if (pfnMciSetMasterVolume && pfnMciGetMasterVolume)
            {
            lVolume = pfnMciGetMasterVolume ();

            if (lVolume >= 0)
                {
                lVolume = lVolume + sIncrement;
                if (lVolume > 100) lVolume = 100;
                if (lVolume < 0)   lVolume = 0;

                pfnMciSetMasterVolume (lVolume);

                DebugUL ("WinSetMasterVolume", "tid = ", tidVolumePaint);
                if (tidVolumePaint == NULLHANDLE)
                    DosCreateThread (&tidVolumePaint,
                                     (PFNTHREAD)PaintVolumeThread,
                                     (ULONG)0, CREATE_READY, 0x8000);

                rc = DosPostEventSem (hevPaintVolume);
                if (rc != NO_ERROR)
                    DebugUL ("WinSetMasterVolume", "rc = ", rc);
                }
            }
        }

    return;
    }

BOOL WinSetMasterVolume (SHORT sIncrement)
    {
    BOOL bRC = TRUE;
    PTIB ptib;
    PPIB ppib;

    DosExitList (EXLST_ADD, (PFNEXITLIST)exitList);

    /* correct session type? */
    DosGetInfoBlocks (&ptib, &ppib);
    if (ppib->pib_ultype == 3)
        setMasterVolume (sIncrement);
    else
        bRC = FALSE;

    return bRC;
    }

VOID handleWheelTurns (SHORT sWheelTurns, ULONG ulScrollDir, ULONG ulScrollNum, ULONG ulScrollMode, PPOINTL pPointer, ULONG ulWheelTarget)
    {
    HWND  hwnd2send2;
    ULONG ulcLoop, flWindow;

    WinQueryPointerPos (HWND_DESKTOP, pPointer);
    hwnd2send2 = (ulWheelTarget == WHEEL_TARGET_KBD) ? WinQueryFocus (HWND_DESKTOP) :
                                                       WinWindowFromPoint (HWND_DESKTOP, pPointer, TRUE);

    DebugS ("------------------------------------------");
    Debug2UL ("handleWheelTurns", "window = ", (ULONG)hwnd2send2, " numOfTurns = ", (ULONG)(sWheelTurns));

    if (pfnFindWindowHandle && pfnFindWindowHandle (hwnd2send2, &flWindow))
        {
        USHORT fwKeys;
        HWND   hwndMsg;

        DebugE ("handleWheelTurns", "registered window");

        if (flWindow & AW_OWNERFRAME)
            hwndMsg = findOwnerFrame (hwnd2send2);
        else
            hwndMsg = hwnd2send2;

        fwKeys =  getShiftKeyState ();      // KC_* values are identical to MK_* values for SHIFT/CTRL/ALT
        fwKeys |= getMouseButtonState ();   // add mouse button values

        WinPostMsg (hwndMsg,
                    (ulScrollDir == SCROLL_DIR_VERT ? WM_MOUSEWHEEL_VERT : WM_MOUSEWHEEL_HORZ),
                    MPFROM2SHORT (fwKeys, sWheelTurns * ulScrollNum * WHEEL_DELTA),
                    MPFROM2SHORT (pPointer->x, pPointer->y));
        }
    else
        {
        for (ulcLoop = 10; ulcLoop > 0; ulcLoop--)
            {
            if (hwnd2send2 == NULLHANDLE)
                break;

            setShiftKeys ();        // switch off shift keys
            hwnd2send2 = HandleWheelEvent (hwnd2send2,
                                           pPointer,
                                           ulScrollDir,
                                           sWheelTurns,
                                           ulScrollNum,
                                           ulScrollMode);
            restoreShiftKeys ();    // reset shift keys to original state
            }
        }

    return;
    }

/*******************************************************************\
    Thread that checks the wheel of the mouse and sends the
    appropriate window messages to the system.
    The thread never terminates
    Input: ulParm: unused
\*******************************************************************/
VOID _System WheelThread (ULONG ulParm)
    {
    ULONG       ulDataLen, ulAction;
    ULONG       ulWheelTarget, ulWheelTargetC, ulWheelTargetA, ulWheelTargetTmp;
    ULONG       ulScrollNum, ulScrollNumC, ulScrollNumA, ulScrollNumTmp;
    ULONG       ulScrollMode, ulScrollModeC, ulScrollModeA, ulScrollModeTmp;
    ULONG       ulCurrScrollDir, ulWheelCount;
    ULONG       ulcLoop;
    APIRET      rc;
    EMOUEXTDATA usDataPkt;
    POINTL      pointer;
    USHORT      usTimeout = 1000;            // ms
    HMQ         hmq = NULLHANDLE;

    USHORT      usShiftKeyState;

    // variables for acceleration
    ULONG       ulTimestamp1, ulTimestamp2;  // calculation of time difference
    ULONG       ulcAcceleration;             // counter for acceleration steps
    ULONG       ulAcceleration;              // current acceleration increment
    LONG        lDelay;                      // acceleration delay in ms
    USHORT      usWheel1Dir, usWheel2Dir;    // flag for previous wheel direction

    static ULONG arBtnMsg[] = {WM_BUTTON4DOWN, WM_BUTTON4UP,
                               WM_BUTTON5DOWN, WM_BUTTON5UP,
                               WM_BUTTON6DOWN, WM_BUTTON6UP,
                               WM_BUTTON7DOWN, WM_BUTTON7UP};

    rc = DosOpen ("MOUSE$", &hFileDriver, &ulAction, 0,
                  FILE_NORMAL, FILE_OPEN,
                  OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                  (PEAOP2)NULL);

    if (rc != NO_ERROR)
        {
        DebugE ("WheelThread", "Thread terminated: could not open device");
        hFileDriver = NULLHANDLE;
        DosExit (EXIT_THREAD, 0);
        }

    DebugUL ("WheelThread", "hfile = ", hFileDriver);
    if (FALSE == SetExtendedMode ())
        {
        DebugE ("WheelThread", "wrong mouse driver: terminate thread");
        DosClose (hFileDriver);
        hFileDriver = NULLHANDLE;
        DosExit (EXIT_THREAD, 0);
        }

    DosPostEventSem (hevWheelThreadUpdate);

    /* Create a PM message queue necessary for sending messages to other processes */
    hmq = WinCreateMsgQueue (hab, 0);
    WinCancelShutdown (hmq, TRUE);

    DosQuerySysInfo (QSV_MS_COUNT, QSV_MS_COUNT, &ulTimestamp1, sizeof (ULONG));
    lDelay          = pShMemMouseData->ulAccelDelay;
    ulcAcceleration = pShMemMouseData->ulAccelValue;
    ulAcceleration  = 0;
    usWheel1Dir     =
    usWheel2Dir     = 0;

    for (;;)
        {
        /* Determine number of wheel turns since last read */
        ulDataLen = 0;
        rc = DosDevIOCtl (hFileDriver,                  // Device handle
                          IOCTL_POINTINGDEVICE,         // Device category: Pointing-device control
                          MOU_GETEXTDATA,               // Function code: gets number of wheel turns and buttons
                          &usTimeout,                   // Parameter packet: timeout value
                          sizeof (usTimeout),           // Maximum size of parm packet
                          NULL,                         // Size of param packet on exit: not used
                          &usDataPkt,                   // Buffer for data packet
                          sizeof (usDataPkt),           // Maximum size of data packet
                          &ulDataLen);                  // Size of data packet

        /* Handle acceleration of wheel */
        DosQuerySysInfo (QSV_MS_COUNT, QSV_MS_COUNT, &ulTimestamp2, sizeof (ULONG));
        if (ulcAcceleration < ACCEL_MAX_VALUE &&                        // value above deactivates acceleration
            ulTimestamp2 - ulTimestamp1 < ulThreshold &&                // overflow is not critical
            !(usWheel1Dir ^ (USHORT)usDataPkt.sWheelTurns  & 0x8000) && // vertical direction change
            !(usWheel2Dir ^ (USHORT)usDataPkt.sWheel2Turns & 0x8000))   // horizontal direction change
            {
            lDelay -= ulTimestamp2 - ulTimestamp1;
            if (lDelay <= 0)
                {
                lDelay = 0;
                if ((--ulcAcceleration == 0) && (ulAcceleration < 15))
                    {
                    ulAcceleration++;
                    ulcAcceleration = pShMemMouseData->ulAccelValue;
                    }
                }
            }
        else
            {
            lDelay          = pShMemMouseData->ulAccelDelay;
            ulcAcceleration = pShMemMouseData->ulAccelValue;
            ulAcceleration  = 0;
            }
        ulTimestamp1 = ulTimestamp2;
        usWheel1Dir  = (USHORT)usDataPkt.sWheelTurns  & 0x8000;
        usWheel2Dir  = (USHORT)usDataPkt.sWheel2Turns & 0x8000;

        /* initialization of variables for wheel handling */
        DosRequestMutexSem (hmtxWheelThread, (ULONG)SEM_INDEFINITE_WAIT);
        ulScrollMode    = pShMemMouseData->ulScrollMode;
        ulScrollModeC   = pShMemMouseData->ulScrollModeC;
        ulScrollModeA   = pShMemMouseData->ulScrollModeA;
        ulScrollNum     = pShMemMouseData->ulScrollNum + ulAcceleration;
        ulScrollNumC    = pShMemMouseData->ulScrollNumC + ulAcceleration;
        ulScrollNumA    = pShMemMouseData->ulScrollNumA + ulAcceleration;
        ulWheelTarget   = pShMemMouseData->ulWheelTarget;
        ulWheelTargetC  = pShMemMouseData->ulWheelTargetC;
        ulWheelTargetA  = pShMemMouseData->ulWheelTargetA;
        ulCurrScrollDir = pShMemMouseData->ulCurrScrollDir;
        ulWheelCount    = pShMemMouseData->ulWheelCount;
        DosReleaseMutexSem (hmtxWheelThread);

        if (ulWheelCount > 1)
            ulCurrScrollDir = SCROLL_DIR_VERT;

        if (rc == NO_ERROR)
            {
            usShiftKeyState = getShiftKeyState ();

            switch (usShiftKeyState)
                {
                case KC_NONE:
                    ulScrollModeTmp  = ulScrollMode;
                    ulScrollNumTmp   = ulScrollNum;
                    ulWheelTargetTmp = ulWheelTarget;
                    break;

                case KC_CTRL:
                    ulScrollModeTmp  = ulScrollModeC;
                    ulScrollNumTmp   = ulScrollNumC;
                    ulWheelTargetTmp = ulWheelTargetC;
                    break;

                case KC_ALT:
                    ulScrollModeTmp  = ulScrollModeA;
                    ulScrollNumTmp   = ulScrollNumA;
                    ulWheelTargetTmp = ulWheelTargetA;
                    break;

                default:
                    ulWheelTargetTmp = WHEEL_TARGET_POINTER;
                }

            /*****************************\
             *  handling of wheel turns  *
            \*****************************/
            switch (ulScrollModeTmp)
                {
                case SCROLL_MODE_STD:
                case SCROLL_MODE_LINE:
                case SCROLL_MODE_PAGE:
                    if (usDataPkt.sWheelTurns)
                        {
                        DebugUL ("WheelThread", "v wheel turns = ", (ULONG)(usDataPkt.sWheelTurns));
                        handleWheelTurns (usDataPkt.sWheelTurns,
                                          ulCurrScrollDir,
                                          ulScrollNumTmp,
                                          ulScrollModeTmp,
                                          &pointer,
                                          ulWheelTargetTmp);
                        }
                    if (ulWheelCount > 1 && usDataPkt.sWheel2Turns)
                        {
                        DebugUL ("WheelThread", "h wheel turns = ", (ULONG)(usDataPkt.sWheel2Turns));
                        handleWheelTurns (usDataPkt.sWheel2Turns,
                                          SCROLL_DIR_HORZ,
                                          ulScrollNumTmp,
                                          ulScrollModeTmp,
                                          &pointer,
                                          ulWheelTargetTmp);
                        }
                    break;

                case SCROLL_MODE_VOLUME:
                    if (usDataPkt.sWheelTurns)
                        setMasterVolume (usDataPkt.sWheelTurns * (-1-(SHORT)ulAcceleration));
                    break;
                }

            /*****************************\
             * handling of button events *
            \*****************************/
            // any button change?
            if (usDataPkt.usBtnState & BTNSTATE_CHANGE)
                {
                ULONG   ulc;
                HWND    hwnd2send2;

                if (pShMemMouseData->ulSmartCruise & SMART_CRUISE_VERT)
                    usDataPkt.usBtnState &= ~(BTNSTATE_7 | BTNSTATE_7CHG | BTNSTATE_8  | BTNSTATE_8CHG);
                if (pShMemMouseData->ulSmartCruise & SMART_CRUISE_HORZ)
                    usDataPkt.usBtnState &= ~(BTNSTATE_9 | BTNSTATE_9CHG | BTNSTATE_10 | BTNSTATE_10CHG);

                DebugUL ("WheelThread", "usBtnState = ", (ULONG)usDataPkt.usBtnState);
                DebugUL ("WheelThread", "shKeyState = ", (ULONG)usShiftKeyState);
                for (ulcLoop = 0, ulc = 0x0001; ulc < 0x0100; ulc <<= 2, ulcLoop += 2)
                    {
                    if (usDataPkt.usBtnState & (ulc << 1))
                        {
                        WinQueryPointerPos (HWND_DESKTOP, &pointer);
                        hwnd2send2 = WinWindowFromPoint (HWND_DESKTOP, &pointer, TRUE);
                        if (usDataPkt.usBtnState & ulc)
                            ulAction = arBtnMsg[ulcLoop];
                        else
                            ulAction = arBtnMsg[ulcLoop+1];

                        WinPostMsg (hwnd2send2,
                                    ulAction,
                                    MPFROMLONG (MESSAGE_KEY),
                                    MPFROM2SHORT ((usDataPkt.usBtnState & BTNSTATE_SCREENGROUP_PM ? 1 : 0),
                                                  usShiftKeyState));
                        }
                    }
                }
            }
        else
            {
            DebugUL ("WheelThread", "problem during DosDevIOCtl, rc = ", rc);
            break;
            }
        }

    DosCloseEventSem (hevPaintVolume);

    DebugE ("WheelThread", "terminate thread");

    WinDestroyMsgQueue (hmq);
    DosClose (hFileDriver);
    hFileDriver = NULLHANDLE;
    DosExit (EXIT_THREAD, 0);
    }

/*******************************************************************\
    Thread that updates the pShMemMouseData structure, if changes
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
        SetFullScreenMode ();
        if (hFileDriver)
            setMouseTimingValues (hFileDriver);
        DosResetEventSem (hevWheelThreadUpdate, &ulPostCount);
        DebugUL ("UpdateThread", "postCount1: ", ulPostCount);
        }
    }

/*******************************************************************\
    Thread that paints the volume identifier
    Input: ulParm: unused
\*******************************************************************/
VOID _System PaintVolumeThread (ULONG ulParm)
    {
    HMQ            hmq       = NULLHANDLE;
    HPS            hpsScreen = NULLHANDLE;
    PTIB           ptib;
    PPIB           ppib;
    ULONG          ulPostCount;
    LONG           cxScreen, cyScreen;

    static POINTL  ptlBL_BackGnd, ptlTR_BackGnd;
    static POINTL  ptlBL_Slider,  ptlTR_Slider;
    static POINTL  ptlBL_Shaft,   ptlTR_Shaft;
    static POINTL  ptlVolSymbol1, ptlVolSymbol[2];

    /* save the pid of process creating this thread */
    DosGetInfoBlocks (&ptib, &ppib);
    pidVolumePaint = ppib->pib_ulpid;

    /* Create a PM message queue necessary for sending messages to other processes */
    hmq = WinCreateMsgQueue (hab, 0);
    if (hmq != NULLHANDLE)
        {
        WinCancelShutdown (hmq, TRUE);

        if (DosOpenEventSem (NULL, &hevPaintVolume) == NO_ERROR)
            {
            hpsScreen = WinGetScreenPS (HWND_DESKTOP);

            if (rcl_BackGnd.xRight == 0)
                {
                cxScreen = WinQuerySysValue (HWND_DESKTOP, SV_CXSCREEN);
                cyScreen = WinQuerySysValue (HWND_DESKTOP, SV_CYSCREEN);

                ptlBL_BackGnd.x = cxScreen / 7 - 10;
                ptlTR_BackGnd.x = cxScreen - ptlBL_BackGnd.x + 10;
                ptlBL_BackGnd.y = cyScreen / 10 - 10;
                ptlTR_BackGnd.y = ptlBL_BackGnd.y + 30;

                ptlBL_Slider.x = ptlBL_BackGnd.x + cxScreen / 10 + 10;
                ptlTR_Slider.x = ptlTR_BackGnd.x - 10;
                ptlBL_Slider.y = ptlBL_BackGnd.y + 10;
                ptlTR_Slider.y = ptlTR_BackGnd.y - 10;

                ptlVolSymbol1.x = ptlBL_BackGnd.x + (ptlBL_Slider.x - ptlBL_BackGnd.x) / 5;
                ptlVolSymbol1.y = ptlBL_Slider.y;
                ptlVolSymbol[0].x = ptlVolSymbol[1].x = ptlBL_Slider.x - (ptlBL_Slider.x - ptlBL_BackGnd.x) / 5;
                ptlVolSymbol[0].y = ptlVolSymbol1.y;
                ptlVolSymbol[1].y = ptlTR_Slider.y;

                ptlBL_Shaft.y = ptlBL_Slider.y - 9;
                ptlTR_Shaft.y = ptlTR_Slider.y + 9;

                rcl_BackGnd.xLeft   = ptlBL_BackGnd.x;
                rcl_BackGnd.xRight  = ptlTR_BackGnd.x + 1;
                rcl_BackGnd.yBottom = ptlBL_BackGnd.y;
                rcl_BackGnd.yTop    = ptlTR_BackGnd.y + 1;
                }

            for (;;)
                {
                if (DosWaitEventSem (hevPaintVolume, 1000) != NO_ERROR)
                    break;

                DosResetEventSem (hevPaintVolume, &ulPostCount);

                /* Background rectangle */
                GpiSetColor (hpsScreen, CLR_PALEGRAY);
                GpiMove (hpsScreen, &ptlBL_BackGnd);
                GpiBox (hpsScreen, DRO_OUTLINEFILL, &ptlTR_BackGnd, 0, 0);

                /* Volume symbol */
                GpiSetColor (hpsScreen, CLR_BLUE);
                GpiBeginPath (hpsScreen, 1L);
                GpiMove (hpsScreen, &ptlVolSymbol1);
                GpiPolyLine (hpsScreen, 2L, ptlVolSymbol);
                GpiCloseFigure (hpsScreen);
                GpiEndPath (hpsScreen);
                GpiFillPath (hpsScreen, 1L, FPATH_ALTERNATE);

                /* slider */
                GpiSetColor (hpsScreen, CLR_CYAN);
                GpiMove (hpsScreen, &ptlBL_Slider);
                GpiBox (hpsScreen, DRO_OUTLINEFILL, &ptlTR_Slider, 0, 0);

                /* slider shaft */
                ptlBL_Shaft.x = ptlBL_Slider.x + (ptlTR_Slider.x - ptlBL_Slider.x) * lVolume / 100 - 5;
                ptlTR_Shaft.x = ptlBL_Shaft.x + 10;

                GpiSetColor (hpsScreen, CLR_RED);                       // use path because bug when painting
                GpiBeginPath (hpsScreen, 1L);                           // DRO_FILL and rounding parameters
                GpiMove (hpsScreen, &ptlBL_Shaft);                      // > 0: box is too large!
                GpiBox (hpsScreen, DRO_OUTLINE, &ptlTR_Shaft, 8, 8);
                GpiEndPath (hpsScreen);
                GpiFillPath (hpsScreen, 1L, FPATH_ALTERNATE);

                GpiSetColor (hpsScreen, CLR_BLACK);
                GpiMove (hpsScreen, &ptlBL_Shaft);
                GpiBox (hpsScreen, DRO_OUTLINE, &ptlTR_Shaft, 8, 8);
                }

            WinInvalidateRect (HWND_DESKTOP, &rcl_BackGnd, TRUE);
            DosPostEventSem (hevXWPWidgetUpdate);
            }

        if (pfnMciSaveMasterVolume)
            pfnMciSaveMasterVolume ();

        if (hpsScreen == NULLHANDLE)
            WinReleasePS (hpsScreen);

        WinDestroyMsgQueue (hmq);
        }

    DosCloseEventSem (hevPaintVolume);
    tidVolumePaint = NULLHANDLE;
    pidVolumePaint = NULLHANDLE;

    DosExit (EXIT_THREAD, 0);
    }

