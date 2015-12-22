/***************************************************************************\
 *
 * PROGRAMMNAME: AMOUSE
 * -------------
 *
 * VERSION: 2.80
 * --------
 *
 * MODULNAME: VENDOR
 * ----------
 *
 * BESCHREIBUNG:
 * -------------
 *   Parsing der USB.IDS-Datei
 *
 * FUNKTIONEN:
 * -----------
 *
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
#define INCL_DOSMODULEMGR
#define INCL_DOSERRORS
#include <os2.h>

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "AMouseGlobal.h"
#include "AMouseData.h"
#include "common.h"

#define CCHMAXLINE  128

/*******************************************************************\
    atous: converts ascii string to unsigned short
    input:  psz: ascii string
    return: unsigned short result
\*******************************************************************/
USHORT atous (PSZ psz)
    {
    static CHAR cHex[] = "0123456789ABCDEF";
    USHORT usResult;
    ULONG  i;
    PCHAR  p;

    for (i = 0, usResult = 0; i < 4; i++)
        {
        p = strchr (cHex, toupper (psz[i]));
        if (p)
            {
            usResult *= 16;
            usResult += p - cHex;
            }
        else
            break;
        }

    return usResult;
    }

BOOL readVendorName (FILE *file, USHORT usVendorId, PCHAR pszBuffer, ULONG ulcBuffer)
    {
    ULONG ulcTabs;
    ULONG ulc;

    while (fgets (pszBuffer, ulcBuffer, file))
        {
        // count number of tab-characters
        for (ulcTabs = 0; pszBuffer[ulcTabs] == '\t'; ulcTabs++)
            {}
        if (pszBuffer[ulcTabs] == '#')
            continue;       // comment line detected
        if (pszBuffer[ulcTabs] == '\0')
            continue;       // empty line detected
        if (pszBuffer[ulcTabs] == '\n')
            continue;       // empty line detected
        if (ulcTabs > 0)
            continue;       // non-vendor line detected
        if (usVendorId != atous (pszBuffer))
            continue;       // wrong vendor id
        // skip vendor id
        for (ulc = ulcTabs; !isspace (pszBuffer[ulc]); ulc++)
            {}
        // skip white spaces
        for (; isspace (pszBuffer[ulc]); ulc++)
            {}
        // copy vendor string
        memmove (pszBuffer, &pszBuffer[ulc], ulcBuffer - ulc);
        ulc = strlen (pszBuffer);
        if (pszBuffer[ulc-1] == '\n')
            pszBuffer[ulc-1] = '\0';
        return TRUE;
        }

    return FALSE;
    }

BOOL readMouseType (FILE *file, USHORT usTypeId, PCHAR pszBuffer, ULONG ulcBuffer)
    {
    ULONG ulcTabs;
    ULONG ulc;

    while (fgets (pszBuffer, ulcBuffer, file))
        {
        // count number of tab-characters
        for (ulcTabs = 0; pszBuffer[ulcTabs] == '\t'; ulcTabs++)
            {}
        if (pszBuffer[ulcTabs] == '#')
            continue;       // comment line detected
        if (pszBuffer[ulcTabs] == '\0')
            continue;       // empty line detected
        if (pszBuffer[ulcTabs] == '\n')
            continue;       // empty line detected
        if (ulcTabs > 1)
            continue;       // interface type detected
        if (ulcTabs < 1)
            break;          // vendor string detected
        if (usTypeId != atous (&pszBuffer[ulcTabs]))
            continue;       // wrong type id
        // skip type id
        for (ulc = ulcTabs; !isspace (pszBuffer[ulc]); ulc++)
            {}
        // skip white spaces
        for (; isspace (pszBuffer[ulc]); ulc++)
            {}
        // copy type string
        memmove (pszBuffer, &pszBuffer[ulc], ulcBuffer - ulc);
        ulc = strlen (pszBuffer);
        if (pszBuffer[ulc-1] == '\n')
            pszBuffer[ulc-1] = '\0';
        return TRUE;
        }

    return FALSE;
    }

/*******************************************************************\
    getVendorName: retrieves the vendor and product name from the USB
                   vendor file.
    input:  usVendorId:   vendor id
            usTypeId:     type id
            ulcVendor:    length of pszVendor buffer
            ulcMouseType: length of pszMouseType buffer
    output: pszVendor:    buffer for vendor string
            pszMouseType: buffer for mouse type string
\*******************************************************************/
VOID getVendorName (USHORT usVendorId, USHORT usTypeId, PSZ pszVendor, ULONG ulcVendor, PSZ pszMouseType, ULONG ulcMouseType)
    {
    CHAR   szPathName[CCHMAXPATH];
    CHAR   szBuffer[CCHMAXLINE];
    FILE  *file;
    PSZ    psz;
    APIRET rc;

    /* query path name of calling program (amouse.exe or amouse.dll) */
    rc = DosQueryModuleName (hmodLng, CCHMAXPATH, szPathName);
    if (rc == NO_ERROR)
        {
        psz = strrchr (szPathName, '\\');
        if (psz)
            {
            /* not necessary to check string length, as usb.ids is shorter than program name */
            psz++;
            strcpy (psz, "USB.IDS");
            file = fopen (szPathName, "r");

            if (file)
                {
                if (readVendorName (file, usVendorId, szBuffer, CCHMAXLINE))
                    {
                    strncpy (pszVendor, szBuffer, ulcVendor);
                    pszVendor[ulcVendor-1] = '\0';
                    if (readMouseType (file, usTypeId, szBuffer, CCHMAXLINE))
                        {
                        strncpy (pszMouseType, szBuffer, ulcMouseType);
                        pszMouseType[ulcMouseType-1] = '\0';
                        }
                    }
                }

            fclose (file);
            }
        }

    return;
    }

