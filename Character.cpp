#include "Character.h"

#include <iostream>
#include <ostream>
#include "CollisionSystem.h"
#include "Defines.h"

constexpr float maxRunSpeed = 500;
constexpr float jumpForce = 300;

constexpr float acceleration = 500;
constexpr float maxWalkSpeed = 100;

void Character::Init(SpriteData &spriteData, float startPosX, float startPosY, CollisionSystem &collisionSystem)
{
  colBox.entityType = EntityType::Character;

  x = startPosX;
  y = startPosY;

  colBox.x = x;
  colBox.y = y;
  colBox.w = 100;
  colBox.h = 100;

  this->collisionSystem = &collisionSystem;
  collisionSystem.AddToGroup1(&colBox);
  sprite.Init(spriteData);
  sprite.SetAnimation({0, 1}, 0.3f, true);
  sprite.SetAnimation({2, 3, 4, 5}, 0.3f, true);
  sprite.SetCurrentAnimation(0);
}

Character::~Character()
{
  if (collisionSystem)
  {
    collisionSystem->RemoveFromGroup1(&colBox);
  }
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

  y -= verticalSpeed * DeltaTime;

  if (InAir()) {
    verticalSpeed -= gravity * DeltaTime;
  } else {
    y = 800 - 100;
    verticalSpeed = 0;
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
  UpdateColBox();
  HandleCollision();
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
  if (verticalSpeed == 0)
    verticalSpeed += jumpForce;
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

void Character::UpdateColBox() {
  colBox.x = x;
  colBox.y = y;
}

void Character::HandleCollision() {
for (ColBox* other : colBox.collisionList) {
    if (other->entityType == EntityType::Wall) {
        // Handle collision with wall
        // For example, stop movement or adjust position
        if (verticalSpeed < 0) {
            y = other->y + other->h; // Adjust position to be on top of the wall
            verticalSpeed = 0; // Stop upward movement
        } else { 
            y = other->y - colBox.h; // Adjust position to be below the wall
        }

        if (horizontalSpeed > 0) {
            x = other->x - colBox.w; // Adjust position to the left of the wall
        } else if (horizontalSpeed < 0) {
            x = other->x + other->w; // Adjust position to the right of the wall
        }
        horizontalSpeed = 0; // Stop horizontal movement
    }
  }
  colBox.collisionList.clear(); // Clear the collision list after handling
}