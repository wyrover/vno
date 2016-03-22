# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_tws_gas_flow_predict_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper
from math import exp

class TwsGasFlowPredictDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(TwsGasFlowPredictDlg, self).__init__(parent)
		self.ui = Ui_tws_gas_flow_predict_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"掘进工作面瓦斯涌出量")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.wc_cacl.clicked.connect(self.onWcCacl)
		self.ui.cacl.clicked.connect(self.onCacl)
		self.connect(self.ui.drilling_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onDrillingSurfChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 填充掘进面列表
		self.fillDrillingSurfCombox()

	def fillDrillingSurfCombox(self):
		# 填充掘进面列表
		drilling_surf_lists = CbmClientHelper.GetDrillingSurfsOfMine(self.mine_id)
		# 添加到掘进面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.drilling_surf, drilling_surf_lists)

	def onDrillingSurfChanged(self, index):
		drilling_surf_id, ok = self.ui.drilling_surf.itemData(index).toInt()
		drilling_surf = SQLClientHelper.GetDrillingSurfById(drilling_surf_id)
		if drilling_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G1)!')
			return

		# 填充掘进面的数据
		self.ui.q4.setText(u'%.1f' % drilling_surf.q4)
		self.ui.qa.setText(u'%.1f' % drilling_surf.qa)

		# 填充煤层数据
		work_area_id = drilling_surf.work_area_id
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)
		if work_area.id  <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G2)!')
			return
		coal_id = work_area.coal_id
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G3)!')
			return

		# 填充煤层数据
		self.ui.vr.setText(u'%.1f' % coal.vr)
		self.ui.rho.setText(u'%.1f' % coal.rho)
		self.ui.gas_w0.setText(u'%.1f' % coal.gas_w0)
		self.ui.gas_wc2.setText(u'%.1f' % coal.gas_wc2)

		# 填充掘进巷道数据
		tunnel_id = drilling_surf.tunnel_id
		if tunnel_id <= 0:
			self.ui.d.setText(u'0.0')
			self.ui.v.setText(u'0.0')
			self.ui.l.setText(u'0.0')
			self.ui.s.setText(u'0.0')
			self.ui.q0.setText(u'0.0')
			self.ui.q3.setText(u'0.0')
		else:
			tunnel = SQLClientHelper.GetTunnelById(tunnel_id)
			self.ui.d.setText(u'%.1f' % tunnel.d)
			self.ui.v.setText(u'%.1f' % tunnel.v)
			self.ui.l.setText(u'%.1f' % tunnel.l)
			self.ui.s.setText(u'%.1f' % tunnel.s)
			self.ui.q0.setText(u'%.1f' % tunnel.q0)
			self.ui.q3.setText(u'%.1f' % tunnel.q3)

	def onSave(self):
		index = self.ui.drilling_surf.currentIndex()
		if index < 0:return

		drilling_surf_id, ok = self.ui.drilling_surf.itemData(index).toInt()
		drilling_surf = SQLClientHelper.GetDrillingSurfById(drilling_surf_id)
		if drilling_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G4)!')
			return

		# 保存煤层数据
		work_area_id = drilling_surf.work_area_id
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)
		if work_area.id  <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G9)!')
			return		
		coal_id = work_area.coal_id
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G5)!')
			return

		# 保存掘进巷道数据
		tunnel = SQLClientHelper.GetTunnelById(drilling_surf.tunnel_id)
		tunnel_id = tunnel.id
		if tunnel_id <= 0:
			# 新建一条巷道,提交到数据库得到id
			tunnel = Tunnel()
			tunnel_id = SQLClientHelper.AddTunnel(tunnel)
		# 更新掘进面关联的掘进巷道id
		drilling_surf.tunnel_id = tunnel_id
		# 从界面中读取掘进巷道的数据
		tunnel.d, ok = self.ui.d.text().toDouble()
		tunnel.v, ok = self.ui.v.text().toDouble()
		tunnel.l, ok = self.ui.l.text().toDouble()
		tunnel.s, ok = self.ui.s.text().toDouble()
		tunnel.q0, ok = self.ui.q0.text().toDouble()
		tunnel.q3, ok = self.ui.q3.text().toDouble()

		# 从界面中读取掘进面数据
		drilling_surf.q4, ok = self.ui.q4.text().toDouble()
		drilling_surf.qa, ok = self.ui.qa.text().toDouble()

		# 从界面中读取煤层数据
		coal.vr, ok = self.ui.vr.text().toDouble()
		coal.rho, ok = self.ui.rho.text().toDouble()
		coal.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		coal.gas_wc2, ok = self.ui.gas_wc2.text().toDouble()

		# 提交到数据库
		if not SQLClientHelper.UpdateDrillingSurf(drilling_surf):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G6)!')
			return
		if not SQLClientHelper.UpdateTunnel(tunnel):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G7)!')
			return
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G8)!')
			return
		#关闭对话框并返回1
		# self.accept()
		UiHelper.MessageBox(u'恭喜您,更新数据成功啦!')

	def onWcCacl(self):
		index = self.ui.drilling_surf.currentIndex()
		if index < 0:return

		drilling_surf_id, ok = self.ui.drilling_surf.itemData(index).toInt()
		drilling_surf = SQLClientHelper.GetDrillingSurfById(drilling_surf_id)
		if drilling_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G11)!')
			return

		# 保存煤层数据
		work_area_id = drilling_surf.work_area_id
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)
		if work_area.id  <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G12)!')
			return		
		coal_id = work_area.coal_id
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G13)!')
			return

		# 查看煤质
		if coal.quality < 3 or caol.gas_w0 > 10:
			pass
			# UiHelper.MessageBox(u'弹出对话框让用户选择(尚未实现)')
		else:
			# 通过经验公式计算
			W0 = coal.gas_w0
			Wc = 10.385*exp(-7.207*W0)
			coal.gas_wc2 = Wc
		# 更新到界面
		self.ui.gas_wc2.setText(u'%.1f' % coal.gas_wc2)

	def onCacl(self):
		index = self.ui.drilling_surf.currentIndex()
		if index < 0:return

		drilling_surf_id, ok = self.ui.drilling_surf.itemData(index).toInt()
		drilling_surf = SQLClientHelper.GetDrillingSurfById(drilling_surf_id)
		if drilling_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G14)!')
			return

		# 保存煤层数据
		work_area_id = drilling_surf.work_area_id
		work_area = SQLClientHelper.GetWorkAreaById(work_area_id)
		if work_area.id  <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G15)!')
			return		
		coal_id = work_area.coal_id
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G16)!')
			return

		# 保存掘进巷道数据
		tunnel = SQLClientHelper.GetTunnelById(drilling_surf.tunnel_id)
		tunnel_id = tunnel.id
		if tunnel_id <= 0:
			# 新建一条巷道
			tunnel = Tunnel()

		# 更新掘进面关联的掘进巷道id
		drilling_surf.tunnel_id = tunnel_id
		# 从界面中读取掘进巷道的数据
		tunnel.d, ok = self.ui.d.text().toDouble()
		tunnel.v, ok = self.ui.v.text().toDouble()
		tunnel.l, ok = self.ui.l.text().toDouble()
		tunnel.s, ok = self.ui.s.text().toDouble()
		tunnel.q0, ok = self.ui.q0.text().toDouble()
		tunnel.q3, ok = self.ui.q3.text().toDouble()

		# 从界面中读取掘进面数据
		drilling_surf.q4, ok = self.ui.q4.text().toDouble()
		drilling_surf.qa, ok = self.ui.qa.text().toDouble()

		# 从界面中读取煤层数据
		coal.vr, ok = self.ui.vr.text().toDouble()
		coal.rho, ok = self.ui.rho.text().toDouble()
		coal.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		coal.gas_wc2, ok = self.ui.gas_wc2.text().toDouble()

		# 数据检查
		if tunnel.v <= 0:
			UiHelper.MessageBox(u'巷道掘进速度v必须取大于0的值')
			return

		# 调用rpc计算掘进面瓦斯涌出量
		ret = CbmClientHelper.DrillingSurfGasFlow(coal, drilling_surf, tunnel)
		# 计算结果更新到界面
		tunnel.q0 = ret.q0
		tunnel.q3 = ret.q3
		drilling_surf.q4 = ret.q4
		drilling_surf.qa = ret.qa
		UiHelper.MessageBox(u'数据计算成功,请查看"瓦斯涌出量预测结果"部分的数据!')