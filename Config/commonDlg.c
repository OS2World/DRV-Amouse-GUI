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
 *   populateComboboxes
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
#define INCL_DOSPROCESS
#define INCL_DOSRESOURCES
#define INCL_DOSMISC
#define INCL_DOSERRORS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#pragma info(noeff)         // suppress SOM compiler informationals

#include "AMouseGlobal.h"
#include "AMouse.h"
#include "AMouseData.h"
#include "AMouRes.h"
#include "res.h"
#include "dlg.h"
#include "panel.h"
#include "common.h"
#include "commonDlg.h"
#include "Vendor.h"

#define CCHMAXDESCRIPTION   32          // buffer length for key description

PFNWP pOldBattStateWndProc = NULL;
static BOOL bIsDebugMode = FALSE;

static CHAR szMessage1[] = "Device ID:\t%d\t\tPort Number:\t%d\n";
static CHAR szMessage2[] = "Type:\t\t%s\t\tButtons:\t\t%s\nWheels:\t\t%s\t\tSub-type:\t%s\nShape:\t\t%s\t\tDevice No:\t%s\nChannel:\t%s\t\tBattery:\t\t%s\nVendor:\t\t%s\n";
static CHAR szMsgTitle[] = "Device Information";
static CHAR szClipboard[] = "\nDevice information has been copied into the clipboard\n";

static BOOL bBatteryWarning = TRUE;     // TRUE: battery warning activated
static BOOL bWarnedState    = FALSE;    // TRUE: already warned

/*******************************************************************\
    Static data of InsertApplicationDlgProc
\*******************************************************************/
PSZ pszMode[] =
    {
    "Scroll",               // MODE_STD
    "Cursor",               // MODE_CSR
    "Page",                 // MODE_PAGE
    "Scroll or Cursor",     // MODE_LINE
    "All",                  // MODE_ALL
    NULL
    };

USHORT usMode[] = {MODE_STD, MODE_CSR, MODE_PAGE, MODE_LINE, MODE_ALL};

PSZ pszRelation[] =
    {
    "None",                 // REL_NONE
    "Parent",               // REL_PARENT
    "Owner",                // REL_OWNER
    "Next",                 // REL_NEXT
    "CB Next",              // REL_IGLB
    "Sibling[Option]",      // REL_SPEC
    NULL
    };

USHORT usRelation[] = {REL_NONE, REL_PARENT, REL_OWNER, REL_NEXT, REL_IGLB, REL_SPEC};

PSZ pszOptionStd[] =
    {
    "page",                 // VKP_PAGE
    "mult cursor ",        // VKP_CUD
    "mult cursor ",        // VKP_CLR
    "cursor ",             // VKP_SUD
    "cursor ",             // VKP_SLR
    NULL
    };

USHORT usOptionStd[] = {VKP_PAGE, VKP_CUD, VKP_CLR, VKP_SUD, VKP_SLR};

PSZ pszMessage[] =
    {
    "WM_NULL",              // WM_NULL
    "WM_CONTROL",           // WM_CONTROL
    "N x WM_VSCROLL",       // WM_VSCROLL
    "N x WM_HSCROLL",       // WM_HSCROLL
    "WM_VSCROLL",           // WM_VSCROLL1
    "WM_HSCROLL",           // WM_HSCROLL1
    "WM_CHAR",              // WM_CHAR
    NULL
    };

USHORT usMessage[] = {WM_NULL, WM_CONTROL, WM_VSCROLL, WM_HSCROLL,
                      WM_VSCROLL1, WM_HSCROLL1, WM_CHAR};

PFNWP pfnwpEntryField = NULL;

/*******************************************************************\
    private function definitions
\*******************************************************************/
MRESULT EXPENTRY BattStateWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY InsertApplicationDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT          InsertApplicationInitDlg (HWND hwndDlg, PINSERTAPPLDLGDATA pInsertApplDlgData);
VOID             InsertApplicationDestroy (HWND hwndDlg);
MRESULT          InsertApplicationCommand (HWND hwndDlg, MPARAM mp1);
MRESULT          InsertApplicationControl (HWND hwndDlg, MPARAM mp1);
MRESULT          InsertApplicationHelp (HWND hwndDlg);

/*******************************************************************\
    Thread that checks the battery state of Logitech mice and pops
    up a warning window, if low.
    input:  ulParm: unused
\*******************************************************************/
VOID _System BatteryCheckThread (ULONG ulParm)
    {
    HFILE     hf;                               // File handle for the device
    ULONG     ulAction;                         // Action taken by DosOpen
    EXT_INFO  strucExtInfo;                     // structure for extended mouse info
    HMQ       hmq = NULLHANDLE;

    static CHAR      szWarning[128];
    static MB2INFO   mb2 =
        {
        sizeof (MB2INFO),                       // cb;          (Current size of the structure.)
        NULLHANDLE,                             // hIcon;       (Icon handle.)
        1,                                      // cButtons;    (Number of buttons.)
        MB_CUSTOMICON,                          // flStyle;     (Icon style flags.)
        NULLHANDLE,                             // hwndNotify;  (Owner notification handle.)
            {
            "~Ok",                              // achText[MAX_MB2DTEXT+1];  (Text of the button.)
            0,                                  // idButton;                 (Button Id returned when selected.)
            BS_DEFAULT                          // flStyle;                  (Button style flags.)
            }
        };

    ulParm;                                     // remove unused-warning

    if (DosOpen ("MOUSE$", &hf, &ulAction, 0,
                 FILE_NORMAL, FILE_OPEN,
                 OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                 (PEAOP2)NULL) == NO_ERROR)
        {
        hmq = WinCreateMsgQueue (hab, 0);
        WinCancelShutdown (hmq, TRUE);

        mb2.hIcon = WinLoadPointer (HWND_DESKTOP, hmod, IDI_BATTERY);
        WinLoadString (hab, hmodLng, IDS_BATT_EMPTY, sizeof (szWarning), szWarning);

        bBatteryWarning = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_BATTERYWARNING, TRUE);

        for (;;)
            {
            if (bBatteryWarning)
                {
                if (getLogiInfo (hf, &strucExtInfo))
                    {
                    if (strucExtInfo.usIndex & ExtBattIdx)
                        {
                        // Battery State 0=unknown, 1+2=critical, 3+4=low, 5+6=ok, 7=high
                        if (!bWarnedState && strucExtInfo.ucBatt == 1)
                            {
                            WinMessageBox2 (HWND_DESKTOP, HWND_DESKTOP, szWarning, "", 0L, &mb2);
                            bWarnedState = TRUE;
                            }
                        else if (strucExtInfo.ucBatt > 2)
                            bWarnedState = FALSE;
                        }
                    }
                }
            DosSleep (5000);
            }
        // WinDestroyMsgQueue (hmq);
        }

    DosExit (EXIT_THREAD, 0);
    }

/*******************************************************************\
    SetDebugMode: Sets the debug mode for Device Information page
    input:  bDebugMode: TRUE  = Debug on
                        FALSE = Debug off
\*******************************************************************/
VOID SetDebugMode (BOOL bDebugMode)
    {
    bIsDebugMode = bDebugMode;
    return;
    }

/*******************************************************************\
    SetButtonsWheelSettings1: Sets the MSG buttons in
        WheelSettings1DlgProc as well as the enabled state of all
        other controls in this dialog.
    input:  hwndDlg:        Window-Handle
            somClassObject: pointer to class object
            pWheelDlgData:  pointer to window instance data
\*******************************************************************/
VOID SetButtonsWheelSettings1 (HWND hwndDlg, M_AMouse *somClassObject, PWHEELDLG1DATA pWheelDlgData)
    {
    ULONG ulScrollModeBtn;
    BOOL  bState;

    ulScrollModeBtn = calcControlId (_clsGetScrollMode (somClassObject, pWheelDlgData->ulWheelPageType));

    WinCheckButton (hwndDlg,
                    (pWheelDlgData->currWheelTarget == WHEEL_TARGET_POINTER ? DID_POINTER_FOCUS : DID_KBD_FOCUS),
                    1);
    WinCheckButton (hwndDlg, ulScrollModeBtn, 1);

    switch (ulScrollModeBtn)
        {
        case DID_MSG_STD:
        case DID_MSG_LINE:
        case DID_MSG_PAGE:
            bState = TRUE;
            break;

        default:
            bState = FALSE;
        }
    WinEnableControl (hwndDlg, DID_POINTER_FOCUS, bState);
    WinEnableControl (hwndDlg, DID_KBD_FOCUS,     bState);
    WinEnableControl (hwndDlg, DID_SCROLLITEMS,   bState);

    return;
    }

VOID SetWheelSettings2Controls (HWND hwndDlg, ULONG ulWheelCount, ULONG ulStartupMode)
    {
    ULONG ulState = (ulWheelCount < 2 ? 0 : 1);
    ULONG ulBtnId = (ulStartupMode == SCROLL_DIR_VERT ? DID_SCROLL_VERT : DID_SCROLL_HORZ);

    WinCheckButton (hwndDlg, DID_WHEEL2, ulState);

    WinEnableControl (hwndDlg, DID_SCROLL_VERT, TRUE);
    WinEnableControl (hwndDlg, DID_SCROLL_HORZ, TRUE);

    WinCheckButton (hwndDlg, DID_SCROLL_VERT, 0);
    WinCheckButton (hwndDlg, DID_SCROLL_HORZ, 0);
    if (!ulState)
        WinCheckButton (hwndDlg, ulBtnId, 1);

    WinEnableControl (hwndDlg, DID_SCROLL_VERT, !ulState);
    WinEnableControl (hwndDlg, DID_SCROLL_HORZ, !ulState);

    return;
    }

/*******************************************************************\
    ReturnSpinIndex: Returns the index of pszText in a text array
        for use in InsertApplicationDlgProc to interpret spin
        button selections
    input:  ppszArray:      pointer to string array
            pszText:        text to be searched
    return: index in ppszArray
\*******************************************************************/
ULONG ReturnSpinIndex (PSZ *ppszArray, PSZ pszText)
    {
    ULONG ulIndex;

    for (ulIndex = 0; ppszArray[ulIndex]; ulIndex++)
        if (strcmp (ppszArray[ulIndex], pszText) == 0)
            return ulIndex;

    return 0;
    }

/*******************************************************************\
    ReturnSpinTextIndex: Returns the index of pszText a text array
        for use in InsertApplicationDlgProc to interpret spin
        button selections
    input:  ppszArray:      pointer to string array
            pusArray:       pointer to array of id's
            usId:           id to be searched in pusArray
    return: index in ppszArray
\*******************************************************************/
ULONG ReturnSpinTextIndex (PSZ *ppszArray, PUSHORT pusArray, USHORT usId)
    {
    ULONG ulIndex;

    for (ulIndex = 0; ppszArray[ulIndex]; ulIndex++)
        if (pusArray[ulIndex] == usId)
            return ulIndex;

    return 0;
    }

/*******************************************************************\
    FillApplicationListBox: fills list box of WheelSettings3DlgProc
    input:  hwndDlg:     dialog window handle
            sIndex:      index of item to be selected
            pstructAppl: application definition array
\*******************************************************************/
VOID FillApplicationListBox (HWND hwndDlg, SHORT sIndex, PSTRUCTAPPL pstructAppl)
    {
    ULONG ulIndex;
    ULONG ulCount;

    WinSendDlgItemMsg (hwndDlg, DID_W3_DESCRIPTION, LM_DELETEALL, MPVOID, MPVOID);
    ulCount = ApplNumOfEntries (pstructAppl);

    /* Refresh dialog entries */
    for (ulIndex = 0; ulIndex < ulCount; ulIndex++)
        WinSendDlgItemMsg (hwndDlg, DID_W3_DESCRIPTION, LM_INSERTITEM,
                           MPFROMSHORT (LIT_END),
                           MPFROMP (pstructAppl[ulIndex].szDescription));

    if (sIndex >= ulCount && sIndex > 0)
        sIndex--;

    WinSendDlgItemMsg (hwndDlg,
                       DID_W3_DESCRIPTION,
                       LM_SELECTITEM,
                       MPFROMSHORT (sIndex),
                       MPFROMSHORT (TRUE));

    WinEnableControl (hwndDlg, DID_W3_UP,     (sIndex == 0         ? FALSE : TRUE));
    WinEnableControl (hwndDlg, DID_W3_DOWN,   (sIndex+1 >= ulIndex ? FALSE : TRUE));
    WinEnableControl (hwndDlg, DID_W3_INSERT, ApplFreeEntries (pstructAppl));
    WinEnableControl (hwndDlg, DID_W3_DELETE, ApplNumOfEntries (pstructAppl) > 0);

    return;
    }

