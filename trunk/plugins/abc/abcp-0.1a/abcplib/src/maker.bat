@echo off

if not exist %1.re goto nofile
echo Creating %1.c from %1.re

::..\..\bin\
re2c -s %1.re >%1.c

echo %1.c created
echo.
goto done

:nofile
echo File "%1.re" not found

:done
