/***************************************************************************\
 *
 * PROGRAMMNAME: AMouse
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMouseData.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr AMouseData.C
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
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#ifndef AMOUSEDATA_H
#define AMOUSEDATA_H

#define BUFFLEN     1024                // Length of ASCIIZ buffer

#ifndef AMOUSEDATA_DEFINED

extern CHAR     szBuffer[BUFFLEN];      // string buffer

extern BOOL     bIsWarp4;               // Operating system version

extern BOOL     bIsHelp;                // TRUE: Help verfÅgbar
extern HWND     hwndHelp;

extern HAB      hab;
extern HMODULE  hmod;                   // Module handle
extern HMODULE  hmodLng;                // Module-Handle Language DLL

#endif /* AMOUSEDATA_DEFINED */

#endif /* AMOUSEDATA_H */
