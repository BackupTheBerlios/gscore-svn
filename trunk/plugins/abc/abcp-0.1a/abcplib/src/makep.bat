@echo off

if not exist %1.c goto nofile
echo Creating %1.h from %1.c

cd ..\perfect
make

if not exist ..\src\lookupa.obj copy lookupa.obj ..\src

hlist < ..\src\%1.c | perfect -mn

del hhlist.*
make hhlist

type phash.c  > ..\src\%1.h

echo static ub4 codes[]={ >> ..\src\%1.h

hhlist < ..\src\%1.c | sort >> ..\src\%1.h

echo /*      */ 0x00000000 }; >> ..\src\%1.h

echo #define code(s) codes[phash(s,strlen(s))] >> ..\src\%1.h

cd ..\src
echo %1.h created
echo.

goto done

:nofile
echo File "%1.c" not found

:done
