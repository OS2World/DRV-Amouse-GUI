# makefile
# Erstellt von IBM WorkFrame/2 MakeMake um 18:08:58 am 1 Mai 1998
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::Resource Compiler
#  Compile::C++ Compiler
#  Link::Linker
#  Bind::Resource Bind

.SUFFIXES:

.SUFFIXES: \
    .c .obj .rc .res

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|fF.RES

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /I .. /I ..\.. /Ss /Ti /Q /G5 /C %s

all: \
    .\APITest.exe

.\APITest.exe: \
    .\APITest.obj \
    ..\AMouDll.lib \
    .\APITest.def \
    .\APITest.res
    @echo " Link::Linker "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /Q /B" /de /pmtype:pm     "
     /FeAPITest.exe
     .\APITest.def
     .\APITest.obj
     ..\AMouDll.lib
<<
    rc.exe .\APITest.res APITest.exe

.\APITest.res: \
    .\APITest.rc \
    .\APITest.dlg \
    .\dlg.h

.\APITest.obj: \
    .\APITest.c \
    .\dlg.h

