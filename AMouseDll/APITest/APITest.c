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
#include "pmwinmou.h"

MRESULT EXPENTRY DialogWndProc (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);

HAB    hab;
HWND   hwndFrame;

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
    strcpy (switchCntrl.szSwtitle, "API Test");
    WinCreateSwitchEntry (hab, &switchCntrl);

    /*  Message-Schleife */
    while (WinGetMsg (hab, &qmsg, 0L, 0L, 0L))
        {
        if (qmsg.hwnd == hwndFrame)
            {
            if (qmsg.hwnd == WM_MOUSEWHEEL_HORZ || qmsg.hwnd == WM_MOUSEWHEEL_VERT)
                printf ("frame message arrived\n");
            }
        WinDispatchMsg (hab, &qmsg);
        }

    /*  Programmende */
    WinDestroyWindow (hwndFrame);
    WinDestroyMsgQueue (hmq);
    WinTerminate (hab);
    return 0;
    }

VOID InitDlg (HWND hwnd)
    {
    BOOL  bRC;
    ULONG i;
    CHAR  sz[32];

    /* Register for wheel messages being sent to focus window */
    bRC = WinRegisterForWheelMsg (hwnd, AW_NONE);
    printf ("1st registration: %d\n", bRC);

    /* Register for wheel messages being sent to the owner frame window of the listbox */
    bRC = WinRegisterForWheelMsg (WinWindowFromID (hwnd, DID_LIST), AW_OWNERFRAME);
    printf ("2nd registration: %d\n", bRC);

    /* Fill listbox with sample entries */
    for (i = 0; i < 64; i++)
        {
        sprintf (sz, "This is line %d", i);
        WinSendDlgItemMsg (hwnd, DID_LIST, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (sz));
        }

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
                case DID_VOL:
                    WinSetMasterVolume ((SHORT)5);
                    return 0;

                case DID_OK:
                    WinPostMsg (hwnd, WM_CLOSE, 0L, 0L);
                    return 0;
                }
            }
            return 0;

        case WM_MOUSEWHEEL_HORZ:
            printf ("horz: fwKey: %x; turns: %d, x=%d, y=%d\n", SHORT1FROMMP (mp1),
                                                                SHORT2FROMMP (mp1),
                                                                SHORT1FROMMP (mp2),
                                                                SHORT2FROMMP (mp2));
            DosBeep (1000, 100);
            return 0;

        case WM_MOUSEWHEEL_VERT:
            printf ("vert: fwKey: %x; turns: %d, x=%d, y=%d\n", SHORT1FROMMP (mp1),
                                                                SHORT2FROMMP (mp1),
                                                                SHORT1FROMMP (mp2),
                                                                SHORT2FROMMP (mp2));
            DosBeep (4000, 100);
            return 0;

/*----- Window Message WM_CLOSE */
        case WM_CLOSE:
            WinPostMsg (hwnd, WM_QUIT, 0L, 0L);
            return 0;
        }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
    }

