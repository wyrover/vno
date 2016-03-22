# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_ws_gas_flow_predict_dlg import *

from WsGasFlowPredictWorkDlg import *
from WsGasFlowPredictAdjDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

class WsGasFlowPredictDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(WsGasFlowPredictDlg, self).__init__(parent)
		self.ui = Ui_ws_gas_flow_predict_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"回采工作面瓦斯涌出量预测")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.q1_cacl.clicked.connect(self.onQr1Cacl)
		self.ui.q2_cacl.clicked.connect(self.onQr2Cacl)
		self.ui.qr_cacl.clicked.connect(self.onQrCacl)
		self.connect(self.ui.work_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkSurfChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 填充回采面列表
		self.fillWorkSurfCombox()

	def fillWorkSurfCombox(self):
		# 查找矿井的所有工作面
		work_surf_lists = CbmClientHelper.GetWorkSurfsOfMine(self.mine_id)
		# 添加到工作面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.work_surf, work_surf_lists)

	def onWorkSurfChanged(self, index):
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			# UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N1)!')
			return

		# 填充回采工作面的数据
		# 是否分层开采
		self.ui.method_thin.setChecked(work_surf.layerable == 0)
		self.ui.method_thick.setChecked(work_surf.layerable != 0)
		# 工作面长度和采高
		self.ui.l1.setText(u'%.1f' % work_surf.l1)
		# self.ui.hw.setText(u'%.1f' % work_surf.hw)
		# 工作面瓦斯涌出量数据
		self.ui.qr1.setText(u'%.1f' % work_surf.qr1)
		self.ui.qr2.setText(u'%.1f' % work_surf.qr2)
		self.ui.qr.setText(u'%.1f' % work_surf.qr)
		
		# 煤层厚度
		work_area = SQLClientHelper.GetWorkAreaById(work_surf.work_area_id)
		coal = SQLClientHelper.GetCoalById(work_area.coal_id)
		if coal.id <= 0:
			self.ui.hw.setText(u'0.0')
			self.ui.thick.setText(u'0.0')
			self.ui.ws_thick.setText(u'0.0')
		else:
			self.ui.hw.setText(u'%.1f' % coal.hw)
			self.ui.thick.setText(u'%.1f' % coal.thick)
			self.ui.ws_thick.setText(u'%.1f' % coal.thick)

	def onSave(self):
		index = self.ui.work_surf.currentIndex()
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N1)!')
			return
		
		# 煤层厚度
		work_area = SQLClientHelper.GetWorkAreaById(work_surf.work_area_id)
		coal = SQLClientHelper.GetCoalById(work_area.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N2)!')
			return

		# 保存工作面数据
		work_surf.layerable = int(not self.ui.method_thin.isChecked())
		print '-+---+--+-->:', work_surf.layerable
		# 工作面长度和采高
		work_surf.l1, ok = self.ui.l1.text().toDouble()
		# self.ui.hw.text(work_surf.hw).toDouble()
		# 工作面瓦斯涌出量数据
		work_surf.qr1, ok = self.ui.qr1.text().toDouble()
		work_surf.qr2, ok = self.ui.qr2.text().toDouble()
		work_surf.qr, ok = self.ui.qr.text().toDouble()

		# 提交工作面到数据库
		# 注意:煤层数据修改了,也不会提交到数据库!!
		if SQLClientHelper.UpdateWorkSurf(work_surf):
			UiHelper.MessageBox(u'恭喜您,工作面数据更新成功啦!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N3)!')
		# 关闭对话框并返回1
		# self.accept()

	def onQr1Cacl(self):
		# 当前用户选中的回采面
		index = self.ui.work_surf.currentIndex()
		if index < 0:return

		# 根据id查找回采面
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()

		# 弹出开采层计算对话框
		dlg = WsGasFlowPredictWorkDlg(work_surf_id)
		dlg.exec_()

		# 根据id查找回采面->采区->煤层
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		work_area_id = work_surf.work_area_id
		if work_area_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N4)!')
			return
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)
		
		# 查找煤层
		coal_id = work_area.coal_id
		if coal_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N5)!')
			return
		coal = SQLClientHelper.GetCoalById(coal_id)

		# 从界面中读取数据
		# 开采层厚度(????分层如何考虑???)
		coal.thick, ok = self.ui.thick.text().toDouble()
		# 是否分层开采
		work_surf.layerable = int(not self.ui.method_thin.isChecked())

		# 调用rpc计算工作面瓦斯涌出量
		q1 = CbmClientHelper.WorkSurfGasFlow1(coal, work_area, work_surf)
		# 更新计算结果到界面
		self.ui.qr1.setText(u'%.1f' % q1)
		# UiHelper.MessageBox(u'计算成功，更新数据到"开采层相对瓦斯涌出量q1"!!')

	def onQr2Cacl(self):
		# 当前用户选中的回采面
		index = self.ui.work_surf.currentIndex()
		if index < 0:return

		# 根据id查找回采面
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()

		# 弹出邻近层计算对话框
		dlg = WsGasFlowPredictAdjDlg(work_surf_id)
		dlg.exec_()

		# 根据id查找回采面->采区->煤层
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		work_area_id = work_surf.work_area_id
		if work_area_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N4)!')
			return
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)
		
		# 查找煤层
		coal_id = work_area.coal_id
		if coal_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:N5)!')
			return
		coal = SQLClientHelper.GetCoalById(coal_id)

		# 调用rpc计算工作面瓦斯涌出量
		q2 = CbmClientHelper.WorkSurfGasFlow2(coal, work_area, work_surf)
		# 更新计算结果到界面
		self.ui.qr2.setText(u'%.1f' % q2)
		# UiHelper.MessageBox(u'计算成功，更新数据到"邻近层相对瓦斯涌出量q2"!!')

	def onQrCacl(self):
		UiHelper.MessageBox(u'该功能尚未明确如何做???')