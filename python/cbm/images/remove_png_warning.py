#-*- coding:utf-8 -*-

# ��    �⣺"iccp known incorrect srgb profile" �����ȥ��
# ����취: http://www.tuicool.com/articles/j22Yvef
# ע    ��: ���png�ļ����пո� �����ļ�·�����пո�,Ҫ��취ȥ��(���縴�Ƶ������ط������,�ٸ��ƻ���),����ᱨ��!!!
import os

# imageMagick�İ�װ·��
CMD = r'"C:\Program Files\ImageMagick-6.9.2-Q16\convert.exe"'
SOURCE_PATH = r'.'

def doStrip(path):
  data = {};
  print(path)
  for root, dirs, files in os.walk(path):
    for file in files:
      name = file.lower();
      if name.find('.png') != -1:
      	# ·���ϲ����пո�,��������
      	# �ļ���Ҳ�����пո�
        path = os.path.join(root, file)
        os.system('{0} {1} -strip {1}'.format(CMD, path, path))
        print '{0} {1} -strip {1}'.format(CMD, path, path)


doStrip(SOURCE_PATH)