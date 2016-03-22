# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_gas_drilling_optimize_dlg import *

# from GasDrillingAnalyseDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, exp, pow, sin, cos, tan, radians, pi, asin, log10

class GasDrillingOptimizeDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(GasDrillingOptimizeDlg, self).__init__(parent)
		self.ui = Ui_gas_drilling_optimize_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"钻孔间距优化")
		self.setFixedSize(self.width(), self.height())
		#在窗口上为"煤层渗透率"控件安装过滤器
		# self.ui.t0.installEventFilter(self)
		# self.ui.r1.installEventFilter(self) ##在窗口上为"透气性系数"控件安装过滤器
		# self.ui.eta.installEventFilter(self) ##在窗口上为"透气性系数"控件安装过滤器
		self.ui.save.clicked.connect(self.onSave)
		self.ui.x_cacl.clicked.connect(self.onCaclX)
		self.ui.y_cacl.clicked.connect(self.onCaclY)
		self.ui.z_cacl.clicked.connect(self.onCaclZ)
		self.ui.analyse.clicked.connect(self.onAnalyse)
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

	# def eventFilter(self, source, event):
	# 	if source == self.ui.t0:
	# 		# "抽采时间"控件得到焦点
	# 		if event.type() == QtCore.QEvent.FocusIn:
	# 			# 根据"渗透率"计算"透气性系数"
	# 			self.onT0GetFocus()
	# 	elif source == self.ui.r1:
	# 		# "孔间距"控件得到焦点
	# 		if event.type() == QtCore.QEvent.FocusIn:
	# 			# 根据"透气性系数"计算"渗透率"
	# 			self.onR1GetFocus()
	# 	elif source == self.ui.eta:
	# 		# "抽采率"控件得到焦点
	# 		if event.type() == QtCore.QEvent.FocusIn:
	# 			# 根据"透气性系数"计算"渗透率"
	# 			self.onEtaGetFocus()
	# 	return super(GasDrillingOptimizeDlg, self).eventFilter(source, event)

	def onT0GetFocus(self):
		# 提取界面数据
		thick, ok = self.ui.thick.text().toDouble()
		permeability_lambda, ok = self.ui.permeability_lambda.text().toDouble()
		alpha, ok = self.ui.alpha.text().toDouble()
		p0, ok = self.ui.p0.text().toDouble()
		r0, ok = self.ui.r0.text().toInt()
		t0, ok = self.ui.t0.text().toInt()
		r1, ok = self.ui.r1.text().toInt()
		eta, ok = self.ui.eta.text().toDouble()
		if r0 <= 0 or thick <= 0:return

		# 孔径单位换算
		r0, r1 = r0*0.001, r1*1

		# psai计算
		k = DataHelper.gas_psai(permeability_lambda, p0, alpha, r0)
		print 'k= %.2f' % log10(k)

		# 提取x. y, z
		x = t0                                # t0
		y = DataHelper.R0_func(r1, thick)/r0  # R0/r0
		z = eta                               # η

		# 插值计算
		gdo = DataHelper.GasDrillingOpt()
		x = gdo.xValue(y, z, k)
		x = int(round(x))
		# 更新计算结果
		if abs(x - t0) > 1:
			self.ui.t0.setText(u'%d' % x)

	def onR1GetFocus(self):
		# 提取界面数据
		thick, ok = self.ui.thick.text().toDouble()
		permeability_lambda, ok = self.ui.permeability_lambda.text().toDouble()
		alpha, ok = self.ui.alpha.text().toDouble()
		p0, ok = self.ui.p0.text().toDouble()
		r0, ok = self.ui.r0.text().toInt()
		t0, ok = self.ui.t0.text().toInt()
		r1, ok = self.ui.r1.text().toInt()
		eta, ok = self.ui.eta.text().toDouble()
		if r0 <= 0 or thick <= 0:return

		# 孔径单位换算
		r0, r1 = r0*0.001, r1*1

		# psai计算
		k = DataHelper.gas_psai(permeability_lambda, p0, alpha, r0)
		print 'k= %.2f' % log10(k)

		# 提取x. y, z
		x = t0                                # t0
		y = DataHelper.R0_func(r1, thick)/r0  # R0/r0
		z = eta                               # η

		# 插值计算
		gdo = DataHelper.GasDrillingOpt()
		y = gdo.yValue(x, z, k)
		R1 = int(DataHelper.R1_func(y*r0, thick))
		# 更新计算结果
		if abs(R1-r1) > 1:
			self.ui.r1.setText(u'%d' % R1)

	def onEtaGetFocus(self):
		# 提取界面数据
		thick, ok = self.ui.thick.text().toDouble()
		permeability_lambda, ok = self.ui.permeability_lambda.text().toDouble()
		alpha, ok = self.ui.alpha.text().toDouble()
		p0, ok = self.ui.p0.text().toDouble()
		r0, ok = self.ui.r0.text().toInt()
		t0, ok = self.ui.t0.text().toInt()
		r1, ok = self.ui.r1.text().toInt()
		eta, ok = self.ui.eta.text().toDouble()
		if r0 <= 0 or thick <= 0:return

		# 孔径单位换算
		r0, r1 = r0*0.001, r1*1

		# psai计算
		k = DataHelper.gas_psai(permeability_lambda, p0, alpha, r0)
		print 'k= %.2f' % log10(k)

		# 提取x. y, z
		x = t0                                # t0
		y = DataHelper.R0_func(r1, thick)/r0  # R0/r0
		z = eta                               # η

		# 插值计算
		gdo = DataHelper.GasDrillingOpt()
		z = gdo.zValue(x, y, k)
		# 更新计算结果
		if abs(z-eta) > 0.1:
			self.ui.eta.setText(u'%.3f' % z)

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
		self.ui.thick.setText(u'%.1f' % coal.thick)
		self.ui.permeability_lambda.setText(u'%.1f' % coal.permeability_lambda)

		# 填充瓦斯抽采半径数据
		self.ui.alpha.setText(u'%.1f' % drp.a)
		self.ui.p0.setText(u'%.1f' % drp.p0)
		self.ui.p1.setText(u'%.1f' % drp.p1)
		self.ui.r0.setText(u'%d' % int(drp.r0))
		self.ui.t0.setText(u'%d' % int(drp.t))
		self.ui.r1.setText(u'%d' % int(drp.r1))
		self.ui.eta.setText(u'%.1f' % drp.eta)

	def onSave(self):
		index = self.ui.coal.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:YY1)')
			return
		# 查询当前煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:YY2)')
			return

		# 查询煤层关联的抽采半径参数对象
		# 如果没有就内部新建一个
		drp = self.getDrp(coal.id, False)
		if drp.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:YY3)')
			return

		# 保存煤层
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.permeability_lambda, ok = self.ui.permeability_lambda.text().toDouble()
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:YY4)')
			return

		# 保存瓦斯抽采半径数据
		drp.a, ok = self.ui.alpha.text().toDouble()
		drp.p0, ok = self.ui.p0.text().toDouble()
		drp.p1, ok = self.ui.p1.text().toDouble()
		drp.r0, ok = self.ui.r0.text().toDouble()
		drp.t, ok = self.ui.t0.text().toDouble()
		drp.r1, ok = self.ui.r1.text().toDouble()
		drp.eta, ok = self.ui.eta.text().toDouble()

		if not SQLClientHelper.UpdateDrillingRadiusParam(drp):
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:YY5)')
		
		UiHelper.MessageBox(u'恭喜您,更新数据成功!')

		# 关闭对话框并返回1
		# self.accept()
	
	def onAnalyse(self):
		# 提取界面数据
		thick, ok = self.ui.thick.text().toDouble()
		permeability_lambda, ok = self.ui.permeability_lambda.text().toDouble()
		alpha, ok = self.ui.alpha.text().toDouble()
		p0, ok = self.ui.p0.text().toDouble()
		r0, ok = self.ui.r0.text().toInt()
		t0, ok = self.ui.t0.text().toInt()
		r1, ok = self.ui.r1.text().toInt()
		eta, ok = self.ui.eta.text().toDouble()
		if r0 <= 0 or thick <= 0:return

		# 孔径单位换算
		r0, r1 = r0*0.001, r1*1

		# psai计算
		k = DataHelper.gas_psai(permeability_lambda, p0, alpha, r0)
		print 'k= %.2f' % log10(k)

		# 提取x. y, z
		x = t0                                # t0
		y = DataHelper.R0_func(r1, thick)/r0  # R0/r0
		z = eta                               # η

		DataHelper.DrawXYZ(x, y, k)

	def onCaclX(self):
		self.onT0GetFocus()
		pass

	def onCaclY(self):
		self.onR1GetFocus()
		pass

	def onCaclZ(self):
		self.onEtaGetFocus()
		pass