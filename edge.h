#include <GL/glut.h>
#include "points.h"

#ifndef EDGE_H
#define EDGE_H

class Edge
{
 protected:
  Point startPoint;
  Point endPoint;
  GLfloat* color;
 public:
  Edge(Point startPoint, Point endPoint, GLfloat* color);
  Edge();
  ~Edge();
  Point getStart();
  Point getEnd();
  void setStart(Point start);
  void setEnd(Point end);
  void setColor(float r, float g, float b);
  void getColor();
  void drawEdge();

};

#endif
