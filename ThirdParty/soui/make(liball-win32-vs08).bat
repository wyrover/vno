rem LIB_ALL ����ģ�������LIB��
rem USING_MT ָʾ������Ŀʹ��MT��ʽ����CRT
rem CAN_DEBUG ָʾΪ���ɵ�Release�汾�������Է���
call "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat" x86
rem tools\qmake -tp vc -r -spec .\tools\mkspecs\win32-msvc2008 "CONFIG += USING_MT CAN_DEBUG LIB_ALL"
tools\qmake -tp vc -r -spec .\tools\mkspecs\win32-msvc2008 "CONFIG += CAN_DEBUG LIB_ALL"
rem soui.sln