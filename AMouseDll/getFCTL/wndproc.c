/***************************************************************************\
 *
 * PROGRAMMNAME: WPDCF77
 * -------------
 *
 * VERSION: 5.2
 * --------
 *
 * MODULNAME: WNDPROC
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Window-Prozedur fÅr die Darstellung der Uhr
 *
 * FUNKTIONEN:
 * -----------
 *   ClkWndProc ()
 *   ClkDrawString ()
 *   DrawDigitalTime ()
 *   ClkRefresh ()
 *   ClkShowFrameControls ()
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    10-23-94  First release
 *  2.00    06-16-95  Extensions
 *  3.00    10-30-95  Client/Server Support; SOM2
 *  4.00    03-15-96  UnterstÅtzung fÅr hopf
 *  4.20    10-15-96  UnterstÅtzung fÅr hopf GPS
 *  4.40    01-31-00  Multimedia-UnterstÅtzung, Bugfixing
 *  5.10    02-10-01  Fehlerkorrektur Positionsspeicherung Iconview
 *  5.20    06-09-01  Fehlerkorrektur Audiodaten
 *
 *  Copyright (C) noller & breining software 1995...2001
 *
\******************************************************************************/

// flRcvrStatus noch nîtig???
#define INCL_DEV
#define INCL_OS2MM
#define INCL_WININPUT
#define INCL_WINFRAMEMGR
#define INCL_WINTRACKRECT
#define INCL_WINMENUS
#define INCL_WINSYS
#define INCL_WINMESSAGEMGR
#define INCL_WINSHELLDATA
#define INCL_WINWINDOWMGR
#define INCL_WINHELP
#define INCL_WINPOINTERS
#define INCL_GPICONTROL
#define INCL_GPIPRIMITIVES
#define INCL_GPILOGCOLORTABLE
#define INCL_GPIBITMAPS
#define INCL_GPITRANSFORMS
#define INCL_GPIREGIONS
#define INCL_DOSFILEMGR
#define INCL_DOSSEMAPHORES
#define INCL_DOSDATETIME
#define INCL_GPILCIDS

#include <os2.h>
#include <os2me.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cutil.h>

#include "dcfioctl.h"

#include "wpdcf77.ih"
#include "wpdcf.h"

#include "play.h"
#include "clock.h"
#include "res.h"
#include "clkdata.h"
#include "debug.h"

/*--------------------------------------------------------------*\
 *  Globale Definitionen und Variable fÅr dieses Modul          *
\*--------------------------------------------------------------*/
#define CCHMAXFONTSIZENAME      32  //

#define TESTSIZE                12  // Testgrî·e fÅr Font

#define IDX_WINDOWPTR           4   // Index des WindowPtr's (QWL_USER + 4)

const SIZEL sizl = {200, 200};      // Presentation space-Grî·e fÅr Analoguhr

const MATRIXLF vmatlfTrans =
         {
         MAKEFIXED (1, 0), MAKEFIXED (0, 0), 0L,
         MAKEFIXED (0, 0), MAKEFIXED (1, 0), 0L,
         0L,               0L,               1L
         };
const MATRIXLF vmatlfScale =
         {
         MAKEFIXED (1, 0), MAKEFIXED (0, 0), 0L,
         MAKEFIXED (0, 0), MAKEFIXED (1, 0), 0L,
         0L ,              0L,               1L
         };

