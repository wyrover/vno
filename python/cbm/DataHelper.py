#coding:utf-8

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
# from scipy import stats
from scipy.interpolate import griddata
# import statsmodels.api as sm
import matplotlib.pyplot as plt

import os
import os.path
import json
import datetime
import codecs
import urllib
from math import sqrt, pow, exp, sin, cos, tan, radians, log10, pi

import UiHelper
import DataHelper
import EncodeHelper
import doc

#pandas给matplotlib提供了一种ggplot绘图的扩展主题(可以认为类似于windows的主题),效果更好看
pd.set_option('display.mpl_style', 'default') # Make the graphs a bit prettier

#解决matplotlib中文问题
#注意:要放在pd.set_option的后面,否则pd.set_option会覆盖之前的matplotlib设置
import matplotlib as mpl
mpl.rcParams['font.family']='sans-serif'
mpl.rcParams['font.sans-serif'] = ['SimHei']  #指定默认字体
mpl.rcParams['axes.unicode_minus'] = False	#解决保存图像是负号'-'显示为方块的问题

# 枚举--抽采区域
class GasDesignRegion:
	DRILLING_SURF = 1  # 掘进工作面
	WORK_SURF = 2      # 回采工作面
	GOAF = 3           # 采空区

# 由于设计ui的时候,做了3个子菜单(回采面、掘进面、采空区)
# 但它们对应的都是连接一个slot函数,而现有的实现很难实现给slot函数传递参数的功能(可以做,但对本代码来说需要修改的就比较多了)
# 参见MainWindow中的wsGasDesign、twsGasDesign、goafGasDesign 这3个槽函数
GAS_DESIGN_REGION = GasDesignRegion.WORK_SURF

# 枚举--登录限制
class Authority:
	ADMIN = 1  # 只允许管理员登录
	USER = 2   # 只允许普通用户登录
	BOTH = 3   # 两者都可以

# 获取当前时间,格式: 2015-11-13 21:35:15
def current_time():
	now = datetime.datetime.now()
	return now.strftime('%Y-%m-%d %H:%M:%S')

# 用户登录(操作数据库)
def sql_login_user(account_id):
	# 设置当前登录用户(记录到sys_info表)
	sys_info = SysInfo()
	sys_info.account_id = account_id
	sys_info.last_login_time = current_time()
	SQLClientHelper.AddSysInfo(sys_info)

# 用户切换(操作数据库)
def sql_switch_user(account_id):
	sys_info = SQLClientHelper.GetSysInfoByFields({})
	sys_info.account_id = account_id
	sys_info.last_login_time = current_time()
	SQLClientHelper.UpdateSysInfo(sys_info)

# 注销(清空sys_info表)
def sql_logout():
	SQLClientHelper.DeleteMoreSysInfo(SQLClientHelper.GetSysInfoIds())

# 检查用户名是否已注册(操作数据库)
def sql_check_user(uname, pwd):
	return CbmClientHelper.VerifyMineAccount(uname, pwd) == 1

# 新建账户
def sql_create_user(uname, pwd):
	account = Account()
	account.username = uname
	account.password = pwd
	return SQLClientHelper.AddAccount(account)

# 新建煤层
def sql_create_coal(name, mine_id):
	coal = Coal()
	coal.name = name
	coal.mine_id = mine_id
	return SQLClientHelper.AddCoal(coal)

# 新建矿井
def sql_create_mine(name, province, city, region, account_id):
	mine = Mine()
	mine.name = name
	mine.province = province
	mine.city = city
	mine.mine_region_id = SQLClientHelper.GetMineRegionIdByField1('name', region)
	mine.account_id = account_id
	return SQLClientHelper.AddMine(mine)

# 管理员是否登录了
def sql_is_admin_online():
	admin = SQLClientHelper.GetAccountByField1('username', 'admin')
	if admin.id <= 0:
		return False
	else:
		# 查找当前登录账户
		account_id = CbmClientHelper.GetOnlineAccountId()
		return account_id == admin.id

# 登录验证
def sql_login_authority(authority):
	ret = False
	if authority == Authority.ADMIN:
		if sql_is_admin_online():
			ret = True
	elif authority == Authority.USER:
		if not sql_is_admin_online():
			ret = True
	elif authority == Authority.BOTH:
		ret = True
	return ret

# 查看登录状态(哪个用户登录了)
def sql_login_status():
	# 查找管理员账户
	admin = SQLClientHelper.GetAccountByField1('username', 'admin')
	if admin.id <= 0:
		return 0  # 内部错误(无管理员账户)
	else:
		# 查找当前登录账户
		account_id = CbmClientHelper.GetOnlineAccountId()
		if account_id <= 0:
			return 2  # 没有用户登录
		elif account_id == admin.id:
			return 3  # 管理员已登录
		else:
			mine_id = SQLClientHelper.GetMineIdByForeignKey('account_id', account_id)
			if mine_id <= 0: # 内部错误(用户没有关联的矿井)
				return -1
			else:		   # 普通用户已登陆
				return 1

