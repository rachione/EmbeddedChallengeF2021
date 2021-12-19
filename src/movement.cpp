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
    //Gets raw data
    gyro.GetXYZ(vel);

    for (int i = 0; i < AXIS; i++)
    {
        //raw* Full Scale (+-)250 / 2^16
        vel[i] = vel[i] *500/ 65536.0f;
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
