# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_sample_manage import *

from TechModeDlg import *
from TechnologyDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

class SampleManageDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(SampleManageDlg, self).__init__(parent)
		self.ui = Ui_sample_manage()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"示范矿区技术库管理")
		self.setFixedSize(self.width(), self.height())	  
		self.ui.tech_mode.clicked.connect(self.onTechModeClick)
		self.ui.technology.clicked.connect(self.onTechnologyClick)
		self.connect(self.ui.region, QtCore.SIGNAL('currentIndexChanged(int)'), self.onMineRegionChanged)
		self.ui.save.clicked.connect(self.onSave)
		self.ui.mine_index_cacl.clicked.connect(self.onMineIndexCacl)
		self.ui.var_coeff_cacl.clicked.connect(self.onVarCoeffCacl)
		self.ui.czh_cacl.clicked.connect(self.onCzhCacl)
		self.ui.stability_cacl.clicked.connect(self.onStabilityCacl)
		self.ui.influence_factor_cacl.clicked.connect(self.onInfluenceFactorCacl)		
		# 待设计的矿井(本对话框不需要这个数据)
		# self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 激活示范矿区下拉列表框切换事件
		self.ui.region.setCurrentIndex(1)

	def onMineRegionChanged(self, index):
		if index < 0:return

		# 矿区名称
		region_name = unicode(self.ui.region.currentText()).encode('utf-8')
		# 根据示范矿区的名称反查内部的虚拟矿井和虚拟煤层
		mine = CbmClientHelper.GetSampleMineOfRegion(region_name)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:S1)!')
			return
		coal = CbmClientHelper.GetSampleCoalOfRegion(region_name)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:S2)!')
			return

		# 填充矿井数据
		self.ui.topo_geo.setCurrentIndex(mine.topo_geo-1)
		self.ui.hydr_geo.setCurrentIndex(mine.hydr_geo-1)
		self.ui.ground_cond.setChecked(mine.ground_condition != 0)

		# 填充煤层数据
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

	def onTechModeClick(self):
		dlg = TechModeDlg()
		dlg.exec_()

	def onTechnologyClick(self):
		dlg = TechnologyDlg()
		dlg.exec_()

	def onSave(self):
		# 矿区名称
		region_name = unicode(self.ui.region.currentText()).encode('utf-8')
		# 根据示范矿区的名称反查内部的虚拟矿井和虚拟煤层
		mine = CbmClientHelper.GetSampleMineOfRegion(region_name)
		if mine.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:S3)!')
			return
		coal = CbmClientHelper.GetSampleCoalOfRegion(region_name)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:S4)!')
			return

		# 保存矿井数据
		mine.topo_geo = self.ui.topo_geo.currentIndex() + 1
		mine.hydr_geo = self.ui.hydr_geo.currentIndex() + 1
		mine.ground_condition = int(self.ui.ground_cond.isChecked())
		if not SQLClientHelper.UpdateMine(mine):
			UiHelper.MessageBox(u'更新矿井数据失败(错误码:S5)!')
			return

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
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'更新煤层数据失败(错误码:S6)!')
			#关闭对话框并返回1
			# self.accept()
		else:
			UiHelper.MessageBox(u'恭喜您,数据更新成功啦!')