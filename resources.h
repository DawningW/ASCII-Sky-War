#ifndef __RESOURCES_H__
#define __RESOURCES_H__

// �������鳤��
#define length(arr) sizeof(arr) / sizeof(arr[0])

// �洢�ַ���/���Ľṹ��
struct StrObject
{
    const char** str;
    int width;
    int height;
};
// TODO ͸������

// ��Դö��
enum Resources
{
    // ��ʧ
    MISSINGNO,
    
    // �ַ���
    TITLE,
    GAMEOVER,
    PLANE,
    PLANE2,
    WCNB,
    
    // �ַ���
    WEBSITE,

    MENU,
    BUTTONS,
    DIFFICULTY,
    HELP,
    ABOUT,
    STRINGS,

    // ö��Ԫ������
    COUNT
};

void res_add(enum Resources, struct StrObject*);
struct StrObject* res_get(enum Resources);
void res_load();
void res_unload();

#endif // !__RESOURCES_H__
