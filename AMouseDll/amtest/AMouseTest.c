#define  INCL_DOS
#define  INCL_DOSERRORS
#define  INCL_DOSDEVIOCTL
#define  INCL_WIN
#define  INCL_GPI
#include <os2.h>

#define  INCL_MCIOS2
#include <os2me.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dlg.h"

void ManualCall (void);
//void _System toggleScrollDir (void);

MRESULT EXPENTRY DialogWndProc (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);

HAB  hab;
HWND hwndFrame;

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
    BOOL       bRC;
    APIRET     rc;
    ULONG      ulFCF;
    PID        pid;
    TID        tid;
    WNDPARAMS  wnd;
    PWNDPARAMS pWndParams;
    FRAMECDATA fd;
    ERRORID    errid;
    CHAR szBuffer[32];

    WinQueryClassName (hwnd, 32, szBuffer);
/*
    bRC = WinQueryWindowProcess (hwnd, &pid, &tid);
    if (!bRC)
        return 0;

    rc = DosAllocSharedMem ((PPVOID)&pWndParams,
                            NULL,
                            sizeof (WNDPARAMS) + sizeof (FRAMECDATA),
                            PAG_COMMIT | OBJ_GIVEABLE | PAG_READ | PAG_WRITE);

    if (rc != NO_ERROR)
        return 0;

    ulFCF = 0;
    rc = DosGiveSharedMem (pWndParams, pid, PAG_READ | PAG_WRITE);
    if (rc == NO_ERROR) */
        {
        CHAR txt[256];
        CHAR pp[1000];
        pWndParams = &wnd;
//        PFRAMECDATA pf = (PFRAMECDATA)(pWndParams + 1);
//        memset (pWndParams, '\0', sizeof (WNDPARAMS) + sizeof (FRAMECDATA));
        pWndParams->fsStatus  = WPM_CTLDATA | WPM_TEXT | WPM_PRESPARAMS;
        pWndParams->pCtlData  = &fd; //pWndParams + 1;
        pWndParams->cchText   = 256;
        pWndParams->pszText   = txt;
        pWndParams->cbPresParams = 1000;
        pWndParams->pPresParams = pp;
        pWndParams->cbCtlData = sizeof (FRAMECDATA);
        ((PFRAMECDATA)pWndParams->pCtlData)->cb = sizeof (FRAMECDATA);
        bRC = (BOOL)WinSendMsg (hwnd, WM_QUERYWINDOWPARAMS, MPFROMP (pWndParams), MPVOID);
        errid = WinGetLastError (hab);

        if (bRC)
            {
            DosBeep (1000, 100);
            if (pWndParams->pCtlData)
                {
                DosBeep (2000,100);
                ulFCF = ((PFRAMECDATA)(pWndParams->pCtlData))->flCreateFlags;
                }
            }
        else
            DosBeep (200,100);
        }

    DosFreeMem (pWndParams);
    return ulFCF;
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
            ManualCall ();
            return 0;

