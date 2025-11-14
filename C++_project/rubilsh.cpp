//#include <jdbc/cppconn/statement.h>
//#include <jdbc/cppconn/resultset.h>
//#include <jdbc/cppconn/exception.h>
//#include "jdbc/mysql_driver.h"
//#include<windows.h>
//#include<iostream>
//int main() {
//    std::string sql1 = "create database testmysql11";//sql1用于创建testmysql数据库
//    SetConsoleOutputCP(CP_UTF8);
//    try
//    {
//        // 注册MySQL驱动程序
//        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
//        sql::Connection* con;
//        sql::Statement* stmt;
//        sql::ResultSet* res;
//        //获取数据库连接对象
//        con = driver->connect("tcp://localhost:3306", "root", "123456");
//        //获取执行语句对象
//        stmt = con->createStatement();
//        stmt->execute(sql1);
//        delete stmt;
//        delete con;
//    }
//    catch (sql::SQLException& sqle)
//    {
//        std::cout << "error" << std::endl;
//    }
//    return 0;
//}
//




//#include "MySQLDriver.h"
//#include <iostream>
//#include <memory>
//
//int main() {
//    // 创建MySQL驱动器实例
//    MySQLDriver mysql;
//
//    // 连接数据库（不指定具体数据库）
//    if (mysql.connect("localhost", "root", "123456")) {
//        std::cout << "成功连接到MySQL服务器" << std::endl;
//
//        // 创建数据库
//        if (mysql.createDatabase("testmysql11")) {
//            std::cout << "成功创建数据库 testmysql11" << std::endl;
//        }
//        else {
//            std::cout << "创建数据库失败: " << mysql.getLastError() << std::endl;
//        }
//
//        // 使用新创建的数据库
//        if (mysql.useDatabase("testmysql11")) {
//            std::cout << "成功切换到数据库 testmysql11" << std::endl;
//
//            // 创建表
//            std::string createTableSQL =
//                "CREATE TABLE IF NOT EXISTS users ("
//                "id INT AUTO_INCREMENT PRIMARY KEY, "
//                "name VARCHAR(100) NOT NULL, "
//                "email VARCHAR(100) NOT NULL)";
//
//            if (mysql.execute(createTableSQL)) {
//                std::cout << "成功创建表 users" << std::endl;
//            }
//
//            // 插入数据
//            std::string insertSQL =
//                "INSERT INTO users (name, email) VALUES "
//                "('张三', 'zhangsan@example.com'), "
//                "('李四', 'lisi@example.com')";
//
//            if (mysql.execute(insertSQL)) {
//                std::cout << "成功插入数据" << std::endl;
//            }
//
//            // 查询数据
//            auto result = mysql.executeQuery("SELECT * FROM users");
//            if (result) {
//                std::cout << "查询结果:" << std::endl;
//                while (result->next()) {
//                    std::cout << "ID: " << result->getInt("id")
//                        << ", Name: " << result->getString("name")
//                        << ", Email: " << result->getString("email")
//                        << std::endl;
//                }
//            }
//        }
//
//        // 断开连接
//        mysql.disconnect();
//        std::cout << "已断开数据库连接" << std::endl;
//
//    }
//    else {
//        std::cout << "连接失败: " << mysql.getLastError() << std::endl;
//    }
//
//    return 0;
//}
