# -*- coding:utf-8 -*-

import os
import sys
from pyplusplus import module_builder

mb = module_builder.module_builder_t(
         files=['chg.h'], #Ҫ��Ҫ��װ��ͷ�ļ�
         gccxml_path='C:\\Anaconda2\\gccxml')

# import ��������ļ�ʱ,�ļ����Ǵ�Сд���е�
# ��ʹ���ļ�ϵͳ��Сд�����е�ϵͳ��Ҳ�����(Windows��)
# import foo ֻ�ᵼ���ļ�foo.py��������FOO.PY
mb.build_code_creator( module_name='PyArx' ) #Ҫ���ɵ�pythonģ�������

mb.code_creator.user_defined_directories.append( os.path.abspath('.') )

mb.write_module( os.path.join( os.path.abspath('.'), 'chg_py.cpp' ) ) #Ҫ���ɵ�boost.python��װ�õĴ����ļ�������