/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: COMMON
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   gemeinsame Funktionen fÅr AMouse
 *
 * FUNKTIONEN:
 * -----------
 *
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define INCL_DOSPROCESS
#define INCL_DOSMODULEMGR
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSRESOURCES
#define INCL_DOSERRORS
#define INCL_WINACCELERATORS
#define INCL_WINLISTBOXES
#define INCL_WINDIALOGS
#define INCL_WINCLIPBOARD
#define INCL_WININPUT
#include <os2.h>

#include <string.h>
#include <stdlib.h>

#pragma info(noeff)

#include "AMouseGlobal.h"
#include "AMouse.h"
#include "AMouseData.h"
#include "res.h"
#include "dlg.h"
#include "common.h"
#include "commonDlg.h"

#define CCHMAXDESCRIPTION   32          // buffer length for key description
#define CCHMAXEFTEXT        64          // buffer length for key description including IDR_KEY-Text

#pragma pack (1)
typedef struct
    {
    USHORT  usPort;
    USHORT  usWheel;
    USHORT  usAmbiguous;
    CHAR    szTypeString[1];
    } MOURESDATA, *PMOURESDATA;
#pragma pack ()

static ULONG ulPollingValues[] = {40, 60, 80, 100, 200};

/* Default settings for buttons with and without shift keys */
static UCHAR ucKeyDefault[CULNUMBUTTONS]  =
    {
    IDR_DEFAULT_KEY3, IDR_DEFAULT_KEY4, IDR_DEFAULT_KEY5, IDR_DEFAULT_KEY6,
    IDR_DEFAULT_KEY7, IDR_DEFAULT_KEY8, IDR_DEFAULT_KEY9, IDR_DEFAULT_KEY10
    };
static UCHAR ucKeyCDefault[CULNUMBUTTONS] =
    {
    IDR_DEFAULT_KEYC3, IDR_DEFAULT_KEYC4, IDR_DEFAULT_KEYC5, IDR_DEFAULT_KEYC6,
    IDR_DEFAULT_KEYC7, IDR_DEFAULT_KEYC8, IDR_DEFAULT_KEYC9, IDR_DEFAULT_KEYC10
    };
static UCHAR ucKeyADefault[CULNUMBUTTONS] =
    {
    IDR_DEFAULT_KEYA3, IDR_DEFAULT_KEYA4, IDR_DEFAULT_KEYA5, IDR_DEFAULT_KEYA6,
    IDR_DEFAULT_KEYA7, IDR_DEFAULT_KEYA8, IDR_DEFAULT_KEYA9, IDR_DEFAULT_KEYA10
    };

/*******************************************************************\
    setDefaultKeySettings: fills a structure of CHARs with the
                           default settings for mouse buttons
    input:  ulKeyPageType: page type (NONE, CTRL or ALT)
            pucarMode:     pointer to array of size CULNUMBUTTONS
    output: pucarMode:     array set to default values
\*******************************************************************/
VOID setDefaultKeySettings (ULONG ulKeyPageType, PCHAR pucarMode)
    {
    PCHAR pSource;

    switch (ulKeyPageType)
        {
        case BTNPAGE_NONE:
            pSource = ucKeyDefault;
            break;

        case BTNPAGE_CTRL:
            pSource = ucKeyCDefault;
            break;

        case BTNPAGE_ALT:
            pSource = ucKeyADefault;
            break;

        default:
            pSource = NULL;
        }

    if (pSource)
        memcpy ((PVOID)pucarMode, (PVOID)pSource, CULNUMBUTTONS*sizeof (UCHAR));

    return;
    }

/*******************************************************************\
    getDefaultKeySetting: returns the default behaviour of a
                          specific mouse button
    input:  ulKeyPageType: page type (NONE, CTRL or ALT)
            ulKeyNum:      mouse button number
    return: IDR_* value for default behaviour of specified button
\*******************************************************************/
ULONG getDefaultKeySetting (ULONG ulKeyPageType, ULONG ulKeyNum)
    {
    PCHAR pSource;

    switch (ulKeyPageType)
        {
        case BTNPAGE_NONE:
            pSource = ucKeyDefault;
            break;

        case BTNPAGE_CTRL:
            pSource = ucKeyCDefault;
            break;

        case BTNPAGE_ALT:
            pSource = ucKeyADefault;
            break;

        default:
            pSource = NULL;
        }

    if (pSource)
        return pSource[ulKeyNum-CIDBUTTONMIN];
    else
        return IDR_NONE;
    }

VOID appendString (PSZ pszDest, PSZ pszSource, ULONG ulc)
    {
    if (pszDest[0])
        {
        if (ulc > strlen (pszDest) + 3 + strlen (pszSource))
            {
            strcat (pszDest, " +\n");
            strcat (pszDest, pszSource);
            }
        }
     else
        {
        if (ulc > strlen (pszSource))
            {
            strcat (pszDest, pszSource);
            }
        }

    return;
    }

