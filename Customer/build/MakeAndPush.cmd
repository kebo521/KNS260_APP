cd ../../../../
@call Build_SecondAppDebug.bat

cd ./Source/SecondApp/Customer/build
@call Build_kspDebug.cmd
@call pushAPP.cmd
@call fastboot reset

