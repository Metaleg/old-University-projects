#ifndef INTERFACES3_LIBRARY_H
#define INTERFACES3_LIBRARY_H

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include <cmath>
#include <unistd.h>

#define L3G4200D_ADRESS   0x68
#define LIS331DLH_ADRESS  0x18
#define LIS3MDL_ADRESS    0x1C

#define CTRL_REG1         0x20
#define CTRL_REG4         0x23

#define REG_OUT_X_L       0x28
#define REG_OUT_X_H       0x29
#define REG_OUT_Y_L       0x2A
#define REG_OUT_Y_H       0x2B
#define REG_OUT_Z_L       0x2C
#define REG_OUT_Z_H       0x2D


const float SENS_FS_4 = 6842;
const float SENS_FS_250 = 0.00875;
const float RANGE_2G = 2;
const float G = 9.8;
const int num_op_reg = 6;    // number of output x/y/z registers

struct point{
    float x;
    float y;
    float z;
};

struct position{
    point gyro;
    point accel;
    point magn;
};

class imu {
    int fd;
    std::string bus_;
    float gyro_data[num_op_reg];
    float accel_data[num_op_reg];
    float magn_data[num_op_reg];

    position pos;

    void init_gyro();
    void init_accel();
    void init_magn();
    void read_reg(float *data);
    void read_gyro_data();
    void read_accel_data();
    void read_magn_data();
    void convert_gyro_data_deg_per_sec();
    void convert_gyro_data_rad_per_sec();
    void convert_accel_data_g();
    void convert_accel_data();
    void convert_magn_data();

public:
    explicit imu(std::string bus);

    void init();
    void read_data();
    void convert_data();
    void show();

};

#endif