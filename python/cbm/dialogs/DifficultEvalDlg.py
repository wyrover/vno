# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_difficult_eval_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class DifficultEvalDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(DifficultEvalDlg, self).__init__(parent)
		self.ui = Ui_difficult_eval_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"煤层气抽采难易程度评价")
		self.setFixedSize(self.width(), self.height())
		#在窗口上为"煤层渗透率"控件安装过滤器
		self.ui.permeability_k.installEventFilter(self)
		self.ui.permeability_lambda.installEventFilter(self) ##在窗口上为"透气性系数"控件安装过滤器
		self.ui.eval.clicked.connect(self.onEval)
		self.ui.cancel.clicked.connect(self.onCancel)
		self.ui.eval_proof_cacl.clicked.connect(self.onEvalProof)
		self.connect(self.ui.coal, QtCore.SIGNAL('currentIndexChanged(int)'), self.onCoalChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 填充煤层列表
		self.fillCoalCombox()

	def eventFilter(self, source, event):
		if source == self.ui.permeability_k:
			# "煤层渗透率"控件得到焦点
			if event.type() == QtCore.QEvent.FocusIn:
				# 根据"渗透率"计算"透气性系数"
				self.onPermeabilityKGetFocus()
		elif source == self.ui.permeability_lambda:
			# "透气性系数"控件得到焦点
			if event.type() == QtCore.QEvent.FocusIn:
				# 根据"透气性系数"计算"渗透率"
				self.onPermeabilityLambdaGetFocus()
		return super(DifficultEvalDlg, self).eventFilter(source, event)

	def onPermeabilityKGetFocus(self):
		# 根据"渗透率"计算"透气性系数"
		p_lambda, ok = self.ui.permeability_lambda.text().toDouble()
		p_k = DataHelper.permeability_lambda_to_k(p_lambda)
		# 更新计算结果
		self.ui.permeability_k.setText(u'%.2f' % p_k)

	def onPermeabilityLambdaGetFocus(self):
		# 根据"透气性系数"计算"渗透率"
		p_k, ok = self.ui.permeability_k.text().toDouble()
		p_lambda = DataHelper.permeability_k_to_lambda(p_k)
		# 更新计算结果
		self.ui.permeability_lambda.setText(u'%.2f' % p_lambda)

	def fillCoalCombox(self):
		# 清空煤层下拉列表
		self.ui.coal.clear()

		# 查找矿井辖属的煤层
		coal_lists = SQLClientHelper.GetCoalListByForeignKey('mine_id', self.mine_id)
		# 添加到煤层下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.coal, coal_lists)
	
	def onCoalChanged(self, index):
		if index < 0:return

		# 查询当前煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:return

		# 填充界面数据
		self.ui.permeability_k.setText(u'%.1f' % coal.permeability_k)
		self.ui.permeability_lambda.setText(u'%.1f' % coal.permeability_lambda)
		self.ui.decay_alpha.setText(u'%.1f' % coal.decay_alpha)
		self.ui.eval_difficult.setCurrentIndex(coal.eval_difficult-1)

	def onEval(self):
		index = self.ui.coal.currentIndex()
		if index < -1:return

		# 查询当前煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)
		if coal.id <= 0:return

		# 从界面读取数据
		coal.permeability_k, ok = self.ui.permeability_k.text().toDouble()
		coal.permeability_lambda, ok = self.ui.permeability_lambda.text().toDouble()
		coal.decay_alpha, ok = self.ui.decay_alpha.text().toDouble()
		coal.eval_difficult = self.ui.eval_difficult.currentIndex() + 1
		
		# 提交到数据库
		if SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'恭喜您,更新数据成功!!!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误代:F1)!')

	def onEvalProof(self):
		pass
		# UiHelper.MessageBox(u'尚未实现')
	
	def onCancel(self):
		self.reject()