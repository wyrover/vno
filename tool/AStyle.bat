REM bygreencn@gmail.com
REM ��������Ŀ¼�е�����C++�ļ���Astyle���д�����������
REM 2009-01-05
REM ����Astyle����λ�úͲ���
@echo off
set astyle=".\Astyle.exe"
REM ѭ������Ŀ¼
for /r .. %%a in (*.cpp;*.c) do %astyle% --style=allman -N -k1 -p -D  "%%a"
for /r .. %%a in (*.hpp;*.h) do %astyle% --style=allman -N -k1 -p -D  "%%a"
REM ɾ�����е�astyle�����ļ�
for /r .. %%a in (*.orig) do del "%%a"
pause