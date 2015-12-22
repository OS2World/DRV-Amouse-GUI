/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMOUSEGLOBAL.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr Kommunikation zwischen WPS Klasse und Thread
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    02-20-00  First release
 *  2.00    06-16-01  Introduction of WheelThread-DLL
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#ifndef AMOUSEGLOBAL_H
#define AMOUSEGLOBAL_H

/* definitions for application definition data */
#define CCHMAXAPPLSTRING 32     // number of characters in application definition strings (see STRUCTAPPL)
#define CCHMAXAPPL       20     // number of application definitions (STRUCTAPPL structures)
#define CIDBUTTONMIN     3      // id of lowest supported mouse button
#define CIDBUTTONMAX     10     // id of highest supported mouse button
#define CULNUMBUTTONS    CIDBUTTONMAX-CIDBUTTONMIN+1

/* fixed length part of resource data structure */
typedef struct
    {
    USHORT  usScrollMode;
    USHORT  usVRelation;
    USHORT  usVOpt;
    USHORT  usMsgUp;
    USHORT  usMsgDown;
    USHORT  usHRelation;
    USHORT  usHOpt;
    USHORT  usMsgLeft;
    USHORT  usMsgRight;
    } RESDATA, *PRESDATA;

/* definitions for application settings dialog */
typedef struct _STRUCTAPPL
    {
    CHAR    szDescription[CCHMAXAPPLSTRING];
    CHAR    szApplication[CCHMAXAPPLSTRING];
    CHAR    szClass[CCHMAXAPPLSTRING];
    CHAR    szParentClass[CCHMAXAPPLSTRING];
    CHAR    szOption[CCHMAXAPPLSTRING];
    RESDATA strucResData;
    } STRUCTAPPL, *PSTRUCTAPPL;

typedef struct _MOUSEDATA
    {
    ULONG  ulScrollMode;        // SCROLL_MODE_* (wheel)
    ULONG  ulScrollModeC;       // SCROLL_MODE_* (wheel + Ctrl key)
    ULONG  ulScrollModeA;       // SCROLL_MODE_* (wheel + Alt key)
    ULONG  ulScrollNum;         // number of scroll lines per unit
    ULONG  ulScrollNumC;        // number of scroll lines per unit with Ctrl key
    ULONG  ulScrollNumA;        // number of scroll lines per unit with Alt key
    ULONG  ulWheelTarget;       // WHEEL_TARGET_*
    ULONG  ulWheelTargetC;      // WHEEL_TARGET_* with pressed Ctrl key
    ULONG  ulWheelTargetA;      // WHEEL_TARGET_* with pressed Alt key
    ULONG  ulStartupMode;       // SCROLL_DIR_*
    ULONG  ulAccelDelay;        // wheel acceleration delay in ms
    ULONG  ulAccelValue;        // wheel acceleration value
    UCHAR  ucBtnMode[CULNUMBUTTONS];        // index in resource table
    UCHAR  ucBtnCMode[CULNUMBUTTONS];       // index in resource table
    UCHAR  ucBtnAMode[CULNUMBUTTONS];       // index in resource table
    ULONG  ulBtnKeyCombMP1[CULNUMBUTTONS];  // mp1 value of WM_CHAR for key combination
    ULONG  ulBtnKeyCombMP2[CULNUMBUTTONS];  // mp2 value of WM_CHAR for key combination
    ULONG  ulCurrScrollDir;     // SCROLL_DIR_*
    ULONG  ulPollingRate;       // PS/2 mouse polling rate
    ULONG  ulAccelLevel1;       // pointer acceleration level 1 (KEY_ACCELLEVEL1)
    ULONG  ulAccelLvl1Mult;     // pointer acceleration level 1 multiplier (KEY_ACCELLVL1MULT)
    ULONG  ulAccelLevel2;       // pointer acceleration level 2 (KEY_ACCELLEVEL2)
    ULONG  ulAccelLvl2Mult;     // pointer acceleration level 2 multiplier (KEY_ACCELLVL2MULT)
    ULONG  ulWheelCount;        // number of wheels
    BYTE   ulSmartCruise;       // Smart Cruise Setting
    CHAR   cApplications[(4 * CCHMAXAPPLSTRING + sizeof (RESDATA)) * CCHMAXAPPL];
                                // application definitions (STRUCTAPPL without szDescription)
    ULONG  ulcApplications;     // current size of cApplications
    ULONG  ulFlgPmCtls;         // flags for PM-Controls behaviour (PMCTL_*)
    BOOL   bBatteryWarning;     // battery warning on/off
    } MOUSEDATA, *PMOUSEDATA;

#define SHMEMNAME               "\\SHAREMEM\\AMOUSE.DAT"
#define SEMNAMEMTX              "\\SEM32\\WHEELTHREADMTX"
#define SEMNAMEEVT_UPDATE       "\\SEM32\\WHEELTHREADUPDATE"
#define SEMNAMEEVT_WIDGET       "\\SEM32\\XWPWIDGETUPDATE"
#define SEMNAMEEVT_PAINT        "\\SEM32\\PAINTVOLUME"

/* Values for wheel mode */
#define WHEEL_TARGET_KBD        0
#define WHEEL_TARGET_POINTER    1

