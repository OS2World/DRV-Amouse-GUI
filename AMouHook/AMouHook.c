/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUDLL
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: HOOK
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
 *   InitWheelThread
 *   WheelThread
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.10    05-12-02  handling of shift keys
 *  2.20    10-03-02  USB support added
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define INCL_DOSMODULEMGR
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#define INCL_DOSMISC
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSPROFILE
#define INCL_DOSERRORS
#define INCL_WINHOOKS
#define INCL_WININPUT
#define INCL_WINWINDOWMGR
#define INCL_WINMESSAGEMGR
#define INCL_WINPROGRAMLIST
#define INCL_WINSWITCHLIST
#define INCL_WINFRAMEMGR
#define INCL_WINPOINTERS
#define INCL_WINSYS
#define INCL_WINMENUS
#define INCL_WINERRORS
#include <os2.h>
#include <string.h>

#include "AMouseGlobal.h"
#include "AMouHook.h"
#include "AMouHData.h"
#include "AMouHwnd.h"
#include "PMWinMou.h"
#include "res.h"

int _rmem_init (void);
int _rmem_term (void);

#define MAXHWND         256                     // number of window handles for minimize list
#define CCHMAXCLASSNAME 32

#define CCHMAXBUFFER    0x4000
#define RESERVED        0

typedef enum {_btnUp, _btnDn} BTNACTION;

#pragma pack (1)
typedef struct
    {
    USHORT  uscRepeat;
    USHORT  usMakeCode;
    USHORT  usBreakCode;
    } KBDEVENT, *PKBDEVENT;
#pragma pack ()

typedef struct
    {
    ULONG       ulMsg;
    BTNACTION   btnAction;
    ULONG       ulMsgKey;
    ULONG       ulScreenGroup;
    ULONG       ulId;
    } KBDINFO, *PKKBINFO;

/*******************************************************************\
  local data segment (process specific)
\*******************************************************************/
PMOUSEDATA pShMemMouseData      = NULL;
BOOL       bShMemIsInitialized  = FALSE;
HMTX       hmtxWheelThread      = NULLHANDLE;   // semaphore for synchronisation of strucMouseData
HEV        hevXWPWidgetUpdate   = NULLHANDLE;   // semaphore for updating XCenter Widget

PFNWP      pWinDefWndProc       = NULL;

#ifdef _TRACE_
#pragma pack (1)
typedef struct
    {
    ULONG   ulProgType;
    ULONG   ulCharCode;
    } TRACE_PM;

typedef struct
    {
    ULONG   ulProgType;
    ULONG   ulMp1;
    ULONG   ulMp2;
    USHORT  usMakeCode;
    } TRACE_KBD;

typedef struct
    {
    USHORT  usOldShiftState;
    USHORT  usNewShiftState;
    USHORT  usShiftKeys;
    } TRACE_SHIFT;

typedef struct
    {
    ULONG   ulMsg;
    } TRACE_HOOK;
#pragma pack ()

union
    {
    TRACE_PM    trcPm;                          // Minor = 1
    TRACE_KBD   trcKbd;                         // Minor = 2
    TRACE_SHIFT trcShift;                       // Minor = 3
    TRACE_HOOK  trcHook;                        // Minor = 4
    } uTrace;
#endif /* _TRACE_ */

/*******************************************************************\
  global data segment
\*******************************************************************/
#pragma data_seg(GLOBAL_SEG)

HWND       hwndWindowList  = NULLHANDLE;

LONG       lCXScreen       = 0;                 // x-size of screen
LONG       lCYScreen       = 0;                 // y-size of screen

PFN        pfnInput        = NULL;
PFN        pfnMsgInput     = NULL;
PFN        pfnDestroyWnd   = NULL;

ULONG      ulcHwndList     = 0;                 // current number of entries in arHwnd
HWND       arHwnd[MAXHWND];                     // minimized windows

typedef enum {MICompleted, MIInserted, MIRestore} VALIDQMSG;
VALIDQMSG  eValidQmsg      = 0;
QMSG       qmsg;

// array for identification of mouse button number
KBDINFO structKbdInfo[2*CULNUMBUTTONS] =
    {
    {WM_BUTTON3DOWN,  _btnDn, MESSAGE_KEY, 1L, 0L},
    {WM_BUTTON4DOWN,  _btnDn, 0L,          0L, 1L},
    {WM_BUTTON5DOWN,  _btnDn, 0L,          0L, 2L},
    {WM_BUTTON6DOWN,  _btnDn, 0L,          0L, 3L},
    {WM_BUTTON7DOWN,  _btnDn, 0L,          0L, 4L},
    {WM_BUTTON8DOWN,  _btnDn, 0L,          0L, 5L},
    {WM_BUTTON9DOWN,  _btnDn, 0L,          0L, 6L},
    {WM_BUTTON10DOWN, _btnDn, 0L,          0L, 7L},
    {WM_BUTTON3UP,    _btnUp, MESSAGE_KEY, 1L, 0L},
    {WM_BUTTON4UP,    _btnUp, 0L,          0L, 1L},
    {WM_BUTTON5UP,    _btnUp, 0L,          0L, 2L},
    {WM_BUTTON6UP,    _btnUp, 0L,          0L, 3L},
    {WM_BUTTON7UP,    _btnUp, 0L,          0L, 4L},
    {WM_BUTTON8UP,    _btnUp, 0L,          0L, 5L},
    {WM_BUTTON9UP,    _btnUp, 0L,          0L, 6L},
    {WM_BUTTON10UP,   _btnUp, 0L,          0L, 7L}
    };

