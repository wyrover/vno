# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_mine_gas_flow_predict_dlg import *

from MineGasFlowPredictDesignDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

class MineGasFlowPredictDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(MineGasFlowPredictDlg, self).__init__(parent)
		self.ui = Ui_mine_gas_flow_predict_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"矿井相对瓦斯涌出量预测")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.k1_cacl.clicked.connect(self.onK1Help)
		self.ui.k2_cacl.clicked.connect(self.onK2Help)
		self.ui.design_work_area.clicked.connect(self.onDesignWorkArea)
		self.ui.assign.clicked.connect(self.onAssign)
		self.ui.work_area_cacl.clicked.connect(self.onWorkAreaCacl)
		self.connect(self.ui.work_area, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkAreaChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()
		
	def init(self):
		# 填充矿井数据
		self.fillMineData()
		# 填充煤层列表
		self.fillCoalCombox()
		# 填充采区列表
		self.fillWorkAreaCombox()

	def fillMineData(self):
		# 根据id在数据库中查找矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:return

		# 更新数据到界面
		self.ui.k1_gas.setText(u'%.1f' % mine.gas_k1)
		self.ui.k2_gas.setText(u'%.1f' % mine.gas_k2)
		self.ui.qr.setText(u'%.1f' % mine.qr)

	def fillCoalCombox(self):
		# 清空煤层下拉列表
		self.ui.coal.clear()

		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		# 添加到煤层下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.coal, coal_lists)

	def fillWorkAreaCombox(self):
		if self.mine_id <= 0:return
		# 根据id在数据库中查找矿井
		# mine = SQLClientHelper.GetMineById(self.mine_id)
		# if mine.id <= 0:return

		work_area_lists = CbmClientHelper.GetWorkAreasOfMine(self.mine_id)
		# 添加到采区下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.work_area, work_area_lists)

	def onWorkAreaChanged(self, index):
		# 用户选择的采区id
		work_area_id, ok = self.ui.work_area.itemData(index).toInt()
		if work_area_id <= 0:return

		# 根据id查找采区
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)
		if work_area.id <= 0:return

		# 更新界面上的数据
		self.ui.work_area_a.setText(u'%.1f' % work_area.a)
		self.ui.work_area_qr.setText(u'%.1f' % work_area.qr)
		if work_area.coal_id <= 0:
			self.ui.coal.setCurrentIndex(-1)
		else:
			coal = SQLClientHelper.GetCoalById(work_area.coal_id)
			coal_name = coal.name.decode('utf-8')
			index = self.ui.coal.findText(coal_name)
			self.ui.coal.setCurrentIndex(index)
		
	def onK1Help(self):
		pass
		# UiHelper.MessageBox(u'该功能尚未实现!')

	def onK2Help(self):
		pass
		# UiHelper.MessageBox(u'该功能尚未实现!')

	def onDesignWorkArea(self):
		index = self.ui.work_area.currentIndex()
		if index < 0:return

		# 获取用户选择的采区
		work_area_id, ok = self.ui.work_area.itemData(index).toInt()
		if work_area_id <= 0:return

		dlg = MineGasFlowPredictDesignDlg(work_area_id)
		dlg.exec_()

	def onAssign(self):
		# 获取当前煤层
		index = self.ui.coal.currentIndex()
		if index < 0:return
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)

		# 获取当前采区
		index = self.ui.work_area.currentIndex()
		if index < 0:return
		work_area_id, ok = self.ui.work_area.itemData(index).toInt()
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)

		# 采区关联到新的煤层
		work_area.coal_id = coal_id

		# 提交到数据库
		coal_name = coal.name.decode('utf-8')
		work_area_name = work_area.name.decode('utf-8')
		if SQLClientHelper.UpdateWorkArea(work_area):	
			UiHelper.MessageBox(u'采区%s成功布置到煤层:%s!' % (work_area_name, coal_name))
		else:
			UiHelper.MessageBox(u'sorry, 尝试将采区%s布置到煤层:%s失败!' % (work_area_name, coal_name))

	def onWorkAreaCacl(self):
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:return

		# 将数据保存到矿井对象中用于后续计算
		mine.gas_k2, ok = self.ui.k2_gas.text().toDouble()
		# 调用rpc进行计算
		qr = CbmClientHelper.MineGasFlow(mine)

		if qr <= 0:
			UiHelper.MessageBox(u'错误:采区的日产量必须要大于0!!!')
			qr = 0.0
		else:
			UiHelper.MessageBox(u'更新"相对瓦斯涌出量"计算结果!')
		# 更新计算结果到界面
		self.ui.qr.setText(u'%.1f' % qr)
		
	def onSave(self):
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id  <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:K1)!')
		else:
			# 读取矿井数据
			mine.gas_k1, ok = self.ui.k1_gas.text().toDouble()
			mine.gas_k2, ok = self.ui.k2_gas.text().toDouble()

			# 提交到数据库
			if SQLClientHelper.UpdateMine(mine):
				UiHelper.MessageBox(u'更新矿井数据成功!')
			else:
				UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:K2)!')
				return

		# 当前用户选中的采区数据保存
		index = self.ui.work_area.currentIndex()
		if index < 0:return
		work_area_id, ok = self.ui.work_area.itemData(index).toDouble
		if work_area_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:K3)!')
			return
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)

		# 读取采区数据
		work_area.a, ok = self.ui.work_area.text().toDouble()
		work_area.qr, ok = self.ui.work_area.text().toDouble()
		index = self.ui.coal.currentIndex()
		if index >= 0:
			coal_id, ok = self.ui.coal.itemData(index)
			work_area.coal_id = coal_id # 采区属于哪个煤层
		# 提交到数据库
		if SQLClientHelper.UpdateWorkArea(work_area):
			UiHelper.MessageBox(u'更新采区数据成功!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:K4)!')

		# 关闭对话框并返回1
		# self.accept()
