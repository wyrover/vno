# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_pore_size_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, pow, sin, cos, tan, radians

class PoreSizeDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(PoreSizeDlg, self).__init__(parent)
		self.ui = Ui_pore_size_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"抽采管径大小辅助计算")
		self.setFixedSize(self.width(),self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cacl.clicked.connect(self.onCacl)
		# 待设计的矿井
		self.mine_id = mine_id
		# 待设计的钻孔管径对象id
		# self.pore_size.id = -1
		self.pore_size = PoreSize()
		# 初始化
		self.init()

	def init(self):
		# 初始化抽采半径对象id
		self.initPoreSize()
		if self.pore_size.id <= 0:return

		# 获取抽采半径对象
		pore_size = SQLClientHelper.GetPoreSizeById(self.pore_size.id)
		if pore_size.id  <= 0:return

		# 读取数据到界面
		self.ui.q.setText(u'%.1f' % pore_size.q)
		self.ui.v.setText(u'%.1f' % pore_size.v)
		self.ui.d.setText(u'%.1f' % pore_size.d)
		self.ui.p.setText(u'%.1f' % pore_size.p)
		self.ui.sigma.setText(u'%.1f' % pore_size.sigma)
		self.ui.delta.setText(u'%.1f' % pore_size.delta)

	def initPoreSize(self):
		# 查找所有的抽采管径对象
		pore_size_lists = SQLClientHelper.GetPoreSizeList()
		if len(pore_size_lists) == 0:
			pore_size = PoreSize()
			pore_size_id = SQLClientHelper.AddPoreSize(pore_size)
			self.pore_size = SQLClientHelper.GetPoreSizeById(pore_size_id)
		else:
			# 目前只使用第1个数据
			self.pore_size = pore_size_lists[0]

	def onSave(self):
		# 获取抽采半径对象
		# pore_size = SQLClientHelper.GetPoreSizeById(self.pore_size.id)
		pore_size = self.pore_size
		if pore_size.id  <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题, 请联系技术人员(错误码:X1)')
			return

		# 从界面读取数据
		pore_size.q, ok = self.ui.q.text().toDouble()
		pore_size.v, ok = self.ui.v.text().toDouble()
		pore_size.d, ok = self.ui.d.text().toDouble()
		pore_size.p, ok = self.ui.p.text().toDouble()
		pore_size.sigma, ok = self.ui.sigma.text().toDouble()
		pore_size.delta, ok = self.ui.delta.text().toDouble()

		# 保存到数据库
		ret = False
		if pore_size.id <= 0:
			ret = SQLClientHelper.AddPoreSize(pore_size) > 0
		else:
			ret = SQLClientHelper.UpdatePoreSize(pore_size)
		if ret:
			UiHelper.MessageBox(u'恭喜您,更新数据成功!')
		else:
			UiHelper.MessageBox(u'sorry, 出了点问题, 请联系技术人员(错误码:W1)')
		
		# 关闭对话框并返回1
		# self.accept()

	def onCacl(self):
		# 提取界面数据
		Q, ok = self.ui.q.text().toDouble()
		V, ok = self.ui.v.text().toDouble()
		D, ok = self.ui.d.text().toDouble()
		P, ok = self.ui.p.text().toDouble()
		sigma, ok = self.ui.sigma.text().toDouble()

		if sigma == 0 or V == 0:
			UiHelper.MessageBox(u'经济流速或容许压力取值不能为0!!!')
			return

		# 计算
		D = 0.1457 * sqrt( Q / V)
		delta = 0.5 * P * D / sigma

		# 更新到界面
		self.ui.d.setText(u'%.1f' % D)
		self.ui.delta.setText(u'%.1f' % delta)
