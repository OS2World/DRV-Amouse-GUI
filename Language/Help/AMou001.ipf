.************************************************
.*
.*   Copyright 2002-2006 nb software
.*
.*   Help for AMouse
.************************************************

:userdoc.

:h1 res=10 id=aboutMain.AMouse - Advanced Mouse Configuration
:i1 id=aboutMain.AMouse - Advanced Mouse Configuration
:p.:artwork name='C:\work\c\amouse\Language\Help\amouse.bmp' runin align=left.
This program may be used for the configuration of the wheel of a
"wheel mouse" (e. g. Intelli-Mouse). It may&colon.

:ul compact.
:li.control the operation of the wheel
:li.set the number of scroll increments of the wheel
:li.define the function of buttons 3...5 of the mouse
:eul.

:h1 res=1900 id=wheel1.Wheel 1/2/3
:i1 id=wheel1.Wheel 1/2/3
:p.This page is used to setup the actions of the mouse initiated by turning the
wheel. There is one of this page for each supported combination of wheel + shift key.
:p.A more detailed explanation of each control will be shown, if you click on 
one of the items in the list below&colon.

:ul compact.
:li.:link reftype=hd refid=no_func.No function:elink.
:li.:link reftype=hd refid=msgscroll.Scroll messages:elink.
:li.:link reftype=hd refid=msgline.Keyboard messages:elink.
:li.:link reftype=hd refid=msgpage.Scroll entire page per scroll unit:elink.
:li.:link reftype=hd refid=msgvol.Set audio volume:elink.
:li.:link reftype=hd refid=keyboard.Acts on active window:elink.
:li.:link reftype=hd refid=pointer.Acts on window below mouse pointer:elink.
:li.:link reftype=hd refid=scrollitem.Wheel speed:elink.
:li.:link reftype=hd refid=cancel.Undo:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.
:note.
This page is only visible, if a wheel has been detected on the mouse.

:h2 res=1901 id=no_func.Operation Mode - No Function
:p.If this radio button will be selected, a turn of the wheel will
be ignored by the system.

:h2 res=1902 id=msgscroll.Operation Mode - Scroll messages
:p.If this button has been selected, a scroll message (WM_VSCROLL/WM_HSCROLL) 
will be sent to text windows. This simulates the moving of the scroll-bar.

:h2 res=1903 id=msgline.Operation Mode - Keyboard messages
:p.If this button has been selected, am WM_CHAR message will be sent
to text windows. This simulates the pressing of an arrow key, provided
this feature is supported by the window.

:h2 res=1904 id=msgpage.Operation Mode - Scroll entire page per scroll unit
:p.If this button has been selected, a WM_CHAR message will be sent
to text windows. This simulates the pressing of a page up or page down
key, provided this feature is supported by the window.

:h2 res=1905 id=msgvol.Operation Mode - Set Audio Volume
:p.If this button has been selected, turning the wheel sets the volume of the multimedia system.

:h2 res=1906 id=keyboard.Acts on active window
:p.If this radio button will be selected, the vertical scroll bar of the
active window will be moved.
:p.With some mice the window below the mouse pointer may be activated by pressing
the wheel.
:note.
On some windows the subwindows may also contain scroll bars (e. g. in the Netscape
Communicator). In this case the window that has been selected at last is moved.

:h2 res=1907 id=pointer.Acts on window below mouse pointer
:p.If this radio button will be selected, the vertical scroll bar of the window
below the mouse pointer will be moved.
:note.
It doesn't matter, if this window is active in this moment, or even if it is
partially hidden by other windows.

:h2 res=1908 id=scrollitem.Wheel speed
:p.With the :hp2.spin button:ehp2. the number of lines may be selected that are
scrolled if he wheel is moved by one notch.

:h2 id=cancel.Undo
:p.The settings of all parameters are set back to the values before the last change.

:h2 id=standard.Standard
:p.The default settings will be set.

