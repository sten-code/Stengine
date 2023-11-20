@echo off
pushd ..
call premake5.exe vs2022
popd
if %errorlevel% neq 0 pause