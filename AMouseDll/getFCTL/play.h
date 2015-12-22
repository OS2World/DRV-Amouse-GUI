/***************************************************************************\
 *
 * PROGRAMMNAME: WPDCF77
 * -------------
 *
 * VERSION: 5.2
 * --------
 *
 * MODULNAME: PLAY.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Prototyp-Definitionen fÅr Audio-Support
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  4.20    09-12-96  UnterstÅtzung fÅr hopf 6038
 *  4.40    01-31-00  Multimedia-UnterstÅtzung, Bugfixing
 *  5.10    02-10-01  Fehlerkorrektur Positionsspeicherung Iconview
 *  5.20    06-09-01  Fehlerkorrektur Audiodaten
 *
 *  Copyright (C) noller & breining software 1995...2001
 *
\******************************************************************************/
#ifndef PLAY_H
#define PLAY_H

BOOL ClkMciPlayFile (HWND hwnd, PSZ pszFileName);
BOOL ClkMciLoadFile (HWND hwnd, ULONG ulQwlIndex, PCHAR pszFileName, ULONG ulNumOfPlays);
VOID ClkMciStartPlayBack (HWND hwnd, ULONG ulQwlIndex, USHORT usFinishedMsg);
VOID ClkMciCheckRedo (HWND hwnd, ULONG ulQwlIndex);
VOID ClkMciClose (HWND hwnd, ULONG ulQwlIndex);
VOID ClkMciPassDevice (HWND hwnd, ULONG ulQwlIndex, SHORT sAction);
VOID ClkMciActivate (HWND hwnd, ULONG ulQwlIndex, BOOL isActive);
BOOL ClkMciIsMultimedia (VOID);

#endif /* PLAY_H */