def sql_create_work_area(name, coal_id):
	work_area = WorkArea()
	work_area.name = name
	work_area.coal_id = coal_id
	return SQLClientHelper.AddWorkArea(work_area)

def sql_create_work_surf(name, work_area_id):
	work_surf = WorkSurf()
	work_surf.name = name
	work_surf.work_area_id = work_area_id
	return SQLClientHelper.AddWorkSurf(work_surf)

def sql_create_drilling_surf(name, work_area_id):
	drilling_surf = DrillingSurf()
	drilling_surf.name = name
	drilling_surf.work_area_id = work_area_id
	return SQLClientHelper.AddDrillingSurf(drilling_surf)	

def permeability_lambda_to_k(p_lambda):
	return 0.025*p_lambda

def permeability_k_to_lambda(p_k):
	return p_k / 0.025

def dip_angle_type(angle):
	if angle <= 8:
		return 1 # 进水平
	elif angle <= 25:
		return 2 # 缓倾斜
	elif angle <= 45:
		return 3 # 倾斜
	else:
		return 4 # 急倾斜

# 计算评价单元的距离
def Lf(Ln, T, V):
	c1, c2 = 3.0/7.0, 10.0/7.0
	Ln_1 = Ln - c1*T*V
	if Ln_1 <= 0:
		return []

	Li = [Ln, Ln_1]
	while True:
		Ln_1 = c2*Ln_1 - c1*Ln - c1*T*V
		if Ln_1 > 0:
			Li.append(Ln_1)
		else:
			break
	Li.reverse()
	return Li

# 评价单元划分
def design_eval_unit(partition_id):
	# 查询得到评价单元划分
	deup = SQLClientHelper.GetDesignEvalUnitPartitionById(partition_id)
	if deup.id <= 0: return
	# 删除所有与划分id号关联的评价单元
	eval_unit_id_lists = SQLClientHelper.GetDesignEvalUnitIdListByForeignKey('design_eval_unit_partition_id', partition_id)
	SQLClientHelper.DeleteMoreDesignEvalUnit(eval_unit_id_lists)

	# 工作面顺槽长度Ln、巷道掘进速度V、巷道终点钻孔的抽采时间T、抽采半径R
	Ln, V, T, R = deup.l, deup.v, deup.t, deup.r

	# 计算各单元边界线与巷道交点到巷道起点的距离
	Li = Lf(Ln, T, V)
	print Li

	# 计算各单元的起点抽采时间
	g = lambda x:int(round(1.0*(Ln-x)/V+T))
	Ti = [g(x) for x in Li]

	# 评价单元写入到数据库
	print u'单元号\tLi(m)\tTi(d)'
	for i, (x, t) in enumerate(zip(Li, Ti)):
		print u'%d\t%.1f\t%d' % (i+1, x, t)
		a_eval_unit = DesignEvalUnit()
		a_eval_unit.num = i+1
		a_eval_unit.l = x
		a_eval_unit.t = t
		a_eval_unit.design_eval_unit_partition_id = partition_id
		SQLClientHelper.AddDesignEvalUnit(a_eval_unit)

# 绘制曲线
def draw_curve(q0, alpha):
	T = np.arange(0, 60) # 时间
	# 新建一个figure
	fig = plt.figure(figsize=(8, 6))
	# 绘制曲线
	c = 1440*q0/alpha
	f = lambda t:c*(1- exp(-1*alpha*t))
	Q = [f(t) for t in T]
	Q0 = [c for t in T]
	k = [x/x0 for (x, x0) in zip(Q, Q0)]
	plt.subplot(211)
	plt.title(u'百米钻孔在不同时间t内可抽采的瓦斯总量$Q_t(q_0=%.1f, α=%.1f)$' % (q0, alpha))
	plt.xlabel(u'抽采时间$t(d)$')
	plt.ylabel(u'可抽瓦斯总量$Q_t(L)$')
	plt.grid(True)
	plt.plot(T, Q, label=u'$Q_t=1440q_0(1-e^{-αt})/α$')
	plt.plot(T, Q0, 'r--', label=u'$Q_∞$= %.1f ($L$)' % c)
	plt.legend(loc=0)

	plt.subplot(212)
	plt.title(u'钻孔抽采有效系数$k(q_0=%.1f, α=%.1f)$' % (q0, alpha))
	plt.xlabel(u'抽采时间$t(d)$')
	plt.ylabel(u'钻孔抽采有效系数$k(\%)$')
	plt.grid(True)
	plt.plot(T, k, 'g-', label=u'$k=(1-e^{-αt})*100\%$')
	plt.legend(loc=0)
	# 显示图形
	plt.show()


