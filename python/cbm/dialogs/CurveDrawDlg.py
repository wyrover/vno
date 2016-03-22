# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_curve_draw_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, pow, sin, cos, tan, radians

class CurveDrawDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(CurveDrawDlg, self).__init__(parent)
		self.ui = Ui_curve_draw_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"钻孔抽采量预测")
		self.setFixedSize(self.width(),self.height())
		self.ui.draw_curve.clicked.connect(self.onDrawCurve)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		pass

	def onDrawCurve(self):
		# 从界面中读取数据
		q0, ok = self.ui.q0.text().toDouble()
		alpha, ok = self.ui.alpha.text().toDouble()
		# 关闭对话框并返回1
		self.accept()

		# 绘制曲线
		DataHelper.draw_curve(q0, alpha)