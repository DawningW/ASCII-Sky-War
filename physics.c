#include "physics.h"

void getAABB(struct AABB* box, int x, int y, struct StrObject* obj)
{
    box->x1 = x - obj->width / 2;
    box->y1 = y - obj->height / 2;
    box->x2 = box->x1 + obj->width - 1;
    box->y2 = box->y1 + obj->height - 1;
}

int checkBullet(char bullets[][WIDTH], struct AABB* box, char bullet)
{
    int count = 0;
    for (int y = box->y1; y <= box->y2; ++y)
    {
        for (int x = box->x1; x <= box->x2; ++x)
        {
            if (bullets[y][x] == bullet)
            {
                bullets[y][x] = ' ';
                ++count;
            }
        }
    }
    return count;
}

int checkCollision(struct AABB* b1, struct AABB* b2)
{
    return b1->x1 <= b2->x2 && b1->x2 >= b2->x1 && b1->y1 <= b2->y2 && b1->y2 >= b2->y1;
}