VOID FillApplicationEntries (HWND hwndDlg, PSTRUCTAPPL pstructAppl)
    {
    ULONG ulId;
    ULONG ulIndex;

    ulIndex = (ULONG)(SHORT)WinSendDlgItemMsg (hwndDlg,
                                               DID_W3_DESCRIPTION,
                                               LM_QUERYSELECTION,
                                               MPFROMSHORT (LIT_FIRST),
                                               MPVOID);

    if (pstructAppl[ulIndex].szDescription[0] == '\0')
        {
        WinSetDlgItemText (hwndDlg, DID_W3_APPLICATION, "");
        WinSetDlgItemText (hwndDlg, DID_W3_CLASS,       "");
        WinSetDlgItemText (hwndDlg, DID_W3_PARENTCLASS, "");
        WinSetDlgItemText (hwndDlg, DID_W3_OPTION,      "");

        WinSetDlgItemText (hwndDlg, DID_W3_MODE,        "");
        WinSetDlgItemText (hwndDlg, DID_W3_VREL,        "");
        WinSetDlgItemText (hwndDlg, DID_W3_VOPT,        "");
        WinSetDlgItemText (hwndDlg, DID_W3_UPDOWN,      "");
        WinSetDlgItemText (hwndDlg, DID_W3_HREL,        "");
        WinSetDlgItemText (hwndDlg, DID_W3_HOPT,        "");
        WinSetDlgItemText (hwndDlg, DID_W3_LEFTRIGHT,   "");
        }
    else
        {
        WinSetDlgItemText (hwndDlg, DID_W3_APPLICATION, pstructAppl[ulIndex].szApplication);
        WinSetDlgItemText (hwndDlg, DID_W3_CLASS,       pstructAppl[ulIndex].szClass);
        WinSetDlgItemText (hwndDlg, DID_W3_PARENTCLASS, pstructAppl[ulIndex].szParentClass);
        WinSetDlgItemText (hwndDlg, DID_W3_OPTION,      pstructAppl[ulIndex].szOption);

        ulId = ReturnSpinTextIndex (pszMode, usMode, pstructAppl[ulIndex].strucResData.usScrollMode);
        WinSetDlgItemText (hwndDlg, DID_W3_MODE, pszMode[ulId]);

        ulId = ReturnSpinTextIndex (pszRelation, usRelation, pstructAppl[ulIndex].strucResData.usVRelation);
        WinSetDlgItemText (hwndDlg, DID_W3_VREL, pszRelation[ulId]);

        ulId = ReturnSpinTextIndex (pszOptionStd, usOptionStd, pstructAppl[ulIndex].strucResData.usVOpt);
        WinSetDlgItemText (hwndDlg, DID_W3_VOPT, pszOptionStd[ulId]);

        ulId = ReturnSpinTextIndex (pszMessage, usMessage, pstructAppl[ulIndex].strucResData.usMsgUp);
        WinSetDlgItemText (hwndDlg, DID_W3_UPDOWN, pszMessage[ulId]);

        ulId = ReturnSpinTextIndex (pszRelation, usRelation, pstructAppl[ulIndex].strucResData.usHRelation);
        WinSetDlgItemText (hwndDlg, DID_W3_HREL, pszRelation[ulId]);

        ulId = ReturnSpinTextIndex (pszOptionStd, usOptionStd, pstructAppl[ulIndex].strucResData.usHOpt);
        WinSetDlgItemText (hwndDlg, DID_W3_HOPT, pszOptionStd[ulId]);

        ulId = ReturnSpinTextIndex (pszMessage, usMessage, pstructAppl[ulIndex].strucResData.usMsgLeft);
        WinSetDlgItemText (hwndDlg, DID_W3_LEFTRIGHT, pszMessage[ulId]);

        /* Deactivate unused entry fields */
        if (pstructAppl[ulIndex].strucResData.usVRelation != REL_SPEC &&
            pstructAppl[ulIndex].strucResData.usHRelation != REL_SPEC)
            WinSetDlgItemText (hwndDlg, DID_W3_OPTION, "");

        switch (pstructAppl[ulIndex].strucResData.usMsgUp)
            {
            case WM_NULL:
            case WM_VSCROLL:
            case WM_HSCROLL:
            case WM_VSCROLL1:
            case WM_HSCROLL1:
                WinSetDlgItemText (hwndDlg, DID_W3_VOPT, "");
                break;
            }

        switch (pstructAppl[ulIndex].strucResData.usMsgLeft)
            {
            case WM_NULL:
            case WM_VSCROLL:
            case WM_HSCROLL:
            case WM_VSCROLL1:
            case WM_HSCROLL1:
                WinSetDlgItemText (hwndDlg, DID_W3_HOPT, "");
                break;
            }
        }

    return;
    }

MRESULT EXPENTRY KeyCombinationDialogProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    MRESULT rc;

    switch (msg)
        {
        case WM_CHAR:
            // have this key combo checked if valid:
            // if KC_VIRTUALKEY is down,
            // we must filter out the sole CTRL, ALT, and
            // SHIFT keys, because these are valid only
            // when pressed with some other key
            rc = (MRESULT)FALSE;

            if (!(SHORT1FROMMP (mp1) & KC_KEYUP))
                {
                PKEYCOMBDATA pKeyCombData;

                pKeyCombData = (PKEYCOMBDATA)WinQueryWindowPtr (hwndDlg, QWL_USER);

                if (isValidKey (SHORT1FROMMP (mp1), CHAR1FROMMP (mp2), SHORT2FROMMP (mp2)))
                    {
                    CHAR szDescription[CCHMAXDESCRIPTION];

                    // valid key
                    describeKey (szDescription, CCHMAXDESCRIPTION, SHORT1FROMMP (mp1), CHAR1FROMMP (mp2), SHORT2FROMMP (mp2));
                    WinSetWindowText (hwndDlg, szDescription);
                    rc = (MRESULT)TRUE;
                    }
                else
                    {
                    mp1 = mp2 = 0;
                    WinSetWindowText (hwndDlg, "");
                    }
                pKeyCombData->ulCharMP1 = LONGFROMMP (mp1);
                pKeyCombData->ulCharMP2 = LONGFROMMP (mp2);
                }
            return rc;

        case WM_SETFOCUS:
            {
            // if the entry field gets focus, the Accelerator table will be deleted; before, the
            // standard table will be saved for later use.
            // if the entry field looses focus, the old Accelerator table will be restored
            HACCEL  hAccel;
            PKEYCOMBDATA pKeyCombData;

            pKeyCombData = (PKEYCOMBDATA)WinQueryWindowPtr (hwndDlg, QWL_USER);

            if (SHORT1FROMMP (mp2))         // gaining focus
                {
                ULONG ulCopyMax;

                if (!pKeyCombData->pacctAccelTable)
                    {
                    hAccel    = WinQueryAccelTable (hab, NULLHANDLE);
                    ulCopyMax = WinCopyAccelTable (hAccel, NULL, 0);

                    pKeyCombData->pacctAccelTable = (PACCELTABLE)_wpAllocMem (pKeyCombData->somObject, ulCopyMax, NULL);
                    WinCopyAccelTable (hAccel, pKeyCombData->pacctAccelTable, ulCopyMax);
                    }

                WinSetAccelTable (hab, NULLHANDLE, NULLHANDLE);
                }
            else                            // losing focus
                {
                if (pKeyCombData->pacctAccelTable)
                    {
                    hAccel = WinCreateAccelTable (hab, pKeyCombData->pacctAccelTable);
                    WinSetAccelTable (hab, hAccel, NULLHANDLE);
                    }
                }

            break;
            }
        }

    return (MRESULT)pfnwpEntryField (hwndDlg, msg, mp1, mp2);
    }

MRESULT KeySettings1InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject, ULONG ulPageType)
    {
    PKEYDLG1DATA pKeyDlg1Data;
    PKEYCOMBDATA pKeyCombData;
    CHAR         szPageType[CCHMAXPAGETYPE];
    LONG         ulId;

    pKeyDlg1Data = (PKEYDLG1DATA)_wpAllocMem (somObject, sizeof (*pKeyDlg1Data), NULL);

    /* Initialize dialog panel */
    /* 1. Initialize private structure */
    memset ((PVOID)pKeyDlg1Data, 0, sizeof (*pKeyDlg1Data));
    pKeyDlg1Data->cb = sizeof (*pKeyDlg1Data);
    pKeyDlg1Data->somObject      = somObject;
    pKeyDlg1Data->somClassObject = somClassObject;
    pKeyDlg1Data->ulBtnPageType  = ulPageType;

    WinSetWindowPtr (hwndDlg, QWL_USER, pKeyDlg1Data);

    /* 2. Insert strings into Comboboxes */
    populateComboboxes (hwndDlg, hmodLng, ulPageType);

    /* 3. Set Comboboxes to current values */
    for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
        {
        /* 3a: Set button mode */
        pKeyDlg1Data->currBtnMode[ulId] =
        pKeyDlg1Data->prevBtnMode[ulId] = _clsGetBtnMode (somClassObject, pKeyDlg1Data->ulBtnPageType, CIDBUTTONMIN+ulId);

        WinSendDlgItemMsg (hwndDlg, DID_BUTTON3+ulId, LM_SELECTITEM,
                           MPFROMSHORT (pKeyDlg1Data->currBtnMode[ulId]), MPFROMSHORT (TRUE));
        WinSendDlgItemMsg (hwndDlg, DID_BUTTON3+ulId, EM_SETREADONLY, MPFROMLONG (TRUE), 0L);

        /* 3b: If first page: set key combination, if necessary */
        if (BTNPAGE_NONE == pKeyDlg1Data->ulBtnPageType)
            {
            pKeyDlg1Data->currBtnMP1[ulId] =
            pKeyDlg1Data->prevBtnMP1[ulId] = _clsGetBtnKeyCombMP1 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN);
            pKeyDlg1Data->currBtnMP2[ulId] =
            pKeyDlg1Data->prevBtnMP2[ulId] = _clsGetBtnKeyCombMP2 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN);
            if (IDR_KEY == pKeyDlg1Data->currBtnMode[ulId])
                {
                insertKeyCombString (hwndDlg, pKeyDlg1Data->currBtnMP1[ulId], pKeyDlg1Data->currBtnMP2[ulId], DID_BUTTON3+ulId);
                }
            }
        }

    /* 4. Set Page Heading */
    switch (pKeyDlg1Data->ulBtnPageType)
        {
        case BTNPAGE_NONE:
            ulId = IDS_PAGE_BUTTON;
            break;

        case BTNPAGE_CTRL:
            ulId = IDS_PAGE_BUTTON_C;
            break;

        case BTNPAGE_ALT:
            ulId = IDS_PAGE_BUTTON_A;
            break;

        default:
            ulId = NULLHANDLE;
        }

    if (ulId)
        {
        WinLoadString (hab, hmodLng, ulId, CCHMAXPAGETYPE, szPageType);
        WinSetDlgItemText (hwndDlg, DID_BTN_PAGE_TYPE, szPageType);
        }

    /* 5. Subclass Key Entry Control on first page */
    if (BTNPAGE_NONE == pKeyDlg1Data->ulBtnPageType)
        {
        if (!pfnwpEntryField)
            pfnwpEntryField = WinSubclassWindow (WinWindowFromID (hwndDlg, DID_KEYCOMB), (PFNWP)KeyCombinationDialogProc);

        pKeyCombData = (PKEYCOMBDATA)_wpAllocMem (somObject, sizeof (*pKeyCombData), NULL);
        memset ((PVOID)pKeyCombData, 0, sizeof (*pKeyCombData));
        pKeyCombData->cb        = sizeof (*pKeyCombData);
        pKeyCombData->somObject = somObject;
        pKeyCombData->ulCharMP1 = 0;
        pKeyCombData->ulCharMP2 = 0;
        WinSetWindowPtr (WinWindowFromID (hwndDlg, DID_KEYCOMB), QWL_USER, pKeyCombData);
        }
    else
        {
        WinShowWindow (WinWindowFromID (hwndDlg, DID_KEYCOMBTEXT), FALSE);
        WinShowWindow (WinWindowFromID (hwndDlg, DID_KEYCOMB),     FALSE);

        for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
            WinShowWindow (WinWindowFromID (hwndDlg, DID_KC_SET3+ulId), FALSE);
        }

    return (MRESULT)TRUE;
    }

VOID KeySettings1Destroy (HWND hwndDlg)
    {
    PKEYDLG1DATA pKeyDlg1Data;
    PKEYCOMBDATA pKeyCombData;

    pKeyDlg1Data = WinQueryWindowPtr (hwndDlg, QWL_USER);

    if (BTNPAGE_NONE == pKeyDlg1Data->ulBtnPageType)
        {
        if (pfnwpEntryField)
            {
            WinSubclassWindow (WinWindowFromID (hwndDlg, DID_KEYCOMB), pfnwpEntryField);
            pfnwpEntryField = NULL;
            }

        pKeyCombData = WinQueryWindowPtr (WinWindowFromID (hwndDlg, DID_KEYCOMB), QWL_USER);
        if (pKeyCombData->pacctAccelTable)
            _wpFreeMem (pKeyCombData->somObject, (PBYTE)pKeyCombData->pacctAccelTable);
        _wpFreeMem (pKeyCombData->somObject, (PBYTE)pKeyCombData);
        }

    _wpFreeMem (pKeyDlg1Data->somObject, (PBYTE)pKeyDlg1Data);

    return;
    }

