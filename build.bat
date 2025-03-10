@echo off

echo Exécution de cmake --preset debug-windows...
cmake --preset debug-windows
if errorlevel 1 (
    echo Erreur lors de l'exécution de cmake --preset debug-windows.
    pause
    exit /b 1
)

echo Construction du projet...
cmake --build build\debug-windows\ --target ALL_BUILD
if errorlevel 1 (
    echo Erreur lors de la construction du projet.
    pause
    exit /b 1
)

set SOURCE=build\debug-windows\vcpkg_installed\x64-windows\bin
set DEST=build\debug-windows\bin\Debug

if not exist "%SOURCE%" (
    echo Le dossier source "%SOURCE%" n'existe pas.
    pause
    exit /b 1
)

if not exist "%DEST%" (
    echo Le dossier destination "%DEST%" n'existe pas. Création du dossier...
    mkdir "%DEST%"
)

set FILES=libpng16.dll SDL2.dll SDL2_image.dll SDL2_ttf.dll SDL2_ttf.dll SDL2d.dll zlib1.dll brotlicommon.dll brotlidec.dll bz2.dll freetype.dll

for %%F in (%FILES%) do (
    if exist "%SOURCE%\%%F" (
        echo Copie de %%F...
        copy "%SOURCE%\%%F" "%DEST%"
    ) else (
        echo Le fichier %%F est introuvable dans "%SOURCE%".
    )
)

echo Copie terminée.
pause
exit /b 0
