@echo off

rem 生成py代码
call gen_code.bat py

rd /s /q "..\python\cbm\rpc\gen-py\"
rd /s /q "..\python\cbm\thrift\"
md "..\python\cbm\rpc\gen-py\"
md "..\python\cbm\thrift\"

rem 复制thrift的py模块
xcopy "..\ThirdParty\thrift\py\thrift"  "..\python\cbm\Thrift\"  /c /e /y
rem 复制通过IDL生成的py代码
xcopy "gen-py" "..\python\cbm\rpc\gen-py\"  /c /e /y

rem 利用sqlacodegen工具，从msyql数据库中读取表信息，自动生成满足sqlalchemy格式的py代码
sqlacodegen mysql+pymysql://root:@localhost/cbm --outfile SQL.py

rem 复制sql.py
copy /y SQL.py "..\python\cbm\rpc\"
copy /y SQLServerHelper.py "..\python\cbm\rpc\"
copy /y SQLClientHelper.py "..\python\cbm\rpc\"
copy /y CbmRtti.py "..\python\cbm\rpc\"

rem 暂停
pause