
#ifndef EX1_ARENSTORFPOINT_H
#define EX1_ARENSTORFPOINT_H

#include <ostream>


/**
 * Class definition of an ArenstorfPoint.
 * a point is built with 4 parameters. 2 for position and 2 for velocity.
 * Used in Arenstorf static class to calculate Arenstorf course.
 */
class ArenstorfPoint
{
public:
    /**
     * Constructor of ArenstorfPoint.
     * @param x position x.
     * @param y position y.
     * @param vx velocity x.
     * @param vy velocity y.
     */
    ArenstorfPoint(long double x , long double y, long double vx, long double vy):
                    _posx(x), _posy(y), _velx(vx), _vely(vy){};

     /**
     * Print an Arenstorf Point to an output stream.
     * @param os an output stream to print the given Arenstorf Point to.
     * @param point An AenstorfPoint object.
     * @return The used stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const ArenstorfPoint &point);

    /**
     * @return x position.
     */
    long double getX() const;

    /**
     * @return y position.
     */
    long double getY() const;

    /**
     * @return x velocity.
     */
    long double getVelx() const;

    /**
     * @return y velocity.
     */
    long double getVely() const;

private:
    /** fields of anArenstorfPoint. */
    long double _posx, _posy, _velx, _vely;

};


#endif //EX1_ARENSTORFPOINT_H
