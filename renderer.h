#ifndef __RENDERER_H__
#define __RENDERER_H__

#if defined(_WIN32) || defined(_WIN64)
#define PDC_WIDE
#include <PDCurses/curses.h>
#include <PDCurses/curspriv.h>
#else
#include <ncurses.h>
#endif
#include "resources.h"

void renderer_init();
void renderer_end();

void renderer_clear();
void renderer_drawBox();
void renderer_drawHorizontalLine(int x, int y, int n);
void renderer_drawVerticalLine(int x, int y, int n);
void renderer_drawChar(int x, int y, char c);
void renderer_drawWideChar(int x, int y, wchar_t wc);
void renderer_drawStr(int x, int y, const char* str);
#define renderer_drawStrCenter(x, y, str) renderer_drawStr(x - strlen(str) / 2, y, str)
void renderer_drawStrObj(int x, int y, struct StrObject* obj);
#define renderer_drawStrObjCenter(x, y, obj) renderer_drawStrObj(x - obj->width / 2, y - obj->height / 2, obj)
void renderer_drawButton(int x, int y, const char* str, char checked);
#define renderer_drawButtonCenter(x, y, str, checked) renderer_drawButton(x - strlen(str) / 2, y, str, checked)
void renderer_drawProgress(int x, int y, int n, double progress);
#define renderer_printStr(x, y, str, ...) mvwprintw(stdscr, y, x, str, ##__VA_ARGS__)
void renderer_refresh();

void renderer_setWindowTitle(const char* title);
void renderer_setWindowSize(int lines, int cols);

#endif // !__RENDERER_H__
