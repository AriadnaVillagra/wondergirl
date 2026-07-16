#pragma once

#include <vector>

class Animation {
public:
void Init(const std::vector<int> &frames, float length, bool loop = true);
void Update(float deltaT);
int GetCurrentFrame () const;

private:
std::vector<int> animationFrames;
float animationLength;
float progress = 0;
bool isLooping;
};      