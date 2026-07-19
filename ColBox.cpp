#include "ColBox.h"

void ColBox::OnCollision(ColBox &other)
{
collisionList.push_back(&other);
}