// global static variables for setShiftKeys
USHORT     usShiftState;
SHIFTSTATE shiftState;
BYTE       bKeyShift, bKeyAlt, bKeyCtrl;
BYTE       keyState[256];                       // This is a 256 byte table indexed by virtual key value. For any
                                                // virtual key, the 0x80 bit is set if the key is down, and zero
                                                // if it is up. The 0x01 bit is set if the key is toggled,
                                                // (pressed an odd number of times), otherwise it is zero.

BOOL EXPENTRY inputHookProc (HAB hab, PQMSG pQmsg, ULONG fs);

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

            // allocate shared memory for WinRegisterForWheelMsg once
            if (NULL == parWindow)
                {
                DosQuerySysInfo (QSV_PAGE_SIZE, QSV_PAGE_SIZE, &ulcBytePerPage, sizeof (ulcBytePerPage));
                allocSharedHwndArray ();
                }

            // make shared memory for WinRegisterForWheelMsg available in each process
            getSharedHwndArray ();
#ifdef _TRACE_
            {
            PPIB ppib;
            DosGetInfoBlocks (NULL, &ppib);
            uTrace.trcPm.ulProgType = ppib->pib_ulpid;
            uTrace.trcPm.ulCharCode = (ULONG)parWindow;
            Dos16SysTrace (178, 8, 1, (PUCHAR)&uTrace);
            }
#endif /* _TRACE_ */
            break;

        case 1:         // termination
            // free shared memory for WinRegisterForWheelMsg
            freeSharedHwndArray ();

            _rmem_term ();
            break;

        default:
            return 0;
        }

    /* A nonzero value must be returned to indicate success. */
    return 1;
    }

VOID EXPENTRY initHookDLL (HAB hab)
    {
    habDLL = hab;
    DosLoadModule (NULL, 0, "AMouHook", &hModule);
    DosQueryProcAddr (hModule, 0, "inputHookProc",         &pfnInput);
    DosQueryProcAddr (hModule, 0, "msgInputHookProc",      &pfnMsgInput);
    DosQueryProcAddr (hModule, 0, "destroyWindowHookProc", &pfnDestroyWnd);

    return;
    }

BOOL EXPENTRY insertHooks (void)
    {
    BOOL bRC;

    bRC  = WinSetHook (habDLL,                      // anchor block handle
                       NULLHANDLE,                  // system queue
                       HK_INPUT,                    // input hook
                       pfnInput,                    // hook procedure
                       hModule);                    // module handle

    bRC &= WinSetHook (habDLL,                      // anchor block handle
                       NULLHANDLE,                  // system queue
                       HK_DESTROYWINDOW,            // destroy window hook
                       pfnDestroyWnd,               // hook procedure
                       hModule);                    // module handle

    if (!bRC)
        releaseHooks ();

    return bRC;
    }

BOOL EXPENTRY releaseHooks (void)
    {
    BOOL bRC;

    if (pfnInput)
        bRC = WinReleaseHook (habDLL,               // anchor block handle
                              NULLHANDLE,           // system queue
                              HK_INPUT,             // input hook
                              pfnInput,             // hook procedure
                              hModule);             // module handle

    if (pfnDestroyWnd)
        bRC &=  WinReleaseHook (habDLL,             // anchor block handle
                                NULLHANDLE,         // system queue
                                HK_DESTROYWINDOW,   // destroy window hook
                                pfnInput,           // hook procedure
                                hModule);           // module handle

    DosFreeModule (hModule);

    return bRC;
    }

ULONG getFrameCtlFlags (HWND hwnd)
    {
    HWND hwndMinMax;
    SHORT scMenuItems;
    ULONG ulFCB = 0;

    hwndMinMax = WinWindowFromID (hwnd, FID_MINMAX);
    if (!hwndMinMax)
        return 0;

    scMenuItems = SHORT1FROMMR (WinSendMsg (hwndMinMax, MM_QUERYITEMCOUNT, 0, 0));

    if (!scMenuItems)
        return 0;

    if ((BOOL)WinSendMsg (hwndMinMax,
                          MM_ISITEMVALID,
                          MPFROM2SHORT (SC_MINIMIZE, FALSE),
                          MPVOID))
        ulFCB |= FCB_MINBUTTON;

    if ((BOOL)WinSendMsg (hwndMinMax,
                          MM_ISITEMVALID,
                          MPFROM2SHORT (SC_MAXIMIZE, FALSE),
                          MPVOID))
        ulFCB |= FCB_MAXBUTTON;

    if ((BOOL)WinSendMsg (hwndMinMax,
                          MM_ISITEMVALID,
                          MPFROM2SHORT (SC_CLOSE, FALSE),
                          MPVOID))
        ulFCB |= FCB_CLOSEBUTTON;

    if ((BOOL)WinSendMsg (hwndMinMax,
                          MM_ISITEMVALID,
                          MPFROM2SHORT (SC_HIDE, FALSE),
                          MPVOID))
        ulFCB |= FCB_HIDEBUTTON;

    if ((BOOL)WinSendMsg (hwndMinMax,
                          MM_ISITEMVALID,
                          MPFROM2SHORT (SC_RESTORE, FALSE),
                          MPVOID))
        ulFCB |= FCB_RESTOREBUTTON;

    return ulFCB;
    }

