@echo off
@del .\app\app_sign.ksp
@.\KPackage.exe -ksp 		.\app_r.ini

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
