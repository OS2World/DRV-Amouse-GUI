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
#ifndef AUDIO_H
#define AUDIO_H

LONG _System MciGetMasterVolume (VOID);
VOID _System MciSetMasterVolume (LONG lVolume);

#endif /* AUDIO_H */