# 插值计算需要的数据表
# R0/r0=[10, 100]
_Y = [10,10,10,10,10,10,10,10,10,10,20,20,20,20,20,20,20,20,20,20,30,30,30,30,30,30,30,30,30,30,40,40,40,40,40,40,40,40,40,40,50,50,50,50,50,50,50,50,50,50,60,60,60,60,60,60,60,60,60,60,80,80,80,80,80,80,80,80,80,80,100,100,100,100,100,100,100,100,100,100]
# T0=[10, 1800]
_X = [10,20,30,90,180,270,360,720,1080,1800,10,20,30,90,180,270,360,720,1080,1800,10,20,30,90,180,270,360,720,1080,1800,10,20,30,90,180,270,360,720,1080,1800,10,20,30,90,180,270,360,720,1080,1800,10,20,30,90,180,270,360,720,1080,1800,10,20,30,90,180,270,360,720,1080,1800,10,20,30,90,180,270,360,720,1080,1800]
# η (lgχ=0)
_Z0 = [3.848,6.34,8.527,18.24,27.17,32.98,37.19,47.07,52.4,58.49,0.824,1.372,1.86,4.34,7.458,10.13,12.45,19.47,24.32,30.81,0.316,0.531,0.721,1.688,2.935,4.07,5.13,8.782,11.74,16.3,0.156,0.265,0.36,0.845,1.467,2.038,2.579,4.543,6.266,9.174,0.089,0.153,0.208,0.489,0.848,1.177,1.488,2.638,3.685,5.547,0.056,0.097,0.132,0.311,0.539,0.747,0.944,1.673,2.345,3.577,0.026,0.046,0.064,0.151,0.261,0.362,0.456,0.806,1.13,1.735,0.014,0.026,0.036,0.086,0.148,0.205,0.258,0.455,0.636,0.976]
# η (lgχ=1)
_Z1 = [19.48,28.65,34.52,50.06,58.5,62.79,65.54,71.22,73.98,76.87,4.714,8.085,10.93,22.09,30.81,35.99,39.56,47.51,51.62,56.2,1.834,3.194,4.431,10.33,16.3,20.44,23.56,31.2,35.49,40.49,0.918,1.597,2.221,5.431,9.174,12.08,14.44,20.8,24.7,29.51,0.531,0.923,1.282,3.173,5.547,7.534,9.232,14.2,17.52,21.85,0.338,0.586,0.814,2.015,3.577,4.948,6.165,9.965,12.69,16.44,0.164,0.284,0.394,0.97,1.735,2.437,3.089,5.308,7.073,9.749,0.093,0.161,0.223,0.547,0.976,1.375,1.753,3.105,4.253,6.119]
# η (lgχ=2)
_Z2 = [51.43,59.66,63.82,72.79,76.86,78.84,79.99,81.82,82.34,82.76,23.37,32.16,37.31,49.83,56.2,59.36,61.37,65.46,67.37,69.45,11.13,17.34,21.57,33.59,40.49,44.06,46.38,51.21,53.59,56.12,5.901,9.88,12.92,22.94,29.51,33.1,35.47,40.55,43.1,45.87,3.459,6.017,8.128,16.01,21.85,25.24,27.54,32.59,35.18,38.04,2.199,3.897,5.369,11.42,16.44,19.52,21.67,26.54,29.1,31.97,1.059,1.896,2.659,6.237,9.748,12.14,13.91,18.2,20.57,23.32,0.597,1.067,1.503,3.701,6.119,7.908,9.309,12.92,15.04,17.58]
# η (lgχ=3)
_Z3 = [73.65,77.81,79.82,83.45,85,85.65,85.99,86.53,86.96,87.1,50.85,57.02,60.06,66.37,69.11,70.2,70.69,71.19,71.31,71.36,34.69,41.45,44.93,52.55,56.12,57.8,58.87,60.83,61.49,61.92,23.96,30.47,33.98,41.99,45.87,47.77,48.95,51.31,52.41,53.38,16.88,22.74,26.09,34.05,38.04,40.01,41.25,43.76,44.99,46.2,12.15,17.24,20.31,27.98,31.97,33.96,35.23,37.83,39.1,40.43,6.712,10.35,12.78,19.52,23.32,25.27,26.53,29.16,30.44,31.81,4.013,6.559,8.41,14.09,17.58,19.44,20.65,23.22,24.49,25.87]

# 根据不同的χ值判断使用哪一个表的数据
def get_z_datas(k):
	if k <= 0:
		return []
	# 对lgk四舍五入
	k = int(round(log10(k)))
	if k <= 0:
		return _Z0
	elif k == 1:
		return _Z1
	elif k == 2:
		return _Z2
	elif k >= 3:
		return _Z3