MRESULT KeySettings1Command (HWND hwndDlg, MPARAM mp1)
    {
    PKEYDLG1DATA pKeyDlg1Data;
    PKEYCOMBDATA pKeyCombData;
    M_AMouse    *somClassObject;
    ULONG        ulId;

    pKeyDlg1Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pKeyDlg1Data->somClassObject;

    pKeyCombData = WinQueryWindowPtr (WinWindowFromID (hwndDlg, DID_KEYCOMB), QWL_USER);

    switch (SHORT1FROMMP (mp1))
        {
        case DID_KC_SET3:
        case DID_KC_SET4:
        case DID_KC_SET5:
        case DID_KC_SET6:
        case DID_KC_SET7:
        case DID_KC_SET8:
        case DID_KC_SET9:
        case DID_KC_SET10:
            ulId = SHORT1FROMMP (mp1) - DID_KC_SET3;
            insertKeyCombString (hwndDlg, pKeyCombData->ulCharMP1, pKeyCombData->ulCharMP2, DID_BUTTON3+ulId);
            pKeyDlg1Data->prevBtnMP1[ulId] = pKeyDlg1Data->currBtnMP1[ulId];
            pKeyDlg1Data->prevBtnMP2[ulId] = pKeyDlg1Data->currBtnMP2[ulId];
            pKeyDlg1Data->currBtnMP1[ulId] = pKeyCombData->ulCharMP1;
            pKeyDlg1Data->currBtnMP2[ulId] = pKeyCombData->ulCharMP2;
            _clsSetBtnKeyCombMP1 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN, pKeyDlg1Data->currBtnMP1[ulId]);
            _clsSetBtnKeyCombMP2 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN, pKeyDlg1Data->currBtnMP2[ulId]);
            break;

        case DID_UNDO:
            for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
                {
                pKeyDlg1Data->currBtnMode[ulId] = pKeyDlg1Data->prevBtnMode[ulId];
                _clsSetBtnMode (somClassObject,
                                pKeyDlg1Data->ulBtnPageType,
                                CIDBUTTONMIN+ulId,
                                pKeyDlg1Data->currBtnMode[ulId]);

                pKeyDlg1Data->currBtnMP1[ulId] = pKeyDlg1Data->prevBtnMP1[ulId];
                pKeyDlg1Data->currBtnMP2[ulId] = pKeyDlg1Data->prevBtnMP2[ulId];
                _clsSetBtnKeyCombMP1 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN, pKeyDlg1Data->currBtnMP1[ulId]);
                _clsSetBtnKeyCombMP2 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN, pKeyDlg1Data->currBtnMP2[ulId]);

                WinSendDlgItemMsg (hwndDlg, DID_BUTTON3+ulId, LM_SELECTITEM,
                                   MPFROMSHORT (pKeyDlg1Data->currBtnMode[ulId]), MPFROMSHORT (TRUE));
                }

            WinSetDlgItemText (hwndDlg, DID_KEYCOMB, "");
            break;

        case DID_DEFAULT:
            {
            /* message create WM_CONTROL-message, where persistence actions are done */
            for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
                {
                WinSendDlgItemMsg (hwndDlg, DID_BUTTON3+ulId, LM_SELECTITEM,
                    MPFROMSHORT ((SHORT)getDefaultKeySetting (pKeyDlg1Data->ulBtnPageType, CIDBUTTONMIN+ulId)),
                    MPFROMSHORT (TRUE));

                _clsSetBtnKeyCombMP1 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN, 0L);
                _clsSetBtnKeyCombMP2 (somClassObject, pKeyDlg1Data->ulBtnPageType, ulId+CIDBUTTONMIN, 0L);
                }

            WinSetDlgItemText (hwndDlg, DID_KEYCOMB, "");
            break;
            }
        }

    return (MRESULT)0;
    }

MRESULT KeySettings1Control (HWND hwndDlg, MPARAM mp1)
    {
    PKEYDLG1DATA pKeyDlg1Data;
    M_AMouse    *somClassObject;
    ULONG        ulId;

    pKeyDlg1Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pKeyDlg1Data->somClassObject;

    switch (SHORT1FROMMP (mp1))
        {
        case DID_BUTTON3:
        case DID_BUTTON4:
        case DID_BUTTON5:
        case DID_BUTTON6:
        case DID_BUTTON7:
        case DID_BUTTON8:
        case DID_BUTTON9:
        case DID_BUTTON10:
            ulId = SHORT1FROMMP (mp1) - DID_BUTTON3;

            switch (SHORT2FROMMP (mp1))
                {
                case CBN_LBSELECT:
                    pKeyDlg1Data->prevBtnMode[ulId] = pKeyDlg1Data->currBtnMode[ulId];
                    pKeyDlg1Data->currBtnMode[ulId] = (ULONG)WinSendDlgItemMsg (hwndDlg,
                                                                                DID_BUTTON3+ulId,
                                                                                LM_QUERYSELECTION,
                                                                                MPFROMSHORT (0),
                                                                                MPVOID);
                    WinSendDlgItemMsg (hwndDlg, DID_BUTTON3+ulId, EM_SETREADONLY,
                                       MPFROMLONG(!(IDR_KEY == pKeyDlg1Data->currBtnMode[ulId])), 0L);
                    _clsSetBtnMode (somClassObject,
                                    pKeyDlg1Data->ulBtnPageType,
                                    CIDBUTTONMIN+ulId,
                                    pKeyDlg1Data->currBtnMode[ulId]);

                    WinEnableControl (hwndDlg, DID_KC_SET3+ulId, (pKeyDlg1Data->currBtnMode[ulId] == IDR_KEY));
                    break;

                case CBN_ENTER:
                    if ((BTNPAGE_NONE == pKeyDlg1Data->ulBtnPageType) &&
                       (IDR_KEY == pKeyDlg1Data->currBtnMode[ulId]))
                        {
                        insertKeyCombString (hwndDlg,
                                             pKeyDlg1Data->currBtnMP1[ulId],
                                             pKeyDlg1Data->currBtnMP2[ulId],
                                             SHORT1FROMMP (mp1));
                        }
                    break;
                }
            break;
        }

    return 0;
    }

MRESULT KeySettings2InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject)
    {
    PKEYDLG2DATA pKeyDlg2Data;

    pKeyDlg2Data = (PKEYDLG2DATA)_wpAllocMem (somObject, sizeof (*pKeyDlg2Data), NULL);

    memset ((PVOID)pKeyDlg2Data, 0, sizeof (*pKeyDlg2Data));
    pKeyDlg2Data->cb = sizeof (*pKeyDlg2Data);
    pKeyDlg2Data->somObject       = somObject;
    pKeyDlg2Data->somClassObject  = somClassObject;
    pKeyDlg2Data->currFlgPmCtls   =
    pKeyDlg2Data->prevFlgPmCtls   = _clsGetPMCtlsFlags (somClassObject);
    pKeyDlg2Data->currSmartCruise =
    pKeyDlg2Data->prevSmartCruise = _clsGetSmartCruise (somClassObject);
    WinSetWindowPtr (hwndDlg, QWL_USER, pKeyDlg2Data);

    WinCheckButton (hwndDlg, DID_PMCTLS_ENTRY, (pKeyDlg2Data->currFlgPmCtls & PMCTL_ENTRY ? TRUE : FALSE));
    WinCheckButton (hwndDlg, DID_PMCTLS_COMBO, (pKeyDlg2Data->currFlgPmCtls & PMCTL_COMBO ? TRUE : FALSE));
    WinCheckButton (hwndDlg, DID_SMARTCRUISE,  (pKeyDlg2Data->currSmartCruise != SMART_CRUISE_OFF));

    return (MRESULT)TRUE;
    }

VOID KeySettings2Destroy (HWND hwndDlg)
    {
    PKEYDLG2DATA pKeyDlg2Data;

    pKeyDlg2Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    _wpFreeMem (pKeyDlg2Data->somObject, (PBYTE)pKeyDlg2Data);

    return;
    }

MRESULT KeySettings2Command (HWND hwndDlg, MPARAM mp1)
    {
    PKEYDLG2DATA pKeyDlg2Data;
    M_AMouse    *somClassObject;

    pKeyDlg2Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pKeyDlg2Data->somClassObject;

    switch (SHORT1FROMMP (mp1))
        {
        case DID_UNDO:
            pKeyDlg2Data->currFlgPmCtls   = pKeyDlg2Data->prevFlgPmCtls;
            pKeyDlg2Data->currSmartCruise = pKeyDlg2Data->prevSmartCruise;

            _clsSetPMCtlsFlags (somClassObject, pKeyDlg2Data->currFlgPmCtls);
            _clsSetSmartCruise (somClassObject, pKeyDlg2Data->currSmartCruise);

            WinCheckButton (hwndDlg, DID_PMCTLS_ENTRY, (pKeyDlg2Data->currFlgPmCtls & PMCTL_ENTRY ? TRUE : FALSE));
            WinCheckButton (hwndDlg, DID_PMCTLS_COMBO, (pKeyDlg2Data->currFlgPmCtls & PMCTL_COMBO ? TRUE : FALSE));
            WinCheckButton (hwndDlg, DID_SMARTCRUISE,  (pKeyDlg2Data->currSmartCruise != SMART_CRUISE_OFF));
            break;

        case DID_DEFAULT:
            /* preserve previous values */
            pKeyDlg2Data->prevFlgPmCtls   = pKeyDlg2Data->currFlgPmCtls;
            pKeyDlg2Data->currFlgPmCtls   = 0;
            pKeyDlg2Data->prevSmartCruise = pKeyDlg2Data->currSmartCruise;
            pKeyDlg2Data->currSmartCruise = DEF_VALUE_SMARTCRUISE;

            _clsSetPMCtlsFlags (somClassObject, pKeyDlg2Data->currFlgPmCtls);
            _clsSetSmartCruise (somClassObject, pKeyDlg2Data->currSmartCruise);

            WinCheckButton (hwndDlg, DID_PMCTLS_ENTRY, (pKeyDlg2Data->currFlgPmCtls & PMCTL_ENTRY ? TRUE : FALSE));
            WinCheckButton (hwndDlg, DID_PMCTLS_COMBO, (pKeyDlg2Data->currFlgPmCtls & PMCTL_COMBO ? TRUE : FALSE));
            WinCheckButton (hwndDlg, DID_SMARTCRUISE,  (pKeyDlg2Data->currSmartCruise != SMART_CRUISE_OFF));
            break;
        }

    return (MRESULT)0;
    }

MRESULT KeySettings2Control (HWND hwndDlg, MPARAM mp1)
    {
    PKEYDLG2DATA pKeyDlg2Data;
    M_AMouse    *somClassObject;

    pKeyDlg2Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pKeyDlg2Data->somClassObject;

    if (SHORT2FROMMP (mp1) == BN_CLICKED)
        {
        switch (SHORT1FROMMP (mp1))
            {
            case DID_PMCTLS_ENTRY:
                pKeyDlg2Data->prevFlgPmCtls = pKeyDlg2Data->currFlgPmCtls;
                pKeyDlg2Data->currFlgPmCtls &= ~PMCTL_ENTRY;
                pKeyDlg2Data->currFlgPmCtls |= (WinQueryButtonCheckstate (hwndDlg, DID_PMCTLS_ENTRY) ? PMCTL_ENTRY : 0);
                _clsSetPMCtlsFlags (somClassObject, pKeyDlg2Data->currFlgPmCtls);
                break;

            case DID_PMCTLS_COMBO:
                pKeyDlg2Data->prevFlgPmCtls = pKeyDlg2Data->currFlgPmCtls;
                pKeyDlg2Data->currFlgPmCtls &= ~PMCTL_COMBO;
                pKeyDlg2Data->currFlgPmCtls |= (WinQueryButtonCheckstate (hwndDlg, DID_PMCTLS_COMBO) ? PMCTL_COMBO : 0);
                _clsSetPMCtlsFlags (somClassObject, pKeyDlg2Data->currFlgPmCtls);
                break;

            case DID_SMARTCRUISE:
                pKeyDlg2Data->prevSmartCruise = pKeyDlg2Data->currSmartCruise;
                pKeyDlg2Data->currSmartCruise = (WinQueryButtonCheckstate (hwndDlg, DID_SMARTCRUISE) ? SMART_CRUISE_ALL : SMART_CRUISE_OFF);
                _clsSetSmartCruise (somClassObject, pKeyDlg2Data->currSmartCruise);
                break;
            }
        }

    return 0;
    }

MRESULT WheelSettings1InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject, ULONG ulPageType)
    {
    PWHEELDLG1DATA pWheelDlg1Data;
    CHAR           szPageType[CCHMAXPAGETYPE];
    ULONG          ulId;

    pWheelDlg1Data = (PWHEELDLG1DATA)_wpAllocMem (somObject, sizeof (*pWheelDlg1Data), NULL);

    /* Initialize dialog panel */
    memset ((PVOID)pWheelDlg1Data, 0, sizeof (*pWheelDlg1Data));
    pWheelDlg1Data->cb = sizeof (*pWheelDlg1Data);
    pWheelDlg1Data->somObject       = somObject;
    pWheelDlg1Data->somClassObject  = somClassObject;
    pWheelDlg1Data->ulWheelPageType = ulPageType;
    pWheelDlg1Data->currScrollMode  =
    pWheelDlg1Data->prevScrollMode  = _clsGetScrollMode (somClassObject, pWheelDlg1Data->ulWheelPageType);
    pWheelDlg1Data->currScrollNum   =
    pWheelDlg1Data->prevScrollNum   = _clsGetScrollNum  (somClassObject, pWheelDlg1Data->ulWheelPageType);
    pWheelDlg1Data->currWheelTarget =
    pWheelDlg1Data->prevWheelTarget = _clsGetWheelTarget (somClassObject, pWheelDlg1Data->ulWheelPageType);
    WinSetWindowPtr (hwndDlg, QWL_USER, pWheelDlg1Data);

    SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
    WinSendDlgItemMsg (hwndDlg, DID_SCROLLITEMS, SPBM_SETLIMITS, (MPARAM)10, (MPARAM)1);
    WinSendDlgItemMsg (hwndDlg, DID_SCROLLITEMS, SPBM_SETCURRENTVALUE,
                       (MPARAM) pWheelDlg1Data->currScrollNum, NULL);

    switch (pWheelDlg1Data->ulWheelPageType)
        {
        case WHEELPAGE_NONE:
            ulId = IDS_PAGE_WHEEL;
            break;

        case WHEELPAGE_CTRL:
            ulId = IDS_PAGE_WHEEL_C;
            break;

        case WHEELPAGE_ALT:
            ulId = IDS_PAGE_WHEEL_A;
            break;

        default:
            ulId = NULLHANDLE;
        }

    if (ulId)
        {
        WinLoadString (hab, hmodLng, ulId, CCHMAXPAGETYPE, szPageType);
        WinSetDlgItemText (hwndDlg, DID_WHEEL_PAGE_TYPE, szPageType);
        }

    return (MRESULT)TRUE;
    }

