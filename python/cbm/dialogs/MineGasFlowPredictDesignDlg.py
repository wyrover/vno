# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_mine_gas_flow_predict_design_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class MineGasFlowPredictDesignDlg(BaseDialog):
	def __init__(self, work_area_id=-1, parent=None):
		super(MineGasFlowPredictDesignDlg, self).__init__(parent)
		self.ui = Ui_mine_gas_flow_predict_design_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"工作面和掘进面瓦斯涌出量相关参数及设计")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cancel.clicked.connect(self.onCancel)
		self.connect(self.ui.work_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkSurfChanged)
		self.connect(self.ui.drilling_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onDrillingSurfChanged)
		# 待设计的采区
		self.work_area_id = work_area_id
		# 初始化
		self.init()

	def init(self):
		# 填充工作面列表
		self.fillWorkSurfCombox()
		# 填充掘进面列表
		self.fillDrillingSurfCombox()
	
	def fillWorkSurfCombox(self):
		# 填充工作面列表
		work_surf_lists = SQLClientHelper.GetWorkSurfListByForeignKey('work_area_id', self.work_area_id)
		# 添加到工作面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.work_surf, work_surf_lists)
	
	def fillDrillingSurfCombox(self):
		# 填充掘进面列表
		drilling_surf_lists = SQLClientHelper.GetDrillingSurfListByForeignKey('work_area_id', self.work_area_id)
		# 添加到掘进面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.drilling_surf, drilling_surf_lists)

	def onWorkSurfChanged(self, index):
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:return

		# 提取数据到界面
		self.ui.work_surf_a.setText(u'%.1f' % work_surf.a)
		self.ui.work_surf_qr.setText(u'%1.f' % work_surf.qr)

	def onDrillingSurfChanged(self, index):
		drilling_surf_id, ok = self.ui.drilling_surf.itemData(index).toInt()
		drilling_surf = SQLClientHelper.GetDrillingSurfById(drilling_surf_id)
		if drilling_surf.id <= 0:return

		# 提取数据到界面
		self.ui.drilling_surf_qa.setText(u'%.1f' % drilling_surf.qa)

	def onSave(self):
		# 从数据库中查找当前的回采工作面
		index = self.ui.work_surf.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:L6)!')
			return

		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:L5)!')
			return

		# 从界面中读取数据
		work_surf.a, ok = self.ui.work_surf_a.text().toDouble()
		work_surf.qr, ok = self.ui.work_surf_qr.text().toDouble()
		# 提交工作面数据到数据库
		if not SQLClientHelper.UpdateWorkSurf(work_surf):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:L1)!')
			return

		# 从数据库中查找当前的掘进面
		index = self.ui.drilling_surf.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:L3)!')
			return

		drilling_surf_id, ok = self.ui.drilling_surf.itemData(index).toInt()
		drilling_surf = SQLClientHelper.GetDrillingSurfById(drilling_surf_id)
		if drilling_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:L4)!')
			return

		# 从界面中读取数据
		drilling_surf.qa, ok = self.ui.drilling_surf_qa.text().toDouble()
		# 提交掘进面数据到数据库
		if not SQLClientHelper.UpdateDrillingSurf(drilling_surf):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:L2)!')
		#关闭对话框并返回1
		# self.accept()
		UiHelper.MessageBox(u'恭喜您,更新数据成功啦!')
	
	def onCancel(self):
		# 关闭对话框并返回0
		self.reject()