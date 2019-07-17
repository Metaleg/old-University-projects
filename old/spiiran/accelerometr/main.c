/*#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define BUS "/dev/i2c-8"
#define ACC_ADDRESS 0x18
#define ACC_REGISTERS_NUM 6

int main(){
    int i;
    char buf[6];

    // Open up the I2C bus
    int file;
    if ((file = open(BUS, O_RDWR)) < 0){
        perror("Failed to open the bus.\n");
        exit(1);
    }

    // Specify the address of the slave device.
    if (ioctl(file, I2C_SLAVE, ACC_ADDRESS) < 0){
        perror("Failed to acquire bus access and/or talk to slave");
        exit(1);
    }

    while(file > 0){
        // Write a byte to the slave.
        buf[0] = 0;
        if ((write(file, buf, 1) != 1) || (read(file,buf,ACC_REGISTERS_NUM) != ACC_REGISTERS_NUM))        {
            perror("Failed to write to the i2c bus");
            exit(1);
        }

        for(i=0;i<6;i++)
            printf("0x%02X ", buf[i]);
        printf("\n");
        sleep(1);
    }

    return 0;
}*/




/*
 * #include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
*/
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUS "/dev/i2c-8"

//------------------ all l3g4200d-gyroscope's registers------------------------------
#define DEVICE_ADRESS   0x18
#define WHO_AM_I    	0x0F

#define CTRL_REG1       0x20    // power control reg
#define CTRL_REG4       0x23    // interrupt control reg

#define L3G4200D_REG_OUT_X_L       0x28
#define L3G4200D_REG_OUT_X_H       0x29
#define L3G4200D_REG_OUT_Y_L       0x2A
#define L3G4200D_REG_OUT_Y_H       0x2B
#define L3G4200D_REG_OUT_Z_L       0x2C
#define L3G4200D_REG_OUT_Z_H       0x2D

#define L3G4200D_REG_INT1_CFG      0x30

int main(int argc, char **argv){
    /*
         ros::init(argc, argv, "gyro");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::String>("chatter", 1000);
    std_msgs::String msg;
    std::stringstream ss;*/


    int file;
    if((file = open(BUS, O_RDWR)) < 0){
        perror("Failed to open the bus.\n");
        exit(1);
    }

    ioctl(file, I2C_SLAVE, DEVICE_ADRESS);		// Get I2C device, L3G4200D I2C address is 0x68

    // Enable X, Y, Z-Axis and disable Power down mode(0x0F)
    char config[2];
    char data_0, data_1, data_2, data_3, data_4, data_5;
    char reg[1];
    char data[1];

    config[0] = CTRL_REG1;
    config[1] = 0x27;//WHO_AM_I;
    write(file, config, 2);
    //*/ Full scale range, 2000 dps(0x30)
    config[0] = CTRL_REG4;
    config[1] = 0x10000000b;//L3G4200D_REG_INT1_CFG;
    write(file, config, 2);
    sleep(1);

    reg[0] = WHO_AM_I;	// Read xGyro msb data from register(0x29)
    write(file, reg, 1);
    read(file, data, 1);
    printf("WHO_AM_I = %02x\n",data[0]);

    reg[0] = CTRL_REG1;	// Read xGyro msb data from register(0x29)
    write(file, reg, 1);
    read(file, data, 1);
    printf("CTRL_REG1 = %02x\n",data[0]);
    while(file > 0){
        // Read 6 bytes of data
        // lsb first
        // Read xGyro lsb data from register(0x28)
        reg[1] = L3G4200D_REG_OUT_X_L;
        write(file, reg, 1);
        data[1] = 0;
        if(!read(file, data, 1)) {
            perror("Error: Input/Output error.\n");
            exit(1);
        }
        data_0 = data[0];

        reg[0] = L3G4200D_REG_OUT_X_H;	// Read xGyro msb data from register(0x29)
        write(file, reg, 1);
        read(file, data, 1);
        data_1 = data[0];

        reg[0] = L3G4200D_REG_OUT_Y_L;	// Read yGyro lsb data from register(0x2A)
        write(file, reg, 1);
        read(file, data, 1);
        data_2 = data[0];

        reg[0] = L3G4200D_REG_OUT_Y_H;	// Read yGyro msb data from register(0x2B)
        write(file, reg, 1);
        read(file, data, 1);
        data_3 = data[0];

        reg[0] = L3G4200D_REG_OUT_Z_L;	// Read zGyro lsb data from register(0x2C)
        write(file, reg, 1);
        read(file, data, 1);
        data_4 = data[0];

        reg[0] = L3G4200D_REG_OUT_Z_H;	// Read zGyro msb data from register(0x2D)
        write(file, reg, 1);
        read(file, data, 1);
        data_5 = data[0];

        // Convert the data   dps
        int xGyro = (data_1 * 256 + data_0);

        int yGyro = (data_3 * 256 + data_2);

        int zGyro = (data_5 * 256 + data_4);

        // Output data to screen
        /*ss << "Rotation in X-Axis: " << xGyro << std::endl
           << "Rotation in Y-Axis: " << yGyro << std::endl
           << "Rotation in Z-Axis: " << zGyro << std::endl;
        msg.data = ss.str();
        ROS_INFO("%s \n\n", msg.data.c_str());
        pub.publish(msg);*/
//        printf("Rotation in X-Axis : %d \n", xGyro);
//        printf("Rotation in Y-Axis : %d \n", yGyro);
//        printf("Rotation in Z-Axis : %d \n", zGyro);
        printf("data_0: %d \n", data_0);
        printf("data_1: %d \n", data_1);
        printf("data_2: %d \n", data_2);
        printf("data_3: %d \n", data_3);
        printf("data_4: %d \n", data_4);
        printf("data_5: %d \n", data_5);
        printf("\n");
        sleep(1);
        //ros::spinOnce();
    }
    return 0;
}