# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_high_drilling_design_dlg import *

from HighDrillingSiteDlg import *
from HighDrillingPoreDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, pow, sin, cos, tan, radians

class HighDrillingDesignDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(HighDrillingDesignDlg, self).__init__(parent)
		self.ui = Ui_high_drilling_design_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"高位抽采钻场钻孔设计")
		self.setFixedSize(self.width(),self.height())
		# self.ui.abc.setFocusPolicy(Qt.NoFocus);
		# 初始化abc和bcd表格的样式
		UiHelper.InitTableStyle(self.ui.abc)
		UiHelper.InitTableStyle(self.ui.bcd)
		self.ui.save.clicked.connect(self.onSave)
		self.ui.drill_site.clicked.connect(self.onDrillSite)
		self.ui.drill_pore.clicked.connect(self.onDrillPore)
		self.connect(self.ui.work_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkSurfChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 填充工作面列表
		self.fillWorkSurfCombox()

	def fillWorkSurfCombox(self):
		# 查找矿井的所有工作面
		work_surf_lists = CbmClientHelper.GetWorkSurfsOfMine(self.mine_id)
		# 添加到工作面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.work_surf, work_surf_lists)

	def onWorkSurfChanged(self, index):
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:return
		work_area = SQLClientHelper.GetWorkAreaById(work_surf.work_area_id)
		if work_area.id <= 0:return
		coal = SQLClientHelper.GetCoalById(work_area.coal_id)
		if coal.id <= 0:return
		
		# 填充高抽巷钻场的数据
		hdsp = SQLClientHelper.GetHighDrillingSiteParamByForeignKey('work_surf_id', work_surf_id)
		if hdsp.id <= 0:
			self.ui.l1.setText(u'0.0')
			self.ui.l2.setText(u'0.0')
			self.ui.lg.setText(u'0.0')
		else:
			self.ui.l1.setText(u'%.1f' % hdsp.l1)
			self.ui.l2.setText(u'%.1f' % hdsp.l2)
			self.ui.lg.setText(u'%.1f' % hdsp.lg)

		# 填充高抽巷钻孔的数据
		hdpp = SQLClientHelper.GetHighDrillingPoreParamByForeignKey('work_surf_id', work_surf_id)
		# 清空abc和bcd表格
		self.ui.abc.clearContents()
		self.ui.bcd.clearContents()
		# 测试代码
		# self.ui.abc.setRowCount(5)
		# self.ui.abc.setItem(0, 0, QtGui.QTableWidgetItem('1'))
		# self.ui.abc.setItem(0, 1, QtGui.QTableWidgetItem('2'))
		# self.ui.abc.setItem(0, 2, QtGui.QTableWidgetItem('3'))
		# self.ui.abc.setItem(0, 3, QtGui.QTableWidgetItem('4'))
		# return
		if hdpp.id > 0:
			# 查找abc范围的钻孔(type=0表示abc区域)
			abc_pore_lists = SQLClientHelper.GetHighDrillingPoreListByField2('high_drilling_pore_param_id', str(hdpp.id), 'pore_type', str(0))
			# 设置行数
			self.ui.abc.setRowCount(len(abc_pore_lists))
			for i, pore in enumerate(abc_pore_lists):
				self.ui.abc.setItem(i, 0, QtGui.QTableWidgetItem(u'%d' % pore.num))
				self.ui.abc.setItem(i, 1, QtGui.QTableWidgetItem(u'%1.f' % pore.length))
				self.ui.abc.setItem(i, 2, QtGui.QTableWidgetItem(u'%.1f' % pore.angle))
				# self.ui.abc.setItem(i, 3, QtGui.QTableWidgetItem(u'%.1f' % pore.azimuth_angle))

			# 查找bcd范围的钻孔(type=1表示bcd区域)
			bcd_pore_lists = SQLClientHelper.GetHighDrillingPoreListByField2('high_drilling_pore_param_id', str(hdpp.id), 'pore_type', str(1))
			# 设置行数
			self.ui.abc.setRowCount(len(bcd_pore_lists))
			for i, pore in enumerate(bcd_pore_lists):
				self.ui.abc.setItem(i, 0, QtGui.QTableWidgetItem(u'%d' % pore.num))
				self.ui.abc.setItem(i, 1, QtGui.QTableWidgetItem(u'%1.f' % pore.length))
				self.ui.abc.setItem(i, 2, QtGui.QTableWidgetItem(u'%.1f' % pore.angle))
				# self.ui.abc.setItem(i, 3, QtGui.QTableWidgetItem(u'%.1f' % pore.azimuth_angle))

	def getPores(self, table, hdpp_id):
		pores = []
		for i in range(table.rowCount()):
			num, ok = table.item(i, 0).text().toInt()
			length, ok = table.item(i, 1).text().toDouble()
			angle, ok = table.item(i, 2).text().toDouble()

			# 提交得到数据库
			aPore = HighDrillingPore()
			aPore.num = num
			aPore.length = length
			aPore.angle = angle
			aPore.high_drilling_pore_param_id = hdpp_id
			pores.append(aPore)
		return pores
				  
	def onSave(self):
		# 当前选中的工作面
		index = self.ui.work_surf.currentIndex()
		if index < 0:return

		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'请选择一个工作面!')
			return
		
		# 提取钻场参数
		hdsp = SQLClientHelper.GetHighDrillingSiteParamByForeignKey('work_surf_id', work_surf.id)
		if hdsp.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:U1')
			return

		hdsp.l1, ok = self.ui.l1.text().toDouble()
		hdsp.l2, ok = self.ui.l2.text().toDouble()
		hdsp.lg, ok = self.ui.lg.text().toDouble()

		# 保存钻场数据到数据库
		if not SQLClientHelper.UpdateHighDrillingSiteParam(hdsp):
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:U2')
			return

		# 从数据库中提取钻孔参数数据
		hdpp = SQLClientHelper.GetHighDrillingPoreParamByForeignKey('work_surf_id', work_surf.id)
		if hdpp.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:U3')
			return

		# 删除与钻孔参数关联的所有高位抽采钻孔
		pore_id_lists = SQLClientHelper.GetHighDrillingPoreIdListByForeignKey('high_drilling_pore_param_id', hdpp.id)
		SQLClientHelper.DeleteMoreHighDrillingPore(pore_id_lists)

		# 保存abc列表中的钻孔
		pores = self.getPores(self.ui.abc, hdpp.id)
		# 集中提交到数据库
		SQLClientHelper.AddMoreHighDrillingPore(pores)

		# bcd
		pores = self.getPores(self.ui.bcd, hdpp.id)
		# 集中提交到数据库
		SQLClientHelper.AddMoreHighDrillingPore(pores)

		UiHelper.MessageBox(u'保存高抽巷钻场和钻孔数据成功!')
		# self.accept()
		pass

	def onDrillSite(self):
		# 当前选中的工作面
		index = self.ui.work_surf.currentIndex()
		if index < 0:return

		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'请选择一个工作面!')
			return

		# 显示钻场设计对话框
		dlg = HighDrillingSiteDlg(work_surf.id)
		dlg.exec_()

		# 计算钻场参数
		hdsp = SQLClientHelper.GetHighDrillingSiteParamByForeignKey('work_surf_id', work_surf.id)
		if hdsp.id <= 0:return
		hn, Rtn, q, hs, theta = hdsp.hn, hdsp.rtn, hdsp.q, hdsp.hs, hdsp.theta
		L1 = hn * sqrt(2.0 * Rtn / q) + 2 * hs / tan( radians(theta) )
		L2 = hn * sqrt( 2.0 * Rtn / (3 * q) )
		Lg = L2

		# 更新到界面
		self.ui.l1.setText(u'%.1f' % L1)
		self.ui.l2.setText(u'%.1f' % L2)
		self.ui.lg.setText(u'%.1f' % Lg)

	def onDrillPore(self):
		# 当前选中的工作面
		index = self.ui.work_surf.currentIndex()
		if index < 0:return

		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'请选择一个工作面!')
			return

		# 读取界面上的Lg数据
		Lg, ok = self.ui.lg.text().toDouble()

		# 显示对话框
		dlg = HighDrillingPoreDlg(work_surf.id)
		# 传入到对话框中用于计算
		# 这个设计存在一个bug,如果当前界面上的数据Lg没有保存
		# 然后我们把Lg传到HighDrillingPoreDlg对话框里
		# 假若用户在弹出对话框里点"保存",
		# 然后退出本对话框时没有点"保存"
		# 这时会出现数据前后不一致的情况
		dlg.Lg = Lg
		dlg.exec_()

		# 清空钻孔列表
		self.ui.abc.clearContents()
		self.ui.bcd.clearContents()

		# 从数据库中提取钻孔参数数据
		hdpp = SQLClientHelper.GetHighDrillingPoreParamByForeignKey('work_surf_id', work_surf.id)
		if hdpp.id <= 0:return

		# 计算一些重要参数(后续会用到)
		Lc, Ld, beta, n1, n2 = hdpp.lc, hdpp.ld, hdpp.beta, hdpp.n1, hdpp.n2
		n = n1 + n2
		Lk = Lc + Lg
		c = radians(beta) / (n + 1)

		# 计算并保存钻孔数据到abc列表
		self.ui.abc.setRowCount(n1)
		for i in range(n1):
			k = i + 1
			beta_i = k * c # 角度
			Lz_i = Lk / cos(beta_i)  # 长度

			# 添加到表格中
			self.ui.abc.setItem(i, 0, QtGui.QTableWidgetItem(u'%d' % k))
			self.ui.abc.setItem(i, 1, QtGui.QTableWidgetItem(u'%.1f' % Lz_i))
			self.ui.abc.setItem(i, 2, QtGui.QTableWidgetItem(u'%.1f' % beta_i))
		
		# 计算并保存钻孔数据到bcd列表
		self.ui.bcd.setRowCount(n2)
		for i in range(n2):
			k = i + 1 + n1
			beta_i = k * c # 角度
			Lz_i = Ld / sin(beta_i) # 长度

			# 添加到表格中
			self.ui.bcd.setItem(i, 0, QtGui.QTableWidgetItem(u'%d' % k))
			self.ui.bcd.setItem(i, 1, QtGui.QTableWidgetItem(u'%.1f' % Lz_i))
			self.ui.bcd.setItem(i, 2, QtGui.QTableWidgetItem(u'%.1f' % beta_i))

