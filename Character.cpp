#include "Character.h"

#include <iostream>
#include <ostream>

constexpr float maxRunSpeed = 500;
constexpr float jumpForce = 300;
constexpr float gravity = 500;
constexpr float acceleration = 500;
constexpr float maxWalkSpeed = 100;

void Character::Init(SDL_Texture *SdlTexture) {
  x = 500 - 100 / 2;
  y = 800 - 100;
  sprite.target.x = x;
  sprite.target.y = y;

  sprite.Init(SdlTexture);
  sprite.SetAnimation({0, 1}, 0.3f, true);  
  sprite.SetAnimation({2, 3, 4, 5}, 0.3f, true);
  sprite.SetCurrentAnimation(0);
}


void Character::Render(SDL_Renderer *Renderer) { sprite.Render(Renderer); }
void Character::UpdateSpeed(float DeltaTime) {
  if (direction != 0) {
    horizontalSpeed += direction * DeltaTime * acceleration;
  } else {
    if (horizontalSpeed > 0) {
      horizontalSpeed -= DeltaTime * acceleration;
      if (horizontalSpeed < 0) {
        horizontalSpeed = 0;
      }
    } else {
      horizontalSpeed += DeltaTime * acceleration;
      if (horizontalSpeed > 0) {
        horizontalSpeed = 0;
      }
    }
  }

  ClampSpeed();
}
void Character::UpdatePosition(float DeltaTime) {
  x += horizontalSpeed * DeltaTime;

  y -= jump * DeltaTime;

  if (InAir()) {
    jump -= gravity * DeltaTime;
  } else {
    y = 800 - 100;
    jump = 0;
    direction = 0;
  }
}
void Character::UpdateSprite(float DeltaTime) {
  sprite.Update(DeltaTime);
  sprite.target.x = x;
  sprite.target.y = y;
}
void Character::Update(float DeltaTime) {
  UpdateSpeed(DeltaTime);
  UpdatePosition(DeltaTime);
  UpdateSprite(DeltaTime);
}
void Character::MoveLeft() {
  if (!InAir()) {
    direction -= 1;
  }
}
void Character::MoveRight() {
  if (!InAir()) {
    direction += 1;
  }
}
void Character::Jump() {
  if (jump == 0)
    jump += jumpForce;
}
bool Character::InAir() { return y < 800 - 100; }

void Character::ClampSpeed() {
  float topSpeed;
  if (isRunning) {
    topSpeed = maxRunSpeed;
  } else {
    topSpeed = maxWalkSpeed;
  }

  if (horizontalSpeed > topSpeed) {
    horizontalSpeed = topSpeed;
  } else if (horizontalSpeed < -topSpeed) {
    horizontalSpeed = -topSpeed;
  }
}
void Character::Run(bool running) {
  isRunning = running;
  sprite.SetCurrentAnimation(running ? 1 : 0);
}