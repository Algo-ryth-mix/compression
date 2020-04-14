@echo off

echo performing lzma tests
pushd out
cmake -G"Visual Studio 16 2019" -Ax64 -DZIP_T=OFF ..
cmake --build . --config Release
xcopy src\Release\testjig.exe ..\testing /Y
popd
pushd testing
call auto-test
if not exist "../results.lzma" (
    cd ..
    mkdir results.lzma
    cd testing
)
robocopy . ../results.lzma/
del /Q /F /S "*.txt"
del /Q /F /S "*.xz"
popd testing

echo performing zip tests
pushd out
cmake -G"Visual Studio 16 2019" -Ax64 -DZIP_T=ON ..
cmake --build . --config Release
xcopy src\Release\testjig.exe ..\testing /Y
popd
pushd testing
call auto-test
if not exist "../results.zip" (
    cd ..
    mkdir results.zip
    cd testing
)
robocopy . ../results.zip/
del /Q /F /S "*.txt"
del /Q /F /S "*.xz"
popd testing