#ifndef __WEBHELPER_H__
#define __WEBHELPER_H__

#include <cJSON/cJSON.h>
#include <curl/curl.h>

char* util_httpget(const char*);
char* util_httppost(const char*, const char*);

#endif // __WEBHELPER_H__
