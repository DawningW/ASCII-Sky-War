#ifndef __INPUT_H__
#define __INPUT_H__

#if defined(_WIN32) || defined(_WIN64)
#define PDC_NCMOUSE
#include <PDCurses/curses.h>
#else
#include <ncurses.h>
#endif

// ����״̬�ṹ��
typedef struct
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
} Key;

// ��ǰ����״̬
extern Key key;
extern MEVENT mevent;
// TODO ��갴��ʾ�� mevent.bstate & BUTTON1_CLICKED

void input_init();
void input_mode(bool mode);
void input_handle();
int input_getch();
#define input_scan(x, y, fmt, ...) mvwscanw(stdscr, y, x, fmt, ##__VA_ARGS__)

#endif // __INPUT_H__
