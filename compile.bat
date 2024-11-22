@echo off
:: Check if a variable is passed
if "%1"=="" (
    echo No PLATFORM specified. Using default: Win
    set PLATFORM=Win
) else (
    set PLATFORM=%1
)

cd build/ && mingw32-make PLATFORM=%PLATFORM% && cd .. && call Clean_v0.0.1.exe
pause

:: start compile.bat Win/Linux/Web
