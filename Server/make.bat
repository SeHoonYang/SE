ECHO OFF
CLS

IF NOT EXIST bin (mkdir bin)

ECHO Make directory structure
CD bin
IF NOT EXIST release (mkdir release)
CD ..

ECHO Copy data files

XCOPY data bin\release\data\ /Y /E

REM ECHO Create object files

CD tcc

SET /A tcc_errors = 0

IF %ERRORLEVEL% == 0 (
ECHO [main]
ECHO   -release.exe
tcc -lws2_32 -o ../bin/release/release.exe ../main.c ../usr/usr.c ../network/ysock.c ../network/packet.c ../game/map_data.c ../lib/list.c ../lib/lib.c ../game/map.c ../game/mob.c
SET /A tcc_errors = %tcc_errors% + %ERRORLEVEL%
)

IF NOT %ERRORLEVEL% == 0 (
ECHO %ERRORLEVEL% Errors occured.
)ELSE (ECHO Done.)

CD ..
CD bin\release\data
IF NOT EXIST userdata (mkdir userdata)

PAUSE
