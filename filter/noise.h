#pragma once
#include <cstdint>

class WhiteNoise
{
public:
    explicit WhiteNoise(uint32_t seed = 666);
    float tick();

private:
    uint32_t _state;
};

inline WhiteNoise::WhiteNoise(uint32_t seed) : _state(seed) {}

inline float WhiteNoise::tick()
{
    _state = _state * 1664525 + 1013904223;
    return int32_t(_state) * float(1.0 / INT32_MAX);
}