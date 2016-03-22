# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_high_drilling_site_dlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

class HighDrillingSiteDlg(BaseDialog):
	def __init__(self, work_surf_id=-1, parent=None):
		super(HighDrillingSiteDlg, self).__init__(parent)
		self.ui = Ui_high_drilling_site_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.setTitle(u"高位抽采钻场范围计算")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)
		self.ui.cancel.clicked.connect(self.onCancel)
		# 待设计的工作面
		self.work_surf_id = work_surf_id
		# 初始化
		self.init()

	def init(self):
		# 填充工作面、采区、煤层的数据
		self.fillDatas()

	def fillDatas(self):
		# 根据id查找工作面
		work_surf = SQLClientHelper.GetWorkSurfById(self.work_surf_id)
		if work_surf.id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:P1)!')
			return
		
		# 提取钻场参数
		hdsp = SQLClientHelper.GetHighDrillingSiteParamByForeignKey('work_surf_id', work_surf.id)
		if hdsp.id <= 0:
			UiHelper.MessageBox(u'sorry, 出了点问题,请联系技术人员(错误码:P2')
			return

		self.ui.hn.setText(u'%.1f' % hdsp.hn)
		self.ui.hs.setText(u'%.1f' % hdsp.hs)
		self.ui.theta.setText(u'%.1f' % hdsp.theta)
		self.ui.rtn.setText(u'%.1f' % hdsp.rtn)
		self.ui.q.setText(u'%.1f' % hdsp.q)

	def onSave(self):
		# 根据id查找工作面
		work_surf = SQLClientHelper.GetWorkSurfById(self.work_surf_id)
		work_surf_id = work_surf.id
		if work_surf_id <= 0:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:P3)!')
			return
		
		# 提取钻场参数
		hdsp = SQLClientHelper.GetHighDrillingSiteParamByForeignKey('work_surf_id', work_surf_id)
		
		if hdsp.id <= 0:
			hdsp = HighDrillingSiteParam()
			hdsp.work_surf_id = work_surf_id

		hdsp.hn, ok = self.ui.hn.text().toDouble()
		hdsp.hs, ok = self.ui.hs.text().toDouble()
		hdsp.theta, ok = self.ui.theta.text().toDouble()
		hdsp.rtn, ok = self.ui.rtn.text().toDouble()
		hdsp.q, ok = self.ui.q.text().toDouble()

		# 保存到数据库
		ret = False
		if work_surf_id <= 0:
			ret = SQLClientHelper.AddHighDrillingSiteParam(hdsp) > 0
		else:
			ret = SQLClientHelper.UpdateHighDrillingSiteParam(hdsp)

		if ret:
			UiHelper.MessageBox(u'更新数据成功!')
		else:
			UiHelper.MessageBox(u'sorry,出了点问题,请联系技术人员(错误码:P4)!')
	
	def onCancel(self):
		# 关闭对话框并返回0
		self.reject()