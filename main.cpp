#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const int sampleRate = 44100;

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



int main() {
    int duration = 2;
    ofstream audioFile;
    audioFile.open("waveform", ios::binary);

    SineOscillator sineOscillator(440, 0.5);

    for(int i = 0; i < sampleRate * duration; i++) {
        audioFile << sineOscillator.process() << endl;
    }

    audioFile.close();
    return 0;
}