VOID WheelSettings1Destroy (HWND hwndDlg)
    {
    PWHEELDLG1DATA pWheelDlg1Data;

    pWheelDlg1Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    _wpFreeMem (pWheelDlg1Data->somObject, (PBYTE)pWheelDlg1Data);

    return;
    }

MRESULT WheelSettings1Command (HWND hwndDlg, MPARAM mp1)
    {
    PWHEELDLG1DATA pWheelDlg1Data;
    M_AMouse      *somClassObject;

    pWheelDlg1Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pWheelDlg1Data->somClassObject;

    switch (SHORT1FROMMP (mp1))
        {
        case DID_UNDO:
            pWheelDlg1Data->currScrollMode  = pWheelDlg1Data->prevScrollMode;
            pWheelDlg1Data->currScrollNum   = pWheelDlg1Data->prevScrollNum;
            pWheelDlg1Data->currWheelTarget = pWheelDlg1Data->prevWheelTarget;

            _clsSetScrollMode  (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollMode);
            _clsSetScrollNum   (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollNum);
            _clsSetWheelTarget (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currWheelTarget);

            WinSendDlgItemMsg (hwndDlg, DID_SCROLLITEMS, SPBM_SETCURRENTVALUE,
                               (MPARAM)pWheelDlg1Data->currScrollNum, NULL);
            SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
            break;

        case DID_DEFAULT:
            /* preserve previous values and set default values */
            pWheelDlg1Data->prevScrollMode  = pWheelDlg1Data->currScrollMode;
            if (pWheelDlg1Data->ulWheelPageType == WHEELPAGE_NONE)
                pWheelDlg1Data->currScrollMode  = SCROLL_MODE_STD;
            else
                pWheelDlg1Data->currScrollMode  = SCROLL_MODE_NONE;
            pWheelDlg1Data->prevScrollNum   = pWheelDlg1Data->currScrollNum;
            pWheelDlg1Data->currScrollNum   = 3;
            pWheelDlg1Data->prevWheelTarget = pWheelDlg1Data->currWheelTarget;
            pWheelDlg1Data->currWheelTarget = WHEEL_TARGET_POINTER;

            _clsSetScrollMode  (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollMode);
            _clsSetScrollNum   (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollNum);
            _clsSetWheelTarget (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currWheelTarget);

            WinSendDlgItemMsg (hwndDlg, DID_SCROLLITEMS, SPBM_SETCURRENTVALUE,
                               (MPARAM)pWheelDlg1Data->currScrollNum, NULL);
            SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
            break;
        }

    return (MRESULT)0;
    }

MRESULT WheelSettings1Control (HWND hwndDlg, MPARAM mp1)
    {
    PWHEELDLG1DATA pWheelDlg1Data;
    M_AMouse      *somClassObject;

    pWheelDlg1Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pWheelDlg1Data->somClassObject;

    if ((SHORT2FROMMP (mp1) == BN_CLICKED) ||
        (SHORT1FROMMP (mp1) == DID_SCROLLITEMS))
        {
        switch (SHORT1FROMMP (mp1))
            {
            case DID_KBD_FOCUS:
            case DID_POINTER_FOCUS:
                pWheelDlg1Data->prevWheelTarget = pWheelDlg1Data->currWheelTarget;
                pWheelDlg1Data->currWheelTarget = WHEEL_TARGET_POINTER;
                if (WinQueryButtonCheckstate (hwndDlg, DID_KBD_FOCUS))
                    pWheelDlg1Data->currWheelTarget = WHEEL_TARGET_KBD;
                _clsSetWheelTarget (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currWheelTarget);
            break;

            case DID_SCROLLITEMS:
                if (SHORT2FROMMP (mp1) == SPBN_UPARROW ||
                    SHORT2FROMMP (mp1) == SPBN_DOWNARROW)
                    {
                    pWheelDlg1Data->prevScrollNum = pWheelDlg1Data->currScrollNum;
                    WinSendDlgItemMsg (hwndDlg, DID_SCROLLITEMS, SPBM_QUERYVALUE,
                                       (MPARAM)&(pWheelDlg1Data->currScrollNum),
                                       MPFROM2SHORT (0, SPBQ_DONOTUPDATE));
                    _clsSetScrollNum (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollNum);
                    }
                break;

            case DID_NOFUNCTION:
                pWheelDlg1Data->prevScrollMode = pWheelDlg1Data->currScrollMode;
                pWheelDlg1Data->currScrollMode = SCROLL_MODE_NONE;
                _clsSetScrollMode (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollMode);
                SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
                break;

            case DID_MSG_STD:
                pWheelDlg1Data->prevScrollMode = pWheelDlg1Data->currScrollMode;
                pWheelDlg1Data->currScrollMode = SCROLL_MODE_STD;
                _clsSetScrollMode (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollMode);
                SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
                break;

            case DID_MSG_LINE:
                pWheelDlg1Data->prevScrollMode = pWheelDlg1Data->currScrollMode;
                pWheelDlg1Data->currScrollMode = SCROLL_MODE_LINE;
                _clsSetScrollMode (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollMode);
                SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
                break;

            case DID_MSG_PAGE:
                pWheelDlg1Data->prevScrollMode = pWheelDlg1Data->currScrollMode;
                pWheelDlg1Data->currScrollMode = SCROLL_MODE_PAGE;
                _clsSetScrollMode (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollMode);
                SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
                break;

            case DID_MSG_VOLUME:
                pWheelDlg1Data->prevScrollMode = pWheelDlg1Data->currScrollMode;
                pWheelDlg1Data->currScrollMode = SCROLL_MODE_VOLUME;
                _clsSetScrollMode (somClassObject, pWheelDlg1Data->ulWheelPageType, pWheelDlg1Data->currScrollMode);
                SetButtonsWheelSettings1 (hwndDlg, somClassObject, pWheelDlg1Data);
                break;
            }
        }

    return 0;
    }

MRESULT WheelSettings2InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject)
    {
    PWHEELDLG2DATA pWheelDlg2Data;
    LONG           l;
    LONG           lWheelCount;
    CHAR           sz[8];
    BOOL           bWheel2Enabled;

    pWheelDlg2Data = (PWHEELDLG2DATA)_wpAllocMem (somObject, sizeof (*pWheelDlg2Data), NULL);

    /* Initialize dialog panel */
    memset ((PVOID)pWheelDlg2Data, 0, sizeof (*pWheelDlg2Data));
    pWheelDlg2Data->cb = sizeof (*pWheelDlg2Data);
    pWheelDlg2Data->currStartupMode =
    pWheelDlg2Data->prevStartupMode = _clsGetStartupMode (somClassObject);
    pWheelDlg2Data->somObject       = somObject;
    pWheelDlg2Data->somClassObject  = somClassObject;
    pWheelDlg2Data->currAccelDelay  =
    pWheelDlg2Data->prevAccelDelay  = _clsGetAccelDelay (somClassObject);
    pWheelDlg2Data->currAccelValue  =
    pWheelDlg2Data->prevAccelValue  = _clsGetAccelValue (somClassObject);
    pWheelDlg2Data->currWheelCount  =
    pWheelDlg2Data->prevWheelCount  = _clsGetWheelCount (somClassObject);
    WinSetWindowPtr (hwndDlg, QWL_USER, pWheelDlg2Data);

    lWheelCount = getWheelCount ();

    /* Wheel 2 activation button and Startup-Mode buttons */
    if (lWheelCount < 0)
        {
        bWheel2Enabled = TRUE;
        lWheelCount = pWheelDlg2Data->currWheelCount;
        }
    else
        {
        bWheel2Enabled = FALSE;
        }
    WinEnableControl (hwndDlg, DID_WHEEL2, bWheel2Enabled);
    SetWheelSettings2Controls (hwndDlg, lWheelCount, pWheelDlg2Data->currStartupMode);

    /* Acceleration delay slider */
    WinSendDlgItemMsg (hwndDlg,
                       DID_ACCEL_DELAY, SLM_SETSLIDERINFO,
                       MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                       MPFROMSHORT (pWheelDlg2Data->currAccelDelay / 100 - 1));

    for (l = 0; l < TICKNUMBER_DELAY; l++)
        {
        if (!(l % 5))
            WinSendDlgItemMsg (hwndDlg,
                               DID_ACCEL_DELAY, SLM_SETSCALETEXT,
                               MPFROMSHORT (l), MPFROMP (_ltoa (100*(l+1), sz, 10)));
        WinSendDlgItemMsg (hwndDlg,
                           DID_ACCEL_DELAY, SLM_SETTICKSIZE,
                           MPFROM2SHORT (l, ((l % 5) ? 4 : 7)), MPVOID);
        }

    /* Acceleration value slider */
    WinSendDlgItemMsg (hwndDlg,
                       DID_ACCEL_VALUE, SLM_SETSLIDERINFO,
                       MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                       MPFROMSHORT (ACCEL_MAX_VALUE - pWheelDlg2Data->currAccelValue));

    for (l = 0; l < TICKNUMBER_VALUE; l++)
        {
        if (l == 0)
            {
            WinLoadString (hab, hmodLng, IDS_ACCEL_VAL_OFF, 8, sz);
            WinSendDlgItemMsg (hwndDlg,
                               DID_ACCEL_VALUE, SLM_SETSCALETEXT,
                               MPFROMSHORT (l), MPFROMP (sz));
            }
        else if (l == TICKNUMBER_VALUE - 1)
            {
            WinLoadString (hab, hmodLng, IDS_ACCEL_VAL_FAST, 8, sz);
            WinSendDlgItemMsg (hwndDlg,
                               DID_ACCEL_VALUE, SLM_SETSCALETEXT,
                               MPFROMSHORT (l), MPFROMP (sz));
            }

        WinSendDlgItemMsg (hwndDlg,
                           DID_ACCEL_VALUE, SLM_SETTICKSIZE,
                           MPFROM2SHORT (l, 4), MPVOID);
        }

    return (MRESULT)TRUE;
    }

VOID WheelSettings2Destroy (HWND hwndDlg)
    {
    PWHEELDLG2DATA pWheelDlg2Data;

    pWheelDlg2Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    _wpFreeMem (pWheelDlg2Data->somObject, (PBYTE)pWheelDlg2Data);

    return;
    }

MRESULT WheelSettings2Command (HWND hwndDlg, MPARAM mp1)
    {
    PWHEELDLG2DATA pWheelDlg2Data;
    M_AMouse      *somClassObject;

    pWheelDlg2Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pWheelDlg2Data->somClassObject;

    switch (SHORT1FROMMP (mp1))
        {
        case DID_UNDO:
            pWheelDlg2Data->currStartupMode = pWheelDlg2Data->prevStartupMode;
            pWheelDlg2Data->currAccelDelay  = pWheelDlg2Data->prevAccelDelay;
            pWheelDlg2Data->currAccelValue  = pWheelDlg2Data->prevAccelValue;
            pWheelDlg2Data->currWheelCount  = pWheelDlg2Data->prevWheelCount;

            _clsSetStartupMode (somClassObject, pWheelDlg2Data->currStartupMode);
            _clsSetAccelDelay  (somClassObject, pWheelDlg2Data->currAccelDelay);
            _clsSetAccelValue  (somClassObject, pWheelDlg2Data->currAccelValue);
            _clsSetWheelCount  (somClassObject, pWheelDlg2Data->currWheelCount);

            WinCheckButton (hwndDlg,
                            pWheelDlg2Data->currStartupMode == SCROLL_DIR_VERT ? DID_SCROLL_VERT : DID_SCROLL_HORZ,
                            1);

            WinSendDlgItemMsg (hwndDlg,
                               DID_ACCEL_DELAY, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (pWheelDlg2Data->currAccelDelay / 100 - 1));

            WinSendDlgItemMsg (hwndDlg,
                               DID_ACCEL_VALUE, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (TICKNUMBER_VALUE - pWheelDlg2Data->currAccelValue));

            SetWheelSettings2Controls (hwndDlg, pWheelDlg2Data->currWheelCount, pWheelDlg2Data->currStartupMode);
            break;

        case DID_DEFAULT:
            /* preserve previous values */
            pWheelDlg2Data->prevStartupMode = pWheelDlg2Data->currStartupMode;
            pWheelDlg2Data->currStartupMode = SCROLL_DIR_VERT;
            pWheelDlg2Data->prevAccelDelay  = pWheelDlg2Data->currAccelDelay;
            pWheelDlg2Data->currAccelDelay  = ACCEL_DEF_DELAY;
            pWheelDlg2Data->prevAccelValue  = pWheelDlg2Data->currAccelValue;
            pWheelDlg2Data->currAccelValue  = ACCEL_DEF_VALUE;
            pWheelDlg2Data->prevWheelCount  = pWheelDlg2Data->currWheelCount;
            pWheelDlg2Data->currWheelCount  = DEF_VALUE_WHEELCOUNT;

            _clsSetStartupMode (somClassObject, pWheelDlg2Data->currStartupMode);
            _clsSetAccelDelay  (somClassObject, pWheelDlg2Data->currAccelDelay);
            _clsSetAccelValue  (somClassObject, pWheelDlg2Data->currAccelValue);
            _clsSetWheelCount  (somClassObject, pWheelDlg2Data->currWheelCount);

            WinCheckButton (hwndDlg, DID_SCROLL_VERT, 1);

            WinSendDlgItemMsg (hwndDlg,
                               DID_ACCEL_DELAY, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (ACCEL_DEF_DELAY / 100 - 1));

            WinSendDlgItemMsg (hwndDlg,
                               DID_ACCEL_VALUE, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (TICKNUMBER_VALUE - ACCEL_DEF_VALUE));

            SetWheelSettings2Controls (hwndDlg, pWheelDlg2Data->currWheelCount, pWheelDlg2Data->currStartupMode);
            break;
        }

    return (MRESULT)0;
    }

