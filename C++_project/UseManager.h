#pragma once
#include<string>
using namespace std;
class UseManager{
public:
    UseManager();
	~UseManager();

	bool registerUser(const string& username, const string& password);
	bool loginUser(const string& username, const string& password);
	bool userExists(const string& username);
};