/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUDLL
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMOUINI
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   This DLL is registered at the OS/2 Presentation Manager. It starts
 *   the WheelThread after establishing the semaphores and shared memory
 *   necessary for communication with the WPS class
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
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define INCL_DOSMEMMGR
#define INCL_DOSSEMAPHORES
#define INCL_DOSPROCESS
#define INCL_WINSHELLDATA
#include <os2.h>
#include <string.h>
#include <stdlib.h>

#include <Log.h>
#include "AMouData.h"
#include "AMouIni.h"
#include "res.h"

/*******************************************************************\
  local data segment (process specific)
\*******************************************************************/

/*******************************************************************\
  global data segment
\*******************************************************************/
#pragma data_seg(GLOBAL_SEG)

/* Default settings for buttons with and without shift keys */
static UCHAR ucKeyDefault[CULNUMBUTTONS]  =
    {
    IDR_DEFAULT_KEY3, IDR_DEFAULT_KEY4, IDR_DEFAULT_KEY5, IDR_DEFAULT_KEY6,
    IDR_DEFAULT_KEY7, IDR_DEFAULT_KEY8, IDR_DEFAULT_KEY9, IDR_DEFAULT_KEY10
    };
static UCHAR ucKeyCDefault[CULNUMBUTTONS] =
    {
    IDR_DEFAULT_KEYC3, IDR_DEFAULT_KEYC4, IDR_DEFAULT_KEYC5, IDR_DEFAULT_KEYC6,
    IDR_DEFAULT_KEYC7, IDR_DEFAULT_KEYC8, IDR_DEFAULT_KEYC9, IDR_DEFAULT_KEYC10
    };
static UCHAR ucKeyADefault[CULNUMBUTTONS] =
    {
    IDR_DEFAULT_KEYA3, IDR_DEFAULT_KEYA4, IDR_DEFAULT_KEYA5, IDR_DEFAULT_KEYA6,
    IDR_DEFAULT_KEYA7, IDR_DEFAULT_KEYA8, IDR_DEFAULT_KEYA9, IDR_DEFAULT_KEYA10
    };

