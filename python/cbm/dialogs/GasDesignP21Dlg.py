# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_gas_design_p2_1_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import UiHelper
import DataHelper
import doc

class GasDesignP21Dlg(BaseDialog):
	def __init__(self, coal_id=-1, design_id=-1, parent=None):
		super(GasDesignP21Dlg, self).__init__(parent)
		self.ui = Ui_gas_design_p2_1_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"底板岩巷大面积穿层钻孔抽采工作面瓦斯")
		self.setFixedSize(self.width(),self.height())
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
		self.ui.wd.setText(u'%.1f' % ws_tech.wd)
		self.ui.hd.setText(u'%.1f' % ws_tech.hd)
		self.ui.v_offset.setText(u'%.1f' % ws_tech.v_offset)
		self.ui.h_offset.setText(u'%.1f' % ws_tech.h_offset)
		self.ui.dp.setText(u'%.1f' % ws_tech.dp)
		self.ui.gp.setText(u'%.1f' % ws_tech.gp)
		self.ui.left.setText(u'%.1f' % ws_tech.left_side)
		self.ui.right.setText(u'%.1f' % ws_tech.right_side)
		self.ui.top.setText(u'%.1f' % ws_tech.top_side)
		self.ui.bottom.setText(u'%.1f' % ws_tech.bottom_side)
		self.ui.ls.setText(u'%.1f' % ws_tech.ls)
		self.ui.ws.setText(u'%.1f' % ws_tech.ws)
		self.ui.gs.setText(u'%.1f' % ws_tech.gs)
		self.ui.hs.setText(u'%.1f' % ws_tech.hs)
		self.ui.single_rock_tunnel.setChecked(ws_tech.single_rock_tunnel != 0)
		self.ui.d_offset.setText(u'%.1f' % ws_tech.d_offset)
		self.ui.p_offset.setText(u'%.1f' % ws_tech.p_offset)
		self.ui.close_length.setText(u'%.1f' % ws_tech.close_length)
	
	def onSave(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:130)')
			return

		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:131)')
			return
		
		# 保存煤层数据到数据库
		coal.thick, ok = self.ui.thick.text().toDouble()
		coal.dip_angle, ok = self.ui.dip_angle.text().toDouble()
		if not SQLClientHelper.UpdateCoal(coal):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:132)')
			return

		# 保存抽采技术参数到数据库
		ws_tech.l1, ok = self.ui.l1.text().toDouble()
		ws_tech.l2, ok = self.ui.l2.text().toDouble()
		ws_tech.w, ok = self.ui.w.text().toDouble()
		ws_tech.h, ok = self.ui.h.text().toDouble()
		ws_tech.wd, ok = self.ui.wd.text().toDouble()
		ws_tech.hd, ok = self.ui.hd.text().toDouble()
		ws_tech.v_offset, ok = self.ui.v_offset.text().toDouble()
		ws_tech.h_offset, ok = self.ui.h_offset.text().toDouble()
		ws_tech.dp, ok = self.ui.dp.text().toDouble()
		ws_tech.gp, ok = self.ui.gp.text().toDouble()
		ws_tech.left_side, ok = self.ui.left.text().toDouble()
		ws_tech.right_side, ok = self.ui.right.text().toDouble()
		ws_tech.top_side, ok = self.ui.top.text().toDouble()
		ws_tech.bottom_side, ok = self.ui.bottom.text().toDouble()
		ws_tech.ls, ok = self.ui.ls.text().toDouble()
		ws_tech.ws, ok = self.ui.ws.text().toDouble()
		ws_tech.gs, ok = self.ui.gs.text().toDouble()
		ws_tech.hs, ok = self.ui.hs.text().toDouble()
		ws_tech.single_rock_tunnel = int(self.ui.single_rock_tunnel.isChecked())
		ws_tech.d_offset, ok = self.ui.d_offset.text().toDouble()
		ws_tech.p_offset, ok = self.ui.p_offset.text().toDouble()
		ws_tech.close_length, ok = self.ui.close_length.text().toDouble()

		# 保存到数据库
		if not SQLClientHelper.UpdateDesignWorkSurfTechnology(ws_tech):
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:133)')
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
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:134)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:135)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawPlaneGraph21 %d %d" % (coal.id, ws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def head_graph(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:134)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:135)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawHeadGraph21 %d %d" % (coal.id, ws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def dip_graph(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:134)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:135)')
			return
		# 向cad发送命令请求绘图
		ret = CbmClientHelper.SendCommandToCAD("JL.DrawDipGraph21 %d %d" % (coal.id, ws_tech.id), True)
		if not ret:
			UiHelper.MessageBox(u'启动AutoCAD失败')

	def onCreatReport(self):
		coal = SQLClientHelper.GetCoalById(self.coal_id)
		if coal.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:134)')
			return
		# 查找掘进面的抽采技术
		ws_tech = SQLClientHelper.GetDesignWorkSurfTechnologyById(self.design_id)
		if ws_tech.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:135)')
			return

		# 向cad发送命令请求生成钻孔数据
		ret = CbmClientHelper.SendCommandToCAD("JL.GeneratePore21 %d %d" % (coal.id, ws_tech.id), True)
		if ret:
			# 显示钻孔报表
			DataHelper.show_report21(coal, ws_tech)
		else:
			UiHelper.MessageBox(u'启动AutoCAD失败!!!')

		# json文件路径(使用绝对路径,避免出错!!!)
		# json_file = os.path.abspath('.\\help\\json\\reportP21.json')
		# 生成json文件
		# self.make_json(coal.id, tws_tech.id, json_file)
		# 生成word报单
		# doc.CreatReport(json_file)