/*----- Window Message WM_COMMAND */
/*      WinDefDlgProc darf nicht aufgerufen werden, da diese WinDismissDlg  */
/*      aufruft. Damit wird die Dialog-Box beendet, die Message-Schleife im */
/*      Hauptprogramm l„uft jedoch endlos weiter und wartet auf WM_QUIT.    */
        case WM_COMMAND:
            {
            CHAR    sz[16];
            MRESULT rcSpy;
            HWND    hwndSpy;
            ULONG   msgSpy;
            MPARAM  mp1Spy, mp2Spy;

            switch (COMMANDMSG(&msg)->cmd)
                {
                case DID_TOGGLE:
                    {
                    ULONG                 rc;
                    ULONG                 ulMasterVolume;
                    USHORT                usDeviceID;
                    MCI_AMP_OPEN_PARMS    ampOpenParms;
                    MCI_MASTERAUDIO_PARMS recMasterAudio;

                    memset (&ampOpenParms, '\0', sizeof (MCI_AMP_OPEN_PARMS));
                    ampOpenParms.usDeviceID    = (USHORT)0;
                    ampOpenParms.pszDeviceType = (PSZ)MCI_DEVTYPE_AUDIO_AMPMIX;
                    rc = mciSendCommand (0,
                                         MCI_OPEN,
                                         MCI_WAIT | MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE,
                                         (PVOID)&ampOpenParms,
                                         0);

                    if (ULONG_LOWD (rc) != MCIERR_SUCCESS)
                        return 0;

                    usDeviceID = ampOpenParms.usDeviceID;

                    /* get current master volume */
                    rc = mciSendCommand (usDeviceID,
                                         MCI_MASTERAUDIO,
                                         MCI_WAIT | MCI_QUERYCURRENTSETTING | MCI_MASTERVOL,
                                         (PVOID)&recMasterAudio,
                                         0);
                    if (ULONG_LOWD (rc) != MCIERR_SUCCESS)
                        return 0;

                    ulMasterVolume = recMasterAudio.ulReturn;
                    ulMasterVolume--;
                    recMasterAudio.ulMasterVolume = ulMasterVolume;

                    rc = mciSendCommand (usDeviceID,
                                         MCI_MASTERAUDIO,
                                         MCI_WAIT | MCI_MASTERVOL,
                                         (PVOID)&recMasterAudio,
                                         0);

                    memset (&recMasterAudio, '\0', sizeof (MCI_MASTERAUDIO_PARMS));

                    mciSendCommand (0,
                                    MCI_MASTERAUDIO,
                                    MCI_WAIT | MCI_MASTERVOL | MCI_SAVESETTING,
                                    (PVOID)&recMasterAudio,
                                    0);

                    _itoa ((int)ulMasterVolume, sz, 10);
                    WinSetDlgItemText (hwnd, DID_RC, sz);
                    }
                    return 0;

                case DID_SEND:
                    WinQueryDlgItemText (hwnd, DID_HWND, 16, sz);
                    hwndSpy = (HWND)strtoul (sz, NULL, 0);
                    WinQueryDlgItemText (hwnd, DID_WM, 16, sz);
                    msgSpy = (ULONG)strtol (sz, NULL, 0);
                    WinQueryDlgItemText (hwnd, DID_MP1, 16, sz);
                    mp1Spy = (MPARAM)strtol (sz, NULL, 0);
                    WinQueryDlgItemText (hwnd, DID_MP2, 16, sz);
                    mp2Spy = (MPARAM)strtol (sz, NULL, 0);
                    rcSpy = (MRESULT)WinPostMsg (hwndSpy, msgSpy, mp1Spy, mp2Spy);
                    printf ("post %.4x to %.8x (%.8x; %.8x)\n", msgSpy, hwndSpy, mp1Spy, mp2Spy);
                    _itoa ((int)rcSpy, sz, 16);
                    WinSetDlgItemText (hwnd, DID_RC, sz);

                    msgSpy = getFrameCtlFlags (hwnd); //Spy);

                    return 0;
                }
            }
            return 0;

        case WM_CHAR:
//            if (!(SHORT1FROMMP (mp1) & KC_CTRL))
                printf ("key arrived mp1=%4.x|%2.x|%2.x mp2=%4.x|%4.x\n",
                        SHORT1FROMMP (mp1), CHAR3FROMMP (mp1), CHAR4FROMMP (mp1),
                        SHORT1FROMMP (mp2), SHORT2FROMMP (mp2));
            break;

        case WM_HELP:
            WinAlarm (HWND_DESKTOP, WA_NOTE);
            return 0;

/*----- Window Message WM_CLOSE */
        case WM_CLOSE:
            WinPostMsg (hwnd, WM_QUIT, 0L, 0L);
            return 0;
        }
    return WinDefDlgProc (hwnd, msg, mp1, mp2);
    }

