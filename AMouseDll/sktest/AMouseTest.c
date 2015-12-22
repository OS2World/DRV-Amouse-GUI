#define  INCL_DOS
#define  INCL_DOSERRORS
#define  INCL_DOSDEVIOCTL
#define  INCL_WIN
#define  INCL_GPI
#include <os2.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dlg.h"

MRESULT EXPENTRY DialogWndProc (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);

HAB    hab;
HWND   hwndFrame;
HFILE  hFileDriver;

/***********************************
    H a u p t p r o g r a m m
 **********************************/
int main (void)
    {
    HMQ      hmq;
    QMSG     qmsg;
    SWCNTRL  switchCntrl;
    PTIB     ptib;
    PPIB     ppib;

    /* console for PM application */
    DosGetInfoBlocks (&ptib, &ppib);
    ppib->pib_ultype = 3;

    /* PM Initialisierung und Hauptschleife */
    hab = WinInitialize (0);
    hmq = WinCreateMsgQueue (hab, 0);

    hwndFrame = WinLoadDlg (HWND_DESKTOP,   /* Dialogbox laden */
                            HWND_DESKTOP,
                            (PFNWP) DialogWndProc,
                            0,
                            ID_MAIN,
                            NULL);

    switchCntrl.hwnd          = hwndFrame;
    switchCntrl.hwndIcon      = 0;
    switchCntrl.hprog         = 0L;
    switchCntrl.idProcess     = 0 ;
    switchCntrl.idSession     = 0;
    switchCntrl.uchVisibility = SWL_VISIBLE;
    switchCntrl.fbJump        = SWL_JUMPABLE;
    strcpy (switchCntrl.szSwtitle, "Shift key test");
    WinCreateSwitchEntry (hab, &switchCntrl);

    /*  Message-Schleife */
    while (WinGetMsg (hab, &qmsg, 0L, 0L, 0L))
         WinDispatchMsg (hab, &qmsg);

    /*  Programmende */
    WinDestroyWindow (hwndFrame);
    WinDestroyMsgQueue (hmq);
    WinTerminate (hab);
    return 0;
    }

VOID InitDlg (HWND hwnd)
    {
    APIRET     rc;
    ULONG      ulAction;

    rc = DosOpen ("KBD$", &hFileDriver, &ulAction, 0,
                  FILE_NORMAL, FILE_OPEN,
                  OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                  (PEAOP2)NULL);

    printf ("Return from DosOpen: %d\n", rc);
    if (rc != NO_ERROR)
        hFileDriver = NULLHANDLE;

    WinStartTimer (hab, hwnd, 1, 500);

    return;
    }

VOID Timer (HWND hwnd)
    {
    LONG lKeyState;
    LONG lPhKeyState;
    CHAR szKeyState[16];
    CHAR szPhKeyState[16];

    lKeyState   = WinGetKeyState (HWND_DESKTOP, VK_SHIFT);
    lPhKeyState = WinGetPhysKeyState (HWND_DESKTOP, 42);

    _itoa (lKeyState, szKeyState, 16);
    _itoa (lPhKeyState, szPhKeyState, 16);
    WinSetDlgItemText (hwnd, DID_VK, szKeyState);
    WinSetDlgItemText (hwnd, DID_SC, szPhKeyState);

    return;
    }

VOID CommandUnset (VOID)
    {
    BOOL b;
    BYTE KeyState[256]; /* This is a 256 byte table   */
                        /* indexed by virtual key     */
                        /* value.                     */
                        /* For any virtual key, the   */
                        /* 0x80 bit is set if the key */
                        /* is down, and zero if it is */
                        /* up.  The 0x01 bit is set   */
                        /* if the key is toggled,     */
                        /* (pressed an odd number     */
                        /* of times), otherwise it is */
                        /* zero.                      */
    WinSetKeyboardStateTable (HWND_DESKTOP,
                              KeyState,
                              FALSE);     // get a copy of the keyboard state.
    KeyState[VK_SHIFT] = 0x00;            // set the CAPSLOCK key to off state

    b = WinSetKeyboardStateTable (HWND_DESKTOP,
                                  KeyState,
                                  TRUE);  // set the keyboard state

    printf ("Return from WinSetKeyboardStateTable: %s\n", (b ? "TRUE" : "FALSE"));

    return;
    }

VOID CommandUnset2 (VOID)
    {
    APIRET     rc;
    SHIFTSTATE shiftState;
    ULONG      ulParmLen;
    ULONG      ulDataLen;

    ulDataLen = sizeof (shiftState);
    rc = DosDevIOCtl (hFileDriver,
                      IOCTL_KEYBOARD,
                      KBD_GETSHIFTSTATE,
                      NULL,
                      0,
                      NULL,
                      &shiftState,
                      sizeof (shiftState),
                      &ulDataLen);
    printf ("-------------------------\n");
    printf ("Return from GetShiftState:%d\n", rc);
    printf ("Shift state: %d\n", shiftState.fsState);
    printf ("NLS shift state: %d\n", shiftState.fNLS);

    shiftState.fsState = 0;
    shiftState.fNLS    = 0;
    ulParmLen = sizeof (shiftState);
    rc = DosDevIOCtl (hFileDriver,
                      IOCTL_KEYBOARD,
                      KBD_SETSHIFTSTATE,
                      &shiftState,
                      sizeof (shiftState),
                      &ulParmLen,
                      NULL,
                      0,
                      NULL);
    printf ("Return from SetShiftState:%d\n", rc);

    return;
    }

/***********************************************************************
    D i a l o g  -  W i n d o w   P r o c e d u r e
 ***********************************************************************/
MRESULT EXPENTRY DialogWndProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
/*----- Window Message WM_INITDLG */
        case WM_INITDLG:
            InitDlg (hwnd);
            return 0;

/*----- Window Message WM_COMMAND */
/*      WinDefDlgProc darf nicht aufgerufen werden, da diese WinDismissDlg  */
/*      aufruft. Damit wird die Dialog-Box beendet, die Message-Schleife im */
/*      Hauptprogramm l„uft jedoch endlos weiter und wartet auf WM_QUIT.    */
        case WM_COMMAND:
            {
            switch (COMMANDMSG(&msg)->cmd)
                {
                case DID_UNSET:
                    CommandUnset2 ();
                    CommandUnset ();
                    return 0;
                }
            }
            return 0;

        case WM_TIMER:
            Timer (hwnd);
            return 0;

/*----- Window Message WM_CLOSE */
        case WM_CLOSE:
            WinPostMsg (hwnd, WM_QUIT, 0L, 0L);
            return 0;
        }
    return WinDefDlgProc (hwnd, msg, mp1, mp2);
    }

