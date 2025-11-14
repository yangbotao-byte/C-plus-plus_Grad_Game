#pragma once
#include"Operator.h"

/* 继承操作 */
class UI:public control{
private:
	IMAGE UI_image;
	int left_top_x;
	int left_top_y;
	int right_top_x;
	int right_top_y;
	int height;
	int width;

public:
	UI(int left_top_x, int left_top_y, int right_top_x, int right_top_y, int height, int width, string address);
	~UI();

	void put();
	/* override 是用来检查虚函数的重写是否对应 */
	tuple<int, int, int, int> get_son_message() const override;

};