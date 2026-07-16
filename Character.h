#pragma once
#include "Sprite.h"

class Character {
public:
  Sprite sprite;
  float x;
  float y;
  float direction;
  float jump;
  float horizontalSpeed;
  bool isRunning;
  void Init(SDL_Texture *SdlTexture);
  void Render(SDL_Renderer *Renderer);
  void UpdateSpeed(float DeltaTime);
  void UpdatePosition(float DeltaTime);
  void UpdateSprite(float DeltaTime);
  void Update(float DeltaTime);
  void MoveLeft();
  void MoveRight();
  void Jump();
  bool InAir();
  void ClampSpeed();
  void Run();
};