VOID findWindowList (VOID)
    {
    HENUM henum;
    HENUM henumFrame;
    HWND  hwnd;
    HWND  hwndChild;
    CHAR  szClass[CCHMAXCLASSNAME];
    CHAR  szChildClass[CCHMAXCLASSNAME];

    // enumerate desktop window to find the window list:
    // according to PMTREE, the window list has the following
    // window hierarchy:
    //      WC_FRAME
    //        +--- WC_TITLEBAR
    //        +--- Menu
    //        +--- WindowList
    //        +---
    henum = WinBeginEnumWindows (HWND_DESKTOP);
    while ((hwnd = WinGetNextWindow (henum)) != NULLHANDLE)
        {
        CHAR    szClass[200];
        if (WinQueryClassName (hwnd, CCHMAXCLASSNAME, szClass))
            {
            if (!strcmp (szClass, "#1"))
                {
                // frame window: check the children
                henumFrame = WinBeginEnumWindows (hwnd);
                while ((hwndChild = WinGetNextWindow (henumFrame)) != NULLHANDLE)
                    {
                    if (WinQueryClassName (hwndChild, CCHMAXCLASSNAME, szChildClass))
                        {
                        if (!strcmp (szChildClass, "WindowList"))
                            {
                            hwndWindowList = hwnd;
                            return;
                            }
                        }
                    }
                WinEndEnumWindows (henumFrame);
                }
            }
        }
    WinEndEnumWindows (henum);

    return;
    }

HWND findTopFrame (HWND hwnd)
    {
    HWND  hwnd1, hwnd2;
    HWND  hwndDesktop;
    HWND  hwndObject;
    LONG  lCode[] = {QW_OWNER, QW_PARENT, -1};
    LONG  l;
    ULONG flFlags;

    hwndDesktop = WinQueryDesktopWindow (habDLL, NULLHANDLE);
    hwndObject  = WinQueryObjectWindow (hwndDesktop);

    for (l = 0; lCode[l] != -1; l++)
        {
        hwnd1 = hwnd;
        for (;;)
            {
            if (hwnd1 == NULLHANDLE   ||
                hwnd1 == HWND_DESKTOP ||
                hwnd1 == HWND_OBJECT  ||
                hwnd1 == hwndDesktop  ||
                hwnd1 == hwndObject)
                {
                hwnd1 = NULLHANDLE;
                break;
                }
            hwnd2 = hwnd1;
            hwnd1 = WinQueryWindow (hwnd1, lCode[l]);
            }
        flFlags = (ULONG)WinSendMsg (hwnd2, WM_QUERYFRAMEINFO, MPVOID, MPVOID);
        if (flFlags & FI_FRAME)
            break;
        }

    hwnd = NULLHANDLE;
    if (hwnd2 != NULLHANDLE)
        hwnd = hwnd2;

    return hwnd;
    }

HWND findTopParentFrame (HWND hwnd)
    {
    HWND  hwnd1, hwnd2;
    HWND  hwndDesktop;
    HWND  hwndObject;
    ULONG flFlags;

    hwndDesktop = WinQueryDesktopWindow (habDLL, NULLHANDLE);
    hwndObject  = WinQueryObjectWindow (hwndDesktop);

    hwnd1 = hwnd;
    for (;;)
        {
        if (hwnd1 == NULLHANDLE   ||
            hwnd1 == HWND_DESKTOP ||
            hwnd1 == HWND_OBJECT  ||
            hwnd1 == hwndDesktop  ||
            hwnd1 == hwndObject)
            {
            hwnd1 = NULLHANDLE;
            break;
            }
        hwnd2 = hwnd1;
        hwnd1 = WinQueryWindow (hwnd1, QW_PARENT);
        }

    hwnd = NULLHANDLE;
    flFlags = (ULONG)WinSendMsg (hwnd2, WM_QUERYFRAMEINFO, MPVOID, MPVOID);
    if (flFlags & FI_FRAME)
        hwnd = hwnd2;

    return hwnd;
    }

HWND findTopWindows (VOID)
    {
    HWND  hwnd;
    HENUM henum;
    ULONG flFlags;

    ulcHwndList = 0;
    henum = WinBeginEnumWindows (HWND_DESKTOP);
    for (;;)
        {
        hwnd = WinGetNextWindow (henum);
        if (hwnd == NULLHANDLE)
            break;

        flFlags = (ULONG)WinSendMsg (hwnd, WM_QUERYFRAMEINFO, MPVOID, MPVOID);
        if (flFlags & FI_FRAME)
            {
            arHwnd[ulcHwndList++] = hwnd;
            if (ulcHwndList >= MAXHWND)
                break;
            }
        }

    WinEndEnumWindows (henum);
    return hwnd;
    }

/*******************************************************************\
    QueryPidFromHWND: determines the pid of an application
                      identified by a hwnd of a window in
                      its window hierarchie
    Input:  hwnd: window handle of application to be determined
    Return: pid
\*******************************************************************/
ULONG queryPidFromHWND (HWND hwnd)
    {
    ULONG     ulPid = 0;
    ULONG     ulc, ul;
    PSWBLOCK  pswblkBlock;

    hwnd = findTopParentFrame (hwnd);

    ulc = WinQuerySwitchList (habDLL, NULL, 0);
    ulc = sizeof (SWBLOCK) + (ulc-1)*sizeof (SWENTRY);

    if (NO_ERROR == DosAllocMem ((PPVOID)&pswblkBlock, ulc, PAG_COMMIT | PAG_READ | PAG_WRITE))
        {
        WinQuerySwitchList (habDLL, pswblkBlock, ulc);

        for (ul = 0; ul < pswblkBlock->cswentry; ul++)
            {
            if (pswblkBlock->aswentry[ul].swctl.hwnd == hwnd)
                {
                ulPid = pswblkBlock->aswentry[ul].swctl.idProcess;
                break;
                }
            }

        DosFreeMem (pswblkBlock);
        }

    return ulPid;
    }

