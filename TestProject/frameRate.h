#pragma once

#include <thread>
#include <chrono>
#include "SDL.h"

class FRAMERATEENUM {
    float f;
    FRAMERATEENUM(float arg) : f(arg) {}
public:

    static const FRAMERATEENUM FPS_240;
    static const FRAMERATEENUM FPS_120;
    static const FRAMERATEENUM FPS_60;

    operator float() const { return f; }
};
const FRAMERATEENUM FRAMERATEENUM::FPS_240(4.166666f);
const FRAMERATEENUM FRAMERATEENUM::FPS_120(8.333333f);
const FRAMERATEENUM FRAMERATEENUM::FPS_60(16.66666f);

class FPS
{
public:
    static inline float fpsCount(Uint64 start,Uint64 end)
    {
        end = SDL_GetPerformanceCounter();
        return (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    }

    static inline float fpsLockToMS(int fps) { return (float)(1000.0f/fps); }
    static inline void delayFPS(float MS, float elapsedMS) // input FPSLOCK time 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds((long)(MS - elapsedMS)));
    }
};