MRESULT WheelSettings2Control (HWND hwndDlg, MPARAM mp1)
    {
    PWHEELDLG2DATA pWheelDlg2Data;
    M_AMouse      *somClassObject;
    USHORT         usPosition;

    pWheelDlg2Data = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pWheelDlg2Data->somClassObject;

    switch (LONGFROMMP (mp1))
        {
        case MAKELONG (DID_SCROLL_VERT, BN_CLICKED):
            pWheelDlg2Data->prevStartupMode = pWheelDlg2Data->currStartupMode;
            pWheelDlg2Data->currStartupMode = SCROLL_DIR_VERT;
            _clsSetStartupMode (somClassObject, pWheelDlg2Data->currStartupMode);
            break;

        case MAKELONG (DID_SCROLL_HORZ, BN_CLICKED):
            pWheelDlg2Data->prevStartupMode = pWheelDlg2Data->currStartupMode;
            pWheelDlg2Data->currStartupMode = SCROLL_DIR_HORZ;
            _clsSetStartupMode (somClassObject, pWheelDlg2Data->currStartupMode);
            break;

        case MAKELONG (DID_ACCEL_DELAY, SLN_CHANGE):
            usPosition =
                (USHORT)WinSendDlgItemMsg (hwndDlg, DID_ACCEL_DELAY,
                                           SLM_QUERYSLIDERINFO,
                                           MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                           MPVOID);
            pWheelDlg2Data->prevAccelDelay  = pWheelDlg2Data->currAccelDelay;
            pWheelDlg2Data->currAccelDelay  = (usPosition + 1) * 100;
            _clsSetAccelDelay (somClassObject, pWheelDlg2Data->currAccelDelay);
            break;

        case MAKELONG (DID_ACCEL_VALUE, SLN_CHANGE):
            usPosition =
                (USHORT)WinSendDlgItemMsg (hwndDlg, DID_ACCEL_VALUE,
                                           SLM_QUERYSLIDERINFO,
                                           MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                           MPVOID);
            pWheelDlg2Data->prevAccelValue  = pWheelDlg2Data->currAccelValue;
            pWheelDlg2Data->currAccelValue  = TICKNUMBER_VALUE - usPosition;
            _clsSetAccelValue (somClassObject, pWheelDlg2Data->currAccelValue);
            break;

        case MAKELONG (DID_WHEEL2, BN_CLICKED):
        case MAKELONG (DID_WHEEL2, BN_DBLCLICKED):
            pWheelDlg2Data->prevWheelCount  = pWheelDlg2Data->currWheelCount;
            pWheelDlg2Data->currWheelCount  = 1 + WinQueryButtonCheckstate (hwndDlg, DID_WHEEL2);
            SetWheelSettings2Controls (hwndDlg, pWheelDlg2Data->currWheelCount, pWheelDlg2Data->currStartupMode);
            _clsSetWheelCount (somClassObject, pWheelDlg2Data->currWheelCount);
            break;
        }

    return 0;
    }

MRESULT WheelSettings3InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject)
    {
    PWHEELDLG3DATA pWheelDlg3Data;

    pWheelDlg3Data = (PWHEELDLG3DATA)_wpAllocMem (somObject, sizeof (*pWheelDlg3Data), NULL);

    /* Initialize dialog panel */
    memset ((PVOID)pWheelDlg3Data, 0, sizeof (*pWheelDlg3Data));
    pWheelDlg3Data->cb = sizeof (*pWheelDlg3Data);
    pWheelDlg3Data->somObject        = somObject;
    pWheelDlg3Data->somClassObject   = somClassObject;
    pWheelDlg3Data->currApplications = _clsGetApplications (somClassObject);
    WinSetWindowPtr (hwndDlg, QWL_USER, pWheelDlg3Data);

    FillApplicationListBox (hwndDlg, 0, pWheelDlg3Data->currApplications);
    WinEnableControl (hwndDlg, DID_W3_INSERT, ApplFreeEntries (pWheelDlg3Data->currApplications));

    return (MRESULT)TRUE;
    }

VOID WheelSettings3Destroy (HWND hwndDlg)
    {
    PWHEELDLG3DATA pWheelDlg3Data;

    pWheelDlg3Data = WinQueryWindowPtr (hwndDlg, QWL_USER);

    _clsSetApplications (pWheelDlg3Data->somClassObject, pWheelDlg3Data->currApplications);
    _wpFreeMem (pWheelDlg3Data->somObject, (PBYTE)pWheelDlg3Data);

    return;
    }

MRESULT WheelSettings3Command (HWND hwndDlg, MPARAM mp1)
    {
    PWHEELDLG3DATA pWheelDlg3Data;
    SHORT          sIndex;
    BOOL           bUp;

    pWheelDlg3Data = WinQueryWindowPtr (hwndDlg, QWL_USER);

    switch (SHORT1FROMMP (mp1))
        {
        case DID_W3_INSERT:
            {
            PINSERTAPPLDLGDATA pInsertApplDlgData;

            pInsertApplDlgData = (PINSERTAPPLDLGDATA)malloc (sizeof (*pInsertApplDlgData));
            memset ((PVOID)pInsertApplDlgData, 0, sizeof (*pInsertApplDlgData));
            pInsertApplDlgData->cb             = sizeof (*pInsertApplDlgData);
            pInsertApplDlgData->somObject      = pWheelDlg3Data->somObject;
            pInsertApplDlgData->somClassObject = pWheelDlg3Data->somClassObject;
            pInsertApplDlgData->pApplications  = pWheelDlg3Data->currApplications;

            WinDlgBox (HWND_DESKTOP,
                       hwndDlg,
                       InsertApplicationDlgProc,
                       hmodLng,
                       IDD_INSERTAPPL,
                       pInsertApplDlgData);

            sIndex = (SHORT)ApplNumOfEntries (pWheelDlg3Data->currApplications);
            FillApplicationListBox (hwndDlg, sIndex - 1, pWheelDlg3Data->currApplications);
            FillApplicationEntries (hwndDlg, pWheelDlg3Data->currApplications);
            break;
            }

        case DID_W3_DELETE:
            sIndex = (SHORT)WinSendDlgItemMsg (hwndDlg,
                                               DID_W3_DESCRIPTION,
                                               LM_QUERYSELECTION,
                                               MPFROMSHORT (LIT_FIRST),
                                               MPVOID);
            ApplDeleteEntry (pWheelDlg3Data->currApplications, (ULONG)sIndex);
            FillApplicationListBox (hwndDlg, sIndex, pWheelDlg3Data->currApplications);
            FillApplicationEntries (hwndDlg, pWheelDlg3Data->currApplications);
            break;

        case DID_W3_UP:
        case DID_W3_DOWN:
            bUp = (SHORT1FROMMP (mp1) == DID_W3_UP ? TRUE : FALSE);
            sIndex = (SHORT)WinSendDlgItemMsg (hwndDlg,
                                               DID_W3_DESCRIPTION,
                                               LM_QUERYSELECTION,
                                               MPFROMSHORT (LIT_FIRST),
                                               MPVOID);
            if (ApplMoveEntry (pWheelDlg3Data->currApplications, sIndex, bUp))
                {
                FillApplicationListBox (hwndDlg, sIndex + (bUp ? -1 : 1), pWheelDlg3Data->currApplications);
                FillApplicationEntries (hwndDlg, pWheelDlg3Data->currApplications);
                }
            break;

        case DID_UNDO:
            free (pWheelDlg3Data->currApplications);
            pWheelDlg3Data->currApplications = _clsGetApplications (pWheelDlg3Data->somClassObject);
            FillApplicationListBox (hwndDlg, 0, pWheelDlg3Data->currApplications);
            FillApplicationEntries (hwndDlg, pWheelDlg3Data->currApplications);
            break;
        }

    return (MRESULT)0;
    }

MRESULT WheelSettings3Control (HWND hwndDlg, MPARAM mp1)
    {
    PWHEELDLG3DATA pWheelDlg3Data;
    SHORT          sCount, sIndex;

    pWheelDlg3Data = WinQueryWindowPtr (hwndDlg, QWL_USER);

    switch (LONGFROMMP (mp1))
        {
        case MAKELONG (DID_W3_DESCRIPTION, LN_SELECT):
            sCount = ApplNumOfEntries (pWheelDlg3Data->currApplications);
            sIndex = (SHORT)WinSendDlgItemMsg (hwndDlg,
                                               DID_W3_DESCRIPTION,
                                               LM_QUERYSELECTION,
                                               MPFROMSHORT (LIT_FIRST),
                                               MPVOID);
            WinEnableControl (hwndDlg, DID_W3_UP,   (sIndex == 0        ? FALSE : TRUE));
            WinEnableControl (hwndDlg, DID_W3_DOWN, (sIndex+1 >= sCount ? FALSE : TRUE));

            FillApplicationEntries (hwndDlg, pWheelDlg3Data->currApplications);
            break;
        }

    return 0;
    }

MRESULT TimingSettingsInitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject)
    {
    PTIMINGDLGDATA pTimingDlgData;
    LONG           l;
    CHAR           sz[8];

    pTimingDlgData = (PTIMINGDLGDATA)_wpAllocMem (somObject, sizeof (*pTimingDlgData), NULL);

    /* Initialize dialog panel */
    memset ((PVOID)pTimingDlgData, 0, sizeof (*pTimingDlgData));
    pTimingDlgData->cb = sizeof (*pTimingDlgData);
    pTimingDlgData->somObject           = somObject;
    pTimingDlgData->somClassObject      = somClassObject;
    pTimingDlgData->currPollingRate     =
    pTimingDlgData->prevPollingRate     = _clsGetPollingRate (somClassObject);
    pTimingDlgData->currAccelLevel1     =
    pTimingDlgData->prevAccelLevel1     = _clsGetAccelLevel1 (somClassObject);
    pTimingDlgData->currAccelLevel1Mult =
    pTimingDlgData->prevAccelLevel1Mult = _clsGetAccelLvl1Mult (somClassObject);
    pTimingDlgData->currAccelLevel2     =
    pTimingDlgData->prevAccelLevel2     = _clsGetAccelLevel2 (somClassObject);
    pTimingDlgData->currAccelLevel2Mult =
    pTimingDlgData->prevAccelLevel2Mult = _clsGetAccelLvl2Mult (somClassObject);
    WinSetWindowPtr (hwndDlg, QWL_USER, pTimingDlgData);

    /* Polling rate slider */
    WinSendDlgItemMsg (hwndDlg,
                       DID_MOU_POLLRATE, SLM_SETSLIDERINFO,
                       MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                       MPFROMSHORT (pollRateValue2Index (pTimingDlgData->currPollingRate)));

    for (l = 0; l < TICKNUMBER_POLLRATE; l++)
        {
        WinSendDlgItemMsg (hwndDlg,
                           DID_MOU_POLLRATE, SLM_SETSCALETEXT,
                           MPFROMSHORT (l), MPFROMP (_ltoa (pollRateIndex2Value (l), sz, 10)));
        WinSendDlgItemMsg (hwndDlg,
                           DID_MOU_POLLRATE, SLM_SETTICKSIZE,
                           MPFROM2SHORT (l, 4), MPVOID);
        }

    WinSetDlgItemText (hwndDlg,
                       DID_MOU_POLLRATE_TXT,
                       _ltoa (pTimingDlgData->currPollingRate, sz, 10));

    /* Accelerator value slider */
    WinSendDlgItemMsg (hwndDlg,
                       DID_MOU_ACCEL_VALUE, SLM_SETSLIDERINFO,
                       MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                       MPFROMSHORT (accelMultValue2Index (pTimingDlgData->currAccelLevel1Mult)));

    for (l = 0; l < TICKNUMBER_ACCELVALUE; l++)
        {
        if (!(l%5))
            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_ACCEL_VALUE, SLM_SETSCALETEXT,
                               MPFROMSHORT (l), MPFROMP (_ltoa (l, sz, 10)));
        WinSendDlgItemMsg (hwndDlg,
                           DID_MOU_ACCEL_VALUE, SLM_SETTICKSIZE,
                           MPFROM2SHORT (l, 4), MPVOID);
        }

    /* Accelerator threshold slider */
    WinSendDlgItemMsg (hwndDlg,
                       DID_MOU_ACCEL_TH, SLM_SETSLIDERINFO,
                       MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                       MPFROMSHORT (accelThreshValue2Index (pTimingDlgData->currAccelLevel1)));

    for (l = 0; l < TICKNUMBER_ACCELTHRESH; l++)
        {
        if (!(l%5))
            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_ACCEL_TH, SLM_SETSCALETEXT,
                               MPFROMSHORT (l), MPFROMP (_ltoa (l, sz, 10)));
        WinSendDlgItemMsg (hwndDlg,
                           DID_MOU_ACCEL_TH, SLM_SETTICKSIZE,
                           MPFROM2SHORT (l, 4), MPVOID);
        }

    return (MRESULT)TRUE;
    }

