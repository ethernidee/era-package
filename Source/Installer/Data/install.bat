cls
color 0f

rem [Constants]
set ROOT_FILES=.\_ROOT_

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

rem [Normalize file and directory names]
rename random_maps Random_Maps
rename MP3 Mp3
rename games Games
rename MP3DEC.ASI mp3dec.asi
rename MSS32.DLL mss32.dll

rem [Move Era root files to game root and remove installation directory]
move /Y "%ROOT_FILES%\*.*" .
rmdir /S /Q "%ROOT_FILES%"

rem [Delete installer script for safety]
del "%~f0"