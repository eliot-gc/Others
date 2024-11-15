::©2024 Wizurth, tous droits réservés.
::Github link: https://github.com/Wizurth

set PROJECT_NAME=RugbyMatch
set DIRECTORY_PROJECT=lyo-t2-amiga-p3-11
set bCopySFMLDll=true
set bAutoOpenSLN=true

set bDebugMode=false

if not "%bDebugMode%" == "true" (
	@echo off
)


if /i "%bCopySFMLDll%" == "true" (
	xcopy /i /c /q /y "src\SFML*\bin\*-d.dll" "ide\vs\%PROJECT_NAME%\Build\Debug\"
	xcopy /i /c /q /y "src\SFML*\bin\*.dll" "ide\vs\%PROJECT_NAME%\Build\Release\"
)


"../SolutionGenerator.exe" -make ../%DIRECTORY_PROJECT%

if /i "%bAutoOpenSLN%" == "true" (
	start "" "ide/vs/%PROJECT_NAME%.sln"
)


if /i "%bDebugMode%" == "true" (
	echo.
	echo ======[DEBUG MODE]======
	echo PROJECT_NAME=%PROJECT_NAME%
	echo DIRECTORY_PROJECT=%DIRECTORY_PROJECT%
	echo bCopySFMLDll=%bCopySFMLDll%
	echo bAutoOpenSLN=%bAutoOpenSLN%
	echo ========================
	echo.

	pause
)