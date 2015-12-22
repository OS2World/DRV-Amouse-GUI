/* REXX */

/*
 * AMouse. This file was created for Noller & Breining
 */

Parse source . . __rexx_name;
__rexx_dir = Filespec('D',__rexx_name)||Filespec('P',__rexx_name)

Call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs';
Call SysLoadFuncs;

rc=SysDeregisterObjectClass('WPStickMouse');     /* Deregister IBM class */
say "Result = " rc

