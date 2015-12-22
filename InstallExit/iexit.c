/***************************************************************************\
 *
 * PROGRAMMNAME: IEXIT
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: IEXIT
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   OS/2-Installer Exit-DLL zur Abfrage der zu installierenden Komponente
 *
 * FUNKTIONEN:
 * -----------
 *
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    15-07-01  First release
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#define INCL_WIN
#define INCL_DOS
#define INCL_DOSERRORS

#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <varsfp.h>

#include "dlg.h"

#include <stdio.h>

/*******************************************************************
   Debug-Definitionen; zu TRACE-Zwecken beim Compilieren
      "DEBUG" angeben!
 *******************************************************************/
#ifdef DEBUG
  void wrtDebug (USHORT n, PCHAR pszTitle, ...);

  #define DBG_ULONG       1
  #define DBG_BYTEPTR     2
  #define DBG_SHORTPTR    3
  #define DBG_STRING      4
  #define DBG_CR          5

  #define DebugS(title)         wrtDebug(0, (title))
  #define DebugE(title,text)    wrtDebug(2, (title), DBG_STRING, (text))
  #define DebugPB(title,s,n,pb) wrtDebug(5, (title), DBG_STRING, (s), \
                                DBG_BYTEPTR, (n), (pb))
  #define DebugUL(title,s,ul)   wrtDebug(4, (title), DBG_STRING, (s), \
                                DBG_ULONG, (ul))
  #define HEADING  "TimeStamp TID PID: title => text\r\n"
  CHAR    szDebug[128];
  CHAR    szNumber[32];
  CHAR    szString[1024];
#else
  #define DebugS(title)
  #define DebugE(title,text)
  #define DebugPB(title,s,n,pb)
  #define DebugUL(title,s,ul)
#endif /* DEBUG */

MRESULT EXPENTRY ExitDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);

USHORT EXPENTRY SELECTCOMPONENT (CHAR *pzParameterString)
    {
    HWND     hwndOwner;
    ULONG    ulResult;
    HMQ      hmq;
    APIRET   rc;
    HMODULE  hMod = NULLHANDLE;

    DebugS ("SELECTCOMPONENT");

    rc = DosQueryModuleHandle ("iexit.dll", &hMod);
    DebugUL ("SELECTCOMPONENT", "hMod = ", (ULONG)hMod);

    if (rc)
        return 1;

    hwndOwner = (HWND)getowner ();
    hmq = WinCreateMsgQueue (WinQueryAnchorBlock (hwndOwner), 0);

    ulResult = WinDlgBox (HWND_DESKTOP,
                          hwndOwner,
                          (PFNWP)ExitDlgProc,
                          hMod,
                          IDD_IEXIT,
                          NULL);

    if (ulResult == DID_ERROR)
        return 2;

    DebugUL ("SELECTCOMPONENT", "ulResult = ", ulResult);
    putvar ("SELCOMPONENT", (ulResult == DID_WPS ? "WPS" : "PROG"));

    WinDestroyMsgQueue (hmq);
    return 0;
    }

/******************************************************************************
*
*   WheelSettingsDlgProc()
*
*   DESCRIPTION:  Dialog Procedure for wheel settings page
*
******************************************************************************/
MRESULT EXPENTRY ExitDlgProc (HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
    {
    switch (msg)
        {
        case WM_INITDLG:
            WinCheckButton (hwndDlg, DID_WPS, 1);
            return (MRESULT)FALSE;

        case WM_COMMAND:
            {
            USHORT usCheckState;
            switch (SHORT1FROMMP (mp1))
                {
                case DID_OK:
                    usCheckState = WinQueryButtonCheckstate (hwndDlg, DID_WPS);
                    WinDismissDlg (hwndDlg, (usCheckState ? DID_WPS : DID_PROGRAM));
                    return 0;

                } /* end switch (SHORT1FROMMP(mp1)) */
            break;
            }
        } /* end switch(msg) */

   return WinDefDlgProc (hwndDlg, msg, mp1, mp2);
   } /* end ExitDlgProc() */

/*******************************************************************
   Debug-Code; zu TRACE-Zwecken beim Compilieren "DEBUG" angeben!
 *******************************************************************/
#ifdef DEBUG
void cvtHex (PCHAR sz, ULONG ul, USHORT n)
    {
    USHORT i;
    CHAR   szTmp[9];
    PCHAR  psz;

    _itoa (ul, szTmp, 16);
    for (psz=sz, i=0; i<n; i++)
        *psz++ = '0';
    *psz = '\0';

    strcpy (sz+n-strlen (szTmp), szTmp);
    return;
    }

void wrtDebug (USHORT n, PCHAR szTitle, ...)
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

    DosOpen ("$$AMOU$$.DBG", &hFile, &ulAction, 0, 0,
        OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_OPEN_IF_EXISTS,
        OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE,
        NULL);
    if (ulAction == FILE_CREATED)
        {
        DosWrite (hFile, HEADING, strlen (HEADING), &ulAction);
        }
    else
        DosSetFilePtr (hFile, 0, FILE_END, &ulPointer);
    DosGetInfoBlocks (&ptib, &ppib);
    DosQuerySysInfo (QSV_TIME_LOW, QSV_TIME_LOW, &ulTime, sizeof (ulTime));
    strcpy (szString, _ultoa (ulTime, szNumber, 10));
    strcat (szString, " ");
    strcat (szString, _itoa (ptib->tib_ptib2->tib2_ultid, szNumber, 16));
    strcat (szString, " ");
    strcat (szString, _itoa (ppib->pib_ulpid, szNumber, 16));
    strcat (szString, ": ");
    strcat (szString, szTitle);
    if (n > 0)
        strcat (szString, " => ");

    for (usArg = 1; usArg < n; usArg++)
        {
        switch (va_arg (parg, USHORT))
            {
            case DBG_ULONG:
                cvtHex (szString+strlen (szString), va_arg (parg, ULONG), 8);
                usArg++;
                break;

            case DBG_BYTEPTR:
                cArg = va_arg (parg, USHORT);
                pb   = va_arg (parg, PBYTE);
                for (i=0; i<cArg; i++)
                    cvtHex (szString+strlen (szString), *pb++, 2);
                usArg += 2;
                break;

            case DBG_SHORTPTR:
                cArg = va_arg (parg, USHORT);
                ps   = va_arg (parg, PSHORT);
                for (i=0; i<cArg; i++)
                    cvtHex (szString+strlen (szString), *ps++, 4);
                usArg += 2;
                break;

            case DBG_STRING:
                strcat (szString, va_arg (parg, PCHAR));
                usArg++;
                break;

            case DBG_CR:
                strcat (szString, "\r\n\t\t");
                break;
            }
        }

    strcat (szString, "\r\n");
    DosWrite (hFile, szString, strlen (szString), &ulAction);
    DosClose (hFile);

    va_end (parg);
    return;
    }

#endif /* DEBUG */

