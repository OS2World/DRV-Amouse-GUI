/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: AMOUSE
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Hauptprogramm
 *
 * FUNKTIONEN:
 * -----------
 *   addSettingsPage
 *   addNotebookPages
 *   _clsInitData
 *   _clsSetScrollMode
 *   _clsGetScrollMode
 *   _clsSetScrollNum
 *   _clsGetScrollNum
 *   _clsSetWheelTarget
 *   _clsGetWheelTarget
 *   _clsSetStartupMode
 *   _clsGetStartupMode
 *   _clsSetAccelDelay
 *   _clsGetAccelDelay
 *   _clsSetAccelValue
 *   _clsGetAccelValue
 *   _clsSetPollingRate
 *   _clsGetPollingRate
 *   _clsSetAccelLevel1
 *   _clsGetAccelLevel1
 *   _clsSetAccelLvl1Mult
 *   _clsGetAccelLvl1Mult
 *   _clsSetAccelLevel2
 *   _clsGetAccelLevel2
 *   _clsSetAccelLvl2Mult
 *   _clsGetAccelLvl2Mult
 *   _clsSetBtnMode
 *   _clsGetBtnMode
 *   _clsSetBtnKeyCombMP1
 *   _clsGetBtnKeyCombMP1
 *   _clsSetBtnKeyCombMP2
 *   _clsGetBtnKeyCombMP2
 *   _clsSetWheelCount
 *   _clsGetWheelCount
 *   _clsSetPMCtlsFlags
 *   _clsGetPMCtlsFlags
 *   _clsSetSmartCruise
 *   _clsGetSmartCruise
 *   _clsSetApplications
 *   _clsGetApplications
 *   main
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  1.00    20-02-00  First release
 *  2.00    06-16-01  WheelThread in separate process
 *  2.10    05-12-02  Handling of shift-keys
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
#define INCL_DOSERRORS

#include <os2.h>
#include <bsedev.h>
#include <string.h>
#include <stdlib.h>

#include <cutil.h>

#include "AMouseGlobal.h"
#include "AMouseData.h"
#include "AMouse.h"
#include "dialogs.h"
#include "res.h"
#include "common.h"
#include "commonDlg.h"
#include "dlg.h"

#define CCHMAXTITLE   80                    // Length of title in help window
#define CCHMAXPGNUM   32                    // Length of status text in notebook pages

HEV     hevWheelThreadUpdate = NULLHANDLE;  // semaphore to notice wheel thread of updated data

static CHAR szWindowTitle[CCHMAXTITLE];        // buffer for title of help window
static CHAR szErrorMsg[CCHMAXTITLE];           // buffer for "no wheel mouse" text
static CHAR szHelpFile[]   = "AMou001.hlp"; // default name of help file
static CHAR szModuleName[] = "AMou001";     // default module name of language dll

#pragma info(nopar)

BOOL addSettingsPage (HWND hwndNotebook, HMODULE hModule, PPAGEINFO pPageInfo, ULONG ulPageNum, ULONG ulMaxPageNum)
    {
    ULONG id;
    BOOL  bRc = FALSE;
    HWND  hwndPage;
    ULONG ulSize;
    CHAR  szPageNumSrc[CCHMAXPGNUM];
    CHAR  szPageNumDst[CCHMAXPGNUM];
    CHAR  szPageNum[2][2];
    PCHAR lvTable[2];

    hwndPage = WinLoadDlg (HWND_OBJECT,   /* Dialogbox laden */
                           hwndNotebook,
                           pPageInfo->pfnwp,
                           hModule,
                           pPageInfo->dlgid,
                           pPageInfo->pCreateParams);
    WinShowWindow (hwndPage, FALSE);

    if (hwndPage)
        {
        id = (ULONG)WinSendMsg (hwndNotebook,
                                BKM_INSERTPAGE,
                                MPFROMLONG (0),
                                MPFROM2SHORT (pPageInfo->usPageStyleFlags | BKA_STATUSTEXTON,
                                              pPageInfo->usPageInsertFlags));

        if (id)
            {
            bRc = (BOOL)WinSendMsg (hwndNotebook,
                                    BKM_SETPAGEWINDOWHWND,
                                    MPFROMLONG (id),
                                    MPFROMLONG (hwndPage));

            WinSendMsg (hwndNotebook,
                        BKM_SETTABTEXT,
                        MPFROMLONG (id),
                        MPFROMP (pPageInfo->pszName));

            if (ulMaxPageNum > 1)
                {
                WinLoadString (hab, hModule, IDS_PAGENUMBER, CCHMAXPGNUM, szPageNumSrc);
                _itoa (ulPageNum,    szPageNum[0], 10);
                _itoa (ulMaxPageNum, szPageNum[1], 10);
                lvTable[0] = szPageNum[0];
                lvTable[1] = szPageNum[1];

                DosInsertMessage (lvTable, 2,
                                  szPageNumSrc, strlen (szPageNumSrc),
                                  szPageNumDst, CCHMAXPGNUM,
                                  &ulSize);

                WinSendMsg (hwndNotebook,
                            BKM_SETSTATUSLINETEXT,
                            MPFROMLONG (id),
                            MPFROMP (szPageNumDst));
                }
            }
        }

    return bRc;
    }

