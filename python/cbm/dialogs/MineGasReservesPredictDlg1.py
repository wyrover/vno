# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_mine_gas_reserves_predict_dlg1 import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class MineGasReservesPredictDlg1(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(MineGasReservesPredictDlg1, self).__init__(parent)
		self.ui = Ui_mine_gas_reserves_predict_dlg1()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"矿井瓦斯储量计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.w1_cacl.clicked.connect(self.onW1Cacl)
		self.ui.w2_cacl.clicked.connect(self.onW2Cacl)
		self.ui.w3_cacl.clicked.connect(self.onCacl)		
		self.ui.ok.clicked.connect(self.onOk)
		self.ui.cancel.clicked.connect(self.onCancel)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()
		# 外部传入的变量
		self.reserve_gas = 0.0

	def init(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:H1)!')
			return
		# 更新数据到界面
		self.ui.reserve_w1.setText(u'%.1f' % mine.reserve_w1)
		self.ui.reserve_w2.setText(u'%.1f' % mine.reserve_w2)
		self.ui.rock_gas_k2.setText(u'%.1f' % mine.rock_gas_k2)
		self.ui.reserve_w3.setText(u'%.1f' % mine.reserve_w3)

	def onOk(self):
		# 数据库中查找id对应的矿井
		mine = SQLClientHelper.GetMineById(self.mine_id)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:H1)!')
			return
		
		# 更新数据到界面
		mine.reserve_w1, ok = self.ui.reserve_w1.text().toDouble()
		mine.reserve_w2, ok = self.ui.reserve_w2.text().toDouble()
		mine.rock_gas_k2, ok = self.ui.rock_gas_k2.text().toDouble()
		mine.reserve_w3, ok = self.ui.reserve_w3.text().toDouble()

		# 计算W
		W1, W2, W3 = mine.reserve_w1, mine.reserve_w2, mine.reserve_w3
		W = W1 + W2 + W3
		mine.reserve_gas = W
		
		# 提交到数据库
		if SQLClientHelper.UpdateMine(mine):
			# 更新外部传入的变量
			self.reserve_gas = W
			UiHelper.MessageBox(u'恭喜您,更新数据成功!!!')
			# 关闭对话框并返回1
			self.accept()
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:H2)!')

	def onW1Cacl(self):
		pass
		# UiHelper.MessageBox(u'该功能尚未实现!')

	def onW2Cacl(self):
		pass
		# UiHelper.MessageBox(u'该功能尚未实现!')

	def onCacl(self):
		pass
		# UiHelper.MessageBox(u'该功能尚未实现!')

	def onCancel(self):
		# 关闭对话框并返回0
		self.reject()