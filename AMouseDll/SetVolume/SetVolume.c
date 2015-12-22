#include <os2.h>

#include <stdio.h>
#include <stdlib.h>

#include "pmwinmou.h"

int main (int argc, char *argv[])
    {
    LONG l;

    if (argc != 2)
        {
        printf ("Syntax: %s <increment value>\n", argv[0]);
        return 1;
        }

    l  = strtol (argv[1], NULL, 0);

    do
        {
        printf ("increment = %d\n", l);
        WinSetMasterVolume ((SHORT)l);
        } while (getchar () != EOF);

    return 0;
    }

