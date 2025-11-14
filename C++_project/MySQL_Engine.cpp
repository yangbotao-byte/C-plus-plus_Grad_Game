#include "MySQL_Engine.h"
#include "tool.h"

MySQLDriver::MySQLDriver()
    : driver(nullptr), connection(nullptr), statement(nullptr) {
    // 设置控制台输出为UTF-8，确保中文正常显示
    SetConsoleOutputCP(CP_UTF8);

    try {
		//尝试获取单例MySQL驱动实例
        driver = sql::mysql::get_mysql_driver_instance();
    }
	// sql::SQLException是MySQL Connector/C++异常库类型
    catch (sql::SQLException& e) {
        // 输出错误信息
       string errorMsg = "Failed to get MySQL driver: " + std::string(e.what());
       cerr << errorMsg << endl;
    }
}


MySQLDriver::~MySQLDriver() {
    disconnect();
}

// 连接数据库
bool MySQLDriver::connect(const std::string& host, const std::string& user,
    const std::string& password, const std::string& database) {

    try {
        std::string connectionString = "tcp://" + host + ":3306";

        // 建立数据库连接
        //con = driver->connect("tcp://localhost:3306", "root", "123456");
        connection = driver->connect(connectionString, user, password);
          
        // 创建SQL语句对象
        statement = connection->createStatement();

        // 需要连接后才可以创建数据库
        string sql = "CREATE DATABASE IF NOT EXISTS " + database;
        execute(sql);

        // 设置连接选项
        connection->setSchema(database); // 如果提供了数据库名，则选择该数据库
        connection->setAutoCommit(true); // 默认自动提交

        lastError.clear();

        //创建成功
        return true;
    }

    catch (sql::SQLException& e) {
        lastError = "Connection failed: " + std::string(e.what());
        cerr << lastError << endl;
        return false;
    }
}

// 将所有指针放空
void MySQLDriver::disconnect() {
    if (statement) {
        delete statement;
        statement = nullptr;
    }
    if (connection) {
        delete connection;
        connection = nullptr;
    }
}

bool MySQLDriver::isConnected() const {
    //判断连接是否关闭，isClosed()方法确认连接状态
    return connection != nullptr && !connection->isClosed();
}

/*
executeQuery	                 execute
用于SELECT等有返回结果的查询	用于CREATE、INSERT、UPDATE等无返回的操作
返回ResultSet指针	            返回bool表示成功与否
获取查询结果数据	            只关心执行是否成功

*/

bool MySQLDriver::execute(const std::string& sql) {
    try {
        // 1. 检查statement对象是否有效
        // 因为statement对象是用于执行SQL语句的
        if (!statement) {
            lastError = "Statement is not initialized";
            return false;
        }

		//这里的execute不是自己些的，而是调用第三方库的
        statement->execute(sql);
        lastError.clear();
        return true;

    }
    catch (sql::SQLException& e) {
        lastError = "Execute failed: " + std::string(e.what()) + " [SQL: " + sql + "]";
        std::cerr << lastError << std::endl;
        return false;
    }
}

std::unique_ptr<sql::ResultSet> MySQLDriver::executeQuery(const std::string& sql) {
    try {
        if (!statement) {
            lastError = "Statement is not initialized";
            return nullptr;
        }

        auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery(sql));
        lastError.clear();
        return result;

    }
    catch (sql::SQLException& e) {
        lastError = "Query failed: " + std::string(e.what()) + " [SQL: " + sql + "]";
        std::cerr << lastError << std::endl;
        return nullptr;
    }
}

string MySQLDriver::getLastError() const {
    return lastError;
}


//bool MySQLDriver::beginTransaction() {
//    try {
//        if (connection) {
//            connection->setAutoCommit(false);
//            lastError.clear();
//            return true;
//        }
//        return false;
//    }
//    catch (sql::SQLException& e) {
//        lastError = "Begin transaction failed: " + std::string(e.what());
//        return false;
//    }
//}
//
//bool MySQLDriver::commitTransaction() {
//    try {
//        if (connection) {
//            connection->commit();
//            connection->setAutoCommit(true);
//            lastError.clear();
//            return true;
//        }
//        return false;
//    }
//    catch (sql::SQLException& e) {
//        lastError = "Commit transaction failed: " + std::string(e.what());
//        return false;
//    }
//}
//
//bool MySQLDriver::rollbackTransaction() {
//    try {
//        if (connection) {
//            connection->rollback();
//            connection->setAutoCommit(true);
//            lastError.clear();
//            return true;
//        }
//        return false;
//    }
//    catch (sql::SQLException& e) {
//        lastError = "Rollback transaction failed: " + std::string(e.what());
//        return false;
//    }
//}
//
//
//std::string MySQLDriver::getServerInfo() const {
//    if (connection) {
//        return connection->getClientInfo();
//    }
//    return "Not connected";
//}