:h1 res=2100 id=wheel2.Wheel 4
:i1 id=wheel2.Wheel 4
:p.This page is used to setup the startup values of the driver, valid upon
boot time of the pc.
:p.The settings may be done by selection of the respective button on this
settings page.
:p.A more detailed explanation for each control will be shown, if you click on
one of the items in the list below&colon.
:ul compact.
:li.:link reftype=hd refid=scroll_vert.vertical scrolling:elink.
:li.:link reftype=hd refid=scroll_horz.horizontal scrolling:elink.
:li.:link reftype=hd refid=accel_delay.delay of scroll acceleration:elink.
:li.:link reftype=hd refid=accel_value.velocity of scroll acceleration:elink.
:li.:link reftype=hd refid=trackball.Number of wheels:elink.
:li.:link reftype=hd refid=cancel.Undo:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.
:note.
This page is only visible, if a wheel has been detected on the mouse.

:h2 res=2101 id=scroll_vert.Startup values - vertical scrolling
:p.If this button has been selected, turning the wheel on a mouse with a 
single wheel results in vertical scrolling.

:h2 res=2102 id=scroll_horz.Startup values - horizontal scrolling
:p.If this button has been selected, turning the wheel on a mouse with a 
single wheel results in horizontal scrolling.

:h2 res=2103 id=accel_delay.Delay of Scroll Acceleration (Delay Time)
:p.If the wheel is scrolled fast longer that the delay time, the number of lines used for scrolling will be 
increased continuously. The delay time may be adjusted between 100 and 2000 ms.

:h2 res=2104 id=accel_value.Velocity of Scroll Acceleration (Acceleration Value)
:p.This slider fixes the number that is used for increasing the scroll units, if the wheel is turned fast.

:h2 res=2105 id=trackball.Number of Wheels
:p.Some mice are unable to notify their number of wheels or the existence of a trackball to the mouse driver. 
In this case it is possible to define this property by means of this button.

:h1 res=2300 id=wheel3.Wheel 5
:i1 id=wheel3.Wheel 5
:p.The page :hp2.Wheel 5:ehp2. defines exceptions of the behaviour of the wheel for some applications.
If you turn the wheel of the mouse, in the list on this page a suitable description for a window / control will be searched for.
Here the list :hp2.Description:ehp2. will be searched downward until a match with the application below the mouse pointer is found.
If there is no match, the default list of :hp2.AMouse:ehp2. (defined in :font facename=Courier size=14x14.AMouRes.rc:font facename=default.)
is taken. The descriptive text in the list is used for identification by the user, therefore the name is arbitrary; there may be even duplicate names.
:p.The settings may be done by selection of the respective buttons on this settings page.
:p.A more detailed explanation for each control will be shown, if you click on
one of the items in the list below&colon.
:ul compact.
:li.:link reftype=hd refid=wheel_up.&uarrow.:elink.
:li.:link reftype=hd refid=wheel_down.&darrow.:elink.
:li.:link reftype=hd refid=wheel_delete.Delete:elink.
:li.:link reftype=hd refid=wheel_insert.Insert:elink.
:li.:link reftype=hd refid=cancel.Cancel:elink.
:eul.
:note.
This page is only visible, if a wheel has been detected on the mouse.

