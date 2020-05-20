@call del  .\app\SecondApp.img

cd ../../../../
@call Build_SecondApp.bat
cp .\Build\SecondApp\Release\img\SecondApp.img  .\Source\SecondApp\Customer\build\app\SecondApp.img
