@echo off

set CBM_ROOT=..\..\..
set DEST_DIR=".\"

copy /y %CBM_ROOT%\x64\debug\*.exe %DEST_DIR%
copy /y %CBM_ROOT%\x64\debug\*.arx %DEST_DIR%
copy /y %CBM_ROOT%\x64\debug\*.dll %DEST_DIR%

rem 复制必须的exe
copy /y %CBM_ROOT%\tool\pdf.exe %DEST_DIR%
copy /y %CBM_ROOT%\tool\ImageView.exe %DEST_DIR%

rem 复制boost dll
copy /y %CBM_ROOT%\ThirdParty\boost\lib\x64\boost_chrono-vc90-mt-1_58.dll %DEST_DIR%
copy /y %CBM_ROOT%\ThirdParty\boost\lib\x64\boost_system-vc90-mt-1_58.dll %DEST_DIR%
copy /y %CBM_ROOT%\ThirdParty\boost\lib\x64\boost_thread-vc90-mt-1_58.dll %DEST_DIR%

rem soui的资源dll
copy /y %CBM_ROOT%\ThirdParty\soui\bin64\soui-sys-resource.dll %DEST_DIR%

pause