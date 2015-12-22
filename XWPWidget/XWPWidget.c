/***************************************************************************\
 *
 * PROGRAMMNAME: XWPWIDGET
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: XWPWIDGET
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *
 * FUNKTIONEN:
 * -----------
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    xx-xx-xx  First release
 *  2.10    05-12-02  Handling of shift-keys
 *  2.40    02-08-03  Dual wheel support
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *
 *  Copyright (C) noller & breining software 2001..2004
 *
\***************************************************************************/
#pragma strings(readonly)

/*
 *  Suggested #include order:
 *  1)  os2.h
 *  2)  C library headers
 *  3)  setup.h (code generation and debugging options)
 *  4)  headers in helpers\
 *  5)  at least one SOM implementation header (*.ih)
 *  6)  dlgids.h, headers in shared\ (as needed)
 *  7)  headers in implementation dirs (e.g. filesys\, as needed)
 *  8)  #pragma hdrstop and then more SOM headers which crash with precompiled headers
 */

#define INCL_DOSMODULEMGR
#define INCL_DOSSEMAPHORES
#define INCL_DOSPROCESS
#define INCL_DOSERRORS

#define INCL_WINWINDOWMGR
#define INCL_WINFRAMEMGR
#define INCL_WINDIALOGS
#define INCL_WININPUT
#define INCL_WINSWITCHLIST
#define INCL_WINRECTANGLES
#define INCL_WINPOINTERS
#define INCL_WINSYS
#define INCL_WINLISTBOXES
#define INCL_WINENTRYFIELDS
#define INCL_WINSTDSPIN
#define INCL_WINSHELLDATA
#define INCL_WINWORKPLACE

#define INCL_GPILOGCOLORTABLE
#define INCL_GPILCIDS
#define INCL_GPIPRIMITIVES
#define INCL_GPIPATHS
#define INCL_GPITRANSFORMS
#include <os2.h>

// C library headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <som.h>
#include <WPObject.h>

#pragma info(noeff)

#include "AMouseGlobal.h"
#include "res.h"
#include <log.h>

// generic headers
#include <setup.h>                         // code generation and debugging options
#include <helpers\comctl.h>                // common controls (window procs)
#include <helpers\dosh.h>                  // Control Program helper routines
#include <helpers\gpih.h>                  // GPI helper routines
// #include "helpers\prfh.h"               // INI file helper routines;
                                           // this include is required for some
                                           // of the structures in shared\center.h
#include <helpers\winh.h>                  // PM helper routines
#include <helpers\xstring.h>               // extended string helpers

#include <shared\center.h>                 // public XCenter interfaces
#include <shared\common.h>                 // XWorkplace include file

#include <config\drivdlgs.h>               // driver configuration dialogs

#pragma hdrstop                            // VAC++ keeps crashing otherwise

/*******************************************************************\
     Private definitions
\*******************************************************************/
#define MATLF_SIZE (sizeof (MATRIXLF) / sizeof (LONG))

#define PANEL_MAIN      1000
#define CCHMAXTOOLTIP   150

const char *INIAPP_XWORKPLACE    = "XWorkplace";
const char *INIKEY_LANGUAGECODE  = "Language";
const char *DEFAULT_LANGUAGECODE = "001";

