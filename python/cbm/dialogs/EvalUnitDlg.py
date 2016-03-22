# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_eval_unit_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

class EvalUnitDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(EvalUnitDlg, self).__init__(parent)
		self.ui = Ui_eval_unit_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"评价单元划分")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.partition.clicked.connect(self.onPartition)
		self.connect(self.ui.work_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkSurfChanged)
		# 外部传入的对象
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
		
		deup = SQLClientHelper.GetDesignEvalUnitPartitionByForeignKey('work_surf_id', work_surf_id)
		if deup.id <= 0:
			deup = DesignEvalUnitPartition()
			deup.work_surf_id = work_surf_id
			deup_id = SQLClientHelper.AddDesignEvalUnitPartition(deup)
			deup = SQLClientHelper.GetDesignEvalUnitPartitionById(deup_id)
			if deup.id <= 0:return

		# 填充评价单元划分数据
		# 这里做了点手脚,所有的数据都放在design_eval_unit_partition表里面,并没有从其它的coal、worksurf里读取数据,仅仅保持了与工作面的外键关系
		self.ui.l1.setText(u'%.1f' % deup.l1)
		self.ui.l2.setText(u'%.1f' % deup.l2)
		self.ui.l.setText(u'%.1f' % deup.l)
		self.ui.w.setText(u'%.1f' % deup.w)
		self.ui.h.setText(u'%.1f' % deup.h)
		self.ui.r.setText(u'%.1f' % deup.r)
		self.ui.t.setText(u'%.1f' % deup.t)
		self.ui.v.setText(u'%d' % int(deup.v))

		# 填充煤层数据
		self.ui.thick.setText(u'%.1f' % coal.thick)
		self.ui.dip_angle.setText(u'%.1f' % coal.dip_angle)

	def onPartition(self):
		index = self.ui.work_surf.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'请指定一个工作面进行设计!')
			return

		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z9)')
			return
		
		deup = SQLClientHelper.GetDesignEvalUnitPartitionByForeignKey('work_surf_id', work_surf_id)
		if deup.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z12)')
			return

		# 设计评价单元
		DataHelper.design_eval_unit(deup.id)
		# 给cad发送命令请求绘制评价单元示意图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawEvalUnitGraph %d" % deup.id, True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')
		
	def onSave(self):
		index = self.ui.work_surf.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z1)')
			return

		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z2)')
			return
		work_area = SQLClientHelper.GetWorkAreaById(work_surf.work_area_id)
		if work_area.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z3)')
			return
		coal = SQLClientHelper.GetCoalById(work_area.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z4)')
			return
		
		deup = SQLClientHelper.GetDesignEvalUnitPartitionByForeignKey('work_surf_id', work_surf_id)
		if deup.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z5)')
			return

		# 从界面读取评价单元划分数据
		# 这里做了点手脚,所有的数据都放在design_eval_unit_partition表里面,
		# 并没有从其它的coal、worksurf里读取数据,仅仅保持了与工作面的外键关系
		deup.l1, ok = self.ui.l1.text().toDouble()
		deup.l2, ok = self.ui.l2.text().toDouble()
		deup.l, ok = self.ui.l.text().toDouble()
		deup.w, ok = self.ui.w.text().toDouble()
		deup.h, ok = self.ui.h.text().toDouble()
		deup.r, ok = self.ui.r.text().toDouble()
		deup.t, ok = self.ui.t.text().toDouble()
		deup.v, ok = self.ui.v.text().toDouble()

		# 提交到数据库
		if not SQLClientHelper.UpdateDesignEvalUnitPartition(deup):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z6)')
			return
		
		# 从界面读取煤层数据
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.dip_angle, ok = self.ui.dip_angle.text().toDouble()

		# 提交到数据库
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Z7)')
			return

		UiHelper.MessageBox(u'恭喜您,更新数据成功!')

		#做保存操作
		# self.accept()
