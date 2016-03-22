@echo off

rem 生成php的服务端需要加server
rem gen_code.bat php:server

rem 生成php客户端代码
call gen_code.bat php

rd /s /q "..\php\cbm\Thrift\"
rd /s /q "..\php\cbm\rpc\gen-php\"
md "..\php\cbm\Thrift\"
md "..\php\cbm\rpc\gen-php\"

rem 复制thrift的php模块
xcopy "..\ThirdParty\thrift\php\Thrift"  "..\php\cbm\Thrift"  /c /e /y
rem 复制通过IDL生成的php代码
xcopy "gen-php" "..\php\cbm\rpc\gen-php\"  /c /e /y

rem 复制sql.py
copy /y SQLClientHelper.php "..\php\cbm\rpc\"

rem 暂停
pause