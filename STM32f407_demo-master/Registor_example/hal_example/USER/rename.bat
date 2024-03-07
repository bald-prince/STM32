echo off
cls
echo *********工程重命名***********
echo 请输入工程名
set /p pj_name=
rename example* %pj_name%.*