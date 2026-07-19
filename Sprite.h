#pragma once

#include <SDL3/SDL_rect.h>
#include <vector>
#include "Animation.h"
#include "SpriteData.h"

struct SDL_Renderer; // Forward declaration of SDL_Renderer
struct SDL_Texture;  // Forward declaration of SDL_Texture

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
