/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: PANEL.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Help panels for AMOUSE
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    02-20-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#ifndef PANEL_H
#define PANEL_H

/* Help Panel IDs */
#define PANEL_MAIN              10
#define PANEL_DEVICEINFO        1100
#define PANEL_WLDEVICEINFO      1300
#define PANEL_KEYSETTINGS1      1500
#define PANEL_KEYSETTINGS2      1700
#define PANEL_WHEELSETTINGS1    1900
#define PANEL_WHEELSETTINGS2    2100
#define PANEL_WHEELSETTINGS3    2300
#define PANEL_TIMINGSETTINGS    2500
#define PANEL_INSERTAPPL        2700

#define PANEL_OSVERSION         1102
#define PANEL_DRIVERVERSION     1103
#define PANEL_DEVICETYPE        1104
#define PANEL_IOPORT            1105
#define PANEL_BUTTONS           1106
#define PANEL_WHEEL             1107

#define PANEL_BATTERYWARNING    1304

#define PANEL_BUTTON3           1501
#define PANEL_BUTTON4           1502
#define PANEL_BUTTON5           1503
#define PANEL_BUTTON6           1504
#define PANEL_BUTTON7           1505
#define PANEL_BUTTON8           1506
#define PANEL_BUTTON9           1507
#define PANEL_BUTTON10          1508
#define PANEL_CBUTTON3          1511
#define PANEL_CBUTTON4          1512
#define PANEL_CBUTTON5          1513
#define PANEL_CBUTTON6          1514
#define PANEL_CBUTTON7          1515
#define PANEL_CBUTTON8          1516
#define PANEL_CBUTTON9          1517
#define PANEL_CBUTTON10         1518
#define PANEL_ABUTTON3          1521
#define PANEL_ABUTTON4          1522
#define PANEL_ABUTTON5          1523
#define PANEL_ABUTTON6          1524
#define PANEL_ABUTTON7          1525
#define PANEL_ABUTTON8          1526
#define PANEL_ABUTTON9          1527
#define PANEL_ABUTTON10         1528
#define PANEL_KEYCOMBSET3       1529
#define PANEL_KEYCOMBSET4       1530
#define PANEL_KEYCOMBSET5       1531
#define PANEL_KEYCOMBSET6       1532
#define PANEL_KEYCOMBSET7       1533
#define PANEL_KEYCOMBSET8       1534
#define PANEL_KEYCOMBSET9       1535
#define PANEL_KEYCOMBSET10      1536
#define PANEL_KEYCOMB           1537

#define PANEL_PMCTLS_ENTRY      1701
#define PANEL_PMCTLS_COMBO      1702
#define PANEL_SMARTCRUISE       1703

#define PANEL_NOFUNCTION        1901
#define PANEL_MSG_STD           1902
#define PANEL_MSG_LINE          1903
#define PANEL_MSG_PAGE          1904
#define PANEL_MSG_VOLUME        1905
#define PANEL_KBD_FOCUS         1906
#define PANEL_POINTER_FOCUS     1907
#define PANEL_SCROLLITEMS       1908

#define PANEL_SCROLL_VERT       2101
#define PANEL_SCROLL_HORZ       2102
#define PANEL_ACCEL_DELAY       2103
#define PANEL_ACCEL_VALUE       2104
#define PANEL_TRACKBALL         2105

#define PANEL_W3_DESCRIPTION    2301
#define PANEL_W3_APPLICATION    2302
#define PANEL_W3_CLASS          2303
#define PANEL_W3_PARENTCLASS    2304
#define PANEL_W3_OPTION         2305
#define PANEL_W3_MODE           2306
#define PANEL_W3_VREL           2307
#define PANEL_W3_VOPT           2308
#define PANEL_W3_UPDOWN         2309
#define PANEL_W3_HREL           2310
#define PANEL_W3_HOPT           2311
#define PANEL_W3_LEFTRIGHT      2312
#define PANEL_W3_UP             2313
#define PANEL_W3_DOWN           2314
#define PANEL_W3_INSERT         2315
#define PANEL_W3_DELETE         2316

#define PANEL_MOU_POLLRATE      2501
#define PANEL_MOU_ACCEL_VALUE   2502
#define PANEL_MOU_ACCEL_TH      2503

#endif /* PANEL_H */
