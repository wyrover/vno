#coding:utf-8

import os
import subprocess
import threading

import MainWindow
import rpc_server

# 调用windows命令taskkill杀死程序
def kill_exe(exe):
	command = 'taskkill /F /IM %s' % exe
	os.system(command)

# 启动一个线程,运行rpc服务器
def run_rpc_server1():
	t1 = threading.Thread(target=rpc_server.main)
	t1.setDaemon(True)
	t1.start()
	return t1

#启动一个进程运行rpc服务器
def run_rpc_server2():
	subprocess.Popen("python rpc_server.py")

if __name__ =='__main__':
	# 启动一个线程,运行rpc服务器
	t1 = run_rpc_server1()
	# 启动一个进程运行rpc服务器
	# run_rpc_server2()

	# 启动主界面
	MainWindow.run()

	#杀死所有的python进程
	kill_exe('python.exe')
