#include "karplus_strong.h"

// gen sample vec from frequencies
template<typename T>
std::vector<T> genSamples(int32_t numSamples, int32_t sampleRate, const std::vector<float>& frequencies)
{
    std::vector<T> samples(numSamples);
    std::vector<KarplusStrongVoice> notes;
    float sample;

    const int32_t noteTime = numSamples / (double)frequencies.size();

    int32_t currFreq = 0;

    for (size_t i = 0; i < samples.size(); i++)
    {
        if (i % noteTime == 0)
        {
            notes.push_back(KarplusStrongVoice(frequencies[currFreq], float(sampleRate), 0.986f));
            ++currFreq;
        }

        sample = 0;
        for (auto& note : notes)
            sample += note.getNext();
        
        sample *= 0.2f;  //  Prevent clipping

        if (sample < 0.0f)
        {
            sample *= -float(std::numeric_limits<T>::lowest());
        }
        else
        {
            sample *= float(std::numeric_limits<T>::max());
        }
        samples[i] = (T)sample;
    }
    return samples;
}

void readFreqToVec(std::vector<float>& frequencies, std::istream& in)
{
    float noteFreq;

    while (in >> noteFreq)
    {
        if (noteFreq < 0.0f) continue;
        frequencies.push_back(noteFreq);
    }
}

int main()
{
    int32_t sampleRate;
    int32_t numSeconds;
    const int numChannels = 1;
    std::vector<float> frequencies;
    
    std::cout << "Enter sample rate: ";
    std::cin >> sampleRate;
    std::cout << "Enter duration (sec): ";
    std::cin >> numSeconds;
    std::cout << "Enter frequencies:\n";
    readFreqToVec(frequencies, std::cin);

    const int numSamples = sampleRate * numSeconds * numChannels;

    std::vector<int16_t> samples = genSamples<int16_t>(numSamples, sampleRate, frequencies);

    WavFile wav_file("out.wav");

    wav_file.write(samples, numChannels, sampleRate);
    std::cout << "File succesfully written: out.wav\n";
    
    return 0;
}