#include "Sprite.h"
void Sprite::Render(SDL_Renderer *renderer) {
  target.h = 100;
  target.w = 100;
  //target.x = 500 - target.w / 2;
  target.y = 800 - target.h;
  SDL_RenderTexture(renderer, texture, &source[currentFrame], &target);
}
constexpr int height = 33;
constexpr int width = 31;
constexpr float animationSpeed = 0.1f;

void Sprite::Init(SDL_Texture *SdlTexture) {
  texture = SdlTexture;
  animationTime = 0;
  for (int i = 0; i < 24; ++i) {
    source[i].h = height;
    source[i].w = width;
  }
  source[1].x = 34.5;
}

void Sprite::Update(float deltaT) {
  animationTime += deltaT;
  if (animationTime > animationSpeed) {
    if (currentFrame == 0) {
      currentFrame = 1;
    } else {
      currentFrame = 0;
    }
    animationTime -= animationSpeed;
  }
}