#coding:utf-8

from BaseDialog import *
from uipy.ui_pore_flow_dlg import *

from PoreFlowKDlg import *
# from PoreFlowbDlg import *
from PoreFlowDeltaPDlg import *
# from PoreFlowDeltaTDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import sqrt, pow, sin, cos, tan, radians

class PoreFlowDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(PoreFlowDlg, self).__init__(parent)
		self.ui = Ui_pore_flow_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"孔板流量计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cacl.clicked.connect(self.onCacl)
		self.ui.k_cacl.clicked.connect(self.onKCacl)
		self.ui.b_cacl.clicked.connect(self.onBCacl)
		self.ui.delta_p_cacl.clicked.connect(self.onDeltaPCacl)
		self.ui.delta_t_cacl.clicked.connect(self.onDeltaTCacl)
		# 待设计的矿井
		self.mine_id = mine_id
		# 待设计的钻孔流量对象
		# self.pore_flow.id = -1
		self.pore_flow = PoreFlow()
		# 初始化
		self.init()
	
	def init(self):
		# 初始化孔板流量对象id
		self.initPoreFlow()
		if self.pore_flow.id <= 0:return

		# 根据id查询数据对象
		pore_flow = SQLClientHelper.GetPoreFlowById(self.pore_flow.id)

		# 读取数据到界面
		self.ui.t.setText(u'%.1f' % pore_flow.t)
		self.ui.dh.setText(u'%.1f' % pore_flow.dh)
		self.ui.x.setText(u'%.1f' % pore_flow.x)
		self.ui.k.setText(u'%.1f' % pore_flow.k)
		self.ui.b.setText(u'%.1f' % pore_flow.b)
		self.ui.delta_p.setText(u'%.1f' % pore_flow.delta_p)
		self.ui.delta_t.setText(u'%.1f' % pore_flow.delta_t)
		self.ui.q_hun.setText(u'%.1f' % pore_flow.q_hun)
		self.ui.q_chun.setText(u'%.1f' % pore_flow.q_chun)

	def initPoreFlow(self):
		# 查找所有的抽采管径对象
		pore_flow_lists = SQLClientHelper.GetPoreFlowList()
		if len(pore_flow_lists) == 0:
			pore_flow = PoreFlow()
			pore_flow_id = SQLClientHelper.AddPoreFlow(pore_flow)
			self.pore_flow = SQLClientHelper.GetPoreFlowById(pore_flow_id)
		else:
			# 目前只使用第1个数据
			self.pore_flow = pore_flow_lists[0]

	def onSave(self):
		# 获取孔板流量计算对象
		if self.pore_flow.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题, 请联系技术人员(错误码:V2)')
			return

		# pore_flow = SQLClientHelper.GetPoreFlowById(self.pore_flow.id)
		pore_flow = self.pore_flow

		# 从界面读取数据
		pore_flow.t, ok = self.ui.t.text().toDouble()
		pore_flow.dh, ok = self.ui.dh.text().toDouble()
		pore_flow.x, ok = self.ui.x.text().toDouble()
		pore_flow.k, ok = self.ui.k.text().toDouble()
		pore_flow.b, ok = self.ui.b.text().toDouble()
		pore_flow.delta_p, ok = self.ui.delta_p.text().toDouble()
		pore_flow.delta_t, ok = self.ui.delta_t.text().toDouble()
		pore_flow.q_hun, ok = self.ui.q_hun.text().toDouble()
		pore_flow.q_chun, ok = self.ui.q_chun.text().toDouble()

		# 保存到数据库
		if SQLClientHelper.UpdatePoreFlow(pore_flow):
			UiHelper.MessageBox(u'恭喜您,更新数据成功!')
		else:
			UiHelper.MessageBox(u'sorry, 出了点问题, 请联系技术人员(错误码:V1)')

		#做保存操作
		# self.accept()

	def onCacl(self):
		# 从界面中提取数据
		k, ok = self.ui.k.text().toDouble()
		b, ok = self.ui.b.text().toDouble()
		delta_p, ok = self.ui.delta_p.text().toDouble()
		delta_t, ok = self.ui.delta_t.text().toDouble()
		dh, ok = self.ui.dh.text().toDouble()
		x, ok = self.ui.x.text().toDouble()
		# 计算
		q_hun = k * b * sqrt(dh) * delta_p * delta_t
		q_chun = q_hun * x
		# 更新到界面
		self.ui.q_hun.setText(u'%.1f' % q_hun)
		self.ui.q_chun.setText(u'%.1f' % q_chun)

	def onKCacl(self):
		# 获取孔板流量计算对象
		# pore_flow = SQLClientHelper.GetPoreFlowById(self.pore_flow.id)
		pore_flow = self.pore_flow
		if pore_flow.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题, 请联系技术人员(错误码:V2)')
			return

		# 弹出对话框计算
		dlg = PoreFlowKDlg(pore_flow)
		dlg.exec_()
		# 更新到界面
		self.ui.k.setText(u'%.1f' % pore_flow.k)

	def onBCacl(self):
		# 从界面中提取X
		x, ok = self.ui.x.text().toDouble()
		# 计算b值
		b = 1.0 / sqrt(1-0.00446*x)
		# 更新到界面
		self.ui.b.setText(u'%.1f' % b)

	def onDeltaPCacl(self):
		# pore_flow = SQLClientHelper.GetPoreFlowById(self.pore_flow.id)
		pore_flow = self.pore_flow
		if pore_flow.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题, 请联系技术人员(错误码:V2)')
			return

		# 弹出对话框计算
		dlg = PoreFlowDeltaPDlg(pore_flow)
		dlg.exec_()
		# 更新到界面
		self.ui.delta_p.setText(u'%.1f' % pore_flow.delta_p)

	def onDeltaTCacl(self):
		# 从界面中提取t
		t, ok = self.ui.t.text().toDouble()
		# 计算deta_t
		delta_t = 293.0 / (273 + t)
		# 更新到界面
		self.ui.delta_t.setText(u'%.1f' % delta_t)
