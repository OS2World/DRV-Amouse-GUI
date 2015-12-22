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
    icc.exe /Ss /Ti /Q /G5 /C %s

{.\}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /Ti /Q /G5 /C %s

all: \
    .\test.exe

.\test.exe: \
    .\test.obj \
    .\test.def
    @echo " Link::Linker "
    icc.exe @<<
     /Q /B" $(LDB) /dbgpack /noe /map"
     .\test.def
     .\test.obj
<<

.\test.obj: \
    .\test.c \

cleanall:
      @if exist *.obj del *.obj

