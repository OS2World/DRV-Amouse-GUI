/* change setup string of <AMouse> object.              */
/* If DEVINFO_DEBUG is set to YES, the device info page */
/* shows a debug button. Any other value removes this   */
/* button. If the button is pressed, the mouse driver   */
/* informations are set into a message box and the      */
/* clipboard                                            */

Call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs';
Call SysLoadFuncs;

/* Delete AMOUSE object */
rc = SysDestroyObject("<AMOUSE>")

If rc = 1 then
  say "Object deleted"
else
  say "Object could not be deleted"
