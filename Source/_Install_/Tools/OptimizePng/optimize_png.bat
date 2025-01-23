@echo off
rem Pass directory path as the only argument to batch file, otherwise current working directory will be used

rem Replace OPTI_PNG_PATH value with fixed absolute path if the utility is not in bat file directory
set OPTI_PNG_PATH=%~dp0optipng.exe
set PNG_DIR=%~1

if "%PNG_DIR%."=="." set PNG_DIR=%CD%
if "%PNG_DIR%."=="" set PNG_DIR=%CD%

echo PNG files directory: "%PNG_DIR%"

for /R "%PNG_DIR%" %%i in ("*.png") do "%OPTI_PNG_PATH%" "%%i"
pause
exit