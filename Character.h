#pragma once
#include "Sprite.h"

class Character {
public:
  Sprite sprite;
  float x;
  float y;
  void Init(SDL_Texture *SdlTexture);
  void Render(SDL_Renderer *Renderer);
  void Update(float DeltaTime);
  void MoveLeft();
  void MoveRight();
};
