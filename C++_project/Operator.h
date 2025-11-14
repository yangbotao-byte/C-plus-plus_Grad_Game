#pragma once
#include"tool.h"
using namespace std;

class control{
public:
	ExMessage msg;

public:
	control();
	~control();
	bool msg_control();

protected:
	/* 设计在这里的原因是只是在子类和父类之间调用 */
	virtual tuple<int, int, int, int> get_son_message() const = 0;

};