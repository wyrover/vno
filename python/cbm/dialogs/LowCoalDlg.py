# -*- coding: utf-8 -*-

from BaseDialog import *
from uipy.ui_low_coal_dlg import *

class LowCoalDlg(BaseDialog):
	def __init__(self, parent=None):
		super(LowCoalDlg, self).__init__(parent)
		self.ui = Ui_low_coal_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # 美化ui
		self.ui.tecl_table.setColumnWidth(2,138)
		self.ui.tecl_table.setColumnWidth(1,330)
		self.ui.tecl_table.setColumnWidth(0,50)
		self.initTable(self.ui.tecl_table);
		self.setTitle(u"低渗单一煤层开采条件井下规模化抽采技术模式")
		self.setFixedSize(self.width(), self.height())

	def initTable(self,table):
		table.setSelectionMode(Qt.QAbstractItemView.NoSelection)
		table.setEditTriggers(Qt.QAbstractItemView.NoEditTriggers)
		table.setFocusPolicy(Qt.Qt.NoFocus)
		table.horizontalHeader().setDefaultAlignment(Qt.Qt.AlignLeft)
		table.horizontalHeader().setResizeMode(QtGui.QHeaderView.Fixed)
		table.setStyleSheet(u"font: 9pt \"微软雅黑\";")