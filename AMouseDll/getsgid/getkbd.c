#define INCL_KBD
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSPROFILE
#define INCL_ERRORS
#include <os2.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RESERVED                0

/*******************************************************************\
    Executes DosQuerySysState and determines the process name for
    pid without path specification
    Input:  pid         : pid of process to be examined
            cbBuffer    : size of buffer
    Output: pProcessName: name of process excluding path specification
    Return: return value of last API call
\*******************************************************************/
ULONG QueryProgType (PID pid)
    {
    PVOID       pBuffer;
    ULONG       ulcBuffer;
    QSPTRREC   *pTop;
    QSPREC     *pP;
    ULONG       ulProgType;
    APIRET rc;

    /* Allocate memory for evaluation */
    ulcBuffer = 0x4000;
    printf ("allocate buffer with size: %d\n", ulcBuffer);
    rc = DosAllocMem (&pBuffer, ulcBuffer, PAG_COMMIT | PAG_READ | PAG_WRITE);
    if (rc != NO_ERROR)
        return rc;

    /* Query system state */
    rc = DosQuerySysState (QS_PROCESS, RESERVED, pid, RESERVED, pBuffer, ulcBuffer);
    if (rc == NO_ERROR)
        {
        pTop = (QSPTRREC *)pBuffer;
        pP   = pTop->pProcRec;
        if (pP && pP->RecType == QS_PROCESS && pP->pid == pid)
            ulProgType = pP->type;
        }

    DosFreeMem (pBuffer);
    return ulProgType;
    }

int main (int argc, char *argv[])
    {
    ULONG ulPid;
    ULONG ulSGID;

    ulPid  = strtol (argv[1], NULL, 0);
    ulSGID = QueryProgType ((PID)ulPid);

    printf ("SGID = %d\n", ulSGID);

    return 0;
    }

