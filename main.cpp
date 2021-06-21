#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

// 44.1khz
const int sampleRate = 44100;
const int bitDepth = 16;

class SineOscillator {
    float frequency, amplitude, angle = 0.0f, offset = 0.0;

public:
    SineOscillator(float freq, float amp) : frequency(freq), amplitude(amp) {
        offset = 2 * M_PI * frequency / sampleRate;
    }

    float process() {
        auto float sample =  amplitude * sin(angle);
        // Asin(2pif/sampling rate)
        angle += offset;
        return sample;
    }
};

void writeToFile(ofstream &file, int value, int size) {
    file.write(reinterpret_cast<const char*> (&value), size);
}

int main() {
    int duration = 2;
    ofstream audioFile;
    audioFile.open("waveform", ios::binary);

    SineOscillator sineOscillator(440, 0.5);

    // Header Chunk
    audioFile << "RIFF";
    audioFile << "----";
    audioFile << "WAVE";

    // Audio Chunk
    audioFile << "fmt ";
    writeToFile(audioFile, 16, 4);

    auto float maxAmplitude = pow(2, bitDepth - 1) -1;
    for(int i = 0; i < sampleRate * duration; i++) {
        auto float sample = sineOscillator.process();
        int intSample = static_cast<int> (sample * maxAmplitude);
        writeToFile(audioFile, intSample, 2);
    }

    audioFile.close();
    return 0;
}