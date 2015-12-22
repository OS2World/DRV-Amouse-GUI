<WARPIN VERSION="0.9" OS="OS2_4x">
  <HEAD>

    <TITLE>AMouse</TITLE>

    <REXX NAME="GetIBMMouseDriver">
      /* Due to a mistake in WarpIN, the ?: macro doesn't work with REMOVELINE */
      rc=rxFuncAdd('SysLoadFuncs','REXXUTIL','SysLoadFuncs')
      rc=SysLoadFuncs()

      irc=SysIni('BOTH','FolderWorkareaRunningObjects','ALL:','Objects')
      BootDrive=left(Objects.1,1)
      rc = "DEVICE="BootDrive":\OS2\BOOT\MOUSE.SYS"
      return rc
    </REXX>

    <REXX NAME="GetIBMUSBMouseDriver">
      /* Due to a mistake in WarpIN, the ?: macro doesn't work with REMOVELINE */
      rc=rxFuncAdd('SysLoadFuncs','REXXUTIL','SysLoadFuncs')
      rc=SysLoadFuncs()

      irc=SysIni('BOTH','FolderWorkareaRunningObjects','ALL:','Objects')
      BootDrive=left(Objects.1,1)
      rc = "DEVICE="BootDrive":\OS2\BOOT\USBMOUSE.SYS"
      return rc
    </REXX>

    <REXX NAME="GetLangPack">
      call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs'
      call SysLoadFuncs
      irc = SysIni('USER','PM_National','iCountry')
      pos = VERIFY(irc,'1234567890','N')
      IF pos > 0 THEN
        irc = SUBSTR(irc,1,pos-1)
      SELECT
        WHEN irc = '07' THEN
          rc = 7
        WHEN irc = '31' THEN
          rc = 9
        WHEN irc = '33' THEN
          rc = 3
        WHEN irc = '34' THEN
          rc = 8
        WHEN irc = '39' THEN
          rc = 4
        WHEN irc = '46' THEN
          rc = 5
        WHEN irc = '49' THEN
          rc = 6
        OTHERWISE
          rc = 2
      END
      return rc
    </REXX>

    <REXX NAME="GetLangCode">
      call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs'
      call SysLoadFuncs
      irc = SysIni('USER','PM_National','iCountry')
      pos = VERIFY(irc,'1234567890','N')
      IF pos > 0 THEN
        irc = SUBSTR(irc,1,pos-1)
      SELECT
        WHEN irc = '07' THEN
          rc = "readme.RUS"
        WHEN irc = '31' THEN
          rc = "readme.NLD"
        WHEN irc = '33' THEN
          rc = "readme.FRA"
        WHEN irc = '34' THEN
          rc = "readme.SPA"
        WHEN irc = '39' THEN
          rc = "readme.ITA"
        WHEN irc = '46' THEN
          rc = "readme.SWE"
        WHEN irc = '49' THEN
          rc = "readme.DEU"
        OTHERWISE
          rc = "readme.ENU"
      END

      return rc
    </REXX>

    <PCK INDEX=1
         PACKAGEID="nb software\AMouse\AMouse base\X\X\X"
         TITLE="AMouse - Advanced Wheel Mouse Driver"
         TARGET="?:\AMouse"
         BASE SELECT NODESELECT
         EXECUTE="REGISTERCLASS | $(1)\MOUCLASS REPLACE"
         EXECUTE="MOUSYDLL.EXE REGISTER NOSOUND"
         CONFIGSYS="DEVICE=$(1)\USBMOUSE.SYS | UNIQUE(\USBMOUSE.SYS) ADDAFTER(\USBMOUSE.SYS)"
         CONFIGSYS="=("GetIBMUSBMouseDriver") | REMOVELINE"
         CONFIGSYS="DEVICE=$(1)\AMOUSE.SYS | UNIQUE(\AMOUSE.SYS) ADDAFTER(\MOUSE.SYS)"
         CONFIGSYS="=("GetIBMMouseDriver") | REMOVELINE"
         CONFIGSYS="LIBPATH=$(1) | ADDRIGHT"
         CONFIGSYS="SET HELP=$(1) | ADDRIGHT"
         CLEARPROFILE="USER\AMouse"
         DEEXECUTE="$(1)\mouclass.exe DEREGISTER"
         >This package contains the AMouse base package.
    </PCK>
    <PCK INDEX=2
         PACKAGEID="nb software\AMouse\AMouse English Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT NODESELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; English Language Support"
         >This package contains the English language support for AMouse
    </PCK>
    <PCK INDEX=3
         PACKAGEID="nb software\AMouse\AMouse French Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; French Language Support"
         >This package contains the French language support for AMouse
    </PCK>
    <PCK INDEX=4
         PACKAGEID="nb software\AMouse\AMouse Italian Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; Italian Language Support"
         >This package contains the Italian language support for AMouse
    </PCK>
    <PCK INDEX=5
         PACKAGEID="nb software\AMouse\AMouse Swedish Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; Swedish Language Support"
         >This package contains the Swedish language support for AMouse
    </PCK>
    <PCK INDEX=6
         PACKAGEID="nb software\AMouse\AMouse German Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; German Language Support"
         >This package contains the German language support for AMouse
    </PCK>
    <PCK INDEX=7
         PACKAGEID="nb software\AMouse\AMouse Russian Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; Russian Language Support"
         >This package contains the Russian language support for AMouse
    </PCK>
    <PCK INDEX=8
         PACKAGEID="nb software\AMouse\AMouse Spanish Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; Spanish Language Support"
         >This package contains the Spanish language support for AMouse
    </PCK>
    <PCK INDEX=9
         PACKAGEID="nb software\AMouse\AMouse Dutch Language Support\2\80\03"
         TARGET="?:\AMouse"
         SELECT
         REQUIRES=1
         TITLE="AMouse - Advanced Wheel Mouse Driver; Dutch Language Support"
         >This package contains the Dutch language support for AMouse
    </PCK>
  </HEAD>
  <!-- Here come the different pages. They are linked by
       the <NEXTBUTTON> tags, which must have a target.
       Each page must have a TYPE= attribute, which tells
       WarpIn what will be visible on that page. -->
  <BODY>
    <!-- page 1: introductory page -->
    <PAGE INDEX=1 TYPE=README>
      <NEXTBUTTON TARGET=2>~Next</NEXTBUTTON>
      <TEXT>
        README
      </TEXT>
      <README EXTRACTFROMPCK="=("GetLangPack")" FORMAT=PLAIN>=("GetLangCode")</README>
    </PAGE>
    <!-- The TYPE=CONTAINER will list the packages which can be installed. -->
    <PAGE INDEX=2 TYPE=CONTAINER>
      <NEXTBUTTON TARGET=3>~Next</NEXTBUTTON>
      <TEXT>
      On this page, you may deselect the package if it is already installed or change the package's target path. </TEXT>
    </PAGE>
    <PAGE INDEX=3 TYPE=CONFIGURE>
      <NEXTBUTTON TARGET=4>~Next</NEXTBUTTON>
      <TEXT>Configuration page</TEXT>
    </PAGE>
    <!-- Display another TEXT page to inform the user
            that installation will begin. We use the TARGET=0
            with the NEXTBUTTON tag which starts installation. -->
    <PAGE INDEX=4 TYPE=TEXT>
      <NEXTBUTTON TARGET=0>I~nstall</NEXTBUTTON>
      <TEXT>
      Press "Install" to begin installing this archive.</TEXT>
    </PAGE>
  </BODY>
</WARPIN>
