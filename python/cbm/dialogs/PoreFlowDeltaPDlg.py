# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_pore_flow_delta_p_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, pow, sin, cos, tan, radians

class PoreFlowDeltaPDlg(BaseDialog):
	def __init__(self, pore_flow, parent=None):
		super(PoreFlowDeltaPDlg, self).__init__(parent)
		self.ui = Ui_pore_flow_delta_p_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"气压校正系数计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		# 外部传入的对象
		self.pore_flow = pore_flow
		# 初始化
		self.init()

	def init(self):
		# 填充数据到界面
		self.ui.p_test.setText(u'%.1f' % self.pore_flow.p_test)
		self.ui.p_cur.setText(u'%.1f' % self.pore_flow.p_cur)
		self.ui.pt.setText(u'%.1f' % self.pore_flow.pt)
		self.ui.delta_p.setText(u'%.1f' % self.pore_flow.delta_p)

	def onSave(self):
		# 从界面提取数据
		p_cur, ok = self.ui.p_cur.text().toDouble()
		p_test, ok = self.ui.p_test.text().toDouble()
		# 计算
		pt = ( p_cur + p_test ) / 13.6
		delta_p = sqrt( pt / 760.0 )
		# 更新到界面
		self.ui.pt.setText(u'%.1f' % pt)
		self.ui.delta_p.setText(u'%.1f' % delta_p)

		# 更新到孔板流量对象
		self.pore_flow.p_test = p_test
		self.pore_flow.p_cur = p_cur
		self.pore_flow.pt = pt
		self.pore_flow.delta_p = delta_p
		
		#做保存操作
		# self.accept()
