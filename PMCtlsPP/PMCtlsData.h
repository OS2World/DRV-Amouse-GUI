/***************************************************************************\
 *
 * PROGRAMMNAME: PMCTLSPP
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: PMCtlsData.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr PMCtlsData.C
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
#ifndef PMCTLSDATA_H
#define PMCTLSDATA_H

extern HAB     hab;

extern PFNWP pfnwpOldEntryFieldWndProc; // original window procedure of entry field
extern PFNWP pfnwpOldComboBoxWndProc;   // original window procedure of combo box

extern HEV   hevWheelThreadUpdate;      // semaphore for updating data in strucMouseData

extern ULONG ulFlgPmCtls;               // replace window classes flag

#endif /* PMCTLSDATA_H */
