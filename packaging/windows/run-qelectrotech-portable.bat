@echo off
setlocal

set "QET_PORTABLE_ROOT=%~dp0"
set "PATH=%QET_PORTABLE_ROOT%;%PATH%"

start "" /D "%QET_PORTABLE_ROOT%" "%QET_PORTABLE_ROOT%qelectrotech.exe" "--common-elements-dir=%QET_PORTABLE_ROOT%elements" "--common-tbt-dir=%QET_PORTABLE_ROOT%titleblocks" "--lang-dir=%QET_PORTABLE_ROOT%lang" %*
