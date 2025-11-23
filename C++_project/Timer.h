#pragma once
// 计时器的实现，使用sleep会导致阻塞线程
#include"UI.h"
class Timer {
private:
	int st;
public:
	Timer();
	~Timer() = default;

	int get_st() const { return st; }
	int Timer_clock(UI& UI_Timer, int time_limit);
};