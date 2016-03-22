# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_ws_gas_flow_predict_adj_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class WsGasFlowPredictAdjDlg(BaseDialog):
	def __init__(self, work_surf_id=-1, parent=None):
		super(WsGasFlowPredictAdjDlg, self).__init__(parent)
		self.ui = Ui_ws_gas_flow_predict_adj_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"邻近层相对瓦斯涌出量q2计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cancel.clicked.connect(self.onCancel)
		self.ui.add_adj_layer.clicked.connect(self.onAddAdjLayer)
		self.ui.del_adj_layer.clicked.connect(self.onDelAdjLayer)
		self.ui.eta_cacl.clicked.connect(self.onEtaCacl)
		self.connect(self.ui.adj_layer, QtCore.SIGNAL('currentIndexChanged(int)'), self.onAdjLayerChanged)		
		# 待设计的工作面
		self.work_surf_id = work_surf_id
		# 初始化
		self.init()

	def init(self):
		# 填充邻近层列表
		self.fillAdjLayerCombox()

	def fillAdjLayerCombox(self):
		# 查找所有的邻近层
		adj_layer_lists = SQLClientHelper.GetAdjLayerListByForeignKey('work_surf_id', self.work_surf_id)
		# 添加到邻近层下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.adj_layer, adj_layer_lists)

	def onAdjLayerChanged(self, index):
		# 根据id查找当前邻近层
		if index < 0:return
		adj_layer_id, ok = self.ui.adj_layer.itemData(index).toInt()
		if adj_layer_id <= 0:return
		adj_layer = SQLClientHelper.GetAdjLayerById(adj_layer_id)
		
		# 查找邻近层关联的煤层
		coal_id = adj_layer.coal_id
		if coal_id <= 0:return
		coal = SQLClientHelper.GetCoalById(coal_id)

		# 更新煤层数据到界面上
		self.ui.thick.setText(u'%.1f' % coal.thick)
		self.ui.gas_eta.setText(u'%.1f' % coal.gas_eta)
		self.ui.gas_w0.setText(u'%.1f' % coal.gas_w0)
		self.ui.gas_wc2.setText(u'%.1f' % coal.gas_wc2)

		# 更新邻近层数据到界面上
		self.ui.h.setText(u'%.1f' % adj_layer.h)
		self.ui.hp.setText(u'%.1f' % adj_layer.hp)
		self.ui.in_cz.setChecked(adj_layer.in_cz != 0)

	def onSave(self):
		index = self.ui.adj_layer.currentIndex()
		if index < 0:return

		adj_layer_id, ok = self.ui.adj_layer.itemData(index).toInt()
		adj_layer = SQLClientHelper.GetAdjLayerById(adj_layer_id)
		if adj_layer.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:P1)!')
			return

		# 得到邻近层关联的煤层
		coal_id = adj_layer.coal_id
		coal = None
		if coal_id <= 0:
			coal = Coal()
		else:
			coal = SQLClientHelper.GetCoalById(coal_id)
		# 读取界面数据到煤层
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.gas_eta, ok = self.ui.gas_eta.text().toDouble()
		coal.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		coal.gas_wc2, ok = self.ui.gas_wc2.text().toDouble()

		# 保存煤层到数据库(如果煤层为空)
		if coal_id <= 0:
			coal_id = SQLClientHelper.AddCoal(coal)
		if coal_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:P2)!')
			return
		else:
			adj_layer.coal_id = coal_id
			adj_layer.hp, ok = self.ui.hp.text().toDouble()
			adj_layer.h, ok = self.ui.h.text().toDouble()
			adj_layer.in_cz = int(self.ui.in_cz.isChecked())

		# 保存煤层到数据库
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'更新邻近层数据失败!')
			return

		# 保存邻近层到数据库
		if not SQLClientHelper.UpdateAdjLayer(adj_layer):
			UiHelper.MessageBox(u'更新邻近层数据失败!')
		else:
			UiHelper.MessageBox(u'更新邻近层数据成功!')

		# 关闭对话框并返回1
		# self.accept()

	def onAddAdjLayer(self):
		# 弹出名称对话框,获取名称
		name = unicode(UiHelper.GetNameFromDlg(u"新增邻近层"))
		if name == u'null':
			UiHelper.MessageBox(u"请输入有效的名称！")
			return
		
		# 新建邻近层,并提交到数据库
		adj_layer = AdjLayer()
		adj_layer.name = name.encode('utf-8')
		adj_layer.work_surf_id = self.work_surf_id
		# 新建煤层(要邻近层关联),提交到数据库获得煤层id
		coal = Coal()
		# 读取界面数据到煤层(这里是为了防止出现None导致计算失败!!)
		# 如果采用其它语言实现,可以不需要这段代码
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.gas_eta, ok = self.ui.gas_eta.text().toDouble()
		coal.gas_w0, ok = self.ui.gas_w0.text().toDouble()
		coal.gas_wc2, ok = self.ui.gas_wc2.text().toDouble()
		print '---------------->:',coal.gas_w0,'----:',coal.gas_wc2
		coal_id = SQLClientHelper.AddCoal(coal)
		if coal_id <= 0:
			UiHelper.MessageBox(u"新增邻近层失败")
			return

		# 新建邻近层与新建煤层关联在一起,并提交到数据库
		adj_layer.coal_id = coal_id
		adj_layer.hp, ok = self.ui.hp.text().toDouble()
		adj_layer.h, ok = self.ui.h.text().toDouble()
		adj_layer.in_cz = int(self.ui.in_cz.isChecked())
		adj_layer_id = SQLClientHelper.AddAdjLayer(adj_layer)
		if adj_layer_id <= 0:
			# 删除之前新增的煤层
			SQLClientHelper.DeleteCoal(coal_id)
			UiHelper.MessageBox(u"新增邻近层失败")
		else:
			# 添加到邻近层下拉列表
			index = UiHelper.AddItemToCombobox(self.ui.adj_layer, name, adj_layer_id)
			# 切换到新增item
			self.ui.adj_layer.setCurrentIndex(index)
			UiHelper.MessageBox(u'新增邻近层成功!')

	def onDelAdjLayer(self):
		index = self.ui.adj_layer.currentIndex()
		if index < 0:return

		adj_layer_id, ok = self.ui.adj_layer.itemData(index).toInt()

		# 从数据库中删除邻近层关联的煤层
		# adj_layer = SQLClientHelper.GetAdjLayerById(adj_layer_id)
		# if adj_layer.coal_id <= 0:
		# 从数据库中删除邻近层(与之关联的煤层是否也需要删除???)
		if SQLClientHelper.DeleteAdjLayer(adj_layer_id):
			# 从邻近层列表中删除
			self.ui.adj_layer.removeItem(index)
		else:
			UiHelper.MessageBox(u'删除邻近层失败!')

	def onEtaCacl(self):
		pass
		# UiHelper.MessageBox(u'自动弹出计算框(尚未实现该功能)')
	
	def onCancel(self):
		# 关闭对话框并返回0
		self.reject()