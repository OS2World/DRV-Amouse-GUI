# makefile
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES:

.SUFFIXES: \
    .c .obj

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) $(CTR) /I. /I.. /Ss /Q /Rn /Gd- /Ge- /G5 /C %s

{.\}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) $(CTR) /I. /I.. /Ss /Q /Rn /Gd- /Ge- /G5 /C %s

all: \
    .\AMouHook.dll

.\AMouHook.dll: \
    .\AMouHook.obj \
    .\AMouHwnd.obj \
    .\AMouHData.obj \
    .\AMouHook.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B" $(LDB) /dbgpack /noe /map"
     /FeAMouHook.dll
     .\AMouHook.def
     .\AMouHook.obj
     .\AMouHwnd.obj
     .\AMouHData.obj
<<
    implib.exe AMouHook.lib AMouHook.dll

.\AMouHook.obj: \
    .\AMouHook.c \
    .\AMouHook.h \
    .\AMouHData.h \
    .\AMouHwnd.h \
    ..\PMWinMou.h

.\AMouHwnd.obj: \
    .\AMouHwnd.c \
    .\AMouHwnd.h \
    .\AMouHData.h

.\AMouHData.obj: \
    .\AMouHData.c \
    .\AMouHData.h

cleanall:
      @if exist *.obj del *.obj
      @if exist *.dll del *.dll

