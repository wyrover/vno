#-*- coding:utf-8 -*-
#!/usr/bin/env python

from rpc import CbmUtil, SQLClientHelper, CbmClientHelper
from rpc.RpcClient import *

from cbm.ttypes import *
from cbm import CbmService

#����1
def QuitServer():
  pass

#����2
def VerifyMineAccount(client):
  username = raw_input('�������û���:')
  pwd = raw_input('����������:')
  ret = client.VerifyMineAccount(username, pwd)
  if ret == 0:
    print '�û���������'
  elif ret == -1:
    print '�������'
  elif ret == 1:
    print '�û�����������ȷ'
  else:
    print 'δ֪����'

#����3
def GetMineBaseNames(client):
  # mine_bases = client.GetMineBaseNames()
  mine_bases = SQLClientHelper.GetMineBaseNames()
  print 'ú̿�����б�:'
  for base in mine_bases:
    print '\t',base

def GetMineRegionsOfBase(client):
  baseName = raw_input('������ú̿��������:')
  mine_regions = client.GetMineRegionsOfBase(baseName)
  print '%s�Ŀ���:' % (baseName)
  for region in mine_regions:
    print '\t',region

def GetBaseByRegion(client):
  regionName = raw_input('���������������:')
  baseName = client.GetBaseByRegion(regionName)
  print '%s�Ļ���:%s' % (regionName, baseName)

def GetSampleMineOfRegion(client):
  regionName = raw_input('���������������:')
  mine = client.GetSampleMineOfRegion(regionName)
  print 'ʾ������:%s�������:%s' % (regionName, mine)

def GetSampleCoalOfRegion(client):
  regionName = raw_input('���������������:')
  coal = client.GetSampleCoalOfRegion(regionName)
  print 'ʾ������:%s������ú��:%s' % (regionName, coal)

def GetDrillingSurfIdsOfMine(client):
  mine_id = int(input('�������id:'))
  coal_names = client.GetDrillingSurfIdsOfMine(mine_id)
  print '��id=%d��ú���б�:' % mine_id
  for name in coal_names:
    print name

def GetCoalIdsOfMine(client):
  mine_id = int(input('�������id:'))
  coal_ids = client.GetCoalIdsOfMine(mine_id)
  print '��id=%d��ú���б�:' % mine_id
  for coal_id in coal_ids:
    print coal_id

def GetOnlineAccountId(client):
  account_id = client.GetOnlineAccountId()
  print '��ǰ��¼�û���id:%d' % account_id

def GetOnlineMine(client):
  mine = client.GetOnlineMine()
  print '��ǰ��¼�û���Ӧ�Ŀ�:',mine

def GetWorkAreasOfMine(client):
  mine_id = int(input('�������id:'))
  work_areas = client.GetWorkAreasOfMine(mine_id)
  print '��id=%d�Ĳ����б�:' % mine_id
  for work_area in work_areas:
    print work_area.id, work_area.name

def GetWorkSurfsOfMine(client):
  mine_id = int(input('�������id:'))
  work_surfs = client.GetWorkSurfsOfMine(mine_id)
  print '��id=%d�Ļزɹ������б�:' % mine_id
  for work_surf in work_surfs:
    print work_surf.id, work_surf.name

def GetDrillingSurfsOfMine(client):
  mine_id = int(input('�������id:'))
  drilling_surfs = client.GetDrillingSurfsOfMine(mine_id)
  print '��id=%d�ľ���������б�:' % mine_id
  for drilling_surf in drilling_surfs:
    print drilling_surf.id, drilling_surf.name

def InitSampleRegion(client):
  print '������������Ա�˻�������'
  client.InitSampleRegion()

def DifficultEval(client):
  # CbmUtil.CopyAttribsOfCbmType
  pass

def DifficultEvalString(client):
  mine_id = int(input('�������id:'))
  coal_ids = client.GetCoalIdsOfMine(mine_id)
  if len(coal_ids) == 0:
    print '�ÿ�û��ú��'
  else:
    print '�ÿ󾮵�ú���б�:', '  '.join([str(i) for i in coal_ids])
    coal_id = int(input('��ѡ��һ��ú��:'))

def MineGasReservesW1(client):
  pass

def MineGasReservesW2(client):
  pass

