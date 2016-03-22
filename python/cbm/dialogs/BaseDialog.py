# -*- coding: utf-8 -*-

# from IconHelper import *
from PyQt4 import QtGui,QtCore,Qt

CACL = '_cacl'

class BaseDialog(QtGui.QDialog):
	def __init__(self, parent=None):
		super(BaseDialog, self).__init__(parent)

	# 自定义ui风格(标题栏、窗体字体、背景透明、图标等)
	def initUi(self, ui):
		# 设置字体:雅黑 12号
		self.setStyleSheet(u"font: 12pt \"微软雅黑\";")
		# 去掉边框和关闭按钮
		self.setWindowFlags(Qt.Qt.WindowCloseButtonHint | Qt.Qt.FramelessWindowHint)
		# 设置窗口背景透明度
		self.setWindowOpacity(1)
		self.mousePressed = False
		# 使用自定义的关闭按钮(btnMenu_Close)
		closePix = self.style().standardPixmap(Qt.QStyle.SP_TitleBarCloseButton)
		ui.btnMenu_Close.setIcon(Qt.QIcon(closePix))
		# 设置窗口左上角的图标
		icoPix = QtGui.QPixmap(u":/images/cbm.ico")
		ui.lab_Ico.setPixmap(icoPix.scaled(Qt.QSize(31,33)))
		# icon1 = QtGui.QIcon()
		# icon1.addPixmap(QtGui.QPixmap(u":/images/close.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
		# ui.btnMenu_Close.setIcon(icon1)
		# instance().setIcon(ui.btnMenu_Close, QtCore.QString(QtCore.QChar(0xf00d)), 12)
		# instance().setIcon(ui.btnMenu_Close, u'\uf00d', 12)
		# 关闭按钮消息处理
		ui.btnMenu_Close.clicked.connect(self.close)
		# 窗口居中
		self.FormInCenter(self)
		# 窗口中的所有以_cacl结尾的按钮高亮的效果
		# 特殊处理(理论上不应该放在基类处理的,这里为了省事!!!)
		self.dealCaclBtn(ui)

	# 设置标题
	def setTitle(self, title):
		if hasattr(self.ui, 'lab_Title'):
			self.ui.lab_Title.setText(title)

	#窗体居中显示
	def FormInCenter(self, frm):
		frmX = frm.width()
		frmY = frm.height()
		w = QtGui.QDesktopWidget()
		deskWidth = w.width()
		deskHeight = w.height()
		movePoint = QtCore.QPoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
		frm.move(movePoint);

	# 处理3个mouse消息,模拟窗口拖拽效果
	def mousePressEvent(self,e):
		if e.button() == QtCore.Qt.LeftButton:
			self.mousePressed = True
			self.mousePoint = e.globalPos() - self.pos()
			e.accept()

	def mouseReleaseEvent(self,e):
		self.mousePressed = False

	def mouseMoveEvent(self,e):
		if self.mousePressed and e.buttons() and QtCore.Qt.LeftButton:
			self.move(e.globalPos()-self.mousePoint)
			e.accept()

	def dealCaclBtn(self,ui):
		for name,value in vars(ui).items():
			if name[-1*len(CACL):] == CACL and isinstance(value,Qt.QPushButton):
				value.setStyleSheet("QPushButton{background: none;}\
									QPushButton:hover{\
									border-color: #C8C8FF;\
									border-width: 1px;\
                                    border-style: solid;}")