@echo off

rem ����py����
call gen_code.bat py

rd /s /q "..\python\cbm\rpc\gen-py\"
rd /s /q "..\python\cbm\thrift\"
md "..\python\cbm\rpc\gen-py\"
md "..\python\cbm\thrift\"

rem ����thrift��pyģ��
xcopy "..\ThirdParty\thrift\py\thrift"  "..\python\cbm\Thrift\"  /c /e /y
rem ����ͨ��IDL���ɵ�py����
xcopy "gen-py" "..\python\cbm\rpc\gen-py\"  /c /e /y

rem ����sqlacodegen���ߣ���msyql���ݿ��ж�ȡ����Ϣ���Զ���������sqlalchemy��ʽ��py����
sqlacodegen mysql+pymysql://root:@localhost/cbm --outfile SQL.py

rem ����sql.py
copy /y SQL.py "..\python\cbm\rpc\"
copy /y SQLServerHelper.py "..\python\cbm\rpc\"
copy /y SQLClientHelper.py "..\python\cbm\rpc\"
copy /y CbmRtti.py "..\python\cbm\rpc\"

rem ��ͣ
pause