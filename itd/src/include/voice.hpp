#pragma once

#include "wav.hpp"

class Voice
{
public:
    Voice(float frequency, float sample_rate, float feedback) : _feedbackValue(feedback)
    {
        _i = 0;
        _buffer.resize(std::max((uint32_t)1, (uint32_t)(sample_rate / frequency)));

        for (size_t i = 0; i < _buffer.size(); i++)
            _buffer[i] = (float)rand() * 2.0f / (float)RAND_MAX;
    }

    float genSample()
    {
        float sample = _buffer[_i];

        size_t next_i = (_i + 1) % _buffer.size();
        float value = (_buffer[_i] + _buffer[next_i]) * 0.5f * _feedbackValue;
        _buffer[next_i] = value;

        return sample;
    }

private:
    std::vector<float> _buffer;
    size_t _i;
    float _feedbackValue;
};