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
#ifndef DIALOGS_H
#define DIALOGS_H

BOOL             checkForWheelMouse (HMODULE hModule);
MRESULT EXPENTRY AboutDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY DeviceInfoDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY WlDeviceInfoDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY KeySettings1DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY KeySettings2DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY WheelSettings1DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY WheelSettings2DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY WheelSettings3DlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY TimingSettingsDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);

#endif /* DIALOGS_H */
