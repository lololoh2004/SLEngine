@echo off
:: works for EVERYONE

set "PATH=%~dp0bin;%PATH%"
start wt -d "%~dp0." "%~dp0sl_engine.exe" & exit
