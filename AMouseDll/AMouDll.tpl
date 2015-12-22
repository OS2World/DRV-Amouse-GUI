LIBRARY AMOUDLL INITINSTANCE TERMINSTANCE

PROTMODE

DESCRIPTION   '@#NB:X.XX.XX#@ AMouse wheel lib (c) nb-software 2001...2007'

DATA MULTIPLE NONSHARED READWRITE LOADONCALL

CODE LOADONCALL

SEGMENTS
   GLOBAL_SEG CLASS 'DATA' SHARED

IMPORTS
   DosQuerySysState = DOSCALLS.368
   Win16DefDlgProc  = PMMERGE.2095

EXPORTS
   _PM_Init                    @1
   ManualCall                  @3
   WinRegisterForWheelMsg      @4
   WinSetMasterVolume          @5

