/* Create help files */

say 'Language is US'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou001.scr AMou001.ipf'
'ipfc -D:001 AMou001.ipf'
if RC > 0 then do
  return RC
end
say '--------------------------------------------------------------------------'

say 'Language is RU'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou007.scr AMou007.ipf'
'ipfc -D:007 AMou007.ipf'
if RC > 0 then do
  return RC
end
say '--------------------------------------------------------------------------'

say 'Language is NL'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou031.scr AMou031.ipf'
'ipfc -D:031 AMou031.ipf'
if RC > 0 then do
  return RC
end
say '--------------------------------------------------------------------------'

say 'Language is FR'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou033.scr AMou033.ipf'
'ipfc -D:033 AMou033.ipf'
if RC > 0 then do
  return RC
end
say '--------------------------------------------------------------------------'

say 'Language is SP'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou034.scr AMou034.ipf'
'ipfc -D:034 AMou034.ipf'
if RC > 0 then do
  return RC
end
say '--------------------------------------------------------------------------'

say 'Language is IT'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou039.scr AMou039.ipf'
'ipfc -D:039 AMou039.ipf'
if RC > 0 then do
  return RC
end
say '--------------------------------------------------------------------------'

say 'Language is SV'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou046.scr AMou046.ipf'
'ipfc -D:046 AMou046.ipf'
if RC > 0 then do
  return RC
end
say '--------------------------------------------------------------------------'

say 'Language is GR'
'l:\devtools\ipfcpp\ipfcprep -i ..\.. AMou049.scr AMou049.ipf'
'ipfc -D:049 AMou049.ipf'
if RC > 0 then do
  return RC
end

return 0
