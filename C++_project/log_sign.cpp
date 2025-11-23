#include "tool.h"
#include "UseManager.h"

// 在指定矩形内绘制（清空）并写入文本（用于输入区域）
static void draw_text_in_box(int x1, int y1, int x2, int y2, const string& text, bool hide = false) {
    // 清空内区（尽量与页面风格匹配，这里用深色填充）
    setfillcolor(0x0A0A0A); // 深色遮盖输入区
    solidrectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2);

    string disp = text;
    if (hide) {
        for (size_t i = 0; i < disp.size(); ++i) disp[i] = '*';
    }

    settextstyle(20, 0, "黑体");
    settextcolor(0xFFFFFF);
    // 文本起点偏移，可根据视觉微调
    outtextxy(x1 + 12, y1 + (y2 - y1) / 2 - 10, disp.c_str());
}

// 画输入框轮廓
static void draw_interface(const IMAGE& bg,
    const string& username, const string& password,
    int focus, // 0:none, 1:username, 2:password
    int ux1, int uy1, int ux2, int uy2,
    int px1, int py1, int px2, int py2,
    int bx1, int by1, int bx2, int by2,
    int mode /*1=login,2=register*/) 
{
    putimage(0, 0, &bg);

    // 输入框外框（白色细框）
    setlinecolor(0xCCCCCC);
    setlinestyle(PS_SOLID, 2);
    rectangle(ux1, uy1, ux2, uy2);
    rectangle(px1, py1, px2, py2);

    // 焦点用绿色框
    if (focus == 1) { setlinecolor(0x00FF00); rectangle(ux1 - 2, uy1 - 2, ux2 + 2, uy2 + 2); }
    if (focus == 2) { setlinecolor(0x00FF00); rectangle(px1 - 2, py1 - 2, px2 + 2, py2 + 2); }

    // 绘制当前文本
    draw_text_in_box(ux1, uy1, ux2, uy2, username, false);
    draw_text_in_box(px1, py1, px2, py2, password, true);

}

// 在矩形内编辑文本（阻塞，直到 Enter 或 Esc）
// 返回 true 表示用户按 Enter 提交，false 表示 Esc 取消（保持字符串原样）
static bool edit_field(string& field, int x1, int y1, int x2, int y2, bool hide) {
    // 编辑时简单使用控制台输入方式 _getch
    while (true) {
        int ch = _getch();
        if (ch == 13) { // Enter
            return true;
        } else if (ch == 27) { // Esc
            return false;
        } else if (ch == 8) { // Backspace
            if (!field.empty()) field.pop_back();
        } else if (ch >= 32 && ch <= 126) { // 常见可打印字符
            field.push_back((char)ch);
        }

        // 每次键入后，清空并绘制当前文本（直接在调用者的主循环中会重绘整个界面）
        setfillcolor(0x0A0A0A);
        solidrectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2);
        string disp = field;
        if (hide) for (size_t i = 0; i < disp.size(); ++i) disp[i] = '*';
        settextstyle(20, 0, "黑体");
        settextcolor(0xFFFFFF);
        outtextxy(x1 + 12, y1 + (y2 - y1) / 2 - 10, disp.c_str());
    }
}

static bool point_in_rect(int px, int py, int lx, int ty, int rx, int by) {
    return px >= lx && px <= rx && py >= ty && py <= by;
}

int Log_Sign(int count) {
    UseManager userManager;

    const char* bgPath = "D:\\VS文件\\project1\\C++_project\\picture\\map\\Log_sign1.png";
    IMAGE bg;
    loadimage(&bg, bgPath);

    const int ux1 = 480, uy1 = 260, ux2 = 720, uy2 = 290; // 用户名框
    const int px1 = 480, py1 = 348, px2 = 720, py2 = 378; // 密码框
    const int bx1 = 510, by1 = 430, bx2 = 695, by2 = 475; // 提交按钮

    string username;
    string password;
    int focus = 0; // 0:none,1:username,2:password

    // 首次绘制
    draw_interface(bg, username, password, focus, ux1, uy1, ux2, uy2, px1, py1, px2, py2, bx1, by1, bx2, by2, count);

    // 主循环：处理鼠标点击与编辑
    while (true) {
        ExMessage msg;
        if (peekmessage(&msg, EX_MOUSE)) {
            if (msg.message == WM_LBUTTONDOWN) {
                int mx = msg.x, my = msg.y;

                if (point_in_rect(mx, my, ux1, uy1, ux2, uy2)) {
                    focus = 1;
                    // 高亮并允许编辑；编辑函数会在屏幕上更新文本
                    draw_interface(bg, username, password, focus, ux1, uy1, ux2, uy2, px1, py1, px2, py2, bx1, by1, bx2, by2, count);
                    edit_field(username, ux1, uy1, ux2, uy2, false);
                    // 结束编辑后重绘
                    focus = 0;
                    continue;
                }

                if (point_in_rect(mx, my, px1, py1, px2, py2)) {
                    focus = 2;
                    draw_interface(bg, username, password, focus, ux1, uy1, ux2, uy2, px1, py1, px2, py2, bx1, by1, bx2, by2, count);
                    edit_field(password, px1, py1, px2, py2, true);
                    focus = 0;
                    continue;
                }

                // 点击提交按钮
                if (point_in_rect(mx, my, bx1, by1, bx2, by2)) {
                    // 简单校验非空，调用 UseManager
                    if (username.empty() || password.empty()) {
                        // 提示信息（短暂）：
                        settextstyle(18, 0, "黑体");
                        settextcolor(0xFFFF00);
                        outtextxy(bx1, by2 + 10, "用户名或密码不能为空");
                        Sleep(80);
                        draw_interface(bg, username, password, focus, ux1, uy1, ux2, uy2, px1, py1, px2, py2, bx1, by1, bx2, by2, count);
                        continue;
                    }

                    if (count == 1) { // 假定 main 中：1 = login
                        if (userManager.loginUser(username, password)) return 1;
                        // 失败提示
                        settextstyle(18, 0, "黑体");
                        settextcolor(0xFF6666);
                        outtextxy(bx1, by2 + 10, "登录失败");
                        Sleep(100);
                        draw_interface(bg, username, password, focus, ux1, uy1, ux2, uy2, px1, py1, px2, py2, bx1, by1, bx2, by2, count);
                        continue;
                    } else if (count == 2) { // 2 = register
                        if (userManager.registerUser(username, password)) return 2;
                        settextstyle(18, 0, "黑体");
                        settextcolor(0xFF6666);
                        outtextxy(bx1, by2 + 10, "注册失败");
                        Sleep(100);
                        draw_interface(bg, username, password, focus, ux1, uy1, ux2, uy2, px1, py1, px2, py2, bx1, by1, bx2, by2, count);
                        continue;
                    } else {
                        // 未知模式，直接返回 0
                        return 0;
                    }
                }
            }
        }
        Sleep(10);
    }

    return 0;
}