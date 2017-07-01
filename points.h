#include <GL/glut.h>
#include <ostream>

using namespace std;

#ifndef POINTS_H
#define POINTS_H


class Point
{
 protected:
  GLint x;
  GLint y;
  GLint z;
 public:
  Point(GLint x, GLint y, GLint z = 1);
  Point();
  Point(const Point&);
  GLint getX();
  GLint getY();
  GLint getZ();
  void setX(GLint newX);
  void setY(GLint newY);
  void setZ(GLint newZ);
};

ostream& operator<<(ostream&, const Point&);

#endif
