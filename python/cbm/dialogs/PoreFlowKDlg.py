#coding:utf-8

from BaseDialog import *
from uipy.ui_pore_flow_K_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, pow, sin, cos, tan, radians

class PoreFlowKDlg(BaseDialog):
	def __init__(self, pore_flow, parent=None):
		super(PoreFlowKDlg, self).__init__(parent)
		self.ui = Ui_pore_flow_K_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"实际孔板流量特性系数计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		# 外部传入的对象
		self.pore_flow = pore_flow
		# 初始化
		self.init()

	def init(self):
		# 填充数据到界面
		self.ui.a0.setText(u'%.1f' % self.pore_flow.a0)
		self.ui.d.setText(u'%.1f' % self.pore_flow.d)
		self.ui.d1.setText(u'%.1f' % self.pore_flow.d1)
		self.ui.k.setText(u'%.1f' % self.pore_flow.k)

	def onSave(self):
		# 从界面提取数据
		a0, ok = self.ui.a0.text().toDouble()
		d1, ok = self.ui.d1.text().toDouble()
		d, ok = self.ui.d.text().toDouble()
		# 计算
		m = pow(d1 / d, 2)
		k = 189.76 * a0 * m * d * d
		# 更新到界面
		self.ui.k.setText(u'%.1f' % k)
		# 更新到孔板流量对象
		self.pore_flow.a0 = a0
		self.pore_flow.d1 = d1
		self.pore_flow.d = d
		self.pore_flow.k = k
		
		# 提交到数据库
		#做保存操作
		# self.accept()
