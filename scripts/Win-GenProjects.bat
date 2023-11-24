@echo off
pushd ..
call "vendor/premake5/bin/premake5.exe" vs2022
popd
pause