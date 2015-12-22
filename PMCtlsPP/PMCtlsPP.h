/***************************************************************************\
 *
 * PROGRAMMNAME: PMCTLSPP
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: PMCtlsPP.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr PMCtlsPP.C
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
#ifndef PMCTLSPP_H
#define PMCTLSPP_H

/*******************************************************************\
  type definitions an function prototypes
\*******************************************************************/
typedef struct _STRUCTCLASS
    {
    PSZ     pszClassName;       // name of class to be replaced as used in WinRegisterClass
    PFN     pPrivRegisterClass; // private class registration, if not NULL
    PFNWP   pWndProc;           // new window procedure
    PFNWP  *ppOldWndProc;       // original window procedure
    } STRUCTCLASS, *PSTRUCTCLASS;

MRESULT EXPENTRY EntryFieldDialogProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY ComboBoxDialogProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

BOOL APIENTRY ComboBoxRegisterClass (HAB hab, PSZ pszClassName, PFNWP pfnWndProc, ULONG flStyle, ULONG cbWindowData);

/*******************************************************************\
  local data segment (process specific)
\*******************************************************************/
extern HMODULE hModule;

/*******************************************************************\
  global data segment
\*******************************************************************/
extern PFNWP pfnwpOldEntryFieldWndProc;
extern PFNWP pfnwpOldComboBoxWndProc;

#endif /* PMCTLSPP_H */
