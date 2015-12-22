/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: VENDOR.H
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Parsing der USB.IDS-Datei
 *
 *  Ver.    Date      Comment
 *  ----    --------  -------
 *  2.50    04-20-03  application behaviour support added
 *  2.60    06-13-04  remove unused settings pages from mouse object
 *  2.70    10-23-04  support for 7 buttons added
 *  2.80    10-02-06  support of arbitary key combinations
 *
 *  Copyright (C) noller & breining software 2001...2006
 *
\******************************************************************************/
#ifndef VENDOR_H
#define VENDOR_H

VOID getVendorName (USHORT usVendorId, USHORT usTypeId, PSZ pszVendor, ULONG ulcVendor, PSZ pszMouseType, ULONG ulcMouseType);

#endif /* VENDOR_H */