# 瓦斯抽采优化
# 抽采率η=f(T0, R0/r0, χ)是关于这3个因变量的一个复杂函数
# 为了便于描述，将函数改写成 z=f(x,y,k)
# 其中 x=T0, y=R0/r0, k=χ 或 lgχ
# 给定这3个变量,通过线性插值得到抽采率η
# griddata用法: http://hyry.dip.jp/tech/slice/slice.html/25
# 注意:k的取值是固定的!!!k={1, 10, 100, 1000}
class GasDrillingOpt:
	def __init__(self, npts=100):
		pass
		# 下面的代码目前还暂时没用上,也许绘制二维等值线图可能会用到
		# 划分网格
		# x_min, x_max = np.min(_X), np.max(_X)
		# y_min, y_max = np.min(_Y), np.max(_Y)
		# Xg = np.linspace(x_min, x_max, npts)
		# Yg = np.linspace(y_min, y_max, npts)

		# # 建立网格数据(后续计算可能会用到)
		# self.x_min = x_min
		# self.x_max = x_max
		# self.y_min = y_min
		# self.y_max = y_max
		# self.Xg = Xg
		# self.Yg = Yg

	# 已知x=T0, y=R0/r0, k=χ计算单点(x, y)的抽采率η
	def zValue(self, x, y, k):
		print 'zValue: x:%.1f, y:%.1f, k:%.1f' % (x, y, k)
		# 根据χ的取值决定用哪个Z值数据
		_Z = get_z_datas(k)
		# k的取值范围不在{1, 10, 100, 1000}之间
		if len(_Z) == 0:
			return 0
		elif x < 10 or x > 1800:
			return 0
		elif y < 10 or y > 100:
			return 0
		else:
			# 线性插值计算(x, y)
			return griddata((_X, _Y), _Z, (x, y), method='linear')

	def zValues(self, X, Y, k):
		# 根据χ的取值决定用哪个Z值数据
		_Z = get_z_datas(k)
		# k的取值范围不在{1, 10, 100, 1000}之间
		if len(_Z) == 0:
			return [0 for x in X]
		else:
			# 线性插值计算(x, y)
			return griddata((_X, _Y), _Z, (X, Y), method='linear')

	# 已知x的值,以及一组Y数据,计算每个点的抽采率η
	# 主要用于观察y与η的关系
	def zValues1(self, x, Y, k):
		X = [x for y in Y]
		return self.zValues(X, Y, k)
	# 已知y的值,以及一组X数据,计算每个点的抽采率η
	# 主要用于观察x与η的关系
	def zValues2(self, X, y, k):
		Y = [y for x in X]
		return self.zValues(X, Y, k)

	# 已知x=T0, y=R0/r0, k=χ计算单点(x, y)的抽采率η
	def xValue(self, y, z, k):
		print 'xValue: y:%.1f, z:%.1f, k:%.1f' % (y, z, k)
		# 根据χ的取值决定用哪个Z值数据
		_Z = get_z_datas(k)
		# k的取值范围不在{1, 10, 100, 1000}之间
		if len(_Z) == 0:
			return 0
		elif z < 0 or z > 100:
			return 0
		elif y < 10 or y > 100:
			return 0
		else:
			# 线性插值计算(x, y)
			return griddata((_Y, _Z), _X, (y, z), method='linear')

	def xValues(self, Y, Z, k):
		# 根据χ的取值决定用哪个Z值数据
		_Z = get_z_datas(k)
		# k的取值范围不在{1, 10, 100, 1000}之间
		if len(_Z) == 0:
			return [0 for y in Y]
		else:
			# 线性插值计算(x, y)
			return griddata((_Y, _Z), _X, (Y, Z), method='linear')

	# 已知x的值,以及一组Y数据,计算每个点的抽采率η
	# 主要用于观察y与η的关系
	def xValues1(self, y, Z, k):
		Y = [y for z in Z]
		return self.zValues(Y, Z, k)
	# 已知y的值,以及一组X数据,计算每个点的抽采率η
	# 主要用于观察x与η的关系
	def xValues2(self, Y, z, k):
		Z = [z for y in Y]
		return self.zValues(Y, Z, k)

	# 已知x=T0, y=R0/r0, k=χ计算单点(x, y)的抽采率η
	def yValue(self, x, z, k):
		print 'yValue: x:%.1f, z:%.1f, k:%.1f' % (x, z, k)
		# 根据χ的取值决定用哪个Z值数据
		_Z = get_z_datas(k)
		# k的取值范围不在{1, 10, 100, 1000}之间
		if len(_Z) == 0:
			return 0
		elif x < 10 or x > 1800:
			return 0
		elif z < 0 or z > 100:
			return 0
		else:
			# 线性插值计算(x, y)
			return griddata((_X, _Z), _Y, (x, z), method='linear')
	def yValues(self, X, Z, k):
		_Z = get_z_datas(k)
		# k的取值范围不在{1, 10, 100, 1000}之间
		if len(_Z) == 0:
			return [0 for x in X]
		else:
			# 线性插值计算(x, y)
			return griddata((_X, _Z), _Y, (X, Z), method='linear')
	def yValues1(self, x, Z, k):
		X = [x for z in Z]
		return self.zValues(X, Z, k)
	def yValues2(self, X, z, k):
		Z = [z for x in X]
		return self.zValues(X, Z, k)

def R0_func(R1, h):
	if R1 <= 0 or h <= 0:
		return 0.0
	else:
		return sqrt(2*R1*h/pi)

def R1_func(R0, h):
	if R0 <= 0 or h <= 0:
		return 0.0
	else:
		return 0.5*pi*R0*R0/h

def gas_psai(permeability_lambda, p0, alpha, r0):
	return 4*permeability_lambda*pow(p0, 3.0/2)/ (alpha*r0*r0)


