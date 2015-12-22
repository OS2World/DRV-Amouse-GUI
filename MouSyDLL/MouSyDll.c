/*
 *
 *   Module Name: MouSyDLL
 *
 *   Register system DLL
 */

#define INCL_WIN
#define INCL_PM
#define INCL_DOS

#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CCHMAXSTRING    1024
#define MAXTOKEN        50
#define ACTION_REG      0
#define ACTION_DEREG    1
#define HINI_APP        "SYS_DLLS"
#define HINI_KEY_OT     "LoadOneTime"
#define HINI_KEY_PP     "LoadPerProcess"

HAB        hab;
const char szKeyAmouse[] = "AMOUDLL";
const char szKeyPmCtls[] = "PMCTLSPP";

void syntax (char *psz)
    {
    printf ("Registration of AMOUDLL system DLL for AMOUSE driver\n\n");
    printf ("Syntax: %s [REGISTER|DEREGISTER] [NOSOUND]\n\n", psz);
    return;
    }

BOOL changeKeyValue (PCHAR szString, const char *szKey, ULONG ulReg)
    {
    ULONG ul, ul1;
    CHAR  szTokens[CCHMAXSTRING];
    PCHAR pszToken[MAXTOKEN];
    BOOL  bRc = TRUE;

    /* Zerlegen des Strings in Tokens */
    strcpy (szTokens, szString);
    for (ul = 0; ul < MAXTOKEN; ul++)
        pszToken[ul] = NULL;

    pszToken[0] = strtok (szTokens, " ");
    for (ul = 1; ul < MAXTOKEN && pszToken[ul-1]; ul++)
        pszToken[ul] = strtok (NULL, " ");

    /* Suchen des Keywords */
    if (ul == MAXTOKEN)
        bRc = FALSE;
    else
        {
        /* Suchen des Tokens */
        for (ul = 0; ul < MAXTOKEN && pszToken[ul]; ul++)
            if (strcmp (pszToken[ul], szKey) == 0)
                break;

        if (ulReg == ACTION_REG)
            {
            /* Registrieren */
            if (ul == MAXTOKEN)                 // Puffer zu klein
                bRc = FALSE;
            else
                {
                if (!pszToken[ul])
                    {
                    pszToken[ul++] = (char *)szKey;

                    strcpy (szString, pszToken[0]);
                    for (ul1 = 1; ul1 < ul; ul1++)
                        {
                        strcat (szString, " ");
                        strcat (szString, pszToken[ul1]);
                        }
                    }
                else
                    bRc = FALSE;
                }
            }
        else
            {
            /* Deregistrieren */
            if (ul < MAXTOKEN && pszToken[ul])  // Token wurde gefunden
                {
                szString[0] = '\0';
                for (ul1 = 0; ul1 < ul; ul1++)
                    {
                    if (strcmp (pszToken[ul1], szKey) != 0)
                        {
                        strcat (szString, pszToken[ul1]);
                        strcat (szString, " ");
                        }
                    }

                ul = strlen (szString);
                if (ul && szString[ul-1] == ' ')
                    szString[ul-1] = '\0';
                }
            else
                bRc = FALSE;
            }
        }

    return bRc;
    }

int main (int argc, char *argv[])
    {
    ULONG ulReg;
    BOOL  bRc;
    CHAR  szString[CCHMAXSTRING];

    if (argc == 1)
        {
        syntax (argv[0]);
        return 1;
        }

    if (stricmp (argv[1], "REGISTER") == 0)
        ulReg = ACTION_REG;
    else if (stricmp (argv[1], "DEREGISTER") == 0)
        ulReg = ACTION_DEREG;
    else
        {
        syntax (argv[0]);
        return 1;
        }

    hab = WinInitialize (0);

    PrfQueryProfileString (HINI_USERPROFILE, HINI_APP, HINI_KEY_OT, NULL, szString, CCHMAXSTRING);
    if (changeKeyValue (szString, szKeyAmouse, ulReg))
        bRc  = PrfWriteProfileString (HINI_USERPROFILE, HINI_APP, HINI_KEY_OT, szString);

    PrfQueryProfileString (HINI_USERPROFILE, HINI_APP, HINI_KEY_PP, NULL, szString, CCHMAXSTRING);
    if (changeKeyValue (szString, szKeyPmCtls, ulReg))
        bRc &= PrfWriteProfileString (HINI_USERPROFILE, HINI_APP, HINI_KEY_PP, szString);

    if (argc < 3 || stricmp (argv[2], "NOSOUND") != 0)
        WinAlarm (HWND_DESKTOP, bRc ? WA_NOTE : WA_ERROR);

    WinTerminate (hab);

    return 0;
    }
