/* generate german installer package */
epfifile.1  = epfiEXTS.dll
epfifile.2  = EPFIHELP.INF
epfifile.3  = EpfiHPLB.HLP
epfifile.4  = epfiicis.ico
epfifile.5  = epfimsg.msg
epfifile.6  = epfinsts.exe
epfifile.7  = epfipii.dll
epfifile.8  = epfiprcs.exe
epfifile.9  = epfirsbk.dll
epfifile.10 = epfiupk2.exe
do i = 1 to 10
  copy epfifile.i 'Source_temp'
end
copy '..\Install_Source\* Source_temp'
copy 'Source\* Source_temp'
'diskgen /AU DRIVE amouse.pkg k:\work\c\amouse\install_deu\dest k:\work\c\amouse\install_deu\Source_temp < answer'
if RC > 0 then SIGNAL ErrExit
say 'correct Y2K problem:'
'sed -e "s/DATE = ''1/DATE = ''/" AMOUSE.GEN > AMOUSE.CVT'
copy 'EPFISINC.PKG dest'
copy 'INSTALL.EXE  dest'
copy 'INSTALL.IN_  dest'
copy 'AMOUSE.CVT   dest\AMOUSE.PKG'
copy 'EPFISINC.GEN dest\EPFISINC.PKG'
copy 'Source\read.me dest'
del  'AMOUSE.CVT'

ErrExit:
'rdelete Source_temp\*'
