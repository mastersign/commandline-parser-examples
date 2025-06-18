@ECHO OFF
SETLOCAL

SET PROGRAM_NAME=tool

IF "%JAVA_HOME%" EQU "" (
    ECHO.JDK not found. Expected environment variable JAVA_HOME.
    EXIT /B 1
)
ECHO.Using JDK at
ECHO.  %JAVA_HOME%
ECHO.

PUSHD "%~dp0"

ECHO.Compiling Java classes with javac
ECHO.
IF NOT EXIST classes\ MKDIR classes
"%JAVA_HOME%\bin\javac.exe" -d classes src\*.java
SET RESULT=%ERRORLEVEL%
IF %RESULT% NEQ 0 GOTO :ERR

ECHO.Creating JAR file
ECHO.
IF NOT EXIST bin\ MKDIR bin
ECHO.  - Tool
"%JAVA_HOME%\bin\jar.exe" --create --file="bin\%PROGRAM_NAME%.jar" --main-class=Tool -C classes Tool.class
SET RESULT=%ERRORLEVEL%
IF %RESULT% NEQ 0 GOTO :ERR
FOR %%f IN ("classes\*.class") DO (
    IF %%~nf NEQ Tool (
        ECHO.  - %%~nf
        "%JAVA_HOME%\bin\jar.exe" --update --file="bin\%PROGRAM_NAME%.jar" -C classes "%%~nxf"
        SET RESULT=%ERRORLEVEL%
        IF %RESULT% NEQ 0 GOTO :ERR
    )
)

:ERR
POPD
EXIT /B %RESULT%
