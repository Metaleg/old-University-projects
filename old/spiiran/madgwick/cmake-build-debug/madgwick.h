//
// Created by metalleg on 20.09.18.
//

#ifndef MADGWICK_MADGWICK_H
#define MADGWICK_MADGWICK_H


#include <math.h>
#define SAMPLE_FREQ	100.0f		// sample frequency in Hz
#define BETA_DEF	0.22f		// 2 * proportional gain

class madgwick {
public:
    madgwick();
    void readQuaternions(float *q0, float *q1, float *q2, float *q3);
    void reset();
    void set_koeff(float sampleFreq, float beta);
    void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void update(float gx, float gy, float gz, float ax, float ay, float az);
    float get_pitch_rad();
    float get_roll_rad();
    float get_yaw_rad();


private:
    float inv_sqrt(float x);
    volatile float _beta = BETA_DEF;				// algorithm gain
    volatile float _sampleFreq = SAMPLE_FREQ;
    volatile float _q0 = 1.0f;
    volatile float _q1 = 0.0f;
    volatile float _q2 = 0.0f;
    volatile float _q3 = 0.0f;
};


#endif //MADGWICK_MADGWICK_H
