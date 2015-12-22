/***************************************************************************\
 *
 * PROGRAMMNAME: PMCTLSPP
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: ENTRYDLGPROC
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   new window procedure for entry fields
 *
 * FUNKTIONEN:
 * -----------
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
#define  INCL_DOS
#define  INCL_WIN
#define  INCL_GPI
#define  INCL_ERRORS
#include <os2.h>

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <Log.h>
#include "AMouseGlobal.h"
#include "PMCtlsData.h"
#include "PmCtlsPP.h"

/*******************************************************************\
  local data segment (process specific)
\*******************************************************************/

/*******************************************************************\
  global data segment
\*******************************************************************/
#pragma data_seg(GLOBAL_SEG)

/*******************************************************************************\
 *      Entry Field Window Procedure                                           *
\*******************************************************************************/
BOOL EntryFieldButton1DblClk (HWND hwnd)
    {
    ULONG ulCursor;
    LONG  lTextLength;
    PCHAR pc;
    PCHAR pc1, pc2;

    // Determine cursor position
    ulCursor = (ULONG)WinSendMsg (hwnd, EM_QUERYSEL, MPVOID, MPVOID);
    if ((ulCursor & 0xFFFF) != (ulCursor >> 16))
        return TRUE;

    ulCursor &= 0xFFFF;

    // Get entry field contents
    lTextLength = WinQueryWindowTextLength (hwnd) + 1;
    if (DosAllocMem ((PPVOID)&pc, lTextLength, PAG_COMMIT | PAG_READ | PAG_WRITE) != NO_ERROR)
        return TRUE;

    WinQueryWindowText (hwnd, lTextLength, pc);

    // Determine new selection
    for (pc1 = pc + ulCursor; pc1 > pc; pc1--)
        {
        if (*(pc1-1) == ' ')
            break;
        }

    for (pc2 = pc + ulCursor; pc2 < pc + lTextLength; pc2++)
        {
        if (*pc2 == ' ')
            break;
        }

    // Set selection
    WinSendMsg (hwnd, EM_SETSEL, MPFROM2SHORT ((pc1-pc), (pc2-pc)), MPVOID);
    DosFreeMem (pc);

    return TRUE;
    }

MRESULT EXPENTRY EntryFieldDialogProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    if (ulFlgPmCtls & PMCTL_ENTRY)
        {
        switch (msg)
            {
            case WM_BUTTON1DBLCLK:
                return (MRESULT)EntryFieldButton1DblClk (hwnd);
            }
        }

    return (MRESULT)pfnwpOldEntryFieldWndProc (hwnd, msg, mp1, mp2);
    }

