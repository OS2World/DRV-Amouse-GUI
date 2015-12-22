/* create language support archive */
call RxFuncadd SysLoadFuncs, RexxUtil, SysLoadFuncs
call SysLoadFuncs

LSDir = 'LangSupport'

TempDir = value('temp',, 'OS2ENVIRONMENT')
ret = Directory(TempDir)

mkdir LSDir
ret = Directory(LSDir)

copy 'd:\devtools\ipfcpp\ipfcprep.exe' .
copy 'd:\devtools\ipfcpp\ipfcprep.inf' .
copy 'k:\work\c\amouse\panel.h' .
copy 'k:\work\c\amouse\res.h'   .
copy 'k:\work\c\amouse\dlg.h'   .
copy 'k:\work\c\amouse\Language\readme' .

mkdir 'Help'
mkdir 'Resource'

/* IBM Installer support removed
 * mkdir 'Install'
 * mkdir 'Install\DEU'
 * mkdir 'Install\ENU'
 * mkdir 'Install\NLD'
 * mkdir 'Install\FRA'
 * mkdir 'Install\ITA'
 * mkdir 'Install\RUS'
 * mkdir 'Install\SWE'
 */

Help.1  = 'AMou001.scr'
Help.2  = 'AMou007.scr'
Help.3  = 'AMou031.scr'
Help.4  = 'AMou033.scr'
Help.5  = 'AMou034.scr'
Help.6  = 'AMou039.scr'
Help.7  = 'AMou046.scr'
Help.8  = 'AMou049.scr'
Help.9  = 'AMouse.bmp'
Help.10 = 'makehlp.cmd'
do i = 1 to 9
  copy 'k:\work\c\AMouse\Language\Help\'Help.i 'Help'
end

/* IBM Installer support removed
 * Install.1 = 'InstallExit\IExit*.dlg'
 * Install.2 = 'InstallExit\IExit*.rc'
 * do i = 1 to 2
 *   copy 'k:\work\c\AMouse\'Install.i 'Install'
 * end
 *
 * InstallLNG.1 = 'Source\AMouse.dsc'
 * InstallLNG.2 = 'Source\AMouse.icf'
 * InstallLNG.3 = 'Source\read.me'
 * InstallLNG.4 = 'AMouse.pkg'
 * InstallLNG.5 = 'iirc.rc'
 * do i = 1 to 6
 *   copy 'k:\work\c\AMouse\Install_DEU\'InstallLNG.i 'Install\DEU'
 *   copy 'k:\work\c\AMouse\Install_ENU\'InstallLNG.i 'Install\ENU'
 *   copy 'k:\work\c\AMouse\Install_NLD\'InstallLNG.i 'Install\NLD'
 *   copy 'k:\work\c\AMouse\Install_FRA\'InstallLNG.i 'Install\FRA'
 *   copy 'k:\work\c\AMouse\Install_ITA\'InstallLNG.i 'Install\ITA'
 *   copy 'k:\work\c\AMouse\Install_RUS\'InstallLNG.i 'Install\RUS'
 *   copy 'k:\work\c\AMouse\Install_SWE\'InstallLNG.i 'Install\SWE'
 * end
 */

Resource.1  = 'AMou001.def'
Resource.2  = 'AMou001.dlg'
Resource.3  = 'AMou001.rc'
Resource.4  = 'AMou007.def'
Resource.5  = 'AMou007.dlg'
Resource.6  = 'AMou007.rc'
Resource.7  = 'AMou031.def'
Resource.8  = 'AMou031.dlg'
Resource.9  = 'AMou031.rc'
Resource.10 = 'AMou033.def'
Resource.11 = 'AMou033.dlg'
Resource.12 = 'AMou033.rc'
Resource.13 = 'AMou034.def'
Resource.14 = 'AMou034.dlg'
Resource.15 = 'AMou034.rc'
Resource.16 = 'AMou039.def'
Resource.17 = 'AMou039.dlg'
Resource.18 = 'AMou039.rc'
Resource.19 = 'AMou046.def'
Resource.20 = 'AMou046.dlg'
Resource.21 = 'AMou046.rc'
Resource.22 = 'AMou049.def'
Resource.23 = 'AMou049.dlg'
Resource.24 = 'AMou049.rc'
Resource.25 = 'dummy.c'
Resource.26 = 'AMouse.ico'
Resource.27 = 'makefile'
do i = 1 to 27
  copy 'k:\work\c\AMouse\Language\Resource\'Resource.i 'Resource'
end

erase 'AMouLang.zip'
'zip -r AMouLang *'

