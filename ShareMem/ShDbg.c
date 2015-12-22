#define INCL_DOSMEMMGR
#define INCL_DOSPROCESS
#include <os2.h>

#include <stdio.h>

#include "..\AMouseGlobal.h"

int main (void)
    {
    PMOUSEDATA pShMem;
    ULONG      ulId;

    if (DosGetNamedSharedMem ((PPVOID)&pShMem, SHMEMNAME, PAG_READ | PAG_WRITE))
        {
        printf ("No shared memory\n");
        return 0;
        }

    printf ("SharedMem::ulScrollMode:              %d\n", pShMem->ulScrollMode);
    printf ("SharedMem::ulScrollModeC:             %d\n", pShMem->ulScrollModeC);
    printf ("SharedMem::ulScrollModeA:             %d\n", pShMem->ulScrollModeA);
    printf ("SharedMem::ulScrollNum:               %d\n", pShMem->ulScrollNum);
    printf ("SharedMem::ulScrollNumC:              %d\n", pShMem->ulScrollNumC);
    printf ("SharedMem::ulScrollNumA:              %d\n", pShMem->ulScrollNumA);
    printf ("SharedMem::ulWheelTarget:             %d\n", pShMem->ulWheelTarget);
    printf ("SharedMem::ulWheelTargetC:            %d\n", pShMem->ulWheelTargetC);
    printf ("SharedMem::ulWheelTargetA:            %d\n", pShMem->ulWheelTargetA);
    printf ("SharedMem::ulStartupMode:             %d\n", pShMem->ulStartupMode);
    printf ("SharedMem::ulAccelDelay:              %d\n", pShMem->ulAccelDelay);
    printf ("SharedMem::ulAccelValue:              %d\n", pShMem->ulAccelValue);
    printf ("SharedMem::ulCurrScrollDir:           %d\n", pShMem->ulCurrScrollDir);
    printf ("SharedMem::ulPollingRate:             %d\n", pShMem->ulPollingRate);
    printf ("SharedMem::ulAccelLevel1:             %d\n", pShMem->ulAccelLevel1);
    printf ("SharedMem::ulAccelLvl1Mult:           %d\n", pShMem->ulAccelLvl1Mult);
    printf ("SharedMem::ulAccelLevel2:             %d\n", pShMem->ulAccelLevel2);
    printf ("SharedMem::ulAccelLvl2Mult:           %d\n", pShMem->ulAccelLvl2Mult);
    printf ("SharedMem::ulWheelCount:              %d\n", pShMem->ulWheelCount);
    printf ("SharedMem::ulcApplications:           %d\n", pShMem->ulcApplications);
    printf ("SharedMem::ulFlgPmCtls:               %d\n", pShMem->ulFlgPmCtls);

    printf ("SharedMem::ulBtnMode:                 ");
    for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
        printf ("%.2X ", pShMem->ucBtnMode[ulId]);
    printf ("\n");

    printf ("SharedMem::ulBtnCMode:                ");
    for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
        printf ("%.2X ", pShMem->ucBtnCMode[ulId]);
    printf ("\n");

    printf ("SharedMem::ulBtnAMode:                ");
    for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
        printf ("%.2X ", pShMem->ucBtnAMode[ulId]);
    printf ("\n");

    printf ("SharedMem::ulBtnKeyCombMP1            ");
    for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
        printf ("%.8X ", pShMem->ulBtnKeyCombMP1[ulId]);
    printf ("\n");

    printf ("SharedMem::ulBtnKeyCombMP2            ");
    for (ulId = 0; ulId < CULNUMBUTTONS; ulId++)
        printf ("%.8X ", pShMem->ulBtnKeyCombMP2[ulId]);
    printf ("\n");

    return 0;
    }

