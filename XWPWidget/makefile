# makefile
# Erstellt von IBM WorkFrame/2 MakeMake um 0:19:38 am 16 Dez 2001
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

{E:\cvs\source\xwphelpers\include}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|fF.RES

{E:\cvs\source\xworkplace\include}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|fF.RES

{.}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|fF.RES

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) /Ie:\cvsroot\XWorkplace\include /Ie:\cvsroot\xwphelpers\include /I\work\c\log /I.. /Ss /Wcmpcndcnscnvdcleffgeniniparprorearet /Ge- /G5 /C %s

{.\include}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) /Ie:\cvsroot\XWorkplace\include /Ie:\cvsroot\xwphelpers\include /I\work\c\log /I.. /Ss /Wcmpcndcnscnvdcleffgeniniparprorearet /Ge- /G5 /C %s

{E:\cvs\source\xworkplace\include}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) /Ie:\cvsroot\XWorkplace\include /Ie:\cvsroot\xwphelpers\include /I\work\c\log /I.. /Ss /Wcmpcndcnscnvdcleffgeniniparprorearet /Ge- /G5 /C %s

{.}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe $(CDB) /Ie:\cvsroot\XWorkplace\include /Ie:\cvsroot\xwphelpers\include /I\work\c\log /I.. /Ss /Wcmpcndcnscnvdcleffgeniniparprorearet /Ge- /G5 /C %s

.\XWPmouse.dll: \
    .\XWPWidget.obj \
    .\XWPWidget.res \
    E:\cvsroot\CompileHelpers\lib\helpers.lib \
    {$(LIB)}XWPWidget.def
    @echo " Link::Linker "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /Q /B"$(LDB) /dbgpack /pmtype:pm     "
     /FeXWPmouse.dll $(LTR)
     E:\cvsroot\CompileHelpers\lib\helpers.lib
     XWPWidget.def
     somtk.lib
     .\XWPWidget.obj
<<
    rc.exe .\XWPWidget.res XWPmouse.dll

!include "makefile.DEP"

cleanall:
      @if exist *.obj del *.obj
      @if exist *.res del *.res
      @if exist *.dll del *.dll

copyall:
      @if exist XWPmouse.dll copy XWPmouse.dll Bundle

