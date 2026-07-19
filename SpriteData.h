#pragma once

struct SDL_Texture; // Forward declaration of SDL_Texture

struct SpriteData {
SDL_Texture *texture;
int framesPerRow;
int rowCount;


};