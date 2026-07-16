#include "Animation.h"

#include <cmath>

void Animation::Init(const std::vector<int> &frames, float length, bool loop)
{
    animationFrames = frames;
    animationLength = length;
    isLooping = loop;
}

void Animation::Update(float deltaT)
{
    progress += deltaT;
    if (progress >= animationLength)
    {
        if (isLooping)
        {
            progress = std::fmod(progress, animationLength);
        }
        else
        {
            progress = animationLength;
        }
    }
}

int Animation::GetCurrentFrame() const
{
    if (animationFrames.empty() || animationLength <= 0)
    {
        return -1; // No frames available
    }


    int currentFrame = static_cast<int>((progress / animationLength) * animationFrames.size());

return animationFrames[currentFrame]; 
    
  
}
