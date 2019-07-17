#include "imu.h"

const std::string bus = "/dev/i2c-8";

int main(int argc, char **argv) {
    imu im(bus);
    im.init();
    while (true){
        im.read_data();
        im.convert_data();
        im.show();

    }
    return 0;
}