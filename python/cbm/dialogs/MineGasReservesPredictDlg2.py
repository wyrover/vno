# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_mine_gas_reserves_predict_dlg2 import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class MineGasReservesPredictDlg2(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(MineGasReservesPredictDlg2, self).__init__(parent)
		self.ui = Ui_mine_gas_reserves_predict_dlg2()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"矿井可抽瓦斯量计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.cacl.clicked.connect(self.onCacl)		
		self.ui.ok.clicked.connect(self.onOk)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()
		# 外部传入的变量
		self.reserve_gas = 0.0
		self.pump_wc = 0.0

	def init(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:H1)!')
			return
		# 更新数据到界面
		self.ui.pump_k2.setText(u'%.1f' % mine.pump_k2)
		self.ui.pump_k3.setText(u'%.1f' % mine.pump_k3)
		self.ui.pump_k4.setText(u'%.1f' % mine.pump_k4)
		self.ui.gas_w0.setText(u'%.1f' % mine.gas_w0)
		self.ui.gas_wc2.setText(u'%.1f' % mine.gas_wc2)
		self.ui.pump_k.setText(u'%.1f' % mine.pump_k)
		self.ui.pump_k1.setText(u'%.1f' % mine.pump_k1)

	def onOk(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:I1)!')
			return
		
		# 更新数据到界面
		mine.pump_k2, ok = self.ui.pump_k2.text().toDouble()
		mine.pump_k3, ok = self.ui.pump_k3.text().toDouble()
		mine.pump_k4, ok = self.ui.pump_k4.text().toDouble()
		mine.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		mine.gas_wc2, ok = self.ui.gas_wc2.text().toDouble()
		mine.pump_k, ok = self.ui.pump_k.text().toDouble()
		mine.pump_k1, ok = self.ui.pump_k1.text().toDouble()		

		K2, K3, K4, My, Mc = mine.pump_k2, mine.pump_k3, mine.pump_k4, mine.gas_w0, mine.gas_wc2
		W = self.reserve_gas

		if My <= 0:
			UiHelper.MessageBox(u'煤层原始瓦斯含量My的值必须大于0!!!')
		else:
			# 计算可抽瓦斯量
			K1 = K4 * ( My - Mc ) / My
			Wc = K1 * K2 * K3 * W
			mine.pump_k = K1 * K2 * K3
			mine.pump_k1 = K1
			mine.pump_k2 = K2
			mine.pump_k3 = K3
			mine.pump_k4 = K4
			mine.pump_wc = Wc
			mine.gas_w0 = My
			mine.gas_wc2 = Mc

			# 提交到数据库
			if SQLClientHelper.UpdateMine(mine):
				# 更新外部传入的变量
				self.pump_wc = Wc
				UiHelper.MessageBox(u'恭喜您,更新数据成功!!!')
				# 关闭对话框并返回1
				self.accept()
			else:
				UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:I2)!')

	def onCacl(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:I1)!')
			return
		
		# 更新数据到界面(与onOk的代码有重复,逻辑有点混乱)
		mine.pump_k2, ok = self.ui.pump_k2.text().toDouble()
		mine.pump_k3, ok = self.ui.pump_k3.text().toDouble()
		mine.pump_k4, ok = self.ui.pump_k4.text().toDouble()
		mine.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		mine.gas_wc2, ok = self.ui.gas_wc2.text().toDouble()	 

		K2, K3, K4, My, Mc = mine.pump_k2, mine.pump_k3, mine.pump_k4, mine.gas_w0, mine.gas_wc2

		if My <= 0:
			UiHelper.MessageBox(u'煤层原始瓦斯含量My的值必须大于0!!!')
		else:
			# 计算瓦斯涌出程度系数K1
			K1 = K4 * ( My - Mc ) / My
			self.ui.pump_k1.setText(u'%.1f' % K1)
			# 计算可抽系数K
			K = K1 * K2 * K3
			self.ui.pump_k.setText(u'%.1f' % K)