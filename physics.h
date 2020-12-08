#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <stdbool.h>
#include "resources.h"

// 轴对齐碰撞箱
typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
} AABB;

// 通过坐标获得该对象的碰撞箱
void getAABB(AABB* box, int x, int y, StrObject* obj);
// 检测给定的碰撞箱内(闭区间)所有的字符并清除
int checkProjectile(char* map, int n, AABB* box, char c); // map 是char[][n]
// 检测给定的两碰撞箱之间(闭区间)是否重叠
bool checkCollision(AABB* b1, AABB* b2);

#endif // !__PHYSICS_H__
