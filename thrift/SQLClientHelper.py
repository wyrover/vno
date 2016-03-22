#-*- coding:utf-8 -*-

from cbm.ttypes import *
from cbm import CbmService
from RpcClient import RpcClient, HOST, PORT1, PORT2
import CbmUtil


#Account 类型的CRUD操作
def AddAccount(account):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddAccount(account)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteAccount(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteAccount(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateAccount(account):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateAccount(account)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetAccountById(id):
	_return = Account()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAccountByForeignKey(fkey, id):
	_return = Account()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAccountIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAccountList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreAccount(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreAccount(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreAccount(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreAccount(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetAccountByFields(fields):
	_return = Account()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAccountByField1(field, value):
	_return = Account()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAccountByField2(field1, value1, field2, value2):
	_return = Account()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAccountListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAccountIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAccountIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAccountIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAccountIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAccountIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#AdjLayer 类型的CRUD操作
def AddAdjLayer(adj_layer):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddAdjLayer(adj_layer)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteAdjLayer(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteAdjLayer(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateAdjLayer(adj_layer):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateAdjLayer(adj_layer)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetAdjLayerById(id):
	_return = AdjLayer()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAdjLayerByForeignKey(fkey, id):
	_return = AdjLayer()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAdjLayerIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAdjLayerList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreAdjLayer(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreAdjLayer(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreAdjLayer(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreAdjLayer(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetAdjLayerByFields(fields):
	_return = AdjLayer()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAdjLayerByField1(field, value):
	_return = AdjLayer()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAdjLayerByField2(field1, value1, field2, value2):
	_return = AdjLayer()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetAdjLayerListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAdjLayerIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAdjLayerIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetAdjLayerIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetAdjLayerIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetAdjLayerIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#Coal 类型的CRUD操作
def AddCoal(coal):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddCoal(coal)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteCoal(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteCoal(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateCoal(coal):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateCoal(coal)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetCoalById(id):
	_return = Coal()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetCoalByForeignKey(fkey, id):
	_return = Coal()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetCoalIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetCoalList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreCoal(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreCoal(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreCoal(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreCoal(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetCoalByFields(fields):
	_return = Coal()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetCoalByField1(field, value):
	_return = Coal()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetCoalByField2(field1, value1, field2, value2):
	_return = Coal()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetCoalListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetCoalIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetCoalIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetCoalIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetCoalIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetCoalIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#Complexity 类型的CRUD操作
def AddComplexity(complexity):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddComplexity(complexity)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteComplexity(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteComplexity(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateComplexity(complexity):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateComplexity(complexity)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetComplexityById(id):
	_return = Complexity()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetComplexityByForeignKey(fkey, id):
	_return = Complexity()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetComplexityIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetComplexityList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreComplexity(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreComplexity(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreComplexity(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreComplexity(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetComplexityByFields(fields):
	_return = Complexity()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetComplexityByField1(field, value):
	_return = Complexity()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetComplexityByField2(field1, value1, field2, value2):
	_return = Complexity()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetComplexityListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetComplexityIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetComplexityIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetComplexityIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetComplexityIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetComplexityIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignDrillingSurfTechnology 类型的CRUD操作
def AddDesignDrillingSurfTechnology(design_drilling_surf_technology):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignDrillingSurfTechnology(design_drilling_surf_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignDrillingSurfTechnology(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignDrillingSurfTechnology(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignDrillingSurfTechnology(design_drilling_surf_technology):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignDrillingSurfTechnology(design_drilling_surf_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignDrillingSurfTechnologyById(id):
	_return = DesignDrillingSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignDrillingSurfTechnologyByForeignKey(fkey, id):
	_return = DesignDrillingSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignDrillingSurfTechnologyIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignDrillingSurfTechnologyList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignDrillingSurfTechnology(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignDrillingSurfTechnology(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignDrillingSurfTechnology(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignDrillingSurfTechnology(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignDrillingSurfTechnologyByFields(fields):
	_return = DesignDrillingSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignDrillingSurfTechnologyByField1(field, value):
	_return = DesignDrillingSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignDrillingSurfTechnologyByField2(field1, value1, field2, value2):
	_return = DesignDrillingSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignDrillingSurfTechnologyListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignDrillingSurfTechnologyIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignDrillingSurfTechnologyIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignDrillingSurfTechnologyIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignDrillingSurfTechnologyIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignDrillingSurfTechnologyIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignEvalUnit 类型的CRUD操作
def AddDesignEvalUnit(design_eval_unit):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignEvalUnit(design_eval_unit)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignEvalUnit(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignEvalUnit(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignEvalUnit(design_eval_unit):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignEvalUnit(design_eval_unit)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignEvalUnitById(id):
	_return = DesignEvalUnit()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitByForeignKey(fkey, id):
	_return = DesignEvalUnit()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignEvalUnit(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignEvalUnit(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignEvalUnit(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignEvalUnit(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignEvalUnitByFields(fields):
	_return = DesignEvalUnit()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitByField1(field, value):
	_return = DesignEvalUnit()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitByField2(field1, value1, field2, value2):
	_return = DesignEvalUnit()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignEvalUnitPartition 类型的CRUD操作
def AddDesignEvalUnitPartition(design_eval_unit_partition):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignEvalUnitPartition(design_eval_unit_partition)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignEvalUnitPartition(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignEvalUnitPartition(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignEvalUnitPartition(design_eval_unit_partition):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignEvalUnitPartition(design_eval_unit_partition)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignEvalUnitPartitionById(id):
	_return = DesignEvalUnitPartition()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitPartitionByForeignKey(fkey, id):
	_return = DesignEvalUnitPartition()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitPartitionIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitPartitionList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignEvalUnitPartition(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignEvalUnitPartition(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignEvalUnitPartition(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignEvalUnitPartition(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignEvalUnitPartitionByFields(fields):
	_return = DesignEvalUnitPartition()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitPartitionByField1(field, value):
	_return = DesignEvalUnitPartition()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitPartitionByField2(field1, value1, field2, value2):
	_return = DesignEvalUnitPartition()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignEvalUnitPartitionListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitPartitionIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitPartitionIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignEvalUnitPartitionIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignEvalUnitPartitionIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignEvalUnitPartitionIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignGoafPore 类型的CRUD操作
def AddDesignGoafPore(design_goaf_pore):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignGoafPore(design_goaf_pore)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignGoafPore(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignGoafPore(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignGoafPore(design_goaf_pore):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignGoafPore(design_goaf_pore)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignGoafPoreById(id):
	_return = DesignGoafPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafPoreByForeignKey(fkey, id):
	_return = DesignGoafPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafPoreIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafPoreList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignGoafPore(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignGoafPore(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignGoafPore(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignGoafPore(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignGoafPoreByFields(fields):
	_return = DesignGoafPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafPoreByField1(field, value):
	_return = DesignGoafPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafPoreByField2(field1, value1, field2, value2):
	_return = DesignGoafPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafPoreListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafPoreIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafPoreIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafPoreIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafPoreIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafPoreIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignGoafTechnology 类型的CRUD操作
def AddDesignGoafTechnology(design_goaf_technology):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignGoafTechnology(design_goaf_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignGoafTechnology(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignGoafTechnology(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignGoafTechnology(design_goaf_technology):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignGoafTechnology(design_goaf_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignGoafTechnologyById(id):
	_return = DesignGoafTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafTechnologyByForeignKey(fkey, id):
	_return = DesignGoafTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafTechnologyIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafTechnologyList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignGoafTechnology(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignGoafTechnology(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignGoafTechnology(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignGoafTechnology(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignGoafTechnologyByFields(fields):
	_return = DesignGoafTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafTechnologyByField1(field, value):
	_return = DesignGoafTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafTechnologyByField2(field1, value1, field2, value2):
	_return = DesignGoafTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignGoafTechnologyListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafTechnologyIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafTechnologyIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignGoafTechnologyIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignGoafTechnologyIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignGoafTechnologyIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignPore 类型的CRUD操作
def AddDesignPore(design_pore):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignPore(design_pore)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignPore(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignPore(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignPore(design_pore):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignPore(design_pore)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignPoreById(id):
	_return = DesignPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignPoreByForeignKey(fkey, id):
	_return = DesignPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignPoreIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignPoreList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignPore(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignPore(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignPore(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignPore(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignPoreByFields(fields):
	_return = DesignPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignPoreByField1(field, value):
	_return = DesignPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignPoreByField2(field1, value1, field2, value2):
	_return = DesignPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignPoreListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignPoreIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignPoreIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignPoreIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignPoreIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignPoreIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignSite 类型的CRUD操作
def AddDesignSite(design_site):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignSite(design_site)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignSite(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignSite(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignSite(design_site):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignSite(design_site)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignSiteById(id):
	_return = DesignSite()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignSiteByForeignKey(fkey, id):
	_return = DesignSite()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignSiteIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignSiteList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignSite(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignSite(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignSite(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignSite(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignSiteByFields(fields):
	_return = DesignSite()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignSiteByField1(field, value):
	_return = DesignSite()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignSiteByField2(field1, value1, field2, value2):
	_return = DesignSite()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignSiteListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignSiteIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignSiteIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignSiteIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignSiteIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignSiteIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignTechnology 类型的CRUD操作
def AddDesignTechnology(design_technology):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignTechnology(design_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignTechnology(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignTechnology(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignTechnology(design_technology):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignTechnology(design_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignTechnologyById(id):
	_return = DesignTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTechnologyByForeignKey(fkey, id):
	_return = DesignTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTechnologyIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTechnologyList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignTechnology(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignTechnology(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignTechnology(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignTechnology(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignTechnologyByFields(fields):
	_return = DesignTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTechnologyByField1(field, value):
	_return = DesignTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTechnologyByField2(field1, value1, field2, value2):
	_return = DesignTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTechnologyListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTechnologyIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTechnologyIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTechnologyIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTechnologyIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTechnologyIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignTunnelControlPoint 类型的CRUD操作
def AddDesignTunnelControlPoint(design_tunnel_control_point):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignTunnelControlPoint(design_tunnel_control_point)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignTunnelControlPoint(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignTunnelControlPoint(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignTunnelControlPoint(design_tunnel_control_point):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignTunnelControlPoint(design_tunnel_control_point)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignTunnelControlPointById(id):
	_return = DesignTunnelControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTunnelControlPointByForeignKey(fkey, id):
	_return = DesignTunnelControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTunnelControlPointIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTunnelControlPointList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignTunnelControlPoint(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignTunnelControlPoint(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignTunnelControlPoint(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignTunnelControlPoint(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignTunnelControlPointByFields(fields):
	_return = DesignTunnelControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTunnelControlPointByField1(field, value):
	_return = DesignTunnelControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTunnelControlPointByField2(field1, value1, field2, value2):
	_return = DesignTunnelControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignTunnelControlPointListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTunnelControlPointIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTunnelControlPointIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignTunnelControlPointIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignTunnelControlPointIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignTunnelControlPointIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignWorkSurfControlPoint 类型的CRUD操作
def AddDesignWorkSurfControlPoint(design_work_surf_control_point):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignWorkSurfControlPoint(design_work_surf_control_point)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignWorkSurfControlPoint(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignWorkSurfControlPoint(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignWorkSurfControlPoint(design_work_surf_control_point):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignWorkSurfControlPoint(design_work_surf_control_point)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignWorkSurfControlPointById(id):
	_return = DesignWorkSurfControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfControlPointByForeignKey(fkey, id):
	_return = DesignWorkSurfControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfControlPointIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfControlPointList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignWorkSurfControlPoint(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignWorkSurfControlPoint(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignWorkSurfControlPoint(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignWorkSurfControlPoint(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignWorkSurfControlPointByFields(fields):
	_return = DesignWorkSurfControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfControlPointByField1(field, value):
	_return = DesignWorkSurfControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfControlPointByField2(field1, value1, field2, value2):
	_return = DesignWorkSurfControlPoint()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfControlPointListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfControlPointIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfControlPointIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfControlPointIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfControlPointIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfControlPointIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DesignWorkSurfTechnology 类型的CRUD操作
def AddDesignWorkSurfTechnology(design_work_surf_technology):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDesignWorkSurfTechnology(design_work_surf_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDesignWorkSurfTechnology(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDesignWorkSurfTechnology(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDesignWorkSurfTechnology(design_work_surf_technology):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDesignWorkSurfTechnology(design_work_surf_technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDesignWorkSurfTechnologyById(id):
	_return = DesignWorkSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfTechnologyByForeignKey(fkey, id):
	_return = DesignWorkSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfTechnologyIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfTechnologyList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDesignWorkSurfTechnology(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDesignWorkSurfTechnology(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDesignWorkSurfTechnology(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDesignWorkSurfTechnology(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDesignWorkSurfTechnologyByFields(fields):
	_return = DesignWorkSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfTechnologyByField1(field, value):
	_return = DesignWorkSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfTechnologyByField2(field1, value1, field2, value2):
	_return = DesignWorkSurfTechnology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDesignWorkSurfTechnologyListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfTechnologyIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfTechnologyIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDesignWorkSurfTechnologyIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDesignWorkSurfTechnologyIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDesignWorkSurfTechnologyIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DrillingRadiusParam 类型的CRUD操作
def AddDrillingRadiusParam(drilling_radius_param):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDrillingRadiusParam(drilling_radius_param)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDrillingRadiusParam(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDrillingRadiusParam(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDrillingRadiusParam(drilling_radius_param):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDrillingRadiusParam(drilling_radius_param)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDrillingRadiusParamById(id):
	_return = DrillingRadiusParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingRadiusParamByForeignKey(fkey, id):
	_return = DrillingRadiusParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingRadiusParamIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingRadiusParamList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDrillingRadiusParam(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDrillingRadiusParam(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDrillingRadiusParam(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDrillingRadiusParam(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDrillingRadiusParamByFields(fields):
	_return = DrillingRadiusParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingRadiusParamByField1(field, value):
	_return = DrillingRadiusParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingRadiusParamByField2(field1, value1, field2, value2):
	_return = DrillingRadiusParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingRadiusParamListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingRadiusParamIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingRadiusParamIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingRadiusParamIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingRadiusParamIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingRadiusParamIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#DrillingSurf 类型的CRUD操作
def AddDrillingSurf(drilling_surf):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddDrillingSurf(drilling_surf)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteDrillingSurf(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteDrillingSurf(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateDrillingSurf(drilling_surf):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateDrillingSurf(drilling_surf)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetDrillingSurfById(id):
	_return = DrillingSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingSurfByForeignKey(fkey, id):
	_return = DrillingSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingSurfIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingSurfList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreDrillingSurf(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreDrillingSurf(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreDrillingSurf(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreDrillingSurf(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetDrillingSurfByFields(fields):
	_return = DrillingSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingSurfByField1(field, value):
	_return = DrillingSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingSurfByField2(field1, value1, field2, value2):
	_return = DrillingSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetDrillingSurfListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingSurfIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingSurfIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetDrillingSurfIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetDrillingSurfIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetDrillingSurfIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#HighDrillingPore 类型的CRUD操作
def AddHighDrillingPore(high_drilling_pore):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddHighDrillingPore(high_drilling_pore)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteHighDrillingPore(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteHighDrillingPore(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateHighDrillingPore(high_drilling_pore):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateHighDrillingPore(high_drilling_pore)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetHighDrillingPoreById(id):
	_return = HighDrillingPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreByForeignKey(fkey, id):
	_return = HighDrillingPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreHighDrillingPore(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreHighDrillingPore(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreHighDrillingPore(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreHighDrillingPore(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetHighDrillingPoreByFields(fields):
	_return = HighDrillingPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreByField1(field, value):
	_return = HighDrillingPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreByField2(field1, value1, field2, value2):
	_return = HighDrillingPore()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#HighDrillingPoreParam 类型的CRUD操作
def AddHighDrillingPoreParam(high_drilling_pore_param):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddHighDrillingPoreParam(high_drilling_pore_param)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteHighDrillingPoreParam(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteHighDrillingPoreParam(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateHighDrillingPoreParam(high_drilling_pore_param):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateHighDrillingPoreParam(high_drilling_pore_param)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetHighDrillingPoreParamById(id):
	_return = HighDrillingPoreParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreParamByForeignKey(fkey, id):
	_return = HighDrillingPoreParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreParamIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreParamList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreHighDrillingPoreParam(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreHighDrillingPoreParam(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreHighDrillingPoreParam(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreHighDrillingPoreParam(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetHighDrillingPoreParamByFields(fields):
	_return = HighDrillingPoreParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreParamByField1(field, value):
	_return = HighDrillingPoreParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreParamByField2(field1, value1, field2, value2):
	_return = HighDrillingPoreParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingPoreParamListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreParamIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreParamIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingPoreParamIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingPoreParamIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingPoreParamIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#HighDrillingSiteParam 类型的CRUD操作
def AddHighDrillingSiteParam(high_drilling_site_param):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddHighDrillingSiteParam(high_drilling_site_param)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteHighDrillingSiteParam(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteHighDrillingSiteParam(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateHighDrillingSiteParam(high_drilling_site_param):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateHighDrillingSiteParam(high_drilling_site_param)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetHighDrillingSiteParamById(id):
	_return = HighDrillingSiteParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingSiteParamByForeignKey(fkey, id):
	_return = HighDrillingSiteParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingSiteParamIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingSiteParamList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreHighDrillingSiteParam(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreHighDrillingSiteParam(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreHighDrillingSiteParam(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreHighDrillingSiteParam(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetHighDrillingSiteParamByFields(fields):
	_return = HighDrillingSiteParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingSiteParamByField1(field, value):
	_return = HighDrillingSiteParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingSiteParamByField2(field1, value1, field2, value2):
	_return = HighDrillingSiteParam()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingSiteParamListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingSiteParamIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingSiteParamIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingSiteParamIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingSiteParamIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingSiteParamIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#HighDrillingTunnel 类型的CRUD操作
def AddHighDrillingTunnel(high_drilling_tunnel):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddHighDrillingTunnel(high_drilling_tunnel)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteHighDrillingTunnel(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteHighDrillingTunnel(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateHighDrillingTunnel(high_drilling_tunnel):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateHighDrillingTunnel(high_drilling_tunnel)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetHighDrillingTunnelById(id):
	_return = HighDrillingTunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingTunnelByForeignKey(fkey, id):
	_return = HighDrillingTunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingTunnelIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingTunnelList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreHighDrillingTunnel(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreHighDrillingTunnel(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreHighDrillingTunnel(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreHighDrillingTunnel(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetHighDrillingTunnelByFields(fields):
	_return = HighDrillingTunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingTunnelByField1(field, value):
	_return = HighDrillingTunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingTunnelByField2(field1, value1, field2, value2):
	_return = HighDrillingTunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHighDrillingTunnelListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingTunnelIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingTunnelIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHighDrillingTunnelIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHighDrillingTunnelIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHighDrillingTunnelIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#HydrGeo 类型的CRUD操作
def AddHydrGeo(hydr_geo):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddHydrGeo(hydr_geo)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteHydrGeo(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteHydrGeo(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateHydrGeo(hydr_geo):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateHydrGeo(hydr_geo)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetHydrGeoById(id):
	_return = HydrGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHydrGeoByForeignKey(fkey, id):
	_return = HydrGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHydrGeoIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHydrGeoList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreHydrGeo(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreHydrGeo(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreHydrGeo(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreHydrGeo(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetHydrGeoByFields(fields):
	_return = HydrGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHydrGeoByField1(field, value):
	_return = HydrGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHydrGeoByField2(field1, value1, field2, value2):
	_return = HydrGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetHydrGeoListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHydrGeoIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHydrGeoIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetHydrGeoIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetHydrGeoIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetHydrGeoIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#Mine 类型的CRUD操作
def AddMine(mine):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddMine(mine)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteMine(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteMine(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateMine(mine):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateMine(mine)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetMineById(id):
	_return = Mine()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineByForeignKey(fkey, id):
	_return = Mine()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreMine(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreMine(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreMine(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreMine(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetMineByFields(fields):
	_return = Mine()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineByField1(field, value):
	_return = Mine()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineByField2(field1, value1, field2, value2):
	_return = Mine()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#MineBase 类型的CRUD操作
def AddMineBase(mine_base):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddMineBase(mine_base)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteMineBase(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteMineBase(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateMineBase(mine_base):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateMineBase(mine_base)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetMineBaseById(id):
	_return = MineBase()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineBaseByForeignKey(fkey, id):
	_return = MineBase()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineBaseIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineBaseList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreMineBase(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreMineBase(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreMineBase(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreMineBase(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetMineBaseByFields(fields):
	_return = MineBase()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineBaseByField1(field, value):
	_return = MineBase()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineBaseByField2(field1, value1, field2, value2):
	_return = MineBase()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineBaseListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineBaseIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineBaseIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineBaseIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineBaseIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineBaseIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#MineRegion 类型的CRUD操作
def AddMineRegion(mine_region):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddMineRegion(mine_region)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteMineRegion(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteMineRegion(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateMineRegion(mine_region):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateMineRegion(mine_region)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetMineRegionById(id):
	_return = MineRegion()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineRegionByForeignKey(fkey, id):
	_return = MineRegion()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineRegionIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineRegionList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreMineRegion(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreMineRegion(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreMineRegion(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreMineRegion(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetMineRegionByFields(fields):
	_return = MineRegion()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineRegionByField1(field, value):
	_return = MineRegion()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineRegionByField2(field1, value1, field2, value2):
	_return = MineRegion()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetMineRegionListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineRegionIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineRegionIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetMineRegionIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetMineRegionIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetMineRegionIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#PoreFlow 类型的CRUD操作
def AddPoreFlow(pore_flow):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddPoreFlow(pore_flow)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeletePoreFlow(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeletePoreFlow(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdatePoreFlow(pore_flow):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdatePoreFlow(pore_flow)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetPoreFlowById(id):
	_return = PoreFlow()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreFlowByForeignKey(fkey, id):
	_return = PoreFlow()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreFlowIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreFlowList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMorePoreFlow(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMorePoreFlow(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMorePoreFlow(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMorePoreFlow(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetPoreFlowByFields(fields):
	_return = PoreFlow()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreFlowByField1(field, value):
	_return = PoreFlow()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreFlowByField2(field1, value1, field2, value2):
	_return = PoreFlow()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreFlowListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreFlowIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreFlowIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreFlowIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreFlowIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreFlowIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#PoreSize 类型的CRUD操作
def AddPoreSize(pore_size):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddPoreSize(pore_size)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeletePoreSize(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeletePoreSize(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdatePoreSize(pore_size):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdatePoreSize(pore_size)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetPoreSizeById(id):
	_return = PoreSize()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreSizeByForeignKey(fkey, id):
	_return = PoreSize()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreSizeIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreSizeList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMorePoreSize(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMorePoreSize(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMorePoreSize(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMorePoreSize(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetPoreSizeByFields(fields):
	_return = PoreSize()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreSizeByField1(field, value):
	_return = PoreSize()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreSizeByField2(field1, value1, field2, value2):
	_return = PoreSize()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetPoreSizeListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreSizeIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreSizeIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetPoreSizeIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetPoreSizeIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetPoreSizeIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#ResAbundance 类型的CRUD操作
def AddResAbundance(res_abundance):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddResAbundance(res_abundance)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteResAbundance(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteResAbundance(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateResAbundance(res_abundance):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateResAbundance(res_abundance)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetResAbundanceById(id):
	_return = ResAbundance()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetResAbundanceByForeignKey(fkey, id):
	_return = ResAbundance()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetResAbundanceIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetResAbundanceList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreResAbundance(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreResAbundance(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreResAbundance(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreResAbundance(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetResAbundanceByFields(fields):
	_return = ResAbundance()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetResAbundanceByField1(field, value):
	_return = ResAbundance()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetResAbundanceByField2(field1, value1, field2, value2):
	_return = ResAbundance()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetResAbundanceListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetResAbundanceIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetResAbundanceIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetResAbundanceIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetResAbundanceIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetResAbundanceIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#Rock 类型的CRUD操作
def AddRock(rock):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddRock(rock)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteRock(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteRock(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateRock(rock):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateRock(rock)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetRockById(id):
	_return = Rock()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetRockByForeignKey(fkey, id):
	_return = Rock()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetRockIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetRockList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreRock(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreRock(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreRock(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreRock(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetRockByFields(fields):
	_return = Rock()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetRockByField1(field, value):
	_return = Rock()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetRockByField2(field1, value1, field2, value2):
	_return = Rock()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetRockListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetRockIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetRockIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetRockIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetRockIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetRockIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#SysInfo 类型的CRUD操作
def AddSysInfo(sys_info):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddSysInfo(sys_info)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteSysInfo(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteSysInfo(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateSysInfo(sys_info):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateSysInfo(sys_info)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetSysInfoById(id):
	_return = SysInfo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetSysInfoByForeignKey(fkey, id):
	_return = SysInfo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetSysInfoIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetSysInfoList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreSysInfo(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreSysInfo(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreSysInfo(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreSysInfo(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetSysInfoByFields(fields):
	_return = SysInfo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetSysInfoByField1(field, value):
	_return = SysInfo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetSysInfoByField2(field1, value1, field2, value2):
	_return = SysInfo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetSysInfoListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetSysInfoIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetSysInfoIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetSysInfoIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetSysInfoIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetSysInfoIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#TechMode 类型的CRUD操作
def AddTechMode(tech_mode):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddTechMode(tech_mode)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteTechMode(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteTechMode(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateTechMode(tech_mode):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateTechMode(tech_mode)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetTechModeById(id):
	_return = TechMode()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechModeByForeignKey(fkey, id):
	_return = TechMode()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechModeIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechModeList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreTechMode(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreTechMode(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreTechMode(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreTechMode(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetTechModeByFields(fields):
	_return = TechMode()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechModeByField1(field, value):
	_return = TechMode()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechModeByField2(field1, value1, field2, value2):
	_return = TechMode()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechModeListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechModeIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechModeIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechModeIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechModeIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechModeIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#Technology 类型的CRUD操作
def AddTechnology(technology):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddTechnology(technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteTechnology(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteTechnology(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateTechnology(technology):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateTechnology(technology)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetTechnologyById(id):
	_return = Technology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechnologyByForeignKey(fkey, id):
	_return = Technology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechnologyIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechnologyList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreTechnology(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreTechnology(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreTechnology(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreTechnology(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetTechnologyByFields(fields):
	_return = Technology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechnologyByField1(field, value):
	_return = Technology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechnologyByField2(field1, value1, field2, value2):
	_return = Technology()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTechnologyListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechnologyIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechnologyIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTechnologyIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTechnologyIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTechnologyIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#TopoGeo 类型的CRUD操作
def AddTopoGeo(topo_geo):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddTopoGeo(topo_geo)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteTopoGeo(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteTopoGeo(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateTopoGeo(topo_geo):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateTopoGeo(topo_geo)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetTopoGeoById(id):
	_return = TopoGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTopoGeoByForeignKey(fkey, id):
	_return = TopoGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTopoGeoIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTopoGeoList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreTopoGeo(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreTopoGeo(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreTopoGeo(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreTopoGeo(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetTopoGeoByFields(fields):
	_return = TopoGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTopoGeoByField1(field, value):
	_return = TopoGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTopoGeoByField2(field1, value1, field2, value2):
	_return = TopoGeo()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTopoGeoListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTopoGeoIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTopoGeoIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTopoGeoIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTopoGeoIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTopoGeoIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#Tunnel 类型的CRUD操作
def AddTunnel(tunnel):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddTunnel(tunnel)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteTunnel(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteTunnel(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateTunnel(tunnel):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateTunnel(tunnel)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetTunnelById(id):
	_return = Tunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTunnelByForeignKey(fkey, id):
	_return = Tunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTunnelIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTunnelList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreTunnel(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreTunnel(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreTunnel(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreTunnel(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetTunnelByFields(fields):
	_return = Tunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTunnelByField1(field, value):
	_return = Tunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTunnelByField2(field1, value1, field2, value2):
	_return = Tunnel()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetTunnelListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTunnelIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTunnelIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetTunnelIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetTunnelIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetTunnelIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#WorkArea 类型的CRUD操作
def AddWorkArea(work_area):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddWorkArea(work_area)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteWorkArea(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteWorkArea(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateWorkArea(work_area):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateWorkArea(work_area)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetWorkAreaById(id):
	_return = WorkArea()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkAreaByForeignKey(fkey, id):
	_return = WorkArea()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkAreaIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkAreaList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreWorkArea(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreWorkArea(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreWorkArea(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreWorkArea(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetWorkAreaByFields(fields):
	_return = WorkArea()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkAreaByField1(field, value):
	_return = WorkArea()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkAreaByField2(field1, value1, field2, value2):
	_return = WorkArea()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkAreaListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkAreaIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkAreaIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkAreaIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkAreaIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkAreaIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return



#WorkSurf 类型的CRUD操作
def AddWorkSurf(work_surf):
	ret = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().AddWorkSurf(work_surf)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = -1
	return ret
def DeleteWorkSurf(id):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().DeleteWorkSurf(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def UpdateWorkSurf(work_surf):
	ret = False
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		ret = service_client.get().UpdateWorkSurf(work_surf)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		ret = False
	return ret
def GetWorkSurfById(id):
	_return = WorkSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfById(int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkSurfByForeignKey(fkey, id):
	_return = WorkSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkSurfIdByForeignKey(fkey, id):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkSurfList():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfList()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfIds():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIds()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfNames():
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfNames()
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def AddMoreWorkSurf(objs):
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().AddMoreWorkSurf(objs)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def DeleteMoreWorkSurf(obj_ids):
	if len(obj_ids) == 0:return
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		service_client.get().DeleteMoreWorkSurf(obj_ids)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
def GetWorkSurfByFields(fields):
	_return = WorkSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkSurfByField1(field, value):
	_return = WorkSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkSurfByField2(field1, value1, field2, value2):
	_return = WorkSurf()
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return.id = -1
	return _return
def GetWorkSurfListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfIdByFields(fields):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkSurfIdByField1(field, value):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkSurfIdByField2(field1, value1, field2, value2):
	_return = -1
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = -1
	return _return
def GetWorkSurfIdListByFields(fields):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdListByFields(fields)
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfIdListByField1(field, value):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdListByField1(field, str(value))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfIdListByField2(field1, value1, field2, value2):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdListByField2(field1, str(value1), field2, str(value2))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return
def GetWorkSurfIdListByForeignKey(fkey, id):
	_return = []
	try:
		service_client = RpcClient(CbmService, host=HOST, port=PORT2)
		service_client.start()
		_return = service_client.get().GetWorkSurfIdListByForeignKey(fkey, int(id))
		service_client.close()
	except Exception, e:
		print 'client exception:',e
		_return = []
	return _return


