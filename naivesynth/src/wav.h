#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <memory.h>

#pragma pack(push, 1)
struct WavHeader
{
    unsigned char chunk_id[4];
    uint32_t chunk_size;
    unsigned char format[4];

    unsigned char subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;

    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;

    unsigned char subchunk2_id[4];
    uint32_t subchunk2_size;
};
#pragma pack(pop)

class WavFile
{
public:
    WavFile(const char* filename);
    ~WavFile();

    template<typename T>
    void write(std::vector<T> data, int32_t num_channels, int32_t sample_rate)
    {
        int32_t size = data.size() * sizeof(T);
        int32_t bitsPerSample = 8 * sizeof(T);

        WavHeader wavHead;
        wavHead.chunk_id[0] = 'R';
        wavHead.chunk_id[1] = 'I';
        wavHead.chunk_id[2] = 'F';
        wavHead.chunk_id[3] = 'F';

        wavHead.chunk_size = size + 36;

        wavHead.format[0] = 'W';
        wavHead.format[1] = 'A';
        wavHead.format[2] = 'V';
        wavHead.format[3] = 'E';

        wavHead.subchunk1_id[0] = 'f';
        wavHead.subchunk1_id[1] = 'm';
        wavHead.subchunk1_id[2] = 't';
        wavHead.subchunk1_id[3] = ' ';

        wavHead.subchunk1_size = 16;
        wavHead.audio_format = 1;

        wavHead.num_channels = num_channels;
        wavHead.sample_rate = sample_rate;
        wavHead.byte_rate = sample_rate * num_channels * bitsPerSample / 8;
        wavHead.block_align = num_channels * bitsPerSample / 8;
        wavHead.bits_per_sample = bitsPerSample;

        wavHead.subchunk2_id[0] = 'd';
        wavHead.subchunk2_id[1] = 'a';
        wavHead.subchunk2_id[2] = 't';
        wavHead.subchunk2_id[3] = 'a';
        wavHead.subchunk2_size = size;

        fwrite((char*)& wavHead, sizeof(WavHeader), 1, _fileHandle);
        fwrite((char*)& data[0], size, 1, _fileHandle);
    }

private:
    FILE* _fileHandle;
    bool _headerWritten = false;

    WavFile(const WavFile&);
    WavFile& operator=(const WavFile&);
};

namespace utils
{
    void printWavHeader(WavHeader wavHead);
    float calcFrequency(int32_t octave, std::string note);
}