/*******************************************************************\
    QueryprogType: determines the program type of an application
                   indicated by its pid.
    Input:  pid: pid of process to be examined
    Return: program type
\*******************************************************************/
ULONG QueryProgType (ULONG pid)
    {
    ULONG       ulProgType = PROG_DEFAULT;
    PVOID       pBuffer;
    APIRET      rc;
    QSPTRREC   *pTop;
    QSPREC     *pP;

    /* Allocate memory for evaluation */
    rc = DosAllocMem (&pBuffer, CCHMAXBUFFER, PAG_COMMIT | PAG_READ | PAG_WRITE);
    if (NO_ERROR == rc)
        {
        /* Query system state */
        rc = DosQuerySysState (QS_PROCESS, RESERVED, pid, RESERVED, pBuffer, CCHMAXBUFFER);
        if (NO_ERROR == rc)
            {
            pTop = (QSPTRREC *)pBuffer;
            pP   = pTop->pProcRec;
            if (pP && pP->RecType == QS_PROCESS && pP->pid == pid)
                {
                ulProgType = pP->type;
                }
            }

        DosFreeMem (pBuffer);
        }

    return ulProgType;
    }


VOID minimizeAllWindows (VOID)
    {
    ULONG ulc, ulFCB;

    findTopWindows ();
    for (ulc = 0; ulc < ulcHwndList; ulc++)
        {
        if (!WinIsWindow (habDLL, arHwnd[ulc]))
            continue;
        ulFCB = getFrameCtlFlags (arHwnd[ulc]);
        if (ulFCB & FCB_MINBUTTON)
            WinPostMsg (arHwnd[ulc],
                        WM_SYSCOMMAND,
                        MPFROMSHORT (SC_MINIMIZE),
                        MPFROM2SHORT(CMDSRC_OTHER, TRUE));
        else if (ulFCB & FCB_HIDEBUTTON)
            WinPostMsg (arHwnd[ulc],
                        WM_SYSCOMMAND,
                        MPFROMSHORT (SC_HIDE),
                        MPFROM2SHORT(CMDSRC_OTHER, TRUE));
        }

    return;
    }

VOID restoreAllWindows (VOID)
    {
    ULONG ulc;

    for (ulc = 0; ulc < ulcHwndList; ulc++)
        {
        if (!WinIsWindow (habDLL, arHwnd[ulc]))
            continue;
        if (getFrameCtlFlags (arHwnd[ulc]) & FCB_RESTOREBUTTON)
            WinPostMsg (arHwnd[ulc],
                        WM_SYSCOMMAND,
                        MPFROMSHORT (SC_RESTORE),
                        MPFROM2SHORT(CMDSRC_OTHER, TRUE));
        }
    ulcHwndList = 0;

    return;
    }

VOID closeApplication (PQMSG pQmsg)
    {
    HWND hwnd;

    hwnd = pQmsg->hwnd;
    hwnd = findTopParentFrame (hwnd);

    if (WinIsWindow (habDLL, hwnd))
        WinPostMsg (hwnd,
                    WM_SYSCOMMAND,
                    MPFROMSHORT (SC_CLOSE),
                    MPFROM2SHORT(CMDSRC_OTHER, TRUE));

    return;
    }

VOID sizeApplicationWindow (PQMSG pQmsg, USHORT usSysCmd)
    {
    HWND   hwnd;
    ULONG  ulFCB;
    USHORT usSysCommand = 0;

    hwnd = pQmsg->hwnd;
    hwnd = findTopParentFrame (hwnd);

    if (WinIsWindow (habDLL, hwnd))
        {
        ulFCB = getFrameCtlFlags (hwnd);
        switch (usSysCmd)
            {
            case SC_MAXIMIZE:
                if (ulFCB & FCB_MAXBUTTON)
                    usSysCommand = usSysCmd;
                break;
            case SC_MINIMIZE:
                if (ulFCB & FCB_MINBUTTON)
                    usSysCommand = usSysCmd;
                else if (ulFCB & FCB_HIDEBUTTON)
                    usSysCommand = SC_HIDE;
                break;
            case SC_RESTORE:
                if (ulFCB & FCB_RESTOREBUTTON)
                    usSysCommand = usSysCmd;
                break;
            }
        if (usSysCommand)
            WinPostMsg (hwnd,
                        WM_SYSCOMMAND,
                        MPFROMSHORT (usSysCommand),
                        MPFROM2SHORT(CMDSRC_OTHER, TRUE));
        }

    return;
    }

VOID toggleScrollDir (VOID)
    {
    DosRequestMutexSem (hmtxWheelThread, (ULONG)SEM_INDEFINITE_WAIT);

    if (pShMemMouseData->ulCurrScrollDir == SCROLL_DIR_VERT)
        pShMemMouseData->ulCurrScrollDir = SCROLL_DIR_HORZ;
    else
        pShMemMouseData->ulCurrScrollDir = SCROLL_DIR_VERT;

    DosReleaseMutexSem (hmtxWheelThread);
    DosPostEventSem (hevXWPWidgetUpdate);

    return;
    }