def DrawYZ_X(x, k):
	# 插值计算
	gdo = GasDrillingOpt()

	# 已知抽采时间T0, 分析R0/r0与抽采率的关系
	# X = np.arange(10, 1810, 10)
	Y = np.arange(10, 110, 10)
	Z = gdo.zValues1(x, Y, k)

	# 新建一个figure
	fig = plt.figure(figsize=(8, 6))
	# 绘制曲线
	# plt.subplot(211)
	plt.title(u'抽采率η与$R_0/r_0$的关系')
	plt.xlabel(u'钻孔间距与钻孔半径比值$R_0/r_0$')
	plt.ylabel(u'抽采率η')
	plt.grid(True)
	plt.plot(Y, Z, label=u'$η=f(R_0/r_0)$')
	plt.legend(loc=0)

	# 显示图形
	plt.show()

def DrawXZ_Y(y, k):
	# 插值计算
	gdo = GasDrillingOpt()

	# 已知抽采时间T0, 分析R0/r0与抽采率的关系
	# X = np.arange(10, 1810, 10)
	X = np.arange(10, 1810, 10)
	Z = gdo.zValues2(X, y, k)

	# 新建一个figure
	fig = plt.figure(figsize=(8, 6))
	# 绘制曲线
	# plt.subplot(211)
	plt.title(u'抽采率η与抽采时间$T_0$的关系')
	plt.xlabel(u'抽采时间$T_0$')
	plt.ylabel(u'抽采率η')
	plt.grid(True)
	plt.plot(X, Z, label=u'$η=f(T_0)$')
	plt.legend(loc=0)

	# 显示图形
	plt.show()

def DrawXYZ(x, y, k):
	# 插值计算
	gdo = GasDrillingOpt()

	# 已知抽采时间T0, 分析R0/r0与抽采率的关系
	# X = np.arange(10, 1810, 10)
	Y = np.arange(10, 110, 10)
	Z = gdo.zValues1(x, Y, k)

	# 新建一个figure
	fig = plt.figure(figsize=(8, 6))
	# 绘制曲线
	plt.subplot(211)
	# plt.subplot(211)
	plt.title(u'抽采率η与$R_0/r_0$的关系($T_0$=%d d)' % x)
	plt.xlabel(u'钻孔间距与钻孔半径比值$R_0/r_0$')
	plt.ylabel(u'抽采率η(%)')
	plt.grid(True)
	plt.plot(Y, Z, label=u'$η=f(R_0/r_0)$')
	plt.legend(loc=0)

	# 已知抽采时间T0, 分析R0/r0与抽采率的关系
	# X = np.arange(10, 1810, 10)
	X = np.arange(10, 1810, 10)
	Z = gdo.zValues2(X, y, k)

	# 绘制曲线
	plt.subplot(212)
	# plt.subplot(211)
	plt.title(u'抽采率η与抽采时间$T_0$的关系($R_0/r_0$=%.1f)' % y)
	plt.xlabel(u'抽采时间$T_0$(d)')
	plt.ylabel(u'抽采率η(%)')
	plt.grid(True)
	plt.plot(X, Z, label=u'$η=f(T_0)$')
	plt.legend(loc=0)

	# 显示图形
	plt.show()

# 生成json数据测试
def test_json(json_file):
	# 准备一个词典数据
	info={}
	info[u"code"]=1
	info[u"id"]=1900
	info[u"name"]=u'张三'
	info[u"sex"]=u'男'
	list=[info,info,info]
	json_data={}
	json_data[u"code"]=1
	json_data[u"id"]=1900
	json_data[u"name"]=u'张三'
	json_data[u"sex"]=u'男'
	json_data[u"info"]=info
	json_data[u"data"]=list
	jsonStr = json.dumps(data)
	print "jsonStr:",jsonStr

# 将json数据写入到文件
# 输出json文件的2种方法:
	# (1) 新建文件(使用何种编码和当前源代码py文件的编码有关)
	# f = open(json_file, 'w')
	# f.write(json.dumps(data))
	# f.close()
	# (2) http://www.2cto.com/kf/201411/351186.html
	#     http://www.tuicool.com/articles/YBbAzi
	#     http://blog.csdn.net/ys_073/article/details/9403039
	#     中文汉字总是被转换为unicode码, 在dumps函数中添加参数ensure_ascii=False即可解决
def write_json_file(json_data, json_file):
	with codecs.open(json_file, 'w', 'utf-8') as f:
		json.dump(json_data, f, ensure_ascii=False)