VOID queryData (VOID)
    {
    ULONG ulc, ul, ulcProfile;
    PCHAR pc, pProfile, pApps;

    DosRequestMutexSem (hmtxWheelThread, (ULONG)SEM_INDEFINITE_WAIT);

    pShMemMouseData->ulScrollMode    = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SCROLLMODE,    SCROLL_MODE_STD);
    pShMemMouseData->ulScrollModeC   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SCROLLMODE_C,  SCROLL_MODE_NONE);
    pShMemMouseData->ulScrollModeA   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SCROLLMODE_A,  SCROLL_MODE_NONE);
    pShMemMouseData->ulScrollNum     = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SCROLLNUM,     3);
    pShMemMouseData->ulScrollNumC    = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SCROLLNUM_C,   3);
    pShMemMouseData->ulScrollNumA    = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SCROLLNUM_A,   3);
    pShMemMouseData->ulWheelTarget   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_WHEELTARGET,   WHEEL_TARGET_POINTER);
    pShMemMouseData->ulWheelTargetC  = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_WHEELTARGET_C, WHEEL_TARGET_POINTER);
    pShMemMouseData->ulWheelTargetA  = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_WHEELTARGET_A, WHEEL_TARGET_POINTER);
    pShMemMouseData->ulStartupMode   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_STARTUPMODE,   SCROLL_DIR_VERT);
    pShMemMouseData->ulAccelDelay    = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELDELAY,    SCROLL_DIR_VERT);
    pShMemMouseData->ulAccelValue    = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELVALUE,    SCROLL_DIR_VERT);
    pShMemMouseData->ulPollingRate   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_POLLINGRATE,   DEF_VALUE_POLLING_RATE);
    pShMemMouseData->ulAccelLevel1   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLEVEL1,   DEF_VALUE_ACCEL_LEVEL1);
    pShMemMouseData->ulAccelLvl1Mult = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLVL1MULT, DEF_VALUE_ACCEL_L1MULT);
    pShMemMouseData->ulAccelLevel2   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLEVEL2,   DEF_VALUE_ACCEL_LEVEL2);
    pShMemMouseData->ulAccelLvl2Mult = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLVL2MULT, DEF_VALUE_ACCEL_L2MULT);
    pShMemMouseData->ulWheelCount    = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_WHEELCOUNT,    DEF_VALUE_WHEELCOUNT);
    pShMemMouseData->ulSmartCruise   = PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SMARTCRUISE,   DEF_VALUE_SMARTCRUISE);

    ulc = sizeof (pShMemMouseData->ucBtnMode);
    if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNMODE,
                                      (PVOID)pShMemMouseData->ucBtnMode, &ulc))
        memcpy ((PVOID)pShMemMouseData->ucBtnMode,
                (PVOID)ucKeyDefault,
                CULNUMBUTTONS*sizeof (UCHAR));

    ulc = sizeof (pShMemMouseData->ucBtnCMode);
    if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNCMODE,
                                      (PVOID)pShMemMouseData->ucBtnCMode, &ulc))
        memcpy ((PVOID)pShMemMouseData->ucBtnCMode,
                (PVOID)ucKeyCDefault,
                CULNUMBUTTONS*sizeof (UCHAR));

    ulc = sizeof (pShMemMouseData->ucBtnAMode);
    if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNAMODE,
                                      (PVOID)pShMemMouseData->ucBtnAMode, &ulc))
        memcpy ((PVOID)pShMemMouseData->ucBtnAMode,
                (PVOID)ucKeyADefault,
                CULNUMBUTTONS*sizeof (UCHAR));

    ulc = sizeof (pShMemMouseData->ulBtnKeyCombMP1);
    if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP1,
                                      (PVOID)pShMemMouseData->ulBtnKeyCombMP1, &ulc))
        memset (pShMemMouseData->ulBtnKeyCombMP1, '\0', sizeof (pShMemMouseData->ulBtnKeyCombMP1));

    ulc = sizeof (pShMemMouseData->ulBtnKeyCombMP2);
    if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP2,
                                      (PVOID)pShMemMouseData->ulBtnKeyCombMP2, &ulc))
        memset (pShMemMouseData->ulBtnKeyCombMP2, '\0', sizeof (pShMemMouseData->ulBtnKeyCombMP2));

    /* read and reformat application definition data */
    PrfQueryProfileSize (HINI_USERPROFILE, APP_AMOUSE, KEY_APPLICATIONS, &ulcProfile);
    pProfile = (PCHAR)malloc (ulcProfile);
    PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_APPLICATIONS, pProfile, &ulcProfile);
    pc = pProfile;

    pApps = pShMemMouseData->cApplications;
    pShMemMouseData->ulcApplications = 0;
    while (pc < pProfile + ulcProfile && pc[0] != '\0')
        {
        pc += strlen (pc) + 1;              // overread szDescription
        for (ulc = ul = 0; ul < 4; ul++)
            while (pc[ulc++] != '\0')
                {}
        ulc += sizeof (RESDATA);
        memcpy (pApps, pc, ulc);            // copy remaining strings + structure
        pApps += ulc;
        pc    += ulc;
        pShMemMouseData->ulcApplications += ulc;
        }

    free (pProfile);

    pShMemMouseData->ulCurrScrollDir = pShMemMouseData->ulStartupMode;
    DosReleaseMutexSem (hmtxWheelThread);

    DosPostEventSem (hevXWPWidgetUpdate);

    return;
    }

BOOL clsInitData (VOID)
    {
    /* Allocate / initialize shared memory */
    if (DosGetNamedSharedMem ((PPVOID)&pShMemMouseData, SHMEMNAME, PAG_READ | PAG_WRITE))
        {
        if (DosAllocSharedMem ((PPVOID)&pShMemMouseData, SHMEMNAME, sizeof (MOUSEDATA), PAG_COMMIT | PAG_WRITE | PAG_READ))
            {
            pShMemMouseData = NULL;                      // Fehler: Anlegen des Shared-Memory nicht m”glich
            return FALSE;
            }
        else
            {
            memset (pShMemMouseData, '\0', sizeof (MOUSEDATA));
            }
        }

    /* open/create semaphore for synchronisation of strucMouseData */
    if (!hmtxWheelThread)
        if (DosOpenMutexSem (SEMNAMEMTX, &hmtxWheelThread))
            if (DosCreateMutexSem (SEMNAMEMTX, &hmtxWheelThread, 0L, FALSE))
                return FALSE;

    /* open/create semaphore for thread unblocking */
    if (hmtxWheelThread)
        {
        if (!hevWheelThreadUpdate)
            if (DosOpenEventSem (SEMNAMEEVT_UPDATE, &hevWheelThreadUpdate))
                if (DosCreateEventSem (SEMNAMEEVT_UPDATE, &hevWheelThreadUpdate, DC_SEM_SHARED, TRUE))
                    return FALSE;

        if (!hevXWPWidgetUpdate)
            if (DosOpenEventSem (SEMNAMEEVT_WIDGET, &hevXWPWidgetUpdate))
                if (DosCreateEventSem (SEMNAMEEVT_WIDGET, &hevXWPWidgetUpdate, DC_SEM_SHARED, TRUE))
                    return FALSE;
        }
    else
        return FALSE;

    /* Klassendaten aus INI-Datei lesen */
    queryData ();

    return TRUE;
    }

