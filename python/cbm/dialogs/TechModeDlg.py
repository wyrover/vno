# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_tech_mode_dlg import *

class TechModeDlg(BaseDialog):
	def __init__(self,parent=None):
		super(TechModeDlg, self).__init__(parent)
		self.ui = Ui_tech_mode_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"煤层气（瓦斯）抽采技术模式参数")
		self.setFixedSize(self.width(), self.height())		
		#self.ui.reg.clicked.connect(self.reg) 
