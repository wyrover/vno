#-*- coding:utf-8 -*-

# 问    题："iccp known incorrect srgb profile" 警告的去除
# 解决办法: http://www.tuicool.com/articles/j22Yvef
# 注    意: 如果png文件名有空格 或者文件路径上有空格,要想办法去掉(比如复制到其他地方处理后,再复制回来),否则会报错!!!
import os

# imageMagick的安装路径
CMD = r'"C:\Program Files\ImageMagick-6.9.2-Q16\convert.exe"'
SOURCE_PATH = r'.'

def doStrip(path):
  data = {};
  print(path)
  for root, dirs, files in os.walk(path):
    for file in files:
      name = file.lower();
      if name.find('.png') != -1:
      	# 路径上不能有空格,否则会错误
      	# 文件名也不能有空格
        path = os.path.join(root, file)
        os.system('{0} {1} -strip {1}'.format(CMD, path, path))
        print '{0} {1} -strip {1}'.format(CMD, path, path)


doStrip(SOURCE_PATH)