/* Values for scroll mode; have to be identical to values MODE_* in AMouRes.h */
#define SCROLL_MODE_NONE        0x0000
#define SCROLL_MODE_STD         0x0001
#define SCROLL_MODE_LINE        0x0002
#define SCROLL_MODE_PAGE        0x0004
#define SCROLL_MODE_VOLUME      0x0008

/* Values for startup mode / current scroll direction */
#define SCROLL_DIR_VERT         1
#define SCROLL_DIR_HORZ         2

/* Values for PM Controls behaviour */
#define PMCTL_ENTRY             0x0001      // entry fields
#define PMCTL_COMBO             0x0002      // combo boxes

/* Default values for wheel acceleration */
#define ACCEL_DEF_DELAY         500
#define ACCEL_DEF_VALUE         3
#define ACCEL_MAX_VALUE         6

/* Values for scroll mode in fullscreen mode; values are derived from other MOUSEDATA values */
#define FSSCROLL_MODE_VERT      0
#define FSSCROLL_MODE_HORZ      1
#define FSSCROLL_MODE_PAGE      2

/* Default value for timing parameters */
#define DEF_VALUE_POLLING_RATE  80
#define DEF_VALUE_ACCEL_LEVEL1  3
#define DEF_VALUE_ACCEL_L1MULT  2
#define DEF_VALUE_ACCEL_LEVEL2  20
#define DEF_VALUE_ACCEL_L2MULT  4

/* Smart Cruise Values */
#define SMART_CRUISE_OFF        0
#define SMART_CRUISE_VERT       1
#define SMART_CRUISE_HORZ       2
#define SMART_CRUISE_ALL        3

/* Other default values */
#define DEF_VALUE_WHEELCOUNT    1
#define DEF_VALUE_SMARTCRUISE   SMART_CRUISE_OFF

/* Labels for OS2.INI file */
#define APP_AMOUSE              "AMouse"
#define KEY_SCROLLMODE          "ScrollMode"
#define KEY_SCROLLMODE_C        "ScrollModeC"
#define KEY_SCROLLMODE_A        "ScrollModeA"
#define KEY_SCROLLNUM           "ScrollNumber"
#define KEY_SCROLLNUM_C         "ScrollNumberC"
#define KEY_SCROLLNUM_A         "ScrollNumberA"
#define KEY_WHEELTARGET         "WheelTarget"
#define KEY_WHEELTARGET_C       "WheelTargetC"
#define KEY_WHEELTARGET_A       "WheelTargetA"
#define KEY_STARTUPMODE         "StartupMode"
#define KEY_ACCELDELAY          "AccelDelay"
#define KEY_ACCELVALUE          "AccelValue"
#define KEY_POLLINGRATE         "PollingRate"
#define KEY_ACCELLEVEL1         "AccelLevel1"
#define KEY_ACCELLVL1MULT       "AccelLvl1Mult"
#define KEY_ACCELLEVEL2         "AccelLevel2"
#define KEY_ACCELLVL2MULT       "AccelLvl2Mult"
#define KEY_BTNMODE             "ButtonMode"
#define KEY_BTNCMODE            "CButtonMode"
#define KEY_BTNAMODE            "AButtonMode"
#define KEY_BTNKEYCOMBMP1       "ButtonKeyCombMP1"
#define KEY_BTNKEYCOMBMP2       "ButtonKeyCombMP2"
#define KEY_WHEELCOUNT          "WheelCount"
#define KEY_APPLICATIONS        "Applications"
#define KEY_PMCTLS              "PMCtls"
#define KEY_BATTERYWARNING      "Batterywarning"
#define KEY_SMARTCRUISE         "SmartCruise"

/* window messages for additional mouse buttons 4...7 */
/* mp1: MESSAGE_KEY                                   */
/* mp2: SHORT 1: 1 = PM screen group                  */
/*               0 = other                            */
/*      SHORT 2: shift key state                      */
#define WM_BUTTON4DOWN          WM_USER + 3100
#define WM_BUTTON4UP            WM_USER + 3101
#define WM_BUTTON5DOWN          WM_USER + 3102
#define WM_BUTTON5UP            WM_USER + 3103
#define WM_BUTTON6DOWN          WM_USER + 3104
#define WM_BUTTON6UP            WM_USER + 3105
#define WM_BUTTON7DOWN          WM_USER + 3106
#define WM_BUTTON7UP            WM_USER + 3107
#define WM_BUTTON8DOWN          WM_USER + 3108
#define WM_BUTTON8UP            WM_USER + 3109
#define WM_BUTTON9DOWN          WM_USER + 3110
#define WM_BUTTON9UP            WM_USER + 3111
#define WM_BUTTON10DOWN         WM_USER + 3112
#define WM_BUTTON10UP           WM_USER + 3113

#define MESSAGE_KEY             0x5555AAAA  // key to detect if message was originated by AMouse

#define MOU_SETKBDEVENT         0x78        // IOCTL function code for IOCTL_POINTINGDEVICE to send kbd event
#define MOU_QUERYMOUDEVDATA     0x79        // IOCTL function code for IOCTL_POINTINGDEVICE to query mouse device data

#endif /* AMOUSEGLOBAL_H */
