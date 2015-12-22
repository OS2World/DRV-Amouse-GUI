/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: DEBUG.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Debug-Funktionen
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
#ifndef DEBUG_H
#define DEBUG_H

#ifndef CLASSNAME
#define CLASSNAME   "AMOUSE"        // Als Id-String fr Instanzvariable
#endif /* CLASSNAME */

#ifndef DBGFILENAME
#define DBGFILENAME "$$AMOUSE$$.DBG"
#endif /* DBGFILENAME */

int SOMLINK myReplacementForSOMOutChar (char);

/* Private Debug-Hilfroutinen fr PMPRINTF */
#ifdef _TRACE_
  int  pmprintf(char *f, ...);
  void wrtDebug (USHORT n, PCHAR szClassname, PCHAR szTitle, ...);
  MRESULT EXPENTRY DbgDlgProc       (HWND, ULONG, MPARAM, MPARAM);

  /* Zahl der Bit-Shifts fr SOM_*Level - Variable */
  #define SHFT_TRACE              0
  #define SHFT_WARN               2
  #define SHFT_ASSERT             4

  /* DEBUG-Maske */
  #define D_IO      0x00000001      // Kommunikation mit Treiber
  #define D_DIAG    0x00000002      // Diagnostik: interne Fehler
  #define D_DLG     0x00000004      // Diagnose in Dialog-Panels
  #define D_SOM     0x00000008      // SOM-Methoden

  /* Hilfe-Text fr DEBUG-Maske */
  #define D_TEXT_MASK   "\
D_IO      Kommunikation mit Treiber    0x00000001\n\
D_DIAG    Diagnostik: interne Fehler   0x00000002\n\
D_DLG     Diagnose in Dialog-Panels    0x00000004\n\
D_SOM     SOM-Methoden                 0x00000008\n"

  extern ULONG ulDebugMask;
  extern CHAR  szDebug[128];
  extern CHAR  szNumber[32];
  extern CHAR  szString[1024];
  extern BOOL  bOnFile;

  #define HEADING  "Class TimeStamp PID TID: title => text\r\n"

  #define DBG_ULONG_X     1
  #define DBG_ULONG_D     2
  #define DBG_BYTEPTR     3
  #define DBG_STRING      4

  #define DebugS(m,title)         if (m&ulDebugMask) wrtDebug(0, CLASSNAME, (title))
  #define DebugE(m,title,text)    if (m&ulDebugMask) wrtDebug(2, CLASSNAME, (title), DBG_STRING, (text))
  #define DebugPB(m,title,s,n,pb) if (m&ulDebugMask) wrtDebug(5, CLASSNAME, (title), DBG_STRING, (s), \
                                                              DBG_BYTEPTR, (n), (pb))
  #define DebugULd(m,title,s,ul)  if (m&ulDebugMask) wrtDebug(4, CLASSNAME, (title), DBG_STRING, (s), \
                                                              DBG_ULONG_D, (ul))
  #define DebugULx(m,title,s,ul)  if (m&ulDebugMask) wrtDebug(4, CLASSNAME, (title), DBG_STRING, (s), \
                                                              DBG_ULONG_X, (ul))
#else
  #define DebugS(m,title)
  #define DebugE(m,title,text)
  #define DebugPB(m,title,s,n,pb)
  #define DebugULd(m,title,s,ul)
  #define DebugULx(m,title,s,ul)
#endif /* _TRACE_ */

#endif /*  DEBUG_H */