VOID showTaskManager (VOID)
    {
    POINTL  ptlPointer;             // position of pointer on desktop
    SWP     strucWinListPos;        // position of window list window
    LONG    lWinListX, lWinListY;   // new ordinates of window list window

    if (hwndWindowList == NULLHANDLE)
        findWindowList ();

    if (lCXScreen * lCYScreen == 0)
        {
        lCXScreen = WinQuerySysValue (HWND_DESKTOP, SV_CXSCREEN);
        lCYScreen = WinQuerySysValue (HWND_DESKTOP, SV_CYSCREEN);
        }

    WinQueryPointerPos (HWND_DESKTOP, &ptlPointer);

    // get position of window list window
    WinQueryWindowPos (hwndWindowList, &strucWinListPos);

    // calculate window list position (mouse pointer is center)
    lWinListX = ptlPointer.x - (strucWinListPos.cx / 2);
    if (lWinListX < 0)
        lWinListX = 0;
    lWinListY = ptlPointer.y - (strucWinListPos.cy / 2);
    if (lWinListY < 0)
        lWinListY = 0;
    if (lWinListX + strucWinListPos.cx > lCXScreen)
        lWinListX = lCXScreen - strucWinListPos.cx;
    if (lWinListY + strucWinListPos.cy > lCYScreen)
        lWinListY = lCYScreen - strucWinListPos.cy;

    // set window list window to calculated position
    WinSetWindowPos (hwndWindowList, HWND_TOP,
                     lWinListX, lWinListY, 0, 0,
                     SWP_MOVE | SWP_SHOW | SWP_ZORDER);

    // now make it the active window
    WinSetActiveWindow (HWND_DESKTOP, hwndWindowList);

    return;
    }

VOID pushToBackground (HWND hwnd)
    {
    HWND hwndFrame = findTopFrame (hwnd);
    HWND hwndNextFocus = NULLHANDLE;

    if (WinIsWindow (habDLL, hwndFrame))
        {
        WinSetWindowPos (hwndFrame,
                         HWND_BOTTOM,
                         0, 0, 0, 0,
                         SWP_ZORDER);
        WinSetFocus (HWND_DESKTOP, HWND_DESKTOP);
        }

    return;
    }

VOID setShiftKeys1 (SHORT sShiftKeys)
    {
    // set shift state
    WinSetKeyboardStateTable (HWND_DESKTOP, keyState, FALSE);   // get a copy of the keyboard state.

    bKeyShift = keyState[VK_SHIFT];
    bKeyAlt   = keyState[VK_ALT];
    bKeyCtrl  = keyState[VK_CTRL];

    keyState[VK_SHIFT] = (sShiftKeys & KC_SHIFT ? 0x80 : 0x00);
    keyState[VK_ALT]   = (sShiftKeys & KC_ALT   ? 0x80 : 0x00);
    keyState[VK_CTRL]  = (sShiftKeys & KC_CTRL  ? 0x80 : 0x00);

    WinSetKeyboardStateTable (HWND_DESKTOP, keyState, TRUE);    // set the keyboard state

    return;
    }

VOID setShiftKeys2 (SHORT sShiftKeys)
    {
    APIRET     rc;
    ULONG      ulAction;
    ULONG      ulc;
    HFILE      hFileDriver;

    rc = DosOpen ("KBD$", &hFileDriver, &ulAction, 0,
                  FILE_NORMAL, FILE_OPEN,
                  OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                  (PEAOP2)NULL);
    if (NO_ERROR != rc)
        return;

    ulc = sizeof (shiftState);
    rc = DosDevIOCtl (hFileDriver,
                      IOCTL_KEYBOARD,
                      KBD_GETSHIFTSTATE,
                      NULL,
                      0,
                      NULL,
                      &shiftState,
                      sizeof (shiftState),
                      &ulc);
    if (NO_ERROR == rc)
        {
        #ifdef _TRACE_
            uTrace.trcShift.usOldShiftState = shiftState.fsState;
            uTrace.trcShift.usShiftKeys     = sShiftKeys & (KC_SHIFT | KC_CTRL | KC_ALT);
        #endif /* _TRACE_ */

        usShiftState        = shiftState.fsState;
        shiftState.fsState &= (SYSREQ    | CAPSLOCK    | NUMLOCK    | SCROLLLOCK    | RIGHTALT |
                               INSERT_ON | CAPSLOCK_ON | NUMLOCK_ON | SCROLLLOCK_ON);
        if (sShiftKeys & KC_SHIFT)
            shiftState.fsState |= LEFTSHIFT;
        if (sShiftKeys & KC_ALT)
            shiftState.fsState |= ALT | LEFTALT;
        if (sShiftKeys & KC_CTRL)
            shiftState.fsState |= CONTROL | LEFTCONTROL;

        #ifdef _TRACE_
            uTrace.trcShift.usNewShiftState = shiftState.fsState;
            Dos16SysTrace (178, 6, 3, (PUCHAR)&uTrace);
        #endif /* _TRACE_ */

        ulc = sizeof (shiftState);
        DosDevIOCtl (hFileDriver,
                     IOCTL_KEYBOARD,
                     KBD_SETSHIFTSTATE,
                     &shiftState,
                     sizeof (shiftState),
                     &ulc,
                     NULL,
                     0,
                     NULL);
        }

    DosClose (hFileDriver);
    return;
    }

VOID restoreShiftKeys1 (VOID)
    {
    // restore previous shift state
    keyState[VK_SHIFT] = bKeyShift;
    keyState[VK_ALT]   = bKeyAlt;
    keyState[VK_CTRL]  = bKeyCtrl;

    WinSetKeyboardStateTable (HWND_DESKTOP, keyState, TRUE);    // set the keyboard state

    return;
    }

