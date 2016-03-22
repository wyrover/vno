REM bygreencn@gmail.com
REM 批量将本目录中的所有C++文件用Astyle进行代码美化操作
REM 2009-01-05
REM 设置Astyle命令位置和参数
@echo off
set astyle=".\Astyle.exe"
REM 循环遍历目录
for /r .. %%a in (*.cpp;*.c) do %astyle% --style=allman -N -k1 -p -D  "%%a"
for /r .. %%a in (*.hpp;*.h) do %astyle% --style=allman -N -k1 -p -D  "%%a"
REM 删除所有的astyle生成文件
for /r .. %%a in (*.orig) do del "%%a"
pause