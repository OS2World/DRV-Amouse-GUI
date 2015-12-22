/***************************************************************************\
 *
 * PROGRAMMNAME: PMCTLSPP
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: PMCTLSINI
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   This DLL is registered at the OS/2 Presentation Manager. It starts
 *   the UpdateThread after establishing the semaphores and shared memory
 *   necessary for communication with the WPS class. It registers new window
 *   procedures for the modified PM controls.
 *
 * FUNKTIONEN:
 * -----------
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
 *
 *  Copyright (C) noller & breining software 2001...2004
 *
\******************************************************************************/
#define INCL_DOSSEMAPHORES
#define INCL_WINSHELLDATA
#include <os2.h>

#include <string.h>

#include <Log.h>
#include "AMouseGlobal.h"
#include "PMCtlsData.h"
#include "PMCtlsIni.h"

VOID queryData (VOID)
    {
    ulFlgPmCtls = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_PMCTLS, 0);

    return;
    }

BOOL clsInitData (VOID)
    {
    if (!hevWheelThreadUpdate)
        if (DosOpenEventSem (SEMNAMEEVT_UPDATE, &hevWheelThreadUpdate))
            if (DosCreateEventSem (SEMNAMEEVT_UPDATE, &hevWheelThreadUpdate, DC_SEM_SHARED, TRUE))
                return FALSE;

    /* Klassendaten aus INI-Datei lesen */
    queryData ();

    return TRUE;
    }