VOID addNotebookPages (HWND hwndNotebook, HMODULE hModule)
    {
    CHAR       szPageWheelTitle[CCHMAXTITLE];
    CHAR       szPageButtonsTitle[CCHMAXTITLE];
    CHAR       szPageInfoTitle[CCHMAXTITLE];
    CHAR       szPageTimingTitle[CCHMAXTITLE];
    ULONG      ulPageId1, ulPageId2;
    PAGEINFO   strucPi1, strucPi2, strucPi3, strucPi4, strucPi5, strucPi6, strucPi7, strucPi8, strucPi9, strucPi10, strucPi11, strucPi12;
    CREATEDATA strucWheelData, strucWheelDataC, strucWheelDataA;
    CREATEDATA strucBtnData,   strucBtnDataC,   strucBtnDataA;

    WinLoadString (hab, hModule, IDS_PAGENAME_WHEEL,   CCHMAXTITLE, szPageWheelTitle);
    WinLoadString (hab, hModule, IDS_PAGENAME_BUTTONS, CCHMAXTITLE, szPageButtonsTitle);
    WinLoadString (hab, hModule, IDS_PAGENAME_DEVINFO, CCHMAXTITLE, szPageInfoTitle);
    WinLoadString (hab, hModule, IDS_PAGENAME_TIMING,  CCHMAXTITLE, szPageTimingTitle);

    strucWheelData.cb = strucWheelDataC.cb = strucWheelDataA.cb = sizeof (CREATEDATA);
    strucWheelData.ulPageType  = WHEELPAGE_NONE;
    strucWheelDataC.ulPageType = WHEELPAGE_CTRL;
    strucWheelDataA.ulPageType = WHEELPAGE_ALT;

    strucBtnData.cb = strucBtnDataC.cb = strucBtnDataA.cb = sizeof (CREATEDATA);
    strucBtnData.ulPageType  = WHEELPAGE_NONE;
    strucBtnDataC.ulPageType = WHEELPAGE_CTRL;
    strucBtnDataA.ulPageType = WHEELPAGE_ALT;

    memset ((PVOID)&strucPi1, '\0', sizeof (PAGEINFO));
    strucPi1.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi1.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi1.pfnwp               =  WheelSettings1DlgProc;          //  Window procedure.
    strucPi1.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi1.pCreateParams       =  (PVOID)&strucWheelData;         //  Pointer to creation parameters.
    strucPi1.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_WHEELSETTINGS1_40 : IDD_WHEELSETTINGS1;
    strucPi1.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MAJOR;   //  Notebook control-page style flags.
    strucPi1.usPageInsertFlags   =  BKA_FIRST;                      //  Notebook control-page insertion flags.
    strucPi1.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi1.pszName             =  szPageWheelTitle;               //  Pointer to a string containing the page name.
    strucPi1.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi1.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi1.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi1.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi1.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi2, '\0', sizeof (PAGEINFO));
    strucPi2.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi2.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi2.pfnwp               =  WheelSettings1DlgProc;          //  Window procedure.
    strucPi2.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi2.pCreateParams       =  (PVOID)&strucWheelDataC;        //  Pointer to creation parameters.
    strucPi2.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_WHEELSETTINGS1_40 : IDD_WHEELSETTINGS1;
    strucPi2.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;   //  Notebook control-page style flags.
    strucPi2.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi2.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi2.pszName             =  szPageWheelTitle;               //  Pointer to a string containing the page name.
    strucPi2.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi2.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi2.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi2.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi2.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi3, '\0', sizeof (PAGEINFO));
    strucPi3.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi3.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi3.pfnwp               =  WheelSettings1DlgProc;          //  Window procedure.
    strucPi3.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi3.pCreateParams       =  (PVOID)&strucWheelDataA;        //  Pointer to creation parameters.
    strucPi3.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_WHEELSETTINGS1_40 : IDD_WHEELSETTINGS1;
    strucPi3.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;   //  Notebook control-page style flags.
    strucPi3.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi3.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi3.pszName             =  szPageWheelTitle;               //  Pointer to a string containing the page name.
    strucPi3.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi3.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi3.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi3.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi3.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi4, '\0', sizeof (PAGEINFO));
    strucPi4.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi4.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi4.pfnwp               =  WheelSettings2DlgProc;          //  Window procedure.
    strucPi4.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi4.pCreateParams       =  NULL;                           //  Pointer to creation parameters.
    strucPi4.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_WHEELSETTINGS2_40 : IDD_WHEELSETTINGS2;
    strucPi4.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;   //  Notebook control-page style flags.
    strucPi4.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi4.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi4.pszName             =  szPageWheelTitle;               //  Pointer to a string containing the page name.
    strucPi4.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi4.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi4.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi4.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi4.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi5, '\0', sizeof (PAGEINFO));
    strucPi5.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi5.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi5.pfnwp               =  WheelSettings3DlgProc;          //  Window procedure.
    strucPi5.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi5.pCreateParams       =  NULL;                           //  Pointer to creation parameters.
    strucPi5.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_WHEELSETTINGS3_40 : IDD_WHEELSETTINGS3;
    strucPi5.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;   //  Notebook control-page style flags.
    strucPi5.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi5.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi5.pszName             =  szPageWheelTitle;               //  Pointer to a string containing the page name.
    strucPi5.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi5.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi5.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi5.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi5.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi6, '\0', sizeof (PAGEINFO));
    strucPi6.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi6.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi6.pfnwp               =  KeySettings1DlgProc;            //  Window procedure.
    strucPi6.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi6.pCreateParams       =  (PVOID)&strucBtnData;           //  Pointer to creation parameters.
    strucPi6.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_KEYSETTINGS1_40 : IDD_KEYSETTINGS1;
    strucPi6.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MAJOR;   //  Notebook control-page style flags.
    strucPi6.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi6.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi6.pszName             =  szPageButtonsTitle;             //  Pointer to a string containing the page name.
    strucPi6.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi6.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi6.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi6.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi6.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi7, '\0', sizeof (PAGEINFO));
    strucPi7.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi7.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi7.pfnwp               =  KeySettings1DlgProc;            //  Window procedure.
    strucPi7.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi7.pCreateParams       =  (PVOID)&strucBtnDataC;          //  Pointer to creation parameters.
    strucPi7.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_KEYSETTINGS1_40 : IDD_KEYSETTINGS1;
    strucPi7.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;   //  Notebook control-page style flags.
    strucPi7.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi7.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi7.pszName             =  szPageButtonsTitle;             //  Pointer to a string containing the page name.
    strucPi7.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi7.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi7.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi7.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi7.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi8, '\0', sizeof (PAGEINFO));
    strucPi8.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi8.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi8.pfnwp               =  KeySettings1DlgProc;            //  Window procedure.
    strucPi8.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi8.pCreateParams       =  (PVOID)&strucBtnDataA;          //  Pointer to creation parameters.
    strucPi8.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_KEYSETTINGS1_40 : IDD_KEYSETTINGS1;
    strucPi8.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;   //  Notebook control-page style flags.
    strucPi8.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi8.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi8.pszName             =  szPageButtonsTitle;             //  Pointer to a string containing the page name.
    strucPi8.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi8.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi8.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi8.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi8.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi9, '\0', sizeof (PAGEINFO));
    strucPi9.cb                  =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi9.hwndPage            =  NULLHANDLE;                     //  Handle of page.
    strucPi9.pfnwp               =  KeySettings2DlgProc;            //  Window procedure.
    strucPi9.resid               =  NULLHANDLE;                     //  Resource identity.
    strucPi9.pCreateParams       =  NULL;                           //  Pointer to creation parameters.
    strucPi9.dlgid               =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_KEYSETTINGS2_40 : IDD_KEYSETTINGS2;
    strucPi9.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;   //  Notebook control-page style flags.
    strucPi9.usPageInsertFlags   =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi9.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi9.pszName             =  szPageButtonsTitle;             //  Pointer to a string containing the page name.
    strucPi9.idDefaultHelpPanel  =  0;                              //  Identity of the default help panel.
    strucPi9.pszHelpLibraryName  =  NULL;                           //  Pointer to the name of the help file.
    strucPi9.pHelpSubtable       =  NULL;                           //  Pointer to the help subtable.
    strucPi9.hmodHelpSubtable    =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi9.ulPageInsertId      =  NULLHANDLE;                     //  Notebook control-page identity.

    memset ((PVOID)&strucPi10, '\0', sizeof (PAGEINFO));
    strucPi10.cb                  =  sizeof (PAGEINFO);             //  Length of PAGEINFO structure.
    strucPi10.hwndPage            =  NULLHANDLE;                    //  Handle of page.
    strucPi10.pfnwp               =  DeviceInfoDlgProc;             //  Window procedure.
    strucPi10.resid               =  NULLHANDLE;                    //  Resource identity.
    strucPi10.pCreateParams       =  NULL;                          //  Pointer to creation parameters.
    strucPi10.dlgid               =  bIsWarp4 ?                     //  Dialog identity.
                                     IDD_DEVICEINFO_40 : IDD_DEVICEINFO;
    strucPi10.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MAJOR;  //  Notebook control-page style flags.
    strucPi10.usPageInsertFlags   =  BKA_LAST;                      //  Notebook control-page insertion flags.
    strucPi10.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;         //  Settings flag.
    strucPi10.pszName             =  szPageInfoTitle;               //  Pointer to a string containing the page name.
    strucPi10.idDefaultHelpPanel  =  0;                             //  Identity of the default help panel.
    strucPi10.pszHelpLibraryName  =  NULL;                          //  Pointer to the name of the help file.
    strucPi10.pHelpSubtable       =  NULL;                          //  Pointer to the help subtable.
    strucPi10.hmodHelpSubtable    =  NULLHANDLE;                    //  Module handle for the help subtable.
    strucPi10.ulPageInsertId      =  NULLHANDLE;                    //  Notebook control-page identity.

    memset ((PVOID)&strucPi11, '\0', sizeof (PAGEINFO));
    strucPi11.cb                  =  sizeof (PAGEINFO);             //  Length of PAGEINFO structure.
    strucPi11.hwndPage            =  NULLHANDLE;                    //  Handle of page.
    strucPi11.pfnwp               =  WlDeviceInfoDlgProc;           //  Window procedure.
    strucPi11.resid               =  NULLHANDLE;                    //  Resource identity.
    strucPi11.pCreateParams       =  NULL;                          //  Pointer to creation parameters.
    strucPi11.dlgid               =  bIsWarp4 ?                     //  Dialog identity.
                                     IDD_WLDEVICEINFO_40 : IDD_WLDEVICEINFO;
    strucPi11.usPageStyleFlags    =  BKA_AUTOPAGESIZE | BKA_MINOR;  //  Notebook control-page style flags.
    strucPi11.usPageInsertFlags   =  BKA_LAST;                      //  Notebook control-page insertion flags.
    strucPi11.usSettingsFlags     =  SETTINGS_PAGE_NUMBERS;         //  Settings flag.
    strucPi11.pszName             =  szPageInfoTitle;               //  Pointer to a string containing the page name.
    strucPi11.idDefaultHelpPanel  =  0;                             //  Identity of the default help panel.
    strucPi11.pszHelpLibraryName  =  NULL;                          //  Pointer to the name of the help file.
    strucPi11.pHelpSubtable       =  NULL;                          //  Pointer to the help subtable.
    strucPi11.hmodHelpSubtable    =  NULLHANDLE;                    //  Module handle for the help subtable.
    strucPi11.ulPageInsertId      =  NULLHANDLE;                    //  Notebook control-page identity.

    memset ((PVOID)&strucPi12, '\0', sizeof (PAGEINFO));
    strucPi12.cb                 =  sizeof (PAGEINFO);              //  Length of PAGEINFO structure.
    strucPi12.hwndPage           =  NULLHANDLE;                     //  Handle of page.
    strucPi12.pfnwp              =  TimingSettingsDlgProc;          //  Window procedure.
    strucPi12.resid              =  NULLHANDLE;                     //  Resource identity.
    strucPi12.pCreateParams      =  NULL;                           //  Pointer to creation parameters.
    strucPi12.dlgid              =  bIsWarp4 ?                      //  Dialog identity.
                                    IDD_TIMINGSETTINGS_40 : IDD_TIMINGSETTINGS;
    strucPi12.usPageStyleFlags   =  BKA_AUTOPAGESIZE | BKA_MAJOR;   //  Notebook control-page style flags.
    strucPi12.usPageInsertFlags  =  BKA_LAST;                       //  Notebook control-page insertion flags.
    strucPi12.usSettingsFlags    =  SETTINGS_PAGE_NUMBERS;          //  Settings flag.
    strucPi12.pszName            =  szPageTimingTitle;              //  Pointer to a string containing the page name.
    strucPi12.idDefaultHelpPanel =  0;                              //  Identity of the default help panel.
    strucPi12.pszHelpLibraryName =  NULL;                           //  Pointer to the name of the help file.
    strucPi12.pHelpSubtable      =  NULL;                           //  Pointer to the help subtable.
    strucPi12.hmodHelpSubtable   =  NULLHANDLE;                     //  Module handle for the help subtable.
    strucPi12.ulPageInsertId     =  NULLHANDLE;                     //  Notebook control-page identity.

    addSettingsPage (hwndNotebook, hModule, &strucPi1,  1, 5);
    addSettingsPage (hwndNotebook, hModule, &strucPi2,  2, 5);
    addSettingsPage (hwndNotebook, hModule, &strucPi3,  3, 5);
    addSettingsPage (hwndNotebook, hModule, &strucPi4,  4, 5);
    addSettingsPage (hwndNotebook, hModule, &strucPi5,  5, 5);
    addSettingsPage (hwndNotebook, hModule, &strucPi6,  1, 4);
    addSettingsPage (hwndNotebook, hModule, &strucPi7,  2, 4);
    addSettingsPage (hwndNotebook, hModule, &strucPi8,  3, 4);
    addSettingsPage (hwndNotebook, hModule, &strucPi9,  4, 4);
    addSettingsPage (hwndNotebook, hModule, &strucPi10, 1, 2);
    addSettingsPage (hwndNotebook, hModule, &strucPi11, 2, 2);
    addSettingsPage (hwndNotebook, hModule, &strucPi12, 1, 1);

    /* Just to repaint the notebook page to overcome a bug */
    ulPageId1 = (ULONG)WinSendMsg (hwndNotebook, BKM_QUERYPAGEID, MPFROMLONG (0),         MPFROM2SHORT (BKA_FIRST, BKA_MAJOR));
    ulPageId2 = (ULONG)WinSendMsg (hwndNotebook, BKM_QUERYPAGEID, MPFROMLONG (ulPageId1), MPFROM2SHORT (BKA_NEXT,  BKA_MAJOR));
    WinSendMsg (hwndNotebook, BKM_TURNTOPAGE, MPFROMLONG (ulPageId2), MPVOID);
    WinSendMsg (hwndNotebook, BKM_TURNTOPAGE, MPFROMLONG (ulPageId1), MPVOID);

    return;
    }

