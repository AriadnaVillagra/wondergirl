#include "Wall.h"
#include "CollisionSystem.h"

void Wall::Init(SpriteData &spriteData, float startPosX, float startPosY, CollisionSystem &collisionSystem)
{
    colBox.entityType = EntityType::Wall;

    x = startPosX;
    y = startPosY;

    colBox.x = x;
    colBox.y = y;

    colBox.w = 100;
    colBox.h = 80;

    this->collisionSystem = &collisionSystem;
    collisionSystem.AddToGroup2(&colBox);
    sprite.Init(spriteData);

}

Wall::~Wall()
{
    if (collisionSystem)
    {
        collisionSystem->RemoveFromGroup2(&colBox);
    }
}

void Wall::Render(SDL_Renderer *Renderer)
{
    sprite.Render(Renderer);
}

void Wall::Update(float DeltaTime)
{
    UpdateSprite(DeltaTime);
    UpdateColBox();
    colBox.collisionList.clear(); // Clear the collision list after handling
}

void Wall::UpdateSprite(float DeltaTime)
{
    sprite.Update(DeltaTime);
    sprite.target.x = x;
    sprite.target.y = y;

}

void Wall::UpdateColBox()
{
    colBox.x = x;
    colBox.y = y;
}
