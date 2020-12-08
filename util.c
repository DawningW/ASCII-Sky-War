#include "util.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <unistd.h>
#endif

long util_getCurrentTime()
{
    return 1000 * clock() / CLOCKS_PER_SEC;
}

void util_sleep(long time)
{
#if defined(_WIN32) || defined(_WIN64)
    Sleep(time);
#else
    usleep(time * 1000);
#endif
}

void util_openBrowser(const char* url)
{
#if defined(_WIN32) || defined(_WIN64)
    // ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    char command[50] = "start ";
#else
    // system("/bin/sh -c chromium-browser");
    char command[50] = "xdg-open ";
#endif
    system(strcat(command, url));
}
