#define  INCL_DOS
#define  INCL_DOSERRORS
#define  INCL_WIN
#define  INCL_GPI
#include <os2.h>

#define INCL_MCIOS2
#define INCL_MACHDR
#include <os2me.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dlg.h"

MRESULT EXPENTRY DialogWndProc (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);

HAB  hab;
HWND hwndFrame;
HMQ  hmq;

#define FCB_MINBUTTON       0x0001
#define FCB_MAXBUTTON       0x0002
#define FCB_CLOSEBUTTON     0x0004
#define FCB_HIDEBUTTON      0x0008
#define FCB_RESTOREBUTTON   0x0010


/***********************************
    H a u p t p r o g r a m m
 **********************************/
int main (void)
    {
    QMSG     qmsg;
    SWCNTRL  switchCntrl;
    PTIB     ptib;
    PPIB     ppib;

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

    printf ("own window handle: %x\n", hwndFrame);

    switchCntrl.hwnd          = hwndFrame;
    switchCntrl.hwndIcon      = 0;
    switchCntrl.hprog         = 0L;
    switchCntrl.idProcess     = 0 ;
    switchCntrl.idSession     = 0;
    switchCntrl.uchVisibility = SWL_VISIBLE;
    switchCntrl.fbJump        = SWL_JUMPABLE;
    strcpy (switchCntrl.szSwtitle, "AMouse Test");
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

ULONG getFrameCtlFlags (HWND hwnd)
    {
    BOOL isMinButton;
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

HWND findTopParentFrame (HWND hwnd)
    {
    HWND  hwnd1, hwnd2;
    CHAR  szBuffer[32];
    HWND  hwndDesktop;
    HWND  hwndObject;
    ULONG flFlags;

    hwndDesktop = WinQueryDesktopWindow (hab, NULLHANDLE);
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

VOID sizeApplicationWindow (HWND hwndWnd, USHORT usSysCmd)
    {
    HWND   hwnd;
    ULONG  ulFCB;
    USHORT usSysCommand = 0;

    hwnd = hwndWnd;
    hwnd = findTopParentFrame (hwnd);

    if (WinIsWindow (hab, hwnd))
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

/***********************************************************************
    D i a l o g  -  W i n d o w   P r o c e d u r e
 ***********************************************************************/
MRESULT EXPENTRY DialogWndProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            return (MPARAM)TRUE;

/*----- Window Message WM_COMMAND */
/*      WinDefDlgProc darf nicht aufgerufen werden, da diese WinDismissDlg  */
/*      aufruft. Damit wird die Dialog-Box beendet, die Message-Schleife im */
/*      Hauptprogramm l„uft jedoch endlos weiter und wartet auf WM_QUIT.    */
        case WM_COMMAND:
            {
            switch (COMMANDMSG(&msg)->cmd)
                {
                CHAR    sz[256];
                HWND    hwndSpy;
                ULONG   ul;

                case DID_TEST:
                    WinQueryDlgItemText (hwnd, DID_HWND, 16, sz);
                    hwndSpy = (HWND)strtoul (sz, NULL, 0);
                    if (hwndSpy == NULLHANDLE)
                        hwndSpy = hwndFrame;

                    ul = getFrameCtlFlags (hwndSpy);

                    sz[0] = '\0';
                    if (ul & FCB_MINBUTTON)
                        strcat (sz, "MIN ");
                    if (ul & FCB_MAXBUTTON)
                        strcat (sz, "MAX ");
                    if (ul & FCB_HIDEBUTTON)
                        strcat (sz, "HIDE ");
                    if (ul & FCB_CLOSEBUTTON)
                        strcat (sz, "CLOSE ");
                    if (ul & FCB_RESTOREBUTTON)
                        strcat (sz, "RESTORE ");

                    WinSetDlgItemText (hwnd, DID_P1, sz);

                    sizeApplicationWindow (hwndSpy, SC_MINIMIZE);
                    return 0;
                }
            }
            return 0;

/*----- Window Message WM_CLOSE */
        case WM_CLOSE:
            WinPostMsg (hwnd, WM_QUIT, 0L, 0L);
            return 0;
        }
    return WinDefDlgProc (hwnd, msg, mp1, mp2);
    }

