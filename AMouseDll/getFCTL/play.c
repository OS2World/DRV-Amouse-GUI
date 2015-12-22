/***************************************************************************\
 *
 * PROGRAMMNAME: WPDCF77
 * -------------
 *
 * VERSION: 5.2
 * --------
 *
 * MODULNAME: PLAY.C
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Methoden fÅr Multimediafunktionen
 *
 * HINWEISE:
 * ---------
 *   Diese Funktonen dienen nur als Stubs in die Multimedia-Dll "nbaudio.dll".
 *   Diese DLL wird mit Hilfe dieser Funktionen dynamisch geladen.
 *
 * FUNKTIONEN:
 * -----------
 *   ClkMciLoadFile ()
 *   ClkMciStartPlayBack ()
 *   ClkMciCheckRedo ()
 *   ClkMciClose ()
 *   ClkMciPassDevice ()
 *   ClkMciActivate ()
 *   ClkMciIsMultimedia ()
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  4.40    01-31-00  Multimedia-UnterstÅtzung, Bugfixing
 *  5.10    02-10-01  Fehlerkorrektur Positionsspeicherung Iconview
 *  5.20    06-09-01  Fehlerkorrektur Audiodaten
 *
 *  Copyright (C) noller & breining software 1995...2001
 *
\******************************************************************************/
#define INCL_DOSMODULEMGR
#define INCL_MMIO_ERRORS
#include <os2.h>
#include <os2me.h>

#include "play.h"
#include "nbaudio.h"

static CHAR          szError[256];              /* error return for DosLoadModule */
static HMODULE       hModMMPM = NULLHANDLE;     /* module handle of mmpm.dll */

static PFN           pfnMciPlayFile    = NULL;
static PFN           pfnMciLoad        = NULL;
static PFN           pfnMciStart       = NULL;
static PFN           pfnClkPassDevice  = NULL;
static PFN           pfnClkActivate    = NULL;
static PFN           pfnMciCheckRedo   = NULL;
static PFN           pfnMciClose       = NULL;

BOOL ClkMciPlayFile (HWND hwnd, PSZ pszFilename)
    {
    if (pfnMciLoad)
        return pfnMciPlayFile (hwnd, pszFilename) == MCIERR_SUCCESS ? TRUE : FALSE;
    else
        return FALSE;
    }

BOOL ClkMciLoadFile (HWND hwnd, ULONG ulQwlIndex, PCHAR pszFileName, ULONG ulNumOfPlays)
    {
    if (pfnMciLoad)
        return pfnMciLoad (hwnd, ulQwlIndex, pszFileName, ulNumOfPlays);
    else
        return FALSE;
    }

VOID ClkMciStartPlayBack (HWND hwnd, ULONG ulQwlIndex, USHORT usFinishedMsg)
    {
    if (pfnMciStart)
        pfnMciStart (hwnd, ulQwlIndex, usFinishedMsg);
    return;
    }

VOID ClkMciCheckRedo (HWND hwnd, ULONG ulQwlIndex)
    {
    if (pfnMciCheckRedo)
        pfnMciCheckRedo (hwnd, ulQwlIndex);
    return;
    }

VOID ClkMciClose (HWND hwnd, ULONG ulQwlIndex)
    {
    if (pfnMciClose)
        pfnMciClose (hwnd, ulQwlIndex);
    return;
    }

VOID ClkMciPassDevice (HWND hwnd, ULONG ulQwlIndex, SHORT sAction)
    {
    if (pfnClkPassDevice)
        pfnClkPassDevice (hwnd, ulQwlIndex, sAction);
    return;
    }

VOID ClkMciActivate (HWND hwnd, ULONG ulQwlIndex, BOOL isActive)
    {
    if (pfnClkActivate)
        pfnClkActivate (hwnd, ulQwlIndex, isActive);
    return;
    }

BOOL ClkMciIsMultimedia (VOID)
    {
    APIRET rc;

    if (hModMMPM)
        return TRUE;

    rc = DosLoadModule (szError, sizeof (szError), "nbaudio.dll", &hModMMPM);
    if (rc)
        return FALSE;

    rc  = DosQueryProcAddr (hModMMPM, 0, "MciPlayFile",       &pfnMciPlayFile);
    rc |= DosQueryProcAddr (hModMMPM, 0, "MciLoadFile",       &pfnMciLoad);
    rc |= DosQueryProcAddr (hModMMPM, 0, "MciStartPlayBack",  &pfnMciStart);
    rc |= DosQueryProcAddr (hModMMPM, 0, "MciPassDevice",     &pfnClkPassDevice);
    rc |= DosQueryProcAddr (hModMMPM, 0, "MciActivate",       &pfnClkActivate);
    rc |= DosQueryProcAddr (hModMMPM, 0, "MciCheckRedo",      &pfnMciCheckRedo);
    rc |= DosQueryProcAddr (hModMMPM, 0, "MciClose",          &pfnMciClose);

    if (rc)
        {
        DosFreeModule (hModMMPM);
        hModMMPM         = NULLHANDLE;
        pfnMciPlayFile   = NULL;
        pfnMciLoad       = NULL;
        pfnMciStart      = NULL;
        pfnClkPassDevice = NULL;
        pfnClkActivate   = NULL;
        pfnMciCheckRedo  = NULL;
        pfnMciClose      = NULL;
        return FALSE;
        }

    return TRUE;
    }

