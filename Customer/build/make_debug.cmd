@call del  .\app\SecondApp.img

cd ../../../../
@call Build_SecondAppDebug.bat
cp .\Build\SecondApp\Debug\img\SecondApp.img  .\Source\SecondApp\Customer\build\app\SecondApp.img

cd .\Source\SecondApp\Customer\build

@Build_kspDebug.cmd
% ��������ʾ������app_sign.ksp�ļ����жϳɹ� %
set file_app_sign = .\app\app_sign.ksp
echo.
if exist %file_app_sign % (
    dir .\app\*.ksp /b
    echo **** ����ɹ� ****
    timeout /t 10
) else (
    echo **** ���ʧ�� ****
    pause
)

@call fastboot fileSystem push app\app_sign.ksp e:\appup.ksp
@call fastboot reset
