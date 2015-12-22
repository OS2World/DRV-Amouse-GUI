/* REXX */

/*
 * AMouse. This file was created for Noller & Breining 
 * by Project Smarts on 30 Aug 1997. 
 */

/*  REXX - AMouse install script                        */
/*  Installs AMouse's DLL                               */

Parse source . . __rexx_name;
__rexx_dir = Filespec('D',__rexx_name)||Filespec('P',__rexx_name)

Call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs';
Call SysLoadFuncs;           

     /* Get system DLL directory path */
     system_dll=FileSpec('Drive',Value('SYSTEM_INI',,'OS2ENVIRONMENT'))||'\OS2\DLL';

     rc=SysDeregisterObjectClass('AMouse');     /* Deregister AMouse class */

     Address CMD '@ERASE 'system_dll'\AMOUSE.DLL 2>NUL';    /* Erase old DLL */

     Address CMD '@COPY '__rexx_dir'AMOUSE.DLL 'system_dll; /* Copy new DLL to system DLL dir */

     If rc <> 0                 /* If AMouse class did not deregister OK */
        Then Do;
          Say  "AMouse: Could not replace the AMouse DLL, rc="rc".";
          Say  "AMouse: Delete the object and the DLL from \OS2\DLL directory.";
          Exit;
          End;

     /* Everything OK so far.  Register AMouse class */
     rc=SysRegisterObjectClass('AMouse',system_dll||'\AMOUSE.DLL');

     If rc <> 1                 /* If AMouse class did not register OK */
        Then Do;
          Say  "AMouse: could not register AMouse class, rc="rc".";
          Exit;
          End;    

     /* Now create object on Desktop */
     rc=SysCreateObject('AMouse', 'AMouse', '<WP_DESKTOP>', ,
                        'ICONFILE='__rexx_dir'AMOUSE.ICO;OBJECTID=<AMOUSE>;',,
                        'replace');

     If rc <> 1                 /* If there were create errors */
        Then Do;
          Say  "AMouse: could not create object on the Desktop, rc="rc".";
          End;
Exit;
