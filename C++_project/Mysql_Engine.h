#pragma once
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <string>
#include <memory>
#include <iostream>
using namespace std;
/*
driver指针: 驱动程序实例的指针, 用于创建连接
connection指针: 数据库连接指针，传输数据
statement指针: SQL语句执行对象的指针，用于执行SQL语句

连接示意图
diver
  ||
connection——lastError
  ||
statement

采取单例设计模式:
确保只有一个数据库连接实例存在，避免资源浪费和连接冲突。
*/

class MySQLDriver {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* connection;
    sql::Statement* statement;
    std::string lastError;

    // 禁用拷贝构造函数和赋值操作符
    // 确保数据的安全
    MySQLDriver(const MySQLDriver&) = delete;
    MySQLDriver& operator=(const MySQLDriver&) = delete;


public:
    // 构造函数和析构函数
    MySQLDriver();
    ~MySQLDriver();

    // 连接管理

    // 用于构造函数
    bool connect(const string& host,    //  本地数据库地址
        const string& user,             //  用户名字
        const string& password,         //  用户密码
        const string& database = "");   //  数据库名字

    // 用于析构函数
    void disconnect();                  //  结束时候手动断开连接, 防止出bug


	bool isConnected() const;           //  判断是否连接成功

    // SQL执行
	bool execute(const std::string& sql);            // 执行非查询SQL语句
	std::unique_ptr<sql::ResultSet> executeQuery(const std::string& sql);  // 执行查询SQL语句

    // 调试方法
    string getLastError() const;

	//暂时用不到的功能
    //// 事务管理
    //bool beginTransaction();
    //bool commitTransaction();
    //bool rollbackTransaction();

    //// 获取连接信息
    //std::string getLastError() const;
    //std::string getServerInfo() const;
};