VOID restoreShiftKeys2 (VOID)
    {
    APIRET     rc;
    ULONG      ulAction;
    ULONG      ulc;
    HFILE      hFileDriver;

    rc = DosOpen ("KBD$", &hFileDriver, &ulAction, 0,
                  FILE_NORMAL, FILE_OPEN,
                  OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                  (PEAOP2)NULL);
    if (NO_ERROR != rc)
        return;

    shiftState.fsState = usShiftState;

    ulc = sizeof (shiftState);
    DosDevIOCtl (hFileDriver,
                 IOCTL_KEYBOARD,
                 KBD_SETSHIFTSTATE,
                 &shiftState,
                 sizeof (shiftState),
                 &ulc,
                 NULL,
                 0,
                 NULL);

    DosClose (hFileDriver);

    return;
    }

VOID postKey (PQMSG pQmsg, ULONG ulProgType, BTNACTION btnAction, MPARAM mp1, MPARAM mp2)
    {
    #ifdef _TRACE_
        uTrace.trcPm.ulProgType = ulProgType;
    #endif /* _TRACE_ */

    switch (ulProgType)
        {
        case PROG_DEFAULT:
        case PROG_PM:
            /* Handling for PM programs */
            qmsg.hwnd = pQmsg->hwnd;
            qmsg.msg  = WM_CHAR;
            qmsg.mp1  = mp1;
            qmsg.mp2  = mp2;
            qmsg.time = pQmsg->time;
            qmsg.ptl  = pQmsg->ptl;

            if (btnAction == _btnUp)
                qmsg.mp1 = MPFROMLONG (LONGFROMMP (qmsg.mp1) | KC_KEYUP | KC_LONEKEY);

            eValidQmsg = MIInserted;

            WinSetHook (habDLL,                     // anchor block handle
                        NULLHANDLE,                 // system queue
                        HK_MSGINPUT,                // input hook
                        pfnMsgInput,                // hook procedure
                        hModule);                   // module handle

            WinCheckInput (habDLL);

            #ifdef _TRACE_
                uTrace.trcPm.ulCharCode = LONGFROMMP (qmsg.mp1);
                Dos16SysTrace (178, 8, 1, (PUCHAR)&uTrace);
            #endif /* _TRACE_ */

            break;

        default:
            {
            /* Handling for non-PM programs (PROG_FULLSCREEN, PROG_WINDOWABLEVIO, PROG_VDM, PROG_WINDOWEDVDM) */
            HFILE    hFileDriver;
            ULONG    ulAction;
            ULONG    ulParmLen;
            APIRET   rc;
            KBDEVENT kbdEvent;

            rc = DosOpen ("MOUSE$", &hFileDriver, &ulAction, 0,
                          FILE_NORMAL, FILE_OPEN,
                          OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                          (PEAOP2)NULL);

            if (rc == NO_ERROR)
                {
                WinSetFocus (HWND_DESKTOP, pQmsg->hwnd);

                setShiftKeys2 (SHORT1FROMMP (mp1));

                ulParmLen = sizeof (KBDEVENT);
                kbdEvent.uscRepeat   = 1;
                if (CHAR1FROMMP (mp2) == 0xE0)
                    kbdEvent.usMakeCode  = SHORT1FROMMP (mp2) + (btnAction == _btnUp ? 0x8000 : 0);
                else
                    kbdEvent.usMakeCode  = CHAR4FROMMP (mp1)  + (btnAction == _btnUp ? 0x80   : 0);
                kbdEvent.usBreakCode = 0;

                DosDevIOCtl (hFileDriver,                   // Device handle
                             IOCTL_POINTINGDEVICE,          // Device category: Pointing-device control
                             MOU_SETKBDEVENT,               // Function code: send keyboard event
                             &kbdEvent,                     // Parameter packet: timeout value
                             sizeof (kbdEvent),             // Maximum size of parm packet
                             &ulParmLen,                    // Size of param packet on exit
                             NULL,                          // Buffer for data packet: not used
                             0,                             // Maximum size of data packet
                             NULL);                         // Size of data packet: not used

                restoreShiftKeys2 ();
                DosClose (hFileDriver);
                }
            #ifdef _TRACE_
                uTrace.trcKbd.ulMp1      = (ULONG)mp1;
                uTrace.trcKbd.ulMp2      = (ULONG)mp2;
                uTrace.trcKbd.usMakeCode = (ULONG)kbdEvent.usMakeCode;
                Dos16SysTrace (178, 14, 2, (PUCHAR)&uTrace);
            #endif /* _TRACE_ */
            }
        }

    return;
    }