/*******************************************************************\
    determineMouseType: determine data of specific mouse
    input:  hab:          anchor block handle
            hModule:      module handle of resource data
            usMouseType:  mouse type
    output: pusPortId:    pointer to port string id
            pusWheelId:   pointer to wheel string id
            pszMouseType: Mouse type string
\*******************************************************************/
VOID determineMouseType (HAB hab, HMODULE hModule, USHORT usMouseType, PUSHORT pusPortId, PUSHORT pusWheelId, PSZ pszMouseType)
    {
    ULONG       ulcResource;
    USHORT      usc;
    PVOID       pResource;
    PMOURESDATA p;

    DosQueryResourceSize (hModule, RT_RCDATA, IDRC_MOUSETYPE, &ulcResource);
    DosGetResource (hModule, RT_RCDATA, IDRC_MOUSETYPE, (PPVOID)&pResource);

    for (p = (PMOURESDATA)pResource, usc = 0; p - (PMOURESDATA)pResource >= ulcResource || usc < usMouseType; usc++)
        {
        p = (PMOURESDATA)((PCHAR)p + sizeof (MOURESDATA) - sizeof (CHAR));
        p = (PMOURESDATA)((PCHAR)p + strlen ((PCHAR)p) + 1);
        }

    if (usc == usMouseType)
        {
        if (pusPortId)
            switch (p->usPort)
                {
                case PORT_SERIAL:
                    *pusPortId = IDS_PORT_SERIAL;
                    break;

                case PORT_PS2:
                    *pusPortId = IDS_PORT_PS2;
                    break;

                case PORT_USB:
                    *pusPortId = IDS_PORT_USB;
                    break;

                default:
                    *pusPortId = IDS_PORT_UNKNOWN;
                }

        if (pusWheelId)
            switch (p->usWheel)
                {
                case WHEEL_1:
                    *pusWheelId = IDS_WHEEL_1;
                    break;

                case WHEEL_2:
                    *pusWheelId = IDS_WHEEL_2;
                    break;

                default:
                    *pusWheelId = IDS_WHEEL_0;
                }

        if (pszMouseType)
            {
            strcpy (pszMouseType, p->szTypeString);
            if (p->usAmbiguous == TYPE_AMBIG)
                {
                usc = strlen (pszMouseType) + 1;
                if (usc < CCHMAXTYPESTRING)
                    WinLoadString (hab,
                                   hModule,
                                   IDS_TYPE_AMBIGUOUS,
                                   CCHMAXTYPESTRING - usc,
                                   pszMouseType + usc - 1);
                }
            }
        }

    DosFreeResource (pResource);
    return;
    }

/*******************************************************************\
    checkForWheelMouse: checks, if present mouse owns a wheel
\*******************************************************************/
BOOL checkForWheelMouse (HMODULE hModule)
    {
    HFILE   hf;                         // File handle for the device
    ULONG   ulDataLen;                  // Size of the Data packet
    ULONG   ulAction;                   // Action taken by DosOpen
    USHORT  ausType[3];                 // Type struct for QueryPointerId
    USHORT  usWheelId;                  // string id

    DosOpen ("MOUSE$", &hf, &ulAction, 0,
             FILE_NORMAL, FILE_OPEN,
             OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
             (PEAOP2)NULL);

    ulDataLen  = 6;
    ausType[0] = 0;
    DosDevIOCtl (hf,                    // Device handle
                 IOCTL_POINTINGDEVICE,  // Pointing-device control
                 MOU_QUERYPOINTERID,    // Gets type of pointer
                 NULL,                  // No Parameter packet
                 0,                     // Maximum size of parm packet
                 NULL,                  // Size of param packet
                 ausType,               // Buffer for data packet
                 sizeof (ausType),      // Maximum size of data packet
                 &ulDataLen);           // Size of data packet

    DosClose (hf);

    determineMouseType (NULLHANDLE, hModule, ausType[0], NULL, &usWheelId, NULL);
    if (usWheelId != IDS_WHEEL_0)
        return TRUE;
    else
        return FALSE;
    }

/*******************************************************************\
    calcControlId: converts the scroll mode to the button id
    input:  ulScrollMode: requested scroll mode
\*******************************************************************/
ULONG calcControlId (ULONG ulScrollMode)
    {
    switch (ulScrollMode)
        {
        case SCROLL_MODE_NONE:
            return DID_NOFUNCTION;
        case SCROLL_MODE_STD:
            return DID_MSG_STD;
        case SCROLL_MODE_LINE:
            return DID_MSG_LINE;
        case SCROLL_MODE_PAGE:
            return DID_MSG_PAGE;
        case SCROLL_MODE_VOLUME:
            return DID_MSG_VOLUME;
        }

    return DID_NOFUNCTION;
    }

