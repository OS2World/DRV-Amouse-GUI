/***************************************************************************\
 *
 * PROGRAMMNAME: WPDCF77
 * -------------
 *
 * VERSION: 1.0
 * --------
 *
 * MODULNAME: NBAUDIO.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Debug-Funktionen
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    01-31-00  First Release
 *
 *  Copyright (C) noller & breining software 2000
 *
\******************************************************************************/
#ifndef NBAUDIO_H
#define NBAUDIO_H

ULONG _System MciPlayFile (HWND hwnd, PSZ pszFilename);
BOOL  _System MciLoadFile (HWND hwnd, ULONG ulQwlIndex, PCHAR pszFileName, ULONG ulNumOfPlays);
VOID  _System MciStartPlayBack (HWND hwnd, ULONG ulQwlIndex, USHORT usFinishedMsg);
VOID  _System MciPassDevice (HWND hwnd, ULONG ulQwlIndex, SHORT sAction);
VOID  _System MciActivate (HWND hwnd, ULONG ulQwlIndex, BOOL isActive);
VOID  _System MciCheckRedo (HWND hwnd, ULONG ulQwlIndex);
VOID  _System MciClose (HWND hwnd, ULONG ulQwlIndex);

#endif /* NBAUDIO_H */
