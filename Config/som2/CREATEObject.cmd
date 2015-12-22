/* REXX */

Call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs';
Call SysLoadFuncs;

/* Query country code of system */
country = SysIni(,'PM_National','iCountry')
num = VERIFY(country,'0123456789')
IF num > 0
   THEN iCountry = ABS(SUBSTR(country,1,num-1))

SELECT
   WHEN iCountry = 7
      THEN Name = 'Œëèì'
   WHEN iCountry = 31
      THEN Name = 'Muis'
   WHEN iCountry = 33
      THEN Name = 'Souris'
   WHEN iCountry = 34
      THEN Name = 'Rat¢n'
   WHEN iCountry = 39
      THEN Name = 'Mouse'
   WHEN iCountry = 46
      THEN Name = 'Mus'
   WHEN iCountry = 49
      THEN Name = 'Maus'
OTHERWISE
   Name = 'Mouse'
END

/* Create AMouse object in config folder */
rc=SysCreateObject('AMouse', Name, '<WP_CONFIG>','OBJECTID=<AMOUSE>','replace');

If rc <> 1                 /* If there were create errors */
   Then Do;
     Say  "AMouse: could not create object on the Desktop, rc="rc".";
     End;

