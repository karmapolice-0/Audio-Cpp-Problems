#include "karplus_strong.h"

KarplusStrongVoice::KarplusStrongVoice(float frequency, float sampleRate, float feedback) :
    _feedbackValue(feedback)
{
    _i = 0;
    _buffer.resize(std::max( (uint32_t)1, (uint32_t)(sampleRate / frequency) ));

    for (size_t i = 0; i < _buffer.size(); i++)
    {
        _buffer[i] = ((float)rand() / (float)RAND_MAX) * 2.0f;
    }
}

float KarplusStrongVoice::getNext()
{
    float sample = _buffer[_i];

    // lowpass filter
    size_t next_i = (_i + 1) % _buffer.size();
    float value = (_buffer[_i] + _buffer[next_i]) * 0.5f * _feedbackValue;
    _buffer[_i] = value;
    _i = next_i;

    return sample;
}