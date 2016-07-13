ECHO OFF
CLS

IF NOT EXIST bin (mkdir bin)

ECHO Make directory structure
CD bin
IF NOT EXIST release (mkdir release)
CD ..

ECHO Copy data files

XCOPY data bin\release\data\ /Y /E

ECHO Copy run.bat

COPY run.bat bin\release\ /Y

CD tcc

SET /A tcc_errors = 0

IF %ERRORLEVEL% == 0 (
ECHO [main]
ECHO   -release.exe
tcc -luser32 -lws2_32 -o ../bin/release/release.exe ../main.c ../console/color.c ../console/cons.c ../network/ysock.c ../network/nwking.c ../network/packet.c ../menu/menu.c ../lib/lib.c ../lib/list.c ../game/item.c ../game/map.c
SET /A tcc_errors = %tcc_errors% + %ERRORLEVEL%
)

IF NOT %ERRORLEVEL% == 0 (
ECHO %ERRORLEVEL% Errors occured.
)ELSE (ECHO Done.)

PAUSE