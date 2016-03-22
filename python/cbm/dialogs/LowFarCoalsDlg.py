# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_low_far_coals_dlg import *
import UiHelper
import doc

class LowFarCoalsDlg(BaseDialog):
	def __init__(self, parent=None):
		super(LowFarCoalsDlg, self).__init__(parent)
		self.ui = Ui_low_far_coals_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.ui.tecl_table.setColumnWidth(2,89)
		self.ui.tecl_table.setColumnWidth(1,230)
		self.ui.tecl_table.setColumnWidth(0,50)
		self.ui.tecl_table_2.setColumnWidth(0,50)
		self.ui.tecl_table_2.setColumnWidth(1,259)
		self.initTable(self.ui.tecl_table);
		self.initTable(self.ui.tecl_table_2)
		self.setTitle(u"低渗中远距离煤层群下保护层开采条件井下规模化抽采技术模式")
		self.setFixedSize(self.width(), self.height())
		UiHelper.SetBtnStytle(self.ui.tBtn)
		self.ui.tBtn.clicked.connect(self.onShowPng)

	def onShowPng(self):
		doc.OpenPNG('images\\low_far_coals.png')

	def initTable(self,table):
		table.setSelectionMode(Qt.QAbstractItemView.NoSelection)
		table.setEditTriggers(Qt.QAbstractItemView.NoEditTriggers)
		table.setFocusPolicy(Qt.Qt.NoFocus)
		table.horizontalHeader().setDefaultAlignment(Qt.Qt.AlignLeft)
		table.horizontalHeader().setResizeMode(QtGui.QHeaderView.Fixed)
		table.setStyleSheet(u"font: 9pt \"微软雅黑\";")