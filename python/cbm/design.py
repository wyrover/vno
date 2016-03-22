#-*- coding:utf-8 -*-
#!/usr/bin/env python

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from rpc.RpcClient import *

from cbm.ttypes import *
import rpc.SQL as SQL

def test_copy_obj():
	# sql_coal = SQLClientHelper.GetCoalById(5)
	# print sql_coal
	# coal = Coal()
	# print coal
	# print CbmUtil.CopyAttribsOfCbmType("Coal", sql_coal, coal)
	# print coal

	coal_lists = SQLClientHelper.GetCoalListByForeignKey("mine_id", 1)
	# coal_lists = SQLClientHelper.GetCoalListByField1("mine_id", '1')
	print coal_lists[0].name.decode('utf-8')
	# print SQLClientHelper.GetCoalByForeignKey('mine_id', '1')
	# print SQLClientHelper.GetCoalListByForeignKey('mine_id', '1')
	# print SQLClientHelper.GetCoalById('1')

def test_draw_coal_occurrence_graph():
	mine_id = 4
	CbmClientHelper.SendCommandToCAD("JL.DrawOccurrenceGraph %d %.1f" % (mine_id, 1), True)

def test_draw_graph_11():
	coal_id, tech_id = 5, 1
	CbmClientHelper.SendCommandToCAD("JL.DrawPlaneGraph11 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawHeadGraph11 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawDipGraph11 %d %d" % (coal_id, tech_id), True)

def test_draw_graph_12():
	coal_id, tech_id = 5, 1
	CbmClientHelper.SendCommandToCAD("JL.DrawPlaneGraph12 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawHeadGraph12 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawDipGraph12 %d %d" % (coal_id, tech_id), True)

def test_draw_graph_21():
	coal_id, tech_id = 5, 1
	CbmClientHelper.SendCommandToCAD("JL.DrawPlaneGraph21 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawHeadGraph21 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawDipGraph21 %d %d" % (coal_id, tech_id), True)

def test_draw_graph_23():
	coal_id, tech_id = 5, 1
	CbmClientHelper.SendCommandToCAD("JL.DrawPlaneGraph23 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawHeadGraph23 %d %d" % (coal_id, tech_id), True)
	# CbmClientHelper.SendCommandToCAD("JL.DrawDipGraph23 %d %d" % (coal_id, tech_id), True)	

# 计算评价单元的距离
def Lf(Ln, T, V):
	c1, c2 = 3.0/7.0, 10.0/7.0
	Ln_1 = Ln - c2*T*V
	if Ln_1 <= 0:
		return []

	Li = [Ln, Ln_1]
	while True:
		Ln_1 = c2*Ln_1-c1*Ln - c1*T*V
		if Ln_1 > 0:
			Li.append(Ln_1)
		else:
			break
	Li.reverse()
	return Li

def test_new_design_eval_unit():
	# 准备一组新数据
	deup = DesignEvalUnitPartition()
	deup.l1 = 1000.0
	deup.l2 = 400.0
	deup.l = 800.0
	deup.w = 4.0
	deup.h = 4.0
	deup.v = 5.0
	deup.t = 50
	deup.r = 4.0
	partition_id = SQLClientHelper.AddDesignEvalUnitPartition(deup)
	# print deup
	if(partition_id < 0):
		print 'faild!'
	else:
		print 'new id:%d' % partition_id
	return partition_id

# 评价单元划分设计
def test_design_eval_unit():
	# 指定一个设计id
	partition_id = 21
	# 查询得到评价单元划分
	deup = SQLClientHelper.GetDesignEvalUnitPartitionById(partition_id)
	if deup.id <= 0: return

	# 工作面顺槽长度Ln、巷道掘进速度V、巷道终点钻孔的抽采时间T、抽采半径R
	Ln, V, T, R = deup.l, deup.v, deup.t, deup.r

	# 计算各单元边界线与巷道交点到巷道起点的距离
	Li = Lf(Ln, T, V)

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

def test_draw_desigin_eval_unit():
	coal_id, eval_unit_partition_id = 5, 21
	CbmClientHelper.SendCommandToCAD("JL.DrawEvalUnitGraph %d" % eval_unit_partition_id, True)