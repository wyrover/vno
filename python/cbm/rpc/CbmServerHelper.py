#-*- coding:utf-8 -*-
#!/usr/bin/env python

import os
import uuid
# import threading
import subprocess
import tempfile
from time import ctime,sleep
from math import sqrt, pow, exp

# 导入sqlalchemy模块
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm.exc import NoResultFound
from sqlalchemy.orm.exc import MultipleResultsFound
# from sqlalchemy.ext.declarative import declarative_base

from cbm import CbmService
from cbm.ttypes import *

import SQL
import CbmUtil
import ThriftServerHelper
import SQLServerHelper

#初始化sqlalchemy，连接mysql数据库
def init_sqlalchemy():
    #连接mysql数据并创建session会话
    # engine = create_engine("mysql+pymysql:# root:@localhost/cbm?charset=utf-8")
    #echo开关用于调试!!!
    engine = create_engine("mysql+pymysql://root:@localhost/cbm",echo=True)
    Session = sessionmaker()
    Session.configure(bind=engine)
    return Session

# 利用tempfile模块生成临时文件名
def gen_temp_filename():
    temp = tempfile.NamedTemporaryFile(mode='w+t')
    temp_fname = temp.name;
    temp.close() # 关闭的时候自动会删除临时文件
    return temp_fname

# cad发送过来的数据缓存
POST_DATA_FROM_CAD_CACHE = {}

