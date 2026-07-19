#include "CollisionSystem.h"
#include "ColBox.h"
#include <algorithm>

bool CollisionSystem::CheckCollision(ColBox &box1, ColBox &box2)
{
    return box1.x < box2.x + box2.w &&
            box1.x + box1.w > box2.x &&
            box1.y < box2.y + box2.h &&
            box1.y + box1.h > box2.y;
}

void CollisionSystem::CheckAllCollisions()
{
    for (ColBox* box1 : group1)
    {
        for (ColBox* box2 : group2)
        {
            if (CheckCollision(*box1, *box2))
            {
                box1->OnCollision(*box2);
                box2->OnCollision(*box1);   
            }
        }
    }
}

void CollisionSystem::AddToGroup1(ColBox* box)
{
    group1.push_back(box);
}

void CollisionSystem::AddToGroup2(ColBox* box)
{
    group2.push_back(box);
}

void CollisionSystem::RemoveFromGroup1(ColBox* box)
{
    group1.erase(std::remove(group1.begin(), group1.end(), box), group1.end());
}

void CollisionSystem::RemoveFromGroup2(ColBox* box)
{
    group2.erase(std::remove(group2.begin(), group2.end(), box), group2.end());
}