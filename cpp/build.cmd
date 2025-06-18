@ECHO OFF
SETLOCAL EnableExtensions
SET PROGRAM_NAME=tool

FOR /D %%d IN ("%ProgramFiles%\Microsoft Visual Studio\2022\*") DO (
    SET "VS_DIR=%%~fd"
    GOTO :BREAK
)
:BREAK

IF "%VS_DIR%" EQU "" (
    ECHO.Could not find Visual Studio 2022
    EXIT /B 1
)
ECHO.Using Visual Studio at
ECHO.  %VS_DIR%

SET "VSDEV_CMD=%VS_DIR%\Common7\Tools\VsDevCmd.bat"
IF NOT EXIST "%VSDEV_CMD%" (
    ECHO.Could not find Visual Studio Command Prompt
    EXIT /B 1
)

ECHO.
ECHO.Loading Visual Studio development environment
ECHO.  %VSDEV_CMD%
CALL "%VSDEV_CMD%" -arch=amd64 -host_arch=amd64 -no_logo
IF %ERRORLEVEL% NEQ 0 (
    EXIT /B 1
)

ECHO.
PUSHD "%~dp0"
IF NOT EXIST obj\ MKDIR obj
IF NOT EXIST bin\ MKDIR bin
ECHO.Building program with Visual C Compiler
ECHO.
CL /EHsc /std:c++20 /O1 /Os /nologo /Fo.\obj\ /Fe".\bin\%PROGRAM_NAME%.exe" ".\src\%PROGRAM_NAME%.cpp"
SET RESULT=%ERRORLEVEL%
POPD

EXIT /B %RESULT%
