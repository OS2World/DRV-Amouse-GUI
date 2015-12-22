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
    icc.exe /Ss /Ti /Q /G5 /C %s

all: \
    .\AMouseTest.exe

.\AMouseTest.exe: \
    .\AMouseTest.obj \
    .\AMouseTest.def \
    .\AMouseTest.res
    @echo " Link::Linker "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /Q /B" /de /pmtype:vio     "
     /FeAMouseTest.exe
     mmpm2.lib
     .\AMouseTest.def
     .\AMouseTest.obj
<<
    rc.exe .\AMouseTest.res AMouseTest.exe

.\AMouseTest.res: \
    .\AMouseTest.rc \
    .\AMouseTest.dlg \
    .\dlg.h

.\AMouseTest.obj: \
    .\AMouseTest.c \
    .\dlg.h

