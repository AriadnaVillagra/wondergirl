#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Sprite {
public:
  SDL_FRect source[24];
  SDL_FRect target;
  SDL_Texture *texture;
  float animationTime;
  int currentFrame = 0;
  void Render(SDL_Renderer *renderer);
  void Init(SDL_Texture* SdlTexture);
  void Update(float deltaT);
};
