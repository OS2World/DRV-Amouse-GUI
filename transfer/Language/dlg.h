/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: DLG.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr AMOUSE.DLG
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    02-20-00  First release
 *  2.00    06-16-01  WheelThread in separate process
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
#ifndef DLG_H
#define DLG_H

/* Dialog-ID's */
#define IDD_MAIN                    100                 /* main dialog */
#define IDD_ABOUTBOX                1000                /* about box */
#define IDD_DEVICEINFO              1100                /* device info page (dialog) */
#define IDD_DEVICEINFO_40           1200                /* device info page for WARP4 (dialog) */
#define IDD_WLDEVICEINFO            1300                /* device info page wireless (dialog) */
#define IDD_WLDEVICEINFO_40         1400                /* device info page wireless for WARP4 (dialog) */
#define IDD_KEYSETTINGS1            1500                /* button settings page 1 (dialog) */
#define IDD_KEYSETTINGS1_40         1600                /* button settings page 1 for WARP4 (dialog) */
#define IDD_KEYSETTINGS2            1700                /* button settings page 2 (dialog) */
#define IDD_KEYSETTINGS2_40         1800                /* button settings page 2 for WARP4 (dialog) */
#define IDD_WHEELSETTINGS1          1900                /* wheel settings page 1 (dialog) */
#define IDD_WHEELSETTINGS1_40       2000                /* wheel settings page 1 for WARP4 (dialog) */
#define IDD_WHEELSETTINGS2          2100                /* wheel settings page 2 (dialog) */
#define IDD_WHEELSETTINGS2_40       2200                /* wheel settings page 2 for WARP4 (dialog) */
#define IDD_WHEELSETTINGS3          2300                /* wheel settings page 3 (dialog) */
#define IDD_WHEELSETTINGS3_40       2400                /* wheel settings page 3 for WARP4 (dialog) */
#define IDD_TIMINGSETTINGS          2500                /* settings page for mouse timing (dialog) */
#define IDD_TIMINGSETTINGS_40       2600                /* settings page for mouse timing for WARP4 (dialog) */
#define IDD_INSERTAPPL              2700                /* dialog box for application behavour entry */
#define IDD_DEBUG                   3000                /* Debugging dialog */

/* gemeinsame IDs */
#define DID_HELP                    20
#define DID_UNDO                    21
#define DID_DEFAULT                 22
#define DID_DEBUG                   23

/* NotebookDlgProc (IDD_MAIN) */
#define DID_NOTEBOOK                101
#define DID_TEXT                    102

/* AboutDlgProc (IDD_ABOUTBOX) */
/* DeviceInfoDlgProc (IDD_DEVICEINFO(_40)) */
#define DID_OSVERSION               1102
#define DID_DRIVERVERSION           1103
#define DID_DEVICETYPE              1104
#define DID_IOPORT                  1105
#define DID_BUTTONS                 1106
#define DID_WHEEL                   1107
#define DID_SHAPE                   1108
#define DID_VENDOR                  1109

/* WlDeviceInfoDlgProc (IDD_WLDEVICEINFO(_40)) */
#define DID_DEVICENO                1301
#define DID_CHANNEL                 1302
#define DID_BATTERYSTATE            1303
#define DID_BATTERYWARNING          1304

/* KeySettingsDlgProc (IDD_KEYSETTINGS(_40)) */
#define DID_BTN_PAGE_TYPE           1501
#define DID_BUTTON3                 1502
#define DID_BUTTON4                 1503
#define DID_BUTTON5                 1504
#define DID_BUTTON6                 1505
#define DID_BUTTON7                 1506
#define DID_BUTTON8                 1507
#define DID_BUTTON9                 1508
#define DID_BUTTON10                1509
#define DID_KEYCOMBTEXT             1510
#define DID_KEYCOMB                 1511
#define DID_KC_SET3                 1512
#define DID_KC_SET4                 1513
#define DID_KC_SET5                 1514
#define DID_KC_SET6                 1515
#define DID_KC_SET7                 1516
#define DID_KC_SET8                 1517
#define DID_KC_SET9                 1518
#define DID_KC_SET10                1519

/* KeySettings2DlgProc (IDD_KEYSETTINGS2(_40)) */
#define DID_PMCTLS_ENTRY            1701
#define DID_PMCTLS_COMBO            1702
#define DID_SMARTCRUISE             1703

/* WheelSettings1DlgProc (IDD_WHEELSETTINGS1(_40)) */
#define DID_WHEEL_PAGE_TYPE         1901
#define DID_NOFUNCTION              1902
#define DID_MSG_STD                 1903
#define DID_MSG_LINE                1904
#define DID_MSG_PAGE                1905
#define DID_MSG_VOLUME              1906
#define DID_KBD_FOCUS               1907
#define DID_POINTER_FOCUS           1908
#define DID_SCROLLITEMS             1909

/* WheelSettings2DlgProc (IDD_WHEELSETTINGS2(_40)) */
#define DID_SCROLL_VERT             2101
#define DID_SCROLL_HORZ             2102
#define DID_ACCEL_DELAY             2103
#define DID_ACCEL_VALUE             2104
#define DID_WHEEL2                  2105

#define TICKNUMBER_DELAY            20
#define TICKNUMBER_VALUE            6

/* WheelSettings3DlgProc (IDD_WHEELSETTINGS3(_40)) */
/* InsertApplicationDlgProc (IDD_INSERTAPPL) */
#define DID_W3_DESCRIPTION          2301
#define DID_W3_APPLICATION          2302
#define DID_W3_CLASS                2303
#define DID_W3_PARENTCLASS          2304
#define DID_W3_OPTION               2305
#define DID_W3_MODE                 2306
#define DID_W3_VREL                 2307
#define DID_W3_VOPT                 2308
#define DID_W3_UPDOWN               2309
#define DID_W3_HREL                 2310
#define DID_W3_HOPT                 2311
#define DID_W3_LEFTRIGHT            2312
#define DID_W3_UP                   2313
#define DID_W3_DOWN                 2314
#define DID_W3_INSERT               2315
#define DID_W3_DELETE               2316

/* TimingSettingsDlgProc (IDD_TIMINGSETTINGS(_40)) */
#define DID_MOU_POLLRATE            2501
#define DID_MOU_POLLRATE_TXT        2502
#define DID_MOU_ACCEL_VALUE         2503
#define DID_MOU_ACCEL_TH            2504

#define TICKNUMBER_POLLRATE         5
#define TICKNUMBER_ACCELVALUE       20
#define TICKNUMBER_ACCELTHRESH      20

/* DbgDlgProc (IDD_DEBUG) */
#define DID_TL_0                    3001
#define DID_TL_1                    3002
#define DID_TL_2                    3003
#define DID_WL_0                    3004
#define DID_WL_1                    3005
#define DID_WL_2                    3006
#define DID_AL_0                    3007
#define DID_AL_1                    3008
#define DID_AL_2                    3009
#define DID_DM                      3010
#define DID_DT                      3011
#define DID_FILEOUTPUT              3012

#endif /* DLG_H */
