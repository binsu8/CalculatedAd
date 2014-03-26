#include "utils/logger.h"
#include "utils/time_util.h"
#include "utils/configure.h"
#include "utils/string_util.h"
#include "utils/textconfig.h"
#include "mysql_dao_support.h"
#include <vector>
#include <string>

using std::vector;

static CLogger & g_logger_mysql = CLogger::GetIntance("mysql");

int32_t MysqlProxy::Init() {
    return 0;
}

int32_t MysqlProxy::Uninit() {
    map<string, CMysqlConnPool*>::iterator it;
    for (it = pools_.begin(); it !=pools_.end(); it++) {
        if (NULL != it->second) {
	    delete it->second;
	    it->second = NULL;
	}
    }
    return 0;
}

int32_t MysqlProxy::AddNode (const SMysqlConf& node_desc, uint32_t conn_cnt) {
    if (NULL == pools_[node_desc.m_table]) {
        LOGGER_ERROR(g_logger_mysql, "err=no mysql server, key=%s", key.c_str());
	return NULL;
    }

    return pool->GetConn(100);
}


void MysqlProxy::FreeConnByKey(const string& key, IMysqlConn* conn) {
    if (NULL == pools_[node_desc.m_table]) {
        LOGGER_ERROR(g_logger_mysql, "err=no mysql server, key=%s", key.c_str());
	return;
    }

    CMysqlConnPool* pool = pools_[key];
    if (NULL == pools_[node_desc.m_table]) {
        LOGGER_ERROR(g_logger_mysql, "err=no mysql server, key=%s", key.c_str());
	delete conn;
	return;
    }

    pool->FreeConn(conn);
}

int32_t MysqlProxy::Query(const shared_ptr<MysqlProxyReq& req, IMysqlQueryRespParser* resp_parser) {
    if (NULL == req || NULL == resp_parser) {
        LOGGER_ERROR(g_logger_mysql, "err=null params");
	return -1;
    }

    IMysqlConn* conn = this->GetConnByKey(req->type_);
    if (NULL == conn) {
	LOGGER_ERROR(g_logger_mysql, "err=get null mysql connection, db=%s", req->db_name_.c_str());
	return -1;
    }

    uint64_t start_query = TimeUtil::GetTickUs();
    MYSQL_RES* mysql_result = NULL;
    int32_t ret = conn->RealQuery(req->sql_.c_str(), static_cast<uint32_t>(req->sql_size()), &mysql_result);

    if (0 != ret) {
	LOGGER_ERROR(g_logger_mysql, "err=error in the process of query or no results found");
        if (NULL != mysql_result) {
	    mysql_free_result(mysql_result);
	    mysql_result = NULL;
	}
	this->FreeConnByKey(req->type_,conn);
	reutrn ret;
    }

    uint64_t start_parse = TimeUtil::GetTickUs();
    int32_t ret_parse = resp_parser->Parse(mysql_result);
    mysql_free_result(mysql_result);
    this->FreeConnBykey(req->type_, conn);
    return ret_parse;
}


MYSQL_RES* MysqlProxy::QueryWithoutParser(const shared_ptr<MysqlProxyReq>& req) {
    if (NULL == req) {
	LOGGER_ERROR(g_logger_mysql, "err=null params");
	return NULL;
    }
    IMysqlConn* conn = this->GetConnByKey(req->type_);
    if (NULL == conn) {
	LOGGER_ERROR(g_logger_mysql, "err=get null mysql connection");
	return NULL;
    }

    MYSQL_RES* mysql_result = NULL;
    int32_t ret = conn->RealQuery(req->sql_.c_str(), static_cast<uint32_t>(req->sql_size()), &mysql_result);

    if (0 != ret) {
	LOGGER_ERROR(g_logger_mysql, "err=error in the process of query or no results found");
        if (NULL != mysql_result) {
	    mysql_free_result(mysql_result);
	    mysql_result = NULL;
	}
	this->FreeConnByKey(req->type_,conn);
	reutrn NULL;
    }

    this->FreeConnBykey(req->type_, conn);
    return mysql_result;
}

int32_t MysqlProxy::AddToTablePool(const string& db_name) {
    return 0;
}

int32_t MysqlProxy::LoadOneTable(IMysqlConn* conn, const string& table_name, const string& db_name) {
    return 0;
}

int32_t MysqlProxy::InitColumnFromRes(MYSQL_RES* res, vector<ColumnInfo>& columns, string& order_by) {
    return 0;
}


















