@echo off
setlocal

set "QET_ROOT=C:\Users\jeykc\Documentos\GitHub\qelectrotech-source-mirror"
set "QET_BUILD=%QET_ROOT%\build\jw-qet-qt5-nokf"

set "PATH=%QET_BUILD%;C:\msys64\ucrt64\bin;%PATH%"

start "" /D "%QET_ROOT%" "%QET_BUILD%\qelectrotech.exe" "--common-elements-dir=%QET_ROOT%\elements" "--common-tbt-dir=%QET_ROOT%\titleblocks" "--lang-dir=%QET_ROOT%\lang" %*
