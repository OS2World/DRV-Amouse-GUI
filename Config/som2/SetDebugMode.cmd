/* change setup string of <AMouse> object.              */
/* If DEVINFO_DEBUG is set to YES, the device info page */
/* shows a debug button. Any other value removes this   */
/* button. If the button is pressed, the mouse driver   */
/* informations are set into a message box and the      */
/* clipboard                                            */

Call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs';
Call SysLoadFuncs;

if arg() = 0 then
  do
  say "Sets the DEVINFO_DEBUG setup string for the <AMOUSE> object"
  say "If set to ""yes"", the device info page shows a DEBUG button,"
  say "   which may be used to determine some mouse parameters that"
  say "   help us to add support for new mice"
  say "If set to ""no"", debugging is disabled"
  exit
  end

/* set default value NO */
command = translate(arg(1))
if command <> "YES" then
  do
  command = "NO"
  say "switch off debugging"
  end
else
  say "switch on debugging"

/* set debug value in AMOUSE object */
objectData = "DEVINFO_DEBUG="command
rc=SysSetObjectData("<AMOUSE>",objectData)

If rc = 1 then
  say "Devinfo_Debug was changed"
else
  say "Devinfo_Debug could not be changed"
