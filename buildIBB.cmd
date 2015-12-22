/* Build AMouse installer based on IBM installer */
/* Syntax: buildIBB <buildlevel>                 */

/* Check arguments */
parse arg bldlvl

if bldlvl='' then do
  say 'incomplete arguments; Syntax:'
  say 'buildIBB <buildlevel>'
  say '  buildlevel := X.XX.XX'
  exit
end

lang.0 = 8
lang.1 = "001"
lang.2 = "007"
lang.3 = "031"
lang.4 = "033"
lang.5 = "034"
lang.6 = "039"
lang.7 = "046"
lang.8 = "049"

ilang.0  = 7
ilang.1  = "US"
ilang.2  = "RU"
ilang.3  = "NL"
ilang.4  = "FR"
ilang.5  = "IT"
ilang.6  = "SV"
ilang.7  = "GR"
ilang1.1 = "u"
ilang1.2 = "r"
ilang1.3 = "n"
ilang1.4 = "f"
ilang1.5 = "i"
ilang1.6 = "s"
ilang1.7 = "g"
ilang3.1 = "ENU"
ilang3.2 = "RUS"
ilang3.3 = "NLD"
ilang3.4 = "FRA"
ilang3.5 = "ITA"
ilang3.6 = "SWE"
ilang3.7 = "DEU"

/* Installer Exit */
say
say '[33m- InstallExit -[37m'
'cd InstallExit'
'sed -e "s/X.XX.XX/'bldlvl'/" IEXIT.tpl > IEXIT.def'
'nmake cleanall'

do i = 1 to ilang.0
  'nmake DEBUG=NO TRACE=NO LANGUAGE='iLang.i
  if RC > 0 then do
    EXIT
  end
  'copy IExit.dll ..\Install_'ilang3.i'\Source'
  'nmake clean'
end

'cd ..'

/* Generate installer packages */
say
say '[33mÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿[37m'
say '[33m³ Installer packages ³[37m'
say '[33mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ[37m'

'copy AMouHook\AMouHook.dll Install_Source'
'copy AMouseDll\AMouDll.lib  Install_Source'
'copy AMouseDll\AMouDll.dll  Install_Source'
'copy AMouseDll\AMouRes.rc   Install_Source'
'copy AMouRes.h Install_Source'
'copy pmwinmou.h Install_Source'
'copy MouClass\MouClass.exe Install_Source'
'copy Config\MouSet\AMouse.exe Install_Source'
'copy Config\som2\AMouse.dll Install_Source'
'copy MouSyDLL\MouSyDLL.exe Install_Source'
'copy PMCtlsPP\PMCtlsPP.dll Install_Source'
'copy ..\nbaudio\nbaudio.dll Install_Source'
do i = 1 to lang.0
  'copy Language\Help\AMou'lang.i'.hlp Install_Source'
  'copy Language\Resource\AMou'lang.i'.dll Install_Source'
end

bldnum = substr(bldlvl, 1, 3)
bldnum = delstr(bldnum, 2, 1)

do i = 1 to ilang.0
  'cd Install_'ilang3.i
  call mouse_diskgen.cmd
  'cd dest'
  'del amou*.zip'
  'zip amou'bldnum''ilang1.i'.zip *'
  'cd ..\..'
end

