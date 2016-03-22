# -*- coding: utf-8 -*-

from PyQt4 import QtGui, QtCore, Qt

class IconHelper:
	def __init__(self):
		fontId = Qt.QFontDatabase.addApplicationFont(u":/images/fontawesome-webfont.ttf")
		fontName = Qt.QFontDatabase.applicationFontFamilies(fontId)[0]
		self.iconFont = Qt.QFont(fontName)

	def setIcon(self,obj,c,size = 10):
		self.iconFont.setPointSize(size)
		obj.setFont(self.iconFont)
		obj.setText(c)

# 单件模式
def instance():
	global inst
	mutex = Qt.QMutex()
	try:
		inst
	except:
		locker = Qt.QMutexLocker(mutex)
		inst = IconHelper()
	return inst
