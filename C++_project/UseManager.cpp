#include"UseManager.h"
#include"tool.h"

UseManager::UseManager(){
}

UseManager::~UseManager(){
}

bool UseManager::registerUser(const string& username, const string& password){
	if (userExists(username)) {
		return false;
	}

	// 单例模式
	string insertSQL = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
	MySQL_engine.execute(insertSQL);
	return true; // 示例返回值
}


// 改进前的代码，存在SQL注入风险
// SELECT * FROM users WHERE username = 'admin' -- ' AND password = 'xxx'
// 直接后面的密码被注释掉了，导致任何密码都能登录成功

bool UseManager::loginUser(const string& username, const string& password){

	std::string sql = "SELECT * FROM users WHERE username = '" + username +
		"' AND password = '" + password + "'";

	// 这里执行的是精准查询，where已经过滤掉了很多不符合的数据
	// 然后这里result一开始指向的是第0行，由于我们精准查询，然后只需要调用一次next()
	/*
	   结果集：
		+ ---- + ---------- + ---------- +
		| id | username | password | ← 游标初始位置（第0行）
		+ ---- + ---------- + ---------- +
		| 1 | john | 123456 | ← 实际匹配的数据（第1行）
		+ ---- + ---------- + ---------- +
	*/

    // 如果不是精准查询，那么就需要调用多次next()

	auto result = MySQL_engine.executeQuery(sql);
	return result && result->next();  // 如果有结果，说明登录成功

	return true; // 示例返回值
}

bool UseManager::userExists(const string& username){
	string sql = "SELECT * FROM users WHERE username = '" + username + "'";
	auto result = MySQL_engine.executeQuery(sql);

	// 这里也是精准查询，只需要调用一次next()
	return result && result->next();
	return false; // 示例返回值
}