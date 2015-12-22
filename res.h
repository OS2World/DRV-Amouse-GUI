/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: RES.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr AMOUSE.RC
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
#ifndef RES_H
#define RES_H

/* Icon file */
#define AMOUSE_ICON             "AMOUSE.ICO"
#define BATTERY_ICON            "BATT.ICO"

/* Icon resource IDs */
#define IDI_ICON                1
#define IDI_BATTERY             2

/* String resource IDs */
#define IDS_ABOUT               1000
#define IDS_HELPWINDOWTITLE     1001
#define IDS_SWENTRY             1002
#define IDS_NOMOUSE             1003

#define IDS_ERR_SEM             1004
#define IDS_ERR_MOD             1005

#define IDS_BATT_EMPTY          1010

#define IDS_PAGENAME_DEVINFO    1100
#define IDS_PAGENAME_WHEEL      1101
#define IDS_PAGENAME_BUTTONS    1102
#define IDS_PAGENAME_TIMING     1103

#define IDS_PORT_UNKNOWN        1200
#define IDS_PORT_SERIAL         1201
#define IDS_PORT_PS2            1202
#define IDS_PORT_USB            1203

#define IDS_WHEEL_0             1204
#define IDS_WHEEL_1             1205
#define IDS_WHEEL_2             1206

#define IDS_ACCEL_VAL_OFF       1207
#define IDS_ACCEL_VAL_FAST      1208

#define IDS_PAGE_WHEEL          1209
#define IDS_PAGE_WHEEL_C        1210
#define IDS_PAGE_WHEEL_A        1211
#define IDS_PAGENUMBER          1212

#define IDS_TYPE_AMBIGUOUS      1213

#define IDS_UNKNOWN             1214
#define IDS_UNKNOWN_DEVICE      1215
#define IDS_UNKNOWN_RECEIVER    1216

#define IDS_PAGE_BUTTON         1217
#define IDS_PAGE_BUTTON_C       1218
#define IDS_PAGE_BUTTON_A       1219

#define IDS_LOGI_SUBT_BASE      1300
#define IDS_LOGI_FREQ_BASE      1350
#define IDB_LOGI_BATT_BASE      1400
#define IDS_USB_FREQ_BASE       1450

#define IDS_KEY_CTRL            1500
#define IDS_KEY_ALT             1501
#define IDS_KEY_SHIFT           1502
#define IDS_KEY_BACKSPACE       1503
#define IDS_KEY_TAB             1504
#define IDS_KEY_BACKTABTAB      1505
#define IDS_KEY_ENTER           1506
#define IDS_KEY_ESC             1507
#define IDS_KEY_SPACE           1508
#define IDS_KEY_PAGEUP          1509
#define IDS_KEY_PAGEDOWN        1510
#define IDS_KEY_END             1511
#define IDS_KEY_HOME            1512
#define IDS_KEY_LEFT            1513
#define IDS_KEY_UP              1514
#define IDS_KEY_RIGHT           1515
#define IDS_KEY_DOWN            1516
#define IDS_KEY_PRINTSCRN       1517
#define IDS_KEY_INSERT          1518
#define IDS_KEY_DELETE          1519
#define IDS_KEY_SCRLLOCK        1520
#define IDS_KEY_NUMLOCK         1521
#define IDS_KEY_WINLEFT         1522
#define IDS_KEY_WINRIGHT        1523
#define IDS_KEY_WINMENU         1524
#define IDS_KEY_SYSRQ           1525

#define MAX_LOGI_SUBT           24
#define MAX_LOGI_FREQ           4
#define MAX_LOGI_BATT           7
#define MAX_USB_FREQ            1

/* KontextmenÅ */
#define IDM_MAINMENU            6002

/* Die folgenden MenÅ-IDs mÅssen bei WPS-Klassen mit den entsprechenden OPEN_*-Werten Åbereinstimmen */
#define IDM_ABOUT               0x6500      // = WPMENUID_USER = OPEN_USER
#define IDM_OPENDEBUG           0x6501

/* General Help res ID  */
#define IDH_AMOUSE_DEFAULT      10

/* Help Panel IDs */
#define PANEL_MAIN              10

/* Mouse type definitions */
#define IDRC_MOUSETYPE          2500
#define PORT_UNKNOWN            0       // unknown port
#define PORT_SERIAL             1       // serial port
#define PORT_PS2                2       // PS/2 port
#define PORT_USB                3       // USB port

#define WHEEL_0                 0       // no wheel
#define WHEEL_1                 1       // 1 wheel
#define WHEEL_2                 2       // 2 wheels

#define TYPE_UNAMBIG            0       // mouse type unambiguous
#define TYPE_AMBIG              1       // mouse type ambiguous

/* Button settings */
#define IDRC_BUTTONSETTINGS     3000
#define IDR_NONE                0
#define IDR_CLIPBOARD_CUT       1
#define IDR_CLIPBOARD_COPY      2
#define IDR_CLIPBOARD_INSERT    3
#define IDR_BUTTON3             4
#define IDR_MINIMIZE_ALL        5
#define IDR_RESTORE_ALL         6
#define IDR_WINDOW_LIST         7
#define IDR_CLOSE_APPLICATION   8
#define IDR_DOUBLECLICK         9
#define IDR_MAXIMIZE_WND        10
#define IDR_MINIMIZE_WND        11
#define IDR_RESTORE_WND         12
#define IDR_TOGGLE_SCROLL       13
#define IDR_PUSH_TO_BACK        14
#define IDR_KEY                 15      // must be last displayable entry, because it is dynamic entry!
#define IDR_END                 16

#define IDR_DEFAULT_KEY3        IDR_BUTTON3
#define IDR_DEFAULT_KEY4        IDR_TOGGLE_SCROLL
#define IDR_DEFAULT_KEY5        IDR_PUSH_TO_BACK
#define IDR_DEFAULT_KEY6        IDR_MINIMIZE_WND
#define IDR_DEFAULT_KEY7        IDR_MAXIMIZE_WND
#define IDR_DEFAULT_KEY8        IDR_NONE
#define IDR_DEFAULT_KEY9        IDR_NONE
#define IDR_DEFAULT_KEY10       IDR_NONE
#define IDR_DEFAULT_KEYC3       IDR_BUTTON3
#define IDR_DEFAULT_KEYC4       IDR_NONE
#define IDR_DEFAULT_KEYC5       IDR_NONE
#define IDR_DEFAULT_KEYC6       IDR_NONE
#define IDR_DEFAULT_KEYC7       IDR_NONE
#define IDR_DEFAULT_KEYC8       IDR_NONE
#define IDR_DEFAULT_KEYC9       IDR_NONE
#define IDR_DEFAULT_KEYC10      IDR_NONE
#define IDR_DEFAULT_KEYA3       IDR_BUTTON3
#define IDR_DEFAULT_KEYA4       IDR_NONE
#define IDR_DEFAULT_KEYA5       IDR_NONE
#define IDR_DEFAULT_KEYA6       IDR_NONE
#define IDR_DEFAULT_KEYA7       IDR_NONE
#define IDR_DEFAULT_KEYA8       IDR_NONE
#define IDR_DEFAULT_KEYA9       IDR_NONE
#define IDR_DEFAULT_KEYA10      IDR_NONE

/* Logitech mouse types */
#define IDRC_LOGI_TYPE          1400

/* Logitech receiver types */
#define IDRC_LOGI_RCV           1500

#endif /* RES_H */
