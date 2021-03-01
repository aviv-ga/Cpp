//
// Created by Aviv on 19/12/2017.
//

#include "cmath"
#include "Arenstorf.h"
/** Precision to the output stream. */
const int PRECISION = 3;
/** relative mass moon to earth. */
const double ALPHA = 0.012299;
const double BETA = 1 - ALPHA;


int Arenstorf::computeArenstorf(const ArenstorfPoint &init, unsigned int n, unsigned int m,
                                long double dt, std::ostream &out)
{

    if(n < m || dt < 0)
    {
        return -1;
    }

    if(!out) // check if stream is ok
    {
        return -1;
    }
    ArenstorfPoint currPoint = init;
    int k = n / m;
    for(unsigned int i = 0; i < n; i++)
    {
        long double accelx = _accelX(currPoint.getX(), currPoint.getY(), currPoint.getVely());
        long double accely = _accelY(currPoint.getX(), currPoint.getY(), currPoint.getVelx());
        long double newVelX = _newVel(currPoint.getVelx(), accelx, dt);
        long double newVelY = _newVel(currPoint.getVely(), accely, dt);
        long double newPosX = _newPos(currPoint.getX(), currPoint.getVelx(), dt);
        long double newPosY = _newPos(currPoint.getY(), currPoint.getVely(), dt);

        currPoint = ArenstorfPoint(newPosX, newPosY, newVelX, newVelY);
        out.precision(PRECISION);
        if((i % k) == 0 && i < n - 1)
        {
            out << std::scientific << currPoint << ", ";
        }
        if(i == (n - 1))
        {
            out << std::scientific << currPoint << std::endl;
        }
    }
    return 0;
}

long double Arenstorf::_d2(const long double &x, const long double &y)
{
    return powl(((powl((x - BETA), 2)) + (powl(y, 2))), 1.5);
}


long double Arenstorf::_d1(const long double &x, const long double &y)
{
    return powl(((powl((x + ALPHA), 2)) + (powl(y, 2))), 1.5);
}


long double Arenstorf::_accelX(const long double &x, const long double &y, const long double &vely)
{
    long double accelx = x + (2 * vely);
    accelx -= BETA * ((x + ALPHA) / _d1(x, y));
    accelx -= ALPHA * (((x - BETA)) / _d2(x, y));
    return accelx;
}


long double Arenstorf::_accelY(const long double &x, const long double &y, const long double &velx)
{
    long double accelx = y - (2 * velx);
    accelx -= BETA * (y / _d1(x, y));
    accelx -= ALPHA * (y / _d2(x, y));
    return accelx;
}


long double Arenstorf::_newPos(const long double &pos, const long double &vel, const long double &dt)
{
    return pos + (vel * dt);
}


long double Arenstorf::_newVel(const long double &vel, const long double &accel, const long double &dt)
{
    return vel + (accel * dt);
}
