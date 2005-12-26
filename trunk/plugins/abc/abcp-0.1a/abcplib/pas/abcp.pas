unit abcp;
interface

function abcScanFile(filename: PChar; handler : pointer) : integer;
  cdecl; external 'abcp.dll' name '_abcScanFile';
function abcScanString(buffer: PChar; handler : pointer) : integer;
  cdecl; external 'abcp.dll' name '_abcScanString';
function abcToken(s: Pointer): integer;
  cdecl; external 'abcp.dll' name '_abcToken';
function abcTokenName(n: integer) : Pchar;
  cdecl; external 'abcp.dll' name '_abcTokenName';
function abcState(s: Pointer): integer;
  cdecl; external 'abcp.dll' name '_abcState';
function abcStateName(s: integer): Pchar;
  cdecl; external 'abcp.dll' name '_abcStateName';
function abcString(s: Pointer): PChar;
  cdecl; external 'abcp.dll' name '_abcString';
function abcFilename(s: Pointer): PChar;
  cdecl; external 'abcp.dll' name '_abcFilename';
function abcLine(s: Pointer): integer;
  cdecl; external 'abcp.dll' name '_abcLine';
function abcColumn(s: Pointer): integer;
  cdecl; external 'abcp.dll' name '_abcColumn';

  implementation
end.
