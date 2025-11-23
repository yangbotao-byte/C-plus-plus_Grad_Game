#include"tool.h"
#include"class_sum.h"
#include"menthod.h"

int main() {
	initgraph(1200,600);
	MySQL_Driver_method();
	//计时器
	Timer log_timer;
	Timer load_timer;

	UI start_page(0, 0, 1200, 600, 600, 1200, "D:\\VS文件\\project1\\C++_project\\picture\\map\\start_page1.jpg");
	UI load_UI(100, 400, 227, 453, 53, 127, "D:\\VS文件\\project1\\C++_project\\picture\\UI\\load.png");
	UI log_UI(100, 500, 227, 553, 53, 127, "D:\\VS文件\\project1\\C++_project\\picture\\UI\\log.png");

	
	while (1) {
		if (!load_UI.msg_control() && !log_UI.msg_control()) {
			settextstyle(16, 0, "黑体");
			settextcolor(0x98FB98);
			BeginBatchDraw(); // 开始批量绘图
			cleardevice();
			start_page.put();
			load_UI.put();
			log_UI.put();
			outtextxy(900, 560, "database is creat successly! Ciallo~");
			outtextxy(900, 580, "database is link successly! Ciallo~");
			EndBatchDraw(); // 结束批量绘图，并一次性绘制到屏幕
			load_UI.get_son_message();
			log_UI.get_son_message();
		}

		if (load_UI.msg_control()) {
			cleardevice();
			Log_Sign(1);
			/*break;*/
		}

		if (log_UI.msg_control()) {
			cleardevice();
			Log_Sign(2);
			/*break;*/
		}
		// 这个会导致CPU死区，所以换用计时器
		/*Sleep(150);*/
		log_timer.Timer_clock(log_UI, 100);
		load_timer.Timer_clock(load_UI, 100);	
		if (log_timer.get_st() == 1) {
			cleardevice();
			Log_Sign(1);
		}
		else if (load_timer.get_st() == 1) {
			cleardevice();
			Log_Sign(2);
		}
	}
	return 0;
}


