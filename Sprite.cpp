#include "Sprite.h"
void Sprite::Render(SDL_Renderer *renderer) {
  target.h = 100;
  target.w = 100;
  //target.x = 500 - target.w / 2;
  //target.y = 800 - target.h;
  SDL_RenderTexture(renderer, texture, &source[animation[currentAnimation].GetCurrentFrame()], &target);
}
constexpr float animationSpeed = 0.1f;

void Sprite::Init(SDL_Texture *SdlTexture) {
texture = SdlTexture;
const int height = texture->h / 4;
const int width = texture->w / 6;

  for (int i = 0; i < 24; ++i) {
    source[i].x = (i % 6) * width;
    source[i].y = (i / 6) * height;
    source[i].h = height;
    source[i].w = width;
  }
}

void Sprite::Update(float deltaT) {
  animation[currentAnimation].Update(deltaT);
}

void Sprite::SetAnimation(const std::vector<int> &frames, float length, bool loop)
{
  Animation newAnimation;
  newAnimation.Init(frames, length, loop);
  animation.push_back(newAnimation);  
}

void Sprite::SetCurrentAnimation(int animationIndex)
{
  if (animationIndex >= 0 && animationIndex < animation.size())
  {
      currentAnimation = animationIndex;
  }
}
