#include"tool.h"
#include"MySQL_Engine.h"

void  MySQL_Driver_method(){
	MySQLDriver MySQL_engine;

	string host = "localhost:3306";
	string user = "root";
	string password = "123456";
	string database = "cardgame_database";

	// 注意connect只可以连接已有的数据库，所以需要再次之前建立数据库
	if (!MySQL_engine.connect(host, user, password, database)) {
		string meg_error = "数据库连接失败:  " + MySQL_engine.getLastError();
		outtextxy(100, 100, meg_error.c_str()); // outtextxy 支持 const char*
		system("pause");
		return;
	}
	
}