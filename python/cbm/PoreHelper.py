#coding:utf-8

from math import sqrt, pow, exp, sin, cos, tan, radians, log10

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from cbm.ttypes import *

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import griddata

# 钻孔坐标计算

# 1 掘进面煤层气规模化抽采技术
# 1.1 底板岩巷密集穿层钻孔抽采煤巷条带瓦斯
# 基本思路:
# 不考虑煤层倾角,因为最终要计算的是钻孔的相对长度、倾角和方位角
# 与真实的坐标无关,因此可以转换为相对坐标系

class P11:
	def __init__(self):
		pass

	def init(self):
		pass

	# 计算煤层上的钻孔xyz坐标
	def caclPoreXYZ(self):
		pass

	# 计算底板行的钻场坐标
	def caclSiteXYZ(self):
		pass
	