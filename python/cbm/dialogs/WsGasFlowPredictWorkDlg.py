# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_ws_gas_flow_predict_work_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

class WsGasFlowPredictWorkDlg(BaseDialog):
	def __init__(self, work_surf_id=-1, parent=None):
		super(WsGasFlowPredictWorkDlg, self).__init__(parent)
		self.ui = Ui_ws_gas_flow_predict_work_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"开采层相对瓦斯涌出量q1计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.k3_cacl.clicked.connect(self.onK3Cacl)
		self.ui.kf_cacl.clicked.connect(self.onKfCacl)
		# 待设计的工作面
		self.work_surf_id = work_surf_id
		# 初始化
		self.init()

	def init(self):
		# 填充工作面、采区、煤层的数据
		self.fillDatas()

	def fillDatas(self):
		# 根据id查找工作面
		work_surf = SQLClientHelper.GetWorkSurfById(self.work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O1)!')
			return
		work_area = SQLClientHelper.GetWorkAreaById(work_surf.work_area_id)
		if work_area.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O2)!')
			return
		coal = SQLClientHelper.GetCoalById(work_area.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O3)!')
			return

		# 提取工作面数据到界面上
		self.ui.k1.setText(u'%.1f' % work_surf.k1)
		self.ui.k2.setText(u'%.1f' % work_surf.k2)
		self.ui.k3.setText(u'%.1f' % work_surf.k3)
		self.ui.kf.setText(u'%.1f' % work_surf.kf)
		# 提取煤层数据到界面上
		self.ui.gas_w0.setText(u'%.1f' % coal.gas_w0)
		self.ui.gas_wc2.setText(u'%.1f' % coal.gas_wc2)

	def onSave(self):
		# 根据id查找工作面
		work_surf = SQLClientHelper.GetWorkSurfById(self.work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O1)!')
			return
		work_area = SQLClientHelper.GetWorkAreaById(work_surf.work_area_id)
		if work_area.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O2)!')
			return
		coal = SQLClientHelper.GetCoalById(work_area.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O3)!')
			return

		# 保存煤层瓦斯涌出量数据
		coal.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		coal.gas_wc2, ok = self.ui.gas_wc2.text().toDouble()
		# 提交到数据库
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O4)!')
			return
		# 保存工作面数据
		work_surf.k1, ok = self.ui.k1.text().toDouble()
		work_surf.k2, ok = self.ui.k2.text().toDouble()
		work_surf.k3, ok = self.ui.k3.text().toDouble()
		work_surf.kf, ok = self.ui.kf.text().toDouble()
		if not SQLClientHelper.UpdateWorkSurf(work_surf):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:O5)!')
		else:
			UiHelper.MessageBox(u'恭喜您,更新数据成功!')
		#关闭对话框并返回1
		# self.accept()

	def onK3Cacl(self):
		UiHelper.MessageBox(u'若无实测值点击自动弹出计算框!')

	def onKfCacl(self):
		UiHelper.MessageBox(u'若无实测值点击自动弹出计算框!')