VOID findResourceString (HMODULE hModule, USHORT usID, PCHAR pszText, ULONG ulcText)
    {
    PVOID   pResource;
    PCHAR   pc;
    ULONG   ulcResource;

    DosQueryResourceSize (hModule, RT_RCDATA, IDRC_BUTTONSETTINGS, &ulcResource);
    DosGetResource       (hModule, RT_RCDATA, IDRC_BUTTONSETTINGS, (PPVOID)&pResource);

    *pszText = '\0';
    pc       = pResource;
    while (*((PSHORT)pc) != IDR_END)
        {
        if (*((PSHORT)pc) == usID)
            {
            strncpy (pszText, pc+2, ulcText);
            pszText[ulcText-1] = '\0';
            break;
            }

        // contents of pResource:
        //   <USHORT><zero terminated STRING>
        pc += 2;
        pc += strlen (pc) + 1;
        }

    DosFreeResource (pResource);
    return;
    }

/*******************************************************************\
    populateComboboxes: uses the IDRC_BUTTONSETTINGS resource data
                        to populate the combo-boxes
    input:  hwndDlg:       Window-Handle
            hModule:       module handle of language module
\*******************************************************************/
VOID populateComboboxes (HWND hwndDlg, HMODULE hModule, ULONG ulPageType)
    {
    PVOID   pResource;
    PCHAR   pc;
    ULONG   ulcResource;
    ULONG   ul;
    USHORT  usBtnMode;

    DosQueryResourceSize (hModule, RT_RCDATA, IDRC_BUTTONSETTINGS, &ulcResource);
    DosGetResource       (hModule, RT_RCDATA, IDRC_BUTTONSETTINGS, (PPVOID)&pResource);

    pc = pResource;
    while ((usBtnMode = *((PSHORT)pc)) != IDR_END)
        {
        // contents of pResource:
        //   <USHORT><zero terminated STRING>
        pc += 2;

        // IDR_KEY is not allowed for ALT+button, CTRL+button
        if ((ulPageType == WHEELPAGE_NONE) ||
            (usBtnMode != IDR_KEY))
            {
            for (ul = DID_BUTTON3; ul <= DID_BUTTON10; ul++)
                WinSendDlgItemMsg (hwndDlg, ul, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (pc));
            }
        pc += strlen (pc) + 1;
        }

    DosFreeResource (pResource);
    return;
    }

/*******************************************************************\
    isValidKey: returns TRUE, if the specified key combo can be
                used on a mouse button
    input:  usFlags:      WM_CHAR flag word
            usVKCode:     WM_CHAR virtual key code
    return: TRUE:         key combination can be used
\*******************************************************************/
BOOL isValidKey (USHORT usFlags, UCHAR  ucCharCode, USHORT usVKCode)
    {
    BOOL bRC;

    // filter out lone modifier keys
    bRC =  (((usFlags & KC_VIRTUALKEY) == 0)   ||
            ((usVKCode != VK_SHIFT)         &&      // shift
             (usVKCode != VK_CTRL)          &&      // ctrl
             (usVKCode != VK_ALT)           &&      // alt
             (usVKCode != VK_TAB)))                 // and filter out the tab key too
           &&
           (((usFlags & KC_VIRTUALKEY) != 0) ||     // a non-virtual key without keycode
            (ucCharCode != 0));                     // is invalid

    return bRC;
    }

