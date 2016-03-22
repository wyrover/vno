# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_decision_dlg import *

from HighCoalDlg import *
from HighCoalsDlg import *
from LowNearlyCoalsDlg import *
from LowFarCoalsDlg import *
from LowCoalDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class DecisionDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(DecisionDlg, self).__init__(parent)
		self.ui = Ui_decision_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		# 设置表格样式
		UiHelper.InitTableStyle(self.ui.permeability_k_table, no_focus=True)
		UiHelper.InitTableStyle(self.ui.protect_layer_table, no_focus=True)
		UiHelper.InitTableStyle(self.ui.coal_population_table, no_focus=True)
		self.ui.permeability_k_table.setColumnWidth(0,100)
		self.ui.permeability_k_table.setColumnWidth(1,100)
		self.ui.permeability_k_table.setColumnWidth(2,100)
		self.ui.permeability_k_table.setColumnWidth(3,190)
		self.ui.protect_layer_table.setColumnWidth(0,100)
		self.ui.protect_layer_table.setColumnWidth(1,100)
		self.ui.protect_layer_table.setColumnWidth(2,100)
		self.ui.protect_layer_table.setColumnWidth(3,100)
		self.ui.coal_population_table.setColumnWidth(0,100)
		self.ui.coal_population_table.setColumnWidth(1,100)
		self.ui.coal_population_table.setColumnWidth(2,125)
		self.ui.coal_population_table.setColumnWidth(3,100)
		self.ui.coal_population_table.setColumnWidth(4,100)

		self.setTitle(u"煤层气抽采技术模式决策依据")
		self.setFixedSize(self.width(), self.height())
		self.ui.graph.clicked.connect(self.onGraph)
		self.ui.decision.clicked.connect(self.onDecision)
		self.ui.help1.clicked.connect(self.onHelp1)
		self.ui.help2.clicked.connect(self.onHelp2)
		self.ui.help3.clicked.connect(self.onHelp3)
		# 待决策的矿井
		self.mine_id = mine_id
		#初始化
		self.init()

	def init(self):
		# 渗透条件表
		self.fillPermeabilityKTable()
		# 保护层开采条件表
		self.fillProtectLayerTable()
		# 煤层群条件表
		self.fillCoalPopulationTable()
		
		# 渗透率条件(1-中高渗  0-低渗)
		# c1 = self.getPermeabilityKType()
	
	def fillPermeabilityKTable(self):
		# 清空
		self.ui.permeability_k_table.clearContents()
		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		self.ui.permeability_k_table.setRowCount(len(coal_lists))
		for i, coal in enumerate(coal_lists):
			self.ui.permeability_k_table.setItem(i, 0, QtGui.QTableWidgetItem(u'%d' % (i+1)))
			self.ui.permeability_k_table.setItem(i, 1, QtGui.QTableWidgetItem(u'%s' % coal.name.decode('utf-8')))
			self.ui.permeability_k_table.setItem(i, 2, QtGui.QTableWidgetItem(u'%.2f' % coal.permeability_k))
			item = QtGui.QTableWidgetItem()
			item.setFlags(QtCore.Qt.ItemIsEnabled)  # 不这么设置，用户点击时，图片被选的状态不美观
			if coal.permeability_k > 5:
				item.setIcon(QtGui.QIcon(':/images/yes.png'))
			else:
				item.setIcon(QtGui.QIcon(':/images/no.png'))
			self.ui.permeability_k_table.setItem(i, 3, item)

	def fillProtectLayerTable(self):
		# 清空
		self.ui.protect_layer_table.clearContents()
		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		self.ui.protect_layer_table.setRowCount(len(coal_lists))
		for i, coal in enumerate(coal_lists):
			self.ui.protect_layer_table.setItem(i, 0, QtGui.QTableWidgetItem(u'%d' % (i+1)))
			self.ui.protect_layer_table.setItem(i, 1, QtGui.QTableWidgetItem(u'%s' % coal.name.decode('utf-8')))
			self.ui.protect_layer_table.setItem(i, 2, QtGui.QTableWidgetItem(u'%.1f' % coal.dip_angle))
			self.ui.protect_layer_table.setItem(i, 3, QtGui.QTableWidgetItem(u'%.1f' % coal.thick))
			
			mine = SQLClientHelper.GetMineById(self.mine_id)
			if mine.id <= 0 or mine.protect_layer_condition == 0:
				self.ui.protect_layer_table.setItem(i, 4, QtGui.QTableWidgetItem(u'—'))
			else:
				protect_item = u'保护层' if coal.is_protectable != 0 else u'被保护层'
				self.ui.protect_layer_table.setItem(i, 4, QtGui.QTableWidgetItem(protect_item))
			# item = QtGui.QTableWidgetItem()
			# item.setFlags(QtCore.Qt.ItemIsEnabled)  # 不这么设置，用户点击时，图片被选的状态不美观
			# if True:
				# item.setIcon(QtGui.QIcon(':/images/yes.png'))
			# else:
				# item.setIcon(QtGui.QIcon(':/images/no.png'))
			# self.ui.protect_layer_table.setItem(i, 3, item)

	def fillCoalPopulationTable(self):
		# 清空
		self.ui.coal_population_table.clearContents()
		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		self.ui.coal_population_table.setRowCount(len(coal_lists))
		for i, coal in enumerate(coal_lists):
			self.ui.coal_population_table.setItem(i, 0, QtGui.QTableWidgetItem(u'%d' % (i+1)))
			self.ui.coal_population_table.setItem(i, 1, QtGui.QTableWidgetItem(u'%s' % coal.name.decode('utf-8')))
			self.ui.coal_population_table.setItem(i, 2, QtGui.QTableWidgetItem(u'%.1f' % coal.layer_gap))
			self.ui.coal_population_table.setItem(i, 3, QtGui.QTableWidgetItem(u'%.1f' % coal.czh))
			self.ui.coal_population_table.setItem(i, 4, QtGui.QTableWidgetItem(u'%.1f' % coal.influence_factor))

	def runResultDlg(self, idx):
		if idx == 1:
			dlg = HighCoalDlg()
			dlg.exec_()
		elif idx == 2:
			dlg = HighCoalsDlg()
			dlg.exec_()
		elif idx == 3:
			dlg = LowNearlyCoalsDlg()
			dlg.exec_()
		elif idx == 4:
			dlg = LowFarCoalsDlg()
			dlg.exec_()
		elif idx == 5:
			dlg = LowCoalDlg()
			dlg.exec_()

	# 决策煤层渗透率条件
	def decisionPermeabilityK(self):
		# 所有煤层渗透率均大于等于5mD时，判定该煤层为中高渗条件；否则，判定该煤层为低渗条件
		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		n = sum([int(float(coal.permeability_k) > 5) for coal in coal_lists])
		return int(n == len(coal_lists))

	# 决策保护层开采条件
	def decisionProtectLayer(self):
		# 查询矿井对象
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:return 0 # 不具备保护层开采条件
		return mine.protect_layer_condition != 0

	# 决策煤层群条件
	def decisionCoalPopulation(self):
		# 当煤层数量为1层
		# 或者虽然为多层，但任何两层间的层间距与下层面的比值均大于40时，判定为单一煤层条件；否则为煤层群条件。
		# 当煤层为煤层群条件时，任何一个煤层的“与上覆煤层间距”均≤“煤层开采冒落带高度”
		# 且采动影响倍数均≤7.5时，判定为近距离煤层群条件；否则判定为中远距离煤层群条件。
		
		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		if len(coal_lists) == 0:
			return 0 # 单一煤层条件
		else:
			# f = lambda coal:int(coal.layer_gap <= coal.czh and coal.influence_factor <= 7.5)
			f = lambda coal:int(coal.influence_factor <= 7.5)
			n = sum([f(coal) for coal in coal_lists])
			if n == len(coal_lists):
				return 1 # 近距离煤层群条件
			else:
				return 2 # 中远距离煤层群条件

	def decision(self):
		k1 = self.decisionPermeabilityK()
		k2 = self.decisionProtectLayer()
		k3 = self.decisionCoalPopulation()

		# 低渗
		if k1 == 0:
			# 不具备保护层开采条件
			if k2 == 0:
				return 5
			# 具备保护层开采条件
			# 单一煤层条件
			elif k3 == 0:
				return 5
			# 近距离煤层群条件
			elif k3 == 1:
				return 3
			# 中远距离煤层群条件
			else:
				return 4
		# 中高渗
		else:
			# 不具备保护层开采条件
			if k2 == 0:
				return 1
			# 具备保护层开采条件
			else:
				return 2		
	
	def onDecision(self):
		# 根据决策结果弹出相应的对话框
		idx = self.decision()
		self.runResultDlg(idx)

	def onGraph(self):
		# 给cad发送命令绘制煤层赋存图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawOccurrenceGraph %d %.1f" % (self.mine_id, 0.5), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def onHelp1(self):
		pass
	
	def onHelp2(self):
		pass
	
	def onHelp3(self):
		pass