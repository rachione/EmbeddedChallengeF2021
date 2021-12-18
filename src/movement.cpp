#include "movement.h"

Movement::Movement(float _radius)
{
    radius = _radius;
}
/**
* @brief  Get angular velocity.
* @param  None
* @retval Angular velocity
*/
float *Movement::GetAngVel()
{
    //Gets (raw * sensitivity) = raw*0.875(I3G4250D_FULLSCALE_245)
    gyro.GetXYZ(vel);

    for (int i = 0; i < AXIS; i++)
    {
        //mdps 250, 0.00875 * raw
        vel[i] = vel[i] * 0.001;
    }
    return vel;
}

/**
* @brief  Get forward velocity.
* @param  angVel: Angular velocity.
* @retval Forward velocity
*/
float *Movement::GetVel(float *angVel)
{
    for (int i = 0; i < AXIS; i++)
    {
        //convert degrees/s to rad/s, V = WR
        vel[i] = angVel[i] / 180.0f * M_PI * radius;
    }
    return vel;
}

/**
* @brief  Get distance from 3 axes. One single leg is oscillating while walking, so the negative value will be positive.
* @param  vel: Forward velocity.
* @retval Distance(cm)
*/
float Movement::GetDistance(float *vel)
{
    return sqrt(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]);
}
