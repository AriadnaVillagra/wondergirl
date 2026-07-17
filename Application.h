#pragma once

#include "Character.h"

#include <cstdint>
#include <vector>
#include "Wall.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Application {
private:
  static constexpr int FPS_SAMPLE_COUNT = 64;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *tomTomTexture;
  SDL_Texture *wallTexture;
  Character tomTom;
  std::vector<Wall> walls;
  bool running;

  uint64_t lastFrameTicks;
  float deltaTime;

  float fpsSamples[FPS_SAMPLE_COUNT];
  int fpsSampleIndex;
  int fpsSampleCount;
  float fpsAccumulator;
  bool isLeftdown = false;
  bool isRigthdown = false;
  bool isShiftDown = false;
  bool lastFrameShiftDown = false;

  void HandleEvents();
  void UpdateTiming();
  void Render();
  void DrawWalls();
  void UpdateEntities();

public:
  Application();
  ~Application();

  bool Init();
  void Run();
  bool Shutdown();
};