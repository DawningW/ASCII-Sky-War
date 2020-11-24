#include "input.h"

#include <stdio.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
#include <PDCurses/curses.h>
#include <Windows.h>
#include <WinUser.h>
#define ISKEYDOWN(key) ((GetKeyState(key) & 0x8000) ? 1 : 0)
HWND hWnd;
#else
#include <ncurses.h>
#define PADENTER 13
#endif

int lastkey;
struct Key key;

void input_init()
{
#if defined(_WIN32) || defined(_WIN64)
    hWnd = GetConsoleWindow();
#endif
    lastkey = -1;
    memset(&key, 0, sizeof(key));
}

void input_handle()
{
#if defined(_WIN32) || defined(_WIN64)
    if (GetForegroundWindow() != hWnd) return;
    if (ISKEYDOWN(VK_ESCAPE)) ++key.esc;
    else key.esc = 0;
    if (ISKEYDOWN(VK_RETURN)) ++key.enter;
    else key.enter = 0;
    if (ISKEYDOWN(VK_BACK)) ++key.backspace;
    else key.backspace = 0;
    if (ISKEYDOWN(VK_UP)) ++key.up;
    else key.up = 0;
    if (ISKEYDOWN(VK_LEFT)) ++key.left;
    else key.left = 0;
    if (ISKEYDOWN(VK_DOWN)) ++key.down;
    else key.down = 0;
    if (ISKEYDOWN(VK_RIGHT)) ++key.right;
    else key.right = 0;
    if (ISKEYDOWN(VK_SPACE)) ++key.space;
    else key.space = 0;
    if (ISKEYDOWN('W')) ++key.w;
    else key.w = 0;
    if (ISKEYDOWN('A')) ++key.a;
    else key.a = 0;
    if (ISKEYDOWN('S')) ++key.s;
    else key.s = 0;
    if (ISKEYDOWN('D')) ++key.d;
    else key.d = 0;
    if (ISKEYDOWN('J')) ++key.j;
    else key.j = 0;
    if (ISKEYDOWN('K')) ++key.k;
    else key.k = 0;
    lastkey = getch();
#else
    int currentkey = getch();
    if (lastkey != currentkey) memset(&key, 0, sizeof(key));
    if (currentkey == 27) ++key.esc;
    else if (currentkey == 13 || currentkey == PADENTER || currentkey == KEY_ENTER) ++key.enter;
    else if (currentkey == 8 || currentkey == 127 || currentkey == KEY_BACKSPACE) ++key.backspace;
    else if (currentkey == KEY_UP) ++key.up;
    else if (currentkey == KEY_LEFT) ++key.left;
    else if (currentkey == KEY_DOWN) ++key.down;
    else if (currentkey == KEY_RIGHT) ++key.right;
    else if (currentkey == ' ') ++key.space;
    else if (currentkey == 'w') ++key.w;
    else if (currentkey == 'a') ++key.a;
    else if (currentkey == 's') ++key.s;
    else if (currentkey == 'd') ++key.d;
    else if (currentkey == 'j') ++key.j;
    else if (currentkey == 'k') ++key.k;
    lastkey = currentkey;
#endif
    // «Âø’ ‰»Îª∫≥Â«¯
    fflush(stdin);
}

int input_getch()
{
    return lastkey;
}
