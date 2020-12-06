@ECHO off & title=dbj runner
@SETLOCAL
@GOTO:BEGIN

(C) 2020 by dbj@dbj.org  https://dbj.org/license_dbj 

 "%~N" is to remove quotes arround param N, where N = [1 .. 8]
 special note: in windows if path contains space or `&` it must be double quoted string

optionaly first we show how we will use args to build a command
over there
we decide where we leave the arg as it is 
where we remove d.quotes
or where we add d.quotes

:BEGIN
REM GOTO:COMPILE  & REM when ready

@ECHO 1 = [%1]    & REM compiler full path in double quotes
@ECHO 2 = [%~2]   & REM argument sets is passed as a single string literal
@ECHO 3 = [%~3]   & REM files to be compiled also passed as a single string literal
@ECHO 4 = [%4]    & REM /o "full path with possible spaces\\exename.exe"
@ECHO 5 = [%~5]   & REM /link and the rest
@ECHO 6 = [%6]
@ECHO 7 = [%7]
@ECHO 8 = [%8]

:: GOTO:eof

:COMPILE
:: be sure to match the quotes expansions or not expansions 
:: as you have researched them above
@echo on
%1 %~2 %~3 %4 %~5

