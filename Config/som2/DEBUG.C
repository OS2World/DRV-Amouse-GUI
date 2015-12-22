/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: DEBUG
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Bereitstellung der Debugfunktionen
 *
 * HINWEISE:
 * ---------
 *   1. myReplacementForSOMOutChar ersetzt die Standard SOMOutCharRoutine
 *      des SOM-Debug-Interfaces. Es gibt einzelne Zeichen Åber PMPRINTF aus
 *   2. DgbDlgProc ist die Dialog-Prozedur zur Einstellung der
 *      SOM-Debug-Variablen und der ulDebugMask-Maske
 *
 * FUNKTIONEN:
 * -----------
 * myReplacementForSOMOutChar ()
 * DbgDlgProc ()
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
#define INCL_WIN
#define INCL_DOS

#include <OS2.H>
#include <stdlib.h>

#include "AMouseGlobal.h"
#include "amouse.ih"
#include "debug.h"
#include "dlg.h"

#ifdef _TRACE_
ULONG ulDebugMask = -1;
BOOL  bOnFile = TRUE;
CHAR  szDebug[128];
CHAR  szNumber[32];
CHAR  szString[1024];
#endif /* _TRACE_ */

/* Define your replacement routine */
int SOMLINK myReplacementForSOMOutChar (char c)
    {
#ifdef _TRACE_
    pmprintf ("%c", c);
#endif /* _TRACE_ */

    return 1;
    }

#ifdef _TRACE_
MRESULT EXPENTRY DbgDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    static ULONG ulResult;
    CHAR szText[9];

    switch (msg)
        {
        case WM_INITDLG:
            ulResult = 0;
            WinSendDlgItemMsg (hwnd, DID_TL_0 + SOM_TraceLevel, BM_SETCHECK,
                MPFROMSHORT (1), 0);
            WinSendDlgItemMsg (hwnd, DID_WL_0 + SOM_WarnLevel, BM_SETCHECK,
                MPFROMSHORT (1), 0);
            WinSendDlgItemMsg (hwnd, DID_AL_0 + SOM_AssertLevel, BM_SETCHECK,
                MPFROMSHORT (1), 0);
            WinSendDlgItemMsg (hwnd, DID_DM, EM_SETTEXTLIMIT, MPFROMSHORT (8), MPVOID);
            WinSetDlgItemText (hwnd, DID_DM, _itoa (ulDebugMask, szText, 16));
            WinSendDlgItemMsg (hwnd, DID_DT, MLM_INSERT, MPFROMP (D_TEXT_MASK), MPVOID);
            break;

        case WM_CONTROL:
            switch (LONGFROMMP (mp1))
                {
                case DID_TL_0 + (BN_CLICKED<<16):
                case DID_TL_1 + (BN_CLICKED<<16):
                case DID_TL_2 + (BN_CLICKED<<16):
                    ulResult &= ~(3 << SHFT_TRACE);
                    ulResult += (SHORT1FROMMP (mp1) - DID_TL_0) << SHFT_TRACE;
                    break;

                case DID_WL_0 + (BN_CLICKED<<16):
                case DID_WL_1 + (BN_CLICKED<<16):
                case DID_WL_2 + (BN_CLICKED<<16):
                    ulResult &= ~(3 << SHFT_WARN);
                    ulResult += (SHORT1FROMMP (mp1) - DID_WL_0) << SHFT_WARN;
                    break;
                case DID_AL_0 + (BN_CLICKED<<16):
                case DID_AL_1 + (BN_CLICKED<<16):
                case DID_AL_2 + (BN_CLICKED<<16):
                    ulResult &= ~(3 << SHFT_ASSERT);
                    ulResult += (SHORT1FROMMP (mp1) - DID_AL_0) << SHFT_ASSERT;
                    break;

                case DID_DM + (EN_KILLFOCUS<<16):
                    WinQueryDlgItemText (hwnd, DID_DM, 9, szText);
                    ulDebugMask = strtoul (szText, NULL, 16);
                    break;
                }
            return 0;

        case WM_CLOSE:
            WinDismissDlg (hwnd, ulResult);
            return 0;
        }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
    }

/*******************************************************************
   Debug-Code fÅr die Ausgabe in eine Datei
 *******************************************************************/
void cvtHex (PCHAR sz, ULONG us, USHORT n)
    {
    USHORT i;
    CHAR   szTmp[9];
    PCHAR  psz;

    _ultoa (us, szTmp, 16);
    for (psz=sz, i=0; i<n; i++)
        *psz++ = '0';
    *psz = '\0';

    strcpy (sz+n-strlen (szTmp), szTmp);
    return;
    }

void wrtDebug (USHORT n, PCHAR szClassname, PCHAR szTitle, ...)
    {
    va_list   parg;
    HFILE     hFile;
    USHORT    usArg, i, cArg;
    ULONG     ulAction;
    ULONG     ulPointer;
    ULONG     ulTime;
    PSHORT    ps;
    PBYTE     pb;
    PTIB      ptib;
    PPIB      ppib;

    va_start (parg, szTitle);

    if (bOnFile)
        {
        DosOpen (DBGFILENAME, &hFile, &ulAction, 0, 0,
            OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_OPEN_IF_EXISTS,
            OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE,
            NULL);
        if (ulAction == FILE_CREATED)
            DosWrite (hFile, HEADING, strlen (HEADING), &ulAction);
        else
            DosSetFilePtr (hFile, 0, FILE_END, &ulPointer);
        }

    DosGetInfoBlocks (&ptib, &ppib);
    DosQuerySysInfo (QSV_TIME_LOW, QSV_TIME_LOW, &ulTime, sizeof (ulTime));

    strcpy (szString, szClassname);
    strcat (szString, "| ");
    if (bOnFile)
        {
        strcat (szString, _ultoa (ulTime, szNumber, 10));
        strcat (szString, " ");
        strcat (szString, _itoa (ptib->tib_ptib2->tib2_ultid, szNumber, 16));
        strcat (szString, " ");
        strcat (szString, _itoa (ppib->pib_ulpid, szNumber, 16));
        strcat (szString, ": ");
        }
    strcat (szString, szTitle);
    if (n > 0)
        strcat (szString, " => ");

    for (usArg = 1; usArg < n; usArg++)
        {
        switch (va_arg (parg, USHORT))
            {
            case DBG_ULONG_X:
                cvtHex (szString+strlen (szString), va_arg (parg, ULONG), 4);
                usArg++;
                break;

            case DBG_ULONG_D:
                _itoa (va_arg (parg, ULONG), szString+strlen (szString), 10);
                usArg++;
                break;

            case DBG_BYTEPTR:
                cArg = va_arg (parg, USHORT);
                pb   = va_arg (parg, PBYTE);
                for (i=0; i<cArg; i++)
                    cvtHex (szString+strlen (szString), (ULONG)(*pb++), 2);
                usArg += 2;
                break;

            case DBG_STRING:
                strcat (szString, va_arg (parg, PCHAR));
                usArg++;
                break;
            }
        }

    if (bOnFile)
        {
        strcat (szString, "\r\n");
        DosWrite (hFile, szString, strlen (szString), &ulAction);
        DosClose (hFile);
        }
    else
        pmprintf ("%s\n", szString);

    va_end (parg);
    return;
    }

#endif /* _TRACE_ */
