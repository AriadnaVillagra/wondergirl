#pragma once

#include <vector>
#include "Defines.h"


class ColBox
{
public: 
float x, y, h, w;
void OnCollision(ColBox &other);
std::vector<ColBox*> collisionList;
EntityType entityType;
};