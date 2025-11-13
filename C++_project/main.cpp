#include"tool.h"
#include"class_sum.h"

int main() {

	initgraph(1200,600);
	UI start_page(0, 0, 1200, 600, 600, 1200, "D:\\VS文件\\project1\\C++_project\\picture\\map\\start_page1.jpg");
	UI load_UI(100, 400, 227, 453, 53, 127, "D:\\VS文件\\project1\\C++_project\\picture\\UI\\load.png");
	UI log_UI(100, 500, 227, 553, 53, 127, "D:\\VS文件\\project1\\C++_project\\picture\\UI\\log.png");
	//UI log_UI(0, 0, 1200, 600, 600, 1200, "D:\\VS文件\\project1\\C++_project\\picture\\map\\start_page1.jpg");

	start_page.put();
	load_UI.put();
	log_UI.put();
	load_UI.get_son_message();
	log_UI.get_son_message();
	
	while (1) {
		if (!load_UI.msg_control() && log_UI.msg_control()) {
			cleardevice();
			start_page.put();
			load_UI.put();
			log_UI.put();
			load_UI.get_son_message();
			log_UI.get_son_message();
			Sleep(100);
		}

		if (load_UI.msg_control()) {
			cleardevice();
			break;
		}

		if (log_UI.msg_control()) {
			cleardevice();
			break;
		}
	}
	return 0;
}