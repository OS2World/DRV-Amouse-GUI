/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: DIALOGS
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   ZustÑndig fÅr die Settings-Pages und andere Dialoge
 *
 * FUNKTIONEN:
 * -----------
 *   determineMouseType
 *   checkForWheelMouse
 *   calcControlId
 *   AboutDlgProc
 *   AboutInitDlg
 *   KeySettingsDlgProc
 *   WheelSettings1DlgProc
 *   WheelSettings2DlgProc
 *   NotebookDlgProc
 *   NotebookInitDlg
 *   NotebookAdjustFramePos
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.10    05-12-02  Handling of shift-keys
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSMODULEMGR
#define INCL_DOSRESOURCES
#define INCL_DOSMISC
#define INCL_DOSERRORS
#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "AMouseGlobal.h"
#include "AMouse.h"
#include "AMouseData.h"
#include "Dialogs.h"
#include "res.h"
#include "dlg.h"
#include "common.h"
#include "commonDlg.h"
#include "panel.h"

/*******************************************************************\
    lokale Funktionsprototypen
\*******************************************************************/
BOOL NotebookInitDlg (HWND hwnd);
VOID NotebookAdjustFramePos (HWND hwndDlg, PSWP pswp);

/*******************************************************************\
    AboutDlgProc: Dialog-Prozedur fÅr About-Box
    Eingang: hwnd: Window-Handle
             msg:  Message-Typ
             mp1:  1. Parameter
             mp2:  2. Parameter
\*******************************************************************/
MRESULT EXPENTRY AboutDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_COMMAND:
            if (SHORT1FROMMP (mp2) == CMDSRC_PUSHBUTTON)
                if (SHORT1FROMMP (mp1) == DID_CANCEL || SHORT1FROMMP (mp1) == DID_OK)
                    WinSendMsg (hwnd, WM_CLOSE, MPVOID, MPVOID);
            return 0;

        case WM_CLOSE:
            WinDismissDlg (hwnd, 0);
            return 0;
        }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
    } /* AboutDlgProc () */

/******************************************************************************
*
*   KeySettings1DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for key settings page 1
*
******************************************************************************/
MRESULT EXPENTRY KeySettings1DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return KeySettings1InitDlg (hwndDlg, NULL, NULL, ((PCREATEDATA)mp2)->ulPageType);

        case WM_DESTROY:
            KeySettings1Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return KeySettings1Command (hwndDlg, mp1);

        case WM_CONTROL:
            return KeySettings1Control (hwndDlg, mp1);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_KEYSETTINGS1),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, 0L, 0L);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* KeySettingsDlgProc */

/******************************************************************************
*
*   KeySettings2DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for key settings page 2
*
******************************************************************************/
MRESULT EXPENTRY KeySettings2DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return KeySettings2InitDlg (hwndDlg, NULL, NULL);

        case WM_DESTROY:
            KeySettings2Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return KeySettings2Command (hwndDlg, mp1);

        case WM_CONTROL:
            return KeySettings2Control (hwndDlg, mp1);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_KEYSETTINGS2),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, 0L, 0L);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* KeySettings2DlgProc */

/******************************************************************************
*
*   WheelSettings1DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/
MRESULT EXPENTRY WheelSettings1DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return WheelSettings1InitDlg (hwndDlg, NULL, NULL, ((PCREATEDATA)mp2)->ulPageType);

        case WM_DESTROY:
            WheelSettings1Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return WheelSettings1Command (hwndDlg, mp1);

        case WM_CONTROL:
            return WheelSettings1Control (hwndDlg, mp1);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_WHEELSETTINGS1),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, 0L, 0L);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* WheelSettings1DlgProc */

/******************************************************************************
*
*   WheelSettings2DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/
MRESULT EXPENTRY WheelSettings2DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return WheelSettings2InitDlg (hwndDlg, NULL, NULL);

        case WM_DESTROY:
            WheelSettings2Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return WheelSettings2Command (hwndDlg, mp1);

        case WM_CONTROL:
            return WheelSettings2Control (hwndDlg, mp1);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_WHEELSETTINGS2),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, 0L, 0L);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* WheelSettings2DlgProc */

/******************************************************************************
*
*   WheelSettings3DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/
MRESULT EXPENTRY WheelSettings3DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return WheelSettings3InitDlg (hwndDlg, NULL, NULL);

        case WM_DESTROY:
            WheelSettings3Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return WheelSettings3Command (hwndDlg, mp1);

        case WM_CONTROL:
            return WheelSettings3Control (hwndDlg, mp1);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_WHEELSETTINGS3),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, 0L, 0L);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* WheelSettings3DlgProc */

