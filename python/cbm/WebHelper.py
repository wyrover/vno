#-*- coding:utf-8 -*-

from PyQt4 import QtWebKit, QtCore, Qt, QtGui
import webbrowser

# qtwebkit使用参考资料:
# http://www.clanfei.com/2013/12/1733.html
# http://www.cnblogs.com/liulun/p/3433003.html

# 处理链接是在本地打开还是调用外部浏览器打开
class WebPage(QtWebKit.QWebPage):
	def __init__(self):
		super(WebPage, self).__init__()
 
	def acceptNavigationRequest(self, frame, request, type):
		if(type == QtWebKit.QWebPage.NavigationTypeLinkClicked):
			if(frame == self.mainFrame()):
				self.view().load(request.url())
			else:
				webbrowser.open(request.url().toString())
				return False
		return QtWebKit.QWebPage.acceptNavigationRequest(self, frame, request, type)

	# 伪造浏览器的user agent
	# 有些网站会屏蔽一些非浏览器客户端(主要是为了防止被爬虫)
	def userAgentForUrl(self, url):
		print u'修改浏览器的user agent'
		return 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36'

# 自定义简单浏览器
class WebBrowser(QtGui.QDialog):
	def __init__(self, parent, url='about:blank'):
		super(WebBrowser, self).__init__(parent)
		# 关闭窗口时自动销毁
		# self.setAttribute(Qt.Qt.WA_DeleteOnClose, True)
		# 显示最小和最大按钮
		self.setWindowFlags(self.windowFlags() | Qt.Qt.WindowCloseButtonHint | Qt.Qt.WindowMinimizeButtonHint | Qt.Qt.WindowMaximizeButtonHint)

		# 修改webkit全局设置
		default_settings = QtWebKit.QWebSettings.globalSettings()
		# 启用javascript支持
		default_settings.setAttribute(QtWebKit.QWebSettings.JavascriptEnabled,True)
		default_settings.setAttribute(QtWebKit.QWebSettings.JavascriptCanOpenWindows,True)
		# 启动开发者工具支持
		default_settings.setAttribute(QtWebKit.QWebSettings.DeveloperExtrasEnabled,True)
		default_settings.setAttribute(QtWebKit.QWebSettings.LocalContentCanAccessRemoteUrls,True)
		default_settings.setAttribute(QtWebKit.QWebSettings.LocalStorageEnabled,True)
		default_settings.setAttribute(QtWebKit.QWebSettings.PluginsEnabled,True)

		# 创建浏览器子窗口
		self.view = QtWebKit.QWebView()
		
		# 禁用浏览器的右键菜单(利用qwidget自带的方法)
		# self.view.setContextMenuPolicy(Qt.Qt.NoContextMenu)

		# 部分链接会调用外部浏览器打开
		self.page = WebPage()
		self.view.setPage(self.page)

		# 创建开发者工具子窗口
		self.wi = QtWebKit.QWebInspector()
		self.wi.setPage(self.view.page())

		# 加载url
		self.view.load(QtCore.QUrl(url))

		# 处理点击一些链接没有反应的问题
		self.view.page().setLinkDelegationPolicy(QtWebKit.QWebPage.DelegateAllLinks)
		self.view.page().linkClicked.connect(self.onLinkClicked)

		layout = QtGui.QVBoxLayout()
		layout.setMargin(0)
		layout.addWidget(self.view)
		layout.addWidget(self.wi)
		self.setLayout(layout)
		
		self.resize(800, 600)

	def onLinkClicked(self, url):
		self.view.load(QtCore.QUrl(url))

# 在某个窗口中弹出浏览器显示url
def show_web(parent, url):
	web = WebBrowser(parent, url)
	web.exec_()