# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_gas_design_p1_2_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper
import doc

class GasDesignP12Dlg(BaseDialog):
	def __init__(self, coal_id=-1, design_id=-1, parent=None):
		super(GasDesignP12Dlg, self).__init__(parent)
		self.ui = Ui_gas_design_p1_2_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"顺层钻孔条带掩护巷道掘进抽采法")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.help.clicked.connect(self.onHelp)
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
		tws_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(self.design_id)
		if tws_tech.id <= 0:return

		# 填充煤层数据
		self.ui.thick.setText(u'%.1f' % coal.thick)
		self.ui.dip_angle.setText(u'%.1f' % coal.dip_angle)

		# 填充抽采技术参数
		self.ui.lm.setText(u'%.1f' % tws_tech.lm)
		self.ui.w.setText(u'%.1f' % tws_tech.w)
		self.ui.h.setText(u'%.1f' % tws_tech.h)
		self.ui.dp.setText(u'%.1f' % tws_tech.dp)
		self.ui.left.setText(u'%.1f' % tws_tech.left_side)
		self.ui.right.setText(u'%.1f' % tws_tech.right_side)
		self.ui.top.setText(u'%.1f' % tws_tech.top_side)
		self.ui.bottom.setText(u'%.1f' % tws_tech.bottom_side)
		self.ui.leading_dist.setText(u'%.1f' % tws_tech.leading_dist)
		self.ui.l_stripe.setText(u'%.1f' % tws_tech.l_stripe)
		self.ui.gbp.setText(u'%.1f' % tws_tech.gbp)
		self.ui.close_length.setText(u'%.1f' % tws_tech.close_length)

	def onSave(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:120)')
			return

		# 查找掘进面的抽采技术
		tws_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(self.design_id)
		if tws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:121)')
			return
		
		# 保存煤层数据到数据库
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.dip_angle, ok = self.ui.dip_angle.text().toDouble()
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:122)')
			return

		# 保存抽采技术参数到数据库
		tws_tech.lm, ok = self.ui.lm.text().toDouble()
		tws_tech.w, ok = self.ui.w.text().toDouble()
		tws_tech.h, ok = self.ui.h.text().toDouble()
		tws_tech.dp, ok = self.ui.dp.text().toDouble()
		tws_tech.left_side, ok = self.ui.left.text().toDouble()
		tws_tech.right_side, ok = self.ui.right.text().toDouble()
		tws_tech.top_side, ok = self.ui.top.text().toDouble()
		tws_tech.bottom_side, ok = self.ui.bottom.text().toDouble()
		tws_tech.leading_dist, ok = self.ui.leading_dist.text().toDouble()
		tws_tech.l_stripe, ok = self.ui.l_stripe.text().toDouble()
		tws_tech.gbp, ok = self.ui.gbp.text().toDouble()
		tws_tech.close_length, ok = self.ui.close_length.text().toDouble()

		# 保存到数据库
		if not SQLClientHelper.UpdateDesignDrillingSurfTechnology(tws_tech):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:123)')
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
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:124)')
			return
		# 查找掘进面的抽采技术
		tws_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(self.design_id)
		if tws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:125)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawPlaneGraph12 %d %d" % (coal.id, tws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def head_graph(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:124)')
			return
		# 查找掘进面的抽采技术
		tws_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(self.design_id)
		if tws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:125)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawHeadGraph12 %d %d" % (coal.id, tws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def dip_graph(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:124)')
			return
		# 查找掘进面的抽采技术
		tws_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(self.design_id)
		if tws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:125)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawDipGraph12 %d %d" % (coal.id, tws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def onCreatReport(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:124)')
			return
		# 查找掘进面的抽采技术
		tws_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(self.design_id)
		if tws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:125)')
			return

		# 向cad发送命令请求生成钻孔数据
		ret = CbmClientHelper.SendCommandToCAD("JL.GeneratePore12 %d %d" % (coal.id, tws_tech.id), True)
		if ret:
			# 显示钻孔报表
			DataHelper.show_report12(coal, tws_tech)
		else:
			UiHelper.MessageBox(u'启动AutoCAD失败!!!')

		# json文件路径(使用绝对路径,避免出错!!!)
		# json_file = os.path.abspath('.\\help\\json\\reportP12.json')
		# 生成json文件
		# self.make_json(coal.id, tws_tech.id, json_file)
		# 生成word报单
		# doc.CreatReport(json_file)
