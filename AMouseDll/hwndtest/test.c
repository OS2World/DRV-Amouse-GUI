#define INCL_DOSMISC
#include <os2.h>
#include <stdio.h>

#include <Log.h>

#include "AMouHwnd.h"
#include "AMouHData.h"

void printout (void)
    {
    printf ("num of entries: %d\n", ulcWindow);

    return;
    }

int main (void)
    {
    BOOL  bRC;
    ULONG fl;
    ULONG ul;

    DosQuerySysInfo (QSV_PAGE_SIZE, QSV_PAGE_SIZE, &ulcBytePerPage, sizeof (ulcBytePerPage));

    TraceInit ("$$test$$.dbg");
    allocSharedHwndArray ();

    bRC = addWindowHandle (1, 0);
    printf ("add; result = %s\n", (bRC ? "True" : "False"));
    printout ();

    printf ("remove %d: %s\n", 1, (removeWindowHandle (1) ? "TRUE" : "FALSE"));
    printout ();

    bRC = addWindowHandle (1, 0);
    printf ("add; result = %s\n", (bRC ? "True" : "False"));

    bRC = addWindowHandle (2, 0);
    printf ("add; result = %s\n", (bRC ? "True" : "False"));

    bRC = addWindowHandle (3, 0);
    printf ("add; result = %s\n", (bRC ? "True" : "False"));

    bRC = addWindowHandle (4, 0);
    printf ("add; result = %s\n", (bRC ? "True" : "False"));
    printout ();

    for (ul = 0; ul < 8; ul++)
        {
        bRC = addWindowHandle (ul, 0);
        printf ("add; result <%d> = %s\n", ul, (bRC ? "True" : "False"));
        }
    printout ();

    bRC = findWindowHandle (100, &ul);
    printf ("search for Window Handle  100: %s\n", (bRC ? "True" : "False"));

    bRC = findWindowHandle (3000, &ul);
    printf ("search for Window Handle 3000: %s\n", (bRC ? "True" : "False"));

    bRC = findWindowHandle (9999, &ul);
    printf ("search for Window Handle 9999: %s\n", (bRC ? "True" : "False"));

    printf ("remove %d: %s\n", 1, (removeWindowHandle (1) ? "TRUE" : "FALSE"));
    printout ();

    for (ul = 2; ul < 8; ul++)
        {
        printf ("remove %d: %s\n", ul, (removeWindowHandle (ul) ? "TRUE" : "FALSE"));
        }
    printout ();

    printf ("remove %d: %s\n", 1, (removeWindowHandle (1) ? "TRUE" : "FALSE"));
    printout ();

    bRC = findWindowHandle (1, &ul);
    printf ("search for Window Handle    1: %s\n", (bRC ? "True" : "False"));

    bRC = findWindowHandle (2, &ul);
    printf ("search for Window Handle    2: %s\n", (bRC ? "True" : "False"));

    bRC = findWindowHandle (3000, &ul);
    printf ("search for Window Handle 3000: %s\n", (bRC ? "True" : "False"));

    bRC = findWindowHandle (9999, &ul);
    printf ("search for Window Handle 9999: %s\n", (bRC ? "True" : "False"));

    return 0;
    }

