#coding:utf-8

from uipy.ui_mainwin import *
from dialogs.LoginDlg import *
from dialogs.SampleManageDlg import *
from dialogs.MineDesignDlg import *
from dialogs.MineBaseParamDlg import *
from dialogs.DifficultEvalDlg import *
from dialogs.MineGasReservesPredictDlg import *
from dialogs.MineGasFlowPredictDlg import *
from dialogs.TwsGasFlowPredictDlg import *
from dialogs.WsGasFlowPredictDlg import *
from dialogs.HighDrillingTunnelDlg import *
from dialogs.HighDrillingDesignDlg import *
from dialogs.PoreSizeDlg import *
from dialogs.PoreFlowDlg import *

from dialogs.GasDesignDlg import *

from dialogs.EvalUnitDlg import *
from dialogs.CurveDrawDlg import *
from dialogs.GasDrillingOptimizeDlg import *
from dialogs.GasDrillingRadiusDlg import *

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import DataHelper
from DataHelper import Authority
import UiHelper
import WebHelper
import doc

class MainWindow(QtGui.QMainWindow):  
	def __init__(self,parent=None):
		super(MainWindow, self).__init__(parent)
		self.ui = Ui_MainWindow()
		self.ui.setupUi(self)
		self.init()

		# ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID("myappid")
		# 瓦斯抽采设计类型

	def init(self):
		self.myActions = []
		self.loginAction = None
		self.logoutAction = None
		self.setAttribute(QtCore.Qt.WA_DeleteOnClose)
		self.createActions()
		self.createMenusToolBars()
		self.setStatusBar(None)
		# self.createStatusBar()
		self.setWindowTitle(u"井下煤层气规模化抽采计算机辅助设计系统")
		self.setWindowIcon(QtGui.QIcon(':/images/cbm.ico'))
		# 增大菜单栏的字体
		self.setStyleSheet(u"font: 11pt \"微软雅黑\";")
		# 设置背景图片的几种方法(推荐用样式CSS)
		# http://blog.chinaunix.net/uid-25749806-id-3522787.html
		# http://blog.csdn.net/yuanzhangmei1/article/details/7698417
		# 方法1: 用palette设置背景
		palette = QtGui.QPalette()
		# palette.setColor(self.backgroundRole(), QColor(192,253,123))#设置背景颜色
		palette.setBrush(self.backgroundRole(), QtGui.QBrush(QtGui.QPixmap(':/images/bg.png')))
		self.setPalette(palette)
		# 方法2: 用CSS设置背景
		# self.setStyleSheet(u"QWidget#centralwidget{ border-image : url(:/images/bg.png)};" );
		# 报表是否显示一页，false代表所有数据都显示在一页上
		self.bypagesize = 'true'

	
	def real_logout(self):
		# 注销(清空sys_info表)
		DataHelper.sql_logout()
		# 设置菜单激活状态
		self.loginAction.setEnabled(True)
		self.logoutAction.setEnabled(False)

	def closeEvent(self, event):
		reply = UiHelper.MessageBox(u'确定退出本系统?', True)
		if reply == True:
			# 注销
			self.real_logout()
			# close消息处理完毕,不再需要qt继续处理close消息了
			event.accept()
		else:
			# qt内部继续处理close消息
			event.ignore()

	def login(self):
		"""返回True或False"""
		dialog = LoginDlg()
		if dialog.exec_():
			self.loginAction.setEnabled(False)
			self.logoutAction.setEnabled(True)
			return True
		else:  
			return False

	def logout(self):
		reply = UiHelper.MessageBox(u'您确定要注销?', True)
		if reply == True:
			# 注销
			self.real_logout()

	def run_dialog(self, DialogClass):
		# 启动对话框(传入当前登录用户的)
		mine = CbmClientHelper.GetOnlineMine()
		dlg = DialogClass(mine.id)
		dlg.exec_()

	# 尝试运行对话框
	def try_run(self, DialogClass, authority):
		can_run = True
		while can_run:
			# 检查用户登录状态
			ret = DataHelper.sql_login_status()
			# 内部错误
			if ret == 0 or ret == -1:
				UiHelper.MessageBox(u"系统技术性故障(错误码:M1),请联系技术人员!",error = True)
				can_run = False
				break
			# 用户未登录
			elif ret == 2:
				if UiHelper.MessageBox(u"您需要登录才能使用本功能!", error = True):
					can_run = self.login() # 登录
				else:
					can_run = False
					break
			# 管理员已登录		
			elif ret == 3 and authority == Authority.USER:
				if UiHelper.MessageBox(u"管理员禁止使用该功能,请重新登录!", error = True):
					can_run = self.login() # 登录
				else:
					can_run = False
					break
			# 普通用户已登录
			elif ret == 1 and authority == Authority.ADMIN:
				if UiHelper.MessageBox(u"您的权限不够,请重新登录!", error = True):
					can_run = self.login() # 登录
				else:
					can_run = False
					break

			if can_run and DataHelper.sql_login_authority(authority):
				break

		# 启动对话框
		if can_run:
			# 启动对话框(传入当前登录用户的)
			self.run_dialog(DialogClass)


	def showSampleData(self):
		# 显示基础数据
		pass

	def sampleManage(self):
		# 启动示范矿区管理库对话框
		self.try_run(SampleManageDlg, Authority.BOTH)

	def designMine(self):
		# 启动矿井设计对话框
		self.try_run(MineDesignDlg, Authority.BOTH)

	def dragTec(self):
		# 启动辅助决策对话框
		self.try_run(MineBaseParamDlg, Authority.USER)

	def difficultEval(self):
		# 启动抽采难易程度评价对话框
		self.try_run(DifficultEvalDlg, Authority.USER)

	def mineGasReservesPredict(self):
		# 启动矿井瓦斯储量计算对话框
		self.try_run(MineGasReservesPredictDlg, Authority.USER)

	def mineGasFlowPredict(self):
		# 启动矿井瓦斯流量计算对话框
		self.try_run(MineGasFlowPredictDlg, Authority.USER)

	def twsGasFlowPredict(self):
		# 启动掘进面瓦斯流量计算对话框
		self.try_run(TwsGasFlowPredictDlg, Authority.USER)

	def wsGasFlowPredict(self):
		# 启动工作面瓦斯流量计算对话框
		self.try_run(WsGasFlowPredictDlg, Authority.USER)

	def highDrillingTunnel(self):
		# 启动高抽巷计算对话框
		self.try_run(HighDrillingTunnelDlg, Authority.USER)

	def highDrillingPore(self):
		# 启动高抽钻孔计算对话框
		self.try_run(HighDrillingDesignDlg, Authority.USER)

	def poreSize(self):
		# 启动瓦斯抽采钻孔计算对话框
		self.try_run(PoreSizeDlg, Authority.USER)

	def poreFlow(self):
		# 启动孔板流量计算对话框
		self.try_run(PoreFlowDlg, Authority.USER)

	# 曲线绘制
	def gasDrillingPredict(self):
		# 绘制曲线
		self.try_run(CurveDrawDlg, Authority.USER)

	# 钻孔间距(抽采半径)优化
	def gasDrillingRadius(self):
		# 启动瓦斯抽采半径计算对话框
		self.try_run(GasDrillingRadiusDlg, Authority.USER)

	def gasDrillingOptimize(self):
		# 启动瓦斯抽采半径计算对话框
		self.try_run(GasDrillingOptimizeDlg, Authority.USER)

	def gasDrillingAnalyse(self):
		# 启动瓦斯抽采半径计算对话框
		self.try_run(GasDrillingAnalyseDlg, Authority.USER)
	
	def evalUnitPartition(self):
		# 启动评价单元划分计算对话框
		self.try_run(EvalUnitDlg, Authority.USER)

	def wsGasDesign(self):
		# 进行工作面的瓦斯抽采设计
		DataHelper.GAS_DESIGN_REGION = 2
		# 启动瓦斯抽采设计对话框
		self.try_run(GasDesignDlg, Authority.USER)

	def twsGasDesign(self):
		# 进行掘进面的瓦斯抽采设计
		DataHelper.GAS_DESIGN_REGION = 1
		# 启动掘进面瓦斯抽采设计对话框
		self.try_run(GasDesignDlg, Authority.USER)

	def goafGasDesign(self):
		# 进行采空区的瓦斯抽采设计
		DataHelper.GAS_DESIGN_REGION = 3
		self.try_run(GasDesignDlg, Authority.USER)

	def openOfficeNet1(self):
		doc.OpenNet('http://www.sxcoal.com/')

	def openOfficeNet2(self):
		doc.OpenNet('http://www.coalchina.org.cn/')

	def openOfficeNet3(self):
		doc.OpenNet('http://www.ccbmg.com/')

	def openOfficeNet4(self):
		doc.OpenNet('http://www.chinacbm.com/')

	def openOfficeNet5(self):
		doc.OpenNet('http://www.ccteg.cn/')

	def openOfficeNet6(self):
		doc.OpenNet('http://www.ccri.com.cn/')

	def openOfficeNet7(self):
		doc.OpenNet('http://www.jamg.cn/web1/index.jsp')

	def openOfficeNet8(self):
		doc.OpenNet('http://www.hnmine.com/index.html')

	def openOfficeNet9(self):
		doc.OpenNet('http://www.hbcoal.com/')

	def openOfficeNet10(self):
		doc.OpenNet('http://www.songzao.com/')

	def showReport1_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=1_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		# 调用qtwebkit打开url(执行jquery的代码时出错,怀疑是qtwebkit版本太低!!!)
		# WebHelper.show_web(self, url)
		# 调用外部浏览器打开url
		doc.OpenNet(url)

	def showReport1_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=1_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport1_3(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=1_3.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport2_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=2_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport2_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=2_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport3_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=3_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport3_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=3_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport4_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=4_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport4_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=4_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport5_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=5_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport5_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=5_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport6_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=6_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport6_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=6_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport7_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=7_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport7_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=7_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport8_1(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=8_1.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	def showReport8_2(self):
		url = u'http://localhost:8081/WebReport/ReportServer?reportlet=8_2.cpt&__bypagesize__=%s' %(self.bypagesize)
		doc.OpenNet(url)

	#查看《煤层气资源勘察技术规范》文档
	def investigationOfCBMResources(self):
		doc.OpenPDFFile(u'help\\pdf\\煤层气资源勘察技术规范.pdf')

	#查看《保护层开采技术规范》文档
	def protectiveLayerMining(self):
		doc.OpenPDFFile('help\\pdf\\保护层开采技术规范.pdf')

	#查看《煤矿瓦斯抽放规范》文档
	def coalMineGasDrainage(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯抽放规范.pdf')

	#查看《煤矿瓦斯抽放技术规范》文档
	def technicalSpecificationCoalMineGasDrainage(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯抽放技术规范.pdf')

	#查看《煤矿瓦斯抽采工程设计规范》文档
	def coalMineGasDrainageEngineeringDesign(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯抽采工程设计规范.pdf')

	#查看《煤矿瓦斯抽采达标暂行规定》文档
	def standardInterimProvisions(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯抽采达标暂行规定.pdf')

	#查看《煤层气(煤矿瓦斯)开发利用十二五规划》文档
	def coalGasDevelopment(self):
		doc.OpenPDFFile(u'help\\pdf\\煤层气(煤矿瓦斯)开发利用十二五规划.pdf')

	#查看《煤矿瓦斯抽采基本指标》文档
	def basicCoalMineGasIndex(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯抽采基本指标.pdf')
	
	def pdfHelp1(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿井下煤层瓦斯压力的直接测定方法.pdf')

	def pdfHelp2(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿用非金属瓦斯输送管材安全技术要求.pdf')

	def pdfHelp3(self):
		doc.OpenPDFFile(u'help\\pdf\\瓦斯管道输送水封阻火泄爆装置技术条件.pdf')

	def pdfHelp4(self):
		doc.OpenPDFFile(u'help\\pdf\\瓦斯管道输送自动阻爆装置技术条件.pdf')

	def pdfHelp5(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯输送管道干式阻火器通用技术条件.pdf')

	def pdfHelp6(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿低浓度瓦斯往复式内燃机驱动的交流发电机组通用技术条件.pdf')

	def pdfHelp7(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿低浓度瓦斯管道输送安全保障系统设计规范.pdf')

	def pdfHelp8(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿低浓度瓦斯与细水雾混合安全输送装置技术规范.pdf')

	def pdfHelp9(self):
		doc.OpenPDFFile(u'help\\pdf\\瓦斯管道输送自动喷粉抑爆装置通用技术条件.pdf')

	def pdfHelp10(self):
		doc.OpenPDFFile(u'help\\pdf\\煤的工业分析方法.pdf')

	def pdfHelp11(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯抽采工程设计规范(GB50471-2008).pdf')

	def pdfHelp12(self):
		doc.OpenPDFFile(u'help\\pdf\\煤自燃倾向性色谱吸氧鉴定法.pdf')

	def pdfHelp13(self):
		doc.OpenPDFFile(u'help\\pdf\\石门揭穿煤与瓦斯突出煤层.pdf')

	def pdfHelp14(self):
		doc.OpenPDFFile(u'help\\pdf\\钻孔瓦斯涌出初速度的测定方法.pdf')

	def pdfHelp15(self):
		doc.OpenPDFFile(u'help\\pdf\\中国煤炭分类国家标准.pdf')

	def pdfHelp16(self):
		doc.OpenPDFFile(u'help\\pdf\\保护层开采技术规范.pdf')

	def pdfHelp17(self):
		doc.OpenPDFFile(u'help\\pdf\\煤与瓦斯突出矿井鉴定规范（AQ1024-2006）.pdf')

	def pdfHelp18(self):
		doc.OpenPDFFile(u'help\\pdf\\煤矿瓦斯抽放规范AQ1027-2006.pdf')

	def pdfHelp19(self):
		doc.OpenPDFFile(u'help\\pdf\\电子等容式瓦斯解吸仪技术条件')

	def pdfHelp20(self):
		doc.OpenPDFFile(u'help\\pdf\\矿井瓦斯等级鉴定规范AQ1025-2006.pdf')

	def pdfHelp21(self):
		doc.OpenPDFFile(u'help\\pdf\\钻孔瓦斯涌出初速度的测定方法.pdf')

	def buildAction(self,name,tip,trigger):
		return QtGui.QAction(name, self, statusTip=tip, triggered=trigger)

	def regAction(self,menu,name,tip,trigger):
		return self.myActions.append([menu,name,tip,trigger])

	def do_nothing(self):
		pass

	def help(self):
		doc.OpenPDFFile(u'help\\使用说明.pdf')

	def createActions(self):
		self.regAction(u"账户管理", u"登录", u"用户登录", self.login)
		self.regAction(u"账户管理", u"注销", u"注销用户", self.logout)		
		# self.regAction(u"基础参数库", u"示范矿区基础参数", u"示范矿区基础参数", self.showSampleData)
		# 两淮矿区
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区钻孔瓦斯含量", u"", self.showReport1_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区钻钻孔瓦斯含量", u"", self.showReport1_2)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区采掘工作面瓦斯含量", u"", self.showReport1_3)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区瓦斯压力", u"", self.showReport2_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区瓦斯压力", u"", self.showReport2_2)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区回采工作面瓦斯涌出量", u"", self.showReport3_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区回采工作面瓦斯涌出量", u"", self.showReport3_2)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区掘进工作面瓦斯涌出量", u"", self.showReport4_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区掘进工作面瓦斯涌出量", u"", self.showReport4_2)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区煤与瓦斯突出点情况", u"", self.showReport5_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区煤与瓦斯突出点情况", u"", self.showReport5_2)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区煤与瓦斯区域突出危险性预测参数", u"", self.showReport6_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区煤与瓦斯区域突出危险性预测参数", u"", self.showReport6_2)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区采（掘）工作面瓦斯突出预测参数", u"", self.showReport7_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区采（掘）工作面瓦斯突出预测参数", u"", self.showReport7_2)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"淮河南矿区采（掘）工作面瓦斯抽放量", u"", self.showReport8_1)
		self.regAction(u"基础参数库/示范矿区基础参数/两淮矿区",u"潘谢矿区采（掘）工作面瓦斯抽放量", u"", self.showReport8_2)

		# 晋城矿区(没有数据,没有实现)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区钻孔瓦斯含量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区钻钻孔瓦斯含量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区采掘工作面瓦斯含量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区瓦斯压力", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区瓦斯压力", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区回采工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区回采工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区掘进工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区掘进工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区煤与瓦斯突出点情况", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区煤与瓦斯突出点情况", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区煤与瓦斯区域突出危险性预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区煤与瓦斯区域突出危险性预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区采（掘）工作面瓦斯突出预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区采（掘）工作面瓦斯突出预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"寺河矿区采（掘）工作面瓦斯抽放量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/晋城矿区",u"赵庄矿区采（掘）工作面瓦斯抽放量", u"", self.do_nothing)

		# 松藻矿区(没有数据,没有实现)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区钻孔瓦斯含量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区钻钻孔瓦斯含量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区采掘工作面瓦斯含量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区瓦斯压力", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区瓦斯压力", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区回采工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区回采工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区掘进工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区掘进工作面瓦斯涌出量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区煤与瓦斯突出点情况", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区煤与瓦斯突出点情况", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区煤与瓦斯区域突出危险性预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区煤与瓦斯区域突出危险性预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区采（掘）工作面瓦斯突出预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区采（掘）工作面瓦斯突出预测参数", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"松藻矿区采（掘）工作面瓦斯抽放量", u"", self.do_nothing)
		self.regAction(u"基础参数库/示范矿区基础参数/松藻矿区",u"渝阳矿区采（掘）工作面瓦斯抽放量", u"", self.do_nothing)

		self.regAction(u"基础参数库", u"示范矿区参数录入", u"对示范矿区进行技术管理", self.sampleManage)
		self.regAction(u"基础参数库", u"目标矿井设计", u"设计目标矿井", self.designMine)
		self.regAction(u"辅助决策", u"抽采技术模式", u"抽采技术模式辅助决策", self.dragTec)
		self.regAction(u"辅助计算", u"煤层气抽采难易程度评价", u"煤层气抽采难易程度评价辅助计算", self.difficultEval)
		self.regAction(u"辅助计算", u"矿井煤层气储量及可抽量预测", u"矿井煤层气储量及可抽量预测辅助计算", self.mineGasReservesPredict)
		self.regAction(u"辅助计算", u"矿井瓦斯涌出量预测", u"矿井瓦斯涌出量预测辅助计算", self.mineGasFlowPredict)
		self.regAction(u"辅助计算", u"掘进面瓦斯涌出量预测", u"掘进面瓦斯涌出量预测辅助计算", self.twsGasFlowPredict)
		self.regAction(u"辅助计算", u"回采面瓦斯涌出量预测", u"回采面瓦斯涌出量预测辅助计算", self.wsGasFlowPredict)
		self.regAction(u"辅助计算", u"高抽巷合理布设层位", u"高抽巷合理布设层位辅助计算", self.highDrillingTunnel)
		self.regAction(u"辅助计算", u"高位抽采钻孔有效布设范围", u"高位抽采钻孔有效布设范围辅助计算", self.highDrillingPore)
		self.regAction(u"辅助计算", u"抽采管径大小", u"抽采管径大小辅助计算", self.poreSize)
		self.regAction(u"辅助计算", u"孔板流量", u"孔板流量辅助计算", self.poreFlow)
		self.regAction(u"抽采参数优化", u"钻孔抽采量预测", u"钻孔抽采量预测", self.gasDrillingPredict)
		self.regAction(u"抽采参数优化", u"钻孔间距计算", u"煤层瓦斯抽采半径辅助计算", self.gasDrillingRadius)
		self.regAction(u"抽采参数优化", u"钻孔间距优化", u"煤层瓦斯抽采半径辅助计算", self.gasDrillingOptimize)
		# self.regAction(u"抽采参数优化", u"钻孔间距优化3", u"煤层瓦斯抽采半径辅助计算", self.gasDrillingAnalyse)
		self.regAction(u"抽采参数优化", u"评价单元划分", u"评价单元划分辅助计算", self.evalUnitPartition)

		self.regAction(u"抽采设计", u"掘进面", u"掘进面瓦斯抽采辅助设计", self.twsGasDesign)
		self.regAction(u"抽采设计", u"工作面", u"工作面瓦斯抽采辅助设计", self.wsGasDesign)
		self.regAction(u"抽采设计", u"采空区", u"采空区瓦斯抽采辅助设计", self.goafGasDesign)

		# 只需要将菜单用符号: / 分隔即可,程序自动解析成相应的子菜单
		self.regAction(u"帮助文档",u"使用说明",u"使用说明", self.help)
		self.regAction(u"帮助文档/相关官网",u"中国煤炭资源网",u"中国煤炭资源网", self.openOfficeNet1)
		self.regAction(u"帮助文档/相关官网",u"国家煤炭工业网",u"国家煤炭工业网", self.openOfficeNet2)
		self.regAction(u"帮助文档/相关官网",u"中国煤层气集团有限公司",u"中国煤层气集团有限公司", self.openOfficeNet3)
		self.regAction(u"帮助文档/相关官网",u"中联煤层气有限责任公司",u"中联煤层气有限责任公司", self.openOfficeNet4)
		self.regAction(u"帮助文档/相关官网",u"中国煤炭科工集团有限公司",u"中国煤炭科工集团有限公司", self.openOfficeNet5)
		self.regAction(u"帮助文档/相关官网",u"煤层科学技术研究院有限公司",u"煤层科学技术研究院有限公司", self.openOfficeNet6)
		self.regAction(u"帮助文档/相关官网",u"山西晋城无烟煤矿业集团有限公司",u"山西晋城无烟煤矿业集团有限公司", self.openOfficeNet7)
		self.regAction(u"帮助文档/相关官网",u"淮南矿业网",u"淮南矿业网", self.openOfficeNet8)
		self.regAction(u"帮助文档/相关官网",u"淮北矿业网",u"淮北矿业网", self.openOfficeNet9)
		self.regAction(u"帮助文档/相关官网",u"重庆松藻煤电有限责任公司",u"重庆松藻煤电有限责任公司", self.openOfficeNet10)

		self.regAction(u"帮助文档/相关规范",u"煤矿井下煤层瓦斯压力的直接测定方法",u"煤矿井下煤层瓦斯压力的直接测定方法",self.pdfHelp1)
		self.regAction(u"帮助文档/相关规范",u"煤矿用非金属瓦斯输送管材安全技术要求",u"煤矿用非金属瓦斯输送管材安全技术要求",self.pdfHelp2)
		self.regAction(u"帮助文档/相关规范",u"瓦斯管道输送水封阻火泄爆装置技术条件",u"瓦斯管道输送水封阻火泄爆装置技术条件",self.pdfHelp3)
		self.regAction(u"帮助文档/相关规范",u"瓦斯管道输送自动阻爆装置技术条件",u"瓦斯管道输送自动阻爆装置技术条件",self.pdfHelp4)
		self.regAction(u"帮助文档/相关规范",u"煤矿瓦斯输送管道干式阻火器通用技术条件",u"煤矿瓦斯输送管道干式阻火器通用技术条件",self.pdfHelp5)
		self.regAction(u"帮助文档/相关规范",u"煤矿低浓度瓦斯往复式内燃机驱动的交流发电机组通用技术条件",u"煤矿低浓度瓦斯往复式内燃机驱动的交流发电机组通用技术条件",self.pdfHelp6)
		self.regAction(u"帮助文档/相关规范",u"煤矿低浓度瓦斯管道输送安全保障系统设计规范",u"煤矿低浓度瓦斯管道输送安全保障系统设计规范",self.pdfHelp7)
		self.regAction(u"帮助文档/相关规范",u"煤矿低浓度瓦斯与细水雾混合安全输送装置技术规范",u"煤矿低浓度瓦斯与细水雾混合安全输送装置技术规范",self.pdfHelp8)
		self.regAction(u"帮助文档/相关规范",u"瓦斯管道输送自动喷粉抑爆装置通用技术条件",u"瓦斯管道输送自动喷粉抑爆装置通用技术条件",self.pdfHelp9)
		self.regAction(u"帮助文档/相关规范",u"煤的工业分析方法",u"煤的工业分析方法",self.pdfHelp10)
		self.regAction(u"帮助文档/相关规范",u"煤矿瓦斯抽采工程设计规范",u"煤矿瓦斯抽采工程设计规范",self.pdfHelp11)
		self.regAction(u"帮助文档/相关规范",u"煤自燃倾向性色谱吸氧鉴定法",u"煤自燃倾向性色谱吸氧鉴定法",self.pdfHelp12)
		self.regAction(u"帮助文档/相关规范",u"石门揭穿煤与瓦斯突出煤层",u"石门揭穿煤与瓦斯突出煤层",self.pdfHelp13)
		self.regAction(u"帮助文档/相关规范",u"钻孔瓦斯涌出初速度的测定方法",u"钻孔瓦斯涌出初速度的测定方法",self.pdfHelp14)
		self.regAction(u"帮助文档/相关规范",u"中国煤炭分类国家标准",u"中国煤炭分类国家标准",self.pdfHelp15)
		self.regAction(u"帮助文档/相关规范",u"保护层开采技术规范",u"保护层开采技术规范",self.pdfHelp16)
		self.regAction(u"帮助文档/相关规范",u"煤与瓦斯突出矿井鉴定规范（AQ1024-2006）",u"煤与瓦斯突出矿井鉴定规范（AQ1024-2006）",self.pdfHelp17)
		self.regAction(u"帮助文档/相关规范",u"煤矿瓦斯抽放规范AQ1027-2006",u"煤矿瓦斯抽放规范AQ1027-2006",self.pdfHelp18)
		self.regAction(u"帮助文档/相关规范",u"电子等容式瓦斯解吸仪技术条件",u"电子等容式瓦斯解吸仪技术条件",self.pdfHelp19)
		self.regAction(u"帮助文档/相关规范",u"矿井瓦斯等级鉴定规范AQ1025-2006",u"矿井瓦斯等级鉴定规范AQ1025-2006",self.pdfHelp20)
		self.regAction(u"帮助文档/相关规范",u"钻孔瓦斯涌出初速度的测定方法",u"钻孔瓦斯涌出初速度的测定方法",self.pdfHelp21)

		# 多级菜单测试
		# self.regAction(u"测试2/test/help", u"采空区", u"采空区瓦斯抽采辅助设计", self.goafGasDesign)
		# self.regAction(u"测试2/test", u"采空区", u"采空区瓦斯抽采辅助设计", self.goafGasDesign)
		# self.regAction(u"测试2/test", u"采空区", u"采空区瓦斯抽采辅助设计", self.goafGasDesign)

	def createMenusToolBars(self):
		menus = {}
		toolBars = {}
		for menu,name,tip,trigger in self.myActions:
			action = self.buildAction(name,tip,trigger)
			if name == u"登录":
				self.loginAction = action
				self.loginAction.setEnabled(False)
			elif name == u"注销":
				self.logoutAction = action
			elif menu[0] == u'/' or name[0] == u'/':
				continue

			# 确定当前菜单的上级菜单(或者叫 父菜单)
			# 如果是1级菜单,则上级菜单就是menuBar()
			# 用上面的例子: 'help' 是 'help/test'的父菜单, 'help/test' 是 'help/test/xx'的上级菜单(父菜单)
			parent_menu = self.menuBar()
			# 将菜单名称按符号 / 进行分解
			menu_list = menu.split(u'/')
			# 菜单的级别(1级菜单、2级菜单、3级菜单等等)
			n = len(menu_list)
			# 构造菜单名
			# 比如: menu = 'help/test/xx'
			#   则: menu_list = ['help', 'test', 'xx']
			#       child_menus = ['help', 'help/test', 'help/test/xx']
			child_menus = [u'/'.join(menu_list[:i+1]) for i in range(n)]
			# print menu_list
			# print child_menus
			# 遍历每个子菜单
			for i, child_menu in enumerate(child_menus):
				if i > 0:
					parent_menu = menus[child_menus[i-1]]
				# 如果菜单缓存中menus没有记录,则新建一个QMenu
				if child_menu not in menus:
					# addMenu函数的C++原型定义: QMenu* QMenu::addMenu(title)
					menus[child_menu] = parent_menu.addMenu(menu_list[i])
			# 级联菜单的名字
			parent_menu = menus[child_menus[-1]]
			# 菜单关联到具体的Action上
			parent_menu.addAction(action)
			# 工具栏按钮关联到具体的Action上
			# toolBars[menu] = self.addToolBar(menu)
			# 增加工具栏
			# toolBars[menu].addAction(action)

	def createStatusBar(self):
		self.statusBar().showMessage(u"欢迎使用\"井下煤层气规模化抽采计算机辅助设计系统\"")


def loginFirst():
	"""返回True或False"""
	dialog = LoginDlg()
	if dialog.exec_():
		return True
	else:
		return False

# 设置皮肤样式
def SetStyle(app, styleName):
	# 从css文件读取样式
	file = QtCore.QFile(QtCore.QString(":/images/%1.css").arg(styleName))
	file.open(QtCore.QFile.ReadOnly)
	qss = QtCore.QString(file.readAll())
	file.close()

	# app全局设置样式
	app.setStyleSheet(qss)
	app.setPalette(QtGui.QPalette(QtGui.QColor("#F0F0F0")))


# 设置编码为UTF8
def SetUTF8Code(app):
	codec = QtCore.QTextCodec.codecForName("UTF-8")
	QtCore.QTextCodec.setCodecForLocale(codec)
	QtCore.QTextCodec.setCodecForCStrings(codec)
	QtCore.QTextCodec.setCodecForTr(codec)

# 加载中文字符
def SetChinese(app):
	translator = QtCore.QTranslator(app)
	translator.load(":/images/qt_zh_CN.qm")
	app.installTranslator(translator)

def run():
	import sys
	app = QtGui.QApplication(sys.argv)
	# 设置utf-8编码
	SetUTF8Code(app)
	# 设置样式
	SetStyle(app, 'blue')
	# 设置qt中文界面(消息框、菜单之类的默认使用中文)
	SetChinese(app)
	# 首先启动登录窗口
	if loginFirst():
		#启动CAD
		# doc.RunCAD()
		# 登录成功后启动主界面
		mw = MainWindow()
		mw.show()
		# 进入消息循环
		app.exec_()
		# 注销(清空sys_info表)
		DataHelper.sql_logout()