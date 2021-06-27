#pragma once

#include "wav.h"


class KarplusStrongVoice
{
public:
    KarplusStrongVoice(float frequency, float sampleRate, float feedback);
    float getNext();
private:
    std::vector<float> _buffer;
    size_t _i;
    float _feedbackValue;
};