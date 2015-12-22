/***************************************************************************\
 *
 * PROGRAMMNAME: AMouse
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: AMouHData.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr AMouData.C
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
#ifndef AMOUHDATA_H
#define AMOUHDATA_H

typedef struct
    {
    HWND    hwnd;
    ULONG   flWindow;
    } WINDOWDATA, *PWINDOWDATA;

#define CULWNDPAGE      16                          // max 64kByte
//#define CULWNDPERPAGE   (0x1000/sizeof(WINDOWDATA)) // number of entries per page

extern ULONG        ulcBytePerPage;

extern HAB          habDLL;
extern HMODULE      hModule;

extern PWINDOWDATA  parWindow;
extern ULONG        ulcWindow;

#endif /* AMOUHDATA_H */
