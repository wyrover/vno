# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_gas_design_dlg import *

from GasDesignP11Dlg import *
from GasDesignP12Dlg import *
from GasDesignP21Dlg import *
from GasDesignP23Dlg import *
from GasDesignP32Dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper

def RunGasDesignDlg(coal_id, region, which_tech, design_id):
	if region <= 0 or design_id <= 0:
		return False

	dlg = None
	if region == 1:
		if which_tech == 1:
			dlg = GasDesignP11Dlg(coal_id, design_id)
		elif which_tech == 2:
			dlg = GasDesignP12Dlg(coal_id, design_id)
		else:
			pass
	elif region == 2:
		if which_tech == 1:
			dlg = GasDesignP21Dlg(coal_id, design_id)
		elif which_tech == 2:
			pass
		elif which_tech == 3:
			dlg = GasDesignP23Dlg(coal_id, design_id)
		else:
			pass
	elif region == 3:
		if which_tech == 1:
			pass
		elif which_tech == 2:
			dlg = GasDesignP32Dlg(coal_id, design_id)
		elif which_tech == 3:
			pass
		else:
			pass
	
	ret = dlg is not None
	if ret:
		# 启动对话框
		dlg.exec_()
	# 返回值
	return ret

# 技术列表
gas_technologies = {
	1 : [
		u'底板岩巷密集穿层钻孔抽采煤巷条带瓦斯',
		u'顺层钻孔条带掩护巷道掘进抽采法',
		u'单巷、双巷或多巷循环迈步式抽采技术'
	],
	2 : [
		u'底板岩巷大面积穿层钻孔抽采工作面瓦斯',
		u'顺层钻孔递进式掩护抽采工作面瓦斯法',
		u'顺层平行钻孔抽采工作面瓦斯',
		u'顺层交叉钻孔抽采工作面瓦斯',
		u'千米钻机定向长钻孔抽采法'
	],
	3 : [
		u'高抽巷卸压瓦斯抽采法',
		u'顶板高位走向钻孔瓦斯抽采法',
		u'沿空留巷穿层钻孔抽采',
		u'采空区埋管瓦斯抽采方法'
	]
}

class GasDesignDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(GasDesignDlg, self).__init__(parent)
		self.ui = Ui_gas_design_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui)
		self.setTitle(u"煤层气抽采技术辅助设计")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.go.clicked.connect(self.onGo)
		self.ui.add_design.clicked.connect(self.onAddDesign)
		self.ui.del_design.clicked.connect(self.onDelDesign)
		self.connect(self.ui.coal, QtCore.SIGNAL('currentIndexChanged(int)'), self.onCoalChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 该变量从外部读进来(设计的不是太好,滥用了全局变量了)
		self.region = DataHelper.GAS_DESIGN_REGION
		# 初始化
		self.init()

	def init(self):
		# 填充煤层列表
		self.fillCoalCombox()
		# 填充技术列表
		self.fillTechnologyList()

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
		self.ui.thick.setText(u'%.1f' % coal.thick)
		self.ui.dip_angle.setText(u'%.1f' % coal.dip_angle)

		# 填充设计方案
		self.fillDesignCombox(coal_id)

	def fillTechnologyList(self):
		# 清空技术列表
		self.ui.technology.clear()
		if self.region not in gas_technologies:
			return
		# 根据设计区域填充不同的技术列表
		for tech in gas_technologies[self.region]:
			self.ui.technology.addItem(tech)

	def fillDesignCombox(self, coal_id):
		# 清空设计方案列表
		self.ui.design.clear()

		# 查找设计技术
		tech_lists = SQLClientHelper.GetDesignTechnologyListByField2('coal_id', str(coal_id), 'region', self.region)
		if len(tech_lists) == 0:return

		# 查询与设计技术关联的详细设计技术方案
		design_tech_list = []
		for tech in tech_lists:
			tech_id = tech.id
			if tech_id <= 0:continue
			
			design_tech = None
			# 查询
			if self.region == 1:
				design_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyByForeignKey('design_technology_id', tech_id)
			elif self.region == 2:
				design_tech = SQLClientHelper.GetDesignWorkSurfTechnologyByForeignKey('design_technology_id', tech_id)
			elif self.region == 3:
				design_tech = SQLClientHelper.GetDesignGoafTechnologyByForeignKey('design_technology_id', tech_id)
			
			# 添加到数组
			if design_tech is None or design_tech.id <= 0:
				continue
			else:
				design_tech_list.append(design_tech)

		# 添加到列表中
		UiHelper.AddObjectListToCombobox(self.ui.design, design_tech_list)

	def onAddDesign(self):
		if self.region not in [1,2,3]:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:104)')
			return
		index = self.ui.coal.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:105)')
			return
		
		# 查找当前煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)

		name = unicode(UiHelper.GetNameFromDlg(u'新增抽采设计方案'))
		if name == u'' or name == u'null':
			UiHelper.MessageBox('请输入有效的名字')
			return

		if self.ui.design.findText(name) > -1:
			UiHelper.MessageBox(u'设计方案名称:%s已存在，换一个吧' % name)
			return

		# 新建设计技术
		tech = DesignTechnology()
		tech.region = self.region
		tech.coal_id = coal_id
		tech_id = SQLClientHelper.AddDesignTechnology(tech)
		if tech_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:103)')
			return

		# 新增与设计技术关联的详细设计技术方案
		design_tech_id = -1
		if self.region == 1:
			design_tech = DesignDrillingSurfTechnology()
			design_tech.name = name.encode('utf-8')
			design_tech.design_technology_id = tech_id
			design_tech_id = SQLClientHelper.AddDesignDrillingSurfTechnology(design_tech)
		elif self.region == 2:
			design_tech = DesignWorkSurfTechnology()
			design_tech.name = name.encode('utf-8')
			design_tech.design_technology_id = tech_id
			design_tech_id = SQLClientHelper.AddDesignWorkSurfTechnology(design_tech)
		elif self.region == 3:
			design_tech = DesignGoafTechnology()
			design_tech.name = name.encode('utf-8')
			design_tech.design_technology_id = tech_id
			design_tech_id = SQLClientHelper.AddDesignGoafTechnology(design_tech)
		
		# 添加到列表中
		if design_tech_id > 0:
			index = UiHelper.AddItemToCombobox(self.ui.design, name, design_tech_id)
  			# 切换到新增item
  			self.ui.design.setCurrentIndex(index)
			UiHelper.MessageBox(u'新增设计方案数据成功!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:104)')

	def onDelDesign(self):
		index = self.ui.design.currentIndex()
		if index < 0:return

		# 从数据库中删除
		design_tech_id, ok = self.ui.design.itemData(index).toInt()
		design_tech = None
		if self.region == 1:
			design_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(design_tech_id)
		elif self.region == 2:
			design_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(design_tech_id)
		elif self.region == 3:
			design_tech = SQLClientHelper.GetDesignGoafTechnologyById(design_tech_id)

		ret = False
		if design_tech is None or design_tech.id <= 0:
			pass
		else:
			# 外键的级联规则可以保证关联的详细设计方案以及钻场和钻孔都被删除掉!!!
			ret = SQLClientHelper.DeleteDesignTechnology(design_tech.design_technology_id)
		
		# 从列表中删除
		if ret:
			self.ui.design.removeItem(index)
			UiHelper.MessageBox(u'删除设计方案成功!')
		else:
			UiHelper.MessageBox(u'删除设计方案失败!')

	def onSave(self):
		index = self.ui.coal.currentIndex()
		if index < 0:return
		
		# 根据id查找煤层
		coal_id, ok = self.ui.coal.itemData(index).toInt()
		coal = SQLClientHelper.GetCoalById(coal_id)

		# 读取界面上的数据保存到煤层对象
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.dip_angle, ok = self.ui.dip_angle.text().toDouble()

		# 提交到数据库
		if SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'更新煤层数据成功!')
			#关闭对话框并返回1
			# self.accept()
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:101)!')

	def onGo(self):
		if self.region <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:102)')
			return
		coal_index = self.ui.coal.currentIndex()
		if coal_index < 0:
			UiHelper.MessageBox(u"请选择煤层！")
			return
		which_tech = self.ui.technology.currentRow()
		if which_tech < 0:
			UiHelper.MessageBox(u"请选择相应的抽采技术！")
			return
		design_index = self.ui.design.currentIndex()
		if design_index < 0:
			UiHelper.MessageBox(u"请选择或增加设计方案！")
			return
		
		# 开始设计
		coal_id, ok = self.ui.coal.itemData(coal_index).toInt()
		design_id, ok = self.ui.design.itemData(design_index).toInt()
		# 调用设计对话框
		if not RunGasDesignDlg(coal_id, self.region, which_tech+1, design_id):
			# UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:106)')
			pass
