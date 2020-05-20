@echo off
@.\PrepKS68.exe  F .\parhead.txt     .\tmp.h     .\par.bin
@.\PrepKS68.exe  F .\par.txt      .\par.h     .\tmp.bin
@.\convpar.exe  .\par.bin
@del .\tmp.h
@del .\debug.txt
@del .\par_res.c
@del .\par_res.h

@..\..\DownLoad\tools\KPackage.exe -ksp 	.\TermPar.ini
@copy ..\par\TermPar.ksp         	..\..\DownLoad\target\TermPar.ksp
dir
pause