@echo off
FOR %%F IN (*.SAVERAM) DO (
  set filename=%%F
  goto run
)
FOR %%F IN (*.mcr) DO (
  set filename=%%F
  goto run
)
FOR %%F IN (*.gme) DO (
  set filename=%%F
  goto run
)
echo Unable to find any .SAVERAM, .mcr, or .gme files in this directory
pause
exit \b
:run
  echo Using "%filename%"
  librarian.exe "%filename%" cards.txt
pause
