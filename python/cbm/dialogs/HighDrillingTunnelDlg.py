# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_high_drilling_tunnel_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper
from math import cos, radians

class HighDrillingTunnelDlg(BaseDialog):
	def __init__(self, mine_id=-1, parent=None):
		super(HighDrillingTunnelDlg, self).__init__(parent)
		self.ui = Ui_high_drilling_tunnel_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"高抽巷合理布设层位计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cacl.clicked.connect(self.onCacl)
		self.connect(self.ui.work_surf, QtCore.SIGNAL('currentIndexChanged(int)'), self.onWorkSurfChanged)
		# 待设计的矿井
		self.mine_id = mine_id
		# 初始化
		self.init()

	def init(self):
		# 填充工作面列表
		self.fillWorkSurfCombox()

	def fillWorkSurfCombox(self):
		# 查找矿井的所有工作面
		work_surf_lists = CbmClientHelper.GetWorkSurfsOfMine(self.mine_id)
		# 添加到工作面下拉列表
		UiHelper.AddObjectListToCombobox(self.ui.work_surf, work_surf_lists)

	def onWorkSurfChanged(self, index):
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:return
		work_area = SQLClientHelper.GetWorkAreaById(work_surf.work_area_id)
		if work_area.id <= 0:return
		coal = SQLClientHelper.GetCoalById(work_area.coal_id)
		if coal.id <= 0:return

		# 填充煤层数据
		self.ui.hw.setText(u'%.1f' % coal.hw)
		self.ui.dip_angle.setText(u'%.1f' % coal.dip_angle)
		
		# 填充高抽巷的数据
		hdt = SQLClientHelper.GetHighDrillingTunnelByForeignKey('work_surf_id', work_surf_id)
		if hdt.id <= 0:
			self.ui.czk.setText(u'0.0')
			self.ui.rock.setCurrentIndex(-1)
			self.ui.hz_min.setText(u'0.0')
			self.ui.hz_max.setText(u'0.0')
		else:
			self.ui.czk.setText(u'%.1f' % hdt.k)
			self.ui.rock.setCurrentIndex(hdt.rock - 1)
			self.ui.hz_min.setText(u'%.1f' % hdt.hz_min)
			self.ui.hz_max.setText(u'%.1f' % hdt.hz_max)

	def onSave(self):
		index = self.ui.work_surf.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:U1)!')
			return

		# 查找回采面
		work_surf_id, ok = self.ui.work_surf.itemData(index).toInt()
		work_surf = SQLClientHelper.GetWorkSurfById(work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:U2)!')
			return

		# 查找高抽巷
		hdt = SQLClientHelper.GetHighDrillingTunnelByForeignKey('work_surf_id', work_surf.id)
		hdt_id = hdt.id
		if hdt_id <= 0:
			hdt = HighDrillingTunnel()
			hdt.work_surf_id = work_surf_id
		hdt.k, ok = self.ui.czk.text().toDouble()
		hdt.hz_min, ok = self.ui.hz_min.text().toDouble()
		hdt.hz_max, ok = self.ui.hz_max.text().toDouble()
		hdt.rock = self.ui.rock.currentIndex() + 1

		ret = False
		if hdt_id <= 0:
			ret = SQLClientHelper.AddHighDrillingTunnel(hdt) > 0
		else:
			ret = SQLClientHelper.UpdateHighDrillingTunnel(hdt)
		if ret:
			UiHelper.MessageBox(u'更新数据成功!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:U3)!')

		# 提交到数据库
		#做保存操作
		# self.accept()

	def onCacl(self):
		k, ok = self.ui.czk.text().toDouble()
		alpha, ok = self.ui.dip_angle.text().toDouble()
		hw, ok = self.ui.hw.text().toDouble()

		index = self.ui.rock.currentIndex()
		if index < 0:
			UiHelper.MessageBox(u'请选择岩性!!')
			return

		# 数据库中查找rock表得到a,b,c
		name = unicode(self.ui.rock.currentText()).encode('utf-8')
		rock = SQLClientHelper.GetRockByField1('name', name)
		if rock.id <= 0:
			UiHelper.MessageBox(u'计算失败(错误码:Q1)!')
			return

		# 计算范围
		a, b, c = rock.a, rock.b, rock.c
		hz_min = hw / ( (k - 1) * cos( radians(alpha) ) )
		hz_max = 100 * hw / ( a * hw + b) + c
		# 更新到界面
		self.ui.hz_min.setText(u'%.1f' % hz_min)
		self.ui.hz_max.setText(u'%.1f' % hz_max)