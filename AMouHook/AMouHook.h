/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: HOOK.H
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
#ifndef HOOK_H
#define HOOK_H

VOID EXPENTRY initHookDLL (HAB hab);
BOOL EXPENTRY insertHooks (void);
BOOL EXPENTRY releaseHooks (void);
BOOL APIENTRY inputHookProc (HAB hab, PQMSG pQmsg, ULONG fs);
BOOL EXPENTRY destroyWindowHookProc (HAB hab, HWND hwnd, ULONG ulReserved);

/* definitions for buttons corresponding to some frame control flags */
#define FCB_MINBUTTON       0x0001
#define FCB_MAXBUTTON       0x0002
#define FCB_CLOSEBUTTON     0x0004
#define FCB_HIDEBUTTON      0x0008
#define FCB_RESTOREBUTTON   0x0010

#endif /* HOOK_H */
