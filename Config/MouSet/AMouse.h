/***************************************************************************\
 *
 * PROGRAMMNAME: AMouse
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMouse.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr AMouse.C
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
 *  Copyright (M_AMouse *somSelf, C) noller & breining software 2001...2006
 *
\******************************************************************************/
#ifndef AMOUSE_H
#define AMOUSE_H

#define M_AMouse            void
#define AMouse              void
#define _wpAllocMem(o,p,e)  malloc(p)
#define _wpFreeMem(o,p)     free(p)

#define CCHMAXPGNAME        32                  // max. StringlÑnge fÅr Seitennamen

#define NUM_DEVICETYPES     12

VOID  _clsInitData (M_AMouse *somSelf);
VOID  _clsSetScrollMode (M_AMouse *somSelf, ULONG ulWheelPageType, ULONG ulScrollMode);
ULONG _clsGetScrollMode (M_AMouse *somSelf, ULONG ulWheelPageType);
VOID  _clsSetScrollNum (M_AMouse *somSelf, ULONG ulWheelPageType, ULONG ulNewScrollNum);
ULONG _clsGetScrollNum (M_AMouse *somSelf, ULONG ulWheelPageType);
VOID  _clsSetWheelTarget (M_AMouse *somSelf, ULONG ulWheelPageType, ULONG ulNewWheelTarget);
ULONG _clsGetWheelTarget (M_AMouse *somSelf, ULONG ulWheelPageType);
VOID  _clsSetStartupMode (M_AMouse *somSelf, ULONG ulStartupMode);
ULONG _clsGetStartupMode (M_AMouse *somSelf);
VOID  _clsSetAccelDelay (M_AMouse *somSelf, ULONG ulAccelDelay);
ULONG _clsGetAccelDelay (M_AMouse *somSelf);
VOID  _clsSetAccelValue (M_AMouse *somSelf, ULONG ulAccelValue);
ULONG _clsGetAccelValue (M_AMouse *somSelf);
VOID  _clsSetPollingRate (M_AMouse *somSelf, ULONG ulPollingRate);
ULONG _clsGetPollingRate (M_AMouse *somSelf);
VOID  _clsSetAccelLevel1 (M_AMouse *somSelf, ULONG ulAccelLevel);
ULONG _clsGetAccelLevel1 (M_AMouse *somSelf);
VOID  _clsSetAccelLvl1Mult (M_AMouse *somSelf, ULONG ulAccelLvlMult);
ULONG _clsGetAccelLvl1Mult (M_AMouse *somSelf);
VOID  _clsSetAccelLevel2 (M_AMouse *somSelf, ULONG ulAccelLevel);
ULONG _clsGetAccelLevel2 (M_AMouse *somSelf);
VOID  _clsSetAccelLvl2Mult (M_AMouse *somSelf, ULONG ulAccelLvlMult);
ULONG _clsGetAccelLvl2Mult (M_AMouse *somSelf);
VOID  _clsSetBtnMode (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum, ULONG ulBtnMode);
ULONG _clsGetBtnMode (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum);
VOID  _clsSetBtnKeyCombMP1 (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum, ULONG ulMP1);
ULONG _clsGetBtnKeyCombMP1 (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum);
VOID  _clsSetBtnKeyCombMP2 (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum, ULONG ulMP2);
ULONG _clsGetBtnKeyCombMP2 (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum);
VOID  _clsSetWheelCount (M_AMouse *somSelf, ULONG ulWheelCount);
ULONG _clsGetWheelCount (M_AMouse *somSelf);
VOID  _clsSetApplications (M_AMouse *somSelf, PSTRUCTAPPL pstructApplications);
PSTRUCTAPPL _clsGetApplications (M_AMouse *somSelf);
VOID  _clsSetPMCtlsFlags (M_AMouse *somSelf, ULONG ulFlgPmCtls);
ULONG _clsGetPMCtlsFlags (M_AMouse *somSelf);
VOID  _clsSetSmartCruise (M_AMouse *somSelf, ULONG ulSmartCruise);
ULONG _clsGetSmartCruise (M_AMouse *somSelf);

#endif /* AMOUSE_H */