/*--------------------------------------------------------------------*/
/* Class initialization method.  It initializes the instance data and */
/* then calls the parent's method.                                    */
/*--------------------------------------------------------------------*/
VOID _clsInitData (M_AMouse *somSelf)
    {
    TID tid;

    /* open/create semaphore for wheel thread unblocking */
    if (DosOpenEventSem (SEMNAMEEVT_UPDATE, &hevWheelThreadUpdate))
        DosCreateEventSem (SEMNAMEEVT_UPDATE, &hevWheelThreadUpdate, DC_SEM_SHARED, TRUE);

    /* Start Battery check thread */
    DosCreateThread (&tid, (PFNTHREAD)BatteryCheckThread,  (ULONG)0, 0L, 0x8000);

    return;
    }

VOID _clsSetScrollMode (M_AMouse *somSelf, ULONG ulWheelPageType, ULONG ulScrollMode)
    {
    PCHAR pKey;
    CHAR  sz[13];

    switch (ulWheelPageType)
        {
        case WHEELPAGE_NONE:
            pKey = KEY_SCROLLMODE;
            break;

        case WHEELPAGE_CTRL:
            pKey = KEY_SCROLLMODE_C;
            break;

        case WHEELPAGE_ALT:
            pKey = KEY_SCROLLMODE_A;
            break;
        }

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, pKey, _itoa (ulScrollMode, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetScrollMode (M_AMouse *somSelf, ULONG ulWheelPageType)
    {
    ULONG ulDefValue;
    PCHAR pKey;

    switch (ulWheelPageType)
        {
        case WHEELPAGE_NONE:
            ulDefValue = SCROLL_MODE_STD;
            pKey       = KEY_SCROLLMODE;
            break;

        case WHEELPAGE_CTRL:
            ulDefValue = SCROLL_MODE_NONE;
            pKey       = KEY_SCROLLMODE_C;
            break;

        case WHEELPAGE_ALT:
            ulDefValue = SCROLL_MODE_NONE;
            pKey       = KEY_SCROLLMODE_A;
            break;
        }

    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, pKey, ulDefValue);
    }

VOID _clsSetScrollNum (M_AMouse *somSelf, ULONG ulWheelPageType, ULONG ulNewScrollNum)
    {
    PCHAR pKey;
    CHAR  sz[13];

    switch (ulWheelPageType)
        {
        case WHEELPAGE_NONE:
            pKey = KEY_SCROLLNUM;
            break;

        case WHEELPAGE_CTRL:
            pKey = KEY_SCROLLNUM_C;
            break;

        case WHEELPAGE_ALT:
            pKey = KEY_SCROLLNUM_A;
            break;
        }

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, pKey, _itoa (ulNewScrollNum, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetScrollNum (M_AMouse *somSelf, ULONG ulWheelPageType)
    {
    PCHAR pKey;

    switch (ulWheelPageType)
        {
        case WHEELPAGE_NONE:
            pKey = KEY_SCROLLNUM;
            break;

        case WHEELPAGE_CTRL:
            pKey = KEY_SCROLLNUM_C;
            break;

        case WHEELPAGE_ALT:
            pKey = KEY_SCROLLNUM_A;
            break;
        }

    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, pKey, 3);
    }

VOID _clsSetWheelTarget (M_AMouse *somSelf, ULONG ulWheelPageType, ULONG ulNewWheelTarget)
    {
    PCHAR pKey;
    CHAR  sz[13];

    switch (ulWheelPageType)
        {
        case WHEELPAGE_NONE:
            pKey = KEY_WHEELTARGET;
            break;

        case WHEELPAGE_CTRL:
            pKey = KEY_WHEELTARGET_C;
            break;

        case WHEELPAGE_ALT:
            pKey = KEY_WHEELTARGET_A;
            break;
        }

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, pKey, _itoa (ulNewWheelTarget, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetWheelTarget (M_AMouse *somSelf, ULONG ulWheelPageType)
    {
    PCHAR pKey;

    switch (ulWheelPageType)
        {
        case WHEELPAGE_NONE:
            pKey = KEY_WHEELTARGET;
            break;

        case WHEELPAGE_CTRL:
            pKey = KEY_WHEELTARGET_C;
            break;

        case WHEELPAGE_ALT:
            pKey = KEY_WHEELTARGET_A;
            break;
        }

    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, pKey, WHEEL_TARGET_POINTER);
    }

VOID _clsSetStartupMode (M_AMouse *somSelf, ULONG ulStartupMode)
    {
    CHAR  sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_STARTUPMODE, _itoa (ulStartupMode, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetStartupMode (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_STARTUPMODE, SCROLL_DIR_VERT);
    }

VOID _clsSetAccelDelay (M_AMouse *somSelf, ULONG ulAccelDelay)
    {
    CHAR  sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELDELAY, _itoa (ulAccelDelay, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetAccelDelay (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELDELAY, ACCEL_DEF_DELAY);
    }

VOID _clsSetAccelValue (M_AMouse *somSelf, ULONG ulAccelValue)
    {
    CHAR  sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELVALUE, _itoa (ulAccelValue, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetAccelValue (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELVALUE, ACCEL_DEF_VALUE);
    }

VOID  _clsSetPollingRate (M_AMouse *somSelf, ULONG ulPollingRate)
    {
    CHAR sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_POLLINGRATE, _itoa (ulPollingRate, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetPollingRate (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_POLLINGRATE, DEF_VALUE_POLLING_RATE);
    }

VOID  _clsSetAccelLevel1 (M_AMouse *somSelf, ULONG ulAccelLevel)
    {
    CHAR sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLEVEL1, _itoa (ulAccelLevel, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetAccelLevel1 (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLEVEL1, DEF_VALUE_ACCEL_LEVEL1);
    }

VOID  _clsSetAccelLvl1Mult (M_AMouse *somSelf, ULONG ulAccelLvlMult)
    {
    CHAR sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLVL1MULT, _itoa (ulAccelLvlMult, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetAccelLvl1Mult (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLVL1MULT, DEF_VALUE_ACCEL_L1MULT);
    }

VOID  _clsSetAccelLevel2 (M_AMouse *somSelf, ULONG ulAccelLevel)
    {
    CHAR sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLEVEL2, _itoa (ulAccelLevel, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetAccelLevel2 (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLEVEL2, DEF_VALUE_ACCEL_LEVEL2);
    }

VOID  _clsSetAccelLvl2Mult (M_AMouse *somSelf, ULONG ulAccelLvlMult)
    {
    CHAR sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLVL2MULT, _itoa (ulAccelLvlMult, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetAccelLvl2Mult (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_ACCELLVL2MULT, DEF_VALUE_ACCEL_L2MULT);
    }

VOID _clsSetBtnMode (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum, ULONG ulBtnMode)
    {
    PCHAR pKey;
    UCHAR ucarMode[CULNUMBUTTONS];
    ULONG ulc;

    switch (ulKeyPageType)
        {
        case BTNPAGE_NONE:
            pKey = KEY_BTNMODE;
            break;

        case BTNPAGE_CTRL:
            pKey = KEY_BTNCMODE;
            break;

        case BTNPAGE_ALT:
            pKey = KEY_BTNAMODE;
            break;
        }

    ulc = sizeof (ucarMode);
    if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, pKey,
                                      (PVOID)ucarMode, &ulc))
        {
        setDefaultKeySettings (ulKeyPageType, ucarMode);
        }
    ucarMode[ulKeyNum-CIDBUTTONMIN] = (UCHAR)ulBtnMode;
    PrfWriteProfileData (HINI_USERPROFILE, APP_AMOUSE, pKey, (PVOID)ucarMode, sizeof (ucarMode));

    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetBtnMode (M_AMouse *somSelf, ULONG ulKeyPageType, ULONG ulKeyNum)
    {
    PCHAR pKey;
    UCHAR ucarMode[CULNUMBUTTONS];
    ULONG ulc;

    switch (ulKeyPageType)
        {
        case BTNPAGE_NONE:
            pKey       = KEY_BTNMODE;
            break;

        case BTNPAGE_CTRL:
            pKey       = KEY_BTNCMODE;
            break;

        case BTNPAGE_ALT:
            pKey       = KEY_BTNAMODE;
            break;
        }

    ulc = sizeof (ucarMode);
    if ((BTNPAGE_NONE != ulKeyPageType) ||
        (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, pKey,
                                       (PVOID)ucarMode, &ulc)))
        {
        setDefaultKeySettings (ulKeyPageType, ucarMode);
        }

    return (ULONG)ucarMode[ulKeyNum-CIDBUTTONMIN];
    }

VOID _clsSetBtnKeyCombMP1 (M_AMouse *somSelf,
                           ULONG ulKeyPageType,
                           ULONG ulKeyNum,
                           ULONG ulMP1)
    {
    ULONG ularMP1[CULNUMBUTTONS];
    ULONG ulc;

    if (BTNPAGE_NONE == ulKeyPageType)
        {
        ulc = sizeof (ularMP1);
        if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP1,
                                          (PVOID)ularMP1, &ulc))
            {
            memset (ularMP1, '\0', sizeof (ularMP1));
            }
        ularMP1[ulKeyNum-CIDBUTTONMIN] = ulMP1;
        PrfWriteProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP1,
                             ularMP1, sizeof (ularMP1));

        DosPostEventSem (hevWheelThreadUpdate);
        }

    return;
    }

ULONG _clsGetBtnKeyCombMP1 (M_AMouse *somSelf,
                            ULONG ulKeyPageType,
                            ULONG ulKeyNum)
    {
    ULONG ularMP1[CULNUMBUTTONS];
    ULONG ulc;

    ulc = sizeof (ularMP1);
    if ((BTNPAGE_NONE != ulKeyPageType) ||
        (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP1,
                                       (PVOID)ularMP1, &ulc)))
        {
        memset (ularMP1, '\0', sizeof (ularMP1));
        }

    return ularMP1[ulKeyNum-CIDBUTTONMIN];
    }

VOID _clsSetBtnKeyCombMP2 (M_AMouse *somSelf,
                           ULONG ulKeyPageType,
                           ULONG ulKeyNum,
                           ULONG ulMP2)
    {
    ULONG ularMP2[CULNUMBUTTONS];
    ULONG ulc;

    if (BTNPAGE_NONE == ulKeyPageType)
        {
        ulc = sizeof (ularMP2);
        if (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP2,
                                          (PVOID)ularMP2, &ulc))
            {
            memset (ularMP2, '\0', sizeof (ularMP2));
            }
        ularMP2[ulKeyNum-CIDBUTTONMIN] = ulMP2;
        PrfWriteProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP2,
                             ularMP2, sizeof (ularMP2));

        DosPostEventSem (hevWheelThreadUpdate);
        }

    return;
    }

ULONG _clsGetBtnKeyCombMP2 (M_AMouse *somSelf,
                            ULONG ulKeyPageType,
                            ULONG ulKeyNum)
    {
    ULONG ularMP2[CULNUMBUTTONS];
    ULONG ulc;

    ulc = sizeof (ularMP2);
    if ((BTNPAGE_NONE != ulKeyPageType) ||
        (FALSE == PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_BTNKEYCOMBMP2,
                                       (PVOID)ularMP2, &ulc)))
        {
        memset (ularMP2, '\0', sizeof (ularMP2));
        }

    return ularMP2[ulKeyNum-CIDBUTTONMIN];
    }

VOID _clsSetWheelCount (M_AMouse *somSelf, ULONG ulWheelCount)
    {
    CHAR  sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_WHEELCOUNT, _itoa (ulWheelCount, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetWheelCount (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_WHEELCOUNT, DEF_VALUE_WHEELCOUNT);
    }

VOID  _clsSetPMCtlsFlags (M_AMouse *somSelf, ULONG ulFlgPmCtls)
    {
    CHAR  sz[13];

    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_PMCTLS, _itoa (ulFlgPmCtls, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

ULONG _clsGetPMCtlsFlags (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_PMCTLS, 0);
    }

VOID _clsSetSmartCruise (M_AMouse *somSelf, ULONG ulSmartCruise)
    {
    CHAR  sz[13];
    PrfWriteProfileString (HINI_USERPROFILE, APP_AMOUSE, KEY_SMARTCRUISE, _itoa (ulSmartCruise, sz, 10));
    DosPostEventSem (hevWheelThreadUpdate);
    }

ULONG _clsGetSmartCruise (M_AMouse *somSelf)
    {
    return PrfQueryProfileInt (HINI_USERPROFILE, APP_AMOUSE, KEY_SMARTCRUISE, DEF_VALUE_SMARTCRUISE);
    }

VOID  _clsSetApplications (M_AMouse *somSelf, PSTRUCTAPPL pstructApplications)
    {
    PCHAR p;
    ULONG ulc;

    ulc = ApplStruct2Profile (pstructApplications, &p);
    PrfWriteProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_APPLICATIONS, p, ulc);
    DosPostEventSem (hevWheelThreadUpdate);

    return;
    }

PSTRUCTAPPL _clsGetApplications (M_AMouse *somSelf)
    {
    PCHAR       pcApplications;
    PSTRUCTAPPL p;
    ULONG       ulc = CCHMAXAPPL * sizeof (STRUCTAPPL);

    pcApplications = (PCHAR)malloc (ulc);
    memset (pcApplications, '\0', ulc);
    PrfQueryProfileData (HINI_USERPROFILE, APP_AMOUSE, KEY_APPLICATIONS, pcApplications, &ulc);

    p = ApplProfile2Struct (pcApplications);
    free (pcApplications);
    return p;
    }

int main (int argc, char *argv[])
    {
    ULONG    ulTextId = 0;
    ULONG    versionData[2];
    HMQ      hmq;
    QMSG     qmsg;
    HELPINIT hini;
    HWND     hwndFrame;
    HWND     hwndNotebook;
    SWCNTRL  switchCntrl;

    /* uncomment the following block, if STDOUT is used for debugging */
    // PTIB     ptib;
    // PPIB     ppib;
    //
    // DosGetInfoBlocks (&ptib, &ppib);
    // ppib->pib_ultype = 3;

    /* Query OS version */
    DosQuerySysInfo (QSV_VERSION_MAJOR, QSV_VERSION_MINOR, versionData, 8);
    if ((versionData[0] <= 20) && (versionData[1] < 40))
        bIsWarp4 = FALSE;
    else
        bIsWarp4 = TRUE;

    /* PM Initialisierung und Hauptschleife */
    hab = WinInitialize (0);
    hmq = WinCreateMsgQueue (hab, 0);

    /* initialize debug mode, if requested */
    if (argc == 2)
        {
        if (stricmp (argv[1], "DEBUG") == 0)
            SetDebugMode (TRUE);
        }

    hmodLng = LoadLanguageModule (szModuleName);
    if (hmodLng == NULLHANDLE)
        {
        PCHAR  pFile = szModuleName;
        CHAR   szMessage[CCHMAXTITLE];
        ULONG  ulc;

        ulTextId = IDS_ERR_MOD;
        WinLoadString (hab, NULLHANDLE, ulTextId, CCHMAXTITLE, szMessage);

        DosInsertMessage (&pFile, 1, szMessage, strlen (szMessage), szErrorMsg, CCHMAXTITLE-1, &ulc);
        szErrorMsg[ulc] = '\0';
        }

    _clsInitData (NULL);
    if (!hevWheelThreadUpdate)
        {
        ulTextId = IDS_ERR_SEM;
        WinLoadString (hab, hmodLng, ulTextId, CCHMAXTITLE, szErrorMsg);
        }

    if (ulTextId != 0)
        {
        WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, szErrorMsg, NULL, NULLHANDLE,
                       MB_OK | MB_ERROR | MB_MOVEABLE);
        }
    else
        {
        hwndFrame = WinLoadDlg (HWND_DESKTOP,   /* Dialogbox laden */
                                HWND_DESKTOP,
                                (PFNWP)NotebookDlgProc,
                                hmodLng,
                                IDD_MAIN,
                                NULL);

        if (checkForWheelMouse (hmodLng))
            szErrorMsg[0] = '\0';
        else
            WinLoadString (hab, hmodLng, IDS_NOMOUSE, CCHMAXTITLE, szErrorMsg);
        WinSetDlgItemText (hwndFrame, DID_TEXT, szErrorMsg);

        switchCntrl.hwnd          = hwndFrame;
        switchCntrl.hwndIcon      = 0;
        switchCntrl.hprog         = 0L;
        switchCntrl.idProcess     = 0 ;
        switchCntrl.idSession     = 0;
        switchCntrl.uchVisibility = SWL_VISIBLE;
        switchCntrl.fbJump        = SWL_JUMPABLE;
        WinLoadString (hab, hmodLng, IDS_SWENTRY, MAXNAMEL + 1,
                       switchCntrl.szSwtitle);
        WinCreateSwitchEntry (hab, &switchCntrl);

        WinSendMsg (hwndFrame,                  /* Icon laden */
                    WM_SETICON,
                    (MPARAM) WinLoadPointer (HWND_DESKTOP, 0, IDI_ICON),
                    0L);

        /*  Hilfe initialisieren */
        DetermineHelpFileName (szHelpFile);
        hini.cb                       = sizeof (HELPINIT);
        hini.ulReturnCode             = 0;
        hini.pszTutorialName          = NULL;
        hini.phtHelpTable             = (PHELPTABLE)MAKEULONG (IDH_AMOUSE_DEFAULT, 0xFFFF);
        hini.hmodHelpTableModule      = NULLHANDLE;
        hini.hmodAccelActionBarModule = NULLHANDLE;
        hini.idAccelTable             = 0;
        hini.idActionBar              = 0;
        hini.fShowPanelId             = CMIC_HIDE_PANEL_ID;
        hini.pszHelpLibraryName       = (PSZ)szHelpFile;

        WinLoadString (hab, hmodLng, IDS_HELPWINDOWTITLE, CCHMAXTITLE, szWindowTitle);
        hini.pszHelpWindowTitle = (PSZ)szWindowTitle;

        hwndHelp = WinCreateHelpInstance (hab, &hini);
        if (hwndHelp)
            {
            WinAssociateHelpInstance (hwndHelp, hwndFrame);
            bIsHelp = TRUE;
            }

        /* Notebookseiten einh„ngen */
        hwndNotebook = WinWindowFromID (hwndFrame, DID_NOTEBOOK);
        addNotebookPages (hwndNotebook, hmodLng);

        /*  Message-Schleife */
        while (WinGetMsg (hab, &qmsg, 0L, 0L, 0L))
             WinDispatchMsg (hab, &qmsg);

        /*  Programmende */
        if (bIsHelp)
            WinDestroyHelpInstance (hwndHelp);
        WinDestroyWindow (hwndFrame);
        }

    WinDestroyMsgQueue (hmq);
    WinTerminate (hab);

    return 0;
    }

#pragma info(restore)
