@echo off
call premake5.exe vs2022
if %errorlevel% neq 0 pause