# 读取数据库生成json数据,数据,用于生成钻孔报表
# 注意: 为了减少错误,生成json数据的时候,所有的字符串建议都使用unicode!!!
#       本代码中字符串, 包括:[代码中定义的字符串]、[从数据库中读取的数据]都是utf-8编码的字节数组(str)
#       需要使用xxx.decode('utf-8')方法进行解码转换成unicode字符串!!!
def generateJsonFileOfPoreReport(coal_id, design_id, json_file):
	# 查找煤层
	coal = SQLClientHelper.GetCoalById(coal_id)
	if coal.id <= 0:return False
	# 查找矿井
	mine = SQLClientHelper.GetMineById(coal.mine_id)
	if mine.id  <= 0:return False
	# 查找掘进面的抽采技术
	tws_tech = SQLClientHelper.GetDesignDrillingSurfTechnologyById(design_id)
	if tws_tech.id <= 0:return False

	# json模块可以直接将词典转换成json编码串
	# 因此主要的
	json_data = {u"pore_header":[u"钻孔编号",u"钻孔长度",u"钻孔倾角",u"钻孔方位角"]}
	# 写入矿井名称(中文汉字必须要用unicode表示,所以需要进行解码decode)
	json_data[u'$*mine_name*$'] = mine.name.decode('utf-8')
	# 写入工作面名称
	json_data[u'$*work_face_name*$'] = 'F292'.decode('utf-8')
	# 写入底板岩巷距离煤层的垂距
	json_data[u'w_dist'] = tws_tech.v_offset
	# 写入水平投影距离
	json_data[u'h_offset'] = tws_tech.h_offset
	# 写入钻场间距
	json_data[u'site_gap'] = tws_tech.gs
	# 写入钻孔孔径
	json_data[u'pore_diameter'] = tws_tech.gp
	# 写入封孔长度
	json_data[u'$*pore_length*$'] = tws_tech.close_length
	# 写入word模板路径(使用绝对路径,避免出错!!!)
	# 中文汉字必须要用unicode表示,所以需要进行解码decode)
	json_data[u'tplPath'] = os.path.abspath(u".\\help\\doc\\tpl\\底板岩巷密集穿层钻孔抽采煤巷条带瓦斯抽采技术.doc")
	# 写入报告默认名称
	json_data[u"reportName"] = u'底板岩巷密集穿层钻孔抽采煤巷条带瓦斯抽采技术报告'
	# print json_data[u'tplPath'].encode('gbk')
	
	# 写入钻孔信息
	# ***待完善***

	# 生成json文件(utf-8编码)
	write_json_file(json_data, json_file)

'''
# 测试参数
params = {
	'mine_name':u"谢一矿",
	'face_name':u"W292",
	'w_dis': 100,
	'tunnel_name':"机巷",
	'h_offset':125,
	'site_gap':123,
	'pore_diameter':200,
	'pore_length':1256,
	'reportlet':'cbm.cpt',  # 模板文件路径
	'__bypagesize__':'true' # 是否按页面大小显示
}
'''
# 报表显示辅助方法
def show_report(params):
	# 确保所有字符串数据(包括key)都是utf-8编码
	# 将unicode字符串进行编码转换,因为urllib.urlencode方法只能处理str类型的字符串
	f = lambda s:s.encode('utf-8') if type(s).__name__ == "unicode" else s
	new_params = dict([(f(k), f(v)) for k, v in params.items()])
	if 'reportlet' not in new_params:
		print '参数中没有指定模板!(reportlet=???)'
	else:
		# 拼接url路径
		url = 'http://localhost:8081/WebReport/ReportServer?%s' %  urllib.urlencode(new_params)
		# 调用浏览器显示报表
		doc.OpenNet(url)

# 显示钻孔报表11
def show_report11(coal, tws_tech):
	# 生成参数
	params = {}
	# 矿井名称
	mine = SQLClientHelper.GetMineById(coal.mine_id)
	params['mine_name'] = mine.name
	# 工作面名称
	# 搜索矿井的所有工作面中的第一个(按道理应该是从界面中提供工作面名称!!!)
	work_surf_list = CbmClientHelper.GetWorkSurfsOfMine(mine.id)
	if len(work_surf_list) == 0:
		params['face_name'] = 'W292'
	else:
		params['face_name'] = work_surf_list[0].name
	# 底板岩巷距离煤层
	params['w_dis'] = tws_tech.v_offset
	# 水平投影距离
	params['h_offset'] = tws_tech.h_offset
	# 钻场间距
	params['site_gap'] = tws_tech.gs
	# 钻孔直径
	params['pore_diameter'] = tws_tech.dp
	# 钻孔间距
	params['pore_gap'] = tws_tech.gp
	# 封孔长度(界面中没有输入,网上搜的一个参照值)
	# http://wenku.baidu.com/link?url=4QOLWZsUfFu5zLewMQCeF_WRzYTWmBYE3SRyk1Cj_JTc1UzbZR54NNkrXUsKc1PDj1Kg4492gfSNaKweJTSWxVqz7VbM-b7G3IAbtcdifBy
	params['close_length'] = tws_tech.close_length
	# 模板文件路径(必须参数)
	params['reportlet'] = 'cbm11.cpt'
	# 设计方案id(必须参数)
	params['design_id'] = tws_tech.design_technology_id
	# 是否按页面大小显示
	params['__bypagesize__'] = 'true'
	# 查询所有钻孔
	print 'xxxxxxxxxxxxxxxxxxxxx:%d' % tws_tech.design_technology_id
	pore_lists = CbmClientHelper.GetAllPores(tws_tech.design_technology_id)
	# 计算钻孔个数
	params['pore_num'] = len(pore_lists)
	# 计算钻孔总长度
	params['pore_sum'] = sum([pore.length for pore in pore_lists])

	# 显示报表
	# params参数中的字符串数据包括key即可以是utf8编码的str字节数组,也可以是unicode字符串
	# show_report方法内部会自动处理
	show_report(params)

