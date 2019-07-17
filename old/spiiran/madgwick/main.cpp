#include <iostream>
#include <random>
#include "cmake-build-debug/madgwick.h"


int main() {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-1, 1);
    madgwick m;
    m.set_koeff(100, 0.22);

    float mas[6];
    for (float &ma : mas) {
        ma = distribution(generator);
    }

    m.update(mas[0], mas[1], mas[2], mas[3], mas[4], mas[5]);

    std::cout << m.get_roll_rad() << std::endl
    << m.get_pitch_rad() << std::endl
    << m.get_yaw_rad() << std::endl;
    return 0;
}