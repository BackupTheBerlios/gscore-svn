@echo off

if not exist conf\%1.cfg goto nocfg

copy conf\%1.cfg+conf\perfect.mkf perfect\Makefile
copy conf\%1.cfg+conf\src.mkf src\Makefile

echo Done!
goto done

:nocfg
echo ABCp - Configuration script
echo Known configurations:
echo  - lcc

:done