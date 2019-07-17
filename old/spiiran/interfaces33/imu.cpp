#include "imu.h"

imu::imu(const std::string bus) : bus_(bus){
    fd = 0;
    for (size_t i = 0 ; i < num_op_reg; ++i){
        gyro_data[i] = 0;
        accel_data[i] = 0;
        magn_data[i] = 0;
    }
}

void imu::init() {
    if((fd = open(bus_.c_str(), O_RDWR)) < 0) {
        std::cerr << "Failed to open the bus.\n";
        exit(1);
    }
    init_gyro();
    init_accel();
    init_magn();
}

void imu::init_gyro() {
    ioctl(fd, I2C_SLAVE, L3G4200D_ADRESS);

    uint8_t config[2] = {0};
    config[0] = CTRL_REG1;
    config[1] = 0x0F;
    write(fd, config, sizeof(config));

    config[0] = CTRL_REG4;
    config[1] = 0x30;
    write(fd, config, sizeof(config));
}

void imu::init_accel() {
    ioctl(fd, I2C_SLAVE, LIS331DLH_ADRESS);

    uint8_t config[2] = {0};
    config[0] = CTRL_REG1;
    config[1] = 0x2F;
    write(fd, config, sizeof(config));

    config[0] = CTRL_REG4;
    config[1] = 0x80;   //TODO wtf. must be 0x0
    write(fd, config, sizeof(config));
}

void imu::init_magn() {
    ioctl(fd, I2C_SLAVE, LIS3MDL_ADRESS);
    uint8_t config[num_op_reg] = {CTRL_REG1, 0x5C, 0x00, 0x00, 0x08, 0x40};
    write(fd, config, sizeof(config));
}

void imu::read_gyro_data() {
    ioctl(fd, I2C_SLAVE, L3G4200D_ADRESS);
    read_reg(gyro_data);
}

void imu::read_accel_data() {
    ioctl(fd, I2C_SLAVE, LIS331DLH_ADRESS);
    read_reg(accel_data);
}

void imu::read_magn_data() {
    ioctl(fd, I2C_SLAVE, LIS3MDL_ADRESS);
    read_reg(magn_data);
}

void imu::read_reg(float *data) {
    char reg[num_op_reg] = { REG_OUT_X_L, REG_OUT_X_H,
                             REG_OUT_Y_L, REG_OUT_Y_H,
                             REG_OUT_Z_L, REG_OUT_Z_H };

    for (size_t i = 0; i < num_op_reg; ++i){
        write(fd, &reg[i], sizeof(reg[i]));
        read(fd, &reg[i], sizeof(reg[i]));
        data[i] = reg[i];
    }
}

void imu::read_data() {
    read_gyro_data();
    read_accel_data();
    read_magn_data();
}

void imu::convert_gyro_data_deg_per_sec() {
    pos.gyro.x = (gyro_data[1] + gyro_data[0]);
    pos.gyro.y = (gyro_data[3] + gyro_data[2]);
    pos.gyro.z = (gyro_data[5] + gyro_data[4]);
}

void imu::convert_gyro_data_rad_per_sec() {
    pos.gyro.x = static_cast<float>((gyro_data[1] + gyro_data[0]) * (M_PI / 180.0));
    pos.gyro.y = static_cast<float>((gyro_data[3] + gyro_data[2]) * (M_PI / 180.0));
    pos.gyro.z = static_cast<float>((gyro_data[5] + gyro_data[4]) * (M_PI / 180.0));
}

void imu::convert_accel_data_g() {
    pos.accel.x = static_cast<float>((accel_data[1] * 256 + accel_data[0]) * RANGE_2G / 32767.0);
    pos.accel.y = static_cast<float>((accel_data[3] * 256 + accel_data[2]) * RANGE_2G / 32767.0);
    pos.accel.z = static_cast<float>((accel_data[5] * 256 + accel_data[4]) * RANGE_2G / 32767.0);
}

// Accelerometr data in m/s^2
void imu::convert_accel_data() {
    pos.accel.x = static_cast<float>(((accel_data[1] * 256 + accel_data[0]) * RANGE_2G / 32767.0) * G);
    pos.accel.y = static_cast<float>(((accel_data[3] * 256 + accel_data[2]) * RANGE_2G / 32767.0) * G);
    pos.accel.z = static_cast<float>(((accel_data[5] * 256 + accel_data[4]) * RANGE_2G / 32767.0) * G);
}

void imu::convert_magn_data() {
    const float compass_calibrated_bias[3] = {
            524.21f,
            3352.214f,
            -1402.236f
    };

    const float compass_calibrated_matrix[3][3] = {
            {1.757f, 0.04f, -0.028f},
            {0.008f, 1.767f, -0.016f},
            {-0.018f, 0.077f, 1.782f}
    };

    float uncalibrated_data[3];
    uncalibrated_data[0] = ((magn_data[1] * 256 + magn_data[0])/SENS_FS_4);
    uncalibrated_data[1] = ((magn_data[3] * 256 + magn_data[2])/SENS_FS_4);
    uncalibrated_data[2] = ((magn_data[5] * 256 + magn_data[4])/SENS_FS_4);

    float uncalibrated_values[3];
    uncalibrated_values[0] = uncalibrated_data[0] - compass_calibrated_bias[0];
    uncalibrated_values[1] = uncalibrated_data[1] - compass_calibrated_bias[1];
    uncalibrated_values[2] = uncalibrated_data[2] - compass_calibrated_bias[2];

    float calibrated_values[3];
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            calibrated_values[i] += compass_calibrated_matrix[i][j] * uncalibrated_values[j];

    pos.magn.x = (calibrated_values[0]/SENS_FS_4);
    pos.magn.y = (calibrated_values[1]/SENS_FS_4);
    pos.magn.z = (calibrated_values[2]/SENS_FS_4);
}

void imu::convert_data() {
    convert_gyro_data_rad_per_sec();
    convert_accel_data();
    convert_magn_data();
}

void imu::show() {
    std::cout << "\ngyro: " << "x = " << pos.gyro.x << " y = " << pos.gyro.y << " z = " << pos.gyro.z << std::endl;
    std::cout << "accel: " << "x = " << pos.accel.x << " y = " << pos.accel.y << " z = " << pos.accel.z << std::endl;
    std::cout << "magn: " << "x = " << pos.magn.x << " y = " << pos.magn.y << " z = " << pos.magn.z << std::endl;
}