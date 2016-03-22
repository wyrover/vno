# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_gas_drilling_radius_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, exp, pow, sin, cos, tan, radians, pi, asin

class GasDrillingRadiusDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(GasDrillingRadiusDlg, self).__init__(parent)
		self.ui = Ui_gas_drilling_radius_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"瓦斯抽采半径计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cacl.clicked.connect(self.onCacl)
		self.connect(self.ui.coal, QtCore.SIGNAL('currentIndexChanged(int)'), self.onCoalChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()
		
	def init(self):
		# 填充煤层列表
		self.fillCoalCombox()

	def fillCoalCombox(self):
		# 清空煤层下拉列表
		self.ui.coal.clear()

		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		# 添加到煤层下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.coal, coal_lists)

	def getDrp(self, coal_id, create_new=False):
		drp = SQLClientHelper.GetDrillingRadiusParamByForeignKey('coal_id', coal_id)
		if drp.id <= 0 and create_new:
			# 新建一个瓦斯半径数据对象提交到数据库
			drp = DrillingRadiusParam()
			drp.coal_id = coal_id
			drp_id = SQLClientHelper.AddDrillingRadiusParam(drp)
			if drp_id <= 0:
				drp.id = -1
			else:
				drp = SQLClientHelper.GetDrillingRadiusParamById(drp_id)
		return drp

	def onCoalChanged(self, index):
		if index < 0:return
		# 查询当前煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:return

		# 查询煤层关联的抽采半径参数对象
		# 如果没有就内部新建一个
		drp = self.getDrp(coal.id, True)
		if drp.id <= 0:return

		# 填充煤层数据
		self.ui.hw.setText(u'%.1f' % coal.hw)
		self.ui.gas_w0.setText(u'%.1f' % coal.gas_w0)
		self.ui.gas_wc3.setText(u'%.1f' % coal.gas_wc3)

		# 填充瓦斯抽采半径数据
		self.ui.rho.setText(u'%.1f' % drp.rho)
		self.ui.a.setText(u'%.1f' % drp.a)
		self.ui.t.setText(u'%.1f' % drp.t)
		self.ui.l.setText(u'%.1f' % drp.l)
		self.ui.q0.setText(u'%.1f' % drp.q0)
		self.ui.r.setText(u'%.1f' % drp.r)
		self.ui.qm.setText(u'%.1f' % drp.qm)
		self.ui.qsum.setText(u'%.1f' % drp.qsum)
		self.ui.eta.setText(u'%.1f' % drp.eta)
		self.ui.k1.setText(u'%.1f' % drp.k1)

	def onSave(self):
		index = self.ui.coal.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:Y1)')
			return
		# 查询当前煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:Y2)')
			return

		# 查询煤层关联的抽采半径参数对象
		# 如果没有就内部新建一个
		drp = self.getDrp(coal.id, False)
		if drp.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:Y3)')
			return

		# 保存煤层
		coal.hw, ok = self.ui.hw.text().toDouble()
		coal.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		coal.gas_wc3, ok = self.ui.gas_wc3.text().toDouble()
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:Y4)')
			return

		# 保存瓦斯抽采半径数据
		drp.rho, ok = self.ui.rho.text().toDouble()
		drp.a, ok = self.ui.a.text().toDouble()
		drp.t, ok = self.ui.t.text().toDouble()
		drp.l, ok = self.ui.l.text().toDouble()
		drp.q0, ok = self.ui.q0.text().toDouble()
		drp.r, ok = self.ui.r.text().toDouble()
		drp.qm, ok = self.ui.qm.text().toDouble()
		drp.qsum, ok = self.ui.qsum.text().toDouble()
		drp.eta, ok = self.ui.eta.text().toDouble()
		drp.k1, ok = self.ui.k1.text().toDouble()

		if not SQLClientHelper.UpdateDrillingRadiusParam(drp):
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:Y5)')
		
		UiHelper.MessageBox(u'恭喜您,更新数据成功!')

		# 关闭对话框并返回1
		# self.accept()

	def onCacl(self):
		DataHelper.drilling_ratio(40,10,1)
		return
		# 从界面中提取数据
		r, ok = self.ui.r.text().toDouble()
		l, ok = self.ui.l.text().toDouble()
		k1, ok = self.ui.k1.text().toDouble()
		rho, ok = self.ui.rho.text().toDouble()
		q0, ok = self.ui.q0.text().toDouble()
		a, ok = self.ui.a.text().toDouble()
		t, ok = self.ui.t.text().toDouble()
		h, ok = self.ui.hw.text().toDouble()
		w, ok = self.ui.gas_w0.text().toDouble()
		qm, ok = self.ui.qm.text().toDouble()
		q, ok = self.ui.qsum.text().toDouble()
		eta, ok = self.ui.eta.text().toDouble()
		
		# 计算
		if r == 0 or h == 0 or w == 0 or l == 0:
			UiHelper.MessageBox(u'所有数据都必须大于0!!!')
			return
		# 计算Qm
		if 2*r < h or abs(2*r - h) < 1e-3:
			s = pi * r * r # 面积
			qm = 1440*k1*q0*(1-exp(-1*a*t)) / (rho * a * s *(r+l))
		else:
			s = 2 * r * r * asin(0.5*h/r) + h*sqrt(r*r -0.25*h*h)
			qm = 1440*k1*q0*(1-exp(-1*a*t)) / (rho * a * s *(r+l))
		
		# 计算eta和wc
		eta = qm / w
		wc = w - q

		# 更新到界面
		self.ui.qm.setText(u'%.1f' % qm)
		self.ui.eta.setText(u'%.1f' % eta)
		self.ui.gas_wc3.setText(u'%.1f' % wc)

		UiHelper.MessageBox(u'更新计算结果成功!')
		# 关闭对话框并返回1
		# self.accept()