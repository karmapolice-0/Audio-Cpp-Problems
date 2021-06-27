#include "include/wav.hpp"
#include "include/voice.hpp"
#include "include/speaker.hpp"
#include "include/observer.hpp"

void WriteSampleWithDelay(std::vector<int32_t>& samples, float sample_to_write, int32_t curr_pos, int32_t delay)
{
    int32_t leftid = curr_pos;
    int32_t rightid = 1 + curr_pos;

    if (delay % 2 == 1)
        ++delay;
    if (delay > 0)
        leftid += delay;
    else
        rightid -= delay;  // += -1 * delay??
    
    if (leftid < (int32_t)samples.size())
        samples[leftid] = (int32_t)sample_to_write;
    if (rightid < (int32_t)samples.size())
        samples[rightid] = (int32_t)sample_to_write;
}

void start(float center_x, float center_y, float radius, double speaker_velocity)
{
    const double sound_velocity = 340.29;
    const double ear_distance = 0.204;
    const int32_t num_seconds = 10;
    const int32_t sample_rate = 44100;
    const int32_t num_channels = 2;
    const int32_t num_samples = sample_rate * num_seconds * num_channels;
    
    std::vector<int32_t> samples(num_samples, 0);  // num_samples samples w/t value = 0
    std::vector<Voice> notes;
    int32_t samples_per_second = sample_rate * num_channels;

    Speaker speaker(center_x, center_y, radius, speaker_velocity / samples_per_second);
    Observer observer(-ear_distance / 2, 0.0f, ear_distance / 2, 0.0f);
    double sample = 0;

    for (size_t i = 0; i < samples.size(); i += num_channels)
    {
        if (i % (int32_t)(samples_per_second / speaker_velocity) == 0)
        {

            // ATTENCION
            // 0.895 - feedback
            notes.push_back( Voice(1000.5f + (27.5f * i / sample_rate * 4), float(sample_rate), 0.895f) );
        }

        // Karplus-Strong
        sample = 0;
        for (auto& note : notes)
            sample += note.genSample();
        
        //sample *= 0.1f; // prevent clipping

        if (sample < 0.0f)
            sample *= -float(std::numeric_limits<int32_t>::lowest());
        else
            sample *= float(std::numeric_limits<int32_t>::max());
        
        speaker.calcNextPoint();

        int32_t delay = (int32_t)(observer.getEarDelta(speaker) * (double)sample_rate / sound_velocity);

        WriteSampleWithDelay(samples, sample, i, delay);
    }

    WavFile wav_file("out.wav");
    wav_file.write(samples, num_channels, sample_rate);
}

int main()
{
    double speaker_x, speaker_y, speaker_radius, speaker_velocity;

    std::cout << "Input speaker's coordinates: ";
    std::cin >> speaker_x >> speaker_y;
    std::cout << "Input speaker's movement radius: ";
    std::cin >> speaker_radius;
    std::cout << "Enter speaker's velocity (m/s): ";
    std::cin >> speaker_velocity;

    start(speaker_x, speaker_y, speaker_radius, speaker_velocity);
    std::cout << "File successfully written: out.wav\n";

    return 0;
}