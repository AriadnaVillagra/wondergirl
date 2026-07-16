cmake_minimum_required(VERSION 3.20)
project(WonderGirl CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(SDL3_DIR "${CMAKE_SOURCE_DIR}/external/SDL/build-mac")
set(SDL3_image_DIR "${CMAKE_SOURCE_DIR}/external/SDL_image/build-mac")
set(SDL3_ttf_DIR "${CMAKE_SOURCE_DIR}/external/SDL_ttf/build-mac")

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(WonderGirl
  WonderGirl.cpp
  Application.cpp
  Character.cpp
  Sprite.cpp
)

target_link_libraries(WonderGirl PRIVATE
  SDL3_ttf::SDL3_ttf
  SDL3_image::SDL3_image
  SDL3::SDL3
)

# The app loads assets with a path relative to the working directory
# (e.g. "assets/Tom-Tom.png"), so run it from the repo root.
