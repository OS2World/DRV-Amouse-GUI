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
 *
 *
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
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSMISC
#define INCL_DOSMODULEMGR
#define INCL_DOSRESOURCES
#define INCL_DOSERRORS
#define INCL_WINACCELERATORS
#define INCL_WINBUTTONS
#define INCL_WINDIALOGS
#define INCL_WINSTDSPIN
#define INCL_WINWINDOWMGR
#define INCL_WINLISTBOXES
#define INCL_WINENTRYFIELDS
#define INCL_WINSTDSLIDER
#include <os2.h>

#pragma info(noeff)         // suppress SOM compiler informationals

#include "AMouseGlobal.h"
#include "AMouse.ih"
#include "AMouse.h"

#include "AMouseData.h"
#include "Dialogs.h"
#include "res.h"
#include "dlg.h"
#include "common.h"
#include "commonDlg.h"


/*******************************************************************\
    AboutDlgProc: Dialog-Prozedur fÅr About-Box
    Eingang: hwnd: Window-Handle
             msg:  Message-Typ
             mp1:  1. Parameter
             mp2:  2. Parameter
\*******************************************************************/
MRESULT EXPENTRY AboutDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    AMouse      *somSelf;
    AMouseData  *somThis;
    CHAR         szText[CCHMAXPGNAME];

    switch (msg)
        {
        case WM_INITDLG:
            somSelf = (AMouse *)mp2;
            somThis = AMouseGetData (somSelf);
            WinSetWindowPtr (hwnd, QWL_USER, (PVOID)somSelf);

            /* Ansicht registrieren */
            memset (&_aboutViewItem, '\0', sizeof (VIEWITEM));
            _aboutUseItem.type    = USAGE_OPENVIEW;
            _aboutViewItem.view   = OPEN_ABOUT;
            _aboutViewItem.handle = hwnd;
            _wpAddToObjUseList (somSelf, &_aboutUseItem);

            WinLoadString (hab, hmodLng, IDS_ABOUT, CCHMAXPGNAME, szText);
            _wpRegisterView (somSelf, hwnd, szText);
            return FALSE;

        case WM_COMMAND:
            if (SHORT1FROMMP (mp2) == CMDSRC_PUSHBUTTON)
                if (SHORT1FROMMP (mp1) == DID_CANCEL || SHORT1FROMMP (mp1) == DID_OK)
                    WinSendMsg (hwnd, WM_CLOSE, MPVOID, MPVOID);
            return 0;

        case WM_CLOSE:
            somSelf = (AMouse *)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = AMouseGetData (somSelf);
            _wpDeleteFromObjUseList (somSelf, &_aboutUseItem);
            WinDestroyWindow (hwnd);
            break;
        }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
    } /* AboutDlgProc () */

/******************************************************************************
*
*   KeySettings1DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for button settings page 1
*
******************************************************************************/
MRESULT EXPENTRY KeySettings1DlgProc (HWND hwndDlg, ULONG msg,
                                     MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            {
            AMouse   *somObject      = ((PCREATEDATA)mp2)->somObject;
            M_AMouse *somClassObject = _somGetClass (somObject);

            KeySettings1InitDlg (hwndDlg, somObject, somClassObject, ((PCREATEDATA)mp2)->ulPageType);
            _wpFreeMem (somObject, mp2);
            return (MRESULT)TRUE;
            }

        case WM_DESTROY:
            KeySettings1Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return KeySettings1Command (hwndDlg, mp1);

        case WM_CONTROL:
            return KeySettings1Control (hwndDlg, mp1);
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);

    } /* end KeySettings1DlgProc() */

/******************************************************************************
*
*   KeySettings2DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for button settings page 2
*
******************************************************************************/
MRESULT EXPENTRY KeySettings2DlgProc (HWND hwndDlg, ULONG msg,
                                     MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            {
            AMouse   *somObject      = ((PCREATEDATA)mp2)->somObject;
            M_AMouse *somClassObject = _somGetClass (somObject);

            KeySettings2InitDlg (hwndDlg, somObject, somClassObject);
            _wpFreeMem (somObject, mp2);
            return (MRESULT)TRUE;
            }

        case WM_DESTROY:
            KeySettings2Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return KeySettings2Command (hwndDlg, mp1);

        case WM_CONTROL:
            return KeySettings2Control (hwndDlg, mp1);
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);

    } /* end KeySettings2DlgProc() */

