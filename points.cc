#include <GL/glui.h>
#include "points.h"
#include <iostream>

using namespace std;

Point::Point(GLint x, GLint y, GLint z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Point::Point()
{
  this->x = 0;
  this->y = 0;
  this->z = 1;
}

Point::Point(const Point& orig)
{
  this->x = orig.x;
  this->y = orig.y;
  this->z = orig.z;
}

GLint Point::getX()
{
  return this->x;
}

GLint Point::getY()
{
  return this->y;
}

GLint Point::getZ()
{
  return this->z;
}

void Point::setX(GLint newX)
{
  this->x = newX;
}

void Point::setY(GLint newY)
{
  this->y = newY;
}

void Point::setZ(GLint newZ)
{
  this->z = newZ;
}

ostream& operator<<(ostream& out, const Point& point)
{
  Point p(point);
  out << '(' << p.getX() << ',' << p.getY() << ',' << p.getZ() << ')' << endl;
  return out;
}
