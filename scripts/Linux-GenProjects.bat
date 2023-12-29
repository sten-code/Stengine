@echo off
pushd ..
call "vendor/premake/bin/premake5.exe" gmake
popd
pause