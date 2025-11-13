#include"UI.h"

/* 运用初始化列表的性能更快 */
UI::UI(int left_top_x, int left_top_y, int right_top_x, int right_top_y, int height, int width, string address)
    : left_top_x(left_top_x), left_top_y(left_top_y),
    right_top_x(right_top_x), right_top_y(right_top_y) {

    loadimage(&UI_image, address.c_str(), width, height);
    

}


/*对于基本数据类型和IMAGE类型的变量，一般不需要自己手动释放，只有自己动态内存分配的时候才要*/
UI::~UI(){

}

tuple<int, int, int, int> UI::get_son_message() const {
    cout << left_top_x << endl;
    cout << left_top_y << endl;
    cout << right_top_x << endl;
    cout << right_top_y << endl;
	return make_tuple(left_top_x, left_top_y, right_top_x, right_top_y);
}

void UI::put() {
    setlinecolor(GREEN);
    putimage(left_top_x, left_top_y, &UI_image);
    rectangle(this->left_top_x, this->left_top_y, this->right_top_x, this->right_top_y);
}   