# 参考:处理多个service(http:# blog.csdn.net/hivon/article/details/11681977)
# sqlalchemy的两种方法详解(http:# www.it165.net/database/html/201404/6034.html)
# service接口处理类
class CbmServiceHandler(SQLServerHelper.SQLServiceHandler):
    def __init__(self, Session):
        self.session = Session()
        # 解决mysql中文乱码问题
        self.session.execute("set names 'utf8'")
        # 调用基类的初始化方法
        super(CbmServiceHandler, self).__init__(self.session)

    def InitSampleMine(self, region_id, account_id, name):
        query = self.session.query(SQL.Mine).filter(SQL.Mine.mine_region_id==region_id, SQL.Mine.account_id==account_id).first()
        if query is None:
            mine = SQL.Mine()
            mine.name = '示范矿区矿井-%s' % name
            mine.mine_region_id = region_id
            mine.account_id = account_id
            self.session.add(mine)
            self.session.flush()
            self.session.commit()

    def InitSampleRegion(self):
        try:
            # 查找管理员帐户
            admin = self.session.query(SQL.Account).filter(SQL.Account.username=='admin').first()
            if admin is None:
                admin = SQL.Account()
                admin.username = 'adminx'
                admin.password = '123'
                admin.comment = '超级管理员'
                self.session.add(admin)
                self.session.flush()
                self.session.commit()
                print admin.id
            # 查找三个示范矿区
            jincheng = self.session.query(SQL.MineRegion).filter(SQL.MineRegion.name=='晋城').first()
            lianghuai = self.session.query(SQL.MineRegion).filter(SQL.MineRegion.name=='两淮').first()
            songzao = self.session.query(SQL.MineRegion).filter(SQL.MineRegion.name=='松藻').first()
            # 根据id依次初始化示范矿区的数据
            self.InitSampleMine(jincheng.id, admin.id, "晋城")
            self.InitSampleMine(lianghuai.id, admin.id, "两淮")
            self.InitSampleMine(songzao.id, admin.id, "松藻")
        except Exception, e:
            print e
    
    def GetOnlineAccountId(self):
        query = self.session.query(SQL.Account).join(SQL.SysInfo).first()
        if query is None:
            return -1
        else:
            return query.id

    def GetOnlineMine(self):
        mine = Mine()
        account_id = self.GetOnlineAccountId()
        if account_id > -1:
            query = self.session.query(SQL.Mine).filter(SQL.Mine.account_id==account_id).first()
            if query is None:
                mine.id = -1
            else:
                CbmUtil.CopyAttribsOfCbmType('Mine', query, mine, True)
        return mine

    def VerifyMineAccount(self, uname, pwd):
        print '. VerifyMineAccount'
        query = self.session.query(SQL.Account).filter(SQL.Account.username==uname)
        if query.count() == 0:
            return 0  # 用户名不存在
        elif query.count() > 1:
            return -2 # 内部错误(用户名不唯一)
        else:
            accout = query.one()
            if accout.password != pwd:
                return -1  # 密码错误
            else:
                return 1  # 用户名和密码均匹配

    def GetMineRegionsOfBase(self, baseName):
        mine_regions = []
        query = self.session.query(SQL.MineRegion).join(SQL.MineBase).filter(SQL.MineBase.name==baseName).all()
        mine_regions = [region.name for region in query]
        return mine_regions

    def GetBaseByRegion(self, regionName):
        query = self.session.query(SQL.MineBase).join(SQL.MineRegion).filter(SQL.MineRegion.name==regionName).first()
        if query is None:
            return ''
        else:
            return query.name

    def GetSampleMineOfRegion(self, regionName):
        sample_mine = Mine()
        query = self.session.query(SQL.Mine).join(SQL.MineRegion).filter(SQL.MineRegion.name==regionName).first()
        if query is None:
            sample_mine.id = -1
        else:
            # 通用复制函数
            CbmUtil.CopyAttribsOfCbmType('Mine', query, sample_mine, True)
        return sample_mine

    def GetSampleCoalOfRegion(self, regionName):
        sample_coal = Coal()      
        sample_mine = self.GetSampleMineOfRegion(regionName)
        if sample_mine.id > -1:
            query = self.session.query(SQL.Coal).filter(SQL.Coal.mine_id==sample_mine.id).first()
            if query is None:
                sample_coal.id = -1
            else:
                # 通用复制函数
                CbmUtil.CopyAttribsOfCbmType('Coal', query, sample_coal, True)
        return sample_coal

    def GetCoalNamesOfMine(self, mine_id):
        query = self.session.query(SQL.Coal).filter(SQL.Coal.mine_id==mine_id).all()
        return [coal.name for coal in query]

    def GetCoalIdsOfMine(self, mine_id):
        query = self.session.query(SQL.Coal).filter(SQL.Coal.mine_id==mine_id).all()
        return [coal.id for coal in query]

    def GetWorkAreasOfMine(self, mine_id):
        coal_ids = self.GetCoalIdsOfMine(mine_id)
        if len(coal_ids) == 0:
            return []

        query = self.session.query(SQL.WorkArea).filter(SQL.WorkArea.coal_id.in_(coal_ids)).all()
        if len(query) == 0:
            return []

        n = len(query)
        work_areas = [WorkArea() for i in range(n)]
        for i in range(n):
            CbmUtil.CopyAttribsOfCbmType('WorkArea', query[i], work_areas[i], True)
        return work_areas

    def GetWorkSurfsOfMine(self, mine_id):
        work_area_ids = self.GetWorkAreaIdsOfMine(mine_id)
        if len(work_area_ids) == 0:
            return []

        query = self.session.query(SQL.WorkSurf).filter(SQL.WorkSurf.work_area_id.in_(work_area_ids)).all()
        if len(query) == 0:
            return []

        n = len(query)
        work_surfs = [WorkSurf() for i in range(n)]
        for i in range(n):
            CbmUtil.CopyAttribsOfCbmType('WorkSurf', query[i], work_surfs[i], True)
        return work_surfs

    def GetDrillingSurfsOfMine(self, mine_id):
        work_area_ids = self.GetWorkAreaIdsOfMine(mine_id)
        if len(work_area_ids) == 0:
            return []

        query = self.session.query(SQL.DrillingSurf).filter(SQL.DrillingSurf.work_area_id.in_(work_area_ids)).all()
        if len(query) == 0:
            return []
        
        n = len(query)
        drilling_surfs = [DrillingSurf() for i in range(n)]
        for i in range(n):
            CbmUtil.CopyAttribsOfCbmType('DrillingSurf', query[i], drilling_surfs[i], True)
        return drilling_surfs

    def GetWorkAreaIdsOfMine(self, mine_id):
        coal_ids = self.GetCoalIdsOfMine(mine_id)
        if len(coal_ids) == 0:
            return []
        query = self.session.query(SQL.WorkArea).filter(SQL.WorkArea.coal_id.in_(coal_ids)).all()
        return [work_area.id for work_area in query]

    def GetWorkSurfIdsOfMine(self, mine_id):
        work_area_ids = self.GetWorkAreaIdsOfMine(mine_id)
        if len(work_area_ids) == 0:
            return []
        query = self.session.query(SQL.WorkSurf).filter(SQL.WorkSurf.work_area_id.in_(work_area_ids)).all()
        return [work_surf.id for work_surf in query]

    def GetDrillingSurfIdsOfMine(self, mine_id):
        work_area_ids = self.GetWorkAreaIdsOfMine(mine_id)
        if len(work_area_ids) == 0:
            return []
        query = self.session.query(SQL.DrillingSurf).filter(SQL.DrillingSurf.work_area_id.in_(work_area_ids)).all()
        return [drilling_surf.id for drilling_surf in query]

    def DifficultEval(self, coal):
        # 根据钻孔流量衰减系数 和 煤层透气性系数进行评价
        k1 = CbmUtil.DifficultEval1(coal.decay_alpha)
        k2 = CbmUtil.DifficultEval2(coal.permeability_lambda)
        return CbmUtil.DifficultEvalHelper(k1, k2)

    def DifficultEvalString(self, coal):
        s1 = PermeabilityString(coal.permeability_k)
        s2 = EvalDifficultString(coal.eval_difficult)
        return "该煤层属于:%s\\n瓦斯抽采难易程度:%s" % (s1, s2)

    def MineGasReservesW1(self, mine_id):
       query = self.session.query(SQL.Coal).filter(SQL.Coal.mine_id==mine_id, SQL.Coal.minable==1).all()
       return sum([coal.res_a1*coal.gas_x1 for coal in query])
    
    def MineGasReservesW2(self, mine_id):
        query = self.session.query(SQL.Coal).filter(SQL.Coal.mine_id==mine_id, SQL.Coal.minable==0).all()
        if len(query) == 0:
            return 0
        else:
            return sum([coal.res_a1*coal.gas_x1 for coal in query])

    def WorkAreaGasFlow(self, work_area, K1):
        query = self.session.query(SQL.WorkSurf).filter(SQL.WorkSurf.work_area_id==work_area.id).all()
        S1 = sum([ws.qr*ws.a for ws in query])
        query = self.session.query(SQL.DrillingSurf).filter(SQL.DrillingSurf.work_area_id==work_area.id).all()
        S2 = sum([tws.qa for tws in query])
        if work_area.a <= 0:
            return -1
        else:
            return K1*(S1+S2)/work_area.a

    def MineGasFlow(self, mine):
        work_areas = self.GetWorkAreasOfMine(mine.id)
        if len(work_areas) == 0:
            return 0.0

        S1 = sum([work_area.qr*work_area.a for work_area in work_areas])
        S2 = sum([work_area.a for work_area in work_areas])
        if S2 <= 0:
            return -1
        else:
            K2 = mine.gas_k2
            return K2*S1/S2

    def WorkSurfGasFlow1(self, coal, work_area, work_surf):
        K1 = work_surf.k1
        K2 = work_surf.k2
        K3 = work_surf.k3
        kf = work_surf.kf
        # 开采层厚度(????分层如何考虑???)
        m = coal.thick
        # 工作面采高
        M = coal.hw
        W0 = coal.gas_w0
        Wc = coal.gas_wc2

        # 计算开采层相对瓦斯涌出量q1
        if work_surf.layerable == 0:
            return K1 * K2 * K3 * ( W0 - Wc ) * m / M
        else:
            return K1 * K2 * K3 * ( W0 - Wc ) * kf

    def WorkSurfGasFlow2(self, coal, work_area, work_surf):
        query = self.session.query(SQL.AdjLayer).filter(SQL.AdjLayer.work_surf_id==work_surf.id).all()
        if len(query) == 0:
            return 0.0
        f = lambda adj_coal:(adj_coal.gas_w0-adj_coal.gas_wc2)*adj_coal.thick*adj_coal.gas_eta
        S = sum([f(adj_layer.coal) for adj_layer in query])
        M = coal.hw
        return S / M

    def DrillingSurfGasFlow(self, coal, drilling_surf, tunnel):
        # 计算q0
        Vr = coal.vr
        W0 = coal.gas_w0
        D = tunnel.d
        v = tunnel.v
        L = tunnel.l
        S = tunnel.s
        r = coal.rho
        Wc = coal.gas_wc2
        q0 = ( 0.0004 * pow( Vr, 2 ) + 0.16 ) * 0.026 * W0
        q3 = D * v * q0 * ( 2 * sqrt( L / v ) - 1 )
        q4 = S * v * r * ( W0 - Wc )
        qa = q3 + q4 #  掘进面瓦斯涌出量

        # 计算结果保存到参数结构体
        ret = DrillingSurfGasFlowResult()
        ret.q0 = q0
        ret.q3 = q3
        ret.q4 = q4
        ret.qa = qa
        return ret

    def GetAllPores(self, design_id):
        # 参考: http://mysrc.sinaapp.com/view_note/?id=455
        query = self.session.query(SQL.DesignPore).join(SQL.DesignSite, SQL.DesignPore.design_site_id==SQL.DesignSite.id).join(SQL.DesignTechnology, SQL.DesignTechnology.id==SQL.DesignSite.design_technology_id).filter(SQL.DesignTechnology.id==design_id).all()
        if len(query) == 0:
            return []

        n = len(query)
        pores = [DesignPore() for i in range(n)]
        for i in range(n):
            CbmUtil.CopyAttribsOfCbmType('DesignPore', query[i], pores[i], True)
        return pores

    def SendCommandToCAD(self, cmd, switch_to_cad):
        exe = 'tool\\send.exe'
        cmd_text = '%s %d %s' % (exe, int(switch_to_cad), cmd)
        # commands.getstatusoutput(cmd_text)
        p = subprocess.Popen(cmd_text, shell=False,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        # 与子进程进行交互,communicate()方法接受一个input参数
        # p.communicate(input=None)
        # 等待进程执行完毕
        p.wait()
        # 获取进程的返回值并判断
        # main函数执行的时候默认返回0表示执行成功,其它值则表示执行失败!
        return p.returncode == 0

    def RequestJsonDatasFromCAD(self, input_datas):
        global POST_DATA_FROM_CAD_CACHE
        # 生成36位密钥
        secret_key = str(uuid.uuid1())

        # 写入数据到临时文件
        temp = open(gen_temp_filename(), 'w')
        temp.writelines(map(lambda x:x.strip()+'\n',[input_datas, secret_key]))
        temp.close()

        # 给cad发送命令：JL.PostJsonDatas 数据文件
        self.SendCommandToCAD("%s %s" % ("JL.PostJsonDatas", temp_fname))
        # 返回组合密钥值
        print "服务端:分配密钥:", secret_key
        # 分配空间用于存放数据
        POST_DATA_FROM_CAD_CACHE[secret_key] = "{}"

        return secret_key

    def GetJsonDatasFromRpcCache(self, secret_key):
        if secret_key == "#":
            return "{}"
        global POST_DATA_FROM_CAD_CACHE
        print "服务端:从缓存中获取数据"
        if secret_key not in POST_DATA_FROM_CAD_CACHE:
            return "{}"
        else:
            out_datas = POST_DATA_FROM_CAD_CACHE[secret_key]
            del POST_DATA_FROM_CAD_CACHE[secret_key]
            return out_datas

    def PostJsonDatasFromCAD(self, secret_key, input_datas, out_datas):
        if secret_key == "#":
            return
        global POST_DATA_FROM_CAD_CACHE
        if secret_key in POST_DATA_FROM_CAD_CACHE:
            POST_DATA_FROM_CAD_CACHE[secret_key] = out_datas
            print '来自cad的数据:%s  密钥:%s' % (out_datas, secret_key)
        # print '服务端: 更新缓存:', POST_DATA_FROM_CAD_CACHE

# 创建服务器
def create_server(host, port):
     # sqlalchemy连接mysql数据库
    Session = init_sqlalchemy()
    # 构造rpc消息处理接口
    handler = CbmServiceHandler(Session)
    processor = CbmService.Processor(handler)
    # 创建thrift rpc服务器
    server = ThriftServerHelper.make_rpc_server(processor, host=host, port=port)
    return handler, server