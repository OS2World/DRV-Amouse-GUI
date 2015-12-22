/* create installer package */
/* Syntax: create_wpi <version> */

/* Check arguments */
parse arg version

if bldlvl='' then do
  say 'incomplete arguments; Syntax:'
  say 'buildall <version>'
  say '  buildlevel := X.XX'
  exit
end

position = POS(".",version)
ver = DELSTR(version,position,1)

'setlocal'
'set path=k:\programme\WarpIn;%path%'
'set beginlibpath=k:\programme\WarpIn'
'del AMouse'ver'.wpi'
'del AMouse'ver'.exe'
'wic AMouse'ver'.wpi -a 1 -cBase * 2 -cNLS\ENU * 3 -cNLS\FRA * 4 -cNLS\ITA * 5 -cNLS\SWE * 6 -cNLS\DEU * 7 -cNLS\RUS * 8 -cNLS\ESP * 9 -cNLS\NLD * -s AMouse.wis '
'wic AMouse'ver'.exe -a 1 -cBase * 2 -cNLS\ENU * 3 -cNLS\FRA * 4 -cNLS\ITA * 5 -cNLS\SWE * 6 -cNLS\DEU * 7 -cNLS\RUS * 8 -cNLS\ESP * 9 -cNLS\NLD * -u -s AMouse.wis '
'endlocal'
