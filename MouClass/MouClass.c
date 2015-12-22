/*
 *
 *   Module Name: MouClass
 *
 *   Register Class AMouse
 */

#define INCL_WIN
#define INCL_PM
#define INCL_DOS

#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

HAB     hab;

void Anleitung (char *psz)
    {
    printf ("Registration of AMOUSE workplace shell class\n\n");
    printf ("Syntax: %s [REGISTER|REPLACE|DEREGISTER|DEREPLACE] [NOSOUND]\n\n", psz);
    printf ("        REPLACE    includes REGISTER\n");
    printf ("        DEREGISTER includes DEREPLACE\n");
    return;
    }

int main (int argc, char *argv[])
    {
    ULONG ulReg;
    BOOL  bRC;

    if (argc == 1)
        {
        Anleitung (argv[0]);
        return 1;
        }

    if (strcmp (strupr (argv[1]), "REPLACE") == 0)
        ulReg = 1;
    else if (strcmp (strupr (argv[1]), "DEREPLACE") == 0)
        ulReg = 2;
    else if (strcmp (strupr (argv[1]), "REGISTER") == 0)
        ulReg = 3;
    else if (strcmp (strupr (argv[1]), "DEREGISTER") == 0)
        ulReg = 4;
    else
        {
        Anleitung (argv[0]);
        return 1;
        }

    hab = WinInitialize (0);

    switch (ulReg)
        {
        case 2:
            bRC = WinReplaceObjectClass ("WPMouse", "AMouse", FALSE);
            break;

        case 4:
            WinReplaceObjectClass ("WPMouse", "AMouse", FALSE);
            bRC = WinDeregisterObjectClass ("AMouse");
            break;

        case 3:
            bRC = WinRegisterObjectClass ("AMouse", "amouse");
            break;

        case 1:
            WinReplaceObjectClass ("WPMouse", "WPStickMouse", FALSE);
            WinDeregisterObjectClass ("WPStickMouse");
            WinRegisterObjectClass ("AMouse", "amouse");
            bRC = WinReplaceObjectClass ("WPMouse", "AMouse", TRUE);
            break;
        }

    if (argc == 3 && strcmp (strupr (argv[2]), "NOSOUND") != 0)
        WinAlarm (HWND_DESKTOP, bRC ? WA_NOTE : WA_ERROR);

    WinTerminate(hab);

    return 0;
    }
