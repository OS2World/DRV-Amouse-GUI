:userdoc.
.************************************************
.*
.*   Copyright 2001 nb software
.*
.*   HELP FOR DIALOG BOX FIELDS
.*   OPEN A GRAPHIC METAFILE
.*
.*   Main panel            -              1000
.*
.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=1000.AMouse - Widget
:i1 id=aboutMain.AMouse - Advanced Mouse Widget
:p.The AMouse widget "XWPMouse" can be used to display
the current settings of the AMouse mouse driver. Three of the
most important settings are displayed on this widget&colon.
:ul compact.
:li.Scroll direction (horizontal / vertical); displayed as a double arrow.
:li.Wheel velocity; the number of lines per scroll unit.
:li.Message type for scroll operation; a bitmap is displayed for these modes&colon.
  :ul compact.
  :li.scroll messages
  :li.keyboard messages&colon.cursor keys
  :li.entire page per scroll unit
  :eul.
:eul.

:p.The first two attributes may be changed using this widget&colon.
:ul compact.
:li.A click on the widget toggles the scroll direction.
:li.Turning the wheel on the widget modifies wheel velocity
:eul.
:euserdoc.

