#define INCL_KBD
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_ERRORS
#include <os2.h>

#include <stdio.h>
#include <string.h>

VOID getViaKbdCall (VOID)
    {
    KBDKEYINFO      CharData;   //  Pointer to character data.
    APIRET          rc;         //  Return code.

    while (TRUE)
        {
        rc = KbdCharIn (&CharData, IO_WAIT, NULLHANDLE);
        if (rc != NO_ERROR)
            {
            printf ("error code: %d\n", rc);
            break;
            }
        else
            {
            printf ("ASCII Character code:              %2.2x\n", CharData.chChar);
            printf ("Code received for the keyboard:    %2.2x\n", CharData.chScan);
            printf ("State of the keystroke event flag: %2.2x\n", CharData.fbStatus);
            printf ("Shift key status flag:             %4.4x\n", CharData.fsState);
            printf ("Time stamp in milliseconds:        %d\n",    CharData.time);
            printf ("--------------------------------------\n");
            }
        }

    return;
    }

VOID getViaIOCTLCall (VOID)
    {
    HFILE      hFileDriver;
    ULONG      ulAction;
    ULONG      ulDataLen, ulParmLen;
    USHORT     ulParmPacket;
    KBDKEYINFO CharData;
    APIRET     rc;

    rc = DosOpen ("KBD$", &hFileDriver, &ulAction, 0,
                  FILE_NORMAL, FILE_OPEN,
                  OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                  (PEAOP2) NULL);

    if (rc == NO_ERROR)
        {
        while (TRUE)
            {
            ulDataLen = sizeof (CharData);
            ulParmLen = sizeof (ulParmPacket);
            ulParmPacket = 1;
            memset (&CharData, 0, sizeof (CharData));
            rc = DosDevIOCtl (hFileDriver,                  // Device handle
                              IOCTL_KEYBOARD,               // Device category
                              KBD_READCHAR,                 // Function code
                              &ulParmPacket,                // Parameter packet
                              ulParmLen,                    // Maximum size of parm packet
                              &ulParmLen,                   // Size of param packet on exit: not used
                              &CharData,                    // Buffer for data packet
                              ulDataLen,                    // Maximum size of data packet
                              &ulDataLen);                  // Size of data packet

            if (rc != NO_ERROR)
                {
                printf ("IOCTL rc = %d\n", rc);
                break;
                }
            printf ("ASCII Character code:              %2.2x\n", CharData.chChar);
            printf ("Code received for the keyboard:    %2.2x\n", CharData.chScan);
            printf ("State of the keystroke event flag: %2.2x\n", CharData.fbStatus);
            printf ("Shift key status flag:             %4.4x\n", CharData.fsState);
            printf ("Time stamp in milliseconds:        %d\n",    CharData.time);
            printf ("--------------------------------------\n");
            }
        }

    return;
    }

int main (int argc, char *argv[])
    {
    getViaIOCTLCall ();
    return 0;
    }

