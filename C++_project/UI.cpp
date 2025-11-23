#include "UI.h"

UI::UI(int left_top_x, int left_top_y, int right_top_x, int right_top_y, int height, int width, string address)
    : left_top_x(left_top_x), left_top_y(left_top_y),
      right_top_x(right_top_x), right_top_y(right_top_y),
      height(height), width(width)
{
    // 假定 loadimage 接受 const char*
    loadimage(&UI_image, address.c_str());
}

UI::~UI() {
}

tuple<int, int, int, int> UI::get_son_message() const {
    return make_tuple(left_top_x, left_top_y, right_top_x, right_top_y);
}

void UI::put() {
    // 根据需要在此实现绘制逻辑，例如 putimage 等
     putimage(left_top_x, left_top_y, &UI_image);

     // 使用绿色方框将图片圈出
     // 使用成员 width 和 height 计算图片右下角坐标
     // RGB(0,255,0) 为纯绿色
     setlinecolor(RGB(0, 255, 0));
     rectangle(left_top_x, left_top_y, left_top_x + width, left_top_y + height);
}