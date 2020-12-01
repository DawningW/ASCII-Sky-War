#include "renderer.h"

#include <stdlib.h>
#include <math.h>

// TODO 游戏中使用子窗口
void renderer_init()
{
    initscr();
    start_color();
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
#if defined(_WIN32) || defined(_WIN64)
    if (is_termresized())
    {
        resize_term(0, 0);
        curs_set(0);
    }
#endif
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

void renderer_drawWideChar(int x, int y, wchar_t wc)
{
    mvwaddch(stdscr, y, x, wc);
    mvwaddch(stdscr, y, x + 1, L' ');
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

void renderer_setWindowTitle(const char* title)
{
#if defined(_WIN32) || defined(_WIN64)
    PDC_set_title(title);
#endif
}

void renderer_setWindowSize(int lines, int cols)
{
#if defined(_WIN32) || defined(_WIN64)
    char command[30];
    sprintf(command, "mode con cols=%d lines=%d", cols, lines);
    system(command);
#else
    resize_term(lines, cols);
#endif
}
