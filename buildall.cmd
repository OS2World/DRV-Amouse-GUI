/* Build complete AMouse package */
/* Syntax: buildall <buildlevel> */

/* Check arguments */
parse arg bldlvl

if bldlvl='' then do
  say 'incomplete arguments; Syntax:'
  say 'buildall <buildlevel>'
  say '  buildlevel := X.XX.XX'
  exit
end

/* Language independent part */
say
say '[33mÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿[37m'
say '[33m³ Language independent part ³[37m'
say '[33mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ[37m'
say '[33m- AMouHook -[37m'
'cd AMouHook'
'sed -e "s/X.XX.XX/'bldlvl'/" AMouHook.tpl > AMouHook.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end

say
say '[33m- AMouDll -[37m'
'cd ..\AMouseDll'
'sed -e "s/X.XX.XX/'bldlvl'/" AMouDll.tpl > AMouDll.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end

say
say '[33m- MouClass -[37m'
'cd ..\MouClass'
'sed -e "s/X.XX.XX/'bldlvl'/" MouClass.tpl > MouClass.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end

say
say '[33m- AMouse.exe -[37m'
'cd ..\Config\MouSet'
'sed -e "s/X.XX.XX/'bldlvl'/" AMouse.tpl > AMouse.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end

say
say '[33m- AMouse.dll -[37m'
'cd ..\som2'
'sed -e "s/X.XX.XX/'bldlvl'/" AMouse.tpl > AMouse.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end
'cd ..'

say
say '[33m- MouSyDll -[37m'
'cd ..\MouSyDLL'
'sed -e "s/X.XX.XX/'bldlvl'/" MouSyDll.tpl > MouSyDll.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end
'cd ..'

say
say '[33m- PMCtlsPP -[37m'
'cd PMCtlsPP'
'sed -e "s/X.XX.XX/'bldlvl'/" PMCtlsPP.tpl > PMCtlsPP.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
'cd ..'

/* Language dependent part */
say
say '[33mÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿[37m'
say '[33m³ Language dependent part ³[37m'
say '[33mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ[37m'

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

say
say '[33m- Header files -[37m'
'cd Language'
'copy ..\dlg.h   .'
'copy ..\panel.h .'
'copy ..\res.h   .'

say
say '[33m- Help files -[37m'
'cd Help'
call makehlp.cmd
if RC > 0 then do
  EXIT
end

say
say '[33m- Resource files -[37m'
'cd ..\Resource'
do i = 1 to lang.0
  'sed -e "s/X.XX.XX/'bldlvl'/" AMou'lang.i'.tpl > AMou'lang.i'.def'
end
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end

/* XWorkplace support */
say
say '[33mÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿[37m'
say '[33m³ Workplace support ³[37m'
say '[33mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ[37m'

xlang.0  = 3
xlang.1  = "001"
xlang.2  = "033"
xlang.3  = "049"
xlang2.1 = "US"
xlang2.2 = "FR"
xlang2.3 = "DE"

'cd ..\..\XWPWidget'
'sed -e "s/X.XX.XX/'bldlvl'/" XWPWidget.tpl > XWPWidget.def'
'nmake cleanall'
'nmake DEBUG=NO TRACE=NO'
if RC > 0 then do
  EXIT
end
'copy XWPMouse.dll Bundle'

'cd Language'
do i = 1 to xlang.0
  call makehlp.cmd xlang.i xlang2.i
  if RC > 0 then do
    EXIT
  end
  'copy XAMou'xlang.i'.hlp ..\Bundle'
end

'cd ..\..'

/* Generate installer packages */
say
say '[33mÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿[37m'
say '[33m³ IBM installer support removed ³[37m'
say '[33mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ[37m'
/* call buildIBB.cmd bldlvl */

/* Generate WARPInstall package */
call buildWarpIn.cmd bldlvl

say '** Finished **'

