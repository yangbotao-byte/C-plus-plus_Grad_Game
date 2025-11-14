#include"operator.h"
/*
    promble1:
      如果我想用孩子的属性返回到父亲的方法里面用于判断，我该怎么处理
    answer1:
      使用虚函数进行解决。
*/

control::control() {

}

control::~control() {

}


bool control::msg_control() {
    // 使用peekmessage获取鼠标消息，不阻塞
    if (peekmessage(&msg, EX_MOUSE)) {
         //检查是否是左键按下
        if (msg.message == WM_LBUTTONDOWN) {
            cout << msg.x << " " << msg.y << endl;

            tuple<int, int, int, int> son_squar = get_son_message();

            /* 获取每一个元组的元素 */
            int left = get<0>(son_squar);
            int top = get<1>(son_squar);
            int right = get<2>(son_squar);
            int bottom = get<3>(son_squar);

            // 判断点击是否在矩形区域内
            if (msg.x >= left && msg.x <= right && msg.y >= top && msg.y <= bottom) {
                /*outtextxy(100, 100, _T("Hello welcome game!"));*/
                return true;
            }
        }
    }
    return false; // 如果没有点击或者点击不在区域内，返回false
}

tuple<int, int, int, int> control::get_son_message() const {
    return make_tuple(0,0,0,0);
}