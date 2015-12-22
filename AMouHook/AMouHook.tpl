LIBRARY AMOUHOOK INITINSTANCE TERMINSTANCE

DESCRIPTION   '@#NB:X.XX.XX#@ AMouse hook lib (c) nb-software 2001...2007'

DATA MULTIPLE NONSHARED READWRITE LOADONCALL

CODE LOADONCALL

SEGMENTS
   GLOBAL_SEG CLASS 'DATA' SHARED

PROTMODE

EXPORTS
   initHookDLL                 @2
   insertHooks                 @3
   releaseHooks                @4
   inputHookProc               @5
   msgInputHookProc            @6
   destroyWindowHookProc       @7
   addWindowHandle             @10
   findWindowHandle            @11
   removeWindowHandle          @12