:p.:hp7.Description of the fields:ehp7.
:p.The behaviour is shown in the bottom box. The left column defines the window / control,
that will react on the wheel turn. The meanings are&colon.
:ul compact.
:li.:hp2.Application:ehp2.
.br
Name of the application (e. g. :font facename=Courier size=14x14.PROGRAMM.EXE:font facename=default.). 
If this field is left empty, the comparison result will always be TRUE. WPS classes always need this field to be empty.
:li.:hp2.Class:ehp2.
.br
Window class of the window / control. Here either the class name (case sensitive!) or the id prefixed by a 
&osq.&numsign.&csq. is entered. If this field is left empty, the comparison result will always be TRUE.
:li.:hp2.Parent Class:ehp2.
.br
Parent window class of the window / control. Here either the class name (case sensitive!) or the id prefixed by a
&osq.&numsign.&csq. is entered. If this field is left empty, the comparison result will always be TRUE.
:li.:hp2.Option:ehp2.
.br
If needed for a specific &osq.vRelation&csq. or &osq.hRelation&csq., here an option will be found (description see there).
In all other cases this field remains empty.
:eul.
:p.The right column defines the action initiated by the wheel. The meanings are&colon.
:ul compact.
:li.:hp2.Mode:ehp2.
.br
Defines the type of message to be sent to the window / control.
:hp2.Scroll:ehp2. will be used, if on page
:link reftype=hd refid=wheel1.Wheel 1:elink. the operation mode
:link reftype=hd refid=msgscroll.Scroll Messages:elink. has been selected.
:hp2.Cursor:ehp2. reacts on 
:link reftype=hd refid=msgline.Keyboard Messages:elink.,
:hp2.Page:ehp2. on
:link reftype=hd refid=msgpage.Scroll entire page per scroll unit:elink..
:hp2.Scroll or Cursor:ehp2. reacts, if the selected operation mode is either
:link reftype=hd refid=msgscroll.Scroll Messages:elink. or
:link reftype=hd refid=msgline.Keyboard Messages:elink..
:hp2.All:ehp2. reacts on all settings.
:li.:hp2.vRelation resp. hRelation:ehp2.
.br
Defines, if the message has to be sent directly to the window / control, or if further searches have to be done
in the window hierarchy. The meanings are&colon.
:ul compact.
:li.:hp2.None:ehp2.&colon. The message will be sent directly to the control found.
:li.:hp2.Parent:ehp2.&colon. A suitable parent is searched for in the description list.
:li.:hp2.Owner:ehp2.&colon. A suitable owner is searched for in the description list.
:li.:hp2.Next:ehp2.&colon. The search will be continued in z-order for controls that also lie below
the mouse pointer.
:li.:hp2.CB Next:ehp2.&colon. Only used for Comboboxes. It basically does the same as :hp2.Next:ehp2.,
but handles the invisible area below the entry field if this list box is not showing.
:li.:hp2.Sibling[Option]:ehp2.&colon. A sibling window will be searched for in the description list with a class name
defined by the :hp2.option:ehp2. entry field.
:eul.
:li.:hp2.vOption / hOption:ehp2.
.br
Contains an option depending on the message type set. See there.
:li.:hp2.Up / Down bzw. Left / Right:ehp2.
.br
Defines the message sent to the window / control. Here the following messages are available&colon.
:ul compact.
:li.:hp2.WM_NULL:ehp2.&colon. No message will be sent. Normally used, if at
:hp2.vRelation:ehp2./:hp2.hRelation:ehp2. the attribute :hp2.None:ehp2. is used.
:li.:hp2.WM_CONTROL:ehp2.&colon. A keyboard code is sent directly to the keyboard driver.
The following options are possible&colon.
:ul compact.
:li.:hp2.page:ehp2.&colon. The keyboard code for the PgUp-/PgDn-keys are sent.
:li.:hp2.cursor up/down:ehp2.&colon. The keyboard code for the Up-/Dn-keys are sent.
:li.:hp2.cursor left/right:ehp2.&colon. The keyboard code for the Left-/Right-cursor keys are sent.
:li.:hp2.mult cursor up/down:ehp2.&colon. The keyboard code for the Up-/Down-cursor keys are sent.
The number of messages sent is defined by the setting in :link reftype=hd refid=scrollitem.Wheel Velocity:elink..
:li.:hp2.mult cursor left/right:ehp2.&colon. The keyboard code for the Left-/Right-cursor keys are sent.
The number of messages sent is defined by the setting in :link reftype=hd refid=scrollitem.Wheel Velocity:elink..
:eul.
:li.:hp2.WM_VSCROLL:ehp2.&colon. A vertical scroll message is sent to the vertical scrollbar.
:li.:hp2.WM_HSCROLL:ehp2.&colon. A vertical scroll message is sent to the horizontal scrollbar.
:li.:hp2.N x WM_VSCROLL:ehp2.&colon. As :hp2.WM_VSCROLL:ehp2., but the number of messages is defined
by the setting in :link reftype=hd refid=scrollitem.Wheel Velocity:elink..
:li.:hp2.N x WM_HSCROLL:ehp2.&colon. As :hp2.WM_HSCROLL:ehp2., but the number of messages is defined
by the setting in :link reftype=hd refid=scrollitem.Wheel Velocity:elink..
:li.:hp2.WM_CHAR:ehp2.&colon. A character message is sent. The same options as for
:hp2.WM_CONTROL:ehp2. are possible.
:eul.
:eul.