/*******************************************************************\
    describeKey: stores a description of a certain key into pszBuf,
                 using resource strings.
    input:  pszBuf:       pointer to result buffer
            ulcBuf:       length of buffer
            usFlags:      WM_CHAR flag word
            ucCharCode:   WM_CHAR character code (lower byte)
            usVKCode:     WM_CHAR virtual key code
    output: pszBuf:       result string
    return: TRUE:         conversion successful
\*******************************************************************/
BOOL describeKey (PSZ pszBuf, ULONG ulcBuf, USHORT usFlags, UCHAR  ucCharCode, USHORT usVKCode)
    {
    BOOL  bRC  = TRUE;
    ULONG ulID = 0;
    LONG  lLength;

    *pszBuf = '\0';
    if (usFlags & KC_CTRL)
        {
        lLength = WinLoadString (hab, hmodLng, IDS_KEY_CTRL, ulcBuf, pszBuf);
        pszBuf += lLength;
        ulcBuf -= lLength;
        }
    if (usFlags & KC_SHIFT)
        {
        lLength = WinLoadString (hab, hmodLng, IDS_KEY_SHIFT, ulcBuf, pszBuf);
        pszBuf += lLength;
        ulcBuf -= lLength;
        }

    if (usFlags & KC_ALT)
        {
        lLength = WinLoadString (hab, hmodLng, IDS_KEY_ALT, ulcBuf, pszBuf);
        pszBuf += lLength;
        ulcBuf -= lLength;
        }

    if (usFlags & KC_VIRTUALKEY)
        {
        switch (usVKCode)
            {
            case VK_BACKSPACE: ulID = IDS_KEY_BACKSPACE;  break; // Backspace
            case VK_TAB:       ulID = IDS_KEY_TAB;        break; // Tab
            case VK_BACKTAB:   ulID = IDS_KEY_BACKTABTAB; break; // Backtab
            case VK_NEWLINE:   ulID = IDS_KEY_ENTER;      break; // Enter
            case VK_ESC:       ulID = IDS_KEY_ESC;        break; // Esc
            case VK_SPACE:     ulID = IDS_KEY_SPACE;      break; // Space
            case VK_PAGEUP:    ulID = IDS_KEY_PAGEUP;     break; // Pageup
            case VK_PAGEDOWN:  ulID = IDS_KEY_PAGEDOWN;   break; // Pagedown
            case VK_END:       ulID = IDS_KEY_END;        break; // End
            case VK_HOME:      ulID = IDS_KEY_HOME;       break; // Home
            case VK_LEFT:      ulID = IDS_KEY_LEFT;       break; // Left
            case VK_UP:        ulID = IDS_KEY_UP;         break; // Up
            case VK_RIGHT:     ulID = IDS_KEY_RIGHT;      break; // Right
            case VK_DOWN:      ulID = IDS_KEY_DOWN;       break; // Down
            case VK_PRINTSCRN: ulID = IDS_KEY_PRINTSCRN;  break; // Printscrn
            case VK_INSERT:    ulID = IDS_KEY_INSERT;     break; // Insert
            case VK_DELETE:    ulID = IDS_KEY_DELETE;     break; // Delete
            case VK_SCRLLOCK:  ulID = IDS_KEY_SCRLLOCK;   break; // ScrlLock
            case VK_NUMLOCK:   ulID = IDS_KEY_NUMLOCK;    break; // NumLock
            case VK_ENTER:     ulID = IDS_KEY_ENTER;      break; // Enter
            case VK_SYSRQ:     ulID = IDS_KEY_SYSRQ;      break; // SysReq
            case VK_F1:        strcat (pszBuf, "F1");     break;
            case VK_F2:        strcat (pszBuf, "F2");     break;
            case VK_F3:        strcat (pszBuf, "F3");     break;
            case VK_F4:        strcat (pszBuf, "F4");     break;
            case VK_F5:        strcat (pszBuf, "F5");     break;
            case VK_F6:        strcat (pszBuf, "F6");     break;
            case VK_F7:        strcat (pszBuf, "F7");     break;
            case VK_F8:        strcat (pszBuf, "F8");     break;
            case VK_F9:        strcat (pszBuf, "F9");     break;
            case VK_F10:       strcat (pszBuf, "F10");    break;
            case VK_F11:       strcat (pszBuf, "F11");    break;
            case VK_F12:       strcat (pszBuf, "F12");    break;
            case VK_F13:       strcat (pszBuf, "F13");    break;
            case VK_F14:       strcat (pszBuf, "F14");    break;
            case VK_F15:       strcat (pszBuf, "F15");    break;
            case VK_F16:       strcat (pszBuf, "F16");    break;
            case VK_F17:       strcat (pszBuf, "F17");    break;
            case VK_F18:       strcat (pszBuf, "F18");    break;
            case VK_F19:       strcat (pszBuf, "F19");    break;
            case VK_F20:       strcat (pszBuf, "F20");    break;
            case VK_F21:       strcat (pszBuf, "F21");    break;
            case VK_F22:       strcat (pszBuf, "F22");    break;
            case VK_F23:       strcat (pszBuf, "F23");    break;
            case VK_F24:       strcat (pszBuf, "F24");    break;
            default:           bRC = FALSE;
            }
        }
    else
        {
        if (!(usFlags & KC_CHAR) && !(usFlags & (KC_SHIFT | KC_CTRL | KC_ALT)))
            {
            // no shift key set but also no KC_CHAR => must be right Alt key
            strcat (pszBuf, "AltGr+");
            }
        switch (ucCharCode)
            {
            case 0xEC00:       ulID = IDS_KEY_WINLEFT;    break; // pszWinLeft
            case 0xED00:       ulID = IDS_KEY_WINRIGHT;   break; // pszWinRight
            case 0xEE00:       ulID = IDS_KEY_WINMENU;    break; // pszWinMenu
            default:
                {
                CHAR szTemp[2];
                if (ucCharCode >= 'a' && ucCharCode <= 'z')
                    szTemp[0] = (CHAR)ucCharCode-32;
                else
                    szTemp[0] = (CHAR)ucCharCode;
                szTemp[1] = '\0';
                strcat (pszBuf, szTemp);
                }
            }
        }

    if (ulID)
        {
        lLength = WinLoadString (hab, hmodLng, ulID, ulcBuf, pszBuf);
        pszBuf += lLength;
        ulcBuf -= lLength;
        }

    return bRC;
    }