/*******************************************************************\
    handleButtonEvent: receives a QMSG structure of a button event
                       and generates the responding action.
    Input:  pQmsg:         pointer to QMSG structure
            ulBtnMode:     user selected mode of button
            ulBtnId:       id of mouse button; id=0 => button3
            ulScreenGroup: 1 = PM; 0 = Fullscreen
            btnAction:     enumeration for button up/down
    Return: TRUE:  message was handled
            FALSE: message was ignored
\*******************************************************************/
BOOL handleButtonEvent (PQMSG pQmsg, ULONG ulBtnMode, ULONG ulBtnId, ULONG ulScreenGroup, BTNACTION btnAction)
    {
    ULONG     ulProgType;   // program type (PROG_* values, see pmshl.h)
    ULONG     ulPid;
    ULONG     ulc;

    // determine program type
    if (ulScreenGroup == 1)
        {
        // NOTE: bProgType determined by SWCNTRl not used, because return
        //       value is wrong sometimes. Instead DosQuerySysState is used
        ulPid      = queryPidFromHWND (pQmsg->hwnd);
        ulProgType = QueryProgType (ulPid);
        }
    else
        ulProgType = PROG_FULLSCREEN;

    switch (ulBtnMode)
        {
        case IDR_KEY:
            postKey (pQmsg,
                     ulProgType,
                     btnAction,
                     MPFROMLONG (pShMemMouseData->ulBtnKeyCombMP1[ulBtnId]),
                     MPFROMLONG (pShMemMouseData->ulBtnKeyCombMP2[ulBtnId]));
            return TRUE;

        case IDR_CLIPBOARD_CUT:
            postKey (pQmsg,
                     ulProgType,
                     btnAction,
                     MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_SHIFT, 1, 0x69),
                     MPFROM2SHORT (0x53E0, VK_DELETE));
            return TRUE;

        case IDR_CLIPBOARD_COPY:
            postKey (pQmsg,
                     ulProgType,
                     btnAction,
                     MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_CTRL, 1, 0x68),
                     MPFROM2SHORT (0x92E0, VK_INSERT));
            return TRUE;

        case IDR_CLIPBOARD_INSERT:
            postKey (pQmsg,
                     ulProgType,
                     btnAction,
                     MPFROMSH2CH (KC_VIRTUALKEY | KC_SCANCODE | KC_SHIFT, 1, 0x68),
                     MPFROM2SHORT (0x52E0, VK_INSERT));
            return TRUE;

        case IDR_BUTTON3:
            if ((pQmsg->msg == WM_BUTTON3DOWN) || (pQmsg->msg == WM_BUTTON3UP))
                return FALSE;
            if (SHORT1FROMMP (pQmsg->mp2) == 1)
                WinPostMsg (pQmsg->hwnd,
                            (btnAction == _btnDn ? WM_BUTTON3DOWN : WM_BUTTON3UP),
                            MPFROM2SHORT ((SHORT)pQmsg->ptl.x, (SHORT)pQmsg->ptl.y),
                            MPFROM2SHORT (HT_NORMAL, SHORT2FROMMP (pQmsg->mp2)));
            return TRUE;

        case IDR_MINIMIZE_ALL:
            if (btnAction == _btnDn && ulProgType != PROG_FULLSCREEN)
                minimizeAllWindows ();
            return TRUE;

        case IDR_RESTORE_ALL:
            if (btnAction == _btnDn && ulProgType == PROG_PM)
                restoreAllWindows ();
            return TRUE;

        case IDR_WINDOW_LIST:
            if (btnAction == _btnDn && ulProgType == PROG_PM)
                showTaskManager ();
            return TRUE;

        case IDR_CLOSE_APPLICATION:
            if (btnAction == _btnDn && ulProgType != PROG_FULLSCREEN)
                closeApplication (pQmsg);
            return TRUE;

        case IDR_DOUBLECLICK:
            if (btnAction == _btnDn && ulProgType == PROG_PM)
                {
                POINTL ptlPointer;

                WinQueryPointerPos (HWND_DESKTOP, &ptlPointer);
                WinMapWindowPoints (HWND_DESKTOP, pQmsg->hwnd, &ptlPointer, 1);

                WinPostMsg (pQmsg->hwnd,
                            WM_BUTTON1DOWN,
                            MPFROM2SHORT (ptlPointer.x, ptlPointer.y),
                            MPFROM2SHORT (HT_NORMAL, KC_NONE));
                WinPostMsg (pQmsg->hwnd,
                            WM_BUTTON1UP,
                            MPFROM2SHORT (ptlPointer.x, ptlPointer.y),
                            MPFROM2SHORT (HT_NORMAL, KC_NONE));
                WinPostMsg (pQmsg->hwnd,
                            WM_SINGLESELECT,
                            MPFROM2SHORT (ptlPointer.x, ptlPointer.y),
                            MPFROMLONG (TRUE));
                WinPostMsg (pQmsg->hwnd,
                            WM_BUTTON1DBLCLK,
                            MPFROM2SHORT (ptlPointer.x, ptlPointer.y),
                            MPFROM2SHORT (HT_NORMAL, KC_NONE));
                WinPostMsg (pQmsg->hwnd,
                            WM_OPEN,
                            MPFROMLONG (TRUE),
                            MPFROM2SHORT (ptlPointer.x, ptlPointer.y));
                WinPostMsg (pQmsg->hwnd,
                            WM_BUTTON1UP,
                            MPFROM2SHORT (ptlPointer.x, ptlPointer.y),
                            MPFROM2SHORT (HT_NORMAL, KC_NONE));
                }
            return TRUE;

        case IDR_MAXIMIZE_WND:
            if (btnAction == _btnDn && ulProgType == PROG_PM)
                sizeApplicationWindow (pQmsg, SC_MAXIMIZE);
            return TRUE;

        case IDR_MINIMIZE_WND:
            if (btnAction == _btnDn && ulProgType == PROG_PM)
                sizeApplicationWindow (pQmsg, SC_MINIMIZE);
            return TRUE;

        case IDR_RESTORE_WND:
            if (btnAction == _btnDn && ulProgType == PROG_PM)
                sizeApplicationWindow (pQmsg, SC_RESTORE);
            return TRUE;

        case IDR_TOGGLE_SCROLL:
            if (btnAction == _btnDn)
                toggleScrollDir ();
            return TRUE;

        case IDR_PUSH_TO_BACK:
            if (btnAction == _btnDn && ulProgType == PROG_PM)
                pushToBackground (pQmsg->hwnd);
            return TRUE;
        }

    return FALSE;
    }

