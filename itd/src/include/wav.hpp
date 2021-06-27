// http://microsin.net/programming/pc/wav-format.html


#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <memory.h>


struct WavHeader
{
    unsigned char chunkId[4];  // riff
    uint32_t chunkSize;
    unsigned char format[4];  // Wave
    
    unsigned char subchunk1Id[4];  // fmt
    uint32_t subchunk1Size;
    uint16_t audioFormat;

    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;

    unsigned char subchunk2Id[4];  // data
    uint32_t subchunk2Size;
};

class WavFile
{
public:
    WavFile(const char* filename)
    {
        _fileHandle = std::fopen(filename, "w+");
        if (!_fileHandle) throw std::runtime_error("Couldn't open WavFile");
    }
    ~WavFile()
    {
        std::fclose(_fileHandle);
    }

    template<typename T>
    void write(std::vector<T> data, int32_t num_channels, int32_t sample_rate)
    {
        int32_t size = data.size() * sizeof(T);
        int32_t bits_per_sample = 8 * sizeof(T);

        WavHeader wavHead;
        wavHead.chunkId[0] = 'R';
        wavHead.chunkId[1] = 'I';
        wavHead.chunkId[2] = 'F';
        wavHead.chunkId[3] = 'F';

        wavHead.chunkSize = size + 36;

        wavHead.format[0] = 'W';
        wavHead.format[1] = 'A';
        wavHead.format[2] = 'V';
        wavHead.format[3] = 'E';

        wavHead.subchunk1Id[0] = 'f';
        wavHead.subchunk1Id[1] = 'm';
        wavHead.subchunk1Id[2] = 't';
        wavHead.subchunk1Id[3] = ' ';

        wavHead.subchunk1Size = 16;
        wavHead.audioFormat = 1;

        wavHead.numChannels = num_channels;
        wavHead.sampleRate = sample_rate;
        wavHead.byteRate = sample_rate * num_channels * bits_per_sample / 8;
        wavHead.blockAlign = num_channels * bits_per_sample / 8;
        wavHead.bitsPerSample = bits_per_sample;

        wavHead.subchunk2Id[0] = 'd';
        wavHead.subchunk2Id[1] = 'a';
        wavHead.subchunk2Id[2] = 't';
        wavHead.subchunk2Id[3] = 'a';
        wavHead.subchunk2Size = size;

        fwrite((char*)& wavHead, sizeof(WavHeader), 1, _fileHandle);
        fwrite((char*)& data[0], size, 1, _fileHandle);
    }

private:
    FILE* _fileHandle;
    bool _headerWritten = false;

    WavFile(const WavFile&);
    WavFile& operator=(const WavFile&);
};