# 显示钻孔报表12
def show_report12(coal, tws_tech):
	# 生成参数
	params = {}
	# 矿井名称
	mine = SQLClientHelper.GetMineById(coal.mine_id)
	params['mine_name'] = mine.name
	# 工作面名称
	# 搜索矿井的所有工作面中的第一个(按道理应该是从界面中提供工作面名称!!!)
	work_surf_list = CbmClientHelper.GetWorkSurfsOfMine(mine.id)
	if len(work_surf_list) == 0:
		params['face_name'] = 'W292'
	else:
		params['face_name'] = work_surf_list[0].name
	# 条带长度
	params['strip_length'] = tws_tech.l_stripe
	# 上下左右帮距
	params['contrl_range_up'] = tws_tech.top_side
	params['contrl_range_down'] = tws_tech.bottom_side
	params['contrl_range_left'] = tws_tech.left_side
	params['contrl_range_right'] = tws_tech.right_side
	# 孔底间距
	params['gbp'] = tws_tech.gbp
	# 钻孔直径
	params['pore_diameter'] = tws_tech.dp
	# 钻孔间距
	params['pore_gap'] = tws_tech.gp
	# 封孔长度(界面中没有输入,网上搜的一个参照值)
	# http://wenku.baidu.com/link?url=4QOLWZsUfFu5zLewMQCeF_WRzYTWmBYE3SRyk1Cj_JTc1UzbZR54NNkrXUsKc1PDj1Kg4492gfSNaKweJTSWxVqz7VbM-b7G3IAbtcdifBy
	params['close_length'] = tws_tech.close_length
	# 巷道长度
	params['tunnel_length'] = tws_tech.lm
	# 循环个数
	params['cycle_num'] = int(tws_tech.lm / (tws_tech.l_stripe - tws_tech.leading_dist))
	# 模板文件路径(必须参数)
	params['reportlet'] = 'cbm12.cpt'
	# 设计方案id(必须参数)
	params['design_id'] = tws_tech.design_technology_id
	# 是否按页面大小显示
	params['__bypagesize__'] = 'true'
	# 查询所有钻孔
	pore_lists = CbmClientHelper.GetAllPores(tws_tech.design_technology_id)
	# 计算钻孔个数
	params['pore_num'] = len(pore_lists)
	# 计算钻孔总长度
	params['pore_sum'] = sum([pore.length for pore in pore_lists])

	# 显示报表
	# params参数中的字符串数据包括key即可以是utf8编码的str字节数组,也可以是unicode字符串
	# show_report方法内部会自动处理
	show_report(params)

# 显示钻孔报表21
def show_report21(coal, ws_tech):
	# 生成参数
	params = {}
	# 矿井名称
	mine = SQLClientHelper.GetMineById(coal.mine_id)
	params['mine_name'] = mine.name
	# 工作面名称
	# 搜索矿井的所有工作面中的第一个(按道理应该是从界面中提供工作面名称!!!)
	work_surf_list = CbmClientHelper.GetWorkSurfsOfMine(mine.id)
	if len(work_surf_list) == 0:
		params['face_name'] = 'W292'
	else:
		params['face_name'] = work_surf_list[0].name
	# 底板岩巷距离煤层
	params['w_dis'] = ws_tech.v_offset
	# 该参数有待商定????
	params['tunnel_name'] = '机巷'
	# 水平投影距离
	params['h_offset'] = ws_tech.h_offset
	# 钻场间距
	params['site_gap'] = ws_tech.gs
	# 钻孔直径
	params['pore_diameter'] = ws_tech.dp
	# 钻孔间距
	params['pore_gap'] = ws_tech.gp
	# 封孔长度(界面中没有输入,网上搜的一个参照值)
	# http://wenku.baidu.com/link?url=4QOLWZsUfFu5zLewMQCeF_WRzYTWmBYE3SRyk1Cj_JTc1UzbZR54NNkrXUsKc1PDj1Kg4492gfSNaKweJTSWxVqz7VbM-b7G3IAbtcdifBy
	params['close_length'] = ws_tech.close_length
	# 模板文件路径(必须参数)
	params['reportlet'] = 'cbm21.cpt'
	# 设计方案id(必须参数)
	params['design_id'] = ws_tech.design_technology_id
	# 是否按页面大小显示
	params['__bypagesize__'] = 'true'
	# 查询所有钻孔
	pore_lists = CbmClientHelper.GetAllPores(ws_tech.design_technology_id)
	# 计算钻孔个数
	params['pore_num'] = len(pore_lists)
	# 计算钻孔总长度
	params['pore_sum'] = sum([pore.length for pore in pore_lists])

	# 显示报表
	# params参数中的字符串数据包括key即可以是utf8编码的str字节数组,也可以是unicode字符串
	# show_report方法内部会自动处理
	show_report(params)

