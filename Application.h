#pragma once

#include "Character.h"

#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Application {
private:
  static constexpr int FPS_SAMPLE_COUNT = 64;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *tomTomTexture;
  Character tomTom;
  bool running;

  uint64_t lastFrameTicks;
  float deltaTime;

  float fpsSamples[FPS_SAMPLE_COUNT];
  int fpsSampleIndex;
  int fpsSampleCount;
  float fpsAccumulator;
  bool isLeftdown;
  bool isRigthdown;

  void HandleEvents();
  void UpdateTiming();
  void Render();

public:
  Application();
  ~Application();

  bool Init();
  void Run();
  bool Shutdown();
};