:p.:hp7.Examples:ehp7.
:p.Due to a bug in older versions of Mozilla (version 1.3 and older) horizontal scrolling by means of the normal WM_SCROLL-messages
doesn't work. A workaround for this may be introduced by the following two entries.
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Line_001.bmp' align=left.
:p.This entry acts, if on page :link reftype=hd refid=wheel1.Wheel 1:elink. the operation mode
:hp2.Scroll Messages:ehp2. or :hp2.Keyboard Messages:ehp2. has been selected.
In this case horizontal and vertical cursor key messages are sent to the the parent.
(&odq.mult cursor&cdq.). Mozilla is identified, if :hp2.Class:ehp2. as well as
:hp2.Parent Class:ehp2. are of type :hp2.MozillaWindowClass:ehp2..
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Page_001.bmp' align=left.
:p.For pagewise scrolling (:hp2.Mode = Page:ehp2.) a PgUp/PgDown character message is sent in case of vertical scrolling.
:p.:artwork name='C:\work\c\amouse\Language\Help\Command_Line_001.bmp' align=left.
:p.If you turn the wheel above a command line window, the default behaviour is to scroll the window contents (if scrollbars 
are present).
The settings shown cause a scrolling of the command history instead.

:h2 res=2313 id=wheel_up.&uarrow. (Move Entry upward)
:p.Moves the entry selected in the application list one positon upward.

:h2 res=2314 id=wheel_down.&darrow. (Move Entry downward)
:p.Moves the entry selected in the application list one position downward.

:h2 res=2316 id=wheel_delete.Delete
:p.Deletes the entry selected in the list left to this button.

:h2 res=2315 id=wheel_insert.Insert
:p.Inserts a new entry to the list left to this button.

:h1 res=2700 id=insertappl.Insert Application
:i1 id=insertappl.Insert Application
:p.This dialog is used to insert a new definition of wheel behaviour for a selected application.
The meaning of the controls are in accordance with the description in
:link reftype=hd refid=wheel3.wheel 5:elink. :hp2.Description:ehp2. may be used to insert
any user-defined text identifying the entries in the listbox in 
:link reftype=hd refid=wheel3.wheel 5:elink..

:h1 res=1500 id=keys1.Keys 1
:i1 id=keys1.Keys 1
:p.This page is used to define the actions for buttons 3, 4 and 5 of the mouse.
:p.The settings may be done by selection of the respective choice on this settings page.
:p.A more detailed explanation for each control will be shown, if you click on 
one of the items in the list below&colon.
:ul compact.
:li.:link reftype=hd refid=button3.Button 3:elink.
:li.:link reftype=hd refid=button4.Button 4:elink.
:li.:link reftype=hd refid=button5.Button 5:elink.
:li.:link reftype=hd refid=button6.Button 6:elink.
:li.:link reftype=hd refid=button7.Button 7:elink.
:li.:link reftype=hd refid=button8.Button 8:elink.
:li.:link reftype=hd refid=button9.Button 9:elink.
:li.:link reftype=hd refid=button10.Button 10:elink.
:li.:link reftype=hd refid=cbutton3.Ctrl+Button 3:elink.
:li.:link reftype=hd refid=cbutton4.Ctrl+Button 4:elink.
:li.:link reftype=hd refid=cbutton5.Ctrl+Button 5:elink.
:li.:link reftype=hd refid=cbutton6.Ctrl+Button 6:elink.
:li.:link reftype=hd refid=cbutton7.Ctrl+Button 7:elink.
:li.:link reftype=hd refid=cbutton8.Ctrl+Button 8:elink.
:li.:link reftype=hd refid=cbutton9.Ctrl+Button 9:elink.
:li.:link reftype=hd refid=cbutton10.Ctrl+Button 10:elink.
:li.:link reftype=hd refid=abutton3.Alt+Button 3:elink.
:li.:link reftype=hd refid=abutton4.Alt+Button 4:elink.
:li.:link reftype=hd refid=abutton5.Alt+Button 5:elink.
:li.:link reftype=hd refid=abutton6.Alt+Button 6:elink.
:li.:link reftype=hd refid=abutton7.Alt+Button 7:elink.
:li.:link reftype=hd refid=abutton8.Alt+Button 8:elink.
:li.:link reftype=hd refid=abutton9.Alt+Button 9:elink.
:li.:link reftype=hd refid=abutton10.Alt+Button 10:elink.
:li.:link reftype=hd refid=keycombset3.Set 3:elink.
:li.:link reftype=hd refid=keycombset4.Set 4:elink.
:li.:link reftype=hd refid=keycombset5.Set 5:elink.
:li.:link reftype=hd refid=keycombset6.Set 6:elink.
:li.:link reftype=hd refid=keycombset7.Set 7:elink.
:li.:link reftype=hd refid=keycombset8.Set 8:elink.
:li.:link reftype=hd refid=keycombset9.Set 9:elink.
:li.:link reftype=hd refid=keycombset10.Set 10:elink.
:li.:link reftype=hd refid=keycomb.Key combination:elink.
:li.:link reftype=hd refid=cancel.Cancel:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.
:note.
This page is only visible, if a wheel has been detected on the mouse.

