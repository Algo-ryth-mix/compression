@echo off


pushd out
cmake -G"Visual Studio 16 2019" -Ax64 ..
cmake --build . --config Release
xcopy src\Release\testjig.exe ..\testing
popd