VOID TimingSettingsDestroy (HWND hwndDlg)
    {
    PTIMINGDLGDATA pTimingDlgData;

    pTimingDlgData = WinQueryWindowPtr (hwndDlg, QWL_USER);
    _wpFreeMem (pTimingDlgData->somObject, (PBYTE)pTimingDlgData);

    return;
    }

MRESULT TimingSettingsCommand (HWND hwndDlg, MPARAM mp1)
    {
    PTIMINGDLGDATA pTimingDlgData;
    M_AMouse      *somClassObject;
    CHAR           sz[8];

    pTimingDlgData = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pTimingDlgData->somClassObject;

    switch (SHORT1FROMMP (mp1))
        {
        case DID_UNDO:
            pTimingDlgData->currPollingRate     = pTimingDlgData->prevPollingRate;
            pTimingDlgData->currAccelLevel1     = pTimingDlgData->prevAccelLevel1;
            pTimingDlgData->currAccelLevel1Mult = pTimingDlgData->prevAccelLevel1Mult;
            pTimingDlgData->currAccelLevel2     = pTimingDlgData->prevAccelLevel2;
            pTimingDlgData->currAccelLevel2Mult = pTimingDlgData->prevAccelLevel2Mult;

            _clsSetPollingRate   (somClassObject, pTimingDlgData->currPollingRate);
            _clsSetAccelLevel1   (somClassObject, pTimingDlgData->currAccelLevel1);
            _clsSetAccelLvl1Mult (somClassObject, pTimingDlgData->currAccelLevel1Mult);
            _clsSetAccelLevel2   (somClassObject, pTimingDlgData->currAccelLevel2);
            _clsSetAccelLvl2Mult (somClassObject, pTimingDlgData->currAccelLevel2Mult);

            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_POLLRATE, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (pollRateValue2Index (pTimingDlgData->currPollingRate)));
            WinSetDlgItemText (hwndDlg,
                               DID_MOU_POLLRATE_TXT,
                               _ltoa (pTimingDlgData->currPollingRate, sz, 10));

            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_ACCEL_VALUE, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (accelMultValue2Index (pTimingDlgData->currAccelLevel1Mult)));

            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_ACCEL_TH, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (accelMultValue2Index (pTimingDlgData->currAccelLevel1)));

            break;

        case DID_DEFAULT:
            /* preserve previous values */
            pTimingDlgData->prevPollingRate     = pTimingDlgData->currPollingRate;
            pTimingDlgData->currPollingRate     = DEF_VALUE_POLLING_RATE;
            pTimingDlgData->prevAccelLevel1     = pTimingDlgData->currAccelLevel1;
            pTimingDlgData->currAccelLevel1     = DEF_VALUE_ACCEL_LEVEL1;
            pTimingDlgData->prevAccelLevel1Mult = pTimingDlgData->currAccelLevel1Mult;
            pTimingDlgData->currAccelLevel1Mult = DEF_VALUE_ACCEL_L1MULT;
            pTimingDlgData->prevAccelLevel2     = pTimingDlgData->currAccelLevel2;
            pTimingDlgData->currAccelLevel2     = DEF_VALUE_ACCEL_LEVEL2;
            pTimingDlgData->prevAccelLevel2Mult = pTimingDlgData->currAccelLevel2Mult;
            pTimingDlgData->currAccelLevel2Mult = DEF_VALUE_ACCEL_L2MULT;

            _clsSetPollingRate   (somClassObject, pTimingDlgData->currPollingRate);
            _clsSetAccelLevel1   (somClassObject, pTimingDlgData->currAccelLevel1);
            _clsSetAccelLvl1Mult (somClassObject, pTimingDlgData->currAccelLevel1Mult);
            _clsSetAccelLevel2   (somClassObject, pTimingDlgData->currAccelLevel2);
            _clsSetAccelLvl2Mult (somClassObject, pTimingDlgData->currAccelLevel2Mult);

            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_POLLRATE, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (pollRateValue2Index (pTimingDlgData->currPollingRate)));
            WinSetDlgItemText (hwndDlg,
                               DID_MOU_POLLRATE_TXT,
                               _ltoa (pTimingDlgData->currPollingRate, sz, 10));

            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_ACCEL_VALUE, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (accelMultValue2Index (pTimingDlgData->currAccelLevel1Mult)));

            WinSendDlgItemMsg (hwndDlg,
                               DID_MOU_ACCEL_TH, SLM_SETSLIDERINFO,
                               MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                               MPFROMSHORT (accelMultValue2Index (pTimingDlgData->currAccelLevel1)));

            break;
        }

    return (MRESULT)0;
    }

MRESULT TimingSettingsControl (HWND hwndDlg, MPARAM mp1)
    {
    PTIMINGDLGDATA pTimingDlgData;
    M_AMouse      *somClassObject;
    USHORT         usPosition;
    CHAR           sz[8];

    pTimingDlgData = WinQueryWindowPtr (hwndDlg, QWL_USER);
    somClassObject = pTimingDlgData->somClassObject;

    switch (LONGFROMMP (mp1))
        {
        case MAKELONG (DID_MOU_POLLRATE, SLN_CHANGE):
            usPosition =
                (USHORT)WinSendDlgItemMsg (hwndDlg, DID_MOU_POLLRATE,
                                           SLM_QUERYSLIDERINFO,
                                           MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                           MPVOID);
            pTimingDlgData->prevPollingRate = pTimingDlgData->currPollingRate;
            pTimingDlgData->currPollingRate = pollRateIndex2Value ((ULONG)usPosition);

            WinSetDlgItemText (hwndDlg,
                               DID_MOU_POLLRATE_TXT,
                               _ltoa (pTimingDlgData->currPollingRate, sz, 10));

            _clsSetPollingRate (somClassObject, pTimingDlgData->currPollingRate);
            break;

        case MAKELONG (DID_MOU_ACCEL_VALUE, SLN_CHANGE):
            usPosition =
                (USHORT)WinSendDlgItemMsg (hwndDlg, DID_MOU_ACCEL_VALUE,
                                           SLM_QUERYSLIDERINFO,
                                           MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                           MPVOID);
            pTimingDlgData->prevAccelLevel1Mult = pTimingDlgData->currAccelLevel1Mult;
            pTimingDlgData->prevAccelLevel2Mult = pTimingDlgData->currAccelLevel2Mult;
            accelMultIndex2Value ((ULONG)usPosition, &pTimingDlgData->currAccelLevel1Mult, &pTimingDlgData->currAccelLevel2Mult);
            _clsSetAccelLvl1Mult (somClassObject, pTimingDlgData->currAccelLevel1Mult);
            _clsSetAccelLvl2Mult (somClassObject, pTimingDlgData->currAccelLevel2Mult);

            break;

        case MAKELONG (DID_MOU_ACCEL_TH, SLN_CHANGE):
            usPosition =
                (USHORT)WinSendDlgItemMsg (hwndDlg, DID_MOU_ACCEL_TH,
                                           SLM_QUERYSLIDERINFO,
                                           MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
                                           MPVOID);
            pTimingDlgData->prevAccelLevel1 = pTimingDlgData->currAccelLevel1;
            pTimingDlgData->prevAccelLevel2 = pTimingDlgData->currAccelLevel2;
            accelThreshIndex2Value ((ULONG)usPosition, &pTimingDlgData->currAccelLevel1, &pTimingDlgData->currAccelLevel2);
            _clsSetAccelLevel1 (somClassObject, pTimingDlgData->currAccelLevel1);
            _clsSetAccelLevel2 (somClassObject, pTimingDlgData->currAccelLevel2);

            break;
        }

    return 0;
    }

MRESULT DeviceInfoInitDlg (HWND hwndDlg)
    {
    HFILE     hf;                                   // File handle for the device
    ULONG     ulDataLen;                            // Size of the Data packet
    ULONG     ulAction;                             // Action taken by DosOpen
    LONG      lBtnCnt;                              // Button count
    ULONG     ulWheels;                             // wheel count
    USHORT    ausType[3];                           // Type struct for QueryPointerId
    USHORT    usVer;                                // Driver Version
    CHAR      szBuffer[35], buf[35];                // buffers for conversions
    ULONG     versionData[2];                       // buffer for OS version
    USHORT    usPortId, usWheelId;                  // string ids
    CHAR      szPortType[32] = "";                  // buffer for port type
    CHAR      szWheels[32]   = "";                  // buffer for wheel number
    CHAR      szShape[32]    = "";                  // buffer for shape
    CHAR      szType[45]     = "";                  // buffer for mouse type or subtype
    CHAR      szRcvType[CCHMAXRCVTYPESTRING] = "";  // buffer for receiver type
    CHAR      szMouseType[CCHMAXTYPESTRING]  = "";  // buffer for complete mouse type string
    CHAR      szVendor[32];                         // buffer for vendor
    EXT_INFO  strucExtInfo;                         // buffer for extended info

    WinShowWindow (WinWindowFromID (hwndDlg, DID_DEBUG), bIsDebugMode);

    if (DosOpen ("MOUSE$", &hf, &ulAction, 0,
                 FILE_NORMAL, FILE_OPEN,
                 OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                 (PEAOP2)NULL) == NO_ERROR)
        {
        /**************************************************/
        /* First group box: driver and OS version details */
        /**************************************************/
        DosQuerySysInfo (QSV_VERSION_MAJOR, QSV_VERSION_MINOR, versionData, 8);

        strcpy (szBuffer, "OS/2 ");

        if ((versionData[0] == 20) && (versionData[1] >= 30))
            {
            strcat (szBuffer, "Warp ");
            strcat (szBuffer, _itoa ((versionData[1] / 10), buf, 10));
            strcat (szBuffer, ".");
            strcat (szBuffer, _itoa ((versionData[1] % 10), buf, 10));
            }
        else
            {
            strcat (szBuffer, _itoa ((versionData[0] / 10), buf, 10));
            strcat (szBuffer, ".");
            strcat (szBuffer, _itoa ((versionData[1] ), buf, 10));
            }
        WinSetDlgItemText (hwndDlg, DID_OSVERSION, szBuffer);

        usVer = 0x55AA;

        ulDataLen = 2;
        DosDevIOCtl (hf,                    /* Device handle                  */
                     IOCTL_POINTINGDEVICE,  /* Pointing-device control        */
                     MOU_VER,               /* Gets version number of driver  */
                     NULL,                  /* No Parameter packet            */
                     0,                     /* Maximum size of parm packet    */
                     NULL,                  /* Size of param packet           */
                     &usVer,                /* Buffer for data packet         */
                     sizeof (usVer),        /* Maximum size of data packet    */
                     &ulDataLen);           /* Size of data packet            */

        if ((usVer != 0x55AA) && (usVer > 2))
            {
            strcpy (szBuffer, "nb-software ");
            _itoa ((usVer / 256), buf, 10);
            strcat (szBuffer, buf);
            strcat (szBuffer, ".");
            usVer = usVer % 256;
            if (usVer > 99)
                strcat (szBuffer, "0");
            _itoa ((usVer % 100), buf, 10);
            strcat (szBuffer, buf);
            WinSetDlgItemText (hwndDlg, DID_DRIVERVERSION, szBuffer);
            }

        /**************************************************/
        /* Second group box: mouse details                */
        /**************************************************/

        /* 1. Fill in infos following standard method */
        // 1.1 determine device type (szMouseType)
        //     determine port type (szPortType)
        //     determine number of wheels (szWheels)
        ulDataLen = 6;
        DosDevIOCtl (hf,                    /* Device handle                  */
                     IOCTL_POINTINGDEVICE,  /* Pointing-device control        */
                     MOU_QUERYPOINTERID,    /* Gets mouse type                */
                     NULL,                  /* No Parameter packet            */
                     0,                     /* Maximum size of parm packet    */
                     NULL,                  /* Size of param packet           */
                     ausType,               /* Buffer for data packet         */
                     sizeof (ausType),      /* Maximum size of data packet    */
                     &ulDataLen);           /* Size of data packet            */

        determineMouseType (hab, hmodLng, ausType[0], &usPortId, &usWheelId, szMouseType);
        WinLoadString      (hab, hmodLng, usPortId,    32, szPortType);
        WinLoadString      (hab, hmodLng, usWheelId,   32, szWheels);
        WinLoadString      (hab, hmodLng, IDS_UNKNOWN, 32, szShape);
        WinLoadString      (hab, hmodLng, IDS_UNKNOWN, 32, szVendor);

        if (usPortId == IDS_PORT_SERIAL)
            {
            szPortType[3] += ausType[1];
            }

        // 1.2 determine number of button (szBuffer)
        lBtnCnt = getButtonCount (hf);

        /* 2. if Logitech mouse overwrite information with special data */
        if (getLogiInfo (hf, &strucExtInfo))
            {
            /* Logitech mouse; get data from info structure */
            getLogiType (hab, hmod, hmodLng, &strucExtInfo,
                         32, szType,
                         CCHMAXRCVTYPESTRING, szRcvType,
                         NULL);

            /* vendor id */
            if ((strucExtInfo.usIndex & ExtVendorIdx) && (strucExtInfo.usIndex & ExtTypeIdx))
                getVendorName (strucExtInfo.usVendorId, strucExtInfo.usType,
                               szVendor, 32,
                               szRcvType, CCHMAXRCVTYPESTRING);

            /* construct strings */
            // contents of strings at this point:
            // ⁄ƒƒƒƒƒƒƒƒƒƒƒƒ¬ƒƒƒƒƒƒƒƒƒƒ¬ƒƒƒƒƒƒƒƒƒƒƒ¬ƒƒƒƒƒƒƒƒƒƒƒ¬ƒƒƒƒƒƒƒƒƒ¬ƒƒƒƒƒƒƒƒƒø
            // ≥String      ≥ PS/2-Std ≥ PS/2-Logi ≥ PS/2-Logi ≥ USB-Std ≥ USB-Logi≥
            // ≥            ≥          ≥           ≥ Cordless  ≥         ≥         ≥
            // √ƒƒƒƒƒƒƒƒƒƒƒƒ≈ƒƒƒƒƒƒƒƒƒƒ≈ƒƒƒƒƒƒƒƒƒƒƒ≈ƒƒƒƒƒƒƒƒƒƒƒ≈ƒƒƒƒƒƒƒƒƒ≈ƒƒƒƒƒƒƒƒƒ¥
            // ≥szMouseType ≥ used     ≥ used      ≥ used      ≥ used    ≥ used    ≥
            // ≥szRcvType   ≥ ./.      ≥ ./.       ≥ used      ≥ used    ≥ used    ≥
            // ≥szType      ≥ ./.      ≥ used      ≥ used      ≥ ./.     ≥ used    ≥
            // ¿ƒƒƒƒƒƒƒƒƒƒƒƒ¡ƒƒƒƒƒƒƒƒƒƒ¡ƒƒƒƒƒƒƒƒƒƒƒ¡ƒƒƒƒƒƒƒƒƒƒƒ¡ƒƒƒƒƒƒƒƒƒ¡ƒƒƒƒƒƒƒƒƒŸ
            // to be copied into szMouseType:
            // PS/2-Std:           szMouseType =  szMouseType
            // PS/2-Logi:          szMouseType =  szType [+ szRcvType]
            // PS/2-Logi Cordless: szMouseType =  szType  + szRcvType
            // USB-Std:            szMouseType = [szType] + szRcvType
            // USB-Logi:           szMouseType =  szType  + szRcvType
            if (szType[0] || szRcvType[0])
                szMouseType[0] = '\0';
            if (szType[0])
                appendString (szMouseType, szType, CCHMAXTYPESTRING);
            if (szRcvType[0])
                appendString (szMouseType, szRcvType, CCHMAXTYPESTRING);

            if (strucExtInfo.usIndex & ExtBttnIdx)
                lBtnCnt = strucExtInfo.ucButtons;
            if (strucExtInfo.usIndex & ExtWheelIdx)
                {
                for (ulWheels = 0; strucExtInfo.ucWheels; strucExtInfo.ucWheels >>= 1)
                    ulWheels += (strucExtInfo.ucWheels & 1 ? 1 : 0);
                _ltoa (ulWheels, szWheels, 10);
                }
            if (strucExtInfo.usIndex & ExtShapeIdx)
                _ltoa (strucExtInfo.ucShape, szShape, 10);
            }

        DosClose (hf);

        // lBtnCnt > 0: display number
        // lBtnCnt < 0: display 1, 2, >2
        if (lBtnCnt < -2)
            strcpy (szBuffer, ">2");
        else
            {
            if (lBtnCnt < 0)
                lBtnCnt *= -1;
            _ltoa (lBtnCnt, szBuffer, 10);
            }

        WinSetDlgItemText (hwndDlg, DID_IOPORT,     szPortType);
        WinSetDlgItemText (hwndDlg, DID_WHEEL,      szWheels);
        WinSetDlgItemText (hwndDlg, DID_DEVICETYPE, szMouseType);
        WinSetDlgItemText (hwndDlg, DID_BUTTONS,    szBuffer);
        WinSetDlgItemText (hwndDlg, DID_SHAPE,      szShape);
        WinSetDlgItemText (hwndDlg, DID_VENDOR,     szVendor);
        }

    return (MRESULT)TRUE;
    }