:p.:hp2.Button functions:ehp2.
:p.The following functions are available&colon.

:ul.
:li.:hp5.Cut:ehp5.
.br
The clipboard function "Cut" will be performed (Shift-Del)
:li.:hp5.Copy:ehp5.
.br
The clipboard function "Copy" will be performed (Ctrl-Ins)
:li.:hp5.Paste:ehp5.
.br
The clipboard function "Paste" will be performed (Shift-Ins)
:li.:hp5.Center button:ehp5.
.br
The selected button will behave as the standard button 3 of a mouse. The state of
shift keys on the keyboard is preserved and handled correctly.
:li.:hp5.Minimize/Hide all windows:ehp5.
.br
All windows will be minimized or hidden, depending on the behaviour of the window.
:li.:hp5.Restore all windows:ehp5.
.br
All windows will be restored to the size prior to the minimize/hide/maximize function.
:li.:hp5.Window list:ehp5.
.br
The window list will be shown.
:li.:hp5.Close application:ehp5. 
.br
The application will be closed.
:li.:hp5.Double click:ehp5.
.br
A double click message will be sent to the applicaton.
:li.:hp5.Maximize window:ehp5.
.br
The window will be maximized.
:li.:hp5.Minimize/Hide window:ehp5.
.br
The window will be minimized or hidded depending on the behaviour of the window.
:li.:hp5.Restore window:ehp5.
.br
The window will be restored to its size prior to a minimize/hide/maximize function.
:li.:hp5.Toggle scroll direction:ehp5.
.br
The scroll direction will be toggled between vertical and horizontal.
:li.:hp5.Push window to background:ehp5.
.br
The window beneath the mouse pointer will be shifted behind all other windows on
the desktop.
:li.:hp5.Key combination:ehp5.
.br
The key code of the key combination shown in the entry field will be sent to the application.
:li.:hp5.No Action:ehp5.
.br
Pressing the button does not cause any action.
:eul.

:h2 res=1501 id=button3.Button 3
:p.This combination box control is used to select the action to occur when
pressing mouse button 3.

:h2 res=1502 id=button4.Button 4
:p.This combination box control is used to select the action to occur when
pressing mouse button 4.

:h2 res=1503 id=button5.Button 5
:p.This combination box control is used to select the action to occur when
pressing mouse button 5.

:h2 res=1504 id=button6.Button 6
:p.This combination box control is used to select the action to occur when
pressing mouse button 6.

:h2 res=1505 id=button7.Button 7
:p.This combination box control is used to select the action to occur when
pressing mouse button 7.

:h2 res=1506 id=button8.Button 8
:p.This combination box control is used to select the action to occur when
pressing mouse button 8.

:h2 res=1507 id=button9.Button 9
:p.This combination box control is used to select the action to occur when
pressing mouse button 9.

:h2 res=1508 id=button10.Button 10
:p.This combination box control is used to select the action to occur when
pressing mouse button 10.

