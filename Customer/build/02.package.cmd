@echo off
@del .\app\app_sign.ksp
@.\KPackage.exe -ksp 		.\app_r.ini

% 打包结果提示，存在app_sign.ksp文件则判断成功 %
set file_app_sign = .\app\app_sign.ksp
echo.
if exist %file_app_sign % (
    dir .\app\*.ksp /b
    echo **** 打包成功 ****
    timeout /t 10
) else (
    echo **** 打包失败 ****
    pause
)
