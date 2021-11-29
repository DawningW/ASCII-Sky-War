#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <stdbool.h>
#include "resources.h"

// �������ײ��
typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
} AABB;

// ͨ�������øö������ײ��
void getAABB(AABB* box, int x, int y, StrObject* obj);
// ����������ײ����(������)���е��ַ������
int checkProjectile(char* map, int n, AABB* box, char c); // map ��char[][n]
// ������������ײ��֮��(������)�Ƿ��ص�
bool checkCollision(AABB* b1, AABB* b2);

#endif // !__PHYSICS_H__
