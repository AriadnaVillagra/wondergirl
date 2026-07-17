#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>
#include "Animation.h"
#include "SpriteData.h"

class Sprite {
public:
  std::vector<SDL_FRect> source;
  SDL_FRect target;
  SDL_Texture *texture;
  std::vector<Animation> animation;
  int currentAnimation;
  void Render(SDL_Renderer *renderer);
  void Init(SpriteData &spriteData);
  void Update(float deltaT);
  void SetAnimation(const std::vector<int> &frames, float length, bool loop = true);
  void SetCurrentAnimation(int animationIndex);

  private:
  SDL_FRect* GetFrame();
};