/*******************************************************************\
    msgInputHookProc: hook procedure that insertes keyboard events
                      into the system message queue. 2 events are
                      generated: the first to insert the message,
                      the second to restore the shift state.
    Input:  hab:           anchor block handle
            pQmsg:         pointer to QMSG structure
            fSkip:         TRUE: do not insert message
            pfNoRecord:    TRUE: do not insert into journal
    Return: TRUE:     message inserted
            FALSE:    no message inserted
\*******************************************************************/
BOOL APIENTRY msgInputHookProc (HAB hab, PQMSG pQmsg, BOOL fSkip, PBOOL pfNoRecord)
    {
    BOOL bRC = FALSE;

    if (fSkip == FALSE)
        {
        switch (eValidQmsg)
            {
            case MIInserted:
                *pQmsg = qmsg;
                setShiftKeys1 (SHORT1FROMMP (qmsg.mp1));
                eValidQmsg = MIRestore;
                bRC = TRUE;
                break;

            case MIRestore:
                restoreShiftKeys1 ();
                eValidQmsg = MICompleted;
                WinReleaseHook (hab, NULLHANDLE, HK_MSGINPUT, (PFN)msgInputHookProc, hModule);
                break;

            default:
                DosBeep (440, 100);
                WinReleaseHook (hab, NULLHANDLE, HK_MSGINPUT, (PFN)msgInputHookProc, hModule);
            }
        }

    *pfNoRecord = TRUE;
    return bRC;
    }

BOOL APIENTRY inputHookProc (HAB hab, PQMSG pQmsg, ULONG fs)
    {
    ULONG     ulBtnMode;
    BTNACTION btnAction;

    #ifdef _TRACE_
        if ((pQmsg->msg > WM_MOUSEFIRST) && (pQmsg->msg <= WM_MOUSELAST))
            {
            uTrace.trcHook.ulMsg = pQmsg->msg;
            Dos16SysTrace (178, 4, 4, (PUCHAR)&uTrace);
            }
    #endif /* _TRACE_ */

    if (!bShMemIsInitialized)
        {
        if (DosGetNamedSharedMem ((PPVOID)&pShMemMouseData,
                                  SHMEMNAME,
                                  PAG_READ | PAG_WRITE))
            {
            pShMemMouseData = NULL;
            }
        else
            {
            /* open semaphores */
            if (DosOpenMutexSem (SEMNAMEMTX, &hmtxWheelThread) == NO_ERROR)
                {
                if (DosOpenEventSem (SEMNAMEEVT_WIDGET, &hevXWPWidgetUpdate))
                    DosCreateEventSem (SEMNAMEEVT_WIDGET, &hevXWPWidgetUpdate, DC_SEM_SHARED, TRUE);
                }
            if (hmtxWheelThread == NULLHANDLE || hmtxWheelThread == NULLHANDLE)
                pShMemMouseData = NULL;
            }
        bShMemIsInitialized = TRUE;
        }

    if (pShMemMouseData)
        {
        ULONG   ulMsgKey;
        ULONG   ulId;
        ULONG   ulScreenGroup;
        ULONG   ulc;

        ulMsgKey = 0L;
        for (ulc = 0; ulc < 2*CULNUMBUTTONS; ulc++)
            {
            if (structKbdInfo[ulc].ulMsg == pQmsg->msg)
                {
                btnAction     = structKbdInfo[ulc].btnAction;
                ulMsgKey      = structKbdInfo[ulc].ulMsgKey;
                ulScreenGroup = structKbdInfo[ulc].ulScreenGroup;
                ulId          = structKbdInfo[ulc].ulId;

                if (ulScreenGroup == 0)
                    ulScreenGroup = (ULONG)SHORT1FROMMP (pQmsg->mp2);

                if (ulMsgKey == 0)
                    ulMsgKey = LONGFROMMP (pQmsg->mp1);
                }
            }

        if (MESSAGE_KEY == ulMsgKey)
            {
            // For WM_BUTTONxUP/WM_BUTTONxDOWN pQmsg->mp2 contains
            //  x == 3: (WM_HITTEST-result, KEYCODE)
            //  x >= 4: (SCREENGROUP, KEYCODE)
            switch (SHORT2FROMMP (pQmsg->mp2))
                {
                case KC_NONE:
                    ulBtnMode = (ULONG)(pShMemMouseData->ucBtnMode[ulId]);
                    break;

                case KC_CTRL:
                    ulBtnMode = (ULONG)(pShMemMouseData->ucBtnCMode[ulId]);
                    break;

                case KC_ALT:
                    ulBtnMode = (ULONG)(pShMemMouseData->ucBtnAMode[ulId]);
                    break;

                default:
                    ulBtnMode = IDR_END;
                }

            if (ulBtnMode != IDR_END)
                {
                return handleButtonEvent (pQmsg, ulBtnMode, ulId, ulScreenGroup, btnAction);
                }
            }
        }

    return FALSE;
    }

BOOL EXPENTRY destroyWindowHookProc (HAB hab, HWND hwnd, ULONG ulReserved)
    {
    removeWindowHandle (hwnd);
    return TRUE;
    }

