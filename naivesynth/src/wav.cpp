#include "wav.h"

WavFile::WavFile(const char* file_name)
{
    _fileHandle = std::fopen(file_name, "w+");
    if (!_fileHandle) throw std::runtime_error("Couldn't open WavFile");
}

WavFile::~WavFile()
{
    std::fclose(_fileHandle);
}

void utils::printWavHeader(const WavHeader wavHead)
{
    float seconds = 1.f * wavHead.subchunk2_size / (wavHead.bits_per_sample * wavHead.num_channels * wavHead.sample_rate / 8);
    int32_t minutes = (int32_t)floor(seconds) / 60;
    seconds -= (minutes * 60);

    std::cout << "Cunk Id: " << wavHead.chunk_id[0] << wavHead.chunk_id[1] << wavHead.chunk_id[2] << wavHead.chunk_id[3] << '\n'
            << "Chunk Size: " << wavHead.chunk_size << '\n'
            << "Format: " << wavHead.format[0] << wavHead.format[1] << wavHead.format[2] << wavHead.format[3] << '\n'
            << "Subchunk1 Id: " << wavHead.subchunk1_id[0] << wavHead.subchunk1_id[1] << wavHead.subchunk1_id[2] << wavHead.subchunk1_id[3] << "\n"
            << "Subchunk1 Size: " << wavHead.subchunk1_size << "\n"
            << "Audio Format: " << wavHead.audio_format << "\n"
            << "Number of channels: " << wavHead.num_channels << "\n"
            << "Sample Rate: " << wavHead.sample_rate << "\n"
            << "Byte Rate: " << wavHead.byte_rate << "\n"
            << "Block Align: " << wavHead.block_align << "\n"
            << "Bits Per Sample: " << wavHead.bits_per_sample << "\n"
            << "Subchunk2 Id: " << wavHead.subchunk2_id[0] << wavHead.subchunk2_id[1] << wavHead.subchunk2_id[2] << wavHead.subchunk2_id[3] << "\n"
            << "Subchunk2 Size: " << wavHead.subchunk2_size << "\n"
            << "Duration: " << minutes << ':' << seconds << '\n';
}

float utils::calcFrequency(int32_t octave, std::string note)
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