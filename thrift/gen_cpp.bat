@echo off

rem ����c++����
call gen_code.bat cpp

rem rd /s /q "..\ArxSoUI\gen-cpp\"
rem md "..\ArxSoUI\gen-cpp\"

rem ����ͨ��IDL���ɵ�cpp����
rem xcopy "gen-cpp" "..\ArxSoUI\gen-cpp\"  /c /e /y

rem ����CbmClientHelper.h
copy /y SQLClientHelper.h "..\ArxSoUI\"
copy /y SQLClientHelper.cpp "..\ArxSoUI\"

rem ��ͣ
pause