# makefile
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES:

.SUFFIXES: \
    .c .obj .rc .res

INCLUDE = ..\AMouHook;$(INCLUDE)

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -i .. -r %s %|fF.RES

{.\}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -i .. -r %s %|fF.RES

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) $(CTR) /I. /I.. /Ss /Q /Rn /Gd- /Ge- /G5 /C %s

{.\}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) $(CTR) /I. /I.. /Ss /Q /Rn /Gd- /Ge- /G5 /C %s

all: \
    .\AMouDll.dll

.\AMouDll.dll: \
    .\AMouDll.obj \
    .\AMouData.obj \
    .\AMouIni.obj \
    .\AMouRes.res \
    .\AMouDll.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B" $(LDB) /dbgpack /noe"
     /FeAMouDll.dll $(LTR)
     /FmAMouDll.map
     .\AMouDll.def
     .\AMouDll.obj
     .\AMouData.obj
     .\AMouIni.obj
<<KEEP
    rc.exe .\AMouRes.res AMouDll.dll
    implib .\AMouDll.lib AMouDll.dll

.\AMouRes.res: \
    .\AMouRes.rc

.\AMouDll.obj: \
    .\AMouDll.c \
    ..\AMouRes.h \
    .\AMouData.h \
    .\AMouIni.h \
    {$(INCLUDE)}AMouHook.h \
    .\dosqss.h \
    ..\AMouseGlobal.h

.\AMouData.obj: \
    .\AMouData.c \
    .\AMouData.h \
    ..\AMouseGlobal.h

.\AMouIni.obj: \
    .\AMouIni.c \
    .\AMouData.h \
    .\AMouIni.h \
    ..\AMouseGlobal.h \
    ..\res.h

cleanall:
      @if exist *.obj del *.obj
      @if exist *.res del *.res
      @if exist *.dll del *.dll

