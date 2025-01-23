cls
color 0f

rem [Constants]
set INSTALL=_Install_
set ROOT_FILES=%INSTALL%\Root
set MOD_FILES=%INSTALL%\Mods

cd /D "%~dp0.."

rem [Clean garbage files and folders]
del /F /Q *.txt
del /F /Q *.doc
del /F /Q *.hlp
del /F /Q *.cnt
del /F /Q *.pdf
del /F /Q *.bat
del /F /Q *.isu
del /F /Q *.reg
del /F /Q *.ini
del /F /Q mplaynow.exe
del /F /Q regsetup.exe
rmdir /S /Q Data\s
rmdir /S /Q Heat
rmdir /S /Q mplayer
rmdir /S /Q online
rmdir /S /Q registersod

rem [Move Era root files to game root and remove installation directory]
move /Y %INSTALL%\* .
rmdir /S /Q %INSTALL%

rem [Delete installer script for safety]
del "%~f0"