:h2 res=1511 id=cbutton3.Ctrl+Button 3
:p.This combination box control is used to select the action to occur when
pressing mouse button 3 together with the Ctrl-key on the keyboard.

:h2 res=1512 id=cbutton4.Ctrl+Button 4
:p.This combination box control is used to select the action to occur when
pressing mouse button 4 together with the Ctrl-key on the keyboard.

:h2 res=1513 id=cbutton5.Ctrl+Button 5
:p.This combination box control is used to select the action to occur when
pressing mouse button 5 together with the Ctrl-key on the keyboard.

:h2 res=1514 id=cbutton6.Ctrl+Button 6
:p.This combination box control is used to select the action to occur when
pressing mouse button 6 together with the Ctrl-key on the keyboard.

:h2 res=1515 id=cbutton7.Ctrl+Button 7
:p.This combination box control is used to select the action to occur when
pressing mouse button 7 together with the Ctrl-key on the keyboard.

:h2 res=1516 id=cbutton8.Ctrl+Button 8
:p.This combination box control is used to select the action to occur when
pressing mouse button 8 together with the Ctrl-key on the keyboard.

:h2 res=1517 id=cbutton9.Ctrl+Button 9
:p.This combination box control is used to select the action to occur when
pressing mouse button 9 together with the Ctrl-key on the keyboard.

:h2 res=1518 id=cbutton10.Ctrl+Button 10
:p.This combination box control is used to select the action to occur when
pressing mouse button 10 together with the Ctrl-key on the keyboard.

:h2 res=1521 id=abutton3.Alt+Button 3
:p.This combination box control is used to select the action to occur when
pressing mouse button 3 together with the Alt-key on the keyboard.

:h2 res=1522 id=abutton4.Alt+Button 4
:p.This combination box control is used to select the action to occur when
pressing mouse button 4 together with the Alt-key on the keyboard.

:h2 res=1523 id=abutton5.Alt+Button 5
:p.This combination box control is used to select the action to occur when
pressing mouse button 5 together with the Alt-key on the keyboard.

:h2 res=1524 id=abutton6.Alt+Button 6
:p.This combination box control is used to select the action to occur when
pressing mouse button 6 together with the Alt-key on the keyboard.

:h2 res=1525 id=abutton7.Alt+Button 7
:p.This combination box control is used to select the action to occur when
pressing mouse button 7 together with the Alt-key on the keyboard.

:h2 res=1526 id=abutton8.Alt+Button 8
:p.This combination box control is used to select the action to occur when
pressing mouse button 8 together with the Alt-key on the keyboard.

:h2 res=1527 id=abutton9.Alt+Button 9
:p.This combination box control is used to select the action to occur when
pressing mouse button 9 together with the Alt-key on the keyboard.

:h2 res=1528 id=abutton10.Alt+Button 10
:p.This combination box control is used to select the action to occur when
pressing mouse button 10 together with the Alt-key on the keyboard.

:h2 res=1529 id=keycombset3.Set key combination 3
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button3.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1530 id=keycombset4.Set key combination 4
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button4.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1531 id=keycombset5.Set key combination 5
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button5.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1532 id=keycombset6.Set key combination 6
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button6.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1533 id=keycombset7.Set key combination 7
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button7.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1534 id=keycombset8.Set key combination 8
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button8.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1535 id=keycombset9.Set key combination 9
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button9.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1536 id=keycombset10.Set key combination 10
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button10.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1537 id=keycomb.Define key combination
:p.This entry field allows to define key combinations, that may be assigned to an arbitrary mouse button.
:p.After a key combination has been defined and assigned to a mouse button, this key combination will be sent to 
the applicaton, if the responding mouse button has been pressed.
:p.To define a key combination, the entry field must be clicked. Afterwards, the key combination has to be pressed (e.g. :hp2.Alt-F4:ehp2.).
The entry field then shows this key combination. By pressing one of the :hp2.Set:ehp2.-buttons, this key combination is
assiged to the corresponding mouse button.

