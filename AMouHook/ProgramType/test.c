#define INCL_DOSMODULEMGR
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#define INCL_DOSMISC
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSPROFILE
#define INCL_DOSERRORS
#define INCL_WINHOOKS
#define INCL_WININPUT
#define INCL_WINWINDOWMGR
#define INCL_WINMESSAGEMGR
#define INCL_WINPROGRAMLIST
#define INCL_WINFRAMEMGR
#define INCL_WINPOINTERS
#define INCL_WINSWITCHLIST
#define INCL_WINSYS
#define INCL_WINMENUS
#define INCL_WINERRORS
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CCHMAXBUFFER 0xFFFF
#define RESERVED     0

char *szType[] =
    {
    "PROG_DEFAULT",                 // 0
    "PROG_FULLSCREEN",              // 1
    "PROG_WINDOWABLEVIO",           // 2
    "PROG_PM",                      // 3
    "PROG_REAL",                    // 4
    "PROG_GROUP",                   // 5
    "PROG_DLL",                     // 6
    "PROG_WINDOWEDVDM",             // 7
    "PROG_PDD",                     // 8
    "PROG_VDD",                     // 9
    "PROG_WINDOW_REAL",             // 10
    "PROG_WINDOW_PROT",             // 11
    "PROG_WINDOW_AUTO",             // 12
    "PROG_SEAMLESSVDM",             // 13
    "PROG_SEAMLESSCOMMON",          // 14
    "PROG_31_STDSEAMLESSVDM",       // 15
    "PROG_31_STDSEAMLESSCOMMON",    // 16
    "PROG_31_ENHSEAMLESSVDM",       // 17
    "PROG_31_ENHSEAMLESSCOMMON",    // 18
    "PROG_31_ENH",                  // 19
    "PROG_31_STD",                  // 20
    "PROG_DOS_GAME",                // 21
    "PROG_WIN_GAME",                // 22
    "PROG_DOS_MODE"                 // 23
    };

ULONG QueryHMte (PCHAR pszName)
    {
    PVOID       pBuffer;
    APIRET      rc;
    QSPTRREC   *pTop;
    QSGREC     *pGlobal;
    QSLREC     *pL;
    USHORT      hmte = 0;
    ULONG       ulEntityList, ulEntityLevel;

    ulEntityList  = QS_MODVER;
    ulEntityLevel = 0;

//    typedef struct _QSLREC
//    {  /* qsLrec */
//           VOID  FAR        *pNextRec;      /* pointer to next record in buffer */
//           USHORT           hmte;           /* handle for this mte */
//           USHORT           fFlat;          /* true if 32 bit module */
//           ULONG            ctImpMod;       /* # of imported modules in table */
//           ULONG            ctObj;          /* # of objects in module (mte_objcnt)*/
//           QSLOBJREC   FAR  *pObjInfo;      /* pointer to per object info if any */
//           UCHAR     FAR    *pName;         /* -> name string following struc */
//    } QSLREC;

    /* Allocate memory for evaluation */
    rc = DosAllocMem (&pBuffer, CCHMAXBUFFER, PAG_COMMIT | PAG_READ | PAG_WRITE);
    if (NO_ERROR == rc)
        {
        /* Query system state */
        rc = DosQuerySysState (ulEntityList, ulEntityLevel, 0, 0, pBuffer, CCHMAXBUFFER);
        if (NO_ERROR == rc)
            {
            pTop = (QSPTRREC *)pBuffer;
            pGlobal = pTop->pGlobalRec;
            pL   = pTop->pLibRec;

            printf ("cThrds:    %d\n", pGlobal->cThrds);
            printf ("c32SSem:   %d\n", pGlobal->c32SSem);
            printf ("cMFTNodes: %d\n", pGlobal->cMFTNodes);

            while (pL)
                {
                printf ("hmte: %.4x; pName: %s\n", pL->hmte, pL->pName);
                if (strcmp (pL->pName, pszName) == 0)
                    break;
                pL = pL->pNextRec;
                }
            if (pL)
                hmte = pL->hmte;
            }
        else
            printf ("no sys state\n");

        DosFreeMem (pBuffer);
        }
    else
        printf ("not allocated\n");

    return hmte;
    }

