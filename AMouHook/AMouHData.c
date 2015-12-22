/***************************************************************************\
 *
 * PROGRAMMNAME: AMouse
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMouHData
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Enth„lt die globalen Variablen
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.10    05-12-02  Handling of shift-keys
 *  2.20    10-03-02  USB support added
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define INCL_DOSSEMAPHORES
#include <os2.h>

#include "AMouHData.h"

/*--------------------------------------------------------------*\
    Global variables
    local data segment (process specific)
\*--------------------------------------------------------------*/

/*--------------------------------------------------------------*\
     global data segment
\*--------------------------------------------------------------*/
#pragma data_seg(GLOBAL_SEG)

ULONG       ulcBytePerPage  = 0;

HAB         habDLL          = NULLHANDLE;
HMODULE     hModule         = NULLHANDLE;

PWINDOWDATA parWindow       = NULL;
ULONG       ulcWindow       = 0;

