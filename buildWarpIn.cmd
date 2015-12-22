/* Build AMouse package based on WarpIn installer */
/* Syntax: buildWarpIn <buildlevel> */

/* Check arguments */
parse arg bldlvl

if bldlvl='' then do
  say 'incomplete arguments; Syntax:'
  say 'buildWarpIn <buildlevel>'
  say '  buildlevel := X.XX.XX'
  exit
end

major = SUBSTR(bldlvl,1,1)
minor = SUBSTR(bldlvl,3,2)
build = SUBSTR(bldlvl,6,2,'0')

/* Generate WARPInstall package */
say
say '[33mÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿[37m'
say '[33m³ WarpIn packages ³[37m'
say '[33mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ[37m'

'copy AMouseDll\AMouDll.dll WPS_Install\Base'
'copy AMouseDll\AMouDll.lib WPS_Install\Base'
'copy AMouHook\AMouHook.dll WPS_Install\Base'
'copy AMouRes.h WPS_Install\Base'
'copy PMWinMou.h WPS_Install\Base'
'copy AMouseDll\AMouRes.rc WPS_Install\Base'
'copy config\som2\amouse.dll WPS_Install\Base'
'copy config\mouSet\amouse.exe WPS_Install\Base'
'copy config\mouSet\AMOUSE.ICO WPS_Install\Base'
'copy Install_Source\amouse.sys WPS_Install\Base'
'copy MouClass\MOUCLASS.exe WPS_Install\Base'
'copy MouSyDLL\MOUSYDLL.exe WPS_Install\Base'
'copy Install_Source\nbaudio.dll WPS_Install\Base'
'copy PMCtlsPP\PMCtlsPP.dll WPS_Install\Base'
'copy Install_Source\usb.ids WPS_Install\Base'
'copy Install_Source\usbmouse.sys WPS_Install\Base'

'copy Language\Resource\AMou001.dll WPS_Install\NLS\ENU'
'copy Language\Resource\AMou007.dll WPS_Install\NLS\RUS'
'copy Language\Resource\AMou031.dll WPS_Install\NLS\NLD'
'copy Language\Resource\AMou033.dll WPS_Install\NLS\FRA'
'copy Language\Resource\AMou034.dll WPS_Install\NLS\ESP'
'copy Language\Resource\AMou039.dll WPS_Install\NLS\ITA'
'copy Language\Resource\AMou046.dll WPS_Install\NLS\SWE'
'copy Language\Resource\AMou049.dll WPS_Install\NLS\DEU'
'copy Language\Help\AMou001.HLP WPS_Install\NLS\ENU'
'copy Language\Help\AMou007.HLP WPS_Install\NLS\RUS'
'copy Language\Help\AMou031.HLP WPS_Install\NLS\NLD'
'copy Language\Help\AMou033.HLP WPS_Install\NLS\FRA'
'copy Language\Help\AMou034.HLP WPS_Install\NLS\ESP'
'copy Language\Help\AMou039.HLP WPS_Install\NLS\ITA'
'copy Language\Help\AMou046.HLP WPS_Install\NLS\SWE'
'copy Language\Help\AMou049.HLP WPS_Install\NLS\DEU'
'copy Install_ENU\source\read.me WPS_Install\NLS\ENU\readme.ENU'
'copy Install_RUS\source\read.me WPS_Install\NLS\RUS\readme.RUS'
'copy Install_ENU\source\read.me WPS_Install\NLS\NLD\readme.NLD'
'copy Install_FRA\source\read.me WPS_Install\NLS\FRA\readme.FRA'
'copy Install_ENU\source\read.me WPS_Install\NLS\ESP\readme.ESP'
'copy Install_ITA\source\read.me WPS_Install\NLS\ITA\readme.ITA'
'copy Install_SWE\source\read.me WPS_Install\NLS\SWE\readme.SWE'
'copy Install_DEU\source\read.me WPS_Install\NLS\DEU\readme.DEU'

'cd WPS_Install'
'sed -e "s/\\X\\X\\X/\\'major'\\'minor'\\'build'/" AMouse.tpl > AMouse.wis'
call create_wpi.cmd major'.'minor
'cd ..'

