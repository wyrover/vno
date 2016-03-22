# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_gas_drilling_analyse_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, exp, pow, sin, cos, tan, radians, pi, asin, log10
import numpy as np

class GasDrillingAnalyseDlg(BaseDialog):
	def __init__(self, mine_id=-1, k = 0, parent=None):
		super(GasDrillingAnalyseDlg, self).__init__(parent)
		self.ui = Ui_gas_drilling_analyse_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"抽采率优化分析")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		# self.ui.cacl.clicked.connect(self.onCacl)
		# self.ui.analyse.clicked.connect(self.onAnalyse)
		# self.connect(self.ui.coal, QtCore.SIGNAL('currentIndexChanged(int)'), self.onCoalChanged)
		self.k = k
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()
	
	def init(self):
		# 填充煤层列表
		# self.fillCoalCombox()
		pass

	def onSave(self):
		# 抽采率η与R0/r0的关系
		if self.ui.data_type1.isChecked():
			self.onDataType1()
		# 抽采率η与抽采时间T0的关系
		elif self.ui.data_type2.isChecked():
			self.onDataType2()

	def onDataType1(self):
		x = 65
		print 'k= %.2f' % log10(self.k)
		# 绘制曲线
		DataHelper.DrawYZ_X(x, self.k)

	def onDataType2(self):
		y = 45
		print 'k= %.2f' % log10(self.k)
		# 绘制曲线
		DataHelper.DrawXZ_Y(y, self.k)
