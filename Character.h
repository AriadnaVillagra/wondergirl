#pragma once
#include "Sprite.h"
#include "ColBox.h"

struct SDL_Renderer;
class CollisionSystem; // Forward declaration of CollisionSystem
class Character {
public:
  ~Character();
  void Init(SpriteData &spriteData, float startPosX, float startPosY, CollisionSystem &collisionSystem);
  void Render(SDL_Renderer *Renderer);

  void Update(float DeltaTime);
  void MoveLeft();
  void MoveRight();
  void Jump();
  bool InAir();
  void ClampSpeed();
  void Run(bool running);
  void HandleCollision();

  private:
  ColBox colBox;
  Sprite sprite;
  CollisionSystem *collisionSystem = nullptr;
  float x;
  float y;
  float direction;
  float verticalSpeed;
  float horizontalSpeed;
  bool isRunning;
  void UpdateColBox();
  void UpdateSpeed(float DeltaTime);
  void UpdatePosition(float DeltaTime);
  void UpdateSprite(float DeltaTime);
 
};
