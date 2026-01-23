@echo off
set PATH=C:\Qt\Tools\mingw1310_64\bin;%PATH%
cd /d "C:\Users\Marco Nie\Library\boost_1_84_0"

echo Building Boost Build engine (b2.exe)...
if exist b2.exe del b2.exe
call bootstrap.bat gcc

echo Building Boost with Qt MinGW...
b2.exe toolset=gcc variant=release link=static threading=multi runtime-link=shared address-model=64 threadapi=pthread --with-filesystem --with-regex stage
pause
