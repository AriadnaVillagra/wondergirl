#pragma once
#include <vector>

class ColBox; // Forward declaration of ColBox

class CollisionSystem
{
private:

public:
bool CheckCollision(ColBox &box1, ColBox &box2);
std::vector<ColBox*> group1;
std::vector<ColBox*> group2;
void CheckAllCollisions();
void AddToGroup1(ColBox* box);
void AddToGroup2(ColBox* box);
void RemoveFromGroup1(ColBox* box);
void RemoveFromGroup2(ColBox* box);
};


