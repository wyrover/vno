# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_cbm_messagebox import *

# 消息对话框类型
class MsgBoxType:
	INFO = 0        # 提示
	QUESTION = 1    # 询问
	ERROR = 2       # 错误

class CbmMessageBox(BaseDialog):
	def __init__(self, parent=None):
		super(CbmMessageBox, self).__init__(parent)
		self.ui = Ui_cbm_messageBox()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setAttribute(Qt.Qt.WA_DeleteOnClose)
		self.ui.btnMenu_Close.clicked.connect(self.close)
		self.ui.btnCancel.clicked.connect(self.close)
		self.ui.btnOk.clicked.connect(self.onBtnOk)

	def onBtnOk(self):
		self.done(1)
		self.close()

	def mousePressEvent(self, event):
		if e.button() == QtCore.Qt.LeftButton:
			self.mousePressed = True
			self.mousePoint = e.globalPos() - self.pos()
			e.accept()
			
	def mouseReleaseEvent(self, event):
		self.mousePressed = False

	def mouseMoveEvent(self,e):
		if self.mousePressed and e.buttons() and QtCore.Qt.LeftButton:
			self.move(e.globalPos()-self.mousePoint)
			e.accept()

	def setMessage(self, msg, type):
		if type == 0:
			self.ui.labIcoMain.setStyleSheet("border-image: url(:/images/info.png);")
			self.ui.btnCancel.setVisible(False)
			self.ui.lab_Title.setText(u"提示")
		elif type == 1:
			self.ui.labIcoMain.setStyleSheet("border-image: url(:/images/question.png);")
			self.ui.lab_Title.setText(u"询问")
		elif type == 2:
			self.ui.labIcoMain.setStyleSheet("border-image: url(:/images/error.png);");
			self.ui.btnCancel.setVisible(False);
			self.ui.lab_Title.setText(u"警告");
		self.ui.labInfo.setText(msg);
