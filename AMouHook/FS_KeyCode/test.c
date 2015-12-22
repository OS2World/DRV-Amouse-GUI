#define INCL_DOS
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSERRORS
#include "os2.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#define MOU_SETKBDEVENT         0x78        // IOCTL function code for IOCTL_POINTINGDEVICE to send kbd event

#pragma pack (1)
typedef struct
    {
    USHORT  uscRepeat;
    USHORT  usMakeCode;
    USHORT  usBreakCode;
    } KBDEVENT, *PKBDEVENT;
#pragma pack ()

VOID postKey (BOOL bIsBtnUp, USHORT usKeyCode)
    {
    HFILE    hFileDriver;
    ULONG    ulAction;
    ULONG    ulParmLen;
    APIRET   rc;
    KBDEVENT kbdEvent;

    rc = DosOpen ("MOUSE$", &hFileDriver, &ulAction, 0,
                  FILE_NORMAL, FILE_OPEN,
                  OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                  (PEAOP2)NULL);

    if (rc == NO_ERROR)
        {
        ulParmLen = sizeof (KBDEVENT);
        kbdEvent.uscRepeat   = 1;
        kbdEvent.usMakeCode  = usKeyCode;
        kbdEvent.usBreakCode = 0;

        if (bIsBtnUp)
        {
            if (usKeyCode > 255)
               kbdEvent.usMakeCode += 0x8000;
            else   
               kbdEvent.usMakeCode += 0x80;
        }

        DosDevIOCtl (hFileDriver,                   // Device handle
                     IOCTL_POINTINGDEVICE,          // Device category: Pointing-device control
                     MOU_SETKBDEVENT,               // Function code: send keyboard event
                     &kbdEvent,                     // Parameter packet: timeout value
                     sizeof (kbdEvent),             // Maximum size of parm packet
                     &ulParmLen,                    // Size of param packet on exit
                     NULL,                          // Buffer for data packet: not used
                     0,                             // Maximum size of data packet
                     NULL);                         // Size of data packet: not used

        DosClose (hFileDriver);
        }

    return;
    }

int main (int argc, char *argv[])
    {
    USHORT usChar;

    if (argc != 2)
        {
        printf ("Syntax: test <charcode>\n");
        return 1;
        }

    usChar = strtoul (argv[1], NULL, 0);
    printf ("Zeichenausgabe: 0x%.4x\n", usChar);

    while (1)
        {
        DosBeep (4000, 50);
        postKey (FALSE, usChar);
        postKey (TRUE,  usChar);
        DosSleep (2000);
        }

    return 0;
    }
