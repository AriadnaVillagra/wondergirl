#pragma once

#include "Sprite.h"
#include "ColBox.h"

class CollisionSystem; // Forward declaration of CollisionSystem
struct SDL_Renderer;

class Wall{
public:

~Wall();
void Init(SpriteData &spriteData, float startPosX, float startPosY, CollisionSystem &collisionSystem);
void Render(SDL_Renderer *Renderer);
void Update(float DeltaTime);

private:
    ColBox colBox;
    Sprite sprite;
    CollisionSystem *collisionSystem = nullptr;
    float x;
    float y;
    void UpdateSprite(float DeltaTime);
    void UpdateColBox();
};
 
