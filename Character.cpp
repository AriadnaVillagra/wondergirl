#include "Character.h"

constexpr float runSpeed = 0.01f;

void Character::Init(SDL_Texture *SdlTexture) {
  sprite.Init(SdlTexture);
}
void Character::Render(SDL_Renderer *Renderer) {
  sprite.Render(Renderer);
}
void Character::Update(float DeltaTime) {
  sprite.Update(DeltaTime);
  sprite.target.x = x;
}
void Character::MoveLeft() {
  
  x -= runSpeed;
  
}
void Character::MoveRight() {
  x +=runSpeed;
  
}