# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_login_dlg import *

from RegDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
import UiHelper

LOGIN_MESSAGE = {
	-4:u"请输入有效的用户名！",
	-3:u"请输入密码！",
	-2:u"内部错误,请联系技术人员!",
	-1:u"密码不正确!",
	0:u"用户名不存在",
	1:u"恭喜您,登录成功!"
}

class LoginDlg(BaseDialog):
	def __init__(self, parent=None):
		super(LoginDlg, self).__init__(parent)
		self.ui = Ui_login_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui)  # 美化ui
		self.setTitle(u"登录")
		self.ui.login.clicked.connect(self.onLogin)
		self.ui.reg.clicked.connect(self.onReg)
		#任务栏图标
		# ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID("myappid")
		# self.setFixedSize(self.width(), self.height())

	def verify_user(self, uname, pwd):
		ret = -2
		if uname == '':ret = -4
		elif pwd == '':ret = -3
		else:ret = CbmClientHelper.VerifyMineAccount(uname, pwd)
		# 弹出提示信息
		if ret != 1:
			UiHelper.MessageBox(LOGIN_MESSAGE[ret],error = True)
		return ret

	def login_or_switch(self, uname, pwd):
		account_id = SQLClientHelper.GetAccountIdByField2('username', uname, 'password', pwd)
		# 查找已登录用户
		pre_account_id = CbmClientHelper.GetOnlineAccountId()
		# 当前没有用户登录
		if pre_account_id <= 0:
			# 用户登陆(记录在sys_info表中)
			DataHelper.sql_login_user(account_id)
			# UiHelper.MessageBox('恭喜您,登录成功!')
		# 当前已有用户登录
		elif pre_account_id == account_id:
			# UiHelper.MessageBox('您已经登录过了!')
			pass
		else:
			reply = UiHelper.MessageBox('是否注销并切换到用户%s?' % uname, True)
			if reply == True:
				# 切换用户
				DataHelper.sql_switch_user(account_id)

	def onLogin(self):
		uname = unicode(self.ui.username.text()).encode('utf-8')
		pwd = unicode(self.ui.password.text()).encode('utf-8')
		#验证用户名和密码
		ret = self.verify_user(uname, pwd)
		# 验证通过
		if ret == 1:
			# 登录或切换用户
			self.login_or_switch(uname, pwd)
			# 关闭对话框并返回1
			self.accept()
		# else:
		# 	# 关闭对话框并返回0
		# 	self.reject()
	
	def onReg(self):
		# 启动注册对话框
		dlg = RegDlg()
		if dlg.exec_():
			self.nameEdit.setText(dlg.reg_user_name)
