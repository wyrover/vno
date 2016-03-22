# -*- coding:utf-8 -*-

import os
import sys
from pyplusplus import module_builder

mb = module_builder.module_builder_t(
         files=['chg.h'], #要需要封装的头文件
         gccxml_path='C:\\Anaconda2\\gccxml')

# import 语句搜索文件时,文件名是大小写敏感的
# 即使在文件系统大小写不敏感的系统上也是如此(Windows等)
# import foo 只会导入文件foo.py而不会是FOO.PY
mb.build_code_creator( module_name='PyArx' ) #要生成的python模块的名称

mb.code_creator.user_defined_directories.append( os.path.abspath('.') )

mb.write_module( os.path.join( os.path.abspath('.'), 'chg_py.cpp' ) ) #要生成的boost.python封装好的代码文件的名称