VOID insertKeyCombString (HWND hwndDlg, ULONG mp1, ULONG mp2, ULONG idEntry)
    {
    CHAR    szKeyDescription[CCHMAXDESCRIPTION];
    CHAR    szEntryText[CCHMAXEFTEXT];

    if (mp1 | mp2)
        describeKey (szKeyDescription, CCHMAXDESCRIPTION,
                     SHORT1FROMMP (mp1), CHAR1FROMMP (mp2), SHORT2FROMMP (mp2));
    else
        szKeyDescription[0] = '\0';

    findResourceString (hmodLng, IDR_KEY, szEntryText, CCHMAXEFTEXT);
    if (*szKeyDescription)
        {
        strcat (szEntryText, " (");
        strcat (szEntryText, szKeyDescription);
        strcat (szEntryText, ")");
        }
    WinSetDlgItemText (hwndDlg, idEntry, szEntryText);

    return;
    }

/*******************************************************************\
    messageThread: internal function used by asyncMessageBox
    input:  pParm: parameter structure
\*******************************************************************/
VOID APIENTRY messageThread (PMSGTHREADPARM pParm)
    {
    HAB hab;
    HMQ hmq;

    hab = WinQueryAnchorBlock (HWND_DESKTOP);
    hmq = WinCreateMsgQueue (hab, 0);

    WinMessageBox (pParm->hwndParent,
                   pParm->hwndOwner,
                   pParm->pszText,
                   pParm->pszCaption,
                   pParm->idWindow,
                   pParm->flStyle);

    WinDestroyMsgQueue (hmq);

    free (pParm);
    return;
    }

/*******************************************************************\
    asyncMessageBox: Function similar to WinMessageBox but runs in a
                     separate thread to offer the opportunity to the
                     main thread to continue processing
    input:  hwndParent: parent window handle
            hwndOwner:  requester owner window handle
            pszText:    message text
            pszCaption: message box title
            idWindow:   dialog window id
            flStyle:    message box style
\*******************************************************************/
VOID asyncMessageBox (HWND hwndParent, HWND hwndOwner, PSZ pszText,
                      PSZ pszCaption, ULONG idWindow, ULONG flStyle)
    {
    TID tid;
    PMSGTHREADPARM p;

    p = (PMSGTHREADPARM)malloc (sizeof (MSGTHREADPARM));
    p->hwndParent = hwndParent;
    p->hwndOwner  = hwndOwner;
    p->pszText    = pszText;
    p->pszCaption = pszCaption;
    p->idWindow   = idWindow;
    p->flStyle    = flStyle;

    DosCreateThread (&tid, (PFNTHREAD)messageThread, (ULONG)p, 0, 0x8000);

    return;
    }

/*******************************************************************\
    isLogitech: checks if mouse uses Logitech protocol for
                communication
    input:  hf:        file handle of mouse driver
            pExtInfo: pointer to empty structure to be filled in
    output: pExtInfo: pointer to structure filled, if extended
                       information available
    return: TRUE:  Logitech mouse
            FALSE: other
\*******************************************************************/
BOOL getLogiInfo (HFILE hf, PEXT_INFO pExtInfo)
    {
    USHORT  usInfoType;
    ULONG   ulParm;
    ULONG   ulData;
    APIRET  rc;

    usInfoType = TYPE_EXTENDED;
    ulParm     = sizeof (usInfoType);
    ulData     = sizeof (*pExtInfo);

    rc = DosDevIOCtl (hf,                    /* Device handle                  */
                      IOCTL_POINTINGDEVICE,  /* Pointing-device control        */
                      MOU_QUERYMOUDEVDATA,   /* Gets extended info from driver */
                      &usInfoType,           /* Parameter packet               */
                      ulParm,                /* Maximum size of parm packet    */
                      &ulParm,               /* Size of param packet           */
                      pExtInfo,              /* Buffer for data packet         */
                      ulData,                /* Maximum size of data packet    */
                      &ulData);              /* Size of data packet            */

    if (rc == NO_ERROR && pExtInfo->usIndex)
        return TRUE;
    else
        return FALSE;
    }