/******************************************************************************
*
*   TimingSettingsDlgProc()
*
*   DESCRIPTION:  Dialog Procedure for timing settings page
*
******************************************************************************/
MRESULT EXPENTRY TimingSettingsDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return TimingSettingsInitDlg (hwndDlg, NULL, NULL);

        case WM_DESTROY:
            TimingSettingsDestroy (hwndDlg);
            break;

        case WM_COMMAND:
            return TimingSettingsCommand (hwndDlg, mp1);

        case WM_CONTROL:
            return TimingSettingsControl (hwndDlg, mp1);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_TIMINGSETTINGS),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, 0L, 0L);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* TimingSettingsDlgProc */

/******************************************************************************
*
*   DeviceInfoDlgProc()
*
*   DESCRIPTION:  Dialog Procedure for DeviceInfo page
*
******************************************************************************/
MRESULT EXPENTRY DeviceInfoDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return DeviceInfoInitDlg (hwndDlg);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_DEVICEINFO),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_COMMAND:
            return DeviceInfoCommand (hwndDlg, mp1);
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* DeviceInfoDlgProc */

/******************************************************************************
*
*   WlDeviceInfoDlgProc()
*
*   DESCRIPTION:  Dialog Procedure for second DeviceInfo page
*
******************************************************************************/
MRESULT EXPENTRY WlDeviceInfoDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return WlDeviceInfoInitDlg (hwndDlg);

        case WM_CONTROL:
            return WlDeviceInfoControl (hwndDlg, mp1);

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_WLDEVICEINFO),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_COMMAND:
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* WlDeviceInfoDlgProc */

/******************************************************************************
*
*   NotebookDlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/
MRESULT EXPENTRY NotebookDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return (MRESULT)NotebookInitDlg (hwndDlg);

        case WM_COMMAND:
            switch (SHORT1FROMMP (mp1))
                {
                case IDM_ABOUT:
                    WinDlgBox (HWND_DESKTOP,
                               hwndDlg,
                               (PFNWP)AboutDlgProc,
                               hmodLng,
                               IDD_ABOUTBOX,
                               NULL);

                    return (MRESULT)0;
                }
            return (MRESULT)0;

        case WM_ADJUSTFRAMEPOS:
            NotebookAdjustFramePos (hwndDlg, (PSWP)MPFROMP (mp1));
            break;

        case WM_HELP:
            if (bIsHelp)
                WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                            MPFROMSHORT (PANEL_MAIN),
                            MPFROMSHORT (HM_RESOURCEID));
            return 0;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, MPVOID, MPVOID);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* NotebookDlgProc */

BOOL NotebookInitDlg (HWND hwndDlg)
    {
    /* Variables for system menu */
    static MENUITEM mi[2] =
        {
        {MIT_END, MIS_SEPARATOR, 0L, 0L,         0L, 0L},
        {MIT_END, MIS_TEXT,      0L, IDM_ABOUT,  0L, 0L},
        };
    HWND        hwndSysMenu, hwndSysSubMenu;
    MENUITEM    miSysMenu;
    USHORT      idSysMenu;

    /* Add "About" to system menu */
    hwndSysMenu = WinWindowFromID (hwndDlg, FID_SYSMENU);

    idSysMenu = SHORT1FROMMR (WinSendMsg (hwndSysMenu, MM_ITEMIDFROMPOSITION, NULL, NULL));

    WinSendMsg (hwndSysMenu, MM_QUERYITEM,
                MPFROM2SHORT (idSysMenu, FALSE),
                MPFROMP (&miSysMenu));

    hwndSysSubMenu = miSysMenu.hwndSubMenu;

    WinLoadString (hab, hmodLng, IDS_ABOUT, BUFFLEN, szBuffer);
    WinSendMsg (hwndSysSubMenu, MM_INSERTITEM, MPFROMP (mi),   MPVOID);
    WinSendMsg (hwndSysSubMenu, MM_INSERTITEM, MPFROMP (mi+1), MPFROMP (szBuffer));

    return FALSE;
    }

VOID NotebookAdjustFramePos (HWND hwndDlg, PSWP pswp)
    {
    HWND  hwndNotebook;
    RECTL rcl;
    SWP   swp;
    ULONG cySizeBorder;
    BOOL  b;

    if (pswp->fl & SWP_SIZE)
        {
        hwndNotebook = WinWindowFromID (hwndDlg, DID_NOTEBOOK);

        rcl.xLeft   = pswp->x;
        rcl.xRight  = pswp->x + pswp->cx;
        rcl.yBottom = pswp->y;
        rcl.yTop    = pswp->y + pswp->cy;

        b  = WinCalcFrameRect (hwndDlg, &rcl, TRUE);
        b &= WinQueryWindowPos (hwndNotebook, &swp);

        cySizeBorder = WinQuerySysValue (HWND_DESKTOP, SV_CYSIZEBORDER);

        if (b && (cySizeBorder != 0))
            WinSetWindowPos (hwndNotebook,
                             NULLHANDLE,
                             rcl.xLeft,
                             rcl.yBottom + swp.y,
                             rcl.xRight - rcl.xLeft,
                             rcl.yTop - rcl.yBottom - swp.y + cySizeBorder + 1,
                             SWP_SIZE);
        }

    return;
    }

