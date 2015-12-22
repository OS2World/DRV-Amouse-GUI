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
    .c .obj

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /Ti /Q /G5 /C %s

all: \
    .\getkbd.exe

.\getkbd.exe: \
    .\getkbd.obj \
    .\getkbd.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B" /de"
     /Fegetkbd.exe
     .\getkbd.def
     .\getkbd.obj
<<

.\getkbd.obj: \
    .\getkbd.c

