# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_high_coals_dlg import *
import UiHelper
import doc

class HighCoalsDlg(BaseDialog):
	def __init__(self, parent=None):
		super(HighCoalsDlg, self).__init__(parent)
		self.ui = Ui_high_coals_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.ui.tecl_table.setColumnWidth(2,128)
		self.ui.tecl_table.setColumnWidth(1,300)
		self.ui.tecl_table.setColumnWidth(0,50)
		self.ui.tecl_table_2.setColumnWidth(0,50)
		self.ui.tecl_table_2.setColumnWidth(1,428)
		self.initTable(self.ui.tecl_table);
		self.initTable(self.ui.tecl_table_2)
		self.setTitle(u"中高渗煤层群条件井下规模化抽采技术模式")
		self.setFixedSize(self.width(), self.height())
		UiHelper.SetBtnStytle(self.ui.tBtn)
		self.ui.tBtn.clicked.connect(self.onShowPng)

	def onShowPng(self):
		doc.OpenPNG('images\\high_coals.png')

	def initTable(self,table):
		table.setSelectionMode(Qt.QAbstractItemView.NoSelection)
		table.setEditTriggers(Qt.QAbstractItemView.NoEditTriggers)
		table.setFocusPolicy(Qt.Qt.NoFocus)
		table.horizontalHeader().setDefaultAlignment(Qt.Qt.AlignLeft)
		table.horizontalHeader().setResizeMode(QtGui.QHeaderView.Fixed)
		table.setStyleSheet(u"font: 9pt \"微软雅黑\";")