# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_gas_design_p2_3_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper
import doc

class GasDesignP23Dlg(BaseDialog):
	def __init__(self, coal_id=-1, design_id=-1, parent=None):
		super(GasDesignP23Dlg, self).__init__(parent)
		self.ui = Ui_gas_design_p2_3_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"顺层平行钻孔抽采工作面瓦斯")
		self.setFixedSize(self.width(),self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.plane_graph.clicked.connect(self.plane_graph)
		self.ui.head_graph.clicked.connect(self.head_graph)
		self.ui.dip_graph.clicked.connect(self.dip_graph)
		self.ui.create_report.clicked.connect(self.onCreatReport)
		# 待设计的煤层以及关联的技术
		self.coal_id = coal_id
		self.design_id = design_id
		# 初始化
		self.init()

	def init(self):
		# 填充数据
		self.fillDatas()

	def fillDatas(self):
		# 查找煤层
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:return

		# 填充煤层数据
		self.ui.thick.setText(u'%.1f' % coal.thick)
		self.ui.dip_angle.setText(u'%.1f' % coal.dip_angle)

		# 填充抽采技术参数
		self.ui.l1.setText(u'%.1f' % ws_tech.l1)
		self.ui.l2.setText(u'%.1f' % ws_tech.l2)
		self.ui.w.setText(u'%.1f' % ws_tech.w)
		self.ui.h.setText(u'%.1f' % ws_tech.h)
		self.ui.dp.setText(u'%.1f' % ws_tech.dp)
		self.ui.gp.setText(u'%.1f' % ws_tech.gp)
		self.ui.pore_stubble.setText(u'%.1f' % ws_tech.pore_stubble)
		self.ui.pore_angle.setText(u'%.1f' % ws_tech.pore_angle)
		self.ui.close_length.setText(u'%.1f' % ws_tech.close_length)

		pore_type = ws_tech.pore_type
		if pore_type == 1:
			self.ui.pore_type1.setChecked(True)
		elif pore_type == 2:
			self.ui.pore_type2.setChecked(True)
		elif pore_type == 3:
			self.ui.pore_type3.setChecked(True)
		elif pore_type == 4:
			self.ui.pore_type4.setChecked(True)
	
	def onSave(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:140)')
			return

		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:141)')
			return
		
		# 保存煤层数据到数据库
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.dip_angle, ok = self.ui.dip_angle.text().toDouble()
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:142)')
			return

		# 保存抽采技术参数到数据库
		ws_tech.l1, ok = self.ui.l1.text().toDouble()
		ws_tech.l2, ok = self.ui.l2.text().toDouble()
		ws_tech.w, ok = self.ui.w.text().toDouble()
		ws_tech.h, ok = self.ui.h.text().toDouble()
		ws_tech.dp, ok = self.ui.dp.text().toDouble()
		ws_tech.gp, ok = self.ui.gp.text().toDouble()
		ws_tech.pore_stubble, ok = self.ui.pore_stubble.text().toDouble()
		ws_tech.pore_angle, ok = self.ui.pore_angle.text().toDouble()
		ws_tech.close_length, ok = self.ui.close_length.text().toDouble()

		if self.ui.pore_type1.isChecked():
			ws_tech.pore_type = 1
		elif self.ui.pore_type2.isChecked():
			ws_tech.pore_type = 2
		elif self.ui.pore_type3.isChecked():
			ws_tech.pore_type = 3
		elif self.ui.pore_type4.isChecked():
			ws_tech.pore_type = 4

		# 保存到数据库
		if not SQLClientHelper.UpdateDesignWorkSurfTechnology(ws_tech):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:143)')
		else:
			UiHelper.MessageBox(u'恭喜您,保存数据成功!')
		#做保存操作
		# self.accept()

	def onHelp(self):
		angle, ok = self.ui.dip_angle.text().toDouble()
		if angle < 0:
			UiHelper.MessageBox(u'煤层倾角不能小于0!!!')
			return

		# 煤层按倾角划分的类型
		left,right, top, bottom = 15, 15, 15, 15
		# 按瓦斯突出规定,调整上下左右帮距
		if DataHelper.dip_angle_type(angle) > 2: # 倾斜、急倾斜煤层
			top, bottom = 20, 10

		# 更新界面
		self.ui.left.setText(u'%.1f' % left)
		self.ui.right.setText(u'%.1f' % right)
		self.ui.top.setText(u'%.1f' % top)
		self.ui.bottom.setText(u'%.1f' % bottom)

	def plane_graph(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:144)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:145)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawPlaneGraph23 %d %d" % (coal.id, ws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def head_graph(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:144)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:145)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawHeadGraph23 %d %d" % (coal.id, ws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def dip_graph(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:144)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:145)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawDipGraph23 %d %d" % (coal.id, ws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def onCreatReport(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:144)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:145)')
			return

		# 向cad发送命令请求生成钻孔数据
		ret = CbmClientHelper.SendCommandToCAD("JL.GeneratePore23 %d %d" % (coal.id, ws_tech.id), True)
		if ret:
			# 显示钻孔报表
			DataHelper.show_report23(coal, ws_tech)
		else:
			UiHelper.MessageBox(u'启动AutoCAD失败!!!')

		# json文件路径(使用绝对路径,避免出错!!!)
		# json_file = os.path.abspath('.\\help\\json\\reportP21.json')
		# 生成json文件
		# self.make_json(coal.id, tws_tech.id, json_file)
		# 生成word报单
		# doc.CreatReport(json_file)