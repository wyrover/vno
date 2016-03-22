# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_mine_gas_reserves_predict_dlg import *

from CoalParamDlg import *
from MineGasReservesPredictDlg1 import *
from MineGasReservesPredictDlg2 import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class MineGasReservesPredictDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(MineGasReservesPredictDlg, self).__init__(parent)
		self.ui = Ui_mine_gas_reserves_predict_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"矿井瓦斯储量及可抽量预测")
		self.setFixedSize(self.width(), self.height())
		self.ui.gas_cacl.clicked.connect(self.onGasCacl)
		self.ui.pump_wc_cacl.clicked.connect(self.onPumpWcCacl)
		self.ui.ok.clicked.connect(self.onOk)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G1)!')
			return
		# 更新数据到界面
		self.ui.reserve_gas.setText(u'%.1f' % mine.reserve_gas)
		self.ui.pump_wc.setText(u'%.1f' % mine.pump_wc)

	def onOk(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:G1)!')
			return
		# 更新数据到界面
		mine.reserve_gas, ok = self.ui.reserve_gas.text().toDouble()
		mine.pump_wc, ok = self.ui.pump_wc.text().toDouble()

		if SQLClientHelper.UpdateMine(mine):
			UiHelper.MessageBox(u'恭喜您,更新数据成功!!!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:D1)!')
		# 关闭对话框并返回1
		# self.accept()

	def onGasCacl(self):
		dlg = MineGasReservesPredictDlg1(self.mine_id)
		# 传入数据
		dlg.reserve_gas, ok = self.ui.reserve_gas.text().toDouble()
		dlg.exec_()
		# 更新计算结果到界面
		self.ui.reserve_gas.setText(u'%.1f' % dlg.reserve_gas)

	def onPumpWcCacl(self):
		dlg = MineGasReservesPredictDlg2(self.mine_id)
		# 传入数据
		dlg.reserve_gas, ok = self.ui.reserve_gas.text().toDouble()
		dlg.pump_wc, ok = self.ui.pump_wc.text().toDouble()
		dlg.exec_()
		# 更新计算结果到界面
		self.ui.pump_wc.setText(u'%.1f' % dlg.pump_wc)
