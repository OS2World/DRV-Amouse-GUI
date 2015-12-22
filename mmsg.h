Hallo Klaus,

/*
Ich denke mal da· Du der einzige Autor eines aktuellen Maustreibers bist. Soweit ich das gesehen habe, kînntest Du Deine "Marktmacht" dazu nutzen, einen Event zu
definieren und ihn in der Doku zu verîffentlichen. Das ganze sollte aber mit den eCS-Jungs abgestimmt sein, wenn die nicht ohnehin Deinen Treiber benutzen (?),
dann erÅbrigt sich die Anfrage. Es wÑre denke ich schon sinnvoll, so einen Event "aus der Taufe zu heben". Hierbei kînnte man sich hinsichtlich Parameter an den
Windows WM_MOUSEWHEEL halten. Windows versendet nÑmlich nicht nur ein Einzelevent, sondern auch noch einen signed short Parameter, aus der StÑrke der Drehung
(absoluter Wert) und Richtung (positiver, negativer Wert) hervorgeht, wobei +120 bzw. -120 erst einmal der Standardwert ist und feinere Abstufungen fÅr
zukÅnftige MÑuse vorbehalten sind. In der Win32-Doku steht folgendes auf der Seite WM_MOUSEWHEEL:

WM_MOUSEWHEEL:

[New - Windows NT]

The WM_MOUSEWHEEL message is sent to the focus window when the mouse wheel is rotated. The DefWindowProc function propagates the message to the window's parent.
There should be no internal forwarding of the message, since DefWindowProc propagates it up the parent chain until it finds a window that processes it.

WM_MOUSEWHEEL
fwKeys = LOWORD(wParam);    // key flags
zDelta = (short) HIWORD(wParam);    // wheel rotation
xPos = (short) LOWORD(lParam);    // horizontal position of pointer
yPos = (short) HIWORD(lParam);    // vertical position of pointer


Parameters

fwKeys

Value of the low-order word of wParam. Indicates whether various virtual keys are down. This parameter can be any combination of the following values:

Value   Description
MK_CONTROL      Set if the CTRL key is down.
MK_LBUTTON      Set if the left mouse button is down.
MK_MBUTTON      Set if the middle mouse button is down.
MK_RBUTTON      Set if the right mouse button is down.
MK_SHIFT        Set if the SHIFT key is down.


zDelta

The value of the high-order word of wParam. Indicates the distance that the wheel is rotated, expressed in multiples or divisions of WHEEL_DELTA, which is 120.
A positive value indicates that the wheel was rotated forward, away from the user; a negative value indicates that the wheel was rotated backward, toward the user.

xPos

Value of the low-order word of lParam. Specifies the x-coordinate of the pointer, relative to the upper-left corner of the screen.

yPos

Value of the high-order word of lParam. Specifies the y-coordinate of the pointer, relative to the upper-left corner of the screen.



Remarks

The zDelta parameter will be a multiple of WHEEL_DELTA, which is set at 120. This is the threshold for action to be taken, and one such action (for example,
scrolling one increment) should occur for each delta.
The delta was set to 120 to allow Microsoft or other vendors to build finer-resolution wheels in the future, including perhaps a freely-rotating wheel with
no notches. The expectation is that such a device would send more messages per rotation, but with a smaller value in each message. To support this possibility,
you should either add the incoming delta values until WHEEL_DELTA is reached (so for a given delta-rotation you get the same response), or scroll partial lines
in response to the more frequent messages. You could also choose your scroll granularity and accumulate deltas until it is reached.

See Also

GetSystemMetrics, mouse_event, SystemParametersInfo

-------------------------------------------------------------------------------

Dann noch ein recht interessantes Suchergebnis bzgl. Windows-Headerdateien:

E:\BC5>do search *.h Wheel
================================================================
E:\BC5\INCLUDE\winresrc.h
----------------------------------------------------------------
*/
(358) #define WM_MOUSEWHEEL                   0x020A
(367) #define WHEEL_DELTA                     120     /* Value for rolling one detent */
(370) #define WHEEL_PAGESCROLL                (UINT_MAX) /* Scroll one page */
================================================================
E:\BC5\INCLUDE\WIN32\winuser.h
----------------------------------------------------------------
(1377) #define WM_MOUSEWHEEL                   0x020A
(1386) #define WHEEL_DELTA                     120     /* Value for rolling onedetent */
(1389) #define WHEEL_PAGESCROLL                (UINT_MAX) /* Scroll one page */
(3985) #define MOUSEEVENTF_WHEEL       0x0800 /* wheel button rolled */
(4337) #define SM_MOUSEWHEELPRESENT    75
(8187) #define SPI_GETWHEELSCROLLLINES   104
(8188) #define SPI_SETWHEELSCROLLLINES   105

/*
Also, ich wÅrde sofort solch einen Event in meinen Freeware-Editor WSedit integrieren und nach und auch noch in
andere Programme von mir.
Man mÅ·te aber dann irgendwie organisieren, da· bestimmte Fenster (nicht Programme) Deinem Maustreiber
vielleicht Åber das Versenden eines Anmelde-Events mitteilen, da· sie die Mauswheel-Events selbst
interpretieren mîchten und nicht andere, von Deinem Programm "Åbersetzte" Events erhalten wollen, die aus
einer Radbewegung resultieren. Das hei·t der Programmierer mÅ·te dann nicht nur Deine kÅnftigen
WM_MOUSEWHEEL Events interpretieren, sondern sich bei der Initialisierung des Fensters explizit
beim Maustreiber als "mousewheel event enabled" ausweisen. Beim Verlassen (WM_CLOSE) mÅ·te sich das
Fenster aber dann auch beim Maustreiber abmelden, und Du mÅ·test im Maustreiber eine Liste von
Window-Handles verwalten, die direkt die WM_MOUSEWHEEL events erwarten und gerade nicht die konvertierten
anderen Events.

Diese Lîsung wÑre dann sogar abwÑrtskompatibler als bei Windows, wo ja der Programmierer
grundsÑtzlich die Mousewheel-Events interpretieren mu·, und ohne passiert gar nichts.
*/

