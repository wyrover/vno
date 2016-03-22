# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_name_dlg import *

class NameDlg(BaseDialog):
	def __init__(self,parent=None):
		super(NameDlg, self).__init__(parent)
		self.ui = Ui_name_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.name = u'' # 外部传入的变量
		self.setFixedSize(self.width(), self.height())
		self.ui.ensure.clicked.connect(self.ensure)

	def ensure(self):
		self.name = self.ui.name.text()
		self.accept()