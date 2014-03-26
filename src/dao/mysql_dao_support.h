#ifndef MSQL_DAO_SUPPORT_
#define MYSQL_DAO_SUPPORT_

#include <string>
#include <map>
#include <list>
#include <vo/vo.h>
#include <boost/shared_ptr.hpp>
#include <db/imysql_conn.h>
#include <db/mysql_conn_pool.h>

using std::string;
using std::map;
using boost::shared_ptr;
using db::CMysqlConnPool;
using db::IMysqlConn;
using db::SMysqlConf;

class MysqlProxyReq {
  public:
    string db_name_;
    string type_;
    string sql_;
};


class MysqlProxy {

  public:
    MysqlProxy() : table_pool_(10) {}
    ~MysqlProxy() { Uninit(); }

    int32_t Init();
    int32_t Uninit();
    int32_t AddNode(const SMysqlConf& node_desc, uint32_t conn_cnt);
    int32_t Querry(const share_ptr<MysqlProxyReq> & req, IMysqlQueryRespParser* resp_parser);
    MYSQL_RES* QueryWithoutParser(const shared_ptr<MysqlProxyReq>& req);
    int32_t AddToTablePool(const string& db_name);
    int32_t LoadOneTable(IMysqlConn* conn, const string& table_name, const string& db_name);
    int32_t InitColumnFromRes(MYSQL_RES8 res, std::vector<ColumnInfo>& columns,std::string& order_by);
    const RowInfo& GetRowInfo(const std::string& table_name);

  protected:
    IMysqlConn* GetConnByKey(const string& key);
    void FreeConnByKey(const string& key, IMysqlConn* conn);

  protected:
    map<string, CMysqlConnPool*> pools_;
    TablePool table_pool_;
};

inline const RowInfo& MysqlProxy::GetRowInfo(const std::string& table_name) {
  return table_pool_.GetRowInfo(table_name);
}

#endif
