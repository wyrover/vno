# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_coal_design_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class CoalDesignDlg(BaseDialog):
	def __init__(self, coal_id=-1, parent=None):
		super(CoalDesignDlg, self).__init__(parent)
		self.ui = Ui_coal_design_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"煤层设计")
		self.setFixedSize(self.width(),self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cancel.clicked.connect(self.onCancel)
		self.ui.mine_index_cacl.clicked.connect(self.onMineIndexCacl)
		self.ui.var_coeff_cacl.clicked.connect(self.onVarCoeffCacl)
		self.ui.czh_cacl.clicked.connect(self.onCzhCacl)
		self.ui.stability_cacl.clicked.connect(self.onStabilityCacl)
		self.ui.influence_factor_cacl.clicked.connect(self.onInfluenceFactorCacl)
		# 待设计的煤层id
		self.coal_id = coal_id
		# 初始化
		self.init()

	def init(self):
		if self.coal_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:C2)!')
			return

		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:return

		self.ui.thick.setText(u'%.1f' % coal.thick)
		self.ui.rank.setCurrentIndex(coal.rank-1)
		self.ui.minable.setChecked(coal.minable != 0)
		self.ui.dip_angle.setText(u'%.1f' % coal.dip_angle)
		self.ui.hw.setText(u'%.1f' % coal.hw)
		self.ui.f_value.setText(u'%.2f' % coal.f_value)
		self.ui.pressure.setText(u'%.1f' % coal.pressure)
		self.ui.gas_content.setText(u'%.1f' % coal.gas_content)
		self.ui.permeability_k.setText(u'%.1f' % coal.permeability_k)
		self.ui.res_abundance.setCurrentIndex(coal.res_abundance - 1)
		self.ui.complexity.setCurrentIndex(coal.complexity - 1)
		self.ui.mine_index.setText(u'%.1f' % coal.mine_index)
		self.ui.var_coeff.setText(u'%.1f' % coal.var_coeff)
		self.ui.caving_zone_height.setText(u'%.1f' % coal.czh)
		self.ui.stability.setCurrentIndex(coal.stability - 1)
		self.ui.layer_gap.setText(u'%.1f' % coal.layer_gap)
		self.ui.influence_factor.setText(u'%.1f' % coal.influence_factor)

	def onMineIndexCacl(self):
		pass
		# UiHelper.MessageBox(u'尚未实现')

	def onVarCoeffCacl(self):
		pass
		# UiHelper.MessageBox(u'尚未实现')

	def onCzhCacl(self):
		pass
		# UiHelper.MessageBox(u'尚未实现')
	
	def onStabilityCacl(self):
		pass
		# UiHelper.MessageBox(u'尚未实现')
	
	def onInfluenceFactorCacl(self):
		pass
		# UiHelper.MessageBox(u'尚未实现')

	def onSave(self):
		if self.coal_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:C3)!')
			return
		
		# 根据id查找煤层
		coal = SQLClientHelper.GetCoalById(self.coal_id)

		# 读取界面上的数据保存到煤层对象
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.rank = self.ui.rank.currentIndex() + 1
		coal.minable = int(self.ui.minable.isChecked())
		coal.dip_angle, ok = self.ui.dip_angle.text().toDouble()
		coal.hw, ok = self.ui.hw.text().toDouble()
		coal.f_value, ok = self.ui.f_value.text().toDouble()
		coal.pressure, ok = self.ui.pressure.text().toDouble()
		coal.gas_content, ok = self.ui.gas_content.text().toDouble()
		coal.permeability_k, ok = self.ui.permeability_k.text().toDouble()
		coal.res_abundance = self.ui.res_abundance.currentIndex() + 1
		coal.complexity = self.ui.complexity.currentIndex() + 1
		coal.mine_index, ok = self.ui.mine_index.text().toDouble()
		coal.var_coeff, ok = self.ui.var_coeff.text().toDouble()
		coal.czh, ok = self.ui.caving_zone_height.text().toDouble()
		coal.stability = self.ui.stability.currentIndex() + 1
		coal.layer_gap, ok = self.ui.layer_gap.text().toDouble()
		coal.influence_factor, ok = self.ui.influence_factor.text().toDouble()

		# 提交到数据库
		if SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'更新煤层数据成功!')
			#关闭对话框并返回1
			# self.accept()
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:C1)!')

	def onCancel(self):
		# 关闭对话框并返回0
		self.reject()