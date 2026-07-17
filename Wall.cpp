#include "Wall.h"

void Wall::Init(SpriteData &spriteData, float startPosX, float startPosY)
{
    x = startPosX;
    y = startPosY;
    sprite.Init(spriteData);

}

void Wall::Render(SDL_Renderer *Renderer)
{
    sprite.Render(Renderer);
}

void Wall::Update(float DeltaTime)
{
    UpdateSprite(DeltaTime);
}

void Wall::UpdateSprite(float DeltaTime)
{
    sprite.Update(DeltaTime);
    sprite.target.x = x;
    sprite.target.y = y;

}
