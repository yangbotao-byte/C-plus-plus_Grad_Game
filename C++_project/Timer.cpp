#include"Timer.h"
#include"tool.h"
#include"UI.h"

Timer::Timer() {
	this->st = 0;
}

int Timer::Timer_clock(UI& UI_Timer, int time_limit){
	// 使用高精度获取现在的时间
	auto start = high_resolution_clock::now();
	/*
	模板类函数
	duration_cast 时间类型转换函数
	milliseconds 毫秒
	这里实现了统一单位为毫秒
	*/
	while(duration_cast<milliseconds>(high_resolution_clock::now() - start).count() < time_limit) {
		/*
		   GetAsyncKeyState(VK_LBUTTON)返回1 0x8000 表示为 1000 0000 0000 0000
				   & 0x8000 是为了判断返回值是否为1
		*/
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			UI_Timer.get_son_message();
			if (UI_Timer.msg_control() == true) {
				while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					std::this_thread::sleep_for(milliseconds(1));
				}
				this->st = 1;
				return 1;
			}
		}

		// 降低 CPU 占用
		std::this_thread::sleep_for(milliseconds(10));
		this->st = 0;
	}
	return 0;
}
