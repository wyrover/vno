#coding:utf-8
import subprocess
import webbrowser
# import win32api
import threading
import win32process

# 启动一个线程,运行命令
def open_cmd(exeName,fileName=''):
	t1 = threading.Thread(target=OpenEXEFile,args = (exeName,fileName,))
	t1.setDaemon(True)
	t1.start()
	return t1

def OpenEXEFile(exeName,fileName=''):
	if type(fileName).__name__ != "unicode":
		fileName = fileName.decode('utf-8')
	fName = '%s %s' % (exeName, fileName)
	# 增加异常处理
	try:
		# win32api.ShellExecute(0, 'open', exeName, fileName,'',1)
		# subprocess.Popen(fName.encode('gb2312'))
		handle = win32process.CreateProcess(None, fName, None , None , 0 ,win32process.CREATE_NO_WINDOW, None , None ,win32process.STARTUPINFO())
	except Exception, e:
		print e


def OpenPDFFile(pdfFile):
	open_cmd('tool\\pdf.exe',pdfFile)

def OpenNet(url):
	fileName = url
	if type(fileName).__name__ != "unicode":
		fileName = fileName.decode('utf-8')
	webbrowser.open(fileName)

def CreatReport(jsonFile):
	open_cmd('tool\\report.exe',jsonFile)

def RunCAD():
	open_cmd('tool\\Launcher.exe')

def OpenPNG(pngFile):
	open_cmd('tool\\ImageView.exe',pngFile)


