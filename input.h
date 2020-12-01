#ifndef __INPUT_H__
#define __INPUT_H__

// 按键状态结构体
struct Key
{
    unsigned int esc;
    unsigned int enter;
    unsigned int backspace;
    unsigned int up;
    unsigned int left;
    unsigned int down;
    unsigned int right;
    unsigned int space;
    unsigned int w;
    unsigned int a;
    unsigned int s;
    unsigned int d;
    unsigned int j;
    unsigned int k;
};

// 当前按键状态
extern struct Key key;

void input_init();
void input_mode(char mode);
void input_handle();
int input_getch();
#define input_scan(x, y, fmt, ...) mvwscanw(stdscr, y, x, fmt, ##__VA_ARGS__)

#endif // __INPUT_H__
