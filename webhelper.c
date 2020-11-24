#include "webhelper.h"

#include <stdlib.h>
#include <string.h>

struct StringMemory
{
    size_t size;
    char* string;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t realsize = size * nmemb;
    struct StringMemory* mem = (struct StringMemory*) userp;
    char* ptr = realloc(mem->string, mem->size + realsize + 1);
    if (!ptr) {
        // �ڴ治��
        fprintf(stderr, "Error: no enough memory.\n");
        return 0;
    }
    mem->string = ptr;
    memcpy(&(mem->string[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->string[mem->size] = 0;
    return realsize;
}

char* util_httpget(const char* url)
{
    return util_httppost(url, NULL);
}

char* util_httppost(const char* url, const char* fields)
{
    struct StringMemory chunk = { 0, malloc(1) };
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode code;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        if (fields != NULL)
        {
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &chunk);
        code = curl_easy_perform(curl);
        if (code != CURLE_OK)
        {
            fprintf(stderr, "Error: http failed: %s.\n", curl_easy_strerror(code));
            free(chunk.string);
            return NULL;
        }
        curl_easy_cleanup(curl);
    }
    return chunk.string;
}