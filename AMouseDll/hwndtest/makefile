# makefile
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES:

.SUFFIXES: \
    .c .obj

INCLUDE = ..\AMouHook;$(INCLUDE)


.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) /I. /I.. /I..\.. /Ss /Q /Rn /Gd- /Ge+ /G5 /C %s

{.\}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) /I. /I.. /I..\.. /Ss /Q /Rn /Gd- /Ge+ /G5 /C %s

all: \
    .\test.exe

.\test.exe: \
    .\AMouHwnd.obj \
    .\AMouHData.obj \
    .\test.obj \
    .\test.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B" $(LDB) /dbgpack /noe"
     $(TDB)
     .\test.def
     .\test.obj
     .\AMouHData.obj
     .\AMouHwnd.obj
<<

.\AMouHwnd.obj: \
    .\AMouHwnd.c \
    ..\..\AMouseGlobal.h

.\AMouHData.obj: \
    .\AMouHData.c \
    .\AMouHData.h \
    ..\..\AMouseGlobal.h

.\test.obj: \
    .\test.c \
    .\AMouHwnd.h \
    ..\..\AMouseGlobal.h

cleanall:
      @if exist *.obj del *.obj
      @if exist *.exe del *.exe

