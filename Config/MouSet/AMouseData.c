/***************************************************************************\
 *
 * PROGRAMMNAME: AMouse
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMouseData
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   EnthÑlt die globalen Variablen
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
#include <os2.h>

#define AMOUSEDATA_DEFINED

#include "AMouseData.h"

/*--------------------------------------------------------------*\
 *  Globale Variablen
\*--------------------------------------------------------------*/
CHAR     szBuffer[BUFFLEN];          // string buffer

BOOL     bIsWarp4;                   // Operating system version

BOOL     bIsHelp = FALSE;            // TRUE: Help verfÅgbar
HWND     hwndHelp = NULLHANDLE;

HAB      hab;                        // Anchor block wird clsInitData gefÅllt
HMODULE  hmod    = NULLHANDLE;       // Module-Handle
HMODULE  hmodLng = NULLHANDLE;       // Module-Handle Language DLL

