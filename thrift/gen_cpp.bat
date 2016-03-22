@echo off

rem 生成c++代码
call gen_code.bat cpp

rem rd /s /q "..\ArxSoUI\gen-cpp\"
rem md "..\ArxSoUI\gen-cpp\"

rem 复制通过IDL生成的cpp代码
rem xcopy "gen-cpp" "..\ArxSoUI\gen-cpp\"  /c /e /y

rem 复制CbmClientHelper.h
copy /y SQLClientHelper.h "..\ArxSoUI\"
copy /y SQLClientHelper.cpp "..\ArxSoUI\"

rem 暂停
pause