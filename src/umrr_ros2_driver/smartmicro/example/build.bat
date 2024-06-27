@echo off
if "%1" == "" (
  GOTO HELP
) else if "%1" == "Release" (
  set libdir=lib-windows-x86_64-msvc_16
) else (
  echo Invalid build type %1
  GOTO HELP
)

echo Build example app!
echo build_type: %~1

mkdir build_dir
cmake -S . -A x64 -B build_dir -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE=windows-x86_64-msvc.cmake -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE -DCMAKE_SYSTEM_VERSION=10.0 -DSMART_ACCESS_LIB_FOLDER=../%libdir%
IF %ERRORLEVEL% NEQ 0 GOTO ERROR
cd build_dir
msbuild SmartAccessExample.sln /property:Configuration=%1 /property:Platform=x64 /m
IF %ERRORLEVEL% NEQ 0 GOTO ERROR

cd ..
mkdir out\bin
xcopy build_dir\%1\example_app.exe out\bin /Y
IF %ERRORLEVEL% NEQ 0 GOTO ERROR
xcopy ..\%libdir%\smart_access.dll out\bin /Y
IF %ERRORLEVEL% NEQ 0 GOTO ERROR
xcopy ..\%libdir%\com_lib.dll out\bin /Y
IF %ERRORLEVEL% NEQ 0 GOTO ERROR
xcopy ..\%libdir%\osal.dll out\bin /Y
IF %ERRORLEVEL% NEQ 0 GOTO ERROR
xcopy ..\%libdir%\basev1.0.2_user_interface.dll out\bin /Y
IF %ERRORLEVEL% NEQ 0 GOTO ERROR


:SUCCESS
echo SUCCESS!
ENDLOCAL
EXIT /B 0

:ERROR
echo FAILED!
ENDLOCAL
EXIT /B 1

:HELP
echo Usage:
echo build.bat Release
ENDLOCAL
EXIT /B 1