/*--------------------------------------------------------------*\
 *  Externe Variable und lokale Funktionsprototypen             *
\*--------------------------------------------------------------*/
MRESULT EXPENTRY ClkTicksDlgProc  (HWND hWnd,ULONG usMessage,
                                   MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY ClkColorsDlgProc (HWND hWnd,ULONG usMessage,
                                   MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY AlarmDlgProc     (HWND hWnd,ULONG usMessage,
                                   MPARAM mp1, MPARAM mp2);

VOID ClkPaint             (HWND hwnd, PWINDOWDATA pWindowData);
VOID ClkCreate            (HWND hwnd, PWINDOWDATA pWindowData);
VOID ClkStartAudioPlay    (HWND hwnd, PWINDOWDATA pWindowData, ULONG ulHours);
VOID ClkDestroy           (PWINDOWDATA pWindowData);
VOID ClkSize              (HWND);
VOID ClkTimer             (HWND);
VOID ClkShowFrameControls (HWND, BOOL);
VOID ClkPresparam         (HWND hwnd, ULONG ulType);

 VOID DrawDigitalTime (HWND, PDATETIME, ULONG);
 VOID DrawClock (HPS, ULONG, WPDCF77Data *, PDATETIME, USHORT);
VOID SetDispMode (VOID);
VOID SetFonts (WPDCF77Data *);
 VOID SetRGBColors (WPDCF77Data *);
 VOID ShadeLight (PCOLORS);
 BYTE LightRGBByte (BYTE);
 BYTE ShadeRGBByte (BYTE);
BOOL AlarmSetTimer (WPDCF77Data *somThis, PDATETIME pdtActual, ALARMTIME *pdtAlarm);
VOID GetDateTimeOffs (LONG lOffset, PDATETIME pdt);
LONG GetTimeLowOffs (LONG lOffset);

/*******************************************************************\
    ClkWndProc: Window-Prozedur fÅr die Uhr
    Eingang: hwnd: Window-Handle
             msg:  Message-Typ
             mp1:  1. Parameter
             mp2:  2. Parameter
\*******************************************************************/
MRESULT EXPENTRY ClkWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    WPDCF77     *somSelf;
    WPDCF77Data *somThis;
    PWINDOWDATA pWindowData;
    POINTL      ptl;
    SWP         swp;
    CHAR        szSubst[CCHMAXDATETIME];

    switch (msg)
        {
        case WM_CREATE:
            pWindowData = (PWINDOWDATA) mp1;
            ClkCreate (hwnd, pWindowData);
            return FALSE;

        case WM_1STIMER:
            ClkTimer (hwnd);
            return 0;

        case WM_BUTTON2CLICK:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;
            somSelf = pWindowData->somSelf;
            WinQueryPointerPos (HWND_DESKTOP, &ptl);
            WinMapWindowPoints (HWND_DESKTOP, hwnd, &ptl, 1);
            _wpDisplayMenu (somSelf, _pIData->hwndFrame, _pIData->hwndFrame, &ptl, MENU_OPENVIEWPOPUP, 0);
            break;

        case WM_PAINT:
            ClkPaint (hwnd, (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER));
            return 0;

        /* WM_MINMAXFRAME wird zur Steuerung der Iconposition verwendet.     */
        /* StandardmÑ·ig legt OS/2 die Iconposition fest und verwaltet diese */
        /* getrennt von der normalen Fensterposition.                        */
        /* Folgende Messages kommen an: WM_MINMAXFRAME - WM_MOVE - WM_SIZE   */
        /* (teilweise auch mehrfach)                                         */
        /* Ist in _ulPresence DISPLAY_ICONPOS gesetzt, geschieht folgendes:  */
        /* - WM_MINMAXFRAME: Bei Wechsel Icon <-> Normal wird ulMinMaxStat   */
        /*                   auf MINMAX_CHANGED gesetzt                      */
        /* - WM_MOVE:        ulMinMaxStat == MINMAX_NORMAL: Position sichern */
        /*                   sonst: ulMinMaxStat = MINMAX_WAIT4SIZE          */
        /* - WM_SIZE:        ulMinMaxStat == MINMAX_WAIT4SIZE: Position neu  */
        /*                   setzen, ulMinMaxStat = MINMAX_NORMAL            */
        case WM_MINMAXFRAME:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;
            if (_ulPresence & PRESENCE_MINMAXPOS)
                {
                _pIData->ulMinMaxStat = MINMAX_CHANGED;
                DebugE (D_MINMAX, "ClkWndProc", "WM_MINMAXFRAME: MINMAX_CHANGED");
                }
            break;

        case WM_PLAY_MMFILE:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;
            DebugE (D_ALARM, "ClkWndProc", "play multimedia file");

            if (_szAlarmSoundFile[0] != '\0' && bIsAudio)
                {
                BOOL bRC;
                bRC = ClkMciPlayFile (HWND_DESKTOP, _szAlarmSoundFile);
                DebugULx (D_ALARM, "ClkWndProc", "return for mciPlayFile: ", (bRC ? "TRUE" : "FALSE"));
                }
            return 0;

        case WM_SIZE:
            ClkSize (hwnd);
            return 0;

        case WM_MOVE:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;

            WinQueryWindowPos (_pIData->hwndFrame, &swp);
            if (!(swp.fl & SWP_MINIMIZE))
                {
                _lcxClock = swp.cx;
                _lcyClock = swp.cy;
                }

            /* Wechsel Icon<->Normal? -> Sonderbehandlung; s. WM_MINMAXFRAME */
            if (_pIData->ulMinMaxStat == MINMAX_NORMAL)
                {
                if (!(swp.fl & SWP_MINIMIZE))
                    {
                    _lxPos = swp.x;
                    _lyPos = swp.y;
                    DebugE (D_MINMAX, "ClkWndProc", "WM_MOVE: Position saved");
                    }
                else if (_ulPresence & PRESENCE_MINMAXPOS)
                    {
                    _lxIconPos = swp.x;
                    _lyIconPos = swp.y;
                    DebugE (D_MINMAX, "ClkWndProc", "WM_MOVE: Icon-Position saved");
                    }
                }
            else
                _pIData->ulMinMaxStat = MINMAX_WAIT4SIZE;

            _wpSaveDeferred (pWindowData->somSelf);
            return 0;

        case WM_BUTTON1DOWN:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;
            if (WinIsChild (_pIData->hwndTitleBar, HWND_OBJECT))
                return WinSendMsg (_pIData->hwndFrame, WM_TRACKFRAME,
                                   MPFROMSHORT((USHORT)mp2 | TF_MOVE), MPVOID);
            else
                break;

        case WM_MESSAGE:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;
            MessageBox (hwnd, (ULONG)mp1, IDMSG_ALARMTITLE, (ULONG)mp2, 0, *_szAlarmMsg == '\0' ? NULL : _szAlarmMsg);
            return 0;

        case WM_SUBSTITUTESTRING:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;
            switch (SHORT1FROMMP (mp1))
                {
                case 0:                     // %t-Parameter: Zeit
                    GetDateTime (&_pIData->dt, MODE_PM | MODE_YEAR_2D, szSubst, NULL);
                    return szSubst;

                case 1:                     // %d-Parameter: Datum
                    GetDateTime (&_pIData->dt, MODE_PM | MODE_YEAR_2D, NULL, szSubst);
                    return szSubst;

                case 2:                     // %z-Parameter: Zeitzone
                    return _szTimezone;
                }
            return 0;

        case WM_PRESPARAMCHANGED:
            ClkPresparam (hwnd, (ULONG)LONGFROMMP (mp1));
            return 0;

        /* WM_USER_STARTPLAY wird zur Initialisierung der Audioausgabe       */
        /* verwendet.                                                        */
        /* mp1: SHORT1: Anzahl der Play-VorgÑnge                             */
        /*      SHORT2: Reserviert                                           */
        /* mp2: Reserviert                                                   */
        case WM_USER_STARTPLAY:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            ClkStartAudioPlay (hwnd, pWindowData, LONGFROMMP (mp1));
            return 0;

        /* MM_MCIPASSDEVICE informiert das System darÅber, da· sich der      */
        /* Besitz des gemeinsam genutzen Multimedia-GerÑtes geÑndert hat.    */
        /* mp1: USHORT1: usDeviceID                                          */
        /*      USHORT2: Reserviert                                          */
        /* mp2: USHORT1: usEvent                                             */
        /*      USHORT2: Reserviert                                          */
        case MM_MCIPASSDEVICE:
            ClkMciPassDevice (hwnd, IDX_WINDOWPTR, SHORT1FROMMP (mp2));
            break;

        /* WM_ACTIVATE informiert das System Åber einen Fokuswechsel im      */
        /* System. Damit kann Åber ein MM_ACQUIREDEVICE der Besitz des       */
        /* Multimedia-Systems angefordert werden.                            */
        /* mp1: USHORT1: usactive                                            */
        /*      USHORT2: Reserviert                                          */
        /* mp2: hwnd                                                         */
        case WM_ACTIVATE:
            ClkMciActivate (hwnd, IDX_WINDOWPTR, (BOOL)mp1);
            break;

        /* WM_PLAY_FINISHED informiert das System darÅber, da· eine Audio-   */
        /* Datei vollstÑndig abgespielt wurde.                               */
        case WM_PLAY_FINISHED:
            ClkMciCheckRedo (hwnd, IDX_WINDOWPTR);
            return 0;

        case WM_DESTROY:
            ClkDestroy ((PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER));
            return 0;

        case WM_CLOSE:
            pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
            somThis = pWindowData->somThis;

            if (pWindowData == NULL)
                {
                DebugE (D_WND | D_DIAG, "ClkWndProc", "WM_CLOSE: couldn't get window words");
                return FALSE;
                }

            /* Alarm anhalten */
            DebugE (D_ALARM, "ClkWndProc", "Alarm STOPPED");
            _pIData->TimerResources.ulDays       = 0;                // Anzahl der Tage
            _pIData->TimerResources.ulTimerValue = 0;                // Anzahl der Millisekunden
            _pIData->TimerResources.ulPostReason = TR_ALARMSTOPPED;  // Timer anhalten
            DosPostEventSem (_pIData->TimerResources.hSemTimer);     // Timerthread informieren

            _wpDeleteFromObjUseList (pWindowData->somSelf, &pWindowData->UseItem);
            _wpRemove1sTimer (pWindowData->somSelf, hwnd);

            ClkMciClose (hwnd, IDX_WINDOWPTR);

            DebugULx (D_WND, "WM_CLOSE", "hwndFrame", _pIData->hwndFrame);
            WinDestroyWindow (_pIData->hwndFrame);
            _wpFreeMem (pWindowData->somSelf, (PBYTE)pWindowData);
            return 0;
        }

    return WinDefWindowProc (hwnd, msg, mp1, mp2);
    }

/*******************************************************************\
    ClkCreate: Behandlung der WM_CREATE-Message: Presentation-spaces
               erzeugen, Variable initialisieren
    Eingang: hwnd:        Window-Handle
             pWindowData: Zeiger auf Window-Daten
\*******************************************************************/
VOID ClkCreate (HWND hwnd, PWINDOWDATA pWindowData)
    {
    LONG lxTemp, lyTemp;
    WPDCF77Data *somThis;

    /* Zugang zu Instanzdaten initialisieren */
    somThis = pWindowData->somThis;

    /* Class view/usage details und Window spezifische Daten */
    pWindowData->UseItem.type    = USAGE_OPENVIEW;
    pWindowData->ViewItem.view   = (_ulPresence & PRESENCE_DISP_DIGITAL) ? OPEN_DIGITAL : OPEN_ANALOG;
    pWindowData->ViewItem.handle = _pIData->hwndFrame;

    /* Window-Ptr mit pWindowData fÅllen und View registrieren */
    WinSetWindowPtr (hwnd, QWL_USER, pWindowData);
    _wpAddToObjUseList (pWindowData->somSelf, &pWindowData->UseItem);
    _wpRegisterView (pWindowData->somSelf, _pIData->hwndFrame,
                     _ulPresence & PRESENCE_DISP_DIGITAL ? "Digital" : "Analog");
    WinSetFocus (HWND_DESKTOP, _pIData->hwndFrame);

    /* Audio initialisieren */
    WinSetWindowPtr (hwnd, QWL_USER + IDX_WINDOWPTR, NULL);
    bIsAudio = ClkMciIsMultimedia () ? TRUE : FALSE;
    DebugE (D_WND, "ClkCreate => bIsAudio", (bIsAudio ? "TRUE" : "FALSE"));

    /* Icon lîschen, damit Uhr als Icon lÑuft */
    WinSendMsg (_pIData->hwndFrame, WM_SETICON, MPVOID, MPVOID);

    _pIData->vmatlfDateTrans = vmatlfTrans;
    _pIData->vmatlfDateScale = vmatlfScale;

    _pIData->hwndTitleBar = WinWindowFromID (_pIData->hwndFrame, FID_TITLEBAR);
    _pIData->hwndSysMenu  = WinWindowFromID (_pIData->hwndFrame, FID_SYSMENU);
    _pIData->hwndMinMax   = WinWindowFromID (_pIData->hwndFrame, FID_MINMAX);

    if (pWindowData->ViewItem.view == OPEN_ANALOG)
        {
        /* Bildschirmgrî·e bestimmen; Device Context îffnen */
        /* Presentation Space erzeugen                      */
        _pIData->hdc = WinOpenWindowDC (hwnd);
        _pIData->hps = GpiCreatePS (hab, _pIData->hdc, (PSIZEL)&sizl,
                           PU_ARBITRARY | GPIT_MICRO | GPIA_ASSOC);

        /* Eigenen off-screen 'Puffer' erzeugen */
        _pIData->hdcBuffer = DevOpenDC ((HAB)0L, OD_MEMORY, "*", 0L, NULL, _pIData->hdc);
        _pIData->hpsBuffer = GpiCreatePS (hab, _pIData->hdcBuffer, (PSIZEL)&sizl,
                                          PU_ARBITRARY | GPIT_MICRO | GPIA_ASSOC);

        /* System in RGB-Modus schalten */
        GpiCreateLogColorTable (_pIData->hpsBuffer, 0, LCOLF_RGB, 0, 0, NULL);

        /* Auflîsung bestimmen, um das Ziffernblatt rund darzustellen */
        DevQueryCaps (_pIData->hdc, CAPS_HORIZONTAL_RESOLUTION, 1, (PLONG)&pWindowData->cxRes);
        DevQueryCaps (_pIData->hdc, CAPS_VERTICAL_RESOLUTION,   1, (PLONG)&pWindowData->cyRes);
        DevQueryCaps (_pIData->hdc, CAPS_COLOR_PLANES,          1, (PLONG)&pWindowData->cColorPlanes);
        DevQueryCaps (_pIData->hdc, CAPS_COLOR_BITCOUNT,        1, (PLONG)&pWindowData->cColorBitcount);
        }
    else
        {
        _pIData->hdc = WinOpenWindowDC (hwnd);
        _pIData->hps = GpiCreatePS (hab, _pIData->hdc, (PSIZEL)&sizl,
                           PU_PELS | GPIT_MICRO | GPIA_ASSOC);
        }

    SetRGBColors (somThis);
    SetFonts (somThis);

    /* Zeit und Datum holen */
    GetDateTimeOffs (_lLOffset, &_pIData->dt);
    _pIData->flRcvrStatus     = GetDCFStatus ();
    _pIData->flRcvrStatusMask = StatDCF.flMaskST & (MASK_ST_TZONE1 | MASK_ST_BATT);

    /* Fenster positionieren und sichtbar machen */
    if (_ulPresence & PRESENCE_DISP_MINIMIZE)
        {
        lxTemp = _lxIconPos;
        lyTemp = _lyIconPos;
        }
    else
        {
        lxTemp = _lxPos;
        lyTemp = _lyPos;
        }

    WinSetWindowPos (_pIData->hwndFrame, NULLHANDLE,
        lxTemp, lyTemp, _lcxClock, _lcyClock,
        SWP_ACTIVATE | SWP_SIZE | SWP_MOVE | (_ulPresence & PRESENCE_DISP_MINIMIZE ? SWP_MINIMIZE : 0));

    if (_ulPresence & (PRESENCE_MINMAXPOS | PRESENCE_DISP_MINIMIZE))
        WinSetWindowPos (_pIData->hwndFrame, NULLHANDLE,
                         lxTemp, lyTemp, _lcxClock, _lcyClock,
                         SWP_MOVE);

    /* Titelleiste anzeige? */
    if (!(_ulPresence & PRESENCE_TITLEBAR))
        ClkShowFrameControls (_pIData->hwndFrame, FALSE);

    WinShowWindow (_pIData->hwndFrame, TRUE);

    /* Timer starten */
    _wpAdd1sTimer (pWindowData->somSelf, hwnd);

    return;
    }

/*******************************************************************\
    ClkDestroy: Behandlung der WM_DESTROY-Message:
                Presentations-spaces freigeben
    Eingang: pWindowData: Zeiger auf Window-Daten
\*******************************************************************/
VOID ClkDestroy (PWINDOWDATA pWindowData)
    {
    WPDCF77Data *somThis;
    HBITMAP     hbm;

    /* Zugang zu Instanzdaten initialisieren */
    somThis = pWindowData->somThis;

    if (pWindowData->ViewItem.view == OPEN_ANALOG)
        {
        hbm = GpiSetBitmap (_pIData->hpsBuffer, NULLHANDLE);

        if (hbm != NULLHANDLE)
            GpiDeleteBitmap (hbm);
        }

    GpiDestroyPS (_pIData->hpsBuffer);
    DevCloseDC   (_pIData->hdcBuffer);
    _pIData->hpsBuffer = NULLHANDLE;
    _pIData->hdcBuffer = NULLHANDLE;

    GpiDestroyPS (_pIData->hps);
    DevCloseDC   (_pIData->hdc);
    _pIData->hps = NULLHANDLE;
    _pIData->hdc = NULLHANDLE;

    return;
    }

/*******************************************************************\
    ClkSize: Behandlung der WM_SIZE-Message:
             Page-Viewports berechnen, Position der Datumsanzeige
             bestimmen
    Eingang: hwnd: Window-handle
\*******************************************************************/
VOID ClkSize (HWND hwnd)
    {
    LONG             cxSquare, cySquare, cxEdge, cyEdge, cxWindow, cyWindow;
    RECTL            rclWindow;
    RECTL            rclPage;               // Grî·e des page viewports
    SWP              swp;
    HBITMAP          hbm;
    BITMAPINFOHEADER bmp;
    PWINDOWDATA      pWindowData;
    WPDCF77Data      *somThis;

    /* Zugang zu Instanzdaten initialisieren */
    pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
    somThis = pWindowData->somThis;

    /* Ist die Uhr ikonisiert? */
    WinQueryWindowPos (_pIData->hwndFrame, &swp);
    if (swp.fl & SWP_MINIMIZE)
        _ulPresence |= PRESENCE_DISP_MINIMIZE;
    else
        {
        _ulPresence &= ~PRESENCE_DISP_MINIMIZE;
        _lcxClock = swp.cx;
        _lcyClock = swp.cy;
        }

    /* Wechsel Icon<->Normal? -> Sonderbehandlung; s. WM_MINMAXFRAME */
    if (_pIData->ulMinMaxStat == MINMAX_WAIT4SIZE)
        {
        if (_ulPresence & PRESENCE_DISP_MINIMIZE)
            {
            swp.x = _lxIconPos;
            swp.y = _lyIconPos;
            }
        else
            {
            swp.x = _lxPos;
            swp.y = _lyPos;
            }
        WinSetWindowPos (_pIData->hwndFrame, NULLHANDLE,
            swp.x, swp.y, _lcxClock, _lcyClock,
            SWP_MOVE);
        _pIData->ulMinMaxStat = MINMAX_NORMAL;
        DebugE (D_MINMAX, "ClkWndProc", "WM_SIZE: Position set");
        }
    else
        {
        if (swp.fl & SWP_MINIMIZE)
            {
            _lxIconPos = swp.x;
            _lyIconPos = swp.y;
            DebugE (D_MINMAX, "ClkWndProc", "WM_SIZE: Icon-Position saved");
            }
        else
            {
            _lxPos    = swp.x;
            _lyPos    = swp.y;
            DebugE (D_MINMAX, "ClkWndProc", "WM_SIZE: Position saved");
            }
        }

    if (pWindowData->ViewItem.view == OPEN_ANALOG)
        {
        /* Evtl. vorhandene Bitmaps im Puffer lîschen */
        hbm = GpiSetBitmap (_pIData->hpsBuffer, NULLHANDLE);
        if (hbm != NULLHANDLE)
            GpiDeleteBitmap (hbm);

        /* Grî·e des Client-Windows bestimmen */
        WinQueryWindowRect (hwnd, &rclWindow);
        cxWindow = rclWindow.xRight - rclWindow.xLeft;
        cyWindow = rclWindow.yTop - rclWindow.yBottom;

        /* Bitmap in Fenstergrî·e erzeugen */
        bmp.cbFix     = sizeof(BITMAPINFOHEADER);
        bmp.cx        = (SHORT)cxWindow;
        bmp.cy        = (SHORT)cyWindow;
        bmp.cPlanes   = (SHORT)pWindowData->cColorPlanes;
        bmp.cBitCount = (SHORT)pWindowData->cColorBitcount;
        hbm = GpiCreateBitmap(_pIData->hpsBuffer, (PBITMAPINFOHEADER2)&bmp, 0, NULL, NULL);
        GpiSetBitmap (_pIData->hpsBuffer, hbm);

        /* Annahme: Rechteck ist durch y-Richtung begrenzt   */
        /* -> cx so berechnen, da· Rechteck quadratisch wird */
        /* wenn Annahme falsch war: umgekehrt vorgehen       */
        cySquare = cyWindow - 4;
        cxSquare = (cyWindow * pWindowData->cxRes) / pWindowData->cyRes;
        if (cxWindow < cxSquare)
            {
            cxSquare = cxWindow - 4;
            cySquare = (cxWindow * pWindowData->cyRes) / pWindowData->cxRes;
            }

        /* RestflÑchen bestimmen und Page Viewport setzen */
        cxEdge = (cxWindow - cxSquare) / 2;
        cyEdge = (cyWindow - cySquare) / 2;
        rclPage.xLeft   = cxEdge;
        rclPage.xRight  = cxWindow - cxEdge;
        rclPage.yBottom = cyEdge;
        rclPage.yTop    = cyWindow - cyEdge;

        /* Position des Datums bestimmen; PrioritÑtsfolge: */
        /* 1. Unter der Uhr                                */
        /* 2. Links von Uhr                                */
        /* 3. In der Uhr                                   */
        if (cyWindow > (cySquare*6/5))          /* Unterhalb Uhr */
            {
            /* Matrix:  2.5    0      0  */
            /*          0      2.5    0  */
            /*         15    -17      1  */
            _pIData->vmatlfDateTrans.lM31 = 15;          /* Horizontal */
            _pIData->vmatlfDateTrans.lM32 = -17;         /* Vertikal   */
            _pIData->vmatlfDateScale.fxM11 = MAKEFIXED (2, 0x8000);
            _pIData->vmatlfDateScale.fxM22 = MAKEFIXED (2, 0x8000);
            rclPage.yTop    += cyEdge;
            rclPage.yBottom += cyEdge;
            }
        else if (cxWindow > (cxSquare * 31/10))
            {
            /* Matrix:  7.875  0      0  */
            /*          0      7.875  0  */
            /*        -53      4      1  */
            _pIData->vmatlfDateTrans.lM31 = -53 ;        /* Horizontal */
            _pIData->vmatlfDateTrans.lM32 = 4;           /* Vertikal   */
            _pIData->vmatlfDateScale.fxM11 = MAKEFIXED (7, 0xE000);
            _pIData->vmatlfDateScale.fxM22 = MAKEFIXED (7, 0xE000);
            rclPage.xRight += cxEdge;
            rclPage.xLeft  += cxEdge;
            }
        else if (cxWindow > (cxSquare * 2))     /* Links */
            {
            /* Matrix:  3.8125 0      0  */
            /*          0      7.8725 0  */
            /*        -52      2      1  */
            _pIData->vmatlfDateTrans.lM31 = -52;         /* Horizontal */
            _pIData->vmatlfDateTrans.lM32 = 2;           /* Vertikal   */
            _pIData->vmatlfDateScale.fxM11 = MAKEFIXED (3, 0xD000);
            _pIData->vmatlfDateScale.fxM22 = MAKEFIXED (3, 0xD000);
            rclPage.xRight += cxEdge;
            rclPage.xLeft  += cxEdge;
            }
        else                                    /* Innerhalb */
            {
            _pIData->vmatlfDateTrans.lM31 = 24;          /* Horizontal */
            _pIData->vmatlfDateTrans.lM32 = 23;          /* Vertikal   */
            _pIData->vmatlfDateScale.fxM11 = MAKEFIXED (2, 0);
            _pIData->vmatlfDateScale.fxM22 = MAKEFIXED (2, 0);
            }

        GpiSetPageViewport (_pIData->hps,       &rclPage);
        GpiSetPageViewport (_pIData->hpsBuffer, &rclPage);
        }

    _pIData->bBufferDirty = TRUE;

    _wpSaveDeferred (pWindowData->somSelf);

    return;
    }

/*******************************************************************\
    ClkTimer: Behandlung der WM_1STIMER-Message:
    Eingang: hwnd: Window-handle
\*******************************************************************/
VOID ClkTimer (HWND hwnd)
    {
    PWINDOWDATA  pWindowData;
    WPDCF77      *somSelf;
    WPDCF77Data  *somThis;
    DATETIME     dtNew;
    USHORT       flRcvrStatusNew;
    USHORT       flRcvrStatusMaskNew;
    ULONG        ulTime;
    BOOL         bUpdate = FALSE;

    /* Zugang zu Instanzdaten initialisieren */
    pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
    somSelf     = pWindowData->somSelf;
    somThis     = pWindowData->somThis;

    /* Neue Zeit holen */
    GetDateTimeOffs (_lLOffset, &dtNew);

    if (pWindowData->ViewItem.view == OPEN_ANALOG)
        {
        /* neuen DCF-Status holen */
        flRcvrStatusNew     = GetDCFStatus ();
        flRcvrStatusMaskNew = StatDCF.flMaskST & (MASK_ST_TZONE1 | MASK_ST_BATT);

        if ((_pIData->dt.minutes ^ dtNew.minutes) + (_pIData->dt.hours ^ dtNew.hours) +
            (_pIData->dt.day     ^ dtNew.day)     + (_pIData->dt.month ^ dtNew.month) +
            (_pIData->dt.year    ^ dtNew.year))
            {
            /* Neuzeichnen, da sich die Minute geÑndert hat */
            DrawClock (_pIData->hpsBuffer, DCLK_HANDS, somThis, &dtNew, flRcvrStatusNew);
            UpdateScreen (_pIData->hps, somThis, NULL);
            bUpdate = TRUE;

            if (_ulPresence & PRESENCE_DISP_SEC_HAND && !(_ulPresence & PRESENCE_DISP_MINIMIZE))
                {
                GpiSetMix (_pIData->hps, FM_INVERT);
                ClkDrawHand (_pIData->hps, somThis, HT_SECOND, dtNew.seconds);
                }
            }

        /* Audioausgabe starten, falls installiert und aktiviert */
        if (dtNew.minutes == 0 && dtNew.seconds == 0 && bIsAudio)
            WinPostMsg (hwnd, WM_USER_STARTPLAY, MPFROMSHORT (dtNew.hours), 0);

        // ??? wird bei einer MinutenÑnderung die Uhr 2x gezeichnet????
        if (flRcvrStatusNew != _pIData->flRcvrStatus || flRcvrStatusMaskNew != _pIData->flRcvrStatusMask)
            {
            if ((flRcvrStatusNew ^ _pIData->flRcvrStatus) &
                (STATUS_TZONE1 | STATUS_TZONE2    | STATUS_CARRIER |
                 STATUS_BATT   | STATUS_TIMEVALID | STATUS_ISDRIVER) ||
                flRcvrStatusMaskNew != _pIData->flRcvrStatusMask)
                {
                /* Statusanzeigen zeichnen */
                DrawClock (_pIData->hpsBuffer, DCLK_ALL, somThis, &dtNew, flRcvrStatusNew);
                UpdateScreen (_pIData->hps, somThis, NULL);
                bUpdate = TRUE;
                _pIData->flRcvrStatus     = flRcvrStatusNew;
                _pIData->flRcvrStatusMask = flRcvrStatusMaskNew;

                if (_ulPresence & PRESENCE_DISP_SEC_HAND && !(_ulPresence & PRESENCE_DISP_MINIMIZE))
                    {
                    GpiSetMix (_pIData->hps, FM_INVERT);
                    ClkDrawHand (_pIData->hps, somThis, HT_SECOND, dtNew.seconds);
                    }
                }
            }

        if (_ulPresence & PRESENCE_DISP_SEC_HAND && !(_ulPresence & PRESENCE_DISP_MINIMIZE) && !bUpdate)
            {
            /* Sonst nur den Sekundenzeiger lîschen und neu zeichnen */
            GpiSetMix (_pIData->hps, FM_INVERT);
            ClkDrawHand (_pIData->hps, somThis, HT_SECOND, _pIData->dt.seconds);
            ClkDrawHand (_pIData->hps, somThis, HT_SECOND, dtNew.seconds);
            }

        }
    else
        {
        DrawDigitalTime (hwnd, &dtNew,
            (_pIData->dt.minutes ^ dtNew.minutes) + (_pIData->dt.hours ^ dtNew.hours) +
            (_pIData->dt.day     ^ dtNew.day)     + (_pIData->dt.month ^ dtNew.month) +
            (_pIData->dt.year    ^ dtNew.year) ?
            DCLK_ALL : DCLK_HANDS);
        }

    _pIData->dt = dtNew;

    if (!_pIData->ulTimeChangeCheck)
        /* Beim ersten Durchlauf initialisieren */
        _pIData->ulTimeChangeCheck = (ULONG)GetTimeLowOffs (_lLOffset);
    else
        {
        /* Ein schneller Check, ob eine andere Session die Zeit geÑndert hat */
        ulTime = (ULONG)GetTimeLowOffs (_lLOffset);
        if (ulTime > (_pIData->ulTimeChangeCheck + 60) ||
            _pIData->ulTimeChangeCheck > (ulTime + 60))
            {
            /* Zeit hat sich um mehr als 60 Sekunden geÑndert */
            DebugE (D_ALARM, "ClkTimer", "TimeChange");
            if (!AlarmSetTimer (somThis, &dtNew, &_dtAlarm))
                _wpSaveDeferred (somSelf);
            _wpRefreshClockView (somSelf);          // nur Face reicht auch! ???
            }
        _pIData->ulTimeChangeCheck = ulTime;
        }

    return;
    }

/*******************************************************************\
    ClkStartAudioPlay: Berechnet die Anzahl der Gongs in AbhÑngigkeit
                       der Uhrzeit und spielt das entsprechende
                       WAV-File, falls mîglich und notwendig
    Eingang: hwnd:    Window handle
             ulHours: Stunden der Uhrzeit
\*******************************************************************/
VOID ClkStartAudioPlay (HWND hwnd, PWINDOWDATA pWindowData, ULONG ulHours)
    {
    WPDCF77     *somSelf;
    WPDCF77Data *somThis;
    HOBJECT      hObject;

    somThis = pWindowData->somThis;
    somSelf = pWindowData->somSelf;
    hObject = _wpQueryHandle (somSelf);

    if ((hObject == hClsRingingObject) && (szClsGongFile[0] != '\0'))
        {
        if (bClsIs1PerHour)
            ulHours = 1;
        else
            {
            ulHours = ulHours % 12;
            ulHours = ulHours ? ulHours : 12;
            }

        if (ClkMciLoadFile (hwnd, IDX_WINDOWPTR, szClsGongFile, ulHours))
            ClkMciStartPlayBack (hwnd, IDX_WINDOWPTR, WM_PLAY_FINISHED);
        }

    return;
    }

/*******************************************************************\
    ClkPresparam: Bearbeitet énderungen der Presentation-Parameter
                  PP_BACKGROUNDCOLOR und PP_FONTNAMESIZE
    Eingang: hwnd:   Window handle
             ulType: PresParam-Typ: PP_*
\*******************************************************************/
VOID ClkPresparam (HWND hwnd, ULONG ulType)
    {
    PWINDOWDATA pWindowData;
    WPDCF77     *somSelf;
    WPDCF77Data *somThis;
    RGB         rgb;
    LONG        lCount;
    PBYTE       pBuffer;

    /* Zugang zu Instanzdaten initialisieren */
    pWindowData = (PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER);
    somSelf     = pWindowData->somSelf;
    somThis     = pWindowData->somThis;

    switch (ulType)
        {
        case PP_BACKGROUNDCOLOR:
            WinQueryPresParam (hwnd, ulType, 0, NULL, sizeof (RGB), (PVOID)&rgb,
                QPF_PURERGBCOLOR);

            _clrFace    = (rgb.bRed<<16) + (rgb.bGreen<<8) + rgb.bBlue;
            _clrBackgnd = _clrDateOnAnalog = _clrFace;
            DebugULx (D_DRAG, "ClkWndProc", "RGB-Wert", _clrFace);
            break;

        case PP_FONTNAMESIZE:
            if (!DosAllocMem ((PPVOID)&pBuffer, CCHMAXFONTSIZENAME + sizeof (FONTMETRICS),
                             PAG_COMMIT | PAG_READ | PAG_WRITE))
                {
                WinQueryPresParam (hwnd, ulType, 0, NULL, CCHMAXFONTSIZENAME, (PVOID)pBuffer, 0);

                lCount = 1;
                GpiQueryFonts (_pIData->hpsBuffer, QF_PUBLIC, strchr (pBuffer, '.')+1, &lCount,
                    sizeof (FONTMETRICS), (PFONTMETRICS)&pBuffer[CCHMAXFONTSIZENAME]);

                DebugE (D_DRAG, "ClkWndProc => szFacename",   ((PFONTMETRICS)(pBuffer+CCHMAXFONTSIZENAME))->szFacename);
                DebugE (D_DRAG, "ClkWndProc => szFamilyname", ((PFONTMETRICS)(pBuffer+CCHMAXFONTSIZENAME))->szFamilyname);

                if (lCount == 1 && ((PFONTMETRICS)(pBuffer+CCHMAXFONTSIZENAME))->fsDefn & FM_DEFN_OUTLINE)
                    {
                    memset (&_fAttrD, 0, sizeof (FATTRS));
                    memset (&_fAttrT, 0, sizeof (FATTRS));
                    _fAttrD.usRecordLength = _fAttrT.usRecordLength = sizeof (FATTRS);
                    _fAttrD.fsFontUse      = _fAttrT.fsFontUse      = 0;
                    _fAttrD.fsType         = _fAttrT.fsType         = FATTR_FONTUSE_OUTLINE;
                    strcpy (_fAttrD.szFacename, ((PFONTMETRICS)(pBuffer+CCHMAXFONTSIZENAME))->szFacename);
                    strcpy (_fAttrT.szFacename, ((PFONTMETRICS)(pBuffer+CCHMAXFONTSIZENAME))->szFacename);
                    strcpy (_szFontFamilyD,     ((PFONTMETRICS)(pBuffer+CCHMAXFONTSIZENAME))->szFamilyname);
                    strcpy (_szFontFamilyT,     ((PFONTMETRICS)(pBuffer+CCHMAXFONTSIZENAME))->szFamilyname);
                    }
                else
                    {
                    WinAlarm (HWND_DESKTOP, WA_ERROR);
                    return;
                    }

                DosFreeMem (pBuffer);
                }
            break;
        }

    _wpRefreshClockView (somSelf);
    _wpSaveDeferred (somSelf);
    return;
    }

/*******************************************************************\
    ClkDrawString: Ausgabe eines Strings in das Rechteck prcl.
                   Die Zeichen werden so verzerrt, da· der gesamte
                   String in das angegebene Rechteck pa·t.
    Eingang: hps:       Presentation space
             ulFGColor: Vordergrundfarbe
             pszString: String
             prcl:      Zeiger auf RECTL-Struktur
\*******************************************************************/
VOID ClkDrawString (HPS hps, ULONG ulFGColor, PCHAR pszString, PRECTL prcl)
    {
    USHORT      cx, cy;
    ULONG       ulc;
    SIZEF       sizef;
    POINTL      ptl;
    POINTL      aptlCharPos[12];                    // Puffer fÅr Zeichenpositionen
    FONTMETRICS fm;

    /* Farbe und Textmodus einstellen */
    GpiSetColor (hps, ulFGColor);
    GpiSetCharMode (hps, CM_MODE3);

    /* VorlÑufige Wahl der Zeichenbox */
    sizef.cx = sizef.cy = MAKEFIXED (TESTSIZE, 0);  // Zeichenaspekt auf Nominalwert 1:1, Grî·e 12 setzen
    GpiSetCharBox (hps, &sizef);

    /* BERECHNUNG DER ZEICHENBREITE:                                        */
    /* Dazu wird auf der Basis eines cy x cy-Zeichens                       */
    /* die Breite des Gesamtstrings bestimmt (180/Pi = 57.3):               */
    /*               l = Xende - Xanfang + tan(sl)*dy                       */
    /*    NÑherung:  l = Xende - Xanfang + sl*lMaxAscender/57.3             */
    /* Die neue Zeichenbreite ist dann x = TESTSIZE * cx/l                  */
    /* AbkÅrzungen: sl:  Zeichenwinkel fÅr Italic                           */
    /*              cx:  Soll-StringlÑnge                                   */
    /*              dy:  empirisch ermittelte Hîhe (ca. lMaxAscender * 1.4) */
    /* BERECHNUNG DER ZEICHENHôHE:                                          */
    /* Die Hîhe der Zeichenbox wird Åber lMaxAscender und eine empirische   */
    /* Konstante (14) eingestellt: cy = cy*14/lMaxAscender                  */
    cx = LOUSHORT (prcl->xRight - prcl->xLeft);
    cy = LOUSHORT (prcl->yTop   - prcl->yBottom);

    ptl.x = prcl->xLeft;
    ptl.y = prcl->yBottom;

    ulc = strlen (pszString);
    GpiQueryCharStringPosAt (hps, &ptl, 0, strlen (pszString), pszString, NULL, aptlCharPos);
    GpiQueryFontMetrics (hps, sizeof (FONTMETRICS), &fm);

    sizef.cy = (FIXED)(65536. * ((double)(cy * 14)/(double)fm.lMaxAscender));
    sizef.cx = (FIXED)(65536 * (double)TESTSIZE * (double)cx /
        ((double)(aptlCharPos[ulc].x - aptlCharPos[0].x) +
        (double)fm.lMaxAscender * (double)(fm.sCharSlope&0x1FF) / 81.86));

    /* String darstellen */
    GpiSetCharBox (hps, &sizef);
    GpiCharStringAt (hps, &ptl, strlen (pszString), pszString);

    return;
    }

/*******************************************************************\
    DrawDigitalTime: Darstellung der Digitaluhr
    Eingang: hwnd:       Window handle
             pdt:        DATETIME-Struktur
             ulPresence: Darstellungs-Flags
             ulMode:     Modus: DCLK_ALL oder DCLK_HANDS
\*******************************************************************/
VOID DrawDigitalTime (HWND hwnd, PDATETIME pdt, ULONG ulMode)
    {
    RECTL  rcl;
    RECTL  rclTime;
    RECTL  rclDate;
    CHAR   achTime[10];
    CHAR   achFinalDate[12];
    WPDCF77Data *somThis;

    somThis = ((PWINDOWDATA)WinQueryWindowPtr (hwnd, QWL_USER))->somThis;

    GetDateTime (pdt, MODE_PM | MODE_YEAR_2D, achTime, achFinalDate);

    WinQueryWindowRect (hwnd, &rcl);
    if (!(_ulPresence & PRESENCE_DISP_MINIMIZE) || (ulMode == DCLK_ALL))
        WinFillRect (_pIData->hps, &rcl, _pIData->sclrBG.ulSurface);

    rcl.yBottom += (rcl.yTop - rcl.yBottom)/10;
    rcl.yTop    -= (rcl.yTop - rcl.yBottom)/20;
    rcl.xLeft   += (rcl.xRight - rcl.xLeft)/20;
    rcl.xRight  -= (rcl.xRight - rcl.xLeft)/20;

    switch (_ulPresence & (PRESENCE_DISP_TIME | PRESENCE_DISP_DATE))
        {
        case PRESENCE_DISP_DATE:
            rclDate = rcl;
            break;

        case PRESENCE_DISP_TIME | PRESENCE_DISP_DATE:
            if (!(_ulPresence & PRESENCE_DISP_MINIMIZE))
                {
                rclTime = rclDate = rcl;
                rclTime.yBottom = rclDate.yTop = (rcl.yTop + rcl.yBottom) / 2;
                rclTime.yBottom += (rclTime.yTop - rclTime.yBottom)/10;
                rclDate.yTop    -= (rclTime.yTop - rclTime.yBottom)/10;
                break;
                } /* else: weiter */

        case PRESENCE_DISP_TIME:
            rclTime = rcl;
            break;
        }

    if (_ulPresence & PRESENCE_DISP_MINIMIZE)
        {
        /* Iconisiert: Refresh nur bei neuer Minute */
        if (ulMode == DCLK_ALL)
            {
            GpiSetCharSet (_pIData->hps, LCID_TIME);
            achTime[5] = '\0';
            ClkDrawString (_pIData->hps, _pIData->ulclrTimeText, achTime, &rcl);
            }
        }
    else
        {
        if (_ulPresence & PRESENCE_DISP_TIME)
            {
            GpiSetCharSet (_pIData->hps, LCID_TIME);
            ClkDrawString (_pIData->hps, _pIData->ulclrTimeText, achTime, &rclTime);
            }
        }

    if (_ulPresence & PRESENCE_DISP_DATE && !(_ulPresence & PRESENCE_DISP_MINIMIZE))
        {
        GpiSetCharSet (_pIData->hps, LCID_DATE);
        ClkDrawString (_pIData->hps, _pIData->ulclrDateText, achFinalDate, &rclDate);
        }

    return;
    }

/*******************************************************************\
    ClkRefresh: Initiiert einen Repaint der Uhr
    Eingang: somThis: Zeiger auf Instanzdaten
\*******************************************************************/
VOID ClkRefresh (WPDCF77Data *somThis)
    {
    _pIData->bBufferDirty = TRUE;
    SetRGBColors (somThis);
    SetFonts (somThis);
    WinInvalidateRect (_pIData->hwndClient, NULL, TRUE);
    return;
    }

/*******************************************************************\
    ClkShowFrameControls: Titlebar ein-/ausschalten
    Eingang: hwndFrame: Window handle des Frame-Windows
             bShow:     TRUE:  einschalten
                        FALSE: ausschalten
\*******************************************************************/
VOID ClkShowFrameControls (HWND hwndFrame, BOOL bShow)
    {
    WPDCF77     *somSelf;
    WPDCF77Data *somThis;
    HWND        hwnd;

    somSelf = (WPDCF77 *)WinQueryWindowPtr (hwndFrame, QWL_USER);
    somThis = WPDCF77GetData (somSelf);

    if (bShow)
        hwnd = hwndFrame;
    else
        hwnd = HWND_OBJECT;

    WinSetParent (_pIData->hwndTitleBar, hwnd, bShow);
    WinSetParent (_pIData->hwndSysMenu,  hwnd, bShow);
    WinSetParent (_pIData->hwndMinMax,   hwnd, bShow);

    WinSendMsg (hwndFrame, WM_UPDATEFRAME,
                MPFROMLONG (FCF_TITLEBAR | FCF_SYSMENU | FCF_MINMAX | FCF_MENU),
                MPVOID);

    if (bShow)
        WinInvalidateRect (hwndFrame, NULL, TRUE);
    return;
    }

/*******************************************************************\
    SetFonts: FATTR-Struktur fÅr die Fonts aus Instanzdaten kopieren
    Eingang: somThis: Zeiger auf Instanzdaten
\*******************************************************************/
VOID SetFonts (WPDCF77Data *somThis)
    {
    /* Font aus Instanzdaten laden */
    memcpy (&_pIData->fAttrDate, &_fAttrD, sizeof (FATTRS));
    memcpy (&_pIData->fAttrTime, &_fAttrT, sizeof (FATTRS));
    strcpy (_pIData->szFontFamilyDate, _szFontFamilyD);
    strcpy (_pIData->szFontFamilyTime, _szFontFamilyT);

    return;
    }

/*******************************************************************\
    SetRGBColors: Schattierungen der RGB-Farben berechnen
    Eingang: somThis: Zeiger auf Instanzdaten
\*******************************************************************/
VOID SetRGBColors (WPDCF77Data *somThis)
    {

    /* Farbwerte umkopieren */
    _pIData->sclrFace.ulSurface       = _clrFace;
    _pIData->sclrBG.ulSurface         = _clrBackgnd;
    _pIData->sclrHHand.ulSurface      = _clrHHand;
    _pIData->sclrMHand.ulSurface      = _clrMHand;
    _pIData->sclrMajorTicks.ulSurface = _clrTick;
    _pIData->sclrMinorTicks.ulSurface = _clrFace;
    _pIData->sclrRing.ulSurface       = _clrFace;
    _pIData->sclrDate.ulSurface       = _clrDateOnAnalog;
    _pIData->ulclrTransparent         = _clrTransparent;
    _pIData->ulclrDateText            = _clrDateText;
    _pIData->ulclrTimeText            = _clrTimeText;

    /* Farbtabellen fÅllen */
    ShadeLight (&_pIData->sclrMajorTicks);
    ShadeLight (&_pIData->sclrMinorTicks);
    ShadeLight (&_pIData->sclrFace);
    ShadeLight (&_pIData->sclrRing);
    ShadeLight (&_pIData->sclrHHand);
    ShadeLight (&_pIData->sclrMHand);
    ShadeLight (&_pIData->sclrBG);
    ShadeLight (&_pIData->sclrDate);

    _pIData->sclrHHand.ulShade = RGB_BLACK;
    _pIData->sclrMHand.ulShade = RGB_BLACK;

    return;
    }

/*******************************************************************\
    ShadeLight: Schattierung einer Farbe bestimmen und in
                COLORS-Struktur eintragen
    Eingang: psColors: Zeiger auf COLORS-Struktur
\*******************************************************************/
VOID ShadeLight (PCOLORS psColors)
    {
    typedef union _RGBLONG
        {
        RGB     rgb;
        LONG    lng;
        } RGBLONG;
    RGBLONG  rgbSurface, rgbShade, rgbLight;

    /* Zuerst alle Farben lîschen */
    rgbSurface.lng = rgbShade.lng = rgbLight.lng = 0L;

    /* Surface-Farbe laden */
    rgbSurface.lng = psColors->ulSurface;

    /* Schatten berechnen */
    rgbShade.rgb.bBlue  = ShadeRGBByte (rgbSurface.rgb.bBlue);
    rgbShade.rgb.bRed   = ShadeRGBByte (rgbSurface.rgb.bRed);
    rgbShade.rgb.bGreen = ShadeRGBByte (rgbSurface.rgb.bGreen);

    /* Helle Farbe berechnen */
    rgbLight.rgb.bBlue  = LightRGBByte (rgbSurface.rgb.bBlue);
    rgbLight.rgb.bRed   = LightRGBByte (rgbSurface.rgb.bRed);
    rgbLight.rgb.bGreen = LightRGBByte (rgbSurface.rgb.bGreen);

    /* Farben umspeichern fÅr RÅckgabe */
    psColors->ulShade = rgbShade.lng;
    psColors->ulLight = rgbLight.lng;

    return;
    }

/*******************************************************************\
    ShadeRGBByte: RGB-Wert des Schattens einer Grundfarbe bestimmen
    Eingang: brgb: Grundfarbe: Normale Helligkeit
    return:        Grundfarbe: Schattierte Helligkeit
\*******************************************************************/
BYTE ShadeRGBByte (BYTE brgb)
    {
    #define SHADER   ( (BYTE) 0x50)

    return (brgb > SHADER) ? (brgb - SHADER) : 0;
    }

/*******************************************************************\
    LightRGBByte: RGB-Wert einer Grundfarbe bei Beleuchtung bestimmen
    Eingang: brgb: Grundfarbe: Normale Helligkeit
    return:        Grundfarbe: Helligkeit bei Beleuchtung
\*******************************************************************/
BYTE LightRGBByte (BYTE brgb)
    {

    #define LIGHTER  ( (BYTE) 0x40)

    return (brgb < (0xFF - LIGHTER)) ? (brgb + LIGHTER) : 0xFF;
    }

