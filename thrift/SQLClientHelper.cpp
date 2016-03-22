#include "stdafx.h"
#include "SQLClientHelper.h"
//Account 类型的CRUD操作
int32_t SQLClientHelper::AddAccount(const cbm::Account & account) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddAccount(account);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteAccount(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteAccount(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateAccount(const cbm::Account & account) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateAccount(account);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetAccountById(cbm::Account & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountByForeignKey(cbm::Account & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetAccountIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAccountIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetAccountList(std::vector<cbm::Account> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreAccount(const std::vector<cbm::Account> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreAccount(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreAccount(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreAccount(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountByFields(cbm::Account & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountByField1(cbm::Account & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountByField2(cbm::Account & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountListByFields(std::vector<cbm::Account> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountListByField1(std::vector<cbm::Account> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountListByField2(std::vector<cbm::Account> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetAccountIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAccountIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetAccountIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAccountIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetAccountIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAccountIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetAccountIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountListByForeignKey(std::vector<cbm::Account> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAccountIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAccountIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//AdjLayer 类型的CRUD操作
int32_t SQLClientHelper::AddAdjLayer(const cbm::AdjLayer & adj_layer) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddAdjLayer(adj_layer);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteAdjLayer(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteAdjLayer(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateAdjLayer(const cbm::AdjLayer & adj_layer) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateAdjLayer(adj_layer);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetAdjLayerById(cbm::AdjLayer & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerByForeignKey(cbm::AdjLayer & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetAdjLayerIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAdjLayerIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetAdjLayerList(std::vector<cbm::AdjLayer> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreAdjLayer(const std::vector<cbm::AdjLayer> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreAdjLayer(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreAdjLayer(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreAdjLayer(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerByFields(cbm::AdjLayer & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerByField1(cbm::AdjLayer & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerByField2(cbm::AdjLayer & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerListByFields(std::vector<cbm::AdjLayer> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerListByField1(std::vector<cbm::AdjLayer> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerListByField2(std::vector<cbm::AdjLayer> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetAdjLayerIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAdjLayerIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetAdjLayerIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAdjLayerIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetAdjLayerIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetAdjLayerIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetAdjLayerIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerListByForeignKey(std::vector<cbm::AdjLayer> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetAdjLayerIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetAdjLayerIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//Coal 类型的CRUD操作
int32_t SQLClientHelper::AddCoal(const cbm::Coal & coal) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddCoal(coal);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteCoal(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteCoal(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateCoal(const cbm::Coal & coal) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateCoal(coal);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetCoalById(cbm::Coal & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalByForeignKey(cbm::Coal & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetCoalIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetCoalIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetCoalList(std::vector<cbm::Coal> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreCoal(const std::vector<cbm::Coal> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreCoal(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreCoal(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreCoal(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalByFields(cbm::Coal & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalByField1(cbm::Coal & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalByField2(cbm::Coal & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalListByFields(std::vector<cbm::Coal> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalListByField1(std::vector<cbm::Coal> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalListByField2(std::vector<cbm::Coal> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetCoalIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetCoalIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetCoalIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetCoalIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetCoalIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetCoalIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetCoalIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalListByForeignKey(std::vector<cbm::Coal> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetCoalIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetCoalIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//Complexity 类型的CRUD操作
int32_t SQLClientHelper::AddComplexity(const cbm::Complexity & complexity) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddComplexity(complexity);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteComplexity(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteComplexity(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateComplexity(const cbm::Complexity & complexity) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateComplexity(complexity);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetComplexityById(cbm::Complexity & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityByForeignKey(cbm::Complexity & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetComplexityIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetComplexityIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetComplexityList(std::vector<cbm::Complexity> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreComplexity(const std::vector<cbm::Complexity> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreComplexity(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreComplexity(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreComplexity(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityByFields(cbm::Complexity & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityByField1(cbm::Complexity & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityByField2(cbm::Complexity & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityListByFields(std::vector<cbm::Complexity> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityListByField1(std::vector<cbm::Complexity> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityListByField2(std::vector<cbm::Complexity> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetComplexityIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetComplexityIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetComplexityIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetComplexityIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetComplexityIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetComplexityIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetComplexityIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityListByForeignKey(std::vector<cbm::Complexity> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetComplexityIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetComplexityIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignDrillingSurfTechnology 类型的CRUD操作
int32_t SQLClientHelper::AddDesignDrillingSurfTechnology(const cbm::DesignDrillingSurfTechnology & design_drilling_surf_technology) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignDrillingSurfTechnology(design_drilling_surf_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignDrillingSurfTechnology(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignDrillingSurfTechnology(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignDrillingSurfTechnology(const cbm::DesignDrillingSurfTechnology & design_drilling_surf_technology) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignDrillingSurfTechnology(design_drilling_surf_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyById(cbm::DesignDrillingSurfTechnology & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyByForeignKey(cbm::DesignDrillingSurfTechnology & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignDrillingSurfTechnologyIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignDrillingSurfTechnologyIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyList(std::vector<cbm::DesignDrillingSurfTechnology> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignDrillingSurfTechnology(const std::vector<cbm::DesignDrillingSurfTechnology> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignDrillingSurfTechnology(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignDrillingSurfTechnology(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignDrillingSurfTechnology(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyByFields(cbm::DesignDrillingSurfTechnology & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyByField1(cbm::DesignDrillingSurfTechnology & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyByField2(cbm::DesignDrillingSurfTechnology & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyListByFields(std::vector<cbm::DesignDrillingSurfTechnology> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyListByField1(std::vector<cbm::DesignDrillingSurfTechnology> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyListByField2(std::vector<cbm::DesignDrillingSurfTechnology> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignDrillingSurfTechnologyIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignDrillingSurfTechnologyIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignDrillingSurfTechnologyIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignDrillingSurfTechnologyIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignDrillingSurfTechnologyIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignDrillingSurfTechnologyIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyListByForeignKey(std::vector<cbm::DesignDrillingSurfTechnology> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignDrillingSurfTechnologyIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignDrillingSurfTechnologyIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignEvalUnit 类型的CRUD操作
int32_t SQLClientHelper::AddDesignEvalUnit(const cbm::DesignEvalUnit & design_eval_unit) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignEvalUnit(design_eval_unit);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignEvalUnit(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignEvalUnit(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignEvalUnit(const cbm::DesignEvalUnit & design_eval_unit) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignEvalUnit(design_eval_unit);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignEvalUnitById(cbm::DesignEvalUnit & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitByForeignKey(cbm::DesignEvalUnit & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignEvalUnitIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignEvalUnitList(std::vector<cbm::DesignEvalUnit> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignEvalUnit(const std::vector<cbm::DesignEvalUnit> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignEvalUnit(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignEvalUnit(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignEvalUnit(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitByFields(cbm::DesignEvalUnit & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitByField1(cbm::DesignEvalUnit & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitByField2(cbm::DesignEvalUnit & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitListByFields(std::vector<cbm::DesignEvalUnit> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitListByField1(std::vector<cbm::DesignEvalUnit> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitListByField2(std::vector<cbm::DesignEvalUnit> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignEvalUnitIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignEvalUnitIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignEvalUnitIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignEvalUnitIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitListByForeignKey(std::vector<cbm::DesignEvalUnit> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignEvalUnitPartition 类型的CRUD操作
int32_t SQLClientHelper::AddDesignEvalUnitPartition(const cbm::DesignEvalUnitPartition & design_eval_unit_partition) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignEvalUnitPartition(design_eval_unit_partition);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignEvalUnitPartition(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignEvalUnitPartition(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignEvalUnitPartition(const cbm::DesignEvalUnitPartition & design_eval_unit_partition) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignEvalUnitPartition(design_eval_unit_partition);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignEvalUnitPartitionById(cbm::DesignEvalUnitPartition & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionByForeignKey(cbm::DesignEvalUnitPartition & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignEvalUnitPartitionIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitPartitionIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignEvalUnitPartitionList(std::vector<cbm::DesignEvalUnitPartition> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignEvalUnitPartition(const std::vector<cbm::DesignEvalUnitPartition> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignEvalUnitPartition(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignEvalUnitPartition(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignEvalUnitPartition(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionByFields(cbm::DesignEvalUnitPartition & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionByField1(cbm::DesignEvalUnitPartition & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionByField2(cbm::DesignEvalUnitPartition & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionListByFields(std::vector<cbm::DesignEvalUnitPartition> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionListByField1(std::vector<cbm::DesignEvalUnitPartition> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionListByField2(std::vector<cbm::DesignEvalUnitPartition> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignEvalUnitPartitionIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitPartitionIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignEvalUnitPartitionIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitPartitionIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignEvalUnitPartitionIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignEvalUnitPartitionIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignEvalUnitPartitionIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionListByForeignKey(std::vector<cbm::DesignEvalUnitPartition> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignEvalUnitPartitionIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignEvalUnitPartitionIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignGoafPore 类型的CRUD操作
int32_t SQLClientHelper::AddDesignGoafPore(const cbm::DesignGoafPore & design_goaf_pore) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignGoafPore(design_goaf_pore);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignGoafPore(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignGoafPore(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignGoafPore(const cbm::DesignGoafPore & design_goaf_pore) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignGoafPore(design_goaf_pore);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignGoafPoreById(cbm::DesignGoafPore & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreByForeignKey(cbm::DesignGoafPore & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignGoafPoreIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafPoreIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignGoafPoreList(std::vector<cbm::DesignGoafPore> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignGoafPore(const std::vector<cbm::DesignGoafPore> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignGoafPore(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignGoafPore(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignGoafPore(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreByFields(cbm::DesignGoafPore & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreByField1(cbm::DesignGoafPore & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreByField2(cbm::DesignGoafPore & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreListByFields(std::vector<cbm::DesignGoafPore> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreListByField1(std::vector<cbm::DesignGoafPore> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreListByField2(std::vector<cbm::DesignGoafPore> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignGoafPoreIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafPoreIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignGoafPoreIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafPoreIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignGoafPoreIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafPoreIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignGoafPoreIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreListByForeignKey(std::vector<cbm::DesignGoafPore> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafPoreIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafPoreIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignGoafTechnology 类型的CRUD操作
int32_t SQLClientHelper::AddDesignGoafTechnology(const cbm::DesignGoafTechnology & design_goaf_technology) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignGoafTechnology(design_goaf_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignGoafTechnology(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignGoafTechnology(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignGoafTechnology(const cbm::DesignGoafTechnology & design_goaf_technology) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignGoafTechnology(design_goaf_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignGoafTechnologyById(cbm::DesignGoafTechnology & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyByForeignKey(cbm::DesignGoafTechnology & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignGoafTechnologyIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafTechnologyIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignGoafTechnologyList(std::vector<cbm::DesignGoafTechnology> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignGoafTechnology(const std::vector<cbm::DesignGoafTechnology> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignGoafTechnology(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignGoafTechnology(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignGoafTechnology(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyByFields(cbm::DesignGoafTechnology & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyByField1(cbm::DesignGoafTechnology & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyByField2(cbm::DesignGoafTechnology & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyListByFields(std::vector<cbm::DesignGoafTechnology> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyListByField1(std::vector<cbm::DesignGoafTechnology> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyListByField2(std::vector<cbm::DesignGoafTechnology> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignGoafTechnologyIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafTechnologyIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignGoafTechnologyIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafTechnologyIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignGoafTechnologyIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignGoafTechnologyIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignGoafTechnologyIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyListByForeignKey(std::vector<cbm::DesignGoafTechnology> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignGoafTechnologyIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignGoafTechnologyIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignPore 类型的CRUD操作
int32_t SQLClientHelper::AddDesignPore(const cbm::DesignPore & design_pore) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignPore(design_pore);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignPore(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignPore(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignPore(const cbm::DesignPore & design_pore) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignPore(design_pore);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignPoreById(cbm::DesignPore & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreByForeignKey(cbm::DesignPore & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignPoreIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignPoreIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignPoreList(std::vector<cbm::DesignPore> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignPore(const std::vector<cbm::DesignPore> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignPore(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignPore(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignPore(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreByFields(cbm::DesignPore & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreByField1(cbm::DesignPore & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreByField2(cbm::DesignPore & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreListByFields(std::vector<cbm::DesignPore> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreListByField1(std::vector<cbm::DesignPore> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreListByField2(std::vector<cbm::DesignPore> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignPoreIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignPoreIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignPoreIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignPoreIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignPoreIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignPoreIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignPoreIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreListByForeignKey(std::vector<cbm::DesignPore> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignPoreIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignPoreIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignSite 类型的CRUD操作
int32_t SQLClientHelper::AddDesignSite(const cbm::DesignSite & design_site) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignSite(design_site);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignSite(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignSite(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignSite(const cbm::DesignSite & design_site) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignSite(design_site);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignSiteById(cbm::DesignSite & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteByForeignKey(cbm::DesignSite & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignSiteIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignSiteIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignSiteList(std::vector<cbm::DesignSite> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignSite(const std::vector<cbm::DesignSite> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignSite(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignSite(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignSite(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteByFields(cbm::DesignSite & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteByField1(cbm::DesignSite & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteByField2(cbm::DesignSite & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteListByFields(std::vector<cbm::DesignSite> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteListByField1(std::vector<cbm::DesignSite> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteListByField2(std::vector<cbm::DesignSite> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignSiteIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignSiteIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignSiteIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignSiteIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignSiteIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignSiteIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignSiteIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteListByForeignKey(std::vector<cbm::DesignSite> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignSiteIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignSiteIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignTechnology 类型的CRUD操作
int32_t SQLClientHelper::AddDesignTechnology(const cbm::DesignTechnology & design_technology) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignTechnology(design_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignTechnology(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignTechnology(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignTechnology(const cbm::DesignTechnology & design_technology) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignTechnology(design_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignTechnologyById(cbm::DesignTechnology & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyByForeignKey(cbm::DesignTechnology & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignTechnologyIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTechnologyIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignTechnologyList(std::vector<cbm::DesignTechnology> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignTechnology(const std::vector<cbm::DesignTechnology> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignTechnology(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignTechnology(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignTechnology(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyByFields(cbm::DesignTechnology & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyByField1(cbm::DesignTechnology & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyByField2(cbm::DesignTechnology & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyListByFields(std::vector<cbm::DesignTechnology> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyListByField1(std::vector<cbm::DesignTechnology> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyListByField2(std::vector<cbm::DesignTechnology> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignTechnologyIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTechnologyIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignTechnologyIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTechnologyIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignTechnologyIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTechnologyIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignTechnologyIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyListByForeignKey(std::vector<cbm::DesignTechnology> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTechnologyIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTechnologyIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignTunnelControlPoint 类型的CRUD操作
int32_t SQLClientHelper::AddDesignTunnelControlPoint(const cbm::DesignTunnelControlPoint & design_tunnel_control_point) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignTunnelControlPoint(design_tunnel_control_point);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignTunnelControlPoint(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignTunnelControlPoint(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignTunnelControlPoint(const cbm::DesignTunnelControlPoint & design_tunnel_control_point) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignTunnelControlPoint(design_tunnel_control_point);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignTunnelControlPointById(cbm::DesignTunnelControlPoint & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointByForeignKey(cbm::DesignTunnelControlPoint & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignTunnelControlPointIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTunnelControlPointIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignTunnelControlPointList(std::vector<cbm::DesignTunnelControlPoint> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignTunnelControlPoint(const std::vector<cbm::DesignTunnelControlPoint> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignTunnelControlPoint(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignTunnelControlPoint(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignTunnelControlPoint(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointByFields(cbm::DesignTunnelControlPoint & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointByField1(cbm::DesignTunnelControlPoint & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointByField2(cbm::DesignTunnelControlPoint & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointListByFields(std::vector<cbm::DesignTunnelControlPoint> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointListByField1(std::vector<cbm::DesignTunnelControlPoint> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointListByField2(std::vector<cbm::DesignTunnelControlPoint> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignTunnelControlPointIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTunnelControlPointIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignTunnelControlPointIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTunnelControlPointIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignTunnelControlPointIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignTunnelControlPointIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignTunnelControlPointIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointListByForeignKey(std::vector<cbm::DesignTunnelControlPoint> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignTunnelControlPointIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignTunnelControlPointIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignWorkSurfControlPoint 类型的CRUD操作
int32_t SQLClientHelper::AddDesignWorkSurfControlPoint(const cbm::DesignWorkSurfControlPoint & design_work_surf_control_point) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignWorkSurfControlPoint(design_work_surf_control_point);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignWorkSurfControlPoint(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignWorkSurfControlPoint(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignWorkSurfControlPoint(const cbm::DesignWorkSurfControlPoint & design_work_surf_control_point) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignWorkSurfControlPoint(design_work_surf_control_point);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignWorkSurfControlPointById(cbm::DesignWorkSurfControlPoint & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointByForeignKey(cbm::DesignWorkSurfControlPoint & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignWorkSurfControlPointIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfControlPointIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignWorkSurfControlPointList(std::vector<cbm::DesignWorkSurfControlPoint> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignWorkSurfControlPoint(const std::vector<cbm::DesignWorkSurfControlPoint> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignWorkSurfControlPoint(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignWorkSurfControlPoint(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignWorkSurfControlPoint(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointByFields(cbm::DesignWorkSurfControlPoint & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointByField1(cbm::DesignWorkSurfControlPoint & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointByField2(cbm::DesignWorkSurfControlPoint & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointListByFields(std::vector<cbm::DesignWorkSurfControlPoint> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointListByField1(std::vector<cbm::DesignWorkSurfControlPoint> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointListByField2(std::vector<cbm::DesignWorkSurfControlPoint> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignWorkSurfControlPointIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfControlPointIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignWorkSurfControlPointIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfControlPointIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignWorkSurfControlPointIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfControlPointIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignWorkSurfControlPointIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointListByForeignKey(std::vector<cbm::DesignWorkSurfControlPoint> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfControlPointIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfControlPointIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DesignWorkSurfTechnology 类型的CRUD操作
int32_t SQLClientHelper::AddDesignWorkSurfTechnology(const cbm::DesignWorkSurfTechnology & design_work_surf_technology) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDesignWorkSurfTechnology(design_work_surf_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDesignWorkSurfTechnology(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDesignWorkSurfTechnology(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDesignWorkSurfTechnology(const cbm::DesignWorkSurfTechnology & design_work_surf_technology) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDesignWorkSurfTechnology(design_work_surf_technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDesignWorkSurfTechnologyById(cbm::DesignWorkSurfTechnology & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyByForeignKey(cbm::DesignWorkSurfTechnology & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignWorkSurfTechnologyIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfTechnologyIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignWorkSurfTechnologyList(std::vector<cbm::DesignWorkSurfTechnology> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDesignWorkSurfTechnology(const std::vector<cbm::DesignWorkSurfTechnology> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDesignWorkSurfTechnology(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDesignWorkSurfTechnology(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDesignWorkSurfTechnology(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyByFields(cbm::DesignWorkSurfTechnology & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyByField1(cbm::DesignWorkSurfTechnology & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyByField2(cbm::DesignWorkSurfTechnology & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyListByFields(std::vector<cbm::DesignWorkSurfTechnology> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyListByField1(std::vector<cbm::DesignWorkSurfTechnology> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyListByField2(std::vector<cbm::DesignWorkSurfTechnology> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDesignWorkSurfTechnologyIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfTechnologyIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignWorkSurfTechnologyIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfTechnologyIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDesignWorkSurfTechnologyIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDesignWorkSurfTechnologyIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDesignWorkSurfTechnologyIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyListByForeignKey(std::vector<cbm::DesignWorkSurfTechnology> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDesignWorkSurfTechnologyIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDesignWorkSurfTechnologyIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DrillingRadiusParam 类型的CRUD操作
int32_t SQLClientHelper::AddDrillingRadiusParam(const cbm::DrillingRadiusParam & drilling_radius_param) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDrillingRadiusParam(drilling_radius_param);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDrillingRadiusParam(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDrillingRadiusParam(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDrillingRadiusParam(const cbm::DrillingRadiusParam & drilling_radius_param) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDrillingRadiusParam(drilling_radius_param);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDrillingRadiusParamById(cbm::DrillingRadiusParam & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamByForeignKey(cbm::DrillingRadiusParam & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDrillingRadiusParamIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingRadiusParamIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDrillingRadiusParamList(std::vector<cbm::DrillingRadiusParam> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDrillingRadiusParam(const std::vector<cbm::DrillingRadiusParam> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDrillingRadiusParam(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDrillingRadiusParam(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDrillingRadiusParam(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamByFields(cbm::DrillingRadiusParam & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamByField1(cbm::DrillingRadiusParam & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamByField2(cbm::DrillingRadiusParam & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamListByFields(std::vector<cbm::DrillingRadiusParam> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamListByField1(std::vector<cbm::DrillingRadiusParam> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamListByField2(std::vector<cbm::DrillingRadiusParam> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDrillingRadiusParamIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingRadiusParamIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDrillingRadiusParamIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingRadiusParamIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDrillingRadiusParamIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingRadiusParamIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDrillingRadiusParamIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamListByForeignKey(std::vector<cbm::DrillingRadiusParam> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingRadiusParamIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingRadiusParamIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//DrillingSurf 类型的CRUD操作
int32_t SQLClientHelper::AddDrillingSurf(const cbm::DrillingSurf & drilling_surf) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddDrillingSurf(drilling_surf);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteDrillingSurf(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteDrillingSurf(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateDrillingSurf(const cbm::DrillingSurf & drilling_surf) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateDrillingSurf(drilling_surf);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetDrillingSurfById(cbm::DrillingSurf & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfByForeignKey(cbm::DrillingSurf & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDrillingSurfIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingSurfIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDrillingSurfList(std::vector<cbm::DrillingSurf> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreDrillingSurf(const std::vector<cbm::DrillingSurf> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreDrillingSurf(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreDrillingSurf(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreDrillingSurf(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfByFields(cbm::DrillingSurf & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfByField1(cbm::DrillingSurf & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfByField2(cbm::DrillingSurf & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfListByFields(std::vector<cbm::DrillingSurf> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfListByField1(std::vector<cbm::DrillingSurf> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfListByField2(std::vector<cbm::DrillingSurf> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetDrillingSurfIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingSurfIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDrillingSurfIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingSurfIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetDrillingSurfIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetDrillingSurfIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetDrillingSurfIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfListByForeignKey(std::vector<cbm::DrillingSurf> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetDrillingSurfIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetDrillingSurfIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//HighDrillingPore 类型的CRUD操作
int32_t SQLClientHelper::AddHighDrillingPore(const cbm::HighDrillingPore & high_drilling_pore) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddHighDrillingPore(high_drilling_pore);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteHighDrillingPore(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteHighDrillingPore(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateHighDrillingPore(const cbm::HighDrillingPore & high_drilling_pore) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateHighDrillingPore(high_drilling_pore);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetHighDrillingPoreById(cbm::HighDrillingPore & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreByForeignKey(cbm::HighDrillingPore & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingPoreIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingPoreList(std::vector<cbm::HighDrillingPore> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreHighDrillingPore(const std::vector<cbm::HighDrillingPore> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreHighDrillingPore(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreHighDrillingPore(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreHighDrillingPore(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreByFields(cbm::HighDrillingPore & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreByField1(cbm::HighDrillingPore & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreByField2(cbm::HighDrillingPore & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreListByFields(std::vector<cbm::HighDrillingPore> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreListByField1(std::vector<cbm::HighDrillingPore> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreListByField2(std::vector<cbm::HighDrillingPore> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingPoreIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingPoreIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingPoreIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingPoreIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreListByForeignKey(std::vector<cbm::HighDrillingPore> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//HighDrillingPoreParam 类型的CRUD操作
int32_t SQLClientHelper::AddHighDrillingPoreParam(const cbm::HighDrillingPoreParam & high_drilling_pore_param) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddHighDrillingPoreParam(high_drilling_pore_param);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteHighDrillingPoreParam(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteHighDrillingPoreParam(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateHighDrillingPoreParam(const cbm::HighDrillingPoreParam & high_drilling_pore_param) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateHighDrillingPoreParam(high_drilling_pore_param);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetHighDrillingPoreParamById(cbm::HighDrillingPoreParam & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamByForeignKey(cbm::HighDrillingPoreParam & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingPoreParamIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreParamIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingPoreParamList(std::vector<cbm::HighDrillingPoreParam> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreHighDrillingPoreParam(const std::vector<cbm::HighDrillingPoreParam> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreHighDrillingPoreParam(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreHighDrillingPoreParam(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreHighDrillingPoreParam(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamByFields(cbm::HighDrillingPoreParam & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamByField1(cbm::HighDrillingPoreParam & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamByField2(cbm::HighDrillingPoreParam & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamListByFields(std::vector<cbm::HighDrillingPoreParam> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamListByField1(std::vector<cbm::HighDrillingPoreParam> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamListByField2(std::vector<cbm::HighDrillingPoreParam> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingPoreParamIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreParamIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingPoreParamIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreParamIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingPoreParamIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingPoreParamIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingPoreParamIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamListByForeignKey(std::vector<cbm::HighDrillingPoreParam> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingPoreParamIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingPoreParamIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//HighDrillingSiteParam 类型的CRUD操作
int32_t SQLClientHelper::AddHighDrillingSiteParam(const cbm::HighDrillingSiteParam & high_drilling_site_param) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddHighDrillingSiteParam(high_drilling_site_param);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteHighDrillingSiteParam(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteHighDrillingSiteParam(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateHighDrillingSiteParam(const cbm::HighDrillingSiteParam & high_drilling_site_param) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateHighDrillingSiteParam(high_drilling_site_param);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetHighDrillingSiteParamById(cbm::HighDrillingSiteParam & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamByForeignKey(cbm::HighDrillingSiteParam & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingSiteParamIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingSiteParamIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingSiteParamList(std::vector<cbm::HighDrillingSiteParam> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreHighDrillingSiteParam(const std::vector<cbm::HighDrillingSiteParam> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreHighDrillingSiteParam(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreHighDrillingSiteParam(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreHighDrillingSiteParam(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamByFields(cbm::HighDrillingSiteParam & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamByField1(cbm::HighDrillingSiteParam & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamByField2(cbm::HighDrillingSiteParam & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamListByFields(std::vector<cbm::HighDrillingSiteParam> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamListByField1(std::vector<cbm::HighDrillingSiteParam> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamListByField2(std::vector<cbm::HighDrillingSiteParam> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingSiteParamIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingSiteParamIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingSiteParamIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingSiteParamIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingSiteParamIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingSiteParamIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingSiteParamIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamListByForeignKey(std::vector<cbm::HighDrillingSiteParam> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingSiteParamIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingSiteParamIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//HighDrillingTunnel 类型的CRUD操作
int32_t SQLClientHelper::AddHighDrillingTunnel(const cbm::HighDrillingTunnel & high_drilling_tunnel) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddHighDrillingTunnel(high_drilling_tunnel);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteHighDrillingTunnel(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteHighDrillingTunnel(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateHighDrillingTunnel(const cbm::HighDrillingTunnel & high_drilling_tunnel) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateHighDrillingTunnel(high_drilling_tunnel);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetHighDrillingTunnelById(cbm::HighDrillingTunnel & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelByForeignKey(cbm::HighDrillingTunnel & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingTunnelIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingTunnelIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingTunnelList(std::vector<cbm::HighDrillingTunnel> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreHighDrillingTunnel(const std::vector<cbm::HighDrillingTunnel> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreHighDrillingTunnel(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreHighDrillingTunnel(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreHighDrillingTunnel(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelByFields(cbm::HighDrillingTunnel & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelByField1(cbm::HighDrillingTunnel & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelByField2(cbm::HighDrillingTunnel & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelListByFields(std::vector<cbm::HighDrillingTunnel> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelListByField1(std::vector<cbm::HighDrillingTunnel> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelListByField2(std::vector<cbm::HighDrillingTunnel> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHighDrillingTunnelIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingTunnelIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingTunnelIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingTunnelIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHighDrillingTunnelIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHighDrillingTunnelIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHighDrillingTunnelIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelListByForeignKey(std::vector<cbm::HighDrillingTunnel> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHighDrillingTunnelIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHighDrillingTunnelIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//HydrGeo 类型的CRUD操作
int32_t SQLClientHelper::AddHydrGeo(const cbm::HydrGeo & hydr_geo) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddHydrGeo(hydr_geo);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteHydrGeo(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteHydrGeo(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateHydrGeo(const cbm::HydrGeo & hydr_geo) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateHydrGeo(hydr_geo);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetHydrGeoById(cbm::HydrGeo & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoByForeignKey(cbm::HydrGeo & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHydrGeoIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHydrGeoIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHydrGeoList(std::vector<cbm::HydrGeo> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreHydrGeo(const std::vector<cbm::HydrGeo> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreHydrGeo(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreHydrGeo(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreHydrGeo(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoByFields(cbm::HydrGeo & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoByField1(cbm::HydrGeo & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoByField2(cbm::HydrGeo & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoListByFields(std::vector<cbm::HydrGeo> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoListByField1(std::vector<cbm::HydrGeo> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoListByField2(std::vector<cbm::HydrGeo> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetHydrGeoIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHydrGeoIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHydrGeoIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHydrGeoIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetHydrGeoIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetHydrGeoIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetHydrGeoIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoListByForeignKey(std::vector<cbm::HydrGeo> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetHydrGeoIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetHydrGeoIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//Mine 类型的CRUD操作
int32_t SQLClientHelper::AddMine(const cbm::Mine & mine) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddMine(mine);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteMine(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteMine(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateMine(const cbm::Mine & mine) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateMine(mine);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetMineById(cbm::Mine & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineByForeignKey(cbm::Mine & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetMineIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetMineList(std::vector<cbm::Mine> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreMine(const std::vector<cbm::Mine> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreMine(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreMine(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreMine(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineByFields(cbm::Mine & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineByField1(cbm::Mine & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineByField2(cbm::Mine & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineListByFields(std::vector<cbm::Mine> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineListByField1(std::vector<cbm::Mine> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineListByField2(std::vector<cbm::Mine> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetMineIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetMineIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetMineIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetMineIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineListByForeignKey(std::vector<cbm::Mine> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//MineBase 类型的CRUD操作
int32_t SQLClientHelper::AddMineBase(const cbm::MineBase & mine_base) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddMineBase(mine_base);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteMineBase(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteMineBase(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateMineBase(const cbm::MineBase & mine_base) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateMineBase(mine_base);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetMineBaseById(cbm::MineBase & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseByForeignKey(cbm::MineBase & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetMineBaseIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineBaseIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetMineBaseList(std::vector<cbm::MineBase> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreMineBase(const std::vector<cbm::MineBase> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreMineBase(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreMineBase(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreMineBase(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseByFields(cbm::MineBase & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseByField1(cbm::MineBase & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseByField2(cbm::MineBase & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseListByFields(std::vector<cbm::MineBase> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseListByField1(std::vector<cbm::MineBase> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseListByField2(std::vector<cbm::MineBase> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetMineBaseIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineBaseIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetMineBaseIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineBaseIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetMineBaseIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineBaseIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetMineBaseIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseListByForeignKey(std::vector<cbm::MineBase> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineBaseIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineBaseIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//MineRegion 类型的CRUD操作
int32_t SQLClientHelper::AddMineRegion(const cbm::MineRegion & mine_region) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddMineRegion(mine_region);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteMineRegion(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteMineRegion(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateMineRegion(const cbm::MineRegion & mine_region) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateMineRegion(mine_region);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetMineRegionById(cbm::MineRegion & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionByForeignKey(cbm::MineRegion & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetMineRegionIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineRegionIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetMineRegionList(std::vector<cbm::MineRegion> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreMineRegion(const std::vector<cbm::MineRegion> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreMineRegion(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreMineRegion(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreMineRegion(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionByFields(cbm::MineRegion & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionByField1(cbm::MineRegion & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionByField2(cbm::MineRegion & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionListByFields(std::vector<cbm::MineRegion> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionListByField1(std::vector<cbm::MineRegion> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionListByField2(std::vector<cbm::MineRegion> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetMineRegionIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineRegionIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetMineRegionIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineRegionIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetMineRegionIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetMineRegionIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetMineRegionIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionListByForeignKey(std::vector<cbm::MineRegion> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetMineRegionIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetMineRegionIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//PoreFlow 类型的CRUD操作
int32_t SQLClientHelper::AddPoreFlow(const cbm::PoreFlow & pore_flow) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddPoreFlow(pore_flow);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeletePoreFlow(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeletePoreFlow(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdatePoreFlow(const cbm::PoreFlow & pore_flow) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdatePoreFlow(pore_flow);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetPoreFlowById(cbm::PoreFlow & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowByForeignKey(cbm::PoreFlow & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetPoreFlowIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreFlowIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetPoreFlowList(std::vector<cbm::PoreFlow> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMorePoreFlow(const std::vector<cbm::PoreFlow> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMorePoreFlow(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMorePoreFlow(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMorePoreFlow(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowByFields(cbm::PoreFlow & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowByField1(cbm::PoreFlow & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowByField2(cbm::PoreFlow & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowListByFields(std::vector<cbm::PoreFlow> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowListByField1(std::vector<cbm::PoreFlow> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowListByField2(std::vector<cbm::PoreFlow> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetPoreFlowIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreFlowIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetPoreFlowIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreFlowIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetPoreFlowIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreFlowIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetPoreFlowIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowListByForeignKey(std::vector<cbm::PoreFlow> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreFlowIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreFlowIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//PoreSize 类型的CRUD操作
int32_t SQLClientHelper::AddPoreSize(const cbm::PoreSize & pore_size) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddPoreSize(pore_size);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeletePoreSize(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeletePoreSize(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdatePoreSize(const cbm::PoreSize & pore_size) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdatePoreSize(pore_size);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetPoreSizeById(cbm::PoreSize & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeByForeignKey(cbm::PoreSize & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetPoreSizeIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreSizeIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetPoreSizeList(std::vector<cbm::PoreSize> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMorePoreSize(const std::vector<cbm::PoreSize> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMorePoreSize(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMorePoreSize(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMorePoreSize(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeByFields(cbm::PoreSize & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeByField1(cbm::PoreSize & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeByField2(cbm::PoreSize & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeListByFields(std::vector<cbm::PoreSize> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeListByField1(std::vector<cbm::PoreSize> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeListByField2(std::vector<cbm::PoreSize> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetPoreSizeIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreSizeIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetPoreSizeIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreSizeIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetPoreSizeIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetPoreSizeIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetPoreSizeIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeListByForeignKey(std::vector<cbm::PoreSize> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetPoreSizeIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetPoreSizeIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//ResAbundance 类型的CRUD操作
int32_t SQLClientHelper::AddResAbundance(const cbm::ResAbundance & res_abundance) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddResAbundance(res_abundance);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteResAbundance(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteResAbundance(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateResAbundance(const cbm::ResAbundance & res_abundance) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateResAbundance(res_abundance);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetResAbundanceById(cbm::ResAbundance & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceByForeignKey(cbm::ResAbundance & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetResAbundanceIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetResAbundanceIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetResAbundanceList(std::vector<cbm::ResAbundance> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreResAbundance(const std::vector<cbm::ResAbundance> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreResAbundance(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreResAbundance(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreResAbundance(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceByFields(cbm::ResAbundance & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceByField1(cbm::ResAbundance & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceByField2(cbm::ResAbundance & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceListByFields(std::vector<cbm::ResAbundance> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceListByField1(std::vector<cbm::ResAbundance> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceListByField2(std::vector<cbm::ResAbundance> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetResAbundanceIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetResAbundanceIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetResAbundanceIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetResAbundanceIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetResAbundanceIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetResAbundanceIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetResAbundanceIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceListByForeignKey(std::vector<cbm::ResAbundance> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetResAbundanceIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetResAbundanceIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//Rock 类型的CRUD操作
int32_t SQLClientHelper::AddRock(const cbm::Rock & rock) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddRock(rock);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteRock(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteRock(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateRock(const cbm::Rock & rock) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateRock(rock);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetRockById(cbm::Rock & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockByForeignKey(cbm::Rock & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetRockIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetRockIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetRockList(std::vector<cbm::Rock> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreRock(const std::vector<cbm::Rock> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreRock(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreRock(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreRock(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockByFields(cbm::Rock & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockByField1(cbm::Rock & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockByField2(cbm::Rock & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockListByFields(std::vector<cbm::Rock> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockListByField1(std::vector<cbm::Rock> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockListByField2(std::vector<cbm::Rock> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetRockIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetRockIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetRockIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetRockIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetRockIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetRockIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetRockIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockListByForeignKey(std::vector<cbm::Rock> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetRockIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetRockIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//SysInfo 类型的CRUD操作
int32_t SQLClientHelper::AddSysInfo(const cbm::SysInfo & sys_info) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddSysInfo(sys_info);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteSysInfo(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteSysInfo(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateSysInfo(const cbm::SysInfo & sys_info) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateSysInfo(sys_info);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetSysInfoById(cbm::SysInfo & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoByForeignKey(cbm::SysInfo & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetSysInfoIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetSysInfoIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetSysInfoList(std::vector<cbm::SysInfo> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreSysInfo(const std::vector<cbm::SysInfo> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreSysInfo(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreSysInfo(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreSysInfo(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoByFields(cbm::SysInfo & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoByField1(cbm::SysInfo & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoByField2(cbm::SysInfo & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoListByFields(std::vector<cbm::SysInfo> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoListByField1(std::vector<cbm::SysInfo> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoListByField2(std::vector<cbm::SysInfo> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetSysInfoIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetSysInfoIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetSysInfoIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetSysInfoIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetSysInfoIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetSysInfoIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetSysInfoIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoListByForeignKey(std::vector<cbm::SysInfo> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetSysInfoIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetSysInfoIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//TechMode 类型的CRUD操作
int32_t SQLClientHelper::AddTechMode(const cbm::TechMode & tech_mode) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddTechMode(tech_mode);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteTechMode(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteTechMode(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateTechMode(const cbm::TechMode & tech_mode) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateTechMode(tech_mode);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetTechModeById(cbm::TechMode & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeByForeignKey(cbm::TechMode & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTechModeIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechModeIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTechModeList(std::vector<cbm::TechMode> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreTechMode(const std::vector<cbm::TechMode> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreTechMode(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreTechMode(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreTechMode(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeByFields(cbm::TechMode & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeByField1(cbm::TechMode & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeByField2(cbm::TechMode & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeListByFields(std::vector<cbm::TechMode> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeListByField1(std::vector<cbm::TechMode> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeListByField2(std::vector<cbm::TechMode> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTechModeIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechModeIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTechModeIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechModeIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTechModeIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechModeIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTechModeIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeListByForeignKey(std::vector<cbm::TechMode> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechModeIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechModeIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//Technology 类型的CRUD操作
int32_t SQLClientHelper::AddTechnology(const cbm::Technology & technology) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddTechnology(technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteTechnology(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteTechnology(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateTechnology(const cbm::Technology & technology) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateTechnology(technology);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetTechnologyById(cbm::Technology & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyByForeignKey(cbm::Technology & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTechnologyIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechnologyIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTechnologyList(std::vector<cbm::Technology> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreTechnology(const std::vector<cbm::Technology> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreTechnology(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreTechnology(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreTechnology(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyByFields(cbm::Technology & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyByField1(cbm::Technology & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyByField2(cbm::Technology & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyListByFields(std::vector<cbm::Technology> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyListByField1(std::vector<cbm::Technology> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyListByField2(std::vector<cbm::Technology> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTechnologyIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechnologyIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTechnologyIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechnologyIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTechnologyIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTechnologyIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTechnologyIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyListByForeignKey(std::vector<cbm::Technology> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTechnologyIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTechnologyIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//TopoGeo 类型的CRUD操作
int32_t SQLClientHelper::AddTopoGeo(const cbm::TopoGeo & topo_geo) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddTopoGeo(topo_geo);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteTopoGeo(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteTopoGeo(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateTopoGeo(const cbm::TopoGeo & topo_geo) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateTopoGeo(topo_geo);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetTopoGeoById(cbm::TopoGeo & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoByForeignKey(cbm::TopoGeo & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTopoGeoIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTopoGeoIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTopoGeoList(std::vector<cbm::TopoGeo> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreTopoGeo(const std::vector<cbm::TopoGeo> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreTopoGeo(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreTopoGeo(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreTopoGeo(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoByFields(cbm::TopoGeo & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoByField1(cbm::TopoGeo & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoByField2(cbm::TopoGeo & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoListByFields(std::vector<cbm::TopoGeo> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoListByField1(std::vector<cbm::TopoGeo> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoListByField2(std::vector<cbm::TopoGeo> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTopoGeoIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTopoGeoIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTopoGeoIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTopoGeoIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTopoGeoIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTopoGeoIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTopoGeoIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoListByForeignKey(std::vector<cbm::TopoGeo> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTopoGeoIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTopoGeoIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//Tunnel 类型的CRUD操作
int32_t SQLClientHelper::AddTunnel(const cbm::Tunnel & tunnel) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddTunnel(tunnel);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteTunnel(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteTunnel(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateTunnel(const cbm::Tunnel & tunnel) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateTunnel(tunnel);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetTunnelById(cbm::Tunnel & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelByForeignKey(cbm::Tunnel & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTunnelIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTunnelIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTunnelList(std::vector<cbm::Tunnel> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreTunnel(const std::vector<cbm::Tunnel> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreTunnel(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreTunnel(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreTunnel(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelByFields(cbm::Tunnel & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelByField1(cbm::Tunnel & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelByField2(cbm::Tunnel & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelListByFields(std::vector<cbm::Tunnel> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelListByField1(std::vector<cbm::Tunnel> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelListByField2(std::vector<cbm::Tunnel> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetTunnelIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTunnelIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTunnelIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTunnelIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetTunnelIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetTunnelIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetTunnelIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelListByForeignKey(std::vector<cbm::Tunnel> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetTunnelIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetTunnelIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//WorkArea 类型的CRUD操作
int32_t SQLClientHelper::AddWorkArea(const cbm::WorkArea & work_area) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddWorkArea(work_area);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteWorkArea(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteWorkArea(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateWorkArea(const cbm::WorkArea & work_area) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateWorkArea(work_area);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetWorkAreaById(cbm::WorkArea & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaByForeignKey(cbm::WorkArea & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetWorkAreaIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkAreaIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetWorkAreaList(std::vector<cbm::WorkArea> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreWorkArea(const std::vector<cbm::WorkArea> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreWorkArea(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreWorkArea(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreWorkArea(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaByFields(cbm::WorkArea & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaByField1(cbm::WorkArea & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaByField2(cbm::WorkArea & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaListByFields(std::vector<cbm::WorkArea> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaListByField1(std::vector<cbm::WorkArea> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaListByField2(std::vector<cbm::WorkArea> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetWorkAreaIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkAreaIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetWorkAreaIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkAreaIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetWorkAreaIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkAreaIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetWorkAreaIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaListByForeignKey(std::vector<cbm::WorkArea> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkAreaIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkAreaIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

//WorkSurf 类型的CRUD操作
int32_t SQLClientHelper::AddWorkSurf(const cbm::WorkSurf & work_surf) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->AddWorkSurf(work_surf);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
	return ret;
}
bool SQLClientHelper::DeleteWorkSurf(const int32_t id) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->DeleteWorkSurf(id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
bool SQLClientHelper::UpdateWorkSurf(const cbm::WorkSurf & work_surf) {
	bool ret = false;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->UpdateWorkSurf(work_surf);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = false;
	}
	return ret;
}
void SQLClientHelper::GetWorkSurfById(cbm::WorkSurf & _return, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfById(_return, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfByForeignKey(cbm::WorkSurf & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetWorkSurfIdByForeignKey(const std::string& fkey, const int32_t id) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkSurfIdByForeignKey(fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetWorkSurfList(std::vector<cbm::WorkSurf> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfList(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfIds(std::vector<int32_t> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfIds(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfNames(std::vector<std::string> & _return) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfNames(_return);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::AddMoreWorkSurf(const std::vector<cbm::WorkSurf> & objs) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->AddMoreWorkSurf(objs);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::DeleteMoreWorkSurf(const std::vector<int32_t> & obj_ids) {
	if(obj_ids.empty()) return;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->DeleteMoreWorkSurf(obj_ids);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfByFields(cbm::WorkSurf & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfByField1(cbm::WorkSurf & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfByField2(cbm::WorkSurf & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfListByFields(std::vector<cbm::WorkSurf> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfListByField1(std::vector<cbm::WorkSurf> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfListByField2(std::vector<cbm::WorkSurf> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
int32_t SQLClientHelper::GetWorkSurfIdByFields(const std::map<std::string, std::string> & fields) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkSurfIdByFields(fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetWorkSurfIdByField1(const std::string& field, const std::string& value) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkSurfIdByField1(field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
int32_t SQLClientHelper::GetWorkSurfIdByField2(const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	int32_t ret = -1;
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		ret = service_client.get()->GetWorkSurfIdByField2(field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
		ret = -1;
	}
return ret;
}
void SQLClientHelper::GetWorkSurfIdListByFields(std::vector<int32_t> & _return, const std::map<std::string, std::string> & fields) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfIdListByFields(_return, fields);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfIdListByField1(std::vector<int32_t> & _return, const std::string& field, const std::string& value) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfIdListByField1(_return, field, value);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfIdListByField2(std::vector<int32_t> & _return, const std::string& field1, const std::string& value1, const std::string& field2, const std::string& value2) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfIdListByField2(_return, field1, value1, field2, value2);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfListByForeignKey(std::vector<cbm::WorkSurf> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}
void SQLClientHelper::GetWorkSurfIdListByForeignKey(std::vector<int32_t> & _return, const std::string& fkey, const int32_t id) {
	try {
		RpcClient<cbm::CbmServiceClient> service_client(HOST, PORT2);
		service_client.start();
		service_client.get()->GetWorkSurfIdListByForeignKey(_return, fkey, id);
		service_client.close();
	}
	catch (TException &tx) {
		std::string error_msg = tx.what();
	}
}

