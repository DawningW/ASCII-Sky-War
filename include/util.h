#ifndef __UTIL_H__
#define __UTIL_H__

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define randInt(a, b) a + rand() % (b - a)

// ºÁÃë
long util_getCurrentTime();
void util_sleep(long);
void util_openBrowser(const char*);

#endif // !__UTIL_H__
