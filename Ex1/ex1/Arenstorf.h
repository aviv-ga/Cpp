#ifndef EX1_ARENSTORF_H
#define EX1_ARENSTORF_H


#include "ArenstorfPoint.h"
#include <ostream>

/**
 * Static class with one public method which calculates arenstorfCourse.
 */
class Arenstorf
{
public:
     /**
     * Compute Arenstorf course.
     * @param init starting point.
     * @param n number of steps
     * @param m number of steps to save
     * @param dt advance in dt time
     * @param out output stream.
     * @return 0 upon success, -1 upon failure.
     */
    static int computeArenstorf(const ArenstorfPoint& currPoint, unsigned int n,
                                unsigned int m, long double dt, std:: ostream& out);

private:
    /**
     * calculate d1 which is a size needed to calculate acceleration.
     * @param x position x.
     * @param y position y.
     * @return d1.
     */
    static long double _d1(const long double &x, const long double &y);

    /**
     * calculate d2 which is a size needed to calculate acceleration.
     * @param x position x.
     * @param y positiony.
     * @return d2.
     */
    static long double _d2(const long double &x, const long double &y);

    /**
     * Calculate acceleration in x direction.
     * @param x position x.
     * @param y position y.
     * @param vely velocity y.
     * @return acceleration in x direction.
     */
    static long double _accelX(const long double &x, const long double &y, const long double &vely);

    /**
     * Calculate acceleration in y direction.
     * @param x position x.
     * @param y position y.
     * @param velx velocity x.
     * @return acceleration in x direction.
     */
    static long double _accelY(const long double &x, const long double &y, const long double &velx);

     /**
     * Calculate new postion in a requested axis..
     * @param vel current velocity in the requested direction.
     * @param accel current acceleration in the requested direction.
     * @param dt advance in dt time.
     * @return new position
     */
    static long double _newPos(const long double &pos, const long double &vel, const long double &dt);

    /**
     * Calculate new velocity in a requested axis..
     * @param vel current velocity in the requested direction.
     * @param accel current acceleration in the requested direction.
     * @param dt advance in dt time.
     * @return new velocity
     */
    static long double _newVel(const long double &vel, const long double &accel, const long double &dt);
};


#endif //EX1_ARENSTORF_H