def WorkAreaGasFlow(client):
  pass

def MineGasFlow(client):
  pass

def WorkSurfGasFlow1(client):
  pass

def WorkSurfGasFlow2(client):
  pass

def DrillingSurfGasFlow(client):
  pass

def GetAccount(client):
  account_id = int(input('�������˻�id:'))
  # account = client.GetAccount(account_id)
  #account = client.GetAccountByFields1('id', '1')
  account = client.GetAccountByFields1('username', 'dlj')
  if account.id < 0:
    print '��ѯ����'
  else:
    print '�˻�id=%d ����:%s' % (account.id, account.username)

def GetMine(client):
  mine = client.GetMineByForeignKey('account_id', 2)
  if mine.id < 0:
    print '��ѯ����'
  else:
    print '��id=%d ����:%s' % (mine.id, mine.name)

def AddAccount(client):
  account = Account()
  account.username = raw_input('�½��û�:')
  account.password = raw_input('����:')

  account_id = client.AddAccount(account)
  print '�½��û���id=%d' % account_id

def DeleteAccount(client):
  pass

# ע�����еĲ��Ժ���
all_cmds = {
  '1': VerifyMineAccount,
  '2': GetMineBaseNames,
  '3': GetMineRegionsOfBase,
  '4': GetBaseByRegion,
  '5': GetSampleMineOfRegion,
  '6': GetSampleCoalOfRegion,
  '7': GetDrillingSurfIdsOfMine,
  '8': GetCoalIdsOfMine,
  '9': GetOnlineAccountId,
  '10': GetOnlineMine,
  '11': GetWorkAreasOfMine,
  '12': GetWorkSurfsOfMine,
  '13': GetDrillingSurfsOfMine,
  '14': InitSampleRegion,
  '15': DifficultEval,
  '16': DifficultEvalString,
  '17': MineGasReservesW1,
  '18': MineGasReservesW2,
  '19': WorkAreaGasFlow,
  '20': MineGasFlow,
  '21': WorkSurfGasFlow1,
  '22': WorkSurfGasFlow2,
  '23': DrillingSurfGasFlow,
  '24': GetAccount,
  '25': AddAccount,
  '26': GetMine,
  'q': QuitServer
}

'''
ע��:������start��close֮�����SQLClientHelper�ķ���
ԭ��:start��close������rpc������������ռ��ͬһ���˿�(9100)
     
'''
def test_cbm():
  try:  
    service_client = RpcClient(CbmService, port=PORT2)
    service_client.start()

    goto_quit = False
    while True:
      cmd = raw_input('����������:')
      if cmd == 'q' or cmd == 'Q':
        goto_quit = True
        break
      elif cmd == 'c' or cmd == 'C':
        break
      if cmd in all_cmds:
        all_cmds[cmd](service_client.get())
        print '\n'
      else:
        print '����%sδʵ��!!!' % cmd
    service_client.close()

    if goto_quit:
      # �ر�rpc������
      QuitServer()

  except Thrift.TException, tx:
    print '%s' % (tx.message)

import design

'''
����SQLClientHelperģ��
sqlalchemy��delete����������:
   http://segmentfault.com/q/1010000000130368
   http://www.keakon.net/2012/12/03/SQLAlchemy%E4%BD%BF%E7%94%A8%E7%BB%8F%E9%AA%8C
'''
def test_sql():
    print len(CbmClientHelper.GetAllPores(45))
    # print SQLClientHelper.GetMineBaseNames()
    # print CbmClientHelper.SendCommandToCAD("zoom a", True)
    # print CbmClientHelper.SendCommandToCAD("regen", False)
    # print CbmClientHelper.GetJsonDatasFromCAD("{}", 2)
    
    # design.test_copy_obj()
    # design.test_draw_coal_occurrence_graph()

    # design.test_draw_graph_11()
    # design.test_draw_graph_12()
    # design.test_draw_graph_21()
    # design.test_draw_graph_23()

    # design.test_new_design_eval_unit
    # design.test_design_eval_unit()
    # design.test_draw_desigin_eval_unit()

    # SQLClientHelper.DeleteMoreSysInfo(SQLClientHelper.GetSysInfoIds())

def main():
  if False:
    test_cbm()
  else:
    test_sql()

if __name__ == '__main__':
  main()	