# -*- coding: utf-8 -*-

# 从网上找的widget基类

import time
import sys
from PyQt4 import QtGui, QtCore


class MyQwidget(QtGui.QDialog):

    def __init__(self, title=None, icon=None):
        QtGui.QDialog.__init__(self)
        self.setGeometry(300, 200, 600, 500)
        self.center()
        self.setTitle(title)
        self.setIcon(icon)

    def setTitle(self, title=None):
        if title != None:
            self.setWindowTitle(title)

    def setIcon(self, icon=None):
        if icon != None:
            self.setWindowIcon(QtGui.QIcon(icon))

    def resize(self, width, height):
        QtGui.QDialog.resize(self, width, height)
        self.center()

    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width() - size.width()) / 2,
                  (screen.height() - size.height()) / 2)

    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(
            self, 'Message', 'Are you sure to close?', QtGui.QMessageBox.Yes, QtGui.QMessageBox.No)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()


class Widget2(MyQwidget):
    pass


class MainWindow(QtGui.QMainWindow, MyQwidget):

    def __init__(self, parent=None):
        QtGui.QMainWindow.__init__(self)
        self.resize(300, 200)
        self.setTitle('statusbar')
        self.statusBar().showMessage('Ready')


app = QtGui.QApplication(sys.argv)

w1 = Widget2(icon='image\\RK.gif', title='MyQwidget')
w1.show()

w2 = Widget2()
w2.setTitle('hehe')
w2.setIcon('image\\fire.gif')
w2.resize(400, 300)
w2.show()

w3 = MainWindow()
w3.show()

sys.exit(app.exec_())