#include "renderer.h"

#include <stdlib.h>
#include <math.h>

// TODO 游戏中使用子窗口
void renderer_init()
{
#if defined(_WIN32) || defined(_WIN64)
    system("mode con cols=80 lines=40");
#endif
    initscr();
    start_color();
    intrflush(stdscr, FALSE);
    curs_set(0);
    noecho();
    nonl();
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    // Colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
}

void renderer_end()
{
    endwin();
}

void renderer_clear()
{
    clear();
}

void renderer_drawBox()
{
    box(stdscr, ACS_VLINE, ACS_HLINE);
}

void renderer_drawHorizontalLine(int x, int y, int n)
{
    mvwhline(stdscr, y, x, '-', n);
}

void renderer_drawVerticalLine(int x, int y, int n)
{
    mvwvline(stdscr, y, x, '|', n);
}

void renderer_drawChar(int x, int y, char c)
{
    mvwaddch(stdscr, y, x, c);
}

void renderer_drawStr(int x, int y, const char* str)
{
    mvwaddstr(stdscr, y, x, str);
}

void renderer_drawStrObj(int x, int y, struct StrObject* obj)
{
    for (unsigned char i = 0; i < obj->height; ++i)
    {
        renderer_drawStr(x, y + i, obj->str[i]);
    }
}

void renderer_drawButton(int x, int y, const char* str, char checked)
{
    if (checked) attron(A_REVERSE);
    renderer_drawStr(x, y, str);
    if (checked) attroff(A_REVERSE);
}

void renderer_drawProgress(int x, int y, int n, double progress)
{
    n = (int) ceil(n * progress);
    for (int i = 0; i < n; ++i)
    {
        renderer_drawChar(x + i, y, '|');
    }
}

void renderer_refresh()
{
    refresh();
}
