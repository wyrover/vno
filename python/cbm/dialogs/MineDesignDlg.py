# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_mine_design_dlg import *

from CoalDesignDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class MineDesignDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(MineDesignDlg, self).__init__(parent)
		self.ui = Ui_mine_design_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"矿井设计")
		self.setFixedSize(self.width(), self.height())
		self.ui.add_coal.clicked.connect(self.onAddCoal)
		self.ui.add_work_area.clicked.connect(self.onAddWorkArea)
		self.ui.add_work_surf.clicked.connect(self.onAddWorkSurf)
		self.ui.add_drilling_surf.clicked.connect(self.onAddDrillingSurf)
		self.ui.del_coal.clicked.connect(self.onDelCoal)
		self.ui.del_work_area.clicked.connect(self.onDelWorkArea)
		self.ui.del_work_surf.clicked.connect(self.onDelWorkSurf)
		self.ui.del_drilling_surf.clicked.connect(self.onDelDrillingSurf)
		self.ui.more_coal.clicked.connect(self.onCoalDetail)
		self.ui.more_work_area.clicked.connect(self.onWorkAreaDetail)
		self.ui.more_work_surf.clicked.connect(self.onWorkSurfDetail)
		self.ui.more_drilling_surf.clicked.connect(self.onDrillingSurfDetail)
		# 煤炭基地切换 事件处理
		self.connect(self.ui.base, QtCore.SIGNAL('currentIndexChanged(int)'), self.onMineBaseChanged)
		self.connect(self.ui.coal, QtCore.SIGNAL('currentIndexChanged(int)'), self.onCoalChanged)
		self.connect(self.ui.work_area, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkAreaChanged)
		self.connect(self.ui.work_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkSurfChanged)
		self.connect(self.ui.drilling_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onDrillingSurfChanged)
		self.ui.save.clicked.connect(self.onSave)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 填充煤炭基地列表
		self.fillBaseCombox()
		# 填充矿井数据
		self.fillMineDatas()
		# 填充煤层列表
		self.fillCoalCombox()

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
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:M2)!')
			return

		# 填充数据
		name = mine.name.decode('utf-8')
		capacity = mine.capacity
		province = mine.province.decode('utf-8')
		city = mine.city.decode('utf-8')
		topo_geo = mine.topo_geo
		hydr_geo = mine.hydr_geo
		ground_condition = mine.ground_condition
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

	def fillCoalCombox(self):
		# 清空煤层下拉列表
		self.ui.coal.clear()

		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		# 添加到煤层下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.coal, coal_lists)

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

	def onAddCoal(self):
		# 弹出名称对话框,获取名称
		coal_name = unicode(UiHelper.GetNameFromDlg(u"新增煤层"))
		if coal_name == u'null' or coal_name == u'':
			UiHelper.MessageBox(u"请输入有效的名称！")
		else:
			# 新建煤层,并提交到数据库
			coal_id = DataHelper.sql_create_coal(coal_name.encode('utf-8'), self.mine_id)
			if coal_id <= 0:
				UiHelper.MessageBox(u"新增煤层失败")
			else:
				# 添加到下拉列表
				index = UiHelper.AddItemToCombobox(self.ui.coal, coal_name, coal_id)
				# 切换到新增item
				self.ui.coal.setCurrentIndex(index)

	def onAddWorkArea(self):
		# 获取当前煤层id
		index = self.ui.coal.currentIndex()
		if index < 0:return
		coal_id, ok = self.ui.coal.itemData(index).toInt()

		# 弹出名称对话框,获取名称
		work_area_name = unicode(UiHelper.GetNameFromDlg(u"新增采区"))
		if work_area_name == u'null' or work_area_name == u'':
			UiHelper.MessageBox(u"请输入有效的名称！")
		else:
			# 新建煤层,并提交到数据库
			work_area_id = DataHelper.sql_create_work_area(work_area_name.encode('utf-8'), coal_id)
			if work_area_id <= 0:
				UiHelper.MessageBox(u"新增采区失败")
			else:
				# 添加到下拉列表
				index = UiHelper.AddItemToCombobox(self.ui.work_area, work_area_name, work_area_id)
				# 切换到新增item
				self.ui.work_area.setCurrentIndex(index)

	def onAddWorkSurf(self):
		# 获取当前煤层id
		index = self.ui.work_area.currentIndex()
		if index < 0:return
		work_area_id, ok = self.ui.work_area.itemData(index).toInt()

		# 弹出名称对话框,获取名称
		work_surf_name = unicode(UiHelper.GetNameFromDlg(u"新增回采工作面"))
		if work_surf_name == u'null' or work_surf_name == u'':
			UiHelper.MessageBox(u"请输入有效的名称！")
		else:
			# 新建煤层,并提交到数据库
			work_surf_id = DataHelper.sql_create_work_surf(work_surf_name.encode('utf-8'), work_area_id)
			if work_surf_id <= 0:
				UiHelper.MessageBox(u"新增回采工作面失败")
			else:
				# 添加到下拉列表
				index = UiHelper.AddItemToCombobox(self.ui.work_surf, work_surf_name, work_surf_id)
				# 切换到新增item
				self.ui.work_surf.setCurrentIndex(index)

	def onAddDrillingSurf(self):
		# 获取当前煤层id
		index = self.ui.work_area.currentIndex()
		if index < 0:return
		work_area_id, ok = self.ui.work_area.itemData(index).toInt()

		# 弹出名称对话框,获取名称
		drilling_surf_name = unicode(UiHelper.GetNameFromDlg(u"新增掘进工作面"))
		if drilling_surf_name == u'null' or drilling_surf_name == u'':
			UiHelper.MessageBox(u"请输入有效的名称！")
		else:
			# 新建煤层,并提交到数据库
			drilling_surf_id = DataHelper.sql_create_drilling_surf(drilling_surf_name.encode('utf-8'), work_area_id)
			if drilling_surf_id <= 0:
				UiHelper.MessageBox(u"新增掘进工作面失败")
			else:
				# 添加到下拉列表
				index = UiHelper.AddItemToCombobox(self.ui.drilling_surf, drilling_surf_name, drilling_surf_id)
				# 切换到新增item
				self.ui.drilling_surf.setCurrentIndex(index)

	def onDelCoal(self):
		# 从数据库删除煤层(sql内部的级联delete机制可以保证关联的work_surf、drilling_surf同时也被删除)
		index = self.ui.coal.currentIndex()
		if index < 0:return

		if not UiHelper.MessageBox(u'您确定要删除该煤层？', question=True):
			return

		coal_id, ok = self.ui.coal.itemData(index).toInt()
		if SQLClientHelper.DeleteCoal(coal_id):
			# 从采区列表中删除
			self.ui.coal.removeItem(index)
			self.ui.coal.setCurrentIndex(0)
			UiHelper.MessageBox(u'删除煤层成功!')

	def onDelWorkArea(self):
		# 从数据库删除采区(sql内部的级联delete机制可以保证关联的work_surf、drilling_surf同时也被删除)
		index = self.ui.work_area.currentIndex()
		if index < 0:return

		if not UiHelper.MessageBox(u'您确定要删除该采区？', question=True):
			return

		work_area_id, ok = self.ui.work_area.itemData(index).toInt()
		if SQLClientHelper.DeleteWorkArea(work_area_id):
			# 从采区列表中删除
			self.ui.work_area.removeItem(index)
			self.ui.work_area.setCurrentIndex(0)
			UiHelper.MessageBox(u'删除采区成功!')

	def onDelWorkSurf(self):
		index = self.ui.work_surf.currentIndex()
		if index < 0:return

		if not UiHelper.MessageBox(u'您确定要删除该回采工作面？', question=True):
			return

		# 从数据库中删除工作面
		drilling_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		if SQLClientHelper.DeleteWorkSurf(drilling_surf_id):
			# 从工作面列表中删除
			self.ui.work_surf.removeItem(index)
			self.ui.work_surf.setCurrentIndex(0)
			UiHelper.MessageBox(u'删除回采工作面成功!')

	def onDelDrillingSurf(self):
		index = self.ui.drilling_surf.currentIndex()
		if index < 0:return

		if not UiHelper.MessageBox(u'您确定要删除该掘进工作面？', question=True):
			return

		# 从数据库中删除掘进面
		drilling_surf_id, ok = self.ui.drilling_surf.itemData(index).toInt()
		if SQLClientHelper.DeleteDrillingSurf(drilling_surf_id):
			# 从掘进面列表中删除
			self.ui.drilling_surf.removeItem(index)
			self.ui.drilling_surf.setCurrentIndex(0)
			UiHelper.MessageBox(u'删除掘进面成功!')

	def onCoalDetail(self):
		# 煤层列表显示的当前煤层
		index = self.ui.coal.currentIndex()
		if index < 0:return
		coal_id, ok = self.ui.coal.itemData(index).toInt()

		# 显示煤层设计对话卡U给你
		dlg = CoalDesignDlg(coal_id)
		dlg.exec_()

	def onWorkAreaDetail(self):
		pass
	
	def onWorkSurfDetail(self):
		pass

	def onDrillingSurfDetail(self):
		pass

	def onCoalChanged(self, index):
		# 清空采空区、工作面、掘进面列表
		self.ui.work_area.clear()
		self.ui.work_surf.clear()
		self.ui.drilling_surf.clear()

		if index < 0:return

		# 查询当前煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		# 双保险(确认煤层确实是在数据库中!!!)
		# coal = SQLClientHelper.GetCoalById(coal_id)
		# if coal.id <= 0:return

		# 填充采区列表
		work_area_lists = SQLClientHelper.GetWorkAreaListByForeignKey('coal_id', coal_id)
		# 添加到采区下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.work_area, work_area_lists)

	def onWorkAreaChanged(self, index):
		# 清空工作面和掘进面列表
		self.ui.work_surf.clear()
		self.ui.drilling_surf.clear()

		if index < 0:return

		# 查找当前采区
		work_area_id, ok = self.ui.work_area.itemData(index).toInt()
		# 填充工作面列表
		work_surf_lists = SQLClientHelper.GetWorkSurfListByForeignKey('work_area_id', work_area_id)
		# 添加到工作面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.work_surf, work_surf_lists)

		# 填充掘进面列表
		drilling_surf_lists = SQLClientHelper.GetDrillingSurfListByForeignKey('work_area_id', work_area_id)
		# 添加到掘进面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.drilling_surf, drilling_surf_lists)

	def onWorkSurfChanged(self, index):
		# if index < 0:return
		pass

	def onDrillingSurfChanged(self, index):
		# if index < 0:return
		pass

	def onSave(self):
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:M4)!')
			return

		mine.name = unicode(self.ui.name.text()).encode('utf-8')
		mine.capacity, ok = self.ui.capacity.text().toDouble()
		mine.province = unicode(self.ui.province.text()).encode('utf-8')
		mine.city = unicode(self.ui.city.text()).encode('utf-8')
		mine.topo_geo = self.ui.topo_geo.currentIndex() + 1
		mine.hydr_geo = self.ui.hydr_geo.currentIndex() + 1
		mine.ground_condition = int(self.ui.ground_cond.isChecked())
		region_name = unicode(self.ui.region.currentText()).encode('utf-8')
		mine.mine_region_id = SQLClientHelper.GetMineRegionIdByField1('name', region_name)
		if SQLClientHelper.UpdateMine(mine):
			UiHelper.MessageBox(u'恭喜您,更新矿井数据成功!!!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:D1)!')
