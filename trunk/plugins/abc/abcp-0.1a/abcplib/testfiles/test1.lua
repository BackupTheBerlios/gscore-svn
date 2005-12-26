ignore={}
ignore["T_ENDLINE"] =1
ignore["T_STARTLINE"] =1
ignore["T_FIELD"] =1
ignore["T_EXTFIELD"] =1

function abcHandler(sta, tok, str,file,ln, col)

  --print(sta,tok,str)
 
  if tok == "T_FIELDB" then
    if sta == "S_FIELD_T" then
      Title=Title .. " " .. str
    elseif sta == "S_FIELD_X" then
      Num=str
      Title=""
      Incipit=""
      Bars=0
    end
  elseif tok == "T_EMPTYLINE" or tok == "T_EOF" then
    if Num then
      if Title == "" then
         Title=" Untitled"
      end
      print(string.format("%4s -%s \n       %s",Num,Title,Incipit))
    end
    Num=nil
  elseif sta == "S_TUNE" and Bars < 5 and not ignore[tok] then
    if tok == "T_BAR" then
      if Incipit ~= "" then Bars = Bars+1 end
    end
    Incipit = Incipit .. str
  end 
  return 0;
end

