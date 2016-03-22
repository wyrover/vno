# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_technology_dlg import *

class TechnologyDlg(BaseDialog):
	def __init__(self,parent=None):
		super(TechnologyDlg, self).__init__(parent)
		self.ui = Ui_technologyDlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"推荐煤层气（瓦斯）抽采技术")
		self.setFixedSize(self.width(), self.height())		
		#self.ui.reg.clicked.connect(self.reg) 

