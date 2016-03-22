#-*- coding:utf-8 -*-

import codecs

def ReadFile(filePath,encoding="utf-8"):
	with codecs.open(filePath,"r",encoding) as f:
		return f.read()


def WriteFile(filePath,u,encoding="gbk"):
	with codecs.open(filePath,"w") as f:
		f.write(u.encode(encoding,errors="ignore"))

def UTF8_2_GBK(src, dst):
	content = ReadFile(src,encoding="utf-8")
	WriteFile(dst,content,encoding="gb18030")