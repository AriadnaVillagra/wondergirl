#include "Application.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>

Application::Application()
    : window(nullptr), renderer(nullptr), tomTomTexture(nullptr), tomTom(),
      running(false), lastFrameTicks(0), deltaTime(0.0f), fpsSamples{},
      fpsSampleIndex(0), fpsSampleCount(0), fpsAccumulator(0.0f) {}
Application::~Application() {}

bool Application::Init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return false;
  }
  std::cout << "SDL " << SDL_GetVersion() << " linked ok" << std::endl;

  window = SDL_CreateWindow("WonderGirl", 1000, 800, 0);
  if (!window) {
    std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
    return false;
  }

  tomTomTexture = IMG_LoadTexture(renderer, "assets/Tom-Tom.png");
  if (!tomTomTexture) {
    std::cout << "IMG_LoadTexture failed: " << SDL_GetError() << std::endl;
    return false;
  }

  tomTom.Init(tomTomTexture);

  if (!TTF_Init()) {
    std::cout << "TTF_Init failed: " << SDL_GetError() << std::endl;
    return false;
  }

  running = true;
  lastFrameTicks = SDL_GetTicksNS();
  return true;
}

void Application::HandleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      running = false;
      break;
    case SDL_EVENT_KEY_DOWN:
      if (event.key.key == SDLK_ESCAPE) {
        running = false;
      } else if (event.key.key == SDLK_LEFT) {
        isLeftdown = true;
      } else if (event.key.key == SDLK_RIGHT) {
        isRigthdown = true;
      }
      break;
    case SDL_EVENT_KEY_UP:
      if (event.key.key == SDLK_LEFT) {
        isLeftdown = false;
      } else if (event.key.key == SDLK_RIGHT) {
        isRigthdown = false;
      }
      break;
    default:
      break;
    }
  }
}

void Application::UpdateTiming() {
  uint64_t now = SDL_GetTicksNS();
  deltaTime = static_cast<float>(now - lastFrameTicks) / 1e9f;
  lastFrameTicks = now;

  fpsSamples[fpsSampleIndex] = deltaTime;
  fpsSampleIndex = (fpsSampleIndex + 1) % FPS_SAMPLE_COUNT;
  if (fpsSampleCount < FPS_SAMPLE_COUNT)
    fpsSampleCount++;

  fpsAccumulator += deltaTime;
  if (fpsAccumulator >= 0.5f) {
    float avgDelta = 0.0f;
    for (int i = 0; i < fpsSampleCount; ++i)
      avgDelta += fpsSamples[i];
    avgDelta /= static_cast<float>(fpsSampleCount);

    float fps = avgDelta > 0.0f ? 1.0f / avgDelta : 0.0f;
    std::string title =
        "WonderGirl - " + std::to_string(static_cast<int>(fps)) + " FPS";
    SDL_SetWindowTitle(window, title.c_str());

    fpsAccumulator = 0.0f;
  }
}

void Application::Render() {
  SDL_SetRenderDrawColor(renderer, 35, 199, 201, 255);
  SDL_RenderClear(renderer);
  tomTom.Render(renderer);

  SDL_RenderPresent(renderer);
}

void Application::Run() {
  while (running) {
    UpdateTiming();
    HandleEvents();
    if (isLeftdown) {
      tomTom.MoveLeft();
    }
    if (isRigthdown) {
      tomTom.MoveRight();
    }
    tomTom.Update(deltaTime);
    Render();
  }
}

bool Application::Shutdown() {
  std::cout << "WonderGirl" << std::endl;
  TTF_Quit();
  SDL_DestroyTexture(tomTomTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  return true;
}