/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: COMMON.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Debug-Funktionen
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  2.00    02-12-02  WheelThread in separate process
 *  2.40    02-01-03  support for 2 wheels; wildcards for process name
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#ifndef COMMON_H
#define COMMON_H

typedef struct
    {
    HWND  hwndParent;
    HWND  hwndOwner;
    PSZ   pszText;
    PSZ   pszCaption;
    ULONG idWindow;
    ULONG flStyle;
    } MSGTHREADPARM, *PMSGTHREADPARM;

/* IOCTL specific definitions */
#define TYPE_EXTENDED   1

#pragma pack(1)
typedef struct
    {
    USHORT usIndex;     // flags for following values; see Ext??? below
    USHORT usType;
    UCHAR  ucButtons;
    UCHAR  ucWheels;
    UCHAR  ucSubType;
    UCHAR  ucShape;
    UCHAR  ucDevNum;
    UCHAR  ucChannel;
    UCHAR  ucBatt;
    USHORT usVendorId;
    } EXT_INFO, *PEXT_INFO;

#pragma pack()

#define ExtTypeIdx      0x01
#define ExtBttnIdx      0x02
#define ExtWheelIdx     0x04
#define ExtSubTIdx      0x08
#define ExtShapeIdx     0x10
#define ExtDevNoIdx     0x20
#define ExtChnlIdx      0x40
#define ExtBattIdx      0x80
#define ExtVendorIdx    0x100

#define MAX_EXT_SUBT    24      // maximum number in Logitech subtype table

/* function prototypes */
VOID  setDefaultKeySettings (ULONG ulKeyPageType, PCHAR pucarMode);
ULONG getDefaultKeySetting (ULONG ulKeyPageType, ULONG ulKeyNum);
VOID  appendString (PSZ pszDest, PSZ pszSource, ULONG ulc);
VOID  determineMouseType (HAB hab, HMODULE hModule, USHORT usMouseType, PUSHORT pusPortId, PUSHORT pusWheelId, PSZ pszMouseType);
BOOL  checkForWheelMouse (HMODULE hModule);
ULONG calcControlId (ULONG ulScrollMode);
VOID  findResourceString (HMODULE hModule, USHORT usID, PCHAR pszText, ULONG ulcText);
BOOL  isValidKey (USHORT usFlags, UCHAR  ucCharCode, USHORT usVKCode);
BOOL  describeKey (PSZ pszBuf, ULONG ulcBuf, USHORT usFlags, UCHAR  ucCharCode, USHORT usVKCode);
VOID  populateComboboxes (HWND hwndDlg, HMODULE hModule, ULONG ulPageType);
VOID  insertKeyCombString (HWND hwndDlg, ULONG mp1, ULONG mp2, ULONG idEntry);
VOID  asyncMessageBox (HWND hwndParent, HWND hwndOwner, PSZ pszText, PSZ pszCaption, ULONG idWindow, ULONG flStyle);
BOOL  getLogiInfo (HFILE hf, PEXT_INFO pLogiInfo);
VOID  getLogiType (HAB hab, HMODULE hModule, HMODULE hModLang, PEXT_INFO pLogiInfo, ULONG ulcTypeString, PCHAR pTypeString, ULONG ulcRcvString,  PCHAR pRcvString, PULONG pulChannels);
LONG  getButtonCount (HFILE hf);
LONG  getWheelCount (VOID);
ULONG pollRateIndex2Value (ULONG ulIndex);
ULONG pollRateValue2Index (ULONG ulValue);
VOID  accelMultIndex2Value (ULONG ulIndex, PULONG pulValue1, PULONG pulValue2);
ULONG accelMultValue2Index (ULONG ulValue);
VOID  accelThreshIndex2Value (ULONG ulIndex, PULONG pulValue1, PULONG pulValue2);
ULONG accelThreshValue2Index (ULONG ulValue);
VOID  setClipboard (PSZ pszClipString);
PSTRUCTAPPL ApplProfile2Struct (PCHAR pcApplication);
ULONG ApplStruct2Profile (PSTRUCTAPPL pstructAppl, PCHAR *pProfile);
ULONG ApplNumOfEntries (PSTRUCTAPPL pstructAppl);
BOOL  ApplFreeEntries (PSTRUCTAPPL pstructAppl);
BOOL  ApplInsertNewEntry (PSTRUCTAPPL pstructAppl, PSTRUCTAPPL pstructNewEntry);
BOOL  ApplMoveEntry (PSTRUCTAPPL pstructAppl, ULONG ulIndex, BOOL bUp);
VOID  ApplDeleteEntry (PSTRUCTAPPL pstructAppl, ULONG ulIndex);

#define CCHMAXRCVTYPESTRING 64
#define CCHMAXTYPESTRING    128

#define FLG_COMBOBOX_3      0x0001
#define FLG_COMBOBOX_4      0x0002
#define FLG_COMBOBOX_5      0x0004
#define FLG_COMBOBOX_6      0x0008
#define FLG_COMBOBOX_7      0x0010

#endif /* COMMON_H */