/******************************************************************************
*
*   WheelSettings1DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/
MRESULT EXPENTRY WheelSettings1DlgProc (HWND hwndDlg, ULONG msg,
                                        MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            {
            AMouse   *somObject      = ((PCREATEDATA)mp2)->somObject;
            M_AMouse *somClassObject = _somGetClass (somObject);

            WheelSettings1InitDlg (hwndDlg, somObject, somClassObject, ((PCREATEDATA)mp2)->ulPageType);
            _wpFreeMem (somObject, mp2);
            return (MRESULT)TRUE;
            }

        case WM_DESTROY:
            WheelSettings1Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return WheelSettings1Command (hwndDlg, mp1);

        case WM_CONTROL:
            return WheelSettings1Control (hwndDlg, mp1);
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* end WheelSettings1DlgProc() */

/******************************************************************************
*
*   WheelSettings2DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/

MRESULT EXPENTRY WheelSettings2DlgProc (HWND hwndDlg, ULONG msg,
                                        MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            {
            AMouse   *somObject      = ((PCREATEDATA)mp2)->somObject;
            M_AMouse *somClassObject = _somGetClass (somObject);

            WheelSettings2InitDlg (hwndDlg, somObject, somClassObject);
            _wpFreeMem (somObject, mp2);
            return (MRESULT)TRUE;
            }   /* end case WM_INITDLG: */

        case WM_DESTROY:
            WheelSettings2Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return WheelSettings2Command (hwndDlg, mp1);

        case WM_CONTROL:
            return WheelSettings2Control (hwndDlg, mp1);
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* end WheelSettings2DlgProc() */

/******************************************************************************
*
*   WheelSettings3DlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/

MRESULT EXPENTRY WheelSettings3DlgProc (HWND hwndDlg, ULONG msg,
                                        MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            {
            AMouse   *somObject      = ((PCREATEDATA)mp2)->somObject;
            M_AMouse *somClassObject = _somGetClass (somObject);

            WheelSettings3InitDlg (hwndDlg, somObject, somClassObject);
            _wpFreeMem (somObject, mp2);
            return (MRESULT)TRUE;
            }   /* end case WM_INITDLG: */

        case WM_DESTROY:
            WheelSettings3Destroy (hwndDlg);
            break;

        case WM_COMMAND:
            return WheelSettings3Command (hwndDlg, mp1);

        case WM_CONTROL:
            return WheelSettings3Control (hwndDlg, mp1);
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* end WheelSettings3DlgProc() */

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
            {
            AMouse   *somObject      = ((PCREATEDATA)mp2)->somObject;
            M_AMouse *somClassObject = _somGetClass (somObject);

            TimingSettingsInitDlg (hwndDlg, somObject, somClassObject);
            _wpFreeMem (somObject, mp2);
            return (MRESULT)TRUE;
            }

        case WM_DESTROY:
            TimingSettingsDestroy (hwndDlg);
            break;

        case WM_COMMAND:
            return TimingSettingsCommand (hwndDlg, mp1);

        case WM_CONTROL:
            return TimingSettingsControl (hwndDlg, mp1);
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
MRESULT EXPENTRY DeviceInfoDlgProc (HWND hwndDlg, ULONG msg,
                                    MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return DeviceInfoInitDlg (hwndDlg);

        case WM_COMMAND:
            return DeviceInfoCommand (hwndDlg, mp1);
        } /* end switch(msg) */

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* end DeviceInfoDlgProc() */

/******************************************************************************
*
*   WlDeviceInfoDlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wireless DeviceInfo page
*
******************************************************************************/
MRESULT EXPENTRY WlDeviceInfoDlgProc (HWND hwndDlg, ULONG msg,
                                      MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return (MRESULT)WlDeviceInfoInitDlg (hwndDlg);

        case WM_CONTROL:
            return (MRESULT)WlDeviceInfoControl (hwndDlg, mp1);

        case WM_COMMAND:
            return 0;
        } /* end switch(msg) */

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* end WlDeviceInfoDlgProc() */

