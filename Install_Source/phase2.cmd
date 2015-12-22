/* Replace OS/2 mouse configuration object */
'@echo off'

Call RxFuncadd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
Call SysLoadFuncs

'mouclass.exe REPLACE'

/* Now create object on Desktop */
Call SysCreateObject 'AMouse', 'AMouse', '<NBMSFLDR>',,
                'ICONFILE='__rexx_dir'AMOUSE.ICO;OBJECTID=<AMOUSE>;',,
                'replace'

/* Deregister IBM's wheel mouse WPS class */
Call SysDeregisterObjectClass 'WPStickMouse'

Call SysDestroyObject '<MOUPHASE2>'

