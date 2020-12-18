#include "physics.h"

void getAABB(AABB* box, int x, int y, StrObject* obj)
{
    box->x1 = x - obj->width / 2;
    box->y1 = y - obj->height / 2;
    box->x2 = box->x1 + obj->width - 1;
    box->y2 = box->y1 + obj->height - 1;
}

int checkProjectile(char* map, int n, AABB* box, char c)
{
    int count = 0;
    for (int y = box->y1; y <= box->y2; ++y)
    {
        for (int x = box->x1; x <= box->x2; ++x)
        {
            if (*(map + y * n + x) == c)
            {
                *(map + y * n + x) = ' ';
                ++count;
            }
        }
    }
    return count;
}

bool checkCollision(AABB* b1, AABB* b2)
{
    return b1->x1 <= b2->x2 && b1->x2 >= b2->x1 && b1->y1 <= b2->y2 && b1->y2 >= b2->y1;
}