MRESULT EXPENTRY fnwpAMouseWidget (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
VOID EXPENTRY WgtShowSettingsDlg (PWIDGETSETTINGSDLGDATA pData);
VOID APIENTRY updateThread (ULONG ulParm);

/*******************************************************************\
     XCenter widget class definition
\*******************************************************************/

/*
 *      This contains the name of the PM window class and
 *      the XCENTERWIDGETCLASS definition(s) for the widget
 *      class(es) in this DLL.
 *
 *      The address of this structure (or an array of these
 *      structures, if there were several widget classes in
 *      this plugin) is returned by the "init" export
 *      (WgtInitModule).
 */

#define WNDCLASS_WIDGET_AMOUSE  "XWPAMouseWidget"

static XCENTERWIDGETCLASS G_WidgetClasses[] =
    {
    WNDCLASS_WIDGET_AMOUSE,                 // PM window class name
    0,                                      // additional flag, not used here
    "AMouseWidget",                         // internal widget class name
    "AMouse Widget",                        // widget class name displayed to user
    WGTF_UNIQUEPERXCENTER | WGTF_TOOLTIP,   // widget class flags
    WgtShowSettingsDlg                      // settings dialog
    };

/*******************************************************************\
     Function imports from XFLDR.DLL
\*******************************************************************/
PCMNQUERYDEFAULTFONT pcmnQueryDefaultFont = NULL;
PCTRFREESETUPVALUE   pctrFreeSetupValue   = NULL;
PCTRPARSECOLORSTRING pctrParseColorString = NULL;
PCTRSCANSETUPSTRING  pctrScanSetupString  = NULL;
PDRV_SPRINTF         pdrv_sprintf         = NULL;
PGPIHCREATEFONT      pgpihCreateFont      = NULL;
PGPIHDRAW3DFRAME     pgpihDraw3DFrame     = NULL;
PGPIHMATCHFONT       pgpihMatchFont       = NULL;
PGPIHSETPOINTSIZE    pgpihSetPointSize    = NULL;
PGPIHSPLITPRESFONT   pgpihSplitPresFont   = NULL;
PGPIHSWITCHTORGB     pgpihSwitchToRGB     = NULL;
PWINHFREE            pwinhFree            = NULL;
PWINHQUERYPRESCOLOR  pwinhQueryPresColor  = NULL;
PWINHQUERYWINDOWFONT pwinhQueryWindowFont = NULL;
PWINHSETWINDOWFONT   pwinhSetWindowFont   = NULL;
PXSTRCAT             pxstrcat             = NULL;
PXSTRCLEAR           pxstrClear           = NULL;
PXSTRINIT            pxstrInit            = NULL;

RESOLVEFUNCTION G_aImports[] =
    {
    "cmnQueryDefaultFont", (PFN*)&pcmnQueryDefaultFont,
    "ctrFreeSetupValue",   (PFN*)&pctrFreeSetupValue,
    "ctrParseColorString", (PFN*)&pctrParseColorString,
    "ctrScanSetupString",  (PFN*)&pctrScanSetupString,
    "drv_sprintf",         (PFN*)&pdrv_sprintf,
    "gpihCreateFont",      (PFN*)&pgpihCreateFont,
    "gpihDraw3DFrame",     (PFN*)&pgpihDraw3DFrame,
    "gpihMatchFont",       (PFN*)&pgpihMatchFont,
    "gpihSetPointSize",    (PFN*)&pgpihSetPointSize,
    "gpihSplitPresFont",   (PFN*)&pgpihSplitPresFont,
    "gpihSwitchToRGB",     (PFN*)&pgpihSwitchToRGB,
    "winhFree",            (PFN*)&pwinhFree,
    "winhQueryPresColor",  (PFN*)&pwinhQueryPresColor,
    "winhQueryWindowFont", (PFN*)&pwinhQueryWindowFont,
    "winhSetWindowFont",   (PFN*)&pwinhSetWindowFont,
    "xstrcat",             (PFN*)&pxstrcat,
    "xstrClear",           (PFN*)&pxstrClear,
    "xstrInit",            (PFN*)&pxstrInit
    };

/*******************************************************************\
     Private widget instance data
\*******************************************************************/
PMOUSEDATA pShMemMouseData    = NULL;
HMTX       hmtxWheelThread    = NULLHANDLE;     // semaphore for synchronisation of strucMouseData
HEV        hevXWPWidgetUpdate = NULLHANDLE;     // semaphore for updating data in strucMouseData
HMODULE    hModWidget         = NULLHANDLE;     // module handle of widget dll
HMODULE    hModXFldr          = NULLHANDLE;     // module handle of XFolder dll
CHAR       szHelpFile[CCHMAXPATH];
CHAR       szDLLFile[CCHMAXPATH];
CHAR       szLangCode[4];

typedef struct _WIDGETSETUP
    {
    LONG            lcolBackground,             // background color
                    lcolForeground;             // foreground color (for text)
    PSZ             pszFont;                    // font; allocated by local malloc
    } WIDGETSETUP, *PWIDGETSETUP;

typedef struct _WIDGETPRIVATE
    {
    BOOL            bTerminateThread;
    TID             tid;

    ULONG           ulPointSize;
    FATTRS          fattrs;
    FONTMETRICS     fm;
    BOOL            fFontMatched;
    LONG            lcidFont;

    CHAR            szTooltipText[CCHMAXTOOLTIP];

    WIDGETSETUP     setup;
    } WIDGETPRIVATE, *PWIDGETPRIVATE;

PSZ     szAudioDllName        = "nbaudio.dll";
HMODULE hModAudio             = NULLHANDLE;     // module handle of nbaudio.dll
PFN     pfnMciGetMasterVolume = NULL;

/*******************************************************************\
    Try to load nbaudio dll and resolve needed entry points
    Input:  none
    Return: none
\*******************************************************************/
VOID loadMMOS2 (VOID)
    {
    APIRET rc;
    ULONG  ulType;

    if (pfnMciGetMasterVolume)
        return;

    rc = DosLoadModule (NULL, 0, szAudioDllName, &hModAudio);
    if (rc == NO_ERROR)
        {
        rc = DosQueryProcAddr (hModAudio, 0, "MciGetMasterVolume", &pfnMciGetMasterVolume);
        if (rc != NO_ERROR)
            pfnMciGetMasterVolume = NULL;
        }

    return;
    }

/*******************************************************************\
    Initializes shared memory and create semaphores.
    Starts thread that waits for shared memory changes.
    Input:  pWidget: widget class definition
    Return: TRUE:  succesful initialized
            FALSE: otherwise
\*******************************************************************/
BOOL WgtInitData (PXCENTERWIDGET pWidget)
    {
    TID tid;
    APIRET rc;

    /* Allocate / initialize shared memory */
    if (DosGetNamedSharedMem ((PPVOID)&pShMemMouseData, SHMEMNAME, PAG_READ | PAG_WRITE))
        {
        if (DosAllocSharedMem ((PPVOID)&pShMemMouseData, SHMEMNAME, sizeof (MOUSEDATA), PAG_COMMIT | PAG_WRITE | PAG_READ))
            {
            pShMemMouseData = NULL;                      // Fehler: Anlegen des Shared-Memory nicht m”glich
            return FALSE;
            }
        else
            memset (pShMemMouseData, '\0', sizeof (MOUSEDATA));
        }

    /* open/create semaphore for synchronisation of strucMouseData */
    if (!hmtxWheelThread)
        if (DosOpenMutexSem (SEMNAMEMTX, &hmtxWheelThread))
            DosCreateMutexSem (SEMNAMEMTX, &hmtxWheelThread, 0L, FALSE);

    /* open/create semaphore for thread unblocking */
    if (hmtxWheelThread)
        {
        if (!hevXWPWidgetUpdate)
            if (DosOpenEventSem (SEMNAMEEVT_WIDGET, &hevXWPWidgetUpdate))
                if (DosCreateEventSem (SEMNAMEEVT_WIDGET, &hevXWPWidgetUpdate, DC_SEM_SHARED, TRUE))
                    return FALSE;
        }
    else
        return FALSE;

    rc = DosCreateThread (&(((PWIDGETPRIVATE)(pWidget->pUser))->tid), (PFNTHREAD)updateThread, (ULONG)pWidget, CREATE_READY, 0x4000);

    return TRUE;
    }

/*******************************************************************\
    returns PSZ to three-digit language code (e. g. "001").
    points to a global variable; derived from cmnQueryLanguageCode
    in common.c of XWorkplace code
    Input:  pWidget: widget class definition
    Return: TRUE:  succesful initialized
            FALSE: otherwise
\*******************************************************************/
PSZ WgtQueryLanguageCode (VOID)
    {
    if (szLangCode[0] == '\0')
        PrfQueryProfileString (HINI_USERPROFILE,
                               (PSZ)INIAPP_XWORKPLACE,
                               (PSZ)INIKEY_LANGUAGECODE,
                               (PSZ)DEFAULT_LANGUAGECODE,
                               (PVOID)szLangCode,
                               sizeof (szLangCode));

    szLangCode[3] = '\0';

    return szLangCode;
    }

/*******************************************************************\
    used to retrieve the fully qualified file name of the widget DLL
    Input:  pszPath: target buffer
    Return: full path of widget dll
\*******************************************************************/
PSZ WgtQueryWidgetModuleFilename (VOID)
    {
    APIRET rc =  DosQueryModuleName (hModWidget, CCHMAXPATH, szDLLFile);
    return (rc == NO_ERROR) ? szDLLFile : NULL;
    }

/*******************************************************************\
    this routine returns the path of where the widgets are installed,
    i.e. the parent directory of where the widget dll
    resides, without a trailing backslash.

    The buffer to copy this to is assumed to be CCHMAXPATH in size.
    Input:  pszPath: target buffer
    Return: TRUE:  path succesfully written
            FALSE: error occurred
\*******************************************************************/
BOOL WgtQueryXWPWidgetBasePath (PSZ pszPath)
    {
    BOOL brc = FALSE;
    const char *pszDLL = WgtQueryWidgetModuleFilename ();

    if (pszDLL)
        {
        PSZ pszLastSlash = strrchr (pszDLL, '\\');

        strncpy (pszPath, pszDLL, pszLastSlash-pszDLL);
        pszPath[pszLastSlash-pszDLL] = '\0';
        brc = TRUE;
        }

    return brc;
    }

/*******************************************************************\
    Toggles the scrolling direction by changing shared memory
\*******************************************************************/
VOID WgtToggleScrollDir (VOID)
    {
    if (pShMemMouseData)
        {
        DosRequestMutexSem (hmtxWheelThread, (ULONG)SEM_INDEFINITE_WAIT);

        if (pShMemMouseData->ulCurrScrollDir == SCROLL_DIR_VERT)
            pShMemMouseData->ulCurrScrollDir = SCROLL_DIR_HORZ;
        else
            pShMemMouseData->ulCurrScrollDir = SCROLL_DIR_VERT;

        DosReleaseMutexSem (hmtxWheelThread);
        DosPostEventSem (hevXWPWidgetUpdate);
        }

    return;
    }

/*******************************************************************\
    calculates value for ulScrollNum, if wheel was turned to adjust.
    minimal value is 1, maximum is 10
    Input:  msg:         window message received
            lWheelTurns: number of wheel turns detected
\*******************************************************************/
VOID WgtAdjustScrollNum (ULONG msg, LONG lWheelTurns)
    {
    if (pShMemMouseData)
        {
        LONG l;

        DosRequestMutexSem (hmtxWheelThread, (ULONG)SEM_INDEFINITE_WAIT);
        l = (LONG)pShMemMouseData->ulScrollNum;
        switch (msg)
            {
            case SPBM_SPINUP:
                l += lWheelTurns;
                if (l > 10)
                    l = 10;
                break;

            case SPBM_SPINDOWN:
                l -= lWheelTurns;
                if (l < 1)
                    l = 1;
                break;
            }

        pShMemMouseData->ulScrollNum = (ULONG)l;

        DosReleaseMutexSem (hmtxWheelThread);
        DosPostEventSem (hevXWPWidgetUpdate);
        }

    return;
    }

/*******************************************************************\
    scans setup string of widget and parses setup values
    Input:  pcszSetupString: setup string of widget
    Output: pSetup:          widget instance setup data
\*******************************************************************/
VOID WgtScanSetup (const char *pcszSetupString, PWIDGETSETUP pSetup)
    {
    PSZ psz;

    // background color
    psz = pctrScanSetupString (pcszSetupString, "BGNDCOL");
    if (psz)
        {
        pSetup->lcolBackground = pctrParseColorString (psz);
        pctrFreeSetupValue (psz);
        }
    else
        // default color:
        pSetup->lcolBackground = WinQuerySysColor (HWND_DESKTOP, SYSCLR_DIALOGBACKGROUND, 0);

    // text color:
    psz = pctrScanSetupString (pcszSetupString, "TEXTCOL");
    if (psz)
        {
        pSetup->lcolForeground = pctrParseColorString (psz);
        pctrFreeSetupValue (psz);
        }
    else
        pSetup->lcolForeground = WinQuerySysColor (HWND_DESKTOP, SYSCLR_WINDOWSTATICTEXT, 0);

    // font:
    // we set the font presparam, which automatically
    // affects the cached presentation spaces
    psz = pctrScanSetupString (pcszSetupString, "FONT");
    if (psz)
        {
        pSetup->pszFont = strdup (psz);
        pctrFreeSetupValue (psz);
        }
    // else: leave this field null

    return;
    }


/*******************************************************************\
    creates widget setup string
    Input:  pSetup:    widget instance setup data
    Output: pstrSetup: setup string of widget
\*******************************************************************/
VOID WgtSaveSetup (PXSTRING pstrSetup, PWIDGETSETUP pSetup)
    {
    CHAR szTemp[100];

    // PSZ     psz = 0;
    pxstrInit (pstrSetup, 100);

    pdrv_sprintf (szTemp, "BGNDCOL=%06lX;", pSetup->lcolBackground);
    pxstrcat (pstrSetup, szTemp, 0);

    pdrv_sprintf (szTemp, "TEXTCOL=%06lX;", pSetup->lcolForeground);
    pxstrcat (pstrSetup, szTemp, 0);

    if (pSetup->pszFont)
    {
        // non-default font:
        pdrv_sprintf (szTemp, "FONT=%s;", pSetup->pszFont);
        pxstrcat (pstrSetup, szTemp, 0);
    }

    return;
}

/*******************************************************************\
    create and save setup string of widget
    Input:  hwnd:     window handle of widget
            pPrivate: widget instance data
\*******************************************************************/
VOID WgtSaveSetupAndSend (HWND hwnd, PWIDGETPRIVATE pPrivate)
    {
    XSTRING strSetup;
    WgtSaveSetup (&strSetup, &pPrivate->setup);

    if (strSetup.ulLength)
        {
        WinSendMsg (WinQueryWindow (hwnd, QW_PARENT),
                    XCM_SAVESETUP,
                    (MPARAM)hwnd,
                    (MPARAM)strSetup.psz);
        }

    pxstrClear (&strSetup);

    return;
    }

/*******************************************************************\
    handles WM_CREATE message
    Input: hwnd:    window handle of widget
           pWidget: widget instance data
    Return: TRUE:  error occurred
            FALSE: successful
\*******************************************************************/
BOOL WgtCreate (HWND hwnd, PXCENTERWIDGET pWidget)
    {
    PWIDGETPRIVATE pPrivate;

    WinSetWindowPtr (hwnd, QWL_USER, pWidget);
    pPrivate = malloc (sizeof (WIDGETPRIVATE));
    memset (pPrivate, '\0', sizeof (WIDGETPRIVATE));
    pWidget->pUser = pPrivate;

    WgtScanSetup (pWidget->pcszSetupString, &pPrivate->setup);

    // set window font (affects all the cached presentation spaces used)
    if (pPrivate->setup.pszFont == NULL)
        pPrivate->setup.pszFont = strdup (pcmnQueryDefaultFont ());  // default XWorkplace font
    pwinhSetWindowFont (hwnd, pPrivate->setup.pszFont);

    // enable context menu help
    if (WgtQueryXWPWidgetBasePath (szHelpFile))
        {
        sprintf (szHelpFile + strlen (szHelpFile),
                 "\\XAMou%s.hlp",
                 WgtQueryLanguageCode ());
        pWidget->pcszHelpLibrary = szHelpFile;
        pWidget->ulHelpPanelID   = PANEL_MAIN;
        }

    // Aufr„umen ???
    if ((!pWidget) || (!pWidget->pfnwpDefWidgetProc))
        return TRUE;

    if (!WgtInitData (pWidget))
        return TRUE;

    return FALSE;
    }

/*******************************************************************\
    The XCenter communicates with widgets through WM_CONTROL
    messages. At the very least, the widget should respond to
    XN_QUERYSIZE because otherwise it will be given some dumb
    default size.
    Input:  hwnd:    window handle of widget
            mp1:     mp1 of WM_CONTROL
            mp2:     mp2 of WM_CONTROL
    Return: TRUE:  succesful initialized
            FALSE: otherwise
\*******************************************************************/
BOOL WgtControl (HWND hwnd, MPARAM mp1, MPARAM mp2)
    {
    BOOL           bRC          = FALSE;
    USHORT         usID         = SHORT1FROMMP (mp1),
                   usNotifyCode = SHORT2FROMMP (mp1);
    PXCENTERWIDGET pWidget      = NULL;
    PWIDGETPRIVATE pPrivate     = NULL;

    if ((pWidget = (PXCENTERWIDGET)WinQueryWindowPtr (hwnd, QWL_USER)) != NULL)
        pPrivate = (PWIDGETPRIVATE)pWidget->pUser;

    switch (usID)
        {
        case ID_XCENTER_CLIENT:
            // this is from the XCenter client
            switch (usNotifyCode)
                {
                // XN_QUERYSIZE: XCenter wants to know our size.
                case XN_QUERYSIZE:
                    {
                    PSIZEL pszl = (PSIZEL)mp2;
                    pszl->cx = 60;      // desired width
                    pszl->cy = 20;      // desired minimum height
                    bRC = TRUE;
                    break;
                    }
                }
            break;

        case ID_XCENTER_TOOLTIP:
            switch (usNotifyCode)
                {
                case TTN_NEEDTEXT:
                    if (pPrivate)
                        {
                        PTOOLTIPTEXT pttt = (PTOOLTIPTEXT)mp2;
                        pttt->pszText = pPrivate->szTooltipText;
                        pttt->ulFormat = TTFMT_PSZ;
                        }
                    break;
                }
            break;
        }

    return bRC;
    }

/*******************************************************************\
    Loads the XCenter default font and initializes instance data
    structure
    Input:  pWidget: widget instance data
            hps:     presentation space handle
\*******************************************************************/
VOID WgtLoadFont (PXCENTERWIDGET pWidget, HPS hps)
    {
    PSZ            pszFace;
    PWIDGETPRIVATE pPrivate = (PWIDGETPRIVATE)pWidget->pUser;

    if (!pPrivate->fFontMatched)
        {
        pgpihSplitPresFont ("9.WarpSans",
                            &pPrivate->ulPointSize,
                            &pszFace);

        pgpihMatchFont (hps,
                        pPrivate->ulPointSize,
                        FALSE,
                        pszFace,
                        0,
                        &pPrivate->fattrs,
                        &pPrivate->fm);
        pPrivate->fFontMatched = TRUE;
        }

    pPrivate->lcidFont = pgpihCreateFont (hps, &pPrivate->fattrs);

    GpiSetCharSet (hps, pPrivate->lcidFont);
    if (pPrivate->fm.fsDefn & FM_DEFN_OUTLINE)
        pgpihSetPointSize (hps, pPrivate->ulPointSize);

    return;
    }

/*******************************************************************\
    Used in WgtPaint: paints scroll-mode bitmap
    Input:  hPS:   presentation space handle
            prcl:  paint rectangle
\*******************************************************************/
VOID WgtPaintBmp (HPS hPS, PRECTL prcl)
    {
    ULONG             ulBmpId;
    HBITMAP           hBmp;
    POINTL            aptl[4];
    BITMAPINFOHEADER2 bmpInfo;

    GpiSetBackColor (hPS, 0L);
    GpiSetBackMix (hPS, BM_SRCTRANSPARENT);

    switch (pShMemMouseData->ulScrollMode)
        {
        case SCROLL_MODE_NONE:
            ulBmpId = ID_NOBMP;
            break;

        case SCROLL_MODE_STD:
            ulBmpId = ID_STBMP;
            break;

        case SCROLL_MODE_LINE:
            ulBmpId = ID_LNBMP;
            break;

        case SCROLL_MODE_PAGE:
            ulBmpId = ID_PGBMP;
            break;

        case SCROLL_MODE_VOLUME:
            ulBmpId = ID_VOLBMP;
            break;
        }

    hBmp = GpiLoadBitmap (hPS, hModWidget, ulBmpId, 0, 0);
    bmpInfo.cbFix = sizeof (BITMAPINFOHEADER2);
    GpiQueryBitmapInfoHeader (hBmp, &bmpInfo);

    aptl[0].x = prcl->xLeft;
    aptl[0].y = prcl->yBottom;
    aptl[1].x = prcl->xRight;
    aptl[1].y = prcl->yTop;
    aptl[2].x = 0;
    aptl[2].y = 0;
    aptl[3].x = bmpInfo.cx;
    aptl[3].y = bmpInfo.cy;

    GpiWCBitBlt (hPS, hBmp, 4, aptl, ROP_SRCCOPY, BBO_IGNORE);
    GpiDeleteBitmap (hBmp);

    return;
    }

/*******************************************************************\
    Used in WgtPaint: draws scroll direction arrow
    Input:  hPS:   presentation space handle
            prcl:  paint rectangle
            ulDir: scroll direction: SCROLL_DIR_VERT: vertical
                                     SCROLL_DIR_HORZ: horizontal
\*******************************************************************/
VOID WgtPaintArrow (HPS hps, PRECTL prcl, ULONG ulDir)
    {
    static FIXED    fxWidth  = MAKEFIXED (2, 0);
    static MATRIXLF matlfStd =
        {
        MAKEFIXED (1, 0),   MAKEFIXED (0,  0),   0,
        MAKEFIXED (0, 0),   MAKEFIXED (1,  0),   0,
        0,                  0,                   1
        };
    static MATRIXLF matlfVert =
        {
        MAKEFIXED (1, 0),   MAKEFIXED (0,  0),   0,
        MAKEFIXED (0, 0),   MAKEFIXED (1,  0),   0,
        9,                 0,                   1
        };
    static MATRIXLF matlfHorz   =
        {
        MAKEFIXED (0, 0),   MAKEFIXED (-1, 0),   0,
        MAKEFIXED (1, 0),   MAKEFIXED ( 0, 0),   0,
        0,                  11,                  1
        };

    POINTL ptl;
    LONG   lColor;

    lColor = 0xFFFF00;

    if (ulDir == SCROLL_DIR_VERT)
        GpiSetModelTransformMatrix (hps, MATLF_SIZE, &matlfVert, TRANSFORM_REPLACE);
    else
        GpiSetModelTransformMatrix (hps, MATLF_SIZE, &matlfHorz, TRANSFORM_REPLACE);
    GpiSetLineWidth (hps, fxWidth);
    GpiSetColor (hps, lColor);

    GpiBeginPath (hps, 1);

    // vertical line
    ptl.x = prcl->xLeft;     ptl.y = prcl->yBottom;
    GpiMove (hps, &ptl);
    ptl.y = prcl->yTop;
    GpiLine (hps, &ptl);

    // bottom arrow
    ptl.x = prcl->xLeft-2;   ptl.y = prcl->yTop/3;
    GpiMove (hps, &ptl);
    ptl.x = prcl->xLeft;     ptl.y = prcl->yBottom;
    GpiLine (hps, &ptl);
    ptl.x = prcl->xLeft+2;   ptl.y = prcl->yTop/3;
    GpiLine (hps, &ptl);

    // top arrow
    ptl.x = prcl->xLeft-2;   ptl.y = 2*prcl->yTop/3;
    GpiMove (hps, &ptl);
    ptl.x = prcl->xLeft;     ptl.y = prcl->yTop;
    GpiLine (hps, &ptl);
    ptl.x = prcl->xLeft+2;   ptl.y = 2*prcl->yTop/3;
    GpiLine (hps, &ptl);

    GpiEndPath (hps);
    GpiFillPath (hps, 1, 0);
    GpiSetModelTransformMatrix (hps, MATLF_SIZE, &matlfStd, TRANSFORM_REPLACE);

    return;
    }

PCHAR WgtAddWheelModeText (PCHAR szString, ULONG ulMode)
    {
    switch (ulMode)
        {
        case SCROLL_MODE_NONE:
            strcat (szString, "none");
            break;

        case SCROLL_MODE_STD:
            strcat (szString, "scroll");
            break;

        case SCROLL_MODE_LINE:
            strcat (szString, "cursor");
            break;

        case SCROLL_MODE_PAGE:
            strcat (szString, "page");
            break;

        case SCROLL_MODE_VOLUME:
            strcat (szString, "volume");
            break;
        }

    return szString;
    }

/*******************************************************************\
    handles the WM_DRAW message
    Input:  hwnd:    window handle of widget
            pWidget: widget instance data
\*******************************************************************/
VOID WgtPaint (HWND hwnd, PXCENTERWIDGET pWidget)
    {
    CHAR           szText[10];
    RECTL          rcl;
    HPS            hps = WinBeginPaint (hwnd, NULLHANDLE, NULL);
    PWIDGETPRIVATE pPrivate = (PWIDGETPRIVATE)pWidget->pUser;

    if (hps && pPrivate)
        {
        RECTL rclWin;

        pPrivate->szTooltipText[0] = '\0';

        WgtLoadFont (pWidget, hps);

        // now paint frame
        WinQueryWindowRect (hwnd, &rclWin);

        pgpihSwitchToRGB (hps);

        WinFillRect (hps,
                     &rclWin,                // exclusive
                     pPrivate->setup.lcolBackground);

        // draw border
        if (pWidget->pGlobals->flDisplayStyle & XCS_SUNKBORDERS)
            {
            ULONG ulBorder=1;
            RECTL rcl2;

            memcpy (&rcl2, &rclWin, sizeof(RECTL));
            rcl2.xRight--;
            rcl2.yTop--;

            pgpihDraw3DFrame (hps,
                              &rcl2,
                              ulBorder,
                              pWidget->pGlobals->lcol3DDark,
                              pWidget->pGlobals->lcol3DLight);

            // update rclWin structure to available drawing rectangle and
            // convert inclusive-exclusive rectangle to inclusive-inclusive
            rclWin.xLeft   += ulBorder;
            rclWin.yBottom += ulBorder;
            rclWin.xRight  -= ulBorder+1;
            rclWin.yTop    -= ulBorder+1;
            }

        // draw graphics
        rcl.xLeft   = rclWin.xRight - 19;
        rcl.yBottom = rclWin.yBottom;
        rcl.xRight  = rclWin.xRight;
        rcl.yTop    = rclWin.yTop;

        WgtPaintBmp (hps, &rcl);

        if (pShMemMouseData->ulScrollMode == SCROLL_MODE_STD  ||
            pShMemMouseData->ulScrollMode == SCROLL_MODE_LINE ||
            pShMemMouseData->ulScrollMode == SCROLL_MODE_PAGE)
            {
            strcpy (pPrivate->szTooltipText, "Direction: ");
            if (pShMemMouseData->ulWheelCount <= 1)
                {
                if (pShMemMouseData->ulCurrScrollDir == SCROLL_DIR_VERT)
                    strcat (pPrivate->szTooltipText, "vertical");
                else
                    strcat (pPrivate->szTooltipText, "horizontal");
                WgtPaintArrow (hps, &rclWin, pShMemMouseData->ulCurrScrollDir);
                }
            else
                {
                strcat (pPrivate->szTooltipText, "both");
                WgtPaintArrow (hps, &rclWin, SCROLL_DIR_VERT);
                WgtPaintArrow (hps, &rclWin, SCROLL_DIR_HORZ);
                }
            strcat (pPrivate->szTooltipText, "\n");
            }

        // print Text
        strcat (pPrivate->szTooltipText, "Mode (wheel): ");
        WgtAddWheelModeText (pPrivate->szTooltipText, pShMemMouseData->ulScrollMode);
        strcat (pPrivate->szTooltipText, "\nMode (Ctrl+wheel): ");
        WgtAddWheelModeText (pPrivate->szTooltipText, pShMemMouseData->ulScrollModeC);
        strcat (pPrivate->szTooltipText, "\nMode (Alt+wheel): ");
        WgtAddWheelModeText (pPrivate->szTooltipText, pShMemMouseData->ulScrollModeA);

        if (pShMemMouseData->ulScrollMode == SCROLL_MODE_STD  ||
            pShMemMouseData->ulScrollMode == SCROLL_MODE_LINE ||
            pShMemMouseData->ulScrollMode == SCROLL_MODE_VOLUME)
            {
            ULONG flDrawCmd = DT_CENTER | DT_VCENTER;

            if (pShMemMouseData->ulScrollMode == SCROLL_MODE_VOLUME)
                {
                loadMMOS2 ();
                if (pfnMciGetMasterVolume)
                    {
                    LONG lVolume = pfnMciGetMasterVolume ();
                    _itoa (lVolume, szText, 10);
                    strcat (szText, "%");
                    flDrawCmd = DT_LEFT | DT_VCENTER;
                    }
                else
                    strcpy (szText, "-");
                }
            else
                _itoa (pShMemMouseData->ulScrollNum, szText, 10);

            GpiSetBackMix (hps, BM_OVERPAINT);
            WinDrawText (hps,
                         strlen (szText),
                         szText,
                         &rclWin,                           // exclusive
                         pPrivate->setup.lcolForeground,
                         pPrivate->setup.lcolBackground,
                         flDrawCmd);
            }

        WinEndPaint (hps);
        }

    return;
    }

/*******************************************************************\
    handles the WM_PRESPARAMCHANGED message and queries colors and
    font
    Input:  hwnd:          window handle of widget
            ulAttrChanged: type of presentation parameter
            pWidget:       widget instance data
\*******************************************************************/
VOID WgtPresParamChanged (HWND hwnd, ULONG ulAttrChanged, PXCENTERWIDGET pWidget)
    {
    PWIDGETPRIVATE pPrivate = (PWIDGETPRIVATE)pWidget->pUser;
    if (pPrivate)
        {
        BOOL fInvalidate = TRUE;
        switch (ulAttrChanged)
            {
            case 0:     // layout palette thing dropped
            case PP_BACKGROUNDCOLOR:
            case PP_FOREGROUNDCOLOR:
                pPrivate->setup.lcolBackground =
                    pwinhQueryPresColor (hwnd,
                                         PP_BACKGROUNDCOLOR,
                                         FALSE,
                                         SYSCLR_DIALOGBACKGROUND);
                pPrivate->setup.lcolForeground =
                    pwinhQueryPresColor (hwnd,
                                         PP_FOREGROUNDCOLOR,
                                         FALSE,
                                         SYSCLR_WINDOWSTATICTEXT);
                break;

            case PP_FONTNAMESIZE:
                {
                PSZ pszFont = NULL;

                if (pPrivate->setup.pszFont)
                    {
                    free (pPrivate->setup.pszFont);
                    pPrivate->setup.pszFont = NULL;
                    }

                pszFont = pwinhQueryWindowFont (hwnd);
                if (pszFont)
                    {
                    // we must use local malloc() for the font
                    pPrivate->setup.pszFont = strdup (pszFont);
                    pwinhFree (pszFont);
                    }

                // re-match the font now
                pPrivate->fFontMatched = FALSE;
                break;
                }

            default:
                fInvalidate = FALSE;
        }

        if (fInvalidate)
            {
            WinInvalidateRect (hwnd, NULL, FALSE);
            WgtSaveSetupAndSend(hwnd, pPrivate);
            }
        }

    return;
    }

/*******************************************************************\
    releases memory of widget instance setup data
    Input:  pSetup: widget instance setup data
\*******************************************************************/
VOID WgtFreeSetup (PWIDGETSETUP pSetup)
    {
    if (pSetup)
        {
        if (pSetup->pszFont)
            {
            free (pSetup->pszFont);
            pSetup->pszFont = NULL;
            }
        }
    return;
    }

/*******************************************************************\
    handles the WM_DESTROY message
    Input:  pWidget: widget instance data
\*******************************************************************/
VOID WgtDestroy (PXCENTERWIDGET pWidget)
    {
    PWIDGETPRIVATE pPrivate = (PWIDGETPRIVATE)pWidget->pUser;

    pPrivate->bTerminateThread = TRUE;
    DosPostEventSem (hevXWPWidgetUpdate);
    DosWaitThread (&pPrivate->tid, DCWW_WAIT);

    WgtFreeSetup (&pPrivate->setup);
    free (pPrivate);

    return;
    }

/********************************************************************
 *
 *   Exported procedures
 *
 ********************************************************************/

/*
 *@@ WgtInitModule:
 *      required export with ordinal 1, which must tell
 *      the XCenter how many widgets this DLL provides,
 *      and give the XCenter an array of XCENTERWIDGETCLASS
 *      structures describing the widgets.
 *
 *      With this call, you are given the module handle of
 *      XFLDR.DLL. For convenience, and if you have the full
 *      XWorkplace source code, you could resolve imports
 *      for some useful functions which are exported thru
 *      src\shared\xwp.def. We don't do this here.
 *
 *      This function must also register the PM window classes
 *      which are specified in the XCENTERWIDGETCLASS array
 *      entries. For this, you are given a HAB which you
 *      should pass to WinRegisterClass. For the window
 *      class style (4th param to WinRegisterClass),
 *      you should specify
 *
 +          CS_PARENTCLIP | CS_SIZEREDRAW | CS_SYNCPAINT
 *
 *      Your widget window _will_ be resized by the XCenter,
 *      even if you're not planning it to be.
 *
 *      This function only gets called _once_ when the widget
 *      DLL has been successfully loaded by the XCenter. If
 *      there are several instances of a widget running (in
 *      the same or in several XCenters), this function does
 *      not get called again. However, since the XCenter unloads
 *      the widget DLLs again if they are no longer referenced
 *      by any XCenter, this might get called again when the
 *      DLL is re-loaded.
 *
 *      There will ever be only one load occurence of the DLL.
 *      The XCenter manages sharing the DLL between several
 *      XCenters. As a result, it doesn't matter if the DLL
 *      has INITINSTANCE etc. set or not.
 *
 *      If this returns 0, this is considered an error, and the
 *      DLL will be unloaded again immediately.
 *
 *      If this returns any value > 0, *ppaClasses must be
 *      set to a static array (best placed in the DLL's
 *      global data) of XCENTERWIDGETCLASS structures,
 *      which must have as many entries as the return value.
 */
ULONG EXPENTRY WgtInitModule (HAB hab,              // XCenter's anchor block
                              HMODULE hmodPlugin,   // module handle of the widget DLL
                              HMODULE hmodXFLDR,    // XFLDR.DLL module handle
                              PXCENTERWIDGETCLASS *ppaClasses,
                              PSZ pszErrorMsg)      // if 0 is returned, 500 bytes of error msg
    {
    ULONG   ulrc = 0;
    ULONG   ul   = 0;
    BOOL    bImportsFailed = FALSE;

    TraceInit ("d:\\$$xwp$$.dbg");

    hModWidget = hmodPlugin;
    hModXFldr  = hmodXFLDR;

    // resolve imports from XFLDR.DLL
    for (ul = 0; ul < sizeof (G_aImports) / sizeof (G_aImports[0]); ul++)
        {
        if (DosQueryProcAddr (hmodXFLDR,
                              0,                // ordinal, ignored
                              (PSZ)G_aImports[ul].pcszFunctionName,
                              G_aImports[ul].ppFuncAddress)
            != NO_ERROR)
            {
            strcpy (pszErrorMsg, "Import ");
            strcat (pszErrorMsg, G_aImports[ul].pcszFunctionName);
            strcat (pszErrorMsg, " failed.");
            bImportsFailed = TRUE;
            break;
            }
        }

    if (!bImportsFailed)
        {
        // register our PM window class
        if (!WinRegisterClass (hab,
                               WNDCLASS_WIDGET_AMOUSE,
                               fnwpAMouseWidget,
                               CS_PARENTCLIP | CS_SIZEREDRAW | CS_SYNCPAINT,
                               sizeof (PVOID)))         // extra memory to reserve for QWL_USER
            {
            // error registering class: report error then
            strcpy (pszErrorMsg, "WinRegisterClass failed.");
            }
        else
            {
            // no error: return widget classes array
            *ppaClasses = G_WidgetClasses;

            // return no. of classes in this DLL (one here):
            ulrc = sizeof (G_WidgetClasses) / sizeof (G_WidgetClasses[0]);
            }
        }

    return ulrc;
    }

/*
 *@@ WgtUnInitModule:
 *      optional export with ordinal 2, which can clean
 *      up global widget class data.
 *
 *      This gets called by the XCenter right before
 *      a widget DLL gets unloaded. Note that this
 *      gets called even if the "init module" export
 *      returned 0 (meaning an error) and the DLL
 *      gets unloaded right away.
 */
VOID EXPENTRY WgtUnInitModule(VOID)
    {
    }

/*
 *@@ WgtQueryVersion:
 *      this new export with ordinal 3 can return the
 *      XWorkplace version number which is required
 *      for this widget to run. For example, if this
 *      returns 0.9.10, this widget will not run on
 *      earlier XWorkplace versions.
 */
VOID EXPENTRY WgtQueryVersion (PULONG pulMajor,
                               PULONG pulMinor,
                               PULONG pulRevision)
    {
    // report 0.9.9
    *pulMajor    = 0;
    *pulMinor    = 9;
    *pulRevision = 9;

    return;
    }

/*
 *@@ WgtShowSettingsDlg:
 *      This method searches for the WPMouse class object, determines
 *      one of its instances and opens its settings view
 */
VOID EXPENTRY WgtShowSettingsDlg (PWIDGETSETTINGSDLGDATA pData)
    {
    WPFolder *pDesktop = _wpclsQueryFolder (_WPObject, "<WP_DESKTOP>", FALSE);

    if (pDesktop)
        {
        PXCENTERGLOBALS  pGlobals     = (PXCENTERGLOBALS)pData->pGlobals;
        M_WPObject      *somSelf      = pGlobals->pvSomSelf;
        somId            somidThis    = somIdFromString ("WPMouse");
        SOMClass        *pClassObject = _somFindClass (SOMClassMgrObject, somidThis, 0, 0);

        if (pClassObject)
            {
            CLASS     classObject[2];
            HFIND     hFind;             /*  Address of the handle returned by this method. */
            WPObject *pObject;
            ULONG     ulc;               /*  Address of the number of matching entries requested in pBuffer. */
            BOOL      rc;                 /*  Success indicator. */

            classObject[0] = pClassObject;
            classObject[1] = NULL;
            ulc            = 1;

            rc = _wpclsFindObjectFirst (_WPObject,
                                        classObject,
                                        &hFind,
                                        NULL,
                                        pDesktop,
                                        TRUE,
                                        NULL,
                                        &pObject,
                                        &ulc);

            if (ulc == 1)
                _wpViewObject (pObject, NULLHANDLE, OPEN_SETTINGS, 0);

            _wpclsFindObjectEnd (_WPObject, hFind);
            }

        SOMFree (somidThis);
        }

    return;
    }

/*******************************************************************\
    window procedure of widget
\*******************************************************************/
MRESULT EXPENTRY fnwpAMouseWidget (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    PXCENTERWIDGET pWidget = (PXCENTERWIDGET)WinQueryWindowPtr (hwnd, QWL_USER);

    switch (msg)
        {
        /*
         * WM_CREATE:
         *      as with all widgets, we receive a pointer to the
         *      XCENTERWIDGET in mp1, which was created for us.
         *
         *      We could use XCENTERWIDGET.pUser for allocating
         *      another private memory block for our own stuff,
         *      for example to be able to store fonts and colors.
         *      We ain't doing this in the minimal sample.
         */
        case WM_CREATE:
            WgtCreate (hwnd, (PXCENTERWIDGET)mp1);
            return (MRESULT)FALSE;

        /*
         * WM_CONTROL:
         *      process notifications/queries from the XCenter.
         */
        case WM_CONTROL:
            return (MPARAM)WgtControl (hwnd, mp1, mp2);

        /*
         * WM_PAINT:
         *      well, paint the widget.
         */
        case WM_PAINT:
            WgtPaint (hwnd, pWidget);
            return (MRESULT)FALSE;

        case WM_BUTTON1CLICK:
            WgtToggleScrollDir ();
            return (MRESULT)FALSE;

        case SPBM_SPINUP:
        case SPBM_SPINDOWN:
            WgtAdjustScrollNum (msg, (ULONG)mp1);
            return (MRESULT)FALSE;

        case WM_PRESPARAMCHANGED:
            if (pWidget)
                WgtPresParamChanged (hwnd, (ULONG)mp1, pWidget);
            break;

        /*
         * WM_DESTROY:
         *      clean up. This _must_ be passed on to
         *      ctrDefWidgetProc.
         */
        case WM_DESTROY:
            WgtDestroy (pWidget);
            break;
        }

    if (pWidget)
        return pWidget->pfnwpDefWidgetProc (hwnd, msg, mp1, mp2);
    else
        return WinDefWindowProc (hwnd, msg, mp1, mp2);
    }

/*******************************************************************\
    Thread that updates the pShMemMouseData structure, if changes
    have been made to the respective data in the ini-file.
    The thread never terminates
    Input: ulParm: unused
\*******************************************************************/
VOID APIENTRY updateThread (ULONG ulParm)
    {
    ULONG          ulPostCount;
    PXCENTERWIDGET pWidget = (PXCENTERWIDGET)ulParm;

    for (;;)
        {
        DosWaitEventSem (hevXWPWidgetUpdate, SEM_INDEFINITE_WAIT);
        if (((PWIDGETPRIVATE)(pWidget->pUser))->bTerminateThread == TRUE)
            break;

        WinInvalidateRect (pWidget->hwndWidget, NULL, FALSE);
        DosResetEventSem (hevXWPWidgetUpdate, &ulPostCount);
        }

    return;
    }

