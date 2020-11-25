#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "resources.h"

// TODO ���Ӳ����
#define WIDTH 60

// �������ײ��
struct AABB
{
    int x1;
    int y1;
    int x2;
    int y2;
};

// ͨ�������øö������ײ��
void getAABB(struct AABB* box, int x, int y, struct StrObject* obj);
// �����������˵�֮��(������)���е��ӵ������
int checkBullet(char bullets[][WIDTH], struct AABB* box, char bullet);
// ������������ײ��֮��(������)�Ƿ��ص�
int checkCollision(struct AABB* b1, struct AABB* b2);

#endif // !__PHYSICS_H__
