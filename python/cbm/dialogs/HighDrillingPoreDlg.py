# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_high_drilling_pore_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

from math import atan, degrees

class HighDrillingPoreDlg(BaseDialog):
	def __init__(self, work_surf_id=-1, parent=None):
		super(HighDrillingPoreDlg, self).__init__(parent)
		self.ui = Ui_high_drilling_pore_dlg()  
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"高位抽采钻孔有效布设范围计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cacl.clicked.connect(self.onCacl)
		# 待设计的工作面
		self.work_surf_id = work_surf_id
		self.Lg = 0.0 # 外部传入该变量
		# 初始化
		self.init()

	def init(self):
		# 填充钻孔参数
		self.fillDatas()

	def fillDatas(self):
		# 根据id查找工作面
		work_surf = SQLClientHelper.GetWorkSurfById(self.work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:Q1)!')
			return
		
		# 提取钻场参数
		hdpp = SQLClientHelper.GetHighDrillingPoreParamByForeignKey('work_surf_id', work_surf.id)
		if hdpp.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:Q2')
			return

		self.ui.lk.setText(u'%.1f' % hdpp.lk)
		self.ui.lc.setText(u'%.1f' % hdpp.lc)
		self.ui.lw.setText(u'%.1f' % hdpp.lw)
		self.ui.beta.setText(u'%.1f' % hdpp.beta)
		self.ui.ld.setText(u'%.1f' % hdpp.ld)
		self.ui.n2.setText(u'%.1f' % hdpp.n1)
		self.ui.n1.setText(u'%.1f' % hdpp.n2)

	def onSave(self):
		# 根据id查找工作面
		work_surf = SQLClientHelper.GetWorkSurfById(self.work_surf_id)
		work_surf_id = work_surf.id
		if work_surf_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:P3)!')
			return
		
		# 提取钻场参数
		hdpp = SQLClientHelper.GetHighDrillingPoreParamByForeignKey('work_surf_id', work_surf_id)
		
		if hdpp.id <= 0:
			hdpp = HighDrillingPoreParam()
			hdpp.work_surf_id = work_surf_id

		hdpp.lk, ok = self.ui.lk.text().toDouble()
		hdpp.lc, ok = self.ui.lc.text().toDouble()
		hdpp.lw, ok = self.ui.lw.text().toDouble()
		hdpp.beta, ok = self.ui.beta.text().toDouble()
		hdpp.n1, ok = self.ui.n1.text().toDouble()
		hdpp.n2, ok = self.ui.n2.text().toDouble()

		# 保存到数据库
		ret = False
		if work_surf_id <= 0:
			ret = SQLClientHelper.AddHighDrillingPoreParam(hdpp) > 0
		else:
			ret = SQLClientHelper.UpdateHighDrillingPoreParam(hdpp)

		if ret:
			UiHelper.MessageBox(u'更新数据成功!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:P4)!')

	def onCacl(self):
		# 从界面提取数据
		Lc, ok = self.ui.lc.text().toDouble()
		Ld, ok = self.ui.ld.text().toDouble()

		# 计算
		Lk = Lc + self.Lg
		beta = degrees( atan( Ld / Lc) )

		# 更新到界面
		self.ui.lk.setText(u'%.1f' % Lk)
		self.ui.beta.setText(u'%.1f' % beta)