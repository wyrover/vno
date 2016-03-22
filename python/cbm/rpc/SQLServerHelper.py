#-*- coding:utf-8 -*-

from cbm.ttypes import *
import SQL
import CbmUtil


class SQLServiceHandler(object):
	def __init__(self, session):
		self.session = session

	#Account 类型的CRUD操作
	def AddAccount(self, account):
		sql_obj = SQL.Account()
		CbmUtil.CopyAttribsOfCbmType("Account", account, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteAccount(self, id):
		ret=True
		try:
			self.session.query(SQL.Account).filter(SQL.Account.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateAccount(self, account):
		ret=True
		try:
			sql_obj = SQL.Account()
			CbmUtil.CopyAttribsOfCbmType("Account", account, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("Account", sql_obj)
			del attribs['id']
			self.session.query(SQL.Account).filter(SQL.Account.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetAccountById(self, id):
		query=self.session.query(SQL.Account).filter(SQL.Account.id==id).first()
		obj = Account()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("Account", query, obj, True)
		return obj
	def GetAccountByForeignKey(self, fkey, id):
		return self.GetAccountByFields({fkey:id})
	def GetAccountIdByForeignKey(self, fkey, id):
		return self.GetAccountIdByFields({fkey:id})
	def GetAccountList(self):
		query = self.session.query(SQL.Account).order_by(SQL.Account.id).all()
		n = len(query)
		obj_list = [Account() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Account", query[i], obj_list[i], True)
		return obj_list
	def GetAccountIds(self):
		query=self.session.query(SQL.Account).order_by(SQL.Account.id).all()
		return [obj.id for obj in query]
	def GetAccountNames(self):
		query=self.session.query(SQL.Account).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreAccount(self, objs):
		n = len(objs)
		sql_objs = [SQL.Account() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Account", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreAccount(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.Account).filter(SQL.Account.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetAccountByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Account", fields)
		query = self.session.query(SQL.Account).filter_by(**sql_fields).order_by(SQL.Account.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [Account() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("Account", query[i], obj_list[i], True)
			return obj_list
	def __GetAccountIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Account", fields)
		query = self.session.query(SQL.Account).filter_by(**sql_fields).order_by(SQL.Account.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetAccountByFields(self, fields):
		objs = self.__GetAccountByFields(fields)
		if len(objs) == 0:
			obj = Account()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetAccountByField1(self, field, value):
		return self.GetAccountByFields({field:value})
	def GetAccountByField2(self, field1, value1, field2, value2):
		return self.GetAccountByFields({field1:value1, field2:value2})
	def GetAccountListByFields(self, fields):
		return self.__GetAccountByFields(fields)
	def GetAccountListByField1(self, field, value):
		return self.GetAccountListByFields({field:value})
	def GetAccountListByField2(self, field1, value1, field2, value2):
		return self.GetAccountListByFields({field1:value1, field2:value2})
	def GetAccountIdByFields(self, fields):
		obj_ids = self.__GetAccountIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetAccountIdByField1(self, field, value):
		return self.GetAccountIdByFields({field:value})
	def GetAccountIdByField2(self, field1, value1, field2, value2):
		return self.GetAccountIdByFields({field1:value1, field2:value2})
	def GetAccountIdListByFields(self, fields):
		return self.__GetAccountIdsByFields(fields)
	def GetAccountIdListByField1(self, field, value):
		return self.GetAccountIdListByFields({field:value})
	def GetAccountIdListByField2(self, field1, value1, field2, value2):
		return self.GetAccountIdListByFields({field1:value1, field2:value2})
	def GetAccountListByForeignKey(self, fkey, id):
		return self.GetAccountListByFields({fkey:id})
	def GetAccountIdListByForeignKey(self, fkey, id):
		return self.GetAccountIdListByFields({fkey:id})

	#AdjLayer 类型的CRUD操作
	def AddAdjLayer(self, adj_layer):
		sql_obj = SQL.AdjLayer()
		CbmUtil.CopyAttribsOfCbmType("AdjLayer", adj_layer, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteAdjLayer(self, id):
		ret=True
		try:
			self.session.query(SQL.AdjLayer).filter(SQL.AdjLayer.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateAdjLayer(self, adj_layer):
		ret=True
		try:
			sql_obj = SQL.AdjLayer()
			CbmUtil.CopyAttribsOfCbmType("AdjLayer", adj_layer, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("AdjLayer", sql_obj)
			del attribs['id']
			self.session.query(SQL.AdjLayer).filter(SQL.AdjLayer.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetAdjLayerById(self, id):
		query=self.session.query(SQL.AdjLayer).filter(SQL.AdjLayer.id==id).first()
		obj = AdjLayer()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("AdjLayer", query, obj, True)
		return obj
	def GetAdjLayerByForeignKey(self, fkey, id):
		return self.GetAdjLayerByFields({fkey:id})
	def GetAdjLayerIdByForeignKey(self, fkey, id):
		return self.GetAdjLayerIdByFields({fkey:id})
	def GetAdjLayerList(self):
		query = self.session.query(SQL.AdjLayer).order_by(SQL.AdjLayer.id).all()
		n = len(query)
		obj_list = [AdjLayer() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("AdjLayer", query[i], obj_list[i], True)
		return obj_list
	def GetAdjLayerIds(self):
		query=self.session.query(SQL.AdjLayer).order_by(SQL.AdjLayer.id).all()
		return [obj.id for obj in query]
	def GetAdjLayerNames(self):
		query=self.session.query(SQL.AdjLayer).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreAdjLayer(self, objs):
		n = len(objs)
		sql_objs = [SQL.AdjLayer() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("AdjLayer", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreAdjLayer(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.AdjLayer).filter(SQL.AdjLayer.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetAdjLayerByFields(self, fields):
		sql_fields = CbmUtil.map_fields("AdjLayer", fields)
		query = self.session.query(SQL.AdjLayer).filter_by(**sql_fields).order_by(SQL.AdjLayer.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [AdjLayer() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("AdjLayer", query[i], obj_list[i], True)
			return obj_list
	def __GetAdjLayerIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("AdjLayer", fields)
		query = self.session.query(SQL.AdjLayer).filter_by(**sql_fields).order_by(SQL.AdjLayer.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetAdjLayerByFields(self, fields):
		objs = self.__GetAdjLayerByFields(fields)
		if len(objs) == 0:
			obj = AdjLayer()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetAdjLayerByField1(self, field, value):
		return self.GetAdjLayerByFields({field:value})
	def GetAdjLayerByField2(self, field1, value1, field2, value2):
		return self.GetAdjLayerByFields({field1:value1, field2:value2})
	def GetAdjLayerListByFields(self, fields):
		return self.__GetAdjLayerByFields(fields)
	def GetAdjLayerListByField1(self, field, value):
		return self.GetAdjLayerListByFields({field:value})
	def GetAdjLayerListByField2(self, field1, value1, field2, value2):
		return self.GetAdjLayerListByFields({field1:value1, field2:value2})
	def GetAdjLayerIdByFields(self, fields):
		obj_ids = self.__GetAdjLayerIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetAdjLayerIdByField1(self, field, value):
		return self.GetAdjLayerIdByFields({field:value})
	def GetAdjLayerIdByField2(self, field1, value1, field2, value2):
		return self.GetAdjLayerIdByFields({field1:value1, field2:value2})
	def GetAdjLayerIdListByFields(self, fields):
		return self.__GetAdjLayerIdsByFields(fields)
	def GetAdjLayerIdListByField1(self, field, value):
		return self.GetAdjLayerIdListByFields({field:value})
	def GetAdjLayerIdListByField2(self, field1, value1, field2, value2):
		return self.GetAdjLayerIdListByFields({field1:value1, field2:value2})
	def GetAdjLayerListByForeignKey(self, fkey, id):
		return self.GetAdjLayerListByFields({fkey:id})
	def GetAdjLayerIdListByForeignKey(self, fkey, id):
		return self.GetAdjLayerIdListByFields({fkey:id})

	#Coal 类型的CRUD操作
	def AddCoal(self, coal):
		sql_obj = SQL.Coal()
		CbmUtil.CopyAttribsOfCbmType("Coal", coal, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteCoal(self, id):
		ret=True
		try:
			self.session.query(SQL.Coal).filter(SQL.Coal.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateCoal(self, coal):
		ret=True
		try:
			sql_obj = SQL.Coal()
			CbmUtil.CopyAttribsOfCbmType("Coal", coal, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("Coal", sql_obj)
			del attribs['id']
			self.session.query(SQL.Coal).filter(SQL.Coal.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetCoalById(self, id):
		query=self.session.query(SQL.Coal).filter(SQL.Coal.id==id).first()
		obj = Coal()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("Coal", query, obj, True)
		return obj
	def GetCoalByForeignKey(self, fkey, id):
		return self.GetCoalByFields({fkey:id})
	def GetCoalIdByForeignKey(self, fkey, id):
		return self.GetCoalIdByFields({fkey:id})
	def GetCoalList(self):
		query = self.session.query(SQL.Coal).order_by(SQL.Coal.id).all()
		n = len(query)
		obj_list = [Coal() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Coal", query[i], obj_list[i], True)
		return obj_list
	def GetCoalIds(self):
		query=self.session.query(SQL.Coal).order_by(SQL.Coal.id).all()
		return [obj.id for obj in query]
	def GetCoalNames(self):
		query=self.session.query(SQL.Coal).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreCoal(self, objs):
		n = len(objs)
		sql_objs = [SQL.Coal() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Coal", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreCoal(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.Coal).filter(SQL.Coal.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetCoalByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Coal", fields)
		query = self.session.query(SQL.Coal).filter_by(**sql_fields).order_by(SQL.Coal.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [Coal() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("Coal", query[i], obj_list[i], True)
			return obj_list
	def __GetCoalIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Coal", fields)
		query = self.session.query(SQL.Coal).filter_by(**sql_fields).order_by(SQL.Coal.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetCoalByFields(self, fields):
		objs = self.__GetCoalByFields(fields)
		if len(objs) == 0:
			obj = Coal()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetCoalByField1(self, field, value):
		return self.GetCoalByFields({field:value})
	def GetCoalByField2(self, field1, value1, field2, value2):
		return self.GetCoalByFields({field1:value1, field2:value2})
	def GetCoalListByFields(self, fields):
		return self.__GetCoalByFields(fields)
	def GetCoalListByField1(self, field, value):
		return self.GetCoalListByFields({field:value})
	def GetCoalListByField2(self, field1, value1, field2, value2):
		return self.GetCoalListByFields({field1:value1, field2:value2})
	def GetCoalIdByFields(self, fields):
		obj_ids = self.__GetCoalIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetCoalIdByField1(self, field, value):
		return self.GetCoalIdByFields({field:value})
	def GetCoalIdByField2(self, field1, value1, field2, value2):
		return self.GetCoalIdByFields({field1:value1, field2:value2})
	def GetCoalIdListByFields(self, fields):
		return self.__GetCoalIdsByFields(fields)
	def GetCoalIdListByField1(self, field, value):
		return self.GetCoalIdListByFields({field:value})
	def GetCoalIdListByField2(self, field1, value1, field2, value2):
		return self.GetCoalIdListByFields({field1:value1, field2:value2})
	def GetCoalListByForeignKey(self, fkey, id):
		return self.GetCoalListByFields({fkey:id})
	def GetCoalIdListByForeignKey(self, fkey, id):
		return self.GetCoalIdListByFields({fkey:id})

	#Complexity 类型的CRUD操作
	def AddComplexity(self, complexity):
		sql_obj = SQL.Complexity()
		CbmUtil.CopyAttribsOfCbmType("Complexity", complexity, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteComplexity(self, id):
		ret=True
		try:
			self.session.query(SQL.Complexity).filter(SQL.Complexity.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateComplexity(self, complexity):
		ret=True
		try:
			sql_obj = SQL.Complexity()
			CbmUtil.CopyAttribsOfCbmType("Complexity", complexity, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("Complexity", sql_obj)
			del attribs['id']
			self.session.query(SQL.Complexity).filter(SQL.Complexity.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetComplexityById(self, id):
		query=self.session.query(SQL.Complexity).filter(SQL.Complexity.id==id).first()
		obj = Complexity()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("Complexity", query, obj, True)
		return obj
	def GetComplexityByForeignKey(self, fkey, id):
		return self.GetComplexityByFields({fkey:id})
	def GetComplexityIdByForeignKey(self, fkey, id):
		return self.GetComplexityIdByFields({fkey:id})
	def GetComplexityList(self):
		query = self.session.query(SQL.Complexity).order_by(SQL.Complexity.id).all()
		n = len(query)
		obj_list = [Complexity() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Complexity", query[i], obj_list[i], True)
		return obj_list
	def GetComplexityIds(self):
		query=self.session.query(SQL.Complexity).order_by(SQL.Complexity.id).all()
		return [obj.id for obj in query]
	def GetComplexityNames(self):
		query=self.session.query(SQL.Complexity).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreComplexity(self, objs):
		n = len(objs)
		sql_objs = [SQL.Complexity() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Complexity", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreComplexity(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.Complexity).filter(SQL.Complexity.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetComplexityByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Complexity", fields)
		query = self.session.query(SQL.Complexity).filter_by(**sql_fields).order_by(SQL.Complexity.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [Complexity() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("Complexity", query[i], obj_list[i], True)
			return obj_list
	def __GetComplexityIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Complexity", fields)
		query = self.session.query(SQL.Complexity).filter_by(**sql_fields).order_by(SQL.Complexity.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetComplexityByFields(self, fields):
		objs = self.__GetComplexityByFields(fields)
		if len(objs) == 0:
			obj = Complexity()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetComplexityByField1(self, field, value):
		return self.GetComplexityByFields({field:value})
	def GetComplexityByField2(self, field1, value1, field2, value2):
		return self.GetComplexityByFields({field1:value1, field2:value2})
	def GetComplexityListByFields(self, fields):
		return self.__GetComplexityByFields(fields)
	def GetComplexityListByField1(self, field, value):
		return self.GetComplexityListByFields({field:value})
	def GetComplexityListByField2(self, field1, value1, field2, value2):
		return self.GetComplexityListByFields({field1:value1, field2:value2})
	def GetComplexityIdByFields(self, fields):
		obj_ids = self.__GetComplexityIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetComplexityIdByField1(self, field, value):
		return self.GetComplexityIdByFields({field:value})
	def GetComplexityIdByField2(self, field1, value1, field2, value2):
		return self.GetComplexityIdByFields({field1:value1, field2:value2})
	def GetComplexityIdListByFields(self, fields):
		return self.__GetComplexityIdsByFields(fields)
	def GetComplexityIdListByField1(self, field, value):
		return self.GetComplexityIdListByFields({field:value})
	def GetComplexityIdListByField2(self, field1, value1, field2, value2):
		return self.GetComplexityIdListByFields({field1:value1, field2:value2})
	def GetComplexityListByForeignKey(self, fkey, id):
		return self.GetComplexityListByFields({fkey:id})
	def GetComplexityIdListByForeignKey(self, fkey, id):
		return self.GetComplexityIdListByFields({fkey:id})

	#DesignDrillingSurfTechnology 类型的CRUD操作
	def AddDesignDrillingSurfTechnology(self, design_drilling_surf_technology):
		sql_obj = SQL.DesignDrillingSurfTechnology()
		CbmUtil.CopyAttribsOfCbmType("DesignDrillingSurfTechnology", design_drilling_surf_technology, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignDrillingSurfTechnology(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignDrillingSurfTechnology).filter(SQL.DesignDrillingSurfTechnology.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignDrillingSurfTechnology(self, design_drilling_surf_technology):
		ret=True
		try:
			sql_obj = SQL.DesignDrillingSurfTechnology()
			CbmUtil.CopyAttribsOfCbmType("DesignDrillingSurfTechnology", design_drilling_surf_technology, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignDrillingSurfTechnology", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignDrillingSurfTechnology).filter(SQL.DesignDrillingSurfTechnology.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignDrillingSurfTechnologyById(self, id):
		query=self.session.query(SQL.DesignDrillingSurfTechnology).filter(SQL.DesignDrillingSurfTechnology.id==id).first()
		obj = DesignDrillingSurfTechnology()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignDrillingSurfTechnology", query, obj, True)
		return obj
	def GetDesignDrillingSurfTechnologyByForeignKey(self, fkey, id):
		return self.GetDesignDrillingSurfTechnologyByFields({fkey:id})
	def GetDesignDrillingSurfTechnologyIdByForeignKey(self, fkey, id):
		return self.GetDesignDrillingSurfTechnologyIdByFields({fkey:id})
	def GetDesignDrillingSurfTechnologyList(self):
		query = self.session.query(SQL.DesignDrillingSurfTechnology).order_by(SQL.DesignDrillingSurfTechnology.id).all()
		n = len(query)
		obj_list = [DesignDrillingSurfTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignDrillingSurfTechnology", query[i], obj_list[i], True)
		return obj_list
	def GetDesignDrillingSurfTechnologyIds(self):
		query=self.session.query(SQL.DesignDrillingSurfTechnology).order_by(SQL.DesignDrillingSurfTechnology.id).all()
		return [obj.id for obj in query]
	def GetDesignDrillingSurfTechnologyNames(self):
		query=self.session.query(SQL.DesignDrillingSurfTechnology).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignDrillingSurfTechnology(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignDrillingSurfTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignDrillingSurfTechnology", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignDrillingSurfTechnology(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignDrillingSurfTechnology).filter(SQL.DesignDrillingSurfTechnology.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignDrillingSurfTechnologyByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignDrillingSurfTechnology", fields)
		query = self.session.query(SQL.DesignDrillingSurfTechnology).filter_by(**sql_fields).order_by(SQL.DesignDrillingSurfTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignDrillingSurfTechnology() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignDrillingSurfTechnology", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignDrillingSurfTechnologyIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignDrillingSurfTechnology", fields)
		query = self.session.query(SQL.DesignDrillingSurfTechnology).filter_by(**sql_fields).order_by(SQL.DesignDrillingSurfTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignDrillingSurfTechnologyByFields(self, fields):
		objs = self.__GetDesignDrillingSurfTechnologyByFields(fields)
		if len(objs) == 0:
			obj = DesignDrillingSurfTechnology()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignDrillingSurfTechnologyByField1(self, field, value):
		return self.GetDesignDrillingSurfTechnologyByFields({field:value})
	def GetDesignDrillingSurfTechnologyByField2(self, field1, value1, field2, value2):
		return self.GetDesignDrillingSurfTechnologyByFields({field1:value1, field2:value2})
	def GetDesignDrillingSurfTechnologyListByFields(self, fields):
		return self.__GetDesignDrillingSurfTechnologyByFields(fields)
	def GetDesignDrillingSurfTechnologyListByField1(self, field, value):
		return self.GetDesignDrillingSurfTechnologyListByFields({field:value})
	def GetDesignDrillingSurfTechnologyListByField2(self, field1, value1, field2, value2):
		return self.GetDesignDrillingSurfTechnologyListByFields({field1:value1, field2:value2})
	def GetDesignDrillingSurfTechnologyIdByFields(self, fields):
		obj_ids = self.__GetDesignDrillingSurfTechnologyIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignDrillingSurfTechnologyIdByField1(self, field, value):
		return self.GetDesignDrillingSurfTechnologyIdByFields({field:value})
	def GetDesignDrillingSurfTechnologyIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignDrillingSurfTechnologyIdByFields({field1:value1, field2:value2})
	def GetDesignDrillingSurfTechnologyIdListByFields(self, fields):
		return self.__GetDesignDrillingSurfTechnologyIdsByFields(fields)
	def GetDesignDrillingSurfTechnologyIdListByField1(self, field, value):
		return self.GetDesignDrillingSurfTechnologyIdListByFields({field:value})
	def GetDesignDrillingSurfTechnologyIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignDrillingSurfTechnologyIdListByFields({field1:value1, field2:value2})
	def GetDesignDrillingSurfTechnologyListByForeignKey(self, fkey, id):
		return self.GetDesignDrillingSurfTechnologyListByFields({fkey:id})
	def GetDesignDrillingSurfTechnologyIdListByForeignKey(self, fkey, id):
		return self.GetDesignDrillingSurfTechnologyIdListByFields({fkey:id})

	#DesignEvalUnit 类型的CRUD操作
	def AddDesignEvalUnit(self, design_eval_unit):
		sql_obj = SQL.DesignEvalUnit()
		CbmUtil.CopyAttribsOfCbmType("DesignEvalUnit", design_eval_unit, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignEvalUnit(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignEvalUnit).filter(SQL.DesignEvalUnit.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignEvalUnit(self, design_eval_unit):
		ret=True
		try:
			sql_obj = SQL.DesignEvalUnit()
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnit", design_eval_unit, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignEvalUnit", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignEvalUnit).filter(SQL.DesignEvalUnit.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignEvalUnitById(self, id):
		query=self.session.query(SQL.DesignEvalUnit).filter(SQL.DesignEvalUnit.id==id).first()
		obj = DesignEvalUnit()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnit", query, obj, True)
		return obj
	def GetDesignEvalUnitByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitByFields({fkey:id})
	def GetDesignEvalUnitIdByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitIdByFields({fkey:id})
	def GetDesignEvalUnitList(self):
		query = self.session.query(SQL.DesignEvalUnit).order_by(SQL.DesignEvalUnit.id).all()
		n = len(query)
		obj_list = [DesignEvalUnit() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnit", query[i], obj_list[i], True)
		return obj_list
	def GetDesignEvalUnitIds(self):
		query=self.session.query(SQL.DesignEvalUnit).order_by(SQL.DesignEvalUnit.id).all()
		return [obj.id for obj in query]
	def GetDesignEvalUnitNames(self):
		query=self.session.query(SQL.DesignEvalUnit).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignEvalUnit(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignEvalUnit() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnit", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignEvalUnit(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignEvalUnit).filter(SQL.DesignEvalUnit.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignEvalUnitByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignEvalUnit", fields)
		query = self.session.query(SQL.DesignEvalUnit).filter_by(**sql_fields).order_by(SQL.DesignEvalUnit.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignEvalUnit() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignEvalUnit", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignEvalUnitIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignEvalUnit", fields)
		query = self.session.query(SQL.DesignEvalUnit).filter_by(**sql_fields).order_by(SQL.DesignEvalUnit.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignEvalUnitByFields(self, fields):
		objs = self.__GetDesignEvalUnitByFields(fields)
		if len(objs) == 0:
			obj = DesignEvalUnit()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignEvalUnitByField1(self, field, value):
		return self.GetDesignEvalUnitByFields({field:value})
	def GetDesignEvalUnitByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitListByFields(self, fields):
		return self.__GetDesignEvalUnitByFields(fields)
	def GetDesignEvalUnitListByField1(self, field, value):
		return self.GetDesignEvalUnitListByFields({field:value})
	def GetDesignEvalUnitListByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitListByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitIdByFields(self, fields):
		obj_ids = self.__GetDesignEvalUnitIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignEvalUnitIdByField1(self, field, value):
		return self.GetDesignEvalUnitIdByFields({field:value})
	def GetDesignEvalUnitIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitIdByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitIdListByFields(self, fields):
		return self.__GetDesignEvalUnitIdsByFields(fields)
	def GetDesignEvalUnitIdListByField1(self, field, value):
		return self.GetDesignEvalUnitIdListByFields({field:value})
	def GetDesignEvalUnitIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitIdListByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitListByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitListByFields({fkey:id})
	def GetDesignEvalUnitIdListByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitIdListByFields({fkey:id})

	#DesignEvalUnitPartition 类型的CRUD操作
	def AddDesignEvalUnitPartition(self, design_eval_unit_partition):
		sql_obj = SQL.DesignEvalUnitPartition()
		CbmUtil.CopyAttribsOfCbmType("DesignEvalUnitPartition", design_eval_unit_partition, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignEvalUnitPartition(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignEvalUnitPartition).filter(SQL.DesignEvalUnitPartition.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignEvalUnitPartition(self, design_eval_unit_partition):
		ret=True
		try:
			sql_obj = SQL.DesignEvalUnitPartition()
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnitPartition", design_eval_unit_partition, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignEvalUnitPartition", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignEvalUnitPartition).filter(SQL.DesignEvalUnitPartition.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignEvalUnitPartitionById(self, id):
		query=self.session.query(SQL.DesignEvalUnitPartition).filter(SQL.DesignEvalUnitPartition.id==id).first()
		obj = DesignEvalUnitPartition()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnitPartition", query, obj, True)
		return obj
	def GetDesignEvalUnitPartitionByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitPartitionByFields({fkey:id})
	def GetDesignEvalUnitPartitionIdByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitPartitionIdByFields({fkey:id})
	def GetDesignEvalUnitPartitionList(self):
		query = self.session.query(SQL.DesignEvalUnitPartition).order_by(SQL.DesignEvalUnitPartition.id).all()
		n = len(query)
		obj_list = [DesignEvalUnitPartition() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnitPartition", query[i], obj_list[i], True)
		return obj_list
	def GetDesignEvalUnitPartitionIds(self):
		query=self.session.query(SQL.DesignEvalUnitPartition).order_by(SQL.DesignEvalUnitPartition.id).all()
		return [obj.id for obj in query]
	def GetDesignEvalUnitPartitionNames(self):
		query=self.session.query(SQL.DesignEvalUnitPartition).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignEvalUnitPartition(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignEvalUnitPartition() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignEvalUnitPartition", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignEvalUnitPartition(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignEvalUnitPartition).filter(SQL.DesignEvalUnitPartition.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignEvalUnitPartitionByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignEvalUnitPartition", fields)
		query = self.session.query(SQL.DesignEvalUnitPartition).filter_by(**sql_fields).order_by(SQL.DesignEvalUnitPartition.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignEvalUnitPartition() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignEvalUnitPartition", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignEvalUnitPartitionIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignEvalUnitPartition", fields)
		query = self.session.query(SQL.DesignEvalUnitPartition).filter_by(**sql_fields).order_by(SQL.DesignEvalUnitPartition.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignEvalUnitPartitionByFields(self, fields):
		objs = self.__GetDesignEvalUnitPartitionByFields(fields)
		if len(objs) == 0:
			obj = DesignEvalUnitPartition()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignEvalUnitPartitionByField1(self, field, value):
		return self.GetDesignEvalUnitPartitionByFields({field:value})
	def GetDesignEvalUnitPartitionByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitPartitionByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitPartitionListByFields(self, fields):
		return self.__GetDesignEvalUnitPartitionByFields(fields)
	def GetDesignEvalUnitPartitionListByField1(self, field, value):
		return self.GetDesignEvalUnitPartitionListByFields({field:value})
	def GetDesignEvalUnitPartitionListByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitPartitionListByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitPartitionIdByFields(self, fields):
		obj_ids = self.__GetDesignEvalUnitPartitionIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignEvalUnitPartitionIdByField1(self, field, value):
		return self.GetDesignEvalUnitPartitionIdByFields({field:value})
	def GetDesignEvalUnitPartitionIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitPartitionIdByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitPartitionIdListByFields(self, fields):
		return self.__GetDesignEvalUnitPartitionIdsByFields(fields)
	def GetDesignEvalUnitPartitionIdListByField1(self, field, value):
		return self.GetDesignEvalUnitPartitionIdListByFields({field:value})
	def GetDesignEvalUnitPartitionIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignEvalUnitPartitionIdListByFields({field1:value1, field2:value2})
	def GetDesignEvalUnitPartitionListByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitPartitionListByFields({fkey:id})
	def GetDesignEvalUnitPartitionIdListByForeignKey(self, fkey, id):
		return self.GetDesignEvalUnitPartitionIdListByFields({fkey:id})

	#DesignGoafPore 类型的CRUD操作
	def AddDesignGoafPore(self, design_goaf_pore):
		sql_obj = SQL.DesignGoafPore()
		CbmUtil.CopyAttribsOfCbmType("DesignGoafPore", design_goaf_pore, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignGoafPore(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignGoafPore).filter(SQL.DesignGoafPore.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignGoafPore(self, design_goaf_pore):
		ret=True
		try:
			sql_obj = SQL.DesignGoafPore()
			CbmUtil.CopyAttribsOfCbmType("DesignGoafPore", design_goaf_pore, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignGoafPore", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignGoafPore).filter(SQL.DesignGoafPore.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignGoafPoreById(self, id):
		query=self.session.query(SQL.DesignGoafPore).filter(SQL.DesignGoafPore.id==id).first()
		obj = DesignGoafPore()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignGoafPore", query, obj, True)
		return obj
	def GetDesignGoafPoreByForeignKey(self, fkey, id):
		return self.GetDesignGoafPoreByFields({fkey:id})
	def GetDesignGoafPoreIdByForeignKey(self, fkey, id):
		return self.GetDesignGoafPoreIdByFields({fkey:id})
	def GetDesignGoafPoreList(self):
		query = self.session.query(SQL.DesignGoafPore).order_by(SQL.DesignGoafPore.id).all()
		n = len(query)
		obj_list = [DesignGoafPore() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignGoafPore", query[i], obj_list[i], True)
		return obj_list
	def GetDesignGoafPoreIds(self):
		query=self.session.query(SQL.DesignGoafPore).order_by(SQL.DesignGoafPore.id).all()
		return [obj.id for obj in query]
	def GetDesignGoafPoreNames(self):
		query=self.session.query(SQL.DesignGoafPore).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignGoafPore(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignGoafPore() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignGoafPore", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignGoafPore(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignGoafPore).filter(SQL.DesignGoafPore.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignGoafPoreByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignGoafPore", fields)
		query = self.session.query(SQL.DesignGoafPore).filter_by(**sql_fields).order_by(SQL.DesignGoafPore.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignGoafPore() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignGoafPore", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignGoafPoreIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignGoafPore", fields)
		query = self.session.query(SQL.DesignGoafPore).filter_by(**sql_fields).order_by(SQL.DesignGoafPore.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignGoafPoreByFields(self, fields):
		objs = self.__GetDesignGoafPoreByFields(fields)
		if len(objs) == 0:
			obj = DesignGoafPore()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignGoafPoreByField1(self, field, value):
		return self.GetDesignGoafPoreByFields({field:value})
	def GetDesignGoafPoreByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafPoreByFields({field1:value1, field2:value2})
	def GetDesignGoafPoreListByFields(self, fields):
		return self.__GetDesignGoafPoreByFields(fields)
	def GetDesignGoafPoreListByField1(self, field, value):
		return self.GetDesignGoafPoreListByFields({field:value})
	def GetDesignGoafPoreListByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafPoreListByFields({field1:value1, field2:value2})
	def GetDesignGoafPoreIdByFields(self, fields):
		obj_ids = self.__GetDesignGoafPoreIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignGoafPoreIdByField1(self, field, value):
		return self.GetDesignGoafPoreIdByFields({field:value})
	def GetDesignGoafPoreIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafPoreIdByFields({field1:value1, field2:value2})
	def GetDesignGoafPoreIdListByFields(self, fields):
		return self.__GetDesignGoafPoreIdsByFields(fields)
	def GetDesignGoafPoreIdListByField1(self, field, value):
		return self.GetDesignGoafPoreIdListByFields({field:value})
	def GetDesignGoafPoreIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafPoreIdListByFields({field1:value1, field2:value2})
	def GetDesignGoafPoreListByForeignKey(self, fkey, id):
		return self.GetDesignGoafPoreListByFields({fkey:id})
	def GetDesignGoafPoreIdListByForeignKey(self, fkey, id):
		return self.GetDesignGoafPoreIdListByFields({fkey:id})

	#DesignGoafTechnology 类型的CRUD操作
	def AddDesignGoafTechnology(self, design_goaf_technology):
		sql_obj = SQL.DesignGoafTechnology()
		CbmUtil.CopyAttribsOfCbmType("DesignGoafTechnology", design_goaf_technology, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignGoafTechnology(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignGoafTechnology).filter(SQL.DesignGoafTechnology.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignGoafTechnology(self, design_goaf_technology):
		ret=True
		try:
			sql_obj = SQL.DesignGoafTechnology()
			CbmUtil.CopyAttribsOfCbmType("DesignGoafTechnology", design_goaf_technology, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignGoafTechnology", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignGoafTechnology).filter(SQL.DesignGoafTechnology.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignGoafTechnologyById(self, id):
		query=self.session.query(SQL.DesignGoafTechnology).filter(SQL.DesignGoafTechnology.id==id).first()
		obj = DesignGoafTechnology()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignGoafTechnology", query, obj, True)
		return obj
	def GetDesignGoafTechnologyByForeignKey(self, fkey, id):
		return self.GetDesignGoafTechnologyByFields({fkey:id})
	def GetDesignGoafTechnologyIdByForeignKey(self, fkey, id):
		return self.GetDesignGoafTechnologyIdByFields({fkey:id})
	def GetDesignGoafTechnologyList(self):
		query = self.session.query(SQL.DesignGoafTechnology).order_by(SQL.DesignGoafTechnology.id).all()
		n = len(query)
		obj_list = [DesignGoafTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignGoafTechnology", query[i], obj_list[i], True)
		return obj_list
	def GetDesignGoafTechnologyIds(self):
		query=self.session.query(SQL.DesignGoafTechnology).order_by(SQL.DesignGoafTechnology.id).all()
		return [obj.id for obj in query]
	def GetDesignGoafTechnologyNames(self):
		query=self.session.query(SQL.DesignGoafTechnology).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignGoafTechnology(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignGoafTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignGoafTechnology", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignGoafTechnology(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignGoafTechnology).filter(SQL.DesignGoafTechnology.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignGoafTechnologyByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignGoafTechnology", fields)
		query = self.session.query(SQL.DesignGoafTechnology).filter_by(**sql_fields).order_by(SQL.DesignGoafTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignGoafTechnology() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignGoafTechnology", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignGoafTechnologyIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignGoafTechnology", fields)
		query = self.session.query(SQL.DesignGoafTechnology).filter_by(**sql_fields).order_by(SQL.DesignGoafTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignGoafTechnologyByFields(self, fields):
		objs = self.__GetDesignGoafTechnologyByFields(fields)
		if len(objs) == 0:
			obj = DesignGoafTechnology()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignGoafTechnologyByField1(self, field, value):
		return self.GetDesignGoafTechnologyByFields({field:value})
	def GetDesignGoafTechnologyByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafTechnologyByFields({field1:value1, field2:value2})
	def GetDesignGoafTechnologyListByFields(self, fields):
		return self.__GetDesignGoafTechnologyByFields(fields)
	def GetDesignGoafTechnologyListByField1(self, field, value):
		return self.GetDesignGoafTechnologyListByFields({field:value})
	def GetDesignGoafTechnologyListByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafTechnologyListByFields({field1:value1, field2:value2})
	def GetDesignGoafTechnologyIdByFields(self, fields):
		obj_ids = self.__GetDesignGoafTechnologyIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignGoafTechnologyIdByField1(self, field, value):
		return self.GetDesignGoafTechnologyIdByFields({field:value})
	def GetDesignGoafTechnologyIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafTechnologyIdByFields({field1:value1, field2:value2})
	def GetDesignGoafTechnologyIdListByFields(self, fields):
		return self.__GetDesignGoafTechnologyIdsByFields(fields)
	def GetDesignGoafTechnologyIdListByField1(self, field, value):
		return self.GetDesignGoafTechnologyIdListByFields({field:value})
	def GetDesignGoafTechnologyIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignGoafTechnologyIdListByFields({field1:value1, field2:value2})
	def GetDesignGoafTechnologyListByForeignKey(self, fkey, id):
		return self.GetDesignGoafTechnologyListByFields({fkey:id})
	def GetDesignGoafTechnologyIdListByForeignKey(self, fkey, id):
		return self.GetDesignGoafTechnologyIdListByFields({fkey:id})

	#DesignPore 类型的CRUD操作
	def AddDesignPore(self, design_pore):
		sql_obj = SQL.DesignPore()
		CbmUtil.CopyAttribsOfCbmType("DesignPore", design_pore, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignPore(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignPore).filter(SQL.DesignPore.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignPore(self, design_pore):
		ret=True
		try:
			sql_obj = SQL.DesignPore()
			CbmUtil.CopyAttribsOfCbmType("DesignPore", design_pore, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignPore", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignPore).filter(SQL.DesignPore.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignPoreById(self, id):
		query=self.session.query(SQL.DesignPore).filter(SQL.DesignPore.id==id).first()
		obj = DesignPore()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignPore", query, obj, True)
		return obj
	def GetDesignPoreByForeignKey(self, fkey, id):
		return self.GetDesignPoreByFields({fkey:id})
	def GetDesignPoreIdByForeignKey(self, fkey, id):
		return self.GetDesignPoreIdByFields({fkey:id})
	def GetDesignPoreList(self):
		query = self.session.query(SQL.DesignPore).order_by(SQL.DesignPore.id).all()
		n = len(query)
		obj_list = [DesignPore() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignPore", query[i], obj_list[i], True)
		return obj_list
	def GetDesignPoreIds(self):
		query=self.session.query(SQL.DesignPore).order_by(SQL.DesignPore.id).all()
		return [obj.id for obj in query]
	def GetDesignPoreNames(self):
		query=self.session.query(SQL.DesignPore).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignPore(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignPore() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignPore", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignPore(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignPore).filter(SQL.DesignPore.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignPoreByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignPore", fields)
		query = self.session.query(SQL.DesignPore).filter_by(**sql_fields).order_by(SQL.DesignPore.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignPore() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignPore", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignPoreIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignPore", fields)
		query = self.session.query(SQL.DesignPore).filter_by(**sql_fields).order_by(SQL.DesignPore.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignPoreByFields(self, fields):
		objs = self.__GetDesignPoreByFields(fields)
		if len(objs) == 0:
			obj = DesignPore()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignPoreByField1(self, field, value):
		return self.GetDesignPoreByFields({field:value})
	def GetDesignPoreByField2(self, field1, value1, field2, value2):
		return self.GetDesignPoreByFields({field1:value1, field2:value2})
	def GetDesignPoreListByFields(self, fields):
		return self.__GetDesignPoreByFields(fields)
	def GetDesignPoreListByField1(self, field, value):
		return self.GetDesignPoreListByFields({field:value})
	def GetDesignPoreListByField2(self, field1, value1, field2, value2):
		return self.GetDesignPoreListByFields({field1:value1, field2:value2})
	def GetDesignPoreIdByFields(self, fields):
		obj_ids = self.__GetDesignPoreIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignPoreIdByField1(self, field, value):
		return self.GetDesignPoreIdByFields({field:value})
	def GetDesignPoreIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignPoreIdByFields({field1:value1, field2:value2})
	def GetDesignPoreIdListByFields(self, fields):
		return self.__GetDesignPoreIdsByFields(fields)
	def GetDesignPoreIdListByField1(self, field, value):
		return self.GetDesignPoreIdListByFields({field:value})
	def GetDesignPoreIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignPoreIdListByFields({field1:value1, field2:value2})
	def GetDesignPoreListByForeignKey(self, fkey, id):
		return self.GetDesignPoreListByFields({fkey:id})
	def GetDesignPoreIdListByForeignKey(self, fkey, id):
		return self.GetDesignPoreIdListByFields({fkey:id})

	#DesignSite 类型的CRUD操作
	def AddDesignSite(self, design_site):
		sql_obj = SQL.DesignSite()
		CbmUtil.CopyAttribsOfCbmType("DesignSite", design_site, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignSite(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignSite).filter(SQL.DesignSite.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignSite(self, design_site):
		ret=True
		try:
			sql_obj = SQL.DesignSite()
			CbmUtil.CopyAttribsOfCbmType("DesignSite", design_site, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignSite", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignSite).filter(SQL.DesignSite.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignSiteById(self, id):
		query=self.session.query(SQL.DesignSite).filter(SQL.DesignSite.id==id).first()
		obj = DesignSite()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignSite", query, obj, True)
		return obj
	def GetDesignSiteByForeignKey(self, fkey, id):
		return self.GetDesignSiteByFields({fkey:id})
	def GetDesignSiteIdByForeignKey(self, fkey, id):
		return self.GetDesignSiteIdByFields({fkey:id})
	def GetDesignSiteList(self):
		query = self.session.query(SQL.DesignSite).order_by(SQL.DesignSite.id).all()
		n = len(query)
		obj_list = [DesignSite() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignSite", query[i], obj_list[i], True)
		return obj_list
	def GetDesignSiteIds(self):
		query=self.session.query(SQL.DesignSite).order_by(SQL.DesignSite.id).all()
		return [obj.id for obj in query]
	def GetDesignSiteNames(self):
		query=self.session.query(SQL.DesignSite).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignSite(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignSite() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignSite", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignSite(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignSite).filter(SQL.DesignSite.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignSiteByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignSite", fields)
		query = self.session.query(SQL.DesignSite).filter_by(**sql_fields).order_by(SQL.DesignSite.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignSite() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignSite", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignSiteIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignSite", fields)
		query = self.session.query(SQL.DesignSite).filter_by(**sql_fields).order_by(SQL.DesignSite.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignSiteByFields(self, fields):
		objs = self.__GetDesignSiteByFields(fields)
		if len(objs) == 0:
			obj = DesignSite()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignSiteByField1(self, field, value):
		return self.GetDesignSiteByFields({field:value})
	def GetDesignSiteByField2(self, field1, value1, field2, value2):
		return self.GetDesignSiteByFields({field1:value1, field2:value2})
	def GetDesignSiteListByFields(self, fields):
		return self.__GetDesignSiteByFields(fields)
	def GetDesignSiteListByField1(self, field, value):
		return self.GetDesignSiteListByFields({field:value})
	def GetDesignSiteListByField2(self, field1, value1, field2, value2):
		return self.GetDesignSiteListByFields({field1:value1, field2:value2})
	def GetDesignSiteIdByFields(self, fields):
		obj_ids = self.__GetDesignSiteIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignSiteIdByField1(self, field, value):
		return self.GetDesignSiteIdByFields({field:value})
	def GetDesignSiteIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignSiteIdByFields({field1:value1, field2:value2})
	def GetDesignSiteIdListByFields(self, fields):
		return self.__GetDesignSiteIdsByFields(fields)
	def GetDesignSiteIdListByField1(self, field, value):
		return self.GetDesignSiteIdListByFields({field:value})
	def GetDesignSiteIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignSiteIdListByFields({field1:value1, field2:value2})
	def GetDesignSiteListByForeignKey(self, fkey, id):
		return self.GetDesignSiteListByFields({fkey:id})
	def GetDesignSiteIdListByForeignKey(self, fkey, id):
		return self.GetDesignSiteIdListByFields({fkey:id})

	#DesignTechnology 类型的CRUD操作
	def AddDesignTechnology(self, design_technology):
		sql_obj = SQL.DesignTechnology()
		CbmUtil.CopyAttribsOfCbmType("DesignTechnology", design_technology, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignTechnology(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignTechnology).filter(SQL.DesignTechnology.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignTechnology(self, design_technology):
		ret=True
		try:
			sql_obj = SQL.DesignTechnology()
			CbmUtil.CopyAttribsOfCbmType("DesignTechnology", design_technology, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignTechnology", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignTechnology).filter(SQL.DesignTechnology.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignTechnologyById(self, id):
		query=self.session.query(SQL.DesignTechnology).filter(SQL.DesignTechnology.id==id).first()
		obj = DesignTechnology()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignTechnology", query, obj, True)
		return obj
	def GetDesignTechnologyByForeignKey(self, fkey, id):
		return self.GetDesignTechnologyByFields({fkey:id})
	def GetDesignTechnologyIdByForeignKey(self, fkey, id):
		return self.GetDesignTechnologyIdByFields({fkey:id})
	def GetDesignTechnologyList(self):
		query = self.session.query(SQL.DesignTechnology).order_by(SQL.DesignTechnology.id).all()
		n = len(query)
		obj_list = [DesignTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignTechnology", query[i], obj_list[i], True)
		return obj_list
	def GetDesignTechnologyIds(self):
		query=self.session.query(SQL.DesignTechnology).order_by(SQL.DesignTechnology.id).all()
		return [obj.id for obj in query]
	def GetDesignTechnologyNames(self):
		query=self.session.query(SQL.DesignTechnology).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignTechnology(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignTechnology", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignTechnology(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignTechnology).filter(SQL.DesignTechnology.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignTechnologyByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignTechnology", fields)
		query = self.session.query(SQL.DesignTechnology).filter_by(**sql_fields).order_by(SQL.DesignTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignTechnology() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignTechnology", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignTechnologyIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignTechnology", fields)
		query = self.session.query(SQL.DesignTechnology).filter_by(**sql_fields).order_by(SQL.DesignTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignTechnologyByFields(self, fields):
		objs = self.__GetDesignTechnologyByFields(fields)
		if len(objs) == 0:
			obj = DesignTechnology()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignTechnologyByField1(self, field, value):
		return self.GetDesignTechnologyByFields({field:value})
	def GetDesignTechnologyByField2(self, field1, value1, field2, value2):
		return self.GetDesignTechnologyByFields({field1:value1, field2:value2})
	def GetDesignTechnologyListByFields(self, fields):
		return self.__GetDesignTechnologyByFields(fields)
	def GetDesignTechnologyListByField1(self, field, value):
		return self.GetDesignTechnologyListByFields({field:value})
	def GetDesignTechnologyListByField2(self, field1, value1, field2, value2):
		return self.GetDesignTechnologyListByFields({field1:value1, field2:value2})
	def GetDesignTechnologyIdByFields(self, fields):
		obj_ids = self.__GetDesignTechnologyIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignTechnologyIdByField1(self, field, value):
		return self.GetDesignTechnologyIdByFields({field:value})
	def GetDesignTechnologyIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignTechnologyIdByFields({field1:value1, field2:value2})
	def GetDesignTechnologyIdListByFields(self, fields):
		return self.__GetDesignTechnologyIdsByFields(fields)
	def GetDesignTechnologyIdListByField1(self, field, value):
		return self.GetDesignTechnologyIdListByFields({field:value})
	def GetDesignTechnologyIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignTechnologyIdListByFields({field1:value1, field2:value2})
	def GetDesignTechnologyListByForeignKey(self, fkey, id):
		return self.GetDesignTechnologyListByFields({fkey:id})
	def GetDesignTechnologyIdListByForeignKey(self, fkey, id):
		return self.GetDesignTechnologyIdListByFields({fkey:id})

	#DesignTunnelControlPoint 类型的CRUD操作
	def AddDesignTunnelControlPoint(self, design_tunnel_control_point):
		sql_obj = SQL.DesignTunnelControlPoint()
		CbmUtil.CopyAttribsOfCbmType("DesignTunnelControlPoint", design_tunnel_control_point, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignTunnelControlPoint(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignTunnelControlPoint).filter(SQL.DesignTunnelControlPoint.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignTunnelControlPoint(self, design_tunnel_control_point):
		ret=True
		try:
			sql_obj = SQL.DesignTunnelControlPoint()
			CbmUtil.CopyAttribsOfCbmType("DesignTunnelControlPoint", design_tunnel_control_point, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignTunnelControlPoint", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignTunnelControlPoint).filter(SQL.DesignTunnelControlPoint.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignTunnelControlPointById(self, id):
		query=self.session.query(SQL.DesignTunnelControlPoint).filter(SQL.DesignTunnelControlPoint.id==id).first()
		obj = DesignTunnelControlPoint()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignTunnelControlPoint", query, obj, True)
		return obj
	def GetDesignTunnelControlPointByForeignKey(self, fkey, id):
		return self.GetDesignTunnelControlPointByFields({fkey:id})
	def GetDesignTunnelControlPointIdByForeignKey(self, fkey, id):
		return self.GetDesignTunnelControlPointIdByFields({fkey:id})
	def GetDesignTunnelControlPointList(self):
		query = self.session.query(SQL.DesignTunnelControlPoint).order_by(SQL.DesignTunnelControlPoint.id).all()
		n = len(query)
		obj_list = [DesignTunnelControlPoint() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignTunnelControlPoint", query[i], obj_list[i], True)
		return obj_list
	def GetDesignTunnelControlPointIds(self):
		query=self.session.query(SQL.DesignTunnelControlPoint).order_by(SQL.DesignTunnelControlPoint.id).all()
		return [obj.id for obj in query]
	def GetDesignTunnelControlPointNames(self):
		query=self.session.query(SQL.DesignTunnelControlPoint).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignTunnelControlPoint(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignTunnelControlPoint() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignTunnelControlPoint", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignTunnelControlPoint(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignTunnelControlPoint).filter(SQL.DesignTunnelControlPoint.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignTunnelControlPointByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignTunnelControlPoint", fields)
		query = self.session.query(SQL.DesignTunnelControlPoint).filter_by(**sql_fields).order_by(SQL.DesignTunnelControlPoint.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignTunnelControlPoint() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignTunnelControlPoint", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignTunnelControlPointIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignTunnelControlPoint", fields)
		query = self.session.query(SQL.DesignTunnelControlPoint).filter_by(**sql_fields).order_by(SQL.DesignTunnelControlPoint.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignTunnelControlPointByFields(self, fields):
		objs = self.__GetDesignTunnelControlPointByFields(fields)
		if len(objs) == 0:
			obj = DesignTunnelControlPoint()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignTunnelControlPointByField1(self, field, value):
		return self.GetDesignTunnelControlPointByFields({field:value})
	def GetDesignTunnelControlPointByField2(self, field1, value1, field2, value2):
		return self.GetDesignTunnelControlPointByFields({field1:value1, field2:value2})
	def GetDesignTunnelControlPointListByFields(self, fields):
		return self.__GetDesignTunnelControlPointByFields(fields)
	def GetDesignTunnelControlPointListByField1(self, field, value):
		return self.GetDesignTunnelControlPointListByFields({field:value})
	def GetDesignTunnelControlPointListByField2(self, field1, value1, field2, value2):
		return self.GetDesignTunnelControlPointListByFields({field1:value1, field2:value2})
	def GetDesignTunnelControlPointIdByFields(self, fields):
		obj_ids = self.__GetDesignTunnelControlPointIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignTunnelControlPointIdByField1(self, field, value):
		return self.GetDesignTunnelControlPointIdByFields({field:value})
	def GetDesignTunnelControlPointIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignTunnelControlPointIdByFields({field1:value1, field2:value2})
	def GetDesignTunnelControlPointIdListByFields(self, fields):
		return self.__GetDesignTunnelControlPointIdsByFields(fields)
	def GetDesignTunnelControlPointIdListByField1(self, field, value):
		return self.GetDesignTunnelControlPointIdListByFields({field:value})
	def GetDesignTunnelControlPointIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignTunnelControlPointIdListByFields({field1:value1, field2:value2})
	def GetDesignTunnelControlPointListByForeignKey(self, fkey, id):
		return self.GetDesignTunnelControlPointListByFields({fkey:id})
	def GetDesignTunnelControlPointIdListByForeignKey(self, fkey, id):
		return self.GetDesignTunnelControlPointIdListByFields({fkey:id})

	#DesignWorkSurfControlPoint 类型的CRUD操作
	def AddDesignWorkSurfControlPoint(self, design_work_surf_control_point):
		sql_obj = SQL.DesignWorkSurfControlPoint()
		CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfControlPoint", design_work_surf_control_point, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignWorkSurfControlPoint(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignWorkSurfControlPoint).filter(SQL.DesignWorkSurfControlPoint.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignWorkSurfControlPoint(self, design_work_surf_control_point):
		ret=True
		try:
			sql_obj = SQL.DesignWorkSurfControlPoint()
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfControlPoint", design_work_surf_control_point, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignWorkSurfControlPoint", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignWorkSurfControlPoint).filter(SQL.DesignWorkSurfControlPoint.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignWorkSurfControlPointById(self, id):
		query=self.session.query(SQL.DesignWorkSurfControlPoint).filter(SQL.DesignWorkSurfControlPoint.id==id).first()
		obj = DesignWorkSurfControlPoint()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfControlPoint", query, obj, True)
		return obj
	def GetDesignWorkSurfControlPointByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfControlPointByFields({fkey:id})
	def GetDesignWorkSurfControlPointIdByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfControlPointIdByFields({fkey:id})
	def GetDesignWorkSurfControlPointList(self):
		query = self.session.query(SQL.DesignWorkSurfControlPoint).order_by(SQL.DesignWorkSurfControlPoint.id).all()
		n = len(query)
		obj_list = [DesignWorkSurfControlPoint() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfControlPoint", query[i], obj_list[i], True)
		return obj_list
	def GetDesignWorkSurfControlPointIds(self):
		query=self.session.query(SQL.DesignWorkSurfControlPoint).order_by(SQL.DesignWorkSurfControlPoint.id).all()
		return [obj.id for obj in query]
	def GetDesignWorkSurfControlPointNames(self):
		query=self.session.query(SQL.DesignWorkSurfControlPoint).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignWorkSurfControlPoint(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignWorkSurfControlPoint() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfControlPoint", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignWorkSurfControlPoint(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignWorkSurfControlPoint).filter(SQL.DesignWorkSurfControlPoint.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignWorkSurfControlPointByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignWorkSurfControlPoint", fields)
		query = self.session.query(SQL.DesignWorkSurfControlPoint).filter_by(**sql_fields).order_by(SQL.DesignWorkSurfControlPoint.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignWorkSurfControlPoint() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfControlPoint", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignWorkSurfControlPointIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignWorkSurfControlPoint", fields)
		query = self.session.query(SQL.DesignWorkSurfControlPoint).filter_by(**sql_fields).order_by(SQL.DesignWorkSurfControlPoint.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignWorkSurfControlPointByFields(self, fields):
		objs = self.__GetDesignWorkSurfControlPointByFields(fields)
		if len(objs) == 0:
			obj = DesignWorkSurfControlPoint()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignWorkSurfControlPointByField1(self, field, value):
		return self.GetDesignWorkSurfControlPointByFields({field:value})
	def GetDesignWorkSurfControlPointByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfControlPointByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfControlPointListByFields(self, fields):
		return self.__GetDesignWorkSurfControlPointByFields(fields)
	def GetDesignWorkSurfControlPointListByField1(self, field, value):
		return self.GetDesignWorkSurfControlPointListByFields({field:value})
	def GetDesignWorkSurfControlPointListByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfControlPointListByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfControlPointIdByFields(self, fields):
		obj_ids = self.__GetDesignWorkSurfControlPointIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignWorkSurfControlPointIdByField1(self, field, value):
		return self.GetDesignWorkSurfControlPointIdByFields({field:value})
	def GetDesignWorkSurfControlPointIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfControlPointIdByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfControlPointIdListByFields(self, fields):
		return self.__GetDesignWorkSurfControlPointIdsByFields(fields)
	def GetDesignWorkSurfControlPointIdListByField1(self, field, value):
		return self.GetDesignWorkSurfControlPointIdListByFields({field:value})
	def GetDesignWorkSurfControlPointIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfControlPointIdListByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfControlPointListByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfControlPointListByFields({fkey:id})
	def GetDesignWorkSurfControlPointIdListByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfControlPointIdListByFields({fkey:id})

	#DesignWorkSurfTechnology 类型的CRUD操作
	def AddDesignWorkSurfTechnology(self, design_work_surf_technology):
		sql_obj = SQL.DesignWorkSurfTechnology()
		CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfTechnology", design_work_surf_technology, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDesignWorkSurfTechnology(self, id):
		ret=True
		try:
			self.session.query(SQL.DesignWorkSurfTechnology).filter(SQL.DesignWorkSurfTechnology.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDesignWorkSurfTechnology(self, design_work_surf_technology):
		ret=True
		try:
			sql_obj = SQL.DesignWorkSurfTechnology()
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfTechnology", design_work_surf_technology, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DesignWorkSurfTechnology", sql_obj)
			del attribs['id']
			self.session.query(SQL.DesignWorkSurfTechnology).filter(SQL.DesignWorkSurfTechnology.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDesignWorkSurfTechnologyById(self, id):
		query=self.session.query(SQL.DesignWorkSurfTechnology).filter(SQL.DesignWorkSurfTechnology.id==id).first()
		obj = DesignWorkSurfTechnology()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfTechnology", query, obj, True)
		return obj
	def GetDesignWorkSurfTechnologyByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfTechnologyByFields({fkey:id})
	def GetDesignWorkSurfTechnologyIdByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfTechnologyIdByFields({fkey:id})
	def GetDesignWorkSurfTechnologyList(self):
		query = self.session.query(SQL.DesignWorkSurfTechnology).order_by(SQL.DesignWorkSurfTechnology.id).all()
		n = len(query)
		obj_list = [DesignWorkSurfTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfTechnology", query[i], obj_list[i], True)
		return obj_list
	def GetDesignWorkSurfTechnologyIds(self):
		query=self.session.query(SQL.DesignWorkSurfTechnology).order_by(SQL.DesignWorkSurfTechnology.id).all()
		return [obj.id for obj in query]
	def GetDesignWorkSurfTechnologyNames(self):
		query=self.session.query(SQL.DesignWorkSurfTechnology).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDesignWorkSurfTechnology(self, objs):
		n = len(objs)
		sql_objs = [SQL.DesignWorkSurfTechnology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfTechnology", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDesignWorkSurfTechnology(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DesignWorkSurfTechnology).filter(SQL.DesignWorkSurfTechnology.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDesignWorkSurfTechnologyByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignWorkSurfTechnology", fields)
		query = self.session.query(SQL.DesignWorkSurfTechnology).filter_by(**sql_fields).order_by(SQL.DesignWorkSurfTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DesignWorkSurfTechnology() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DesignWorkSurfTechnology", query[i], obj_list[i], True)
			return obj_list
	def __GetDesignWorkSurfTechnologyIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DesignWorkSurfTechnology", fields)
		query = self.session.query(SQL.DesignWorkSurfTechnology).filter_by(**sql_fields).order_by(SQL.DesignWorkSurfTechnology.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDesignWorkSurfTechnologyByFields(self, fields):
		objs = self.__GetDesignWorkSurfTechnologyByFields(fields)
		if len(objs) == 0:
			obj = DesignWorkSurfTechnology()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDesignWorkSurfTechnologyByField1(self, field, value):
		return self.GetDesignWorkSurfTechnologyByFields({field:value})
	def GetDesignWorkSurfTechnologyByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfTechnologyByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfTechnologyListByFields(self, fields):
		return self.__GetDesignWorkSurfTechnologyByFields(fields)
	def GetDesignWorkSurfTechnologyListByField1(self, field, value):
		return self.GetDesignWorkSurfTechnologyListByFields({field:value})
	def GetDesignWorkSurfTechnologyListByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfTechnologyListByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfTechnologyIdByFields(self, fields):
		obj_ids = self.__GetDesignWorkSurfTechnologyIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDesignWorkSurfTechnologyIdByField1(self, field, value):
		return self.GetDesignWorkSurfTechnologyIdByFields({field:value})
	def GetDesignWorkSurfTechnologyIdByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfTechnologyIdByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfTechnologyIdListByFields(self, fields):
		return self.__GetDesignWorkSurfTechnologyIdsByFields(fields)
	def GetDesignWorkSurfTechnologyIdListByField1(self, field, value):
		return self.GetDesignWorkSurfTechnologyIdListByFields({field:value})
	def GetDesignWorkSurfTechnologyIdListByField2(self, field1, value1, field2, value2):
		return self.GetDesignWorkSurfTechnologyIdListByFields({field1:value1, field2:value2})
	def GetDesignWorkSurfTechnologyListByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfTechnologyListByFields({fkey:id})
	def GetDesignWorkSurfTechnologyIdListByForeignKey(self, fkey, id):
		return self.GetDesignWorkSurfTechnologyIdListByFields({fkey:id})

	#DrillingRadiusParam 类型的CRUD操作
	def AddDrillingRadiusParam(self, drilling_radius_param):
		sql_obj = SQL.DrillingRadiusParam()
		CbmUtil.CopyAttribsOfCbmType("DrillingRadiusParam", drilling_radius_param, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDrillingRadiusParam(self, id):
		ret=True
		try:
			self.session.query(SQL.DrillingRadiusParam).filter(SQL.DrillingRadiusParam.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDrillingRadiusParam(self, drilling_radius_param):
		ret=True
		try:
			sql_obj = SQL.DrillingRadiusParam()
			CbmUtil.CopyAttribsOfCbmType("DrillingRadiusParam", drilling_radius_param, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DrillingRadiusParam", sql_obj)
			del attribs['id']
			self.session.query(SQL.DrillingRadiusParam).filter(SQL.DrillingRadiusParam.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDrillingRadiusParamById(self, id):
		query=self.session.query(SQL.DrillingRadiusParam).filter(SQL.DrillingRadiusParam.id==id).first()
		obj = DrillingRadiusParam()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DrillingRadiusParam", query, obj, True)
		return obj
	def GetDrillingRadiusParamByForeignKey(self, fkey, id):
		return self.GetDrillingRadiusParamByFields({fkey:id})
	def GetDrillingRadiusParamIdByForeignKey(self, fkey, id):
		return self.GetDrillingRadiusParamIdByFields({fkey:id})
	def GetDrillingRadiusParamList(self):
		query = self.session.query(SQL.DrillingRadiusParam).order_by(SQL.DrillingRadiusParam.id).all()
		n = len(query)
		obj_list = [DrillingRadiusParam() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DrillingRadiusParam", query[i], obj_list[i], True)
		return obj_list
	def GetDrillingRadiusParamIds(self):
		query=self.session.query(SQL.DrillingRadiusParam).order_by(SQL.DrillingRadiusParam.id).all()
		return [obj.id for obj in query]
	def GetDrillingRadiusParamNames(self):
		query=self.session.query(SQL.DrillingRadiusParam).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDrillingRadiusParam(self, objs):
		n = len(objs)
		sql_objs = [SQL.DrillingRadiusParam() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DrillingRadiusParam", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDrillingRadiusParam(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DrillingRadiusParam).filter(SQL.DrillingRadiusParam.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDrillingRadiusParamByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DrillingRadiusParam", fields)
		query = self.session.query(SQL.DrillingRadiusParam).filter_by(**sql_fields).order_by(SQL.DrillingRadiusParam.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DrillingRadiusParam() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DrillingRadiusParam", query[i], obj_list[i], True)
			return obj_list
	def __GetDrillingRadiusParamIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DrillingRadiusParam", fields)
		query = self.session.query(SQL.DrillingRadiusParam).filter_by(**sql_fields).order_by(SQL.DrillingRadiusParam.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDrillingRadiusParamByFields(self, fields):
		objs = self.__GetDrillingRadiusParamByFields(fields)
		if len(objs) == 0:
			obj = DrillingRadiusParam()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDrillingRadiusParamByField1(self, field, value):
		return self.GetDrillingRadiusParamByFields({field:value})
	def GetDrillingRadiusParamByField2(self, field1, value1, field2, value2):
		return self.GetDrillingRadiusParamByFields({field1:value1, field2:value2})
	def GetDrillingRadiusParamListByFields(self, fields):
		return self.__GetDrillingRadiusParamByFields(fields)
	def GetDrillingRadiusParamListByField1(self, field, value):
		return self.GetDrillingRadiusParamListByFields({field:value})
	def GetDrillingRadiusParamListByField2(self, field1, value1, field2, value2):
		return self.GetDrillingRadiusParamListByFields({field1:value1, field2:value2})
	def GetDrillingRadiusParamIdByFields(self, fields):
		obj_ids = self.__GetDrillingRadiusParamIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDrillingRadiusParamIdByField1(self, field, value):
		return self.GetDrillingRadiusParamIdByFields({field:value})
	def GetDrillingRadiusParamIdByField2(self, field1, value1, field2, value2):
		return self.GetDrillingRadiusParamIdByFields({field1:value1, field2:value2})
	def GetDrillingRadiusParamIdListByFields(self, fields):
		return self.__GetDrillingRadiusParamIdsByFields(fields)
	def GetDrillingRadiusParamIdListByField1(self, field, value):
		return self.GetDrillingRadiusParamIdListByFields({field:value})
	def GetDrillingRadiusParamIdListByField2(self, field1, value1, field2, value2):
		return self.GetDrillingRadiusParamIdListByFields({field1:value1, field2:value2})
	def GetDrillingRadiusParamListByForeignKey(self, fkey, id):
		return self.GetDrillingRadiusParamListByFields({fkey:id})
	def GetDrillingRadiusParamIdListByForeignKey(self, fkey, id):
		return self.GetDrillingRadiusParamIdListByFields({fkey:id})

	#DrillingSurf 类型的CRUD操作
	def AddDrillingSurf(self, drilling_surf):
		sql_obj = SQL.DrillingSurf()
		CbmUtil.CopyAttribsOfCbmType("DrillingSurf", drilling_surf, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteDrillingSurf(self, id):
		ret=True
		try:
			self.session.query(SQL.DrillingSurf).filter(SQL.DrillingSurf.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateDrillingSurf(self, drilling_surf):
		ret=True
		try:
			sql_obj = SQL.DrillingSurf()
			CbmUtil.CopyAttribsOfCbmType("DrillingSurf", drilling_surf, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("DrillingSurf", sql_obj)
			del attribs['id']
			self.session.query(SQL.DrillingSurf).filter(SQL.DrillingSurf.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetDrillingSurfById(self, id):
		query=self.session.query(SQL.DrillingSurf).filter(SQL.DrillingSurf.id==id).first()
		obj = DrillingSurf()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("DrillingSurf", query, obj, True)
		return obj
	def GetDrillingSurfByForeignKey(self, fkey, id):
		return self.GetDrillingSurfByFields({fkey:id})
	def GetDrillingSurfIdByForeignKey(self, fkey, id):
		return self.GetDrillingSurfIdByFields({fkey:id})
	def GetDrillingSurfList(self):
		query = self.session.query(SQL.DrillingSurf).order_by(SQL.DrillingSurf.id).all()
		n = len(query)
		obj_list = [DrillingSurf() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DrillingSurf", query[i], obj_list[i], True)
		return obj_list
	def GetDrillingSurfIds(self):
		query=self.session.query(SQL.DrillingSurf).order_by(SQL.DrillingSurf.id).all()
		return [obj.id for obj in query]
	def GetDrillingSurfNames(self):
		query=self.session.query(SQL.DrillingSurf).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreDrillingSurf(self, objs):
		n = len(objs)
		sql_objs = [SQL.DrillingSurf() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("DrillingSurf", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreDrillingSurf(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.DrillingSurf).filter(SQL.DrillingSurf.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetDrillingSurfByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DrillingSurf", fields)
		query = self.session.query(SQL.DrillingSurf).filter_by(**sql_fields).order_by(SQL.DrillingSurf.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [DrillingSurf() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("DrillingSurf", query[i], obj_list[i], True)
			return obj_list
	def __GetDrillingSurfIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("DrillingSurf", fields)
		query = self.session.query(SQL.DrillingSurf).filter_by(**sql_fields).order_by(SQL.DrillingSurf.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetDrillingSurfByFields(self, fields):
		objs = self.__GetDrillingSurfByFields(fields)
		if len(objs) == 0:
			obj = DrillingSurf()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetDrillingSurfByField1(self, field, value):
		return self.GetDrillingSurfByFields({field:value})
	def GetDrillingSurfByField2(self, field1, value1, field2, value2):
		return self.GetDrillingSurfByFields({field1:value1, field2:value2})
	def GetDrillingSurfListByFields(self, fields):
		return self.__GetDrillingSurfByFields(fields)
	def GetDrillingSurfListByField1(self, field, value):
		return self.GetDrillingSurfListByFields({field:value})
	def GetDrillingSurfListByField2(self, field1, value1, field2, value2):
		return self.GetDrillingSurfListByFields({field1:value1, field2:value2})
	def GetDrillingSurfIdByFields(self, fields):
		obj_ids = self.__GetDrillingSurfIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetDrillingSurfIdByField1(self, field, value):
		return self.GetDrillingSurfIdByFields({field:value})
	def GetDrillingSurfIdByField2(self, field1, value1, field2, value2):
		return self.GetDrillingSurfIdByFields({field1:value1, field2:value2})
	def GetDrillingSurfIdListByFields(self, fields):
		return self.__GetDrillingSurfIdsByFields(fields)
	def GetDrillingSurfIdListByField1(self, field, value):
		return self.GetDrillingSurfIdListByFields({field:value})
	def GetDrillingSurfIdListByField2(self, field1, value1, field2, value2):
		return self.GetDrillingSurfIdListByFields({field1:value1, field2:value2})
	def GetDrillingSurfListByForeignKey(self, fkey, id):
		return self.GetDrillingSurfListByFields({fkey:id})
	def GetDrillingSurfIdListByForeignKey(self, fkey, id):
		return self.GetDrillingSurfIdListByFields({fkey:id})

	#HighDrillingPore 类型的CRUD操作
	def AddHighDrillingPore(self, high_drilling_pore):
		sql_obj = SQL.HighDrillingPore()
		CbmUtil.CopyAttribsOfCbmType("HighDrillingPore", high_drilling_pore, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteHighDrillingPore(self, id):
		ret=True
		try:
			self.session.query(SQL.HighDrillingPore).filter(SQL.HighDrillingPore.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateHighDrillingPore(self, high_drilling_pore):
		ret=True
		try:
			sql_obj = SQL.HighDrillingPore()
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPore", high_drilling_pore, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("HighDrillingPore", sql_obj)
			del attribs['id']
			self.session.query(SQL.HighDrillingPore).filter(SQL.HighDrillingPore.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetHighDrillingPoreById(self, id):
		query=self.session.query(SQL.HighDrillingPore).filter(SQL.HighDrillingPore.id==id).first()
		obj = HighDrillingPore()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPore", query, obj, True)
		return obj
	def GetHighDrillingPoreByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreByFields({fkey:id})
	def GetHighDrillingPoreIdByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreIdByFields({fkey:id})
	def GetHighDrillingPoreList(self):
		query = self.session.query(SQL.HighDrillingPore).order_by(SQL.HighDrillingPore.id).all()
		n = len(query)
		obj_list = [HighDrillingPore() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPore", query[i], obj_list[i], True)
		return obj_list
	def GetHighDrillingPoreIds(self):
		query=self.session.query(SQL.HighDrillingPore).order_by(SQL.HighDrillingPore.id).all()
		return [obj.id for obj in query]
	def GetHighDrillingPoreNames(self):
		query=self.session.query(SQL.HighDrillingPore).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreHighDrillingPore(self, objs):
		n = len(objs)
		sql_objs = [SQL.HighDrillingPore() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPore", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreHighDrillingPore(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.HighDrillingPore).filter(SQL.HighDrillingPore.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetHighDrillingPoreByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingPore", fields)
		query = self.session.query(SQL.HighDrillingPore).filter_by(**sql_fields).order_by(SQL.HighDrillingPore.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [HighDrillingPore() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("HighDrillingPore", query[i], obj_list[i], True)
			return obj_list
	def __GetHighDrillingPoreIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingPore", fields)
		query = self.session.query(SQL.HighDrillingPore).filter_by(**sql_fields).order_by(SQL.HighDrillingPore.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetHighDrillingPoreByFields(self, fields):
		objs = self.__GetHighDrillingPoreByFields(fields)
		if len(objs) == 0:
			obj = HighDrillingPore()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetHighDrillingPoreByField1(self, field, value):
		return self.GetHighDrillingPoreByFields({field:value})
	def GetHighDrillingPoreByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreListByFields(self, fields):
		return self.__GetHighDrillingPoreByFields(fields)
	def GetHighDrillingPoreListByField1(self, field, value):
		return self.GetHighDrillingPoreListByFields({field:value})
	def GetHighDrillingPoreListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreListByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreIdByFields(self, fields):
		obj_ids = self.__GetHighDrillingPoreIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetHighDrillingPoreIdByField1(self, field, value):
		return self.GetHighDrillingPoreIdByFields({field:value})
	def GetHighDrillingPoreIdByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreIdByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreIdListByFields(self, fields):
		return self.__GetHighDrillingPoreIdsByFields(fields)
	def GetHighDrillingPoreIdListByField1(self, field, value):
		return self.GetHighDrillingPoreIdListByFields({field:value})
	def GetHighDrillingPoreIdListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreIdListByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreListByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreListByFields({fkey:id})
	def GetHighDrillingPoreIdListByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreIdListByFields({fkey:id})

	#HighDrillingPoreParam 类型的CRUD操作
	def AddHighDrillingPoreParam(self, high_drilling_pore_param):
		sql_obj = SQL.HighDrillingPoreParam()
		CbmUtil.CopyAttribsOfCbmType("HighDrillingPoreParam", high_drilling_pore_param, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteHighDrillingPoreParam(self, id):
		ret=True
		try:
			self.session.query(SQL.HighDrillingPoreParam).filter(SQL.HighDrillingPoreParam.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateHighDrillingPoreParam(self, high_drilling_pore_param):
		ret=True
		try:
			sql_obj = SQL.HighDrillingPoreParam()
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPoreParam", high_drilling_pore_param, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("HighDrillingPoreParam", sql_obj)
			del attribs['id']
			self.session.query(SQL.HighDrillingPoreParam).filter(SQL.HighDrillingPoreParam.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetHighDrillingPoreParamById(self, id):
		query=self.session.query(SQL.HighDrillingPoreParam).filter(SQL.HighDrillingPoreParam.id==id).first()
		obj = HighDrillingPoreParam()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPoreParam", query, obj, True)
		return obj
	def GetHighDrillingPoreParamByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreParamByFields({fkey:id})
	def GetHighDrillingPoreParamIdByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreParamIdByFields({fkey:id})
	def GetHighDrillingPoreParamList(self):
		query = self.session.query(SQL.HighDrillingPoreParam).order_by(SQL.HighDrillingPoreParam.id).all()
		n = len(query)
		obj_list = [HighDrillingPoreParam() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPoreParam", query[i], obj_list[i], True)
		return obj_list
	def GetHighDrillingPoreParamIds(self):
		query=self.session.query(SQL.HighDrillingPoreParam).order_by(SQL.HighDrillingPoreParam.id).all()
		return [obj.id for obj in query]
	def GetHighDrillingPoreParamNames(self):
		query=self.session.query(SQL.HighDrillingPoreParam).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreHighDrillingPoreParam(self, objs):
		n = len(objs)
		sql_objs = [SQL.HighDrillingPoreParam() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingPoreParam", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreHighDrillingPoreParam(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.HighDrillingPoreParam).filter(SQL.HighDrillingPoreParam.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetHighDrillingPoreParamByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingPoreParam", fields)
		query = self.session.query(SQL.HighDrillingPoreParam).filter_by(**sql_fields).order_by(SQL.HighDrillingPoreParam.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [HighDrillingPoreParam() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("HighDrillingPoreParam", query[i], obj_list[i], True)
			return obj_list
	def __GetHighDrillingPoreParamIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingPoreParam", fields)
		query = self.session.query(SQL.HighDrillingPoreParam).filter_by(**sql_fields).order_by(SQL.HighDrillingPoreParam.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetHighDrillingPoreParamByFields(self, fields):
		objs = self.__GetHighDrillingPoreParamByFields(fields)
		if len(objs) == 0:
			obj = HighDrillingPoreParam()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetHighDrillingPoreParamByField1(self, field, value):
		return self.GetHighDrillingPoreParamByFields({field:value})
	def GetHighDrillingPoreParamByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreParamByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreParamListByFields(self, fields):
		return self.__GetHighDrillingPoreParamByFields(fields)
	def GetHighDrillingPoreParamListByField1(self, field, value):
		return self.GetHighDrillingPoreParamListByFields({field:value})
	def GetHighDrillingPoreParamListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreParamListByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreParamIdByFields(self, fields):
		obj_ids = self.__GetHighDrillingPoreParamIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetHighDrillingPoreParamIdByField1(self, field, value):
		return self.GetHighDrillingPoreParamIdByFields({field:value})
	def GetHighDrillingPoreParamIdByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreParamIdByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreParamIdListByFields(self, fields):
		return self.__GetHighDrillingPoreParamIdsByFields(fields)
	def GetHighDrillingPoreParamIdListByField1(self, field, value):
		return self.GetHighDrillingPoreParamIdListByFields({field:value})
	def GetHighDrillingPoreParamIdListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingPoreParamIdListByFields({field1:value1, field2:value2})
	def GetHighDrillingPoreParamListByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreParamListByFields({fkey:id})
	def GetHighDrillingPoreParamIdListByForeignKey(self, fkey, id):
		return self.GetHighDrillingPoreParamIdListByFields({fkey:id})

	#HighDrillingSiteParam 类型的CRUD操作
	def AddHighDrillingSiteParam(self, high_drilling_site_param):
		sql_obj = SQL.HighDrillingSiteParam()
		CbmUtil.CopyAttribsOfCbmType("HighDrillingSiteParam", high_drilling_site_param, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteHighDrillingSiteParam(self, id):
		ret=True
		try:
			self.session.query(SQL.HighDrillingSiteParam).filter(SQL.HighDrillingSiteParam.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateHighDrillingSiteParam(self, high_drilling_site_param):
		ret=True
		try:
			sql_obj = SQL.HighDrillingSiteParam()
			CbmUtil.CopyAttribsOfCbmType("HighDrillingSiteParam", high_drilling_site_param, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("HighDrillingSiteParam", sql_obj)
			del attribs['id']
			self.session.query(SQL.HighDrillingSiteParam).filter(SQL.HighDrillingSiteParam.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetHighDrillingSiteParamById(self, id):
		query=self.session.query(SQL.HighDrillingSiteParam).filter(SQL.HighDrillingSiteParam.id==id).first()
		obj = HighDrillingSiteParam()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("HighDrillingSiteParam", query, obj, True)
		return obj
	def GetHighDrillingSiteParamByForeignKey(self, fkey, id):
		return self.GetHighDrillingSiteParamByFields({fkey:id})
	def GetHighDrillingSiteParamIdByForeignKey(self, fkey, id):
		return self.GetHighDrillingSiteParamIdByFields({fkey:id})
	def GetHighDrillingSiteParamList(self):
		query = self.session.query(SQL.HighDrillingSiteParam).order_by(SQL.HighDrillingSiteParam.id).all()
		n = len(query)
		obj_list = [HighDrillingSiteParam() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingSiteParam", query[i], obj_list[i], True)
		return obj_list
	def GetHighDrillingSiteParamIds(self):
		query=self.session.query(SQL.HighDrillingSiteParam).order_by(SQL.HighDrillingSiteParam.id).all()
		return [obj.id for obj in query]
	def GetHighDrillingSiteParamNames(self):
		query=self.session.query(SQL.HighDrillingSiteParam).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreHighDrillingSiteParam(self, objs):
		n = len(objs)
		sql_objs = [SQL.HighDrillingSiteParam() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingSiteParam", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreHighDrillingSiteParam(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.HighDrillingSiteParam).filter(SQL.HighDrillingSiteParam.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetHighDrillingSiteParamByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingSiteParam", fields)
		query = self.session.query(SQL.HighDrillingSiteParam).filter_by(**sql_fields).order_by(SQL.HighDrillingSiteParam.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [HighDrillingSiteParam() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("HighDrillingSiteParam", query[i], obj_list[i], True)
			return obj_list
	def __GetHighDrillingSiteParamIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingSiteParam", fields)
		query = self.session.query(SQL.HighDrillingSiteParam).filter_by(**sql_fields).order_by(SQL.HighDrillingSiteParam.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetHighDrillingSiteParamByFields(self, fields):
		objs = self.__GetHighDrillingSiteParamByFields(fields)
		if len(objs) == 0:
			obj = HighDrillingSiteParam()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetHighDrillingSiteParamByField1(self, field, value):
		return self.GetHighDrillingSiteParamByFields({field:value})
	def GetHighDrillingSiteParamByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingSiteParamByFields({field1:value1, field2:value2})
	def GetHighDrillingSiteParamListByFields(self, fields):
		return self.__GetHighDrillingSiteParamByFields(fields)
	def GetHighDrillingSiteParamListByField1(self, field, value):
		return self.GetHighDrillingSiteParamListByFields({field:value})
	def GetHighDrillingSiteParamListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingSiteParamListByFields({field1:value1, field2:value2})
	def GetHighDrillingSiteParamIdByFields(self, fields):
		obj_ids = self.__GetHighDrillingSiteParamIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetHighDrillingSiteParamIdByField1(self, field, value):
		return self.GetHighDrillingSiteParamIdByFields({field:value})
	def GetHighDrillingSiteParamIdByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingSiteParamIdByFields({field1:value1, field2:value2})
	def GetHighDrillingSiteParamIdListByFields(self, fields):
		return self.__GetHighDrillingSiteParamIdsByFields(fields)
	def GetHighDrillingSiteParamIdListByField1(self, field, value):
		return self.GetHighDrillingSiteParamIdListByFields({field:value})
	def GetHighDrillingSiteParamIdListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingSiteParamIdListByFields({field1:value1, field2:value2})
	def GetHighDrillingSiteParamListByForeignKey(self, fkey, id):
		return self.GetHighDrillingSiteParamListByFields({fkey:id})
	def GetHighDrillingSiteParamIdListByForeignKey(self, fkey, id):
		return self.GetHighDrillingSiteParamIdListByFields({fkey:id})

	#HighDrillingTunnel 类型的CRUD操作
	def AddHighDrillingTunnel(self, high_drilling_tunnel):
		sql_obj = SQL.HighDrillingTunnel()
		CbmUtil.CopyAttribsOfCbmType("HighDrillingTunnel", high_drilling_tunnel, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteHighDrillingTunnel(self, id):
		ret=True
		try:
			self.session.query(SQL.HighDrillingTunnel).filter(SQL.HighDrillingTunnel.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateHighDrillingTunnel(self, high_drilling_tunnel):
		ret=True
		try:
			sql_obj = SQL.HighDrillingTunnel()
			CbmUtil.CopyAttribsOfCbmType("HighDrillingTunnel", high_drilling_tunnel, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("HighDrillingTunnel", sql_obj)
			del attribs['id']
			self.session.query(SQL.HighDrillingTunnel).filter(SQL.HighDrillingTunnel.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetHighDrillingTunnelById(self, id):
		query=self.session.query(SQL.HighDrillingTunnel).filter(SQL.HighDrillingTunnel.id==id).first()
		obj = HighDrillingTunnel()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("HighDrillingTunnel", query, obj, True)
		return obj
	def GetHighDrillingTunnelByForeignKey(self, fkey, id):
		return self.GetHighDrillingTunnelByFields({fkey:id})
	def GetHighDrillingTunnelIdByForeignKey(self, fkey, id):
		return self.GetHighDrillingTunnelIdByFields({fkey:id})
	def GetHighDrillingTunnelList(self):
		query = self.session.query(SQL.HighDrillingTunnel).order_by(SQL.HighDrillingTunnel.id).all()
		n = len(query)
		obj_list = [HighDrillingTunnel() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingTunnel", query[i], obj_list[i], True)
		return obj_list
	def GetHighDrillingTunnelIds(self):
		query=self.session.query(SQL.HighDrillingTunnel).order_by(SQL.HighDrillingTunnel.id).all()
		return [obj.id for obj in query]
	def GetHighDrillingTunnelNames(self):
		query=self.session.query(SQL.HighDrillingTunnel).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreHighDrillingTunnel(self, objs):
		n = len(objs)
		sql_objs = [SQL.HighDrillingTunnel() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HighDrillingTunnel", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreHighDrillingTunnel(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.HighDrillingTunnel).filter(SQL.HighDrillingTunnel.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetHighDrillingTunnelByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingTunnel", fields)
		query = self.session.query(SQL.HighDrillingTunnel).filter_by(**sql_fields).order_by(SQL.HighDrillingTunnel.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [HighDrillingTunnel() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("HighDrillingTunnel", query[i], obj_list[i], True)
			return obj_list
	def __GetHighDrillingTunnelIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HighDrillingTunnel", fields)
		query = self.session.query(SQL.HighDrillingTunnel).filter_by(**sql_fields).order_by(SQL.HighDrillingTunnel.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetHighDrillingTunnelByFields(self, fields):
		objs = self.__GetHighDrillingTunnelByFields(fields)
		if len(objs) == 0:
			obj = HighDrillingTunnel()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetHighDrillingTunnelByField1(self, field, value):
		return self.GetHighDrillingTunnelByFields({field:value})
	def GetHighDrillingTunnelByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingTunnelByFields({field1:value1, field2:value2})
	def GetHighDrillingTunnelListByFields(self, fields):
		return self.__GetHighDrillingTunnelByFields(fields)
	def GetHighDrillingTunnelListByField1(self, field, value):
		return self.GetHighDrillingTunnelListByFields({field:value})
	def GetHighDrillingTunnelListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingTunnelListByFields({field1:value1, field2:value2})
	def GetHighDrillingTunnelIdByFields(self, fields):
		obj_ids = self.__GetHighDrillingTunnelIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetHighDrillingTunnelIdByField1(self, field, value):
		return self.GetHighDrillingTunnelIdByFields({field:value})
	def GetHighDrillingTunnelIdByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingTunnelIdByFields({field1:value1, field2:value2})
	def GetHighDrillingTunnelIdListByFields(self, fields):
		return self.__GetHighDrillingTunnelIdsByFields(fields)
	def GetHighDrillingTunnelIdListByField1(self, field, value):
		return self.GetHighDrillingTunnelIdListByFields({field:value})
	def GetHighDrillingTunnelIdListByField2(self, field1, value1, field2, value2):
		return self.GetHighDrillingTunnelIdListByFields({field1:value1, field2:value2})
	def GetHighDrillingTunnelListByForeignKey(self, fkey, id):
		return self.GetHighDrillingTunnelListByFields({fkey:id})
	def GetHighDrillingTunnelIdListByForeignKey(self, fkey, id):
		return self.GetHighDrillingTunnelIdListByFields({fkey:id})

	#HydrGeo 类型的CRUD操作
	def AddHydrGeo(self, hydr_geo):
		sql_obj = SQL.HydrGeo()
		CbmUtil.CopyAttribsOfCbmType("HydrGeo", hydr_geo, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteHydrGeo(self, id):
		ret=True
		try:
			self.session.query(SQL.HydrGeo).filter(SQL.HydrGeo.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateHydrGeo(self, hydr_geo):
		ret=True
		try:
			sql_obj = SQL.HydrGeo()
			CbmUtil.CopyAttribsOfCbmType("HydrGeo", hydr_geo, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("HydrGeo", sql_obj)
			del attribs['id']
			self.session.query(SQL.HydrGeo).filter(SQL.HydrGeo.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetHydrGeoById(self, id):
		query=self.session.query(SQL.HydrGeo).filter(SQL.HydrGeo.id==id).first()
		obj = HydrGeo()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("HydrGeo", query, obj, True)
		return obj
	def GetHydrGeoByForeignKey(self, fkey, id):
		return self.GetHydrGeoByFields({fkey:id})
	def GetHydrGeoIdByForeignKey(self, fkey, id):
		return self.GetHydrGeoIdByFields({fkey:id})
	def GetHydrGeoList(self):
		query = self.session.query(SQL.HydrGeo).order_by(SQL.HydrGeo.id).all()
		n = len(query)
		obj_list = [HydrGeo() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HydrGeo", query[i], obj_list[i], True)
		return obj_list
	def GetHydrGeoIds(self):
		query=self.session.query(SQL.HydrGeo).order_by(SQL.HydrGeo.id).all()
		return [obj.id for obj in query]
	def GetHydrGeoNames(self):
		query=self.session.query(SQL.HydrGeo).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreHydrGeo(self, objs):
		n = len(objs)
		sql_objs = [SQL.HydrGeo() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("HydrGeo", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreHydrGeo(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.HydrGeo).filter(SQL.HydrGeo.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetHydrGeoByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HydrGeo", fields)
		query = self.session.query(SQL.HydrGeo).filter_by(**sql_fields).order_by(SQL.HydrGeo.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [HydrGeo() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("HydrGeo", query[i], obj_list[i], True)
			return obj_list
	def __GetHydrGeoIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("HydrGeo", fields)
		query = self.session.query(SQL.HydrGeo).filter_by(**sql_fields).order_by(SQL.HydrGeo.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetHydrGeoByFields(self, fields):
		objs = self.__GetHydrGeoByFields(fields)
		if len(objs) == 0:
			obj = HydrGeo()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetHydrGeoByField1(self, field, value):
		return self.GetHydrGeoByFields({field:value})
	def GetHydrGeoByField2(self, field1, value1, field2, value2):
		return self.GetHydrGeoByFields({field1:value1, field2:value2})
	def GetHydrGeoListByFields(self, fields):
		return self.__GetHydrGeoByFields(fields)
	def GetHydrGeoListByField1(self, field, value):
		return self.GetHydrGeoListByFields({field:value})
	def GetHydrGeoListByField2(self, field1, value1, field2, value2):
		return self.GetHydrGeoListByFields({field1:value1, field2:value2})
	def GetHydrGeoIdByFields(self, fields):
		obj_ids = self.__GetHydrGeoIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetHydrGeoIdByField1(self, field, value):
		return self.GetHydrGeoIdByFields({field:value})
	def GetHydrGeoIdByField2(self, field1, value1, field2, value2):
		return self.GetHydrGeoIdByFields({field1:value1, field2:value2})
	def GetHydrGeoIdListByFields(self, fields):
		return self.__GetHydrGeoIdsByFields(fields)
	def GetHydrGeoIdListByField1(self, field, value):
		return self.GetHydrGeoIdListByFields({field:value})
	def GetHydrGeoIdListByField2(self, field1, value1, field2, value2):
		return self.GetHydrGeoIdListByFields({field1:value1, field2:value2})
	def GetHydrGeoListByForeignKey(self, fkey, id):
		return self.GetHydrGeoListByFields({fkey:id})
	def GetHydrGeoIdListByForeignKey(self, fkey, id):
		return self.GetHydrGeoIdListByFields({fkey:id})

	#Mine 类型的CRUD操作
	def AddMine(self, mine):
		sql_obj = SQL.Mine()
		CbmUtil.CopyAttribsOfCbmType("Mine", mine, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteMine(self, id):
		ret=True
		try:
			self.session.query(SQL.Mine).filter(SQL.Mine.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateMine(self, mine):
		ret=True
		try:
			sql_obj = SQL.Mine()
			CbmUtil.CopyAttribsOfCbmType("Mine", mine, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("Mine", sql_obj)
			del attribs['id']
			self.session.query(SQL.Mine).filter(SQL.Mine.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetMineById(self, id):
		query=self.session.query(SQL.Mine).filter(SQL.Mine.id==id).first()
		obj = Mine()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("Mine", query, obj, True)
		return obj
	def GetMineByForeignKey(self, fkey, id):
		return self.GetMineByFields({fkey:id})
	def GetMineIdByForeignKey(self, fkey, id):
		return self.GetMineIdByFields({fkey:id})
	def GetMineList(self):
		query = self.session.query(SQL.Mine).order_by(SQL.Mine.id).all()
		n = len(query)
		obj_list = [Mine() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Mine", query[i], obj_list[i], True)
		return obj_list
	def GetMineIds(self):
		query=self.session.query(SQL.Mine).order_by(SQL.Mine.id).all()
		return [obj.id for obj in query]
	def GetMineNames(self):
		query=self.session.query(SQL.Mine).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreMine(self, objs):
		n = len(objs)
		sql_objs = [SQL.Mine() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Mine", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreMine(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.Mine).filter(SQL.Mine.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetMineByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Mine", fields)
		query = self.session.query(SQL.Mine).filter_by(**sql_fields).order_by(SQL.Mine.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [Mine() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("Mine", query[i], obj_list[i], True)
			return obj_list
	def __GetMineIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Mine", fields)
		query = self.session.query(SQL.Mine).filter_by(**sql_fields).order_by(SQL.Mine.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetMineByFields(self, fields):
		objs = self.__GetMineByFields(fields)
		if len(objs) == 0:
			obj = Mine()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetMineByField1(self, field, value):
		return self.GetMineByFields({field:value})
	def GetMineByField2(self, field1, value1, field2, value2):
		return self.GetMineByFields({field1:value1, field2:value2})
	def GetMineListByFields(self, fields):
		return self.__GetMineByFields(fields)
	def GetMineListByField1(self, field, value):
		return self.GetMineListByFields({field:value})
	def GetMineListByField2(self, field1, value1, field2, value2):
		return self.GetMineListByFields({field1:value1, field2:value2})
	def GetMineIdByFields(self, fields):
		obj_ids = self.__GetMineIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetMineIdByField1(self, field, value):
		return self.GetMineIdByFields({field:value})
	def GetMineIdByField2(self, field1, value1, field2, value2):
		return self.GetMineIdByFields({field1:value1, field2:value2})
	def GetMineIdListByFields(self, fields):
		return self.__GetMineIdsByFields(fields)
	def GetMineIdListByField1(self, field, value):
		return self.GetMineIdListByFields({field:value})
	def GetMineIdListByField2(self, field1, value1, field2, value2):
		return self.GetMineIdListByFields({field1:value1, field2:value2})
	def GetMineListByForeignKey(self, fkey, id):
		return self.GetMineListByFields({fkey:id})
	def GetMineIdListByForeignKey(self, fkey, id):
		return self.GetMineIdListByFields({fkey:id})

	#MineBase 类型的CRUD操作
	def AddMineBase(self, mine_base):
		sql_obj = SQL.MineBase()
		CbmUtil.CopyAttribsOfCbmType("MineBase", mine_base, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteMineBase(self, id):
		ret=True
		try:
			self.session.query(SQL.MineBase).filter(SQL.MineBase.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateMineBase(self, mine_base):
		ret=True
		try:
			sql_obj = SQL.MineBase()
			CbmUtil.CopyAttribsOfCbmType("MineBase", mine_base, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("MineBase", sql_obj)
			del attribs['id']
			self.session.query(SQL.MineBase).filter(SQL.MineBase.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetMineBaseById(self, id):
		query=self.session.query(SQL.MineBase).filter(SQL.MineBase.id==id).first()
		obj = MineBase()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("MineBase", query, obj, True)
		return obj
	def GetMineBaseByForeignKey(self, fkey, id):
		return self.GetMineBaseByFields({fkey:id})
	def GetMineBaseIdByForeignKey(self, fkey, id):
		return self.GetMineBaseIdByFields({fkey:id})
	def GetMineBaseList(self):
		query = self.session.query(SQL.MineBase).order_by(SQL.MineBase.id).all()
		n = len(query)
		obj_list = [MineBase() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("MineBase", query[i], obj_list[i], True)
		return obj_list
	def GetMineBaseIds(self):
		query=self.session.query(SQL.MineBase).order_by(SQL.MineBase.id).all()
		return [obj.id for obj in query]
	def GetMineBaseNames(self):
		query=self.session.query(SQL.MineBase).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreMineBase(self, objs):
		n = len(objs)
		sql_objs = [SQL.MineBase() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("MineBase", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreMineBase(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.MineBase).filter(SQL.MineBase.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetMineBaseByFields(self, fields):
		sql_fields = CbmUtil.map_fields("MineBase", fields)
		query = self.session.query(SQL.MineBase).filter_by(**sql_fields).order_by(SQL.MineBase.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [MineBase() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("MineBase", query[i], obj_list[i], True)
			return obj_list
	def __GetMineBaseIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("MineBase", fields)
		query = self.session.query(SQL.MineBase).filter_by(**sql_fields).order_by(SQL.MineBase.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetMineBaseByFields(self, fields):
		objs = self.__GetMineBaseByFields(fields)
		if len(objs) == 0:
			obj = MineBase()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetMineBaseByField1(self, field, value):
		return self.GetMineBaseByFields({field:value})
	def GetMineBaseByField2(self, field1, value1, field2, value2):
		return self.GetMineBaseByFields({field1:value1, field2:value2})
	def GetMineBaseListByFields(self, fields):
		return self.__GetMineBaseByFields(fields)
	def GetMineBaseListByField1(self, field, value):
		return self.GetMineBaseListByFields({field:value})
	def GetMineBaseListByField2(self, field1, value1, field2, value2):
		return self.GetMineBaseListByFields({field1:value1, field2:value2})
	def GetMineBaseIdByFields(self, fields):
		obj_ids = self.__GetMineBaseIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetMineBaseIdByField1(self, field, value):
		return self.GetMineBaseIdByFields({field:value})
	def GetMineBaseIdByField2(self, field1, value1, field2, value2):
		return self.GetMineBaseIdByFields({field1:value1, field2:value2})
	def GetMineBaseIdListByFields(self, fields):
		return self.__GetMineBaseIdsByFields(fields)
	def GetMineBaseIdListByField1(self, field, value):
		return self.GetMineBaseIdListByFields({field:value})
	def GetMineBaseIdListByField2(self, field1, value1, field2, value2):
		return self.GetMineBaseIdListByFields({field1:value1, field2:value2})
	def GetMineBaseListByForeignKey(self, fkey, id):
		return self.GetMineBaseListByFields({fkey:id})
	def GetMineBaseIdListByForeignKey(self, fkey, id):
		return self.GetMineBaseIdListByFields({fkey:id})

	#MineRegion 类型的CRUD操作
	def AddMineRegion(self, mine_region):
		sql_obj = SQL.MineRegion()
		CbmUtil.CopyAttribsOfCbmType("MineRegion", mine_region, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteMineRegion(self, id):
		ret=True
		try:
			self.session.query(SQL.MineRegion).filter(SQL.MineRegion.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateMineRegion(self, mine_region):
		ret=True
		try:
			sql_obj = SQL.MineRegion()
			CbmUtil.CopyAttribsOfCbmType("MineRegion", mine_region, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("MineRegion", sql_obj)
			del attribs['id']
			self.session.query(SQL.MineRegion).filter(SQL.MineRegion.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetMineRegionById(self, id):
		query=self.session.query(SQL.MineRegion).filter(SQL.MineRegion.id==id).first()
		obj = MineRegion()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("MineRegion", query, obj, True)
		return obj
	def GetMineRegionByForeignKey(self, fkey, id):
		return self.GetMineRegionByFields({fkey:id})
	def GetMineRegionIdByForeignKey(self, fkey, id):
		return self.GetMineRegionIdByFields({fkey:id})
	def GetMineRegionList(self):
		query = self.session.query(SQL.MineRegion).order_by(SQL.MineRegion.id).all()
		n = len(query)
		obj_list = [MineRegion() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("MineRegion", query[i], obj_list[i], True)
		return obj_list
	def GetMineRegionIds(self):
		query=self.session.query(SQL.MineRegion).order_by(SQL.MineRegion.id).all()
		return [obj.id for obj in query]
	def GetMineRegionNames(self):
		query=self.session.query(SQL.MineRegion).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreMineRegion(self, objs):
		n = len(objs)
		sql_objs = [SQL.MineRegion() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("MineRegion", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreMineRegion(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.MineRegion).filter(SQL.MineRegion.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetMineRegionByFields(self, fields):
		sql_fields = CbmUtil.map_fields("MineRegion", fields)
		query = self.session.query(SQL.MineRegion).filter_by(**sql_fields).order_by(SQL.MineRegion.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [MineRegion() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("MineRegion", query[i], obj_list[i], True)
			return obj_list
	def __GetMineRegionIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("MineRegion", fields)
		query = self.session.query(SQL.MineRegion).filter_by(**sql_fields).order_by(SQL.MineRegion.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetMineRegionByFields(self, fields):
		objs = self.__GetMineRegionByFields(fields)
		if len(objs) == 0:
			obj = MineRegion()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetMineRegionByField1(self, field, value):
		return self.GetMineRegionByFields({field:value})
	def GetMineRegionByField2(self, field1, value1, field2, value2):
		return self.GetMineRegionByFields({field1:value1, field2:value2})
	def GetMineRegionListByFields(self, fields):
		return self.__GetMineRegionByFields(fields)
	def GetMineRegionListByField1(self, field, value):
		return self.GetMineRegionListByFields({field:value})
	def GetMineRegionListByField2(self, field1, value1, field2, value2):
		return self.GetMineRegionListByFields({field1:value1, field2:value2})
	def GetMineRegionIdByFields(self, fields):
		obj_ids = self.__GetMineRegionIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetMineRegionIdByField1(self, field, value):
		return self.GetMineRegionIdByFields({field:value})
	def GetMineRegionIdByField2(self, field1, value1, field2, value2):
		return self.GetMineRegionIdByFields({field1:value1, field2:value2})
	def GetMineRegionIdListByFields(self, fields):
		return self.__GetMineRegionIdsByFields(fields)
	def GetMineRegionIdListByField1(self, field, value):
		return self.GetMineRegionIdListByFields({field:value})
	def GetMineRegionIdListByField2(self, field1, value1, field2, value2):
		return self.GetMineRegionIdListByFields({field1:value1, field2:value2})
	def GetMineRegionListByForeignKey(self, fkey, id):
		return self.GetMineRegionListByFields({fkey:id})
	def GetMineRegionIdListByForeignKey(self, fkey, id):
		return self.GetMineRegionIdListByFields({fkey:id})

	#PoreFlow 类型的CRUD操作
	def AddPoreFlow(self, pore_flow):
		sql_obj = SQL.PoreFlow()
		CbmUtil.CopyAttribsOfCbmType("PoreFlow", pore_flow, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeletePoreFlow(self, id):
		ret=True
		try:
			self.session.query(SQL.PoreFlow).filter(SQL.PoreFlow.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdatePoreFlow(self, pore_flow):
		ret=True
		try:
			sql_obj = SQL.PoreFlow()
			CbmUtil.CopyAttribsOfCbmType("PoreFlow", pore_flow, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("PoreFlow", sql_obj)
			del attribs['id']
			self.session.query(SQL.PoreFlow).filter(SQL.PoreFlow.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetPoreFlowById(self, id):
		query=self.session.query(SQL.PoreFlow).filter(SQL.PoreFlow.id==id).first()
		obj = PoreFlow()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("PoreFlow", query, obj, True)
		return obj
	def GetPoreFlowByForeignKey(self, fkey, id):
		return self.GetPoreFlowByFields({fkey:id})
	def GetPoreFlowIdByForeignKey(self, fkey, id):
		return self.GetPoreFlowIdByFields({fkey:id})
	def GetPoreFlowList(self):
		query = self.session.query(SQL.PoreFlow).order_by(SQL.PoreFlow.id).all()
		n = len(query)
		obj_list = [PoreFlow() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("PoreFlow", query[i], obj_list[i], True)
		return obj_list
	def GetPoreFlowIds(self):
		query=self.session.query(SQL.PoreFlow).order_by(SQL.PoreFlow.id).all()
		return [obj.id for obj in query]
	def GetPoreFlowNames(self):
		query=self.session.query(SQL.PoreFlow).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMorePoreFlow(self, objs):
		n = len(objs)
		sql_objs = [SQL.PoreFlow() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("PoreFlow", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMorePoreFlow(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.PoreFlow).filter(SQL.PoreFlow.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetPoreFlowByFields(self, fields):
		sql_fields = CbmUtil.map_fields("PoreFlow", fields)
		query = self.session.query(SQL.PoreFlow).filter_by(**sql_fields).order_by(SQL.PoreFlow.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [PoreFlow() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("PoreFlow", query[i], obj_list[i], True)
			return obj_list
	def __GetPoreFlowIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("PoreFlow", fields)
		query = self.session.query(SQL.PoreFlow).filter_by(**sql_fields).order_by(SQL.PoreFlow.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetPoreFlowByFields(self, fields):
		objs = self.__GetPoreFlowByFields(fields)
		if len(objs) == 0:
			obj = PoreFlow()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetPoreFlowByField1(self, field, value):
		return self.GetPoreFlowByFields({field:value})
	def GetPoreFlowByField2(self, field1, value1, field2, value2):
		return self.GetPoreFlowByFields({field1:value1, field2:value2})
	def GetPoreFlowListByFields(self, fields):
		return self.__GetPoreFlowByFields(fields)
	def GetPoreFlowListByField1(self, field, value):
		return self.GetPoreFlowListByFields({field:value})
	def GetPoreFlowListByField2(self, field1, value1, field2, value2):
		return self.GetPoreFlowListByFields({field1:value1, field2:value2})
	def GetPoreFlowIdByFields(self, fields):
		obj_ids = self.__GetPoreFlowIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetPoreFlowIdByField1(self, field, value):
		return self.GetPoreFlowIdByFields({field:value})
	def GetPoreFlowIdByField2(self, field1, value1, field2, value2):
		return self.GetPoreFlowIdByFields({field1:value1, field2:value2})
	def GetPoreFlowIdListByFields(self, fields):
		return self.__GetPoreFlowIdsByFields(fields)
	def GetPoreFlowIdListByField1(self, field, value):
		return self.GetPoreFlowIdListByFields({field:value})
	def GetPoreFlowIdListByField2(self, field1, value1, field2, value2):
		return self.GetPoreFlowIdListByFields({field1:value1, field2:value2})
	def GetPoreFlowListByForeignKey(self, fkey, id):
		return self.GetPoreFlowListByFields({fkey:id})
	def GetPoreFlowIdListByForeignKey(self, fkey, id):
		return self.GetPoreFlowIdListByFields({fkey:id})

	#PoreSize 类型的CRUD操作
	def AddPoreSize(self, pore_size):
		sql_obj = SQL.PoreSize()
		CbmUtil.CopyAttribsOfCbmType("PoreSize", pore_size, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeletePoreSize(self, id):
		ret=True
		try:
			self.session.query(SQL.PoreSize).filter(SQL.PoreSize.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdatePoreSize(self, pore_size):
		ret=True
		try:
			sql_obj = SQL.PoreSize()
			CbmUtil.CopyAttribsOfCbmType("PoreSize", pore_size, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("PoreSize", sql_obj)
			del attribs['id']
			self.session.query(SQL.PoreSize).filter(SQL.PoreSize.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetPoreSizeById(self, id):
		query=self.session.query(SQL.PoreSize).filter(SQL.PoreSize.id==id).first()
		obj = PoreSize()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("PoreSize", query, obj, True)
		return obj
	def GetPoreSizeByForeignKey(self, fkey, id):
		return self.GetPoreSizeByFields({fkey:id})
	def GetPoreSizeIdByForeignKey(self, fkey, id):
		return self.GetPoreSizeIdByFields({fkey:id})
	def GetPoreSizeList(self):
		query = self.session.query(SQL.PoreSize).order_by(SQL.PoreSize.id).all()
		n = len(query)
		obj_list = [PoreSize() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("PoreSize", query[i], obj_list[i], True)
		return obj_list
	def GetPoreSizeIds(self):
		query=self.session.query(SQL.PoreSize).order_by(SQL.PoreSize.id).all()
		return [obj.id for obj in query]
	def GetPoreSizeNames(self):
		query=self.session.query(SQL.PoreSize).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMorePoreSize(self, objs):
		n = len(objs)
		sql_objs = [SQL.PoreSize() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("PoreSize", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMorePoreSize(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.PoreSize).filter(SQL.PoreSize.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetPoreSizeByFields(self, fields):
		sql_fields = CbmUtil.map_fields("PoreSize", fields)
		query = self.session.query(SQL.PoreSize).filter_by(**sql_fields).order_by(SQL.PoreSize.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [PoreSize() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("PoreSize", query[i], obj_list[i], True)
			return obj_list
	def __GetPoreSizeIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("PoreSize", fields)
		query = self.session.query(SQL.PoreSize).filter_by(**sql_fields).order_by(SQL.PoreSize.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetPoreSizeByFields(self, fields):
		objs = self.__GetPoreSizeByFields(fields)
		if len(objs) == 0:
			obj = PoreSize()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetPoreSizeByField1(self, field, value):
		return self.GetPoreSizeByFields({field:value})
	def GetPoreSizeByField2(self, field1, value1, field2, value2):
		return self.GetPoreSizeByFields({field1:value1, field2:value2})
	def GetPoreSizeListByFields(self, fields):
		return self.__GetPoreSizeByFields(fields)
	def GetPoreSizeListByField1(self, field, value):
		return self.GetPoreSizeListByFields({field:value})
	def GetPoreSizeListByField2(self, field1, value1, field2, value2):
		return self.GetPoreSizeListByFields({field1:value1, field2:value2})
	def GetPoreSizeIdByFields(self, fields):
		obj_ids = self.__GetPoreSizeIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetPoreSizeIdByField1(self, field, value):
		return self.GetPoreSizeIdByFields({field:value})
	def GetPoreSizeIdByField2(self, field1, value1, field2, value2):
		return self.GetPoreSizeIdByFields({field1:value1, field2:value2})
	def GetPoreSizeIdListByFields(self, fields):
		return self.__GetPoreSizeIdsByFields(fields)
	def GetPoreSizeIdListByField1(self, field, value):
		return self.GetPoreSizeIdListByFields({field:value})
	def GetPoreSizeIdListByField2(self, field1, value1, field2, value2):
		return self.GetPoreSizeIdListByFields({field1:value1, field2:value2})
	def GetPoreSizeListByForeignKey(self, fkey, id):
		return self.GetPoreSizeListByFields({fkey:id})
	def GetPoreSizeIdListByForeignKey(self, fkey, id):
		return self.GetPoreSizeIdListByFields({fkey:id})

	#ResAbundance 类型的CRUD操作
	def AddResAbundance(self, res_abundance):
		sql_obj = SQL.ResAbundance()
		CbmUtil.CopyAttribsOfCbmType("ResAbundance", res_abundance, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteResAbundance(self, id):
		ret=True
		try:
			self.session.query(SQL.ResAbundance).filter(SQL.ResAbundance.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateResAbundance(self, res_abundance):
		ret=True
		try:
			sql_obj = SQL.ResAbundance()
			CbmUtil.CopyAttribsOfCbmType("ResAbundance", res_abundance, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("ResAbundance", sql_obj)
			del attribs['id']
			self.session.query(SQL.ResAbundance).filter(SQL.ResAbundance.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetResAbundanceById(self, id):
		query=self.session.query(SQL.ResAbundance).filter(SQL.ResAbundance.id==id).first()
		obj = ResAbundance()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("ResAbundance", query, obj, True)
		return obj
	def GetResAbundanceByForeignKey(self, fkey, id):
		return self.GetResAbundanceByFields({fkey:id})
	def GetResAbundanceIdByForeignKey(self, fkey, id):
		return self.GetResAbundanceIdByFields({fkey:id})
	def GetResAbundanceList(self):
		query = self.session.query(SQL.ResAbundance).order_by(SQL.ResAbundance.id).all()
		n = len(query)
		obj_list = [ResAbundance() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("ResAbundance", query[i], obj_list[i], True)
		return obj_list
	def GetResAbundanceIds(self):
		query=self.session.query(SQL.ResAbundance).order_by(SQL.ResAbundance.id).all()
		return [obj.id for obj in query]
	def GetResAbundanceNames(self):
		query=self.session.query(SQL.ResAbundance).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreResAbundance(self, objs):
		n = len(objs)
		sql_objs = [SQL.ResAbundance() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("ResAbundance", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreResAbundance(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.ResAbundance).filter(SQL.ResAbundance.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetResAbundanceByFields(self, fields):
		sql_fields = CbmUtil.map_fields("ResAbundance", fields)
		query = self.session.query(SQL.ResAbundance).filter_by(**sql_fields).order_by(SQL.ResAbundance.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [ResAbundance() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("ResAbundance", query[i], obj_list[i], True)
			return obj_list
	def __GetResAbundanceIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("ResAbundance", fields)
		query = self.session.query(SQL.ResAbundance).filter_by(**sql_fields).order_by(SQL.ResAbundance.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetResAbundanceByFields(self, fields):
		objs = self.__GetResAbundanceByFields(fields)
		if len(objs) == 0:
			obj = ResAbundance()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetResAbundanceByField1(self, field, value):
		return self.GetResAbundanceByFields({field:value})
	def GetResAbundanceByField2(self, field1, value1, field2, value2):
		return self.GetResAbundanceByFields({field1:value1, field2:value2})
	def GetResAbundanceListByFields(self, fields):
		return self.__GetResAbundanceByFields(fields)
	def GetResAbundanceListByField1(self, field, value):
		return self.GetResAbundanceListByFields({field:value})
	def GetResAbundanceListByField2(self, field1, value1, field2, value2):
		return self.GetResAbundanceListByFields({field1:value1, field2:value2})
	def GetResAbundanceIdByFields(self, fields):
		obj_ids = self.__GetResAbundanceIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetResAbundanceIdByField1(self, field, value):
		return self.GetResAbundanceIdByFields({field:value})
	def GetResAbundanceIdByField2(self, field1, value1, field2, value2):
		return self.GetResAbundanceIdByFields({field1:value1, field2:value2})
	def GetResAbundanceIdListByFields(self, fields):
		return self.__GetResAbundanceIdsByFields(fields)
	def GetResAbundanceIdListByField1(self, field, value):
		return self.GetResAbundanceIdListByFields({field:value})
	def GetResAbundanceIdListByField2(self, field1, value1, field2, value2):
		return self.GetResAbundanceIdListByFields({field1:value1, field2:value2})
	def GetResAbundanceListByForeignKey(self, fkey, id):
		return self.GetResAbundanceListByFields({fkey:id})
	def GetResAbundanceIdListByForeignKey(self, fkey, id):
		return self.GetResAbundanceIdListByFields({fkey:id})

	#Rock 类型的CRUD操作
	def AddRock(self, rock):
		sql_obj = SQL.Rock()
		CbmUtil.CopyAttribsOfCbmType("Rock", rock, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteRock(self, id):
		ret=True
		try:
			self.session.query(SQL.Rock).filter(SQL.Rock.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateRock(self, rock):
		ret=True
		try:
			sql_obj = SQL.Rock()
			CbmUtil.CopyAttribsOfCbmType("Rock", rock, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("Rock", sql_obj)
			del attribs['id']
			self.session.query(SQL.Rock).filter(SQL.Rock.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetRockById(self, id):
		query=self.session.query(SQL.Rock).filter(SQL.Rock.id==id).first()
		obj = Rock()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("Rock", query, obj, True)
		return obj
	def GetRockByForeignKey(self, fkey, id):
		return self.GetRockByFields({fkey:id})
	def GetRockIdByForeignKey(self, fkey, id):
		return self.GetRockIdByFields({fkey:id})
	def GetRockList(self):
		query = self.session.query(SQL.Rock).order_by(SQL.Rock.id).all()
		n = len(query)
		obj_list = [Rock() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Rock", query[i], obj_list[i], True)
		return obj_list
	def GetRockIds(self):
		query=self.session.query(SQL.Rock).order_by(SQL.Rock.id).all()
		return [obj.id for obj in query]
	def GetRockNames(self):
		query=self.session.query(SQL.Rock).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreRock(self, objs):
		n = len(objs)
		sql_objs = [SQL.Rock() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Rock", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreRock(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.Rock).filter(SQL.Rock.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetRockByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Rock", fields)
		query = self.session.query(SQL.Rock).filter_by(**sql_fields).order_by(SQL.Rock.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [Rock() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("Rock", query[i], obj_list[i], True)
			return obj_list
	def __GetRockIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Rock", fields)
		query = self.session.query(SQL.Rock).filter_by(**sql_fields).order_by(SQL.Rock.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetRockByFields(self, fields):
		objs = self.__GetRockByFields(fields)
		if len(objs) == 0:
			obj = Rock()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetRockByField1(self, field, value):
		return self.GetRockByFields({field:value})
	def GetRockByField2(self, field1, value1, field2, value2):
		return self.GetRockByFields({field1:value1, field2:value2})
	def GetRockListByFields(self, fields):
		return self.__GetRockByFields(fields)
	def GetRockListByField1(self, field, value):
		return self.GetRockListByFields({field:value})
	def GetRockListByField2(self, field1, value1, field2, value2):
		return self.GetRockListByFields({field1:value1, field2:value2})
	def GetRockIdByFields(self, fields):
		obj_ids = self.__GetRockIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetRockIdByField1(self, field, value):
		return self.GetRockIdByFields({field:value})
	def GetRockIdByField2(self, field1, value1, field2, value2):
		return self.GetRockIdByFields({field1:value1, field2:value2})
	def GetRockIdListByFields(self, fields):
		return self.__GetRockIdsByFields(fields)
	def GetRockIdListByField1(self, field, value):
		return self.GetRockIdListByFields({field:value})
	def GetRockIdListByField2(self, field1, value1, field2, value2):
		return self.GetRockIdListByFields({field1:value1, field2:value2})
	def GetRockListByForeignKey(self, fkey, id):
		return self.GetRockListByFields({fkey:id})
	def GetRockIdListByForeignKey(self, fkey, id):
		return self.GetRockIdListByFields({fkey:id})

	#SysInfo 类型的CRUD操作
	def AddSysInfo(self, sys_info):
		sql_obj = SQL.SysInfo()
		CbmUtil.CopyAttribsOfCbmType("SysInfo", sys_info, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteSysInfo(self, id):
		ret=True
		try:
			self.session.query(SQL.SysInfo).filter(SQL.SysInfo.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateSysInfo(self, sys_info):
		ret=True
		try:
			sql_obj = SQL.SysInfo()
			CbmUtil.CopyAttribsOfCbmType("SysInfo", sys_info, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("SysInfo", sql_obj)
			del attribs['id']
			self.session.query(SQL.SysInfo).filter(SQL.SysInfo.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetSysInfoById(self, id):
		query=self.session.query(SQL.SysInfo).filter(SQL.SysInfo.id==id).first()
		obj = SysInfo()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("SysInfo", query, obj, True)
		return obj
	def GetSysInfoByForeignKey(self, fkey, id):
		return self.GetSysInfoByFields({fkey:id})
	def GetSysInfoIdByForeignKey(self, fkey, id):
		return self.GetSysInfoIdByFields({fkey:id})
	def GetSysInfoList(self):
		query = self.session.query(SQL.SysInfo).order_by(SQL.SysInfo.id).all()
		n = len(query)
		obj_list = [SysInfo() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("SysInfo", query[i], obj_list[i], True)
		return obj_list
	def GetSysInfoIds(self):
		query=self.session.query(SQL.SysInfo).order_by(SQL.SysInfo.id).all()
		return [obj.id for obj in query]
	def GetSysInfoNames(self):
		query=self.session.query(SQL.SysInfo).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreSysInfo(self, objs):
		n = len(objs)
		sql_objs = [SQL.SysInfo() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("SysInfo", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreSysInfo(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.SysInfo).filter(SQL.SysInfo.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetSysInfoByFields(self, fields):
		sql_fields = CbmUtil.map_fields("SysInfo", fields)
		query = self.session.query(SQL.SysInfo).filter_by(**sql_fields).order_by(SQL.SysInfo.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [SysInfo() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("SysInfo", query[i], obj_list[i], True)
			return obj_list
	def __GetSysInfoIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("SysInfo", fields)
		query = self.session.query(SQL.SysInfo).filter_by(**sql_fields).order_by(SQL.SysInfo.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetSysInfoByFields(self, fields):
		objs = self.__GetSysInfoByFields(fields)
		if len(objs) == 0:
			obj = SysInfo()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetSysInfoByField1(self, field, value):
		return self.GetSysInfoByFields({field:value})
	def GetSysInfoByField2(self, field1, value1, field2, value2):
		return self.GetSysInfoByFields({field1:value1, field2:value2})
	def GetSysInfoListByFields(self, fields):
		return self.__GetSysInfoByFields(fields)
	def GetSysInfoListByField1(self, field, value):
		return self.GetSysInfoListByFields({field:value})
	def GetSysInfoListByField2(self, field1, value1, field2, value2):
		return self.GetSysInfoListByFields({field1:value1, field2:value2})
	def GetSysInfoIdByFields(self, fields):
		obj_ids = self.__GetSysInfoIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetSysInfoIdByField1(self, field, value):
		return self.GetSysInfoIdByFields({field:value})
	def GetSysInfoIdByField2(self, field1, value1, field2, value2):
		return self.GetSysInfoIdByFields({field1:value1, field2:value2})
	def GetSysInfoIdListByFields(self, fields):
		return self.__GetSysInfoIdsByFields(fields)
	def GetSysInfoIdListByField1(self, field, value):
		return self.GetSysInfoIdListByFields({field:value})
	def GetSysInfoIdListByField2(self, field1, value1, field2, value2):
		return self.GetSysInfoIdListByFields({field1:value1, field2:value2})
	def GetSysInfoListByForeignKey(self, fkey, id):
		return self.GetSysInfoListByFields({fkey:id})
	def GetSysInfoIdListByForeignKey(self, fkey, id):
		return self.GetSysInfoIdListByFields({fkey:id})

	#TechMode 类型的CRUD操作
	def AddTechMode(self, tech_mode):
		sql_obj = SQL.TechMode()
		CbmUtil.CopyAttribsOfCbmType("TechMode", tech_mode, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteTechMode(self, id):
		ret=True
		try:
			self.session.query(SQL.TechMode).filter(SQL.TechMode.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateTechMode(self, tech_mode):
		ret=True
		try:
			sql_obj = SQL.TechMode()
			CbmUtil.CopyAttribsOfCbmType("TechMode", tech_mode, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("TechMode", sql_obj)
			del attribs['id']
			self.session.query(SQL.TechMode).filter(SQL.TechMode.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetTechModeById(self, id):
		query=self.session.query(SQL.TechMode).filter(SQL.TechMode.id==id).first()
		obj = TechMode()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("TechMode", query, obj, True)
		return obj
	def GetTechModeByForeignKey(self, fkey, id):
		return self.GetTechModeByFields({fkey:id})
	def GetTechModeIdByForeignKey(self, fkey, id):
		return self.GetTechModeIdByFields({fkey:id})
	def GetTechModeList(self):
		query = self.session.query(SQL.TechMode).order_by(SQL.TechMode.id).all()
		n = len(query)
		obj_list = [TechMode() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("TechMode", query[i], obj_list[i], True)
		return obj_list
	def GetTechModeIds(self):
		query=self.session.query(SQL.TechMode).order_by(SQL.TechMode.id).all()
		return [obj.id for obj in query]
	def GetTechModeNames(self):
		query=self.session.query(SQL.TechMode).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreTechMode(self, objs):
		n = len(objs)
		sql_objs = [SQL.TechMode() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("TechMode", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreTechMode(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.TechMode).filter(SQL.TechMode.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetTechModeByFields(self, fields):
		sql_fields = CbmUtil.map_fields("TechMode", fields)
		query = self.session.query(SQL.TechMode).filter_by(**sql_fields).order_by(SQL.TechMode.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [TechMode() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("TechMode", query[i], obj_list[i], True)
			return obj_list
	def __GetTechModeIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("TechMode", fields)
		query = self.session.query(SQL.TechMode).filter_by(**sql_fields).order_by(SQL.TechMode.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetTechModeByFields(self, fields):
		objs = self.__GetTechModeByFields(fields)
		if len(objs) == 0:
			obj = TechMode()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetTechModeByField1(self, field, value):
		return self.GetTechModeByFields({field:value})
	def GetTechModeByField2(self, field1, value1, field2, value2):
		return self.GetTechModeByFields({field1:value1, field2:value2})
	def GetTechModeListByFields(self, fields):
		return self.__GetTechModeByFields(fields)
	def GetTechModeListByField1(self, field, value):
		return self.GetTechModeListByFields({field:value})
	def GetTechModeListByField2(self, field1, value1, field2, value2):
		return self.GetTechModeListByFields({field1:value1, field2:value2})
	def GetTechModeIdByFields(self, fields):
		obj_ids = self.__GetTechModeIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetTechModeIdByField1(self, field, value):
		return self.GetTechModeIdByFields({field:value})
	def GetTechModeIdByField2(self, field1, value1, field2, value2):
		return self.GetTechModeIdByFields({field1:value1, field2:value2})
	def GetTechModeIdListByFields(self, fields):
		return self.__GetTechModeIdsByFields(fields)
	def GetTechModeIdListByField1(self, field, value):
		return self.GetTechModeIdListByFields({field:value})
	def GetTechModeIdListByField2(self, field1, value1, field2, value2):
		return self.GetTechModeIdListByFields({field1:value1, field2:value2})
	def GetTechModeListByForeignKey(self, fkey, id):
		return self.GetTechModeListByFields({fkey:id})
	def GetTechModeIdListByForeignKey(self, fkey, id):
		return self.GetTechModeIdListByFields({fkey:id})

	#Technology 类型的CRUD操作
	def AddTechnology(self, technology):
		sql_obj = SQL.Technology()
		CbmUtil.CopyAttribsOfCbmType("Technology", technology, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteTechnology(self, id):
		ret=True
		try:
			self.session.query(SQL.Technology).filter(SQL.Technology.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateTechnology(self, technology):
		ret=True
		try:
			sql_obj = SQL.Technology()
			CbmUtil.CopyAttribsOfCbmType("Technology", technology, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("Technology", sql_obj)
			del attribs['id']
			self.session.query(SQL.Technology).filter(SQL.Technology.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetTechnologyById(self, id):
		query=self.session.query(SQL.Technology).filter(SQL.Technology.id==id).first()
		obj = Technology()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("Technology", query, obj, True)
		return obj
	def GetTechnologyByForeignKey(self, fkey, id):
		return self.GetTechnologyByFields({fkey:id})
	def GetTechnologyIdByForeignKey(self, fkey, id):
		return self.GetTechnologyIdByFields({fkey:id})
	def GetTechnologyList(self):
		query = self.session.query(SQL.Technology).order_by(SQL.Technology.id).all()
		n = len(query)
		obj_list = [Technology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Technology", query[i], obj_list[i], True)
		return obj_list
	def GetTechnologyIds(self):
		query=self.session.query(SQL.Technology).order_by(SQL.Technology.id).all()
		return [obj.id for obj in query]
	def GetTechnologyNames(self):
		query=self.session.query(SQL.Technology).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreTechnology(self, objs):
		n = len(objs)
		sql_objs = [SQL.Technology() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Technology", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreTechnology(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.Technology).filter(SQL.Technology.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetTechnologyByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Technology", fields)
		query = self.session.query(SQL.Technology).filter_by(**sql_fields).order_by(SQL.Technology.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [Technology() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("Technology", query[i], obj_list[i], True)
			return obj_list
	def __GetTechnologyIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Technology", fields)
		query = self.session.query(SQL.Technology).filter_by(**sql_fields).order_by(SQL.Technology.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetTechnologyByFields(self, fields):
		objs = self.__GetTechnologyByFields(fields)
		if len(objs) == 0:
			obj = Technology()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetTechnologyByField1(self, field, value):
		return self.GetTechnologyByFields({field:value})
	def GetTechnologyByField2(self, field1, value1, field2, value2):
		return self.GetTechnologyByFields({field1:value1, field2:value2})
	def GetTechnologyListByFields(self, fields):
		return self.__GetTechnologyByFields(fields)
	def GetTechnologyListByField1(self, field, value):
		return self.GetTechnologyListByFields({field:value})
	def GetTechnologyListByField2(self, field1, value1, field2, value2):
		return self.GetTechnologyListByFields({field1:value1, field2:value2})
	def GetTechnologyIdByFields(self, fields):
		obj_ids = self.__GetTechnologyIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetTechnologyIdByField1(self, field, value):
		return self.GetTechnologyIdByFields({field:value})
	def GetTechnologyIdByField2(self, field1, value1, field2, value2):
		return self.GetTechnologyIdByFields({field1:value1, field2:value2})
	def GetTechnologyIdListByFields(self, fields):
		return self.__GetTechnologyIdsByFields(fields)
	def GetTechnologyIdListByField1(self, field, value):
		return self.GetTechnologyIdListByFields({field:value})
	def GetTechnologyIdListByField2(self, field1, value1, field2, value2):
		return self.GetTechnologyIdListByFields({field1:value1, field2:value2})
	def GetTechnologyListByForeignKey(self, fkey, id):
		return self.GetTechnologyListByFields({fkey:id})
	def GetTechnologyIdListByForeignKey(self, fkey, id):
		return self.GetTechnologyIdListByFields({fkey:id})

	#TopoGeo 类型的CRUD操作
	def AddTopoGeo(self, topo_geo):
		sql_obj = SQL.TopoGeo()
		CbmUtil.CopyAttribsOfCbmType("TopoGeo", topo_geo, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteTopoGeo(self, id):
		ret=True
		try:
			self.session.query(SQL.TopoGeo).filter(SQL.TopoGeo.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateTopoGeo(self, topo_geo):
		ret=True
		try:
			sql_obj = SQL.TopoGeo()
			CbmUtil.CopyAttribsOfCbmType("TopoGeo", topo_geo, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("TopoGeo", sql_obj)
			del attribs['id']
			self.session.query(SQL.TopoGeo).filter(SQL.TopoGeo.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetTopoGeoById(self, id):
		query=self.session.query(SQL.TopoGeo).filter(SQL.TopoGeo.id==id).first()
		obj = TopoGeo()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("TopoGeo", query, obj, True)
		return obj
	def GetTopoGeoByForeignKey(self, fkey, id):
		return self.GetTopoGeoByFields({fkey:id})
	def GetTopoGeoIdByForeignKey(self, fkey, id):
		return self.GetTopoGeoIdByFields({fkey:id})
	def GetTopoGeoList(self):
		query = self.session.query(SQL.TopoGeo).order_by(SQL.TopoGeo.id).all()
		n = len(query)
		obj_list = [TopoGeo() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("TopoGeo", query[i], obj_list[i], True)
		return obj_list
	def GetTopoGeoIds(self):
		query=self.session.query(SQL.TopoGeo).order_by(SQL.TopoGeo.id).all()
		return [obj.id for obj in query]
	def GetTopoGeoNames(self):
		query=self.session.query(SQL.TopoGeo).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreTopoGeo(self, objs):
		n = len(objs)
		sql_objs = [SQL.TopoGeo() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("TopoGeo", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreTopoGeo(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.TopoGeo).filter(SQL.TopoGeo.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetTopoGeoByFields(self, fields):
		sql_fields = CbmUtil.map_fields("TopoGeo", fields)
		query = self.session.query(SQL.TopoGeo).filter_by(**sql_fields).order_by(SQL.TopoGeo.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [TopoGeo() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("TopoGeo", query[i], obj_list[i], True)
			return obj_list
	def __GetTopoGeoIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("TopoGeo", fields)
		query = self.session.query(SQL.TopoGeo).filter_by(**sql_fields).order_by(SQL.TopoGeo.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetTopoGeoByFields(self, fields):
		objs = self.__GetTopoGeoByFields(fields)
		if len(objs) == 0:
			obj = TopoGeo()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetTopoGeoByField1(self, field, value):
		return self.GetTopoGeoByFields({field:value})
	def GetTopoGeoByField2(self, field1, value1, field2, value2):
		return self.GetTopoGeoByFields({field1:value1, field2:value2})
	def GetTopoGeoListByFields(self, fields):
		return self.__GetTopoGeoByFields(fields)
	def GetTopoGeoListByField1(self, field, value):
		return self.GetTopoGeoListByFields({field:value})
	def GetTopoGeoListByField2(self, field1, value1, field2, value2):
		return self.GetTopoGeoListByFields({field1:value1, field2:value2})
	def GetTopoGeoIdByFields(self, fields):
		obj_ids = self.__GetTopoGeoIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetTopoGeoIdByField1(self, field, value):
		return self.GetTopoGeoIdByFields({field:value})
	def GetTopoGeoIdByField2(self, field1, value1, field2, value2):
		return self.GetTopoGeoIdByFields({field1:value1, field2:value2})
	def GetTopoGeoIdListByFields(self, fields):
		return self.__GetTopoGeoIdsByFields(fields)
	def GetTopoGeoIdListByField1(self, field, value):
		return self.GetTopoGeoIdListByFields({field:value})
	def GetTopoGeoIdListByField2(self, field1, value1, field2, value2):
		return self.GetTopoGeoIdListByFields({field1:value1, field2:value2})
	def GetTopoGeoListByForeignKey(self, fkey, id):
		return self.GetTopoGeoListByFields({fkey:id})
	def GetTopoGeoIdListByForeignKey(self, fkey, id):
		return self.GetTopoGeoIdListByFields({fkey:id})

	#Tunnel 类型的CRUD操作
	def AddTunnel(self, tunnel):
		sql_obj = SQL.Tunnel()
		CbmUtil.CopyAttribsOfCbmType("Tunnel", tunnel, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteTunnel(self, id):
		ret=True
		try:
			self.session.query(SQL.Tunnel).filter(SQL.Tunnel.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateTunnel(self, tunnel):
		ret=True
		try:
			sql_obj = SQL.Tunnel()
			CbmUtil.CopyAttribsOfCbmType("Tunnel", tunnel, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("Tunnel", sql_obj)
			del attribs['id']
			self.session.query(SQL.Tunnel).filter(SQL.Tunnel.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetTunnelById(self, id):
		query=self.session.query(SQL.Tunnel).filter(SQL.Tunnel.id==id).first()
		obj = Tunnel()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("Tunnel", query, obj, True)
		return obj
	def GetTunnelByForeignKey(self, fkey, id):
		return self.GetTunnelByFields({fkey:id})
	def GetTunnelIdByForeignKey(self, fkey, id):
		return self.GetTunnelIdByFields({fkey:id})
	def GetTunnelList(self):
		query = self.session.query(SQL.Tunnel).order_by(SQL.Tunnel.id).all()
		n = len(query)
		obj_list = [Tunnel() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Tunnel", query[i], obj_list[i], True)
		return obj_list
	def GetTunnelIds(self):
		query=self.session.query(SQL.Tunnel).order_by(SQL.Tunnel.id).all()
		return [obj.id for obj in query]
	def GetTunnelNames(self):
		query=self.session.query(SQL.Tunnel).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreTunnel(self, objs):
		n = len(objs)
		sql_objs = [SQL.Tunnel() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("Tunnel", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreTunnel(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.Tunnel).filter(SQL.Tunnel.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetTunnelByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Tunnel", fields)
		query = self.session.query(SQL.Tunnel).filter_by(**sql_fields).order_by(SQL.Tunnel.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [Tunnel() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("Tunnel", query[i], obj_list[i], True)
			return obj_list
	def __GetTunnelIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("Tunnel", fields)
		query = self.session.query(SQL.Tunnel).filter_by(**sql_fields).order_by(SQL.Tunnel.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetTunnelByFields(self, fields):
		objs = self.__GetTunnelByFields(fields)
		if len(objs) == 0:
			obj = Tunnel()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetTunnelByField1(self, field, value):
		return self.GetTunnelByFields({field:value})
	def GetTunnelByField2(self, field1, value1, field2, value2):
		return self.GetTunnelByFields({field1:value1, field2:value2})
	def GetTunnelListByFields(self, fields):
		return self.__GetTunnelByFields(fields)
	def GetTunnelListByField1(self, field, value):
		return self.GetTunnelListByFields({field:value})
	def GetTunnelListByField2(self, field1, value1, field2, value2):
		return self.GetTunnelListByFields({field1:value1, field2:value2})
	def GetTunnelIdByFields(self, fields):
		obj_ids = self.__GetTunnelIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetTunnelIdByField1(self, field, value):
		return self.GetTunnelIdByFields({field:value})
	def GetTunnelIdByField2(self, field1, value1, field2, value2):
		return self.GetTunnelIdByFields({field1:value1, field2:value2})
	def GetTunnelIdListByFields(self, fields):
		return self.__GetTunnelIdsByFields(fields)
	def GetTunnelIdListByField1(self, field, value):
		return self.GetTunnelIdListByFields({field:value})
	def GetTunnelIdListByField2(self, field1, value1, field2, value2):
		return self.GetTunnelIdListByFields({field1:value1, field2:value2})
	def GetTunnelListByForeignKey(self, fkey, id):
		return self.GetTunnelListByFields({fkey:id})
	def GetTunnelIdListByForeignKey(self, fkey, id):
		return self.GetTunnelIdListByFields({fkey:id})

	#WorkArea 类型的CRUD操作
	def AddWorkArea(self, work_area):
		sql_obj = SQL.WorkArea()
		CbmUtil.CopyAttribsOfCbmType("WorkArea", work_area, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteWorkArea(self, id):
		ret=True
		try:
			self.session.query(SQL.WorkArea).filter(SQL.WorkArea.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateWorkArea(self, work_area):
		ret=True
		try:
			sql_obj = SQL.WorkArea()
			CbmUtil.CopyAttribsOfCbmType("WorkArea", work_area, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("WorkArea", sql_obj)
			del attribs['id']
			self.session.query(SQL.WorkArea).filter(SQL.WorkArea.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetWorkAreaById(self, id):
		query=self.session.query(SQL.WorkArea).filter(SQL.WorkArea.id==id).first()
		obj = WorkArea()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("WorkArea", query, obj, True)
		return obj
	def GetWorkAreaByForeignKey(self, fkey, id):
		return self.GetWorkAreaByFields({fkey:id})
	def GetWorkAreaIdByForeignKey(self, fkey, id):
		return self.GetWorkAreaIdByFields({fkey:id})
	def GetWorkAreaList(self):
		query = self.session.query(SQL.WorkArea).order_by(SQL.WorkArea.id).all()
		n = len(query)
		obj_list = [WorkArea() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("WorkArea", query[i], obj_list[i], True)
		return obj_list
	def GetWorkAreaIds(self):
		query=self.session.query(SQL.WorkArea).order_by(SQL.WorkArea.id).all()
		return [obj.id for obj in query]
	def GetWorkAreaNames(self):
		query=self.session.query(SQL.WorkArea).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreWorkArea(self, objs):
		n = len(objs)
		sql_objs = [SQL.WorkArea() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("WorkArea", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreWorkArea(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.WorkArea).filter(SQL.WorkArea.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetWorkAreaByFields(self, fields):
		sql_fields = CbmUtil.map_fields("WorkArea", fields)
		query = self.session.query(SQL.WorkArea).filter_by(**sql_fields).order_by(SQL.WorkArea.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [WorkArea() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("WorkArea", query[i], obj_list[i], True)
			return obj_list
	def __GetWorkAreaIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("WorkArea", fields)
		query = self.session.query(SQL.WorkArea).filter_by(**sql_fields).order_by(SQL.WorkArea.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetWorkAreaByFields(self, fields):
		objs = self.__GetWorkAreaByFields(fields)
		if len(objs) == 0:
			obj = WorkArea()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetWorkAreaByField1(self, field, value):
		return self.GetWorkAreaByFields({field:value})
	def GetWorkAreaByField2(self, field1, value1, field2, value2):
		return self.GetWorkAreaByFields({field1:value1, field2:value2})
	def GetWorkAreaListByFields(self, fields):
		return self.__GetWorkAreaByFields(fields)
	def GetWorkAreaListByField1(self, field, value):
		return self.GetWorkAreaListByFields({field:value})
	def GetWorkAreaListByField2(self, field1, value1, field2, value2):
		return self.GetWorkAreaListByFields({field1:value1, field2:value2})
	def GetWorkAreaIdByFields(self, fields):
		obj_ids = self.__GetWorkAreaIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetWorkAreaIdByField1(self, field, value):
		return self.GetWorkAreaIdByFields({field:value})
	def GetWorkAreaIdByField2(self, field1, value1, field2, value2):
		return self.GetWorkAreaIdByFields({field1:value1, field2:value2})
	def GetWorkAreaIdListByFields(self, fields):
		return self.__GetWorkAreaIdsByFields(fields)
	def GetWorkAreaIdListByField1(self, field, value):
		return self.GetWorkAreaIdListByFields({field:value})
	def GetWorkAreaIdListByField2(self, field1, value1, field2, value2):
		return self.GetWorkAreaIdListByFields({field1:value1, field2:value2})
	def GetWorkAreaListByForeignKey(self, fkey, id):
		return self.GetWorkAreaListByFields({fkey:id})
	def GetWorkAreaIdListByForeignKey(self, fkey, id):
		return self.GetWorkAreaIdListByFields({fkey:id})

	#WorkSurf 类型的CRUD操作
	def AddWorkSurf(self, work_surf):
		sql_obj = SQL.WorkSurf()
		CbmUtil.CopyAttribsOfCbmType("WorkSurf", work_surf, sql_obj, False)
		sql_obj.id = None
		self.session.add(sql_obj)
		self.session.flush()
		self.session.commit()
		return sql_obj.id
	def DeleteWorkSurf(self, id):
		ret=True
		try:
			self.session.query(SQL.WorkSurf).filter(SQL.WorkSurf.id==id).delete(synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def UpdateWorkSurf(self, work_surf):
		ret=True
		try:
			sql_obj = SQL.WorkSurf()
			CbmUtil.CopyAttribsOfCbmType("WorkSurf", work_surf, sql_obj, False)
			attribs = CbmUtil.GetAttribsOfCbmType("WorkSurf", sql_obj)
			del attribs['id']
			self.session.query(SQL.WorkSurf).filter(SQL.WorkSurf.id==sql_obj.id).update(attribs, synchronize_session=False)
			self.session.commit()
		except Exception, e:
			print e
			ret=False
		return ret
	def GetWorkSurfById(self, id):
		query=self.session.query(SQL.WorkSurf).filter(SQL.WorkSurf.id==id).first()
		obj = WorkSurf()
		if query is None:
			obj.id = -1
		else:
			CbmUtil.CopyAttribsOfCbmType("WorkSurf", query, obj, True)
		return obj
	def GetWorkSurfByForeignKey(self, fkey, id):
		return self.GetWorkSurfByFields({fkey:id})
	def GetWorkSurfIdByForeignKey(self, fkey, id):
		return self.GetWorkSurfIdByFields({fkey:id})
	def GetWorkSurfList(self):
		query = self.session.query(SQL.WorkSurf).order_by(SQL.WorkSurf.id).all()
		n = len(query)
		obj_list = [WorkSurf() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("WorkSurf", query[i], obj_list[i], True)
		return obj_list
	def GetWorkSurfIds(self):
		query=self.session.query(SQL.WorkSurf).order_by(SQL.WorkSurf.id).all()
		return [obj.id for obj in query]
	def GetWorkSurfNames(self):
		query=self.session.query(SQL.WorkSurf).all()
		if len(query) == 0 or not hasattr(query[0], 'name'):
			return []
		else:
			return [obj.name for obj in query]
	def AddMoreWorkSurf(self, objs):
		n = len(objs)
		sql_objs = [SQL.WorkSurf() for i in range(n)]
		for i in range(n):
			CbmUtil.CopyAttribsOfCbmType("WorkSurf", objs[i], sql_objs[i], False)
			sql_objs[i].id = None
			self.session.add(sql_objs[i])
		self.session.flush()
		self.session.commit()
	def DeleteMoreWorkSurf(self, obj_ids):
		if len(obj_ids) == 0:return
		self.session.query(SQL.WorkSurf).filter(SQL.WorkSurf.id.in_(obj_ids)).delete(synchronize_session=False)
		self.session.commit()
	def __GetWorkSurfByFields(self, fields):
		sql_fields = CbmUtil.map_fields("WorkSurf", fields)
		query = self.session.query(SQL.WorkSurf).filter_by(**sql_fields).order_by(SQL.WorkSurf.id).all()
		if len(query) == 0:
			return []
		else:
			n = len(query)
			obj_list = [WorkSurf() for i in range(n)]
			for i in range(n):
				CbmUtil.CopyAttribsOfCbmType("WorkSurf", query[i], obj_list[i], True)
			return obj_list
	def __GetWorkSurfIdsByFields(self, fields):
		sql_fields = CbmUtil.map_fields("WorkSurf", fields)
		query = self.session.query(SQL.WorkSurf).filter_by(**sql_fields).order_by(SQL.WorkSurf.id).all()
		if len(query) == 0:
			return []
		else:
			return [obj.id for obj in query]
	def GetWorkSurfByFields(self, fields):
		objs = self.__GetWorkSurfByFields(fields)
		if len(objs) == 0:
			obj = WorkSurf()
			obj.id = -1
			return obj
		else:
			return objs[0]
	def GetWorkSurfByField1(self, field, value):
		return self.GetWorkSurfByFields({field:value})
	def GetWorkSurfByField2(self, field1, value1, field2, value2):
		return self.GetWorkSurfByFields({field1:value1, field2:value2})
	def GetWorkSurfListByFields(self, fields):
		return self.__GetWorkSurfByFields(fields)
	def GetWorkSurfListByField1(self, field, value):
		return self.GetWorkSurfListByFields({field:value})
	def GetWorkSurfListByField2(self, field1, value1, field2, value2):
		return self.GetWorkSurfListByFields({field1:value1, field2:value2})
	def GetWorkSurfIdByFields(self, fields):
		obj_ids = self.__GetWorkSurfIdsByFields(fields)
		if len(obj_ids) == 0:
			return -1
		else:
			return obj_ids[0]
	def GetWorkSurfIdByField1(self, field, value):
		return self.GetWorkSurfIdByFields({field:value})
	def GetWorkSurfIdByField2(self, field1, value1, field2, value2):
		return self.GetWorkSurfIdByFields({field1:value1, field2:value2})
	def GetWorkSurfIdListByFields(self, fields):
		return self.__GetWorkSurfIdsByFields(fields)
	def GetWorkSurfIdListByField1(self, field, value):
		return self.GetWorkSurfIdListByFields({field:value})
	def GetWorkSurfIdListByField2(self, field1, value1, field2, value2):
		return self.GetWorkSurfIdListByFields({field1:value1, field2:value2})
	def GetWorkSurfListByForeignKey(self, fkey, id):
		return self.GetWorkSurfListByFields({fkey:id})
	def GetWorkSurfIdListByForeignKey(self, fkey, id):
		return self.GetWorkSurfIdListByFields({fkey:id})

