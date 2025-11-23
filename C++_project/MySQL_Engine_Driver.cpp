#include"tool.h"
#include"MySQL_Engine.h"
MySQLDriver MySQL_engine;

void  MySQL_Driver_method(){

	string host = "localhost:3306";
	string user = "root";
	string password = "123456";
	string database = "cardgame_database";

	// 注意connect只可以连接已有的数据库，所以需要再次之前建立数据库
	if (!MySQL_engine.connect(host, user, password, database)) {
		string meg_error = "数据库连接失败:  " + MySQL_engine.getLastError();
		outtextxy(100, 100, meg_error.c_str()); // outtextxy 支持 const char*
		return;
	}

	// 创建用户表的SQL语句
	// id int 自动增加位数 主键
	// username char类型 唯一且不非空
	// password char类型 不非空
	// created_at 时间戳 默认当前时间
	string createTableSQL = R"(
	CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL
	) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
)";

	if (!MySQL_engine.execute(createTableSQL)) {
		std::cerr << "Create table failed. Check previous error output." << std::endl;
	}
	
}