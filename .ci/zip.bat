@echo off

cd bin/Release

for /d %%a in (*) do cd "%%~a"

for %%I IN (.) DO set CurrentD=%%~nI%%~xI

robocopy ../../../app/data ./ /E

7z a -tzip GameTrainer-%CurrentD%.zip .

cd ../../../
