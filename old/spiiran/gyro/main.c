

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
#define DEVICE_ADRESS   0x68
#define WHO_AM_I    	0xF

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


	int fd;
	if((fd = open(BUS, O_RDWR)) < 0){
		perror("Failed to open the bus.\n");
		exit(1);
	}

	ioctl(fd, I2C_SLAVE, DEVICE_ADRESS);		// Get I2C device, L3G4200D I2C address is 0x68

	// Enable X, Y, Z-Axis and disable Power down mode(0x0F)
	char config[2];
	char data_0, data_1, data_2, data_3, data_4, data_5;
	char reg[1];
	char data[1];

	config[0] = CTRL_REG1;
	config[1] = WHO_AM_I;
	write(fd, config, 2);
	// Full scale range, 2000 dps(0x30)
	config[0] = CTRL_REG4;
	config[1] = L3G4200D_REG_INT1_CFG;
	write(fd, config, 2);
	sleep(1);

	while(fd > 0){
		// Read 6 bytes of data
		// lsb first
		// Read xGyro lsb data from register(0x28)
		reg[1] = L3G4200D_REG_OUT_X_L;
		write(fd, reg, 1);
		data[1] = 0;
		if(!read(fd, data, 1)) {
			perror("Error: Input/Output error.\n");
			exit(1);
		}
		data_0 = data[0];
        printf("data_0 : %d \n", data_0);


        reg[0] = L3G4200D_REG_OUT_X_H;	// Read xGyro msb data from register(0x29)
		write(fd, reg, 1);
		read(fd, data, 1);
		data_1 = data[0];
        printf("data_1 : %d \n", data_1);

		reg[0] = L3G4200D_REG_OUT_Y_L;	// Read yGyro lsb data from register(0x2A)
		write(fd, reg, 1);
		read(fd, data, 1);
		data_2 = data[0];
        printf("data_2 : %d \n", data_2);


        reg[0] = L3G4200D_REG_OUT_Y_H;	// Read yGyro msb data from register(0x2B)
		write(fd, reg, 1);
		read(fd, data, 1);
		data_3 = data[0];
        printf("data_3 : %d \n", data_3);


        reg[0] = L3G4200D_REG_OUT_Z_L;	// Read zGyro lsb data from register(0x2C)
		write(fd, reg, 1);
		read(fd, data, 1);
		data_4 = data[0];
        printf("data_4 : %d \n", data_4);


        reg[0] = L3G4200D_REG_OUT_Z_H;	// Read zGyro msb data from register(0x2D)
		write(fd, reg, 1);
		read(fd, data, 1);
		data_5 = data[0];
        printf("data_5 : %d \n", data_5);


        // Convert the data   dps
		int xGyro = (data_1 * 256 + data_0);
		if(xGyro > 32767)
			xGyro -= 65536;

		int yGyro = (data_3 * 256 + data_2);
		if(yGyro > 32767)
			yGyro -= 65536;

		int zGyro = (data_5 * 256 + data_4);
		if(zGyro > 32767)
			zGyro -= 65536;

		// Output data to screen
//		ss << "Rotation in X-Axis: " << xGyro << std::endl
//		<< "Rotation in Y-Axis: " << yGyro << std::endl
//        << "Rotation in Z-Axis: " << zGyro << std::endl;
//		msg.data = ss.str();
//        ROS_INFO("%s \n\n", msg.data.c_str());	int fd;
	if((fd = open(BUS, O_RDWR)) < 0){
		perror("Failed to open the bus.\n");
		exit(1);
	}

	ioctl(fd, I2C_SLAVE, DEVICE_ADRESS);		// Get I2C device, L3G4200D I2C address is 0x68
//		pub.publish(msg);
        printf("Rotation in X-Axis : %d \n", xGyro);
		printf("Rotation in Y-Axis : %d \n", yGyro);
		printf("Rotation in Z-Axis : %d \n", zGyro);
		printf("\n");
		sleep(1);
//		ros::spinOnce();
	}
	return 0;
}
/*#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUS "/dev/i2c-8"

//------------------ all l3g4200d-gyroscope's registers------------------------------
#define DEVICE_ADRESS   0x68
#define WHO_AM_I    	0xF

#define CTRL_REG1       0x20    // power control reg
#define CTRL_REG4       0x23    // interrupt control reg

#define L3G4200D_REG_OUT_X_L       0x28
#define L3G4200D_REG_OUT_X_H       0x29
#define L3G4200D_REG_OUT_Y_L       0x2A
#define L3G4200D_REG_OUT_Y_H       0x2B
#define L3G4200D_REG_OUT_Z_L       0x2C
#define L3G4200D_REG_OUT_Z_H       0x2D

#define L3G4200D_REG_INT1_CFG      0x30

struct Position{
    double x_gyro;
    double y_gyro;
    double z_gyro;
};

void reg_init();
void read_data();
void convert_data(struct Position *pos, double *data);

int main(){
    int fd;
    int x_gyro, y_gyro, z_gyro;
    double data[6];
    struct Position pos;
    if((fd = open(BUS, O_RDWR)) < 0){
        perror("Failed to open the bus.\n");
        exit(1);
    }
    ioctl(fd, I2C_SLAVE, DEVICE_ADRESS);		// Get I2C device, L3G4200D I2C address is 0x68


//    registers init




    while(fd > 0){
        convert_data(&pos, data);
        sleep(1);
    }

    return 0;
}

void reg_init(){

}

void read_data(){


}

void convert_data(struct Position *pos, double *data){
    pos->x_gyro = (data[1] * 256 + data[0]);
    if(pos->x_gyro > 32767)
        pos->x_gyro -= 65536;

    pos->y_gyro = (data[3] * 256 + data[2]);
    if(pos->y_gyro > 32767)
        pos->y_gyro -= 65536;

    pos->z_gyro = (data[5] * 256 + data[4]);
    if(pos->z_gyro > 32767)
        pos->z_gyro -= 65536;
}



*/
