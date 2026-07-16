#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "Animation.h"

class Sprite {
public:
  SDL_FRect source[24];
  SDL_FRect target;
  SDL_Texture *texture;
  std::vector<Animation> animation;
  int currentAnimation;
  void Render(SDL_Renderer *renderer);
  void Init(SDL_Texture* SdlTexture);
  void Update(float deltaT);
  void SetAnimation(const std::vector<int> &frames, float length, bool loop = true);
  void SetCurrentAnimation(int animationIndex);
};
