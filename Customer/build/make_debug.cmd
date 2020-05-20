@call del  .\app\SecondApp.img

cd ../../../../
@call Build_SecondAppDebug.bat
cp .\Build\SecondApp\Debug\img\SecondApp.img  .\Source\SecondApp\Customer\build\app\SecondApp.img

cd .\Source\SecondApp\Customer\build

@Build_kspDebug.cmd
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

@call fastboot fileSystem push app\app_sign.ksp e:\appup.ksp
@call fastboot reset