VOID getLogiType (HAB hab, HMODULE hModule, HMODULE hModLang, PEXT_INFO pExtInfo,
                  ULONG ulcTypeString, PCHAR pTypeString,
                  ULONG ulcRcvString,  PCHAR pRcvString,
                  PULONG pulChannels)
    {
    ULONG ulcResource;
    PVOID pResource;
    PCHAR pc;

    if (pExtInfo->usIndex & ExtSubTIdx)
        {
        /* SubType available => compose type + receiver string */
        /* if SubType is unknown, leave pTypeString as is */
        if (MAX_EXT_SUBT >= pExtInfo->ucSubType)
            {
            if (ulcTypeString && pTypeString)
                {
                pTypeString[0] = '\0';
                if (pExtInfo->ucSubType)
                    WinLoadString (hab, hModule, IDS_LOGI_SUBT_BASE + pExtInfo->ucSubType, ulcTypeString, pTypeString);
                if (pTypeString[0] == '\0')
                    WinLoadString (hab, hModLang, IDS_UNKNOWN_DEVICE, ulcTypeString, pTypeString);
                }

            if (pExtInfo->usIndex & ExtTypeIdx)
                {
                DosQueryResourceSize (hModule, RT_RCDATA, IDRC_LOGI_RCV, &ulcResource);
                DosGetResource       (hModule, RT_RCDATA, IDRC_LOGI_RCV, (PPVOID)&pResource);
                pc = pResource;

                while (*(PUSHORT)pc != 0)
                    {
                    if (*(PUSHORT)pc == pExtInfo->usType)
                        break;
                    pc += 2 * sizeof (USHORT);
                    while (*(pc++) != '\0') {}
                    }

                if (pulChannels)
                    *pulChannels = (ULONG)*(pc + sizeof (USHORT));

                if (pRcvString)
                    {
                    if (*pc == 0)
                        WinLoadString (hab, hModule, IDS_UNKNOWN_RECEIVER, ulcRcvString, pRcvString);
                    else
                        {
                        pc += 2 * sizeof (USHORT);
                        strncpy (pRcvString, pc, ulcRcvString);
                        pRcvString[ulcRcvString-1] = '\0';
                        }
                    }

                DosFreeResource (pResource);
                }
            }
        }
    else if (pExtInfo->usIndex & ExtTypeIdx)
        {
        /* SubType not available => return type string */
        /* if Type is unknown, leave pTypeString as is */
        DosQueryResourceSize (hModule, RT_RCDATA, IDRC_LOGI_TYPE, &ulcResource);
        DosGetResource       (hModule, RT_RCDATA, IDRC_LOGI_TYPE, (PPVOID)&pResource);
        pc = pResource;

        while (*(PUSHORT)pc != 0)
            {
            if (*(PUSHORT)pc == pExtInfo->usType)
                break;
            pc += sizeof (USHORT);
            while (*(pc++) != '\0') {}
            }

        if (ulcTypeString && pTypeString)
            {
            if (*pc != 0)
                strncpy (pTypeString, pc + sizeof (USHORT), ulcTypeString);
            pTypeString[ulcTypeString-1] = '\0';
            }

        if (pulChannels)
            *pulChannels = 0;

        DosFreeResource (pResource);
        }

    return;
    }

/*******************************************************************\
    getButtonCount: determines the number of buttons on the mouse.
                    First it tries to use the extended function. If
                    successful (> -1), it returns a positive number.
                    Second, if first step was not successful, it uses
                    the standard OS/2 method and returns the result
                    as a negative number.
    input:  hf: file handle of mouse driver
    return: >0: real number of buttons determined by driver
            <0: standard return value of mouse driver (1...3)
\*******************************************************************/
LONG getButtonCount (HFILE hf)
    {
    USHORT  usBtnCnt;                   // Button Count
    ULONG   ulDataLen;                  // Size of the Data packet

    // First test: try extended function to determine if driver is able to detect number of buttons
    ulDataLen = 2;
    usBtnCnt  = 0x55AA;
    DosDevIOCtl (hf,                    // Device handle
                 IOCTL_POINTINGDEVICE,  // Pointing-device control
                 MOU_GETBUTTONCOUNT,    // Gets number of mouse buttons
                 NULL,                  // No Parameter packet
                 0,                     // Maximum size of parm packet
                 NULL,                  // Size of param packet
                 &usBtnCnt,             // Buffer for data packet
                 sizeof (usBtnCnt),     // Maximum size of data packet
                 &ulDataLen);           // Size of data packet

    if ((SHORT)usBtnCnt > 0)
        return (LONG)usBtnCnt;

    // Second test: use standard OS/2 method to determine number of buttons.
    ulDataLen = 2;
    usBtnCnt  = 0;
    DosDevIOCtl (hf,                    // Device handle
                 IOCTL_POINTINGDEVICE,  // Pointing-device control
                 MOU_GETBUTTONCOUNT,    // Gets number of mouse buttons
                 NULL,                  // No Parameter packet
                 0,                     // Maximum size of parm packet
                 NULL,                  // Size of param packet
                 &usBtnCnt,             // Buffer for data packet
                 sizeof (usBtnCnt),     // Maximum size of data packet
                 &ulDataLen);           // Size of data packet

    return -1*((LONG)usBtnCnt);
    }

/*******************************************************************\
    getWheelCount: Determines the number of wheels of the mouse.
                   Only possible for Logitech mice. If unknown
                   count: return -1.
    input:  hf : file handle of mouse driver
    return: >=0: real number of wheels determined by driver
            <0 : unknown
\*******************************************************************/
LONG getWheelCount (VOID)
    {
    HFILE     hf;                       // File handle for the device
    ULONG     ulAction;                 // Action taken by DosOpen
    LONG      lcWheel;                  // number of wheels
    EXT_INFO  strucExtInfo;            // buffer for extenden mouse info

    lcWheel = -1;

    if (DosOpen ("MOUSE$", &hf, &ulAction, 0,
                 FILE_NORMAL, FILE_OPEN,
                 OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                 (PEAOP2)NULL) == NO_ERROR)
        {
        // Logitech mouse -> return known wheel count
        if (getLogiInfo (hf, &strucExtInfo))
            lcWheel = (signed char)strucExtInfo.ucWheels;

        DosClose (hf);
        }

    // otherwise: wheel count unknown
    return lcWheel;
    }

