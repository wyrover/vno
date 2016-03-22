#coding:utf-8

# import datetime
# from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
# from cbm.ttypes import *

from dialogs import NameDlg, CbmMessageBox
from PyQt4 import QtCore, QtGui, Qt

def InitTableStyle(table, no_focus=False):
	# 隐藏表头
	table.verticalHeader().setHidden(True)
	# 单行选择
	table.setSelectionBehavior(QtGui.QAbstractItemView.SelectRows)
	# table.setSelectionMode(QtGui.QAbstractItemView.NoSelection)
	# 不允许调整单元格大小
	table.horizontalHeader().setResizeMode(QtGui.QHeaderView.Fixed)
	# 拉伸???
	table.horizontalHeader().setStretchLastSection(True)
	# 禁止编辑
	table.setEditTriggers(QtGui.QAbstractItemView.NoEditTriggers)
	# 左对齐
	table.horizontalHeader().setDefaultAlignment(Qt.Qt.AlignLeft)
	# 不显示单元格的虚框
	if no_focus:
		table.setFocusPolicy(Qt.Qt.NoFocus)
	# 不显示网格
	table.setShowGrid(False)

# 显示或隐藏窗口
def ShowWidget(widget, bShow=True):
	if widget is not None and hasattr(widget, 'setVisible'):
		if bShow:
			widget.show()
		else:
			widget.hide()
		# widget.setVisible(bShow)

# 自定义消息对话框
def MessageBox(msg_text, question=False, error=False):
	msgbox = CbmMessageBox.CbmMessageBox()
	if question:
		msgbox.setMessage(msg_text, CbmMessageBox.MsgBoxType.QUESTION)
		return msgbox.exec_() == 1
	elif error:
		msgbox.setMessage(msg_text, CbmMessageBox.MsgBoxType.ERROR)
		return msgbox.exec_() == 1
	else:
		msgbox.setMessage(msg_text, CbmMessageBox.MsgBoxType.INFO)
		return msgbox.exec_() == 1

# 弹出对话框，请求用户输入一个"名称""
def GetNameFromDlg(title):
	dlg = NameDlg.NameDlg()
	# 设置标题
	dlg.setTitle(title)
	name = u''
	if dlg.exec_():
		name = dlg.name
	return name

# 增加数据到组合框列表
def AddItemToCombobox(combobox, item_text, item_data=None):
	pos = combobox.findText(item_text)
	if pos != -1:
		# 使用QMessageBox,第一个参数可以用None,没必要传递给它一个widget对象!
		MessageBox(u"您输入的名称已存在！")
	else:
		combobox.addItem(item_text, item_data)
		pos = combobox.count()-1
	return pos

def AddObjectListToCombobox(combobox, obj_lists):
	for obj in obj_lists:
		if not hasattr(obj, 'name') or not hasattr(obj, 'id'):
			continue
		combobox.addItem(obj.name, obj.id)
	combobox.setCurrentIndex(0)

def SetBtnStytle(btn):
	btn.setStyleSheet("QPushButton{background: none;\
						border-color: #C8C8FF;\
						color:rgb(85, 170, 255);\
						border-width: 1px;\
						border-style: solid;}\
						QPushButton:hover{\
						border-color: #A2A2FF;}")
