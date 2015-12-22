# makefile
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES:

.SUFFIXES: \
    .c .obj .rc .res

INCLUDE = ..;$(INCLUDE)

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r $(RTR) -i . -i .. %s %|fF.RES

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /I. /I.. /Ss /Q /Rn /Gd- /Ge- /G5 /C %s

all: \
    .\AMou001.dll \
    .\AMou007.dll \
    .\AMou031.dll \
    .\AMou033.dll \
    .\AMou034.dll \
    .\AMou039.dll \
    .\AMou046.dll \
    .\AMou049.dll

m001:    .\AMou001.dll
m007:    .\AMou007.dll
m031:    .\AMou031.dll
m033:    .\AMou033.dll
m034:    .\AMou034.dll
m039:    .\AMou039.dll
m046:    .\AMou046.dll
m049:    .\AMou049.dll

.\AMou049.dll: \
    .\dummy.obj \
    .\AMou049.res \
    .\AMou049.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou049.dll
     .\AMou049.def
     .\dummy.obj
<<
    rc.exe .\AMou049.res AMou049.dll

.\AMou046.dll: \
    .\dummy.obj \
    .\AMou046.res \
    .\AMou046.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou046.dll
     .\AMou046.def
     .\dummy.obj
<<
    rc.exe .\AMou046.res AMou046.dll

.\AMou039.dll: \
    .\dummy.obj \
    .\AMou039.res \
    .\AMou039.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou039.dll
     .\AMou039.def
     .\dummy.obj
<<
    rc.exe .\AMou039.res AMou039.dll

.\AMou031.dll: \
    .\dummy.obj \
    .\AMou031.res \
    .\AMou031.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou031.dll
     .\AMou031.def
     .\dummy.obj
<<
    rc.exe .\AMou031.res AMou031.dll

.\AMou033.dll: \
    .\dummy.obj \
    .\AMou033.res \
    .\AMou033.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou033.dll
     .\AMou033.def
     .\dummy.obj
<<
    rc.exe .\AMou033.res AMou033.dll

.\AMou034.dll: \
    .\dummy.obj \
    .\AMou034.res \
    .\AMou034.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou034.dll
     .\AMou034.def
     .\dummy.obj
<<
    rc.exe .\AMou034.res AMou034.dll

.\AMou001.dll: \
    .\dummy.obj \
    .\AMou001.res \
    .\AMou001.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou001.dll
     .\AMou001.def
     .\dummy.obj
<<
    rc.exe .\AMou001.res AMou001.dll

.\AMou007.dll: \
    .\dummy.obj \
    .\AMou007.res \
    .\AMou007.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B"/noe"
     /FeAMou007.dll
     .\AMou007.def
     .\dummy.obj
<<
    rc.exe .\AMou007.res AMou007.dll

.\AMou001.res: \
    ..\dlg.h \
    .\batt0.bmp \
    .\batt1.bmp \
    .\batt2.bmp \
    .\batt3.bmp \
    .\batt4.bmp \
    .\batt5.bmp \
    .\batt6.bmp \
    .\batt7.bmp \
    .\AMou001.rc \
    .\AMou001.dlg

.\AMou007.res: \
    ..\dlg.h \
    .\batt0.bmp \
    .\batt1.bmp \
    .\batt2.bmp \
    .\batt3.bmp \
    .\batt4.bmp \
    .\batt5.bmp \
    .\batt6.bmp \
    .\batt7.bmp \
    .\AMou007.rc \
    .\AMou007.dlg

.\AMou033.res: \
    ..\dlg.h \
    .\batt0.bmp \
    .\batt1.bmp \
    .\batt2.bmp \
    .\batt3.bmp \
    .\batt4.bmp \
    .\batt5.bmp \
    .\batt6.bmp \
    .\batt7.bmp \
    .\AMou033.rc \
    .\AMou033.dlg

.\AMou034.res: \
    ..\dlg.h \
    .\batt0.bmp \
    .\batt1.bmp \
    .\batt2.bmp \
    .\batt3.bmp \
    .\batt4.bmp \
    .\batt5.bmp \
    .\batt6.bmp \
    .\batt7.bmp \
    .\AMou034.rc \
    .\AMou034.dlg

.\AMou039.res: \
    ..\dlg.h \
    .\batt0.bmp \
    .\batt1.bmp \
    .\batt2.bmp \
    .\batt3.bmp \
    .\batt4.bmp \
    .\batt5.bmp \
    .\batt6.bmp \
    .\batt7.bmp \
    .\AMou039.rc \
    .\AMou039.dlg

.\AMou046.res: \
    ..\dlg.h \
    .\batt0.bmp \
    .\batt1.bmp \
    .\batt2.bmp \
    .\batt3.bmp \
    .\batt4.bmp \
    .\batt5.bmp \
    .\batt6.bmp \
    .\batt7.bmp \
    .\AMou046.rc \
    .\AMou046.dlg

.\AMou049.res: \
    ..\dlg.h \
    .\batt0.bmp \
    .\batt1.bmp \
    .\batt2.bmp \
    .\batt3.bmp \
    .\batt4.bmp \
    .\batt5.bmp \
    .\batt6.bmp \
    .\batt7.bmp \
    .\AMou049.rc \
    .\AMou049.dlg

.\dummy.obj: \
    .\dummy.c

cleanall:
      @if exist *.obj del *.obj
      @if exist *.res del *.res
      @if exist *.dll del *.dll

copyall:
      @if exist AMou001.dll copy AMou001.dll ..\..\Install_Source
      @if exist AMou007.dll copy AMou007.dll ..\..\Install_Source
      @if exist AMou033.dll copy AMou033.dll ..\..\Install_Source
      @if exist AMou034.dll copy AMou034.dll ..\..\Install_Source
      @if exist AMou039.dll copy AMou039.dll ..\..\Install_Source
      @if exist AMou046.dll copy AMou046.dll ..\..\Install_Source
      @if exist AMou049.dll copy AMou049.dll ..\..\Install_Source