/*******************************************************************\
    pollRateIndex2Value: converts the slider index to polling value
                         (40, 60, 80, 100, 200)
    input:  ulIndex: slider Index (0, 1, 2, 3, 4)
    return: value (40, 60, 80, 100, 200)
\*******************************************************************/
ULONG pollRateIndex2Value (ULONG ulIndex)
    {
    return ulPollingValues[ulIndex];
    }

/*******************************************************************\
    pollRateValue2Index: converts the polling value to slider index
                         (0, 1, 2, 3, 4)
    input:  ulValue: polling value (40, 60, 80, 100, 200)
    return: index (0, 1, 2, 3, 4)
\*******************************************************************/
ULONG pollRateValue2Index (ULONG ulValue)
    {
    LONG l, lMax;

    lMax = sizeof (ulPollingValues) / sizeof (ULONG);
    for (l = 0; l < lMax; l++)
        if (ulPollingValues[l] == ulValue)
            return l;

    return pollRateValue2Index (DEF_VALUE_POLLING_RATE);
    }

/*******************************************************************\
    accelMultIndex2Value: converts acceleration multiplication
                          parameters from slider index to values
                          in IOCTL-format
    input:  ulIndex:   acceleration multiplication value (index)
    output: pulValue1: acceleration multiplier 1
            pulValue2: acceleration multiplier 2
\*******************************************************************/
VOID  accelMultIndex2Value (ULONG ulIndex, PULONG pulValue1, PULONG pulValue2)
    {
    *pulValue1 = 1 * ulIndex;
    *pulValue2 = 2 * ulIndex;
    return;
    }

/*******************************************************************\
    accelMultValue2Index: converts acceleration multiplier parameter
                          from IOCTL-format to slider index
    input:  ulValue: acceleration multiplier 1
    return:          acceleration multiplier (index)
\*******************************************************************/
ULONG accelMultValue2Index (ULONG ulValue)
    {
    return ulValue;
    }

/*******************************************************************\
    accelThreshIndex2Value: converts acceleration threshold
                            parameters from slider index to values
                            in IOCTL-format
    input:  ulIndex:   acceleration threshold (index)
    output: pulValue1: acceleration threshold 1
            pulValue2: acceleration threshold 2
\*******************************************************************/
VOID  accelThreshIndex2Value (ULONG ulIndex, PULONG pulValue1, PULONG pulValue2)
    {
    *pulValue1 = 1 * ulIndex;
    *pulValue2 = 7 * ulIndex;
    return;
    }

/*******************************************************************\
    accelThreshValue2Index: converts acceleration threshold parameter
                          from IOCTL-format to slider index
    input:  ulValue: acceleration threshold 1
    return:          acceleration threshold (index)
\*******************************************************************/
ULONG accelThreshValue2Index (ULONG ulValue)
    {
    return ulValue;
    }

/*******************************************************************\
    SetClipboard: insert a text string into the clipboard
    input:  pszClipString: string to be set into clipboard
\*******************************************************************/
VOID setClipboard (PSZ pszClipString)
    {
    PSZ  pszDest;
    HAB  hab;

    if (WinOpenClipbrd (hab))
        {
        /* Allocate a shared memory object for the text data. */
        if (!DosAllocSharedMem ((PVOID)&pszDest,            // Pointer to shared memory object
                                NULL,                       // Use unnamed shared memory
                                strlen (pszClipString)+1,   // Amount of memory to allocate
                                PAG_WRITE  |                // Allow write access
                                PAG_COMMIT |                // Commit the shared memory
                                OBJ_GIVEABLE))              // Make pointer giveable
            {
            // Copy the string to the allocated memory.
            strcpy (pszDest, pszClipString);

            // Clear old data from the clipboard.
            WinEmptyClipbrd(hab);

            // Pass the pointer to the clipboard in CF_TEXT format. Notice
            // that the pointer must be a ULONG value.
            WinSetClipbrdData (hab,                         // Anchor-block handle
                               (ULONG) pszDest,             // Pointer to text data
                               CF_TEXT,                     // Data is in text format
                               CFI_POINTER);                // Passing a pointer

            // Close the clipboard.
            WinCloseClipbrd(hab);
            }
        }

    return;
    }

