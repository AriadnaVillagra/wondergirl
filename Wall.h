#pragma once

#include "Sprite.h"

class Wall{     
public:

void Init(SpriteData &spriteData, float startPosX, float startPosY);
void Render(SDL_Renderer *Renderer);
void Update(float DeltaTime);

private:
    Sprite sprite;
    float x;
    float y;
    void UpdateSprite(float DeltaTime);
};
 