MRESULT DeviceInfoCommand (HWND hwndDlg, MPARAM mp1)
    {
    switch (SHORT1FROMMP (mp1))
        {
        case DID_DEBUG:
            {
            HFILE     hf;                           // File handle for the device
            ULONG     ulDataLen;                    // Size of the Data packet
            ULONG     ulAction;                     // Action taken by DosOpen
            USHORT    ausType[3];                   // Type struct for QueryPointerId
            CHAR      szBuffer[256];                 // buffer for target string
            EXT_INFO  strucExtInfo;                 // buffer for Logitech-Info

            if (DosOpen ("MOUSE$", &hf, &ulAction, 0,
                         FILE_NORMAL, FILE_OPEN,
                         OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                         (PEAOP2)NULL) == NO_ERROR)
                {
                ulDataLen = 6;
                DosDevIOCtl (hf,                    /* Device handle                  */
                             IOCTL_POINTINGDEVICE,  /* Pointing-device control        */
                             MOU_QUERYPOINTERID,    /* Gets mouse type                */
                             NULL,                  /* No Parameter packet            */
                             0,                     /* Maximum size of parm packet    */
                             NULL,                  /* Size of param packet           */
                             ausType,               /* Buffer for data packet         */
                             sizeof (ausType),      /* Maximum size of data packet    */
                             &ulDataLen);           /* Size of data packet            */

                sprintf (szBuffer, szMessage1, ausType[0], ausType[1]);

                if (getLogiInfo (hf, &strucExtInfo))
                    {
                    CHAR szType[8]     = "-";
                    CHAR szButtons[8]  = "-";
                    CHAR szWheels[8]   = "-";
                    CHAR szSubType[8]  = "-";
                    CHAR szShape[8]    = "-";
                    CHAR szDevNum[8]   = "-";
                    CHAR szChannel[8]  = "-";
                    CHAR szBatt[8]     = "-";
                    CHAR szVendorId[8] = "-";

                    if (strucExtInfo.usIndex & ExtTypeIdx)
                        _ultoa (strucExtInfo.usType, szType, 10);
                    if (strucExtInfo.usIndex & ExtBttnIdx)
                        _ultoa (strucExtInfo.ucButtons, szButtons, 10);
                    if (strucExtInfo.usIndex & ExtWheelIdx)
                        _ultoa (strucExtInfo.ucWheels, szWheels, 10);
                    if (strucExtInfo.usIndex & ExtSubTIdx)
                        _ultoa (strucExtInfo.ucSubType, szSubType, 10);
                    if (strucExtInfo.usIndex & ExtShapeIdx)
                        _ultoa (strucExtInfo.ucShape, szShape, 10);
                    if (strucExtInfo.usIndex & ExtDevNoIdx)
                        _ultoa (strucExtInfo.ucDevNum, szDevNum, 10);
                    if (strucExtInfo.usIndex & ExtChnlIdx)
                        _ultoa (strucExtInfo.ucDevNum, szChannel, 10);
                    if (strucExtInfo.usIndex & ExtBattIdx)
                        _ultoa (strucExtInfo.ucBatt, szBatt, 10);
                    if (strucExtInfo.usIndex & ExtVendorIdx)
                        _ultoa (strucExtInfo.usVendorId, szVendorId, 10);

                    sprintf (szBuffer + strlen (szBuffer), szMessage2,
                             szType, szButtons, szWheels, szSubType,
                             szShape, szDevNum, szChannel, szBatt, szVendorId);
                    }
                DosClose (hf);

                strcat (szBuffer, szClipboard);
                setClipboard (szBuffer);
                WinMessageBox (HWND_DESKTOP, hwndDlg,
                               szBuffer, szMsgTitle, 0, MB_OK | MB_MOVEABLE);
                }

            break;
            } /* end of case */
        } /* end of switch */

    return (MRESULT)0;
    }

MRESULT WlDeviceInfoInitDlg (HWND hwndDlg)
    {
    HFILE     hf;                               // File handle for the device
    HWND      hControl;                         // window handle of battery state control
    LONG      lBattStateID;                     // current battery state bitmap id
    ULONG     ulAction;                         // Action taken by DosOpen
    CHAR      szDeviceNo[8];                    // buffer for device number string
    CHAR      szChannel[32];                    // buffer for frequency string
    ULONG     ulChannels;                       // channel frequency mask
    ULONG     ulPara, ulIndex, ulStringId;

    USHORT    ausType[3];                       // Type struct for QueryPointerId
    USHORT    usPortId;                         // string ids
    ULONG     ulDataLen;

    EXT_INFO  strucExtInfo;                     // structure for extended mouse info

    hControl = WinWindowFromID (hwndDlg, DID_BATTERYSTATE);
    lBattStateID = IDB_LOGI_BATT_BASE;

    if (DosOpen ("MOUSE$", &hf, &ulAction, 0,
                 FILE_NORMAL, FILE_OPEN,
                 OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                 (PEAOP2)NULL) == NO_ERROR)
        {
        // determine port type (szPortType)
        ulDataLen = 6;
        DosDevIOCtl (hf,                    /* Device handle                  */
                     IOCTL_POINTINGDEVICE,  /* Pointing-device control        */
                     MOU_QUERYPOINTERID,    /* Gets mouse type                */
                     NULL,                  /* No Parameter packet            */
                     0,                     /* Maximum size of parm packet    */
                     NULL,                  /* Size of param packet           */
                     ausType,               /* Buffer for data packet         */
                     sizeof (ausType),      /* Maximum size of data packet    */
                     &ulDataLen);           /* Size of data packet            */
        determineMouseType (hab, hmodLng, ausType[0], &usPortId, NULL, NULL);

        // determine wireless information
        if (getLogiInfo (hf, &strucExtInfo))
            {
            if (strucExtInfo.usIndex & ExtDevNoIdx)
                {
                _ltoa (strucExtInfo.ucDevNum, szDeviceNo, 10);
                WinSetDlgItemText (hwndDlg, DID_DEVICENO, szDeviceNo);
                }

            if (strucExtInfo.usIndex & ExtChnlIdx)
                {
                ulStringId = 0;
                ulPara = (ULONG)strucExtInfo.ucChannel;
                _ltoa (ulPara, szChannel, 10);

                if (IDS_PORT_USB == usPortId)
                    {
                    if (strucExtInfo.ucChannel > 0 && strucExtInfo.ucChannel-1 <= MAX_USB_FREQ)
                        ulStringId = IDS_USB_FREQ_BASE + (ULONG)strucExtInfo.ucChannel - 1;
                    }
                 else
                    {
                    getLogiType (hab, hmod, hmodLng, &strucExtInfo, 0, NULL, 0, NULL, &ulChannels);
                    for (ulIndex = 0; ulIndex < 5; ulIndex++)
                        {
                        if (ulChannels & 1)
                            {
                            ulPara--;
                            if (ulPara == 0)
                                break;
                            }
                        ulChannels >>= 1;
                        }

                    if (ulIndex <= MAX_LOGI_FREQ)
                        ulStringId = IDS_LOGI_FREQ_BASE + ulIndex;
                    }

                if (ulStringId)
                    {
                    strcat (szChannel, " => ");
                    WinLoadString (hab, hmod, ulStringId, 16, szChannel + strlen (szChannel));
                    }
                WinSetDlgItemText (hwndDlg, DID_CHANNEL, szChannel);
                }

            if (strucExtInfo.usIndex & ExtBattIdx)
                lBattStateID += (LONG)strucExtInfo.ucBatt;
            }


        DosClose (hf);
        }

    pOldBattStateWndProc = WinSubclassWindow (hControl, BattStateWndProc);
    WinSetWindowULong (hControl, QWL_USER, lBattStateID);

    // Initialize check box
    bBatteryWarning = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_BATTERYWARNING, TRUE);
    WinCheckButton (hwndDlg, DID_BATTERYWARNING, bBatteryWarning);

    return (MRESULT)TRUE;
    }

MRESULT WlDeviceInfoControl (HWND hwndDlg, MPARAM mp1)
    {
    switch (LONGFROMMP (mp1))
        {
        case MAKELONG (DID_BATTERYWARNING, BN_CLICKED):
        case MAKELONG (DID_BATTERYWARNING, BN_DBLCLICKED):
            bBatteryWarning = (BOOL)WinQueryButtonCheckstate (hwndDlg, DID_BATTERYWARNING);
            PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_BATTERYWARNING, (bBatteryWarning ? "1" : "0"));
            bWarnedState = FALSE;
            break;
        }

    return 0;
    }

MRESULT EXPENTRY BattStateWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {

        case WM_PAINT:
            {
            HBITMAP  hbm;
            HPS      hPS;
            RECTL    rectl;
            POINTL   aptl[4];
            ULONG    ulBmpId;
            LONG     lMix;
            LONG     lRgbDialogBackColor;
            BITMAPINFOHEADER2 bmpInfo;

            hPS = WinBeginPaint (hwnd, NULLHANDLE, &rectl);
            WinQueryWindowRect (hwnd, &rectl);

            GpiCreateLogColorTable (hPS, 0, LCOLF_RGB, 0, 0, NULL);
            lMix = GpiQueryBackMix (hPS);
            GpiSetBackMix (hPS, BM_SRCTRANSPARENT);

            ulBmpId = WinQueryWindowULong (hwnd, QWL_USER);

            hbm = GpiLoadBitmap (hPS, hmodLng, ulBmpId, 0, 0);
            bmpInfo.cbFix = sizeof (BITMAPINFOHEADER2);
            GpiQueryBitmapInfoHeader (hbm, &bmpInfo);

            lRgbDialogBackColor = WinQuerySysColor (HWND_DESKTOP, SYSCLR_DIALOGBACKGROUND, 0L);
            GpiSetBackColor (hPS, 0x00CCCCCC);
            WinFillRect (hPS, &rectl, lRgbDialogBackColor);

            aptl[0].x = 0;
            aptl[0].y = 0;
            aptl[1].x = bmpInfo.cx;
            aptl[1].y = bmpInfo.cy;

            aptl[2].x = 0;
            aptl[2].y = 0;
            aptl[3].x = bmpInfo.cx;
            aptl[3].y = bmpInfo.cy;

            GpiWCBitBlt (hPS, hbm, 4, aptl, ROP_SRCCOPY, BBO_IGNORE);
            GpiDeleteBitmap (hbm);
            GpiSetBackMix (hPS, lMix);

            WinEndPaint (hPS);
            }
        }

    return pOldBattStateWndProc (hwnd, msg, mp1, mp2);
    }

