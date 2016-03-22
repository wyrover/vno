# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_mine_base_param_dlg import *

from CoalParamDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

class MineBaseParamDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(MineBaseParamDlg, self).__init__(parent)
		self.ui = Ui_mine_base_param_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"请输入目标矿井基本信息")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cancel.clicked.connect(self.onCancel)
		self.ui.next.clicked.connect(self.onNext)
		# 煤炭基地切换 事件处理
		self.connect(self.ui.base, QtCore.SIGNAL('currentIndexChanged(int)'), self.onMineBaseChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化煤炭基地和矿区列表
		self.init()

	def init(self):
		# 填充煤炭基地列表
		self.fillBaseCombox()
		# 填充矿井数据
		self.fillMineDatas()

	def fillBaseCombox(self):
		# 查询所有的煤炭基地
		mine_base_list = SQLClientHelper.GetMineBaseList()
		if len(mine_base_list) == 0:return
		# 填充煤炭基地列表
		for mine_base in mine_base_list:
			self.ui.base.addItem(mine_base.name.decode('utf-8'), mine_base.id)
		# 默认选中第1个
		self.ui.base.setCurrentIndex(0)

	def fillMineDatas(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:E2)!')
			return

		# 填充数据
		name = mine.name.decode('utf-8')
		capacity = mine.capacity
		province = mine.province.decode('utf-8')
		city = mine.city.decode('utf-8')
		topo_geo = mine.topo_geo
		hydr_geo = mine.hydr_geo
		ground_condition = mine.ground_condition
		protect_layer_condition = mine.protect_layer_condition
		# 查找矿区
		mine_region = SQLClientHelper.GetMineRegionById(mine.mine_region_id)
		# combobox里的text好像不需要unicode,貌似不需要"编码"(encode)
		region_name = 'null' if mine_region.id < 0 else mine_region.name
		# 根据矿区名称反查煤炭基地
		base_name = CbmClientHelper.GetBaseByRegion(region_name)

		# 填充矿井数据		
		self.ui.name.setText(name)
		self.ui.capacity.setText(u'%.2f' % capacity)
		self.ui.province.setText(province)
		self.ui.city.setText(city)
		self.ui.topo_geo.setCurrentIndex(topo_geo-1)
		self.ui.hydr_geo.setCurrentIndex(hydr_geo-1)
		self.ui.ground_cond.setChecked(ground_condition != 0)
		self.ui.base.setCurrentIndex(self.ui.base.findText(base_name))
		self.ui.region.setCurrentIndex(self.ui.region.findText(region_name))
		self.ui.protect_layer_condition.setChecked(protect_layer_condition != 0)

	def onMineBaseChanged(self, index):
		# 清空矿区列表
		self.ui.region.clear()
		# 查询煤炭基地对应的矿区
		mine_base_id, ok = self.ui.base.itemData(index).toInt()
		if not ok:return

		# 查询煤炭基地辖制的矿区
		mine_region_list = SQLClientHelper.GetMineRegionListByField1('mine_base_id', str(mine_base_id))
		if len(mine_region_list) == 0:return
		# 填充矿区列表
		for mine_region in mine_region_list:
			# 从数据库中提取的字符串是utf-8编码的
			self.ui.region.addItem(mine_region.name.decode('utf-8'), mine_region.id)
		# 默认选中第1个
		self.ui.region.setCurrentIndex(0)

	def onSave(self):
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:E4)!')
			return

		mine.name = unicode(self.ui.name.text()).encode('utf-8')
		mine.capacity, ok = self.ui.capacity.text().toDouble()
		mine.province = unicode(self.ui.province.text()).encode('utf-8')
		mine.city = unicode(self.ui.city.text()).encode('utf-8')
		mine.topo_geo = self.ui.topo_geo.currentIndex() + 1
		mine.hydr_geo = self.ui.hydr_geo.currentIndex() + 1
		mine.ground_condition = int(self.ui.ground_cond.isChecked())
		mine.protect_layer_condition = int(self.ui.protect_layer_condition.isChecked())
		region_name = unicode(self.ui.region.currentText()).encode('utf-8')
		mine.mine_region_id = SQLClientHelper.GetMineRegionIdByField1('name', region_name)
		if SQLClientHelper.UpdateMine(mine):
			UiHelper.MessageBox(u'恭喜您,更新矿井数据成功!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:E1)!')

	def onCancel(self):
		# 关闭对话框并返回0
		self.reject()
		# 显示父窗口(这个窗口不需要通过代码来恢复上一个父窗口)
		# UiHelper.ShowWidget(self.parentWidget(), True)

	def onNext(self):
		# 启动下一个对话框: 煤层对话框
		dlg = CoalParamDlg(self.mine_id)
		dlg.exec_()