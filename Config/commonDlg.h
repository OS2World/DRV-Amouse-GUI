/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: DIALOGS.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr DIALOGS.C
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    02-20-00  First release
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
#ifndef COMMONDLG_H
#define COMMONDLG_H

#define CCHMAXPAGETYPE  64

/***** window data for settings notebook *****/
typedef struct _CREATEDATA
    {
    USHORT    cb;
    AMouse   *somObject;
    ULONG     ulPageType;
    } CREATEDATA, *PCREATEDATA;

/***** window data for wheel page 1 *****/
typedef struct _WHEELDLG1DATA
    {
    USHORT    cb;
    AMouse   *somObject;
    M_AMouse *somClassObject;
    ULONG     ulWheelPageType;
    ULONG     currScrollMode;
    ULONG     prevScrollMode;
    ULONG     currScrollNum;
    ULONG     prevScrollNum;
    ULONG     currWheelTarget;
    ULONG     prevWheelTarget;
    } WHEELDLG1DATA, *PWHEELDLG1DATA;

// definitions for WHEELDLG1DATA.ulWheelPageType
#define WHEELPAGE_NONE      0
#define WHEELPAGE_CTRL      1
#define WHEELPAGE_ALT       2

/***** window data for wheel page 2 *****/
typedef struct _WHEELDLG2DATA
    {
    USHORT    cb;
    AMouse   *somObject;
    M_AMouse *somClassObject;
    ULONG     currStartupMode;
    ULONG     prevStartupMode;
    ULONG     currAccelDelay;
    ULONG     prevAccelDelay;
    ULONG     currAccelValue;
    ULONG     prevAccelValue;
    ULONG     currWheelCount;
    ULONG     prevWheelCount;
    } WHEELDLG2DATA, *PWHEELDLG2DATA;

/***** window data for wheel page 3 *****/
typedef struct _WHEELDLG3DATA
    {
    USHORT    cb;
    AMouse   *somObject;
    M_AMouse *somClassObject;
    PSTRUCTAPPL
              currApplications;
    } WHEELDLG3DATA, *PWHEELDLG3DATA;

/***** window data for timing page *****/
typedef struct _TIMINGDLGDATA
    {
    USHORT    cb;
    AMouse   *somObject;
    M_AMouse *somClassObject;
    ULONG     currPollingRate;
    ULONG     prevPollingRate;
    ULONG     currAccelLevel1;
    ULONG     prevAccelLevel1;
    ULONG     currAccelLevel1Mult;
    ULONG     prevAccelLevel1Mult;
    ULONG     currAccelLevel2;
    ULONG     prevAccelLevel2;
    ULONG     currAccelLevel2Mult;
    ULONG     prevAccelLevel2Mult;
    } TIMINGDLGDATA, *PTIMINGDLGDATA;

/***** window data for button page 1 *****/
typedef struct _KEYDLG1DATA
    {
    USHORT    cb;
    AMouse   *somObject;
    M_AMouse *somClassObject;
    ULONG     ulBtnPageType;
    UCHAR     currBtnMode[CULNUMBUTTONS];
    UCHAR     prevBtnMode[CULNUMBUTTONS];
    ULONG     currBtnMP1[CULNUMBUTTONS];
    ULONG     prevBtnMP1[CULNUMBUTTONS];
    ULONG     currBtnMP2[CULNUMBUTTONS];
    ULONG     prevBtnMP2[CULNUMBUTTONS];
    } KEYDLG1DATA, *PKEYDLG1DATA;

// definitions for KEYDLG1DATA.ulBtnPageType
#define BTNPAGE_NONE        0
#define BTNPAGE_CTRL        1
#define BTNPAGE_ALT         2

/***** window data for entry field subclass *****/
typedef struct _KEYCOMBDATA
    {
    USHORT    cb;
    AMouse   *somObject;
    ULONG     ulCharMP1;
    ULONG     ulCharMP2;
    PACCELTABLE pacctAccelTable;
    } KEYCOMBDATA, *PKEYCOMBDATA;

/***** window data for button page 2 *****/
typedef struct _KEYDLG2DATA
    {
    USHORT    cb;
    AMouse   *somObject;
    M_AMouse *somClassObject;
    ULONG     currFlgPmCtls;
    ULONG     prevFlgPmCtls;
    ULONG     currSmartCruise;
    ULONG     prevSmartCruise;
    } KEYDLG2DATA, *PKEYDLG2DATA;

/***** window data for behavior dialog box *****/
typedef struct _INSERTAPPLDLGDATA
    {
    USHORT    cb;
    AMouse   *somObject;
    M_AMouse *somClassObject;
    PSTRUCTAPPL
              pApplications;
    } INSERTAPPLDLGDATA, *PINSERTAPPLDLGDATA;

VOID _System BatteryCheckThread (ULONG ulParm);

VOID SetDebugMode (BOOL bDebugMode);
VOID SetButtonsWheelSettings1 (HWND hwndDlg, M_AMouse *somClassObject, PWHEELDLG1DATA pWheelDlgData);
VOID SetWheelSettings2Controls (HWND hwndDlg, ULONG ulWheelCount, ULONG ulStartupMode);

MRESULT KeySettings1InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject, ULONG ulPageType);
VOID    KeySettings1Destroy (HWND hwndDlg);
MRESULT KeySettings1Command (HWND hwndDlg, MPARAM mp1);
MRESULT KeySettings1Control (HWND hwndDlg, MPARAM mp1);

MRESULT KeySettings2InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject);
VOID    KeySettings2Destroy (HWND hwndDlg);
MRESULT KeySettings2Command (HWND hwndDlg, MPARAM mp1);
MRESULT KeySettings2Control (HWND hwndDlg, MPARAM mp1);

MRESULT WheelSettings1InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject, ULONG ulPageType);
VOID    WheelSettings1Destroy (HWND hwndDlg);
MRESULT WheelSettings1Command (HWND hwndDlg, MPARAM mp1);
MRESULT WheelSettings1Control (HWND hwndDlg, MPARAM mp1);

MRESULT WheelSettings2InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject);
VOID    WheelSettings2Destroy (HWND hwndDlg);
MRESULT WheelSettings2Command (HWND hwndDlg, MPARAM mp1);
MRESULT WheelSettings2Control (HWND hwndDlg, MPARAM mp1);

MRESULT WheelSettings3InitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject);
VOID    WheelSettings3Destroy (HWND hwndDlg);
MRESULT WheelSettings3Command (HWND hwndDlg, MPARAM mp1);
MRESULT WheelSettings3Control (HWND hwndDlg, MPARAM mp1);

MRESULT TimingSettingsInitDlg (HWND hwndDlg, AMouse *somObject, M_AMouse *somClassObject);
VOID    TimingSettingsDestroy (HWND hwndDlg);
MRESULT TimingSettingsCommand (HWND hwndDlg, MPARAM mp1);
MRESULT TimingSettingsControl (HWND hwndDlg, MPARAM mp1);

MRESULT DeviceInfoInitDlg (HWND hwndDlg);
MRESULT DeviceInfoCommand (HWND hwndDlg, MPARAM mp1);

MRESULT WlDeviceInfoInitDlg (HWND hwndDlg);
MRESULT WlDeviceInfoControl (HWND hwndDlg, MPARAM mp1);

#endif /* COMMONDLG_H */
