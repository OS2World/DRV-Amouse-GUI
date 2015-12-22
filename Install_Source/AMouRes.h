/***************************************************************************\
 *
 * PROGRAMMNAME: AMouse
 * -------------
 *
 * VERSION: 2.70
 * --------
 *
 * MODULNAME: AMouRes.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Header-Datei fÅr AMouseRes.C
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
#ifndef _AMOURES_H_
#define _AMOURES_H_

#ifdef IS_RESOURCE
    // Window message definitions
    #define WM_NULL                 0x0000
    #define WM_COMMAND              0x0020
    #define WM_CONTROL              0x0030
    #define WM_VSCROLL              0x0031
    #define WM_HSCROLL              0x0032
    #define WM_CHAR                 0x007A
    #define SPBM_SPINUP             0x0203
    #define SPBM_SPINDOWN           0x0204
    #define SLM_SETSLIDERINFO       0x0371
    #define VM_SELECTITEM           0x0379
    #define CSM_SETVALUE            0x0540
#endif /* IS_RESOURCE */
    #define WM_VSCROLL1             0x8000
    #define WM_HSCROLL1             0x8001

#define RCID_POSTDATA               10

#define REL_NONE                    0
#define REL_PARENT                  1
#define REL_OWNER                   2
#define REL_NEXT                    3
#define REL_IGLB                    4           // like REL_NEXT, if owned window is listbox with parent HWND_OBJECT
#define REL_SPEC                    5

#define MODE_STD                    0x0001      // Scroll messages
#define MODE_CSR                    0x0002      // cursor keys
#define MODE_PAGE                   0x0004      // page keys
#define MODE_LINE                   MODE_STD + MODE_CSR
#define MODE_ALL                    MODE_STD + MODE_CSR + MODE_PAGE

// v/hOption used by WM_CHAR
#define VKP_PAGE                    0           // PgUp/PgDn keys
#define VKP_CLR                     1           // Left/Right keys (multiplied by scroll increments)
#define VKP_CUD                     2           // Up/Down keys    (multiplied by scroll increments)
#define VKP_SLR                     3           // Left/Right keys
#define VKP_SUD                     4           // Up/Down keys

// scroll direction for valueset
#define VS_HORZ                     0
#define VS_VERT                     1

#endif /* _AMOURES_H_ */
