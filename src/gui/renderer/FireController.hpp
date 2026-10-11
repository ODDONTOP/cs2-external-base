#pragma once
#include <windows.h>
#include <cstdlib>

struct FireControllerConfig {
    float minMs;
    float maxMs;
    int mode;
    int bindVk;
};

__forceinline void FireControllerTick(bool visible, FireControllerConfig* cfg, bool* isPressed, unsigned int* nextReleaseTime)
{
    bool shouldFire = visible;
    if (cfg->mode == 1) shouldFire = shouldFire && (GetAsyncKeyState(cfg->bindVk) & 0x8000);
    if (shouldFire && !*isPressed) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        *isPressed = true;
        *nextReleaseTime = GetTickCount() + static_cast<unsigned int>(cfg->minMs + rand() % static_cast<int>(cfg->maxMs - cfg->minMs + 1));
    }
    if (*isPressed && GetTickCount() >= *nextReleaseTime) {
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        *isPressed = false;
    }
}