#include "ArenstorfPoint.h"

/**
* Print an Arenstorf Point to an output stream.
* @param os an output stream to print the given Arenstorf Point to.
* @param point An AenstorfPoint object.
* @return The used stream.
*/
std::ostream &operator<<(std::ostream &os, const ArenstorfPoint &point)
{
    os << point._posx << ", " << point._posy;
    return os;
}

/**
* @return x position.
*/
long double ArenstorfPoint::getX() const
{
    return _posx;
}

/**
* @return y position.
*/
long double ArenstorfPoint::getY() const
{
    return _posy;
}

/**
 * @return x velocity.
 */
long double ArenstorfPoint::getVelx() const
{
    return _velx;
}

/**
* @return y velocity.
*/
long double ArenstorfPoint::getVely() const
{
    return _vely;
}



