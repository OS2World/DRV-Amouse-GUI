/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUDLL
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: AMOUHWND
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   This DLL is registered at the OS/2 Presentation Manager. It starts
 *   the WheelThread after establishing the semaphores and shared memory
 *   necessary for communication with the WPS class
 *
 * FUNKTIONEN:
 * -----------
 *
 *
 *
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.10    05-12-02  Handling of shift-keys
 *  2.20    10-03-02  USB support added
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added; memory leak removed
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *
 *  Copyright (C) noller & breining software 2001...2004
 *
\******************************************************************************/
#define INCL_DOSSEMAPHORES
#define INCL_DOSMEMMGR
#define INCL_DOSPROCESS
#define INCL_DOSERRORS
#include <os2.h>

#include <memory.h>

#include "AMouHwnd.h"
#include "AMouHData.h"

/*******************************************************************\
  local data segment (process specific)
\*******************************************************************/

/*******************************************************************\
  global data segment
\*******************************************************************/
#pragma data_seg(GLOBAL_SEG)

BOOL allocSharedHwndArray (VOID)
    {
    if (NO_ERROR != DosAllocSharedMem ((PVOID *)&parWindow, NULL, 0x2000, OBJ_GETTABLE | PAG_READ | PAG_WRITE))
        return FALSE;

    return TRUE;
    }

VOID freeSharedHwndArray (VOID)
    {
    DosFreeMem (parWindow);

    return;
    }

BOOL getSharedHwndArray (VOID)
    {
    if (NO_ERROR != DosGetSharedMem ((PVOID *)parWindow, PAG_READ | PAG_WRITE))
        return FALSE;

    return TRUE;
    }

LONG findWindow (HWND hwnd)
    {
    LONG    l;

    // is hwnd valid?
    if (hwnd == NULLHANDLE)
        return -1;

    // search for empty entry and insert new window handle
    for (l = 0; l < ulcWindow; l++)
        {
        if (parWindow[l].hwnd == hwnd)
            return l;
        }

    return -1;
    }

BOOL EXPENTRY findWindowHandle (HWND hwnd, PULONG pflWindow)
    {
    LONG lWindow = findWindow (hwnd);

    if (lWindow >= 0)
        *pflWindow = parWindow[lWindow].flWindow;

    return (lWindow < 0 ? FALSE : TRUE);
    }

BOOL EXPENTRY removeWindowHandle (HWND hwnd)
    {
    LONG lWindow = findWindow (hwnd);

    if (lWindow >= 0)
        {
        ulcWindow--;
        parWindow[lWindow] = parWindow[ulcWindow];
        parWindow[ulcWindow].hwnd     = 0;
        parWindow[ulcWindow].flWindow = 0;
        return TRUE;
        }

    return FALSE;
    }

/*******************************************************************\
    addWindowHandle: adds a window handle to a registration list
                     of windows, that will receive WM_MOUSEWHEEL-
                     messages. The list is a linked list of
                     4k-pages, that contain the window handles.
                     empty entries contain NULLHANDLE
                     (HWND_DESKTOP never registers for this messages).
    Input:  hwnd:     window to be registered
            flWindow: operation modifier
    Return: TRUE, if successful
\*******************************************************************/
BOOL EXPENTRY addWindowHandle (HWND hwnd, ULONG flWindow)
    {
    PID     pid;
    TID     tid;
    ULONG   ulcb;
    ULONG   ulFlags;
    APIRET  rc;
    PPIB    ppib = NULL;

    // is hwnd valid window handle? Window must have been created by current process
    if (hwnd == NULLHANDLE)
        return FALSE;

//???    if (WinIsWindow (habDLL, hwnd) == FALSE)
//???        return FALSE;

//???    if (WinQueryWindowProcess (hwnd, &pid, &tid) == FALSE)
//???        return FALSE;

//???    DosGetInfoBlocks (NULL, &ppib);
//???    if (ppib->pib_ulpid != pid)
//???        return FALSE;

    // see if array is allocated; terminate, if not
    if (parWindow == NULL)
        return FALSE;

    if (findWindow (hwnd) >= 0)
        return FALSE;

    // search for empty entry and insert new window handle: ulcWindow contains number
    // of entries. If this is the last entry in page, allocate a new page
    if ((ulcWindow % (ulcBytePerPage / sizeof(WINDOWDATA))) == 0)
        {
        ulcb    = CULWNDPAGE * ulcBytePerPage;
        ulFlags = 0;
        rc = DosQueryMem ((PVOID *)parWindow, &ulcb, &ulFlags);
        if (NO_ERROR != rc)
            return FALSE;
        if ( ((ulFlags & PAG_COMMIT) == 0) ||
            (((ulFlags & PAG_COMMIT) != 0) && (ulcb <= ulcWindow * sizeof (WINDOWDATA))))
            {
            rc = DosSetMem ((PVOID)((PCHAR)parWindow + ulcWindow * sizeof (WINDOWDATA)),
                            ulcBytePerPage,
                            PAG_COMMIT | PAG_READ | PAG_WRITE);
            if (NO_ERROR != rc)
                return FALSE;
            }
        }

    ulcWindow++;
    parWindow[ulcWindow-1].hwnd     = hwnd;
    parWindow[ulcWindow-1].flWindow = flWindow;

    return TRUE;
    }