/******************************************************************************
*
*   InsertApplicationDlgProc()
*
*   DESCRIPTION:  Dialog Procedure to insert application in behaviour
*                 definition
*
******************************************************************************/
MRESULT EXPENTRY InsertApplicationDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return InsertApplicationInitDlg (hwndDlg, (PINSERTAPPLDLGDATA)mp2);

        case WM_COMMAND:
            return InsertApplicationCommand (hwndDlg, mp1);

        case WM_CONTROL:
            return InsertApplicationControl (hwndDlg, mp1);

        case WM_HELP:
            return InsertApplicationHelp (hwndDlg);

        case WM_DESTROY:
            InsertApplicationDestroy (hwndDlg);
            break;

        case WM_CLOSE:
            WinPostMsg (hwndDlg, WM_QUIT, MPVOID, MPVOID);
            return 0;
        }

    return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
    } /* InsertApplicationDlgProc */

MRESULT InsertApplicationInitDlg (HWND hwndDlg, PINSERTAPPLDLGDATA pInsertApplDlgData)
    {
    WinSetWindowPtr (hwndDlg, QWL_USER, pInsertApplDlgData);

    WinSendDlgItemMsg (hwndDlg, DID_W3_DESCRIPTION, EM_SETTEXTLIMIT, MPFROMSHORT (CCHMAXAPPLSTRING-1), MPVOID);
    WinSendDlgItemMsg (hwndDlg, DID_W3_APPLICATION, EM_SETTEXTLIMIT, MPFROMSHORT (CCHMAXAPPLSTRING-1), MPVOID);
    WinSendDlgItemMsg (hwndDlg, DID_W3_CLASS,       EM_SETTEXTLIMIT, MPFROMSHORT (CCHMAXAPPLSTRING-1), MPVOID);
    WinSendDlgItemMsg (hwndDlg, DID_W3_PARENTCLASS, EM_SETTEXTLIMIT, MPFROMSHORT (CCHMAXAPPLSTRING-1), MPVOID);
    WinSendDlgItemMsg (hwndDlg, DID_W3_OPTION,      EM_SETTEXTLIMIT, MPFROMSHORT (CCHMAXAPPLSTRING-1), MPVOID);

    WinSendDlgItemMsg (hwndDlg, DID_W3_MODE,      SPBM_SETARRAY, MPFROMP (&pszMode),      MPFROMSHORT (sizeof (pszMode)/sizeof (PSZ) - 1));
    WinSendDlgItemMsg (hwndDlg, DID_W3_VREL,      SPBM_SETARRAY, MPFROMP (&pszRelation),  MPFROMSHORT (sizeof (pszRelation)/sizeof (PSZ) - 1));
    WinSendDlgItemMsg (hwndDlg, DID_W3_VOPT,      SPBM_SETARRAY, MPFROMP (&pszOptionStd), MPFROMSHORT (sizeof (pszOptionStd)/sizeof (PSZ) - 1));
    WinSendDlgItemMsg (hwndDlg, DID_W3_UPDOWN,    SPBM_SETARRAY, MPFROMP (&pszMessage),   MPFROMSHORT (sizeof (pszMessage)/sizeof (PSZ) - 1));
    WinSendDlgItemMsg (hwndDlg, DID_W3_HREL,      SPBM_SETARRAY, MPFROMP (&pszRelation),  MPFROMSHORT (sizeof (pszRelation)/sizeof (PSZ) - 1));
    WinSendDlgItemMsg (hwndDlg, DID_W3_HOPT,      SPBM_SETARRAY, MPFROMP (&pszOptionStd), MPFROMSHORT (sizeof (pszOptionStd)/sizeof (PSZ) - 1));
    WinSendDlgItemMsg (hwndDlg, DID_W3_LEFTRIGHT, SPBM_SETARRAY, MPFROMP (&pszMessage),   MPFROMSHORT (sizeof (pszMessage)/sizeof (PSZ) - 1));

    WinPostMsg (hwndDlg, WM_CONTROL, MPFROM2SHORT (DID_W3_VREL,      SPBN_ENDSPIN), MPVOID);
    WinPostMsg (hwndDlg, WM_CONTROL, MPFROM2SHORT (DID_W3_HREL,      SPBN_ENDSPIN), MPVOID);
    WinPostMsg (hwndDlg, WM_CONTROL, MPFROM2SHORT (DID_W3_UPDOWN,    SPBN_ENDSPIN), MPVOID);
    WinPostMsg (hwndDlg, WM_CONTROL, MPFROM2SHORT (DID_W3_LEFTRIGHT, SPBN_ENDSPIN), MPVOID);

    return (MRESULT)FALSE;
    }

VOID InsertApplicationDestroy (HWND hwndDlg)
    {
    PINSERTAPPLDLGDATA pInsertApplDlgData;

    pInsertApplDlgData = WinQueryWindowPtr (hwndDlg, QWL_USER);
    free (pInsertApplDlgData);

    return;
    }

MRESULT InsertApplicationCommand (HWND hwndDlg, MPARAM mp1)
    {
    PINSERTAPPLDLGDATA pInsertApplDlgData;
    CHAR               szText[CCHMAXAPPLSTRING];
    STRUCTAPPL         structNewEntry;

    pInsertApplDlgData = WinQueryWindowPtr (hwndDlg, QWL_USER);

    switch (SHORT1FROMMP (mp1))
        {
        case DID_OK:
            /* Read out all fields */
            WinQueryDlgItemText (hwndDlg, DID_W3_DESCRIPTION, CCHMAXAPPLSTRING, szText);
            strcpy (structNewEntry.szDescription, szText);
            WinQueryDlgItemText (hwndDlg, DID_W3_APPLICATION, CCHMAXAPPLSTRING, szText);
            strcpy (structNewEntry.szApplication, szText);
            WinQueryDlgItemText (hwndDlg, DID_W3_CLASS,       CCHMAXAPPLSTRING, szText);
            strcpy (structNewEntry.szClass,       szText);
            WinQueryDlgItemText (hwndDlg, DID_W3_PARENTCLASS, CCHMAXAPPLSTRING, szText);
            strcpy (structNewEntry.szParentClass, szText);
            WinQueryDlgItemText (hwndDlg, DID_W3_OPTION,      CCHMAXAPPLSTRING, szText);
            strcpy (structNewEntry.szOption,      szText);

            WinSendDlgItemMsg (hwndDlg, DID_W3_MODE, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (CCHMAXAPPLSTRING, SPBQ_UPDATEIFVALID));
            structNewEntry.strucResData.usScrollMode = usMode[ReturnSpinIndex (pszMode, szText)];

            WinSendDlgItemMsg (hwndDlg, DID_W3_VREL, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (CCHMAXAPPLSTRING, SPBQ_UPDATEIFVALID));
            structNewEntry.strucResData.usVRelation = usRelation[ReturnSpinIndex (pszRelation, szText)];

            WinSendDlgItemMsg (hwndDlg, DID_W3_VOPT, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (CCHMAXAPPLSTRING, SPBQ_UPDATEIFVALID));
            structNewEntry.strucResData.usVOpt = usOptionStd[ReturnSpinIndex (pszOptionStd, szText)];

            WinSendDlgItemMsg (hwndDlg, DID_W3_UPDOWN, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (CCHMAXAPPLSTRING, SPBQ_UPDATEIFVALID));
            structNewEntry.strucResData.usMsgUp   =
            structNewEntry.strucResData.usMsgDown = usMessage[ReturnSpinIndex (pszMessage, szText)];

            WinSendDlgItemMsg (hwndDlg, DID_W3_HREL, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (CCHMAXAPPLSTRING, SPBQ_UPDATEIFVALID));
            structNewEntry.strucResData.usHRelation = usRelation[ReturnSpinIndex (pszRelation, szText)];

            WinSendDlgItemMsg (hwndDlg, DID_W3_HOPT, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (CCHMAXAPPLSTRING, SPBQ_UPDATEIFVALID));
            structNewEntry.strucResData.usHOpt = usOptionStd[ReturnSpinIndex (pszOptionStd, szText)];

            WinSendDlgItemMsg (hwndDlg, DID_W3_LEFTRIGHT, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (CCHMAXAPPLSTRING, SPBQ_UPDATEIFVALID));
            structNewEntry.strucResData.usMsgLeft  =
            structNewEntry.strucResData.usMsgRight = usMessage[ReturnSpinIndex (pszMessage, szText)];

            /* Handle exceptions */
            if (structNewEntry.strucResData.usVRelation != REL_SPEC &&
                structNewEntry.strucResData.usHRelation != REL_SPEC)
                structNewEntry.szOption[0] = '\0';

            switch (structNewEntry.strucResData.usMsgUp)
                {
                case WM_NULL:
                case WM_VSCROLL:
                case WM_HSCROLL:
                case WM_VSCROLL1:
                case WM_HSCROLL1:
                    structNewEntry.strucResData.usVOpt = 0;
                    break;
                }

            switch (structNewEntry.strucResData.usMsgLeft)
                {
                case WM_NULL:
                case WM_VSCROLL:
                case WM_HSCROLL:
                case WM_VSCROLL1:
                case WM_HSCROLL1:
                    structNewEntry.strucResData.usHOpt = 0;
                    break;
                }

            ApplInsertNewEntry (pInsertApplDlgData->pApplications, &structNewEntry);
            WinDismissDlg (hwndDlg, TRUE);
            break;

        case DID_CANCEL:
            WinDismissDlg (hwndDlg, FALSE);
            break;
        }

    return (MRESULT)0;
    }

MRESULT InsertApplicationControl (HWND hwndDlg, MPARAM mp1)
    {
    CHAR               szText[16];
    BOOL               b;

    switch (LONGFROMMP (mp1))
        {
        case MAKELONG (DID_W3_MODE, SPBN_ENDSPIN):
            // no change in other controls
            break;

        case MAKELONG (DID_W3_VREL, SPBN_ENDSPIN):
        case MAKELONG (DID_W3_HREL, SPBN_ENDSPIN):
            WinSendDlgItemMsg (hwndDlg, DID_W3_VREL, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (32, SPBQ_UPDATEIFVALID));
            b = FALSE;
            if (usRelation[ReturnSpinIndex (pszRelation, szText)] == REL_SPEC)
                b = TRUE;
            WinSendDlgItemMsg (hwndDlg, DID_W3_HREL, SPBM_QUERYVALUE, MPFROMP (szText), MPFROM2SHORT (32, SPBQ_UPDATEIFVALID));
            if (usRelation[ReturnSpinIndex (pszRelation, szText)] == REL_SPEC)
                b = TRUE;
            WinEnableControl (hwndDlg, DID_W3_OPTION, b);
            break;

        case MAKELONG (DID_W3_VOPT, SPBN_ENDSPIN):
        case MAKELONG (DID_W3_HOPT, SPBN_ENDSPIN):
            // no change in other controls
            break;

        case MAKELONG (DID_W3_UPDOWN, SPBN_ENDSPIN):
        case MAKELONG (DID_W3_LEFTRIGHT, SPBN_ENDSPIN):
            WinSendDlgItemMsg (hwndDlg,
                               SHORT1FROMMP (mp1),
                               SPBM_QUERYVALUE,
                               MPFROMP (szText),
                               MPFROM2SHORT (16, SPBQ_UPDATEIFVALID));
            switch (usMessage[ReturnSpinIndex (pszMessage, szText)])
                {
                case WM_NULL:
                case WM_VSCROLL:
                case WM_HSCROLL:
                case WM_VSCROLL1:
                case WM_HSCROLL1:
                    b = FALSE;
                    break;

                case WM_CONTROL:
                case WM_CHAR:
                    b = TRUE;
                    break;
                }
            WinEnableControl (hwndDlg,
                              (SHORT1FROMMP (mp1) == DID_W3_UPDOWN ? DID_W3_VOPT : DID_W3_HOPT),
                              b);
            break;
        }

    return 0;
    }

#pragma info (nopar)
MRESULT InsertApplicationHelp (HWND hwndDlg)
    {
#ifdef SOM_AMouse_h
    /* Help for WPS-application */
    PINSERTAPPLDLGDATA pInsertApplDlgData;

    pInsertApplDlgData = WinQueryWindowPtr (hwndDlg, QWL_USER);

    _wpDisplayHelp (pInsertApplDlgData->somObject,
                    PANEL_INSERTAPPL,
                    szHelpFile);
#else
    /* Help for exe-application */
    if (bIsHelp)
        WinSendMsg (hwndHelp, HM_DISPLAY_HELP,
                    MPFROMSHORT (PANEL_INSERTAPPL),
                    MPFROMSHORT (HM_RESOURCEID));
#endif

    return (MRESULT)0;
    }
#pragma info (restore)
