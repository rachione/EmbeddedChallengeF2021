

#include <math.h>
#include <mbed.h>
//I have change some content in the package (like changing L3GD20 to I3G4250D).
#include "GYRO_DISCO_F429ZI.h"

#define AXIS 3

class Movement
{
private:
    float vel[AXIS];
    float radius;
    GYRO_DISCO_F429ZI gyro;
public:
    Movement(float _radius);
    float *GetAngVel();
    float *GetVel(float *angVel);
    float GetDistance(float *vel);
};
