#include <iostream>

class SineOscillator {
    float frequency, amplitude;
public:
    SineOscillator(float freq, float amp) : frequency(freq), amplitude(amp);
};



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}