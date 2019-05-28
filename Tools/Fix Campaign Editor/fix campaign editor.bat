@echo off
cls
color 0f
title Fix campaign editor by importing text files from WoG into h3bitmap.lod
color 0c

cd "%~dp0..\.."

echo WARNING! This operation will not allow to uninstall Era completely!
echo Are you sure you want to continue (y/n)?
set /P Answer=
if not %Answer%==y goto Exit
color 0f
echo.
echo Merging files, please wait...
echo.

Tools\lodmerge.exe Data\h3bitmap.lod "%~dp0fix campaign editor.lod"

:Exit
pause