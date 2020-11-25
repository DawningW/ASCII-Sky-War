#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "resources.h"

// TODO 宽度硬编码
#define WIDTH 60

// 轴对齐碰撞箱
struct AABB
{
    int x1;
    int y1;
    int x2;
    int y2;
};

// 通过坐标获得该对象的碰撞箱
void getAABB(struct AABB* box, int x, int y, struct StrObject* obj);
// 检测给定的两端点之间(闭区间)所有的子弹并清除
int checkBullet(char bullets[][WIDTH], struct AABB* box, char bullet);
// 检测给定的两碰撞箱之间(闭区间)是否重叠
int checkCollision(struct AABB* b1, struct AABB* b2);

#endif // !__PHYSICS_H__