:h1 res=1700 id=keys2.Keys 2
:i1 id=keys2.Keys 2
:p.This page is used to define the behaviour of various controls on mouse actions.
:p.The settings may be done by selection of the respective choice on this settings page.
:p.A more detailed explanation for each control will be shown, if you click on 
one of the items in the list below&colon.
:ul compact.
:li.:link reftype=hd refid=dblclick_entry.Double click on entry fields:elink.
:li.:link reftype=hd refid=click_combo.Click on combo boxes:elink.
:li.:link reftype=hd refid=smartcruise.SmartCruise:elink.
:li.:link reftype=hd refid=cancel.Undo:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.

:h2 res=1701 id=dblclick_entry.Double Click on Entry Fields
:p.If this button is selected, a double click on an entry field results in the selection of a complete word.

:h2 res=1702 id=click_combo.Click on Combo Boxes
:p.If this button is selected, a click on the entry field part of a combo box results in rolling down 
of the list box part.

:h2 res=1703 id=smartcruise.SmartCruise
:p.This enables the SmartCruise feature of Logitech MX500, MX700 and MX1000 mice. If this checkbox
is activated, the settings for buttons 7, 8, 9 and 10 are ignored. With this feature, buttons 7 and 8 
scroll vertically, buttons 9 and 10 (if present) scroll horizontally. 

:h1 res=1100 id=devinfo.Device Information
:i1 id=devinfo.Device Information
:p.This page shows the kind and version number of the software on the PC that
is related to this product.
:p.Moreover you are informed about the type of mouse detected by your system.
:note.
For a lot of mice it is impossible to detect the number of buttons correctly. Additionally
the Presentation Manager only supports 3 buttons as the maximum. This is the reason
why possibly the number of buttons displayed might be incorrect, if the mouse 
has more than 3 of them.

:h1 res=1300 id=wldevinfo.Device Information 2
:i1 id=wldevinfo.Device Information 2
:p.This pate shows specific informations for wireless mice, if they support the query of these data.
:p.The :hp5.Device number:ehp5. is only interesting for USB mice and shows the device index.
:p.The :hp5.Channel number:ehp5. shows the used channel with mice, that support multiple channels.
:p.The :hp5.Battery state:ehp5. shows the current charging state of the battery.
:p.A more detailed explanation for each control will be shown, if you click on 
one of the items in the list below&colon.
:ul compact.
:li.:link reftype=hd refid=battery_warning.Battery warning:elink.
:eul.

:h2 res=1304 id=battery_warning.Battery Warning
:p.If this checkbox is checked, a message box will pop up, if the battery of your mouse is near to empty.

:h1 res=2500 id=timing.Timings
:i1 id=timing.Timings
:p.This dialog page is used to set some timings of the mouse: the internal polling rate as well as 
the acceleration values.
 
:p.:hp5.Description of the acceleration:ehp5.&colon. For each mouse event, the count of physical 
units moved is compared against the 1st and 2nd level thresholds. If the count is greater than the 2nd level 
threshold, the 2nd level multiplier will be used; if the count is greater than the 
1st level but less than the 2nd level, the 1st level multiplier will be used. If the 
count is less than the 1st level threshold, no multiplier will be used. These 
calculations are done separately for the X- and Y-axis. 
The values are calculated as follows&colon.

:table cols='20 20' rules=both frame=box.
:row.
:c.1st level threshold
:c.slider value
:row.
:c.2nd level threshold
:c.slider value * 7
:row.
:c.1st level multiplier
:c.slider value
:row.
:c.2nd level multiplier
:c.slider value * 2
:etable.

:ul compact.
:li.:link reftype=hd refid=pollrate.Mouse polling rate:elink.
:li.:link reftype=hd refid=mouaccel_value.Acceleration value:elink.
:li.:link reftype=hd refid=mouaccel_threshold.Acceleration threshold:elink.
:li.:link reftype=hd refid=cancel.Cancel:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.

:h2 res=2501 id=pollrate.Mouse Polling Rate
:p.This slider defines the internal polling rate of the mouse.

:h2 res=2502 id=mouaccel_value.Acceleration Value
:p.This slider defines the acceleration value.

:h2 res=2503 id=mouaccel_threshold.Acceleration Threshold
:p.This slider defines the acceleration threshold.

:euserdoc.
