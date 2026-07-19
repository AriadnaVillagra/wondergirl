#include "Sprite.h"
#include <SDL3/SDL_render.h>

void Sprite::Render(SDL_Renderer *renderer) {
  target.h = 100;
  target.w = 100;
  //target.x = 500 - target.w / 2;
  //target.y = 800 - target.h;
  SDL_RenderTexture(renderer, texture, GetFrame(), &target);
}
constexpr float animationSpeed = 0.1f;

void Sprite::Init(SpriteData &spriteData) {
texture = spriteData.texture;
const int height = texture->h / spriteData.rowCount;
const int width = texture->w / spriteData.framesPerRow;

  source.resize(spriteData.framesPerRow * spriteData.rowCount);
  for (int i = 0; i < spriteData.framesPerRow * spriteData.rowCount; ++i) {
    source[i].x = (i % spriteData.framesPerRow) * width;
    source[i].y = (i / spriteData.framesPerRow) * height;
    source[i].h = height;
    source[i].w = width;
  }
}

void Sprite::Update(float deltaT) {
  if (!animation.empty()) {
  animation[currentAnimation].Update(deltaT);
}
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

SDL_FRect* Sprite::GetFrame()
{
  if (animation.empty()) {
    return &source[0]; // Return the first frame if no animations are set
  } else {
    return &source[animation[currentAnimation].GetCurrentFrame()];
  }
}
