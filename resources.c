#include "resources.h"
#include "lang_common.h"
#include "lang_en.h"

#include <stdlib.h>
#include <string.h>

// ´æ´¢×Ö·û´®/»­
struct StrObject* resources[COUNT];

// ¶ÁÈ¡×Ö·û´®/»­
struct StrObject* _readStrObj(const char** strarray, size_t width, size_t height)
{
    struct StrObject* newobj = malloc(sizeof(struct StrObject));
    if (newobj == NULL) return NULL;
    newobj->str = strarray;
    newobj->width = width;
    newobj->height = height;
    return newobj;
}
#define readStrObj(strarray) _readStrObj(strarray, strlen(strarray[0]), length(strarray))

void res_add(enum Resources id, struct StrObject* object)
{
    if (id < MISSINGNO || id >= COUNT) return;
    resources[id] = object;
}
#define res_add_auto(id) res_add(id, readStrObj(_##id))

struct StrObject* res_get(enum Resources id)
{
    if (id <= MISSINGNO || id >= COUNT) id = MISSINGNO;
    return resources[id];
}

void res_load()
{
    res_add_auto(MISSINGNO);

    res_add_auto(TITLE);
    res_add_auto(GAMEOVER);
    res_add_auto(PLANE);
    res_add_auto(PLANE2);
    res_add_auto(WCNB);

    res_add_auto(WEBSITE);

    res_add_auto(MENU);
    res_add_auto(BUTTONS);
    res_add_auto(DIFFICULTY);
    res_add_auto(HELP);
    res_add_auto(ABOUT);
    res_add_auto(STRINGS);

}

void res_unload()
{
    for (int i = 0; i < COUNT; ++i) free(resources[i]);
}
