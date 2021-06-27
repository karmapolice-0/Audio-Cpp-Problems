#include "wav.hpp"

void printWavHeader(const WavHeader wavHead)
{
    float seconds = 1.f * wavHead.subchunk2Size / (wavHead.bitsPerSample * wavHead.numChannels * wavHead.sampleRate / 8);
    int32_t minutes = (int32_t)floor(seconds) / 60;
    seconds -= (minutes * 60);

    std::cout << "Cunk Id: " << wavHead.chunkId[0] << wavHead.chunkId[1] << wavHead.chunkId[2] << wavHead.chunkId[3] << '\n'
            << "Chunk Size: " << wavHead.chunkSize << '\n'
            << "Format: " << wavHead.format[0] << wavHead.format[1] << wavHead.format[2] << wavHead.format[3] << '\n'
            << "Subchunk1 Id: " << wavHead.subchunk1Id[0] << wavHead.subchunk1Id[1] << wavHead.subchunk1Id[2] << wavHead.subchunk1Id[3] << "\n"
            << "Subchunk1 Size: " << wavHead.subchunk1Size << "\n"
            << "Audio Format: " << wavHead.audioFormat << "\n"
            << "Number of channels: " << wavHead.numChannels << "\n"
            << "Sample Rate: " << wavHead.sampleRate << "\n"
            << "Byte Rate: " << wavHead.byteRate << "\n"
            << "Block Align: " << wavHead.blockAlign << "\n"
            << "Bits Per Sample: " << wavHead.bitsPerSample << "\n"
            << "Subchunk2 Id: " << wavHead.subchunk2Id[0] << wavHead.subchunk2Id[1] << wavHead.subchunk2Id[2] << wavHead.subchunk2Id[3] << "\n"
            << "Subchunk2 Size: " << wavHead.subchunk2Size << "\n"
            << "Duration: " << minutes << ':' << seconds << '\n';
}

float noteToFreq(int32_t octave, std::string note)
{
    std::map<std::string, unsigned char> notes =
    {
        {"A", 0},
        {"A#", 1},
        {"B", 2},
        {"C", 3},
        {"C#", 4},
        {"D", 5},
        {"D#", 6},
        {"E", 7},
        {"F", 8},
        {"F#", 9},
        {"G", 10},
        {"G#", 11}
    };
    return (float)(440 * std::pow(2.0, ( (double)((octave - 4) * 12 + notes[note]) ) / 12.0));
}

double distance(double x0, double y0, double x1, double y1)
{
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}