@echo off
setlocal enabledelayedexpansion

REM This script builds the C/C++ project using the GCC compiler.

REM Store the original code page
for /f "tokens=2 delims=:." %%i in ('chcp') do set "ORIGINAL_CODEPAGE=%%i"

REM Change the code page to UTF-8 (65001)
chcp 65001 >nul

REM Compiling resources
windres -F pe-i386 -i resources.rc -o resources.o
if %errorlevel% neq 0 (
    echo Resource compilation failed.
    pause
    exit /b 1
)

REM Save the original folder path
pushd "%~dp0\..\src" || (
    echo Please check the code path!
    pause
    exit /b 1
)

REM Perform the compilation. If you encounter any issues, feel free to ask using ISSUE.
gcc.exe -o ../bin/CursorRestrict.exe CursorRestrict.c ../build/resources.o -m32 -std=c11 -Werror -Wall -Wextra -Wcomment -Wwrite-strings -Wimplicit -Wreturn-type -Wshadow -Wcast-qual -Wpedantic -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-security -Wnull-dereference -Wstack-protector -Wtrampolines -Walloca -Wvla -Warray-bounds=2 -Wimplicit-fallthrough=3 -Wtraditional-conversion -Wshift-overflow=2 -Wstringop-overflow=4 -Wconversion -Warith-conversion -Wlogical-op -Wduplicated-cond -Wduplicated-branches -Wformat-signedness -Wstrict-overflow=4 -Wundef -Wstrict-prototypes -Wswitch-default -Wswitch-enum -Wstack-usage=1000000 -Wcast-align=strict -Wp,-DWIN32_LEAN_AND_MEAN,-D__USE_MINGW_ANSI_STDIO=0,-D_WIN32_WINNT=0x0601,-DWINVER=0x0601,-DSTRICT,-D_MSVCRT_ -Os -luser32 -nostartfiles -nostdlib -fanalyzer -finput-charset=utf-8 --freestanding -fno-ident -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fuse-linker-plugin -ffunction-sections -fmerge-all-constants -Wl,--subsystem,windows,-e,_c,--gc-sections,--disable-dynamicbase,--disable-reloc-section,--relax,-s,--exclude-all-symbols || (
    echo Compilation failed.
    pause
    popd
    chcp %ORIGINAL_CODEPAGE% >nul
    exit /b 1
)

REM Return to the original folder
popd || (
    echo If compilation is complete, ignore this message.
    pause
    exit /b 1
)

echo Success! CursorRestrict.exe has been generated under the bin folder.
pause

REM Restore the code page
chcp %ORIGINAL_CODEPAGE% >nul

exit /b 0
