@echo off

rem ����php�ķ������Ҫ��server
rem gen_code.bat php:server

rem ����php�ͻ��˴���
call gen_code.bat php

rd /s /q "..\php\cbm\Thrift\"
rd /s /q "..\php\cbm\rpc\gen-php\"
md "..\php\cbm\Thrift\"
md "..\php\cbm\rpc\gen-php\"

rem ����thrift��phpģ��
xcopy "..\ThirdParty\thrift\php\Thrift"  "..\php\cbm\Thrift"  /c /e /y
rem ����ͨ��IDL���ɵ�php����
xcopy "gen-php" "..\php\cbm\rpc\gen-php\"  /c /e /y

rem ����sql.py
copy /y SQLClientHelper.php "..\php\cbm\rpc\"

rem ��ͣ
pause