PSTRUCTAPPL ApplProfile2Struct (PCHAR pcApplication)
    {
    PSTRUCTAPPL p = malloc (CCHMAXAPPL * sizeof (STRUCTAPPL));
    ULONG       ulIndex;

    memset (p, '\0', CCHMAXAPPL * sizeof (STRUCTAPPL));
    for (ulIndex = 0; *pcApplication != '\0' && ulIndex < CCHMAXAPPL; ulIndex++)
        {
        strncpy (p[ulIndex].szDescription, pcApplication, CCHMAXAPPLSTRING);
        pcApplication += min (1 + strlen (pcApplication), CCHMAXAPPLSTRING);
        strncpy (p[ulIndex].szApplication, pcApplication, CCHMAXAPPLSTRING);
        pcApplication += min (1 + strlen (pcApplication), CCHMAXAPPLSTRING);
        strncpy (p[ulIndex].szClass,       pcApplication, CCHMAXAPPLSTRING);
        pcApplication += min (1 + strlen (pcApplication), CCHMAXAPPLSTRING);
        strncpy (p[ulIndex].szParentClass, pcApplication, CCHMAXAPPLSTRING);
        pcApplication += min (1 + strlen (pcApplication), CCHMAXAPPLSTRING);
        strncpy (p[ulIndex].szOption,      pcApplication, CCHMAXAPPLSTRING);
        pcApplication += min (1 + strlen (pcApplication), CCHMAXAPPLSTRING);

        p[ulIndex].strucResData = *((PRESDATA)pcApplication);
        pcApplication += sizeof (RESDATA);
        }

    return p;
    }

ULONG ApplStruct2Profile (PSTRUCTAPPL pstructAppl, PCHAR *pProfile)
    {
    PCHAR p;
    ULONG ulIndex;

    *pProfile = p = (PCHAR)malloc (CCHMAXAPPL * sizeof (STRUCTAPPL));
    memset (p, '\0', CCHMAXAPPL * sizeof (STRUCTAPPL));
    for (ulIndex = 0; pstructAppl[ulIndex].szDescription[0] != '\0' && ulIndex < CCHMAXAPPL; ulIndex++)
        {
        strcpy (p, pstructAppl[ulIndex].szDescription);
        p += strlen (p) + 1;
        strcpy (p, pstructAppl[ulIndex].szApplication);
        p += strlen (p) + 1;
        strcpy (p, pstructAppl[ulIndex].szClass);
        p += strlen (p) + 1;
        strcpy (p, pstructAppl[ulIndex].szParentClass);
        p += strlen (p) + 1;
        strcpy (p, pstructAppl[ulIndex].szOption);
        p += strlen (p) + 1;
        memcpy (p, (PCHAR)&pstructAppl[ulIndex].strucResData, sizeof (RESDATA));
        p += sizeof (RESDATA);
        }

    return p - *pProfile;
    }

ULONG ApplNumOfEntries (PSTRUCTAPPL pstructAppl)
    {
    ULONG ulIndex;

    for (ulIndex = 0; pstructAppl[ulIndex].szDescription[0] != '\0' && ulIndex < CCHMAXAPPL; ulIndex++)
        {}

    return ulIndex;
    }

BOOL ApplFreeEntries (PSTRUCTAPPL pstructAppl)
    {
    return (ApplNumOfEntries (pstructAppl) < CCHMAXAPPL) ? TRUE : FALSE;
    }

BOOL ApplInsertNewEntry (PSTRUCTAPPL pstructAppl, PSTRUCTAPPL pstructNewEntry)
    {
    ULONG ulIndex;

    ulIndex = ApplNumOfEntries (pstructAppl);
    if (ulIndex < CCHMAXAPPL)
        {
        pstructAppl[ulIndex] = *pstructNewEntry;
        return TRUE;
        }

    return FALSE;
    }

BOOL ApplMoveEntry (PSTRUCTAPPL pstructAppl, ULONG ulIndex, BOOL bUp)
    {
    STRUCTAPPL structApplTmp;

    if (bUp)
        {
        /* Move entry ulIndex up to position ulIndex-1 */
        if (ulIndex > 0)
            {
            structApplTmp            = pstructAppl[ulIndex];
            pstructAppl[ulIndex]     = pstructAppl[ulIndex - 1];
            pstructAppl[ulIndex - 1] = structApplTmp;
            return TRUE;
            }
        }
    else
        {
        if (ulIndex < ApplNumOfEntries (pstructAppl) - 1)
            {
            structApplTmp            = pstructAppl[ulIndex];
            pstructAppl[ulIndex]     = pstructAppl[ulIndex + 1];
            pstructAppl[ulIndex + 1] = structApplTmp;
            return TRUE;
            }
        }

    return FALSE;
    }

VOID ApplDeleteEntry (PSTRUCTAPPL pstructAppl, ULONG ulIndex)
    {
    ULONG ulc;
    ULONG ul;

    ulc = ApplNumOfEntries (pstructAppl);
    for (ul = ulIndex; ul < ulc; ul++)
        {
        pstructAppl[ul] = pstructAppl[ul+1];
        }
    memset (&pstructAppl[ulc-1], '\0', sizeof (STRUCTAPPL));

    return;
    }
