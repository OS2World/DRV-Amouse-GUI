/* Create help files                        */
/* Syntax: makehlp <country-code> <country> */
/*   country-code := nnn                    */
/*   country      := XX                     */
parse arg langN lang2
if langN='' then do
  say 'missing argument: contry code'
  return 1
end

if lang2='' then do
  say 'missing argument: country'
  return 1
end

say 'Language is 'lang2
'ipfc -D:'langN 'XAMou'langN'.ipf'
if RC > 0 then do
  return RC
end

return 0