USHORT QueryPid (PCHAR pszName)
    {
    PVOID       pBuffer;
    APIRET      rc;
    QSEXLREC   *pL;
    USHORT      pid = 0;
    ULONG       ulEntityList, ulEntityLevel;

    ulEntityList  = QS_MODVER;
    ulEntityLevel = 0;

//    typedef struct _QSEXLREC
//    {  /* qsELrec */
//           struct          _QSEXLREC *next;  /*  Pointer to next Extended Module Data */
//           USHORT          hndmod;           /*  Module Handle */
//           USHORT          pid;              /*  Process ID */
//           USHORT          type;             /*  Type of Module */
//           ULONG           refcnt;           /*  Size of reference array */
//           ULONG           segcnt;           /*  Number of segments in module */
//           VOID            *_reserved_;
//           UCHAR FAR       *name;            /*  Pointer to Module Name  */
//           ULONG           ModuleVersion;    /*  Module version value  */
//           UCHAR FAR       *ShortModName;    /*  New Pointer to Module short name */
//           ULONG           modref;           /*  Start of array of handles of module */
//    } QSEXLREC;

    /* Allocate memory for evaluation */
    rc = DosAllocMem (&pBuffer, CCHMAXBUFFER, PAG_COMMIT | PAG_READ | PAG_WRITE);
    if (NO_ERROR == rc)
        {
        memset (pBuffer, 0, CCHMAXBUFFER);
        /* Query system state */
        rc = DosQuerySysState (ulEntityList, ulEntityLevel, 0, 0, pBuffer, CCHMAXBUFFER);
        if (NO_ERROR == rc)
            {
            pL = (QSEXLREC *)pBuffer;

            while (pL)
                {
                printf ("hmte:       %.4x (%x)\n", pL->hndmod,        &(pL->hndmod));
                printf ("pid:        %.4x (%x)\n", pL->pid,           &(pL->pid));
                printf ("type:       %.4x (%x)\n", pL->type,          &(pL->type));
                printf ("refcnt:     %d   (%x)\n", pL->refcnt,        &(pL->refcnt));
                printf ("segcnt:     %d   (%x)\n", pL->segcnt,        &(pL->segcnt));
                printf ("name:       %s   (%x)\n", pL->name,          &(pL->name));
                printf ("version:    %d   (%x)\n", pL->ModuleVersion, &(pL->ModuleVersion));
                printf ("short name: %s   (%x)\n", pL->ShortModName,  &(pL->ShortModName));
                printf ("--------------\n");

                if (strcmp (pL->name, pszName) == 0)
                    break;
                pL = pL->next;
                }
            if (pL)
                pid = pL->pid;
            }
        else
            printf ("no sys state\n");

        DosFreeMem (pBuffer);
        }
    else
        printf ("not allocated\n");

    return pid;
    }

/*******************************************************************\
    QueryprogType: determines the program type of an application
                   indicated by its pid.
    Input:  pid: pid of process to be examined
    Return: program type
\*******************************************************************/
ULONG QueryProgType (USHORT pid)
    {
    ULONG       ulProgType = PROG_DEFAULT;
    PVOID       pBuffer;
    APIRET      rc;
    QSPTRREC   *pTop;
    QSPREC     *pP;

    /* Allocate memory for evaluation */
    rc = DosAllocMem (&pBuffer, CCHMAXBUFFER, PAG_COMMIT | PAG_READ | PAG_WRITE);
    if (NO_ERROR == rc)
        {
        /* Query system state */
        rc = DosQuerySysState (QS_PROCESS, RESERVED, pid, RESERVED, pBuffer, CCHMAXBUFFER);
        if (NO_ERROR == rc)
            {
            pTop = (QSPTRREC *)pBuffer;
            pP   = pTop->pProcRec;
            if (pP && pP->RecType == QS_PROCESS && pP->pid == pid)
                {
                ulProgType = pP->type;
                printf ("screen group  = %d\n", pP->sgid);
                printf ("process stat  = %d\n", pP->stat);
                printf ("program type  = %s\n", szType[pP->type]);
                printf ("module handle = %d\n", pP->hMte);
                }
            else
                printf ("type not found\n");
            }
        else
            printf ("no sys state\n");

        DosFreeMem (pBuffer);
        }
    else
        printf ("not allocated\n");

    return ulProgType;
    }

VOID QuerySwitchList (VOID)
    {
    HAB       hab;
    ULONG     ulc, ul, ulType;
    ULONG     ulLength;
    PSWBLOCK  pswblkBlock;

    hab = WinQueryAnchorBlock (HWND_DESKTOP);
    ulc = WinQuerySwitchList (hab, NULL, 0);

    ulLength = sizeof (SWBLOCK) + (ulc-1)*sizeof (SWENTRY);
    pswblkBlock = malloc (ulLength);
    ulc = WinQuerySwitchList (hab, pswblkBlock, ulLength);

    for (ul = 0; ul < pswblkBlock->cswentry; ul++)
        {
        printf ("hswitch:      %.8x\n", pswblkBlock->aswentry[ul].hswitch);
        printf ("hwnd:         %.8x\n", pswblkBlock->aswentry[ul].swctl.hwnd);
        printf ("hwndIcon:     %.8x\n", pswblkBlock->aswentry[ul].swctl.hwndIcon);
        printf ("hprog:        %.8x\n", pswblkBlock->aswentry[ul].swctl.hprog);
        printf ("idSession:    %.8x\n", pswblkBlock->aswentry[ul].swctl.idSession);
        printf ("szSwtitle:    %s\n",   pswblkBlock->aswentry[ul].swctl.szSwtitle);
        printf ("pid:          %.8x\n", pswblkBlock->aswentry[ul].swctl.idProcess);
        ulType = pswblkBlock->aswentry[ul].swctl.bProgType;
        if (ulType < 24)
            printf ("bProgType:    %s\n", szType[ulType]);
        else
            printf ("bProgType:    %d = 0x%x\n", ulType, ulType);
        printf ("-----------------\n");
        }

    printf ("\n\n");
    free (pswblkBlock);

    return;
    }

int main (int argc, char *argv[])
    {
    ULONG     ulProgType;   // program type (PROG_* values, see pmshl.h)
    ULONG     ulPid;
    ULONG     ulInfo[2];
    USHORT    pid;

    QuerySwitchList ();
return 0;
    pid = QueryPid (argv[1]);
    printf ("pid = %x\n", pid);

    ulProgType = QueryProgType (pid);
    printf ("progType = %d\n", ulProgType);

    return 0;
    }