# 显示钻孔报表23
def show_report23(coal, ws_tech):
	# 生成参数
	params = {}
	# 矿井名称
	mine = SQLClientHelper.GetMineById(coal.mine_id)
	params['mine_name'] = mine.name
	# 工作面名称
	# 搜索矿井的所有工作面中的第一个(按道理应该是从界面中提供工作面名称!!!)
	work_surf_list = CbmClientHelper.GetWorkSurfsOfMine(mine.id)
	if len(work_surf_list) == 0:
		params['face_name'] = 'W292'
	else:
		params['face_name'] = work_surf_list[0].name
	# 工作面走向长度
	params['strike_length'] = ws_tech.l1
	# 工作面倾向长度
	params['tendency_length'] = ws_tech.l2
	# 钻孔压茬长度
	params['pore_stubble'] = ws_tech.pore_stubble
	# 钻孔间距
	# params['pore_gap'] = ws_tech.gp
	# 钻孔直径
	params['pore_diameter'] = ws_tech.dp
	# 钻孔间距
	params['pore_gap'] = ws_tech.gp
	# 封孔长度(界面中没有输入,网上搜的一个参照值)
	# http://wenku.baidu.com/link?url=4QOLWZsUfFu5zLewMQCeF_WRzYTWmBYE3SRyk1Cj_JTc1UzbZR54NNkrXUsKc1PDj1Kg4492gfSNaKweJTSWxVqz7VbM-b7G3IAbtcdifBy
	params['close_length'] = ws_tech.close_length
	# 模板文件路径(必须参数)
	params['reportlet'] = 'cbm23.cpt'
	# 设计方案id(必须参数)
	params['design_id'] = ws_tech.design_technology_id
	# 是否按页面大小显示
	params['__bypagesize__'] = 'true'
	# 查询所有钻孔
	pore_lists = CbmClientHelper.GetAllPores(ws_tech.design_technology_id)
	# 计算钻孔个数
	params['pore_num'] = len(pore_lists)
	# 计算钻孔总长度
	params['pore_sum'] = sum([pore.length for pore in pore_lists])

	# 显示报表
	# params参数中的字符串数据包括key即可以是utf8编码的str字节数组,也可以是unicode字符串
	# show_report方法内部会自动处理
	show_report(params)

# 显示钻孔报表23
def show_report32(coal, goaf_tech):
	# 生成参数
	params = {}
	# 矿井名称
	mine = SQLClientHelper.GetMineById(coal.mine_id)
	params['mine_name'] = mine.name
	# 工作面名称
	# 搜索矿井的所有工作面中的第一个(按道理应该是从界面中提供工作面名称!!!)
	work_surf_list = CbmClientHelper.GetWorkSurfsOfMine(mine.id)
	if len(work_surf_list) == 0:
		params['face_name'] = 'W292'
	else:
		params['face_name'] = work_surf_list[0].name
	# 工作面走向长度
	params['strike_length'] = goaf_tech.l1
	# 工作面倾向长度
	params['tendency_length'] = goaf_tech.l2
	# 钻孔压茬长度
	params['pore_stubble'] = goaf_tech.pore_stubble
	# 钻场间距
	params['site_gap'] = goaf_tech.gs
	# 钻孔直径
	params['pore_diameter'] = goaf_tech.dp
	# 钻孔间距
	params['pore_gap'] = goaf_tech.gp
	# 封孔长度(界面中没有输入,网上搜的一个参照值)
	# http://wenku.baidu.com/link?url=4QOLWZsUfFu5zLewMQCeF_WRzYTWmBYE3SRyk1Cj_JTc1UzbZR54NNkrXUsKc1PDj1Kg4492gfSNaKweJTSWxVqz7VbM-b7G3IAbtcdifBy
	params['close_length'] = goaf_tech.close_length
	# 开孔参数(这个字段不存在,临时保存在comment字段中,采用json格式保存)
	try:
		json_data = json.loads(goaf_tech.comment.decode('utf-8'))
		params['start_pore'] = json_data[u'begin_dist']
	except Exception, e:
		params['start_pore'] = 0.5
		# print e
	# 模板文件路径(必须参数)
	params['reportlet'] = 'cbm32.cpt'
	# 设计方案id(必须参数)
	params['design_id'] = goaf_tech.design_technology_id
	# 是否按页面大小显示
	params['__bypagesize__'] = 'true'
	# 查询所有钻孔
	pore_lists = CbmClientHelper.GetAllPores(goaf_tech.design_technology_id)
	# 计算钻孔个数
	params['pore_num'] = len(pore_lists)
	# 计算钻孔总长度
	params['pore_sum'] = sum([pore.length for pore in pore_lists])

	# 显示报表
	# params参数中的字符串数据包括key即可以是utf8编码的str字节数组,也可以是unicode字符串
	# show_report方法内部会自动处理
	show_report(params)