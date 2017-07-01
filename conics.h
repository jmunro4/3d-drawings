#include <GL/glut.h>
#include "points.h"
#include "matrix.h"

#ifndef CONICS_H
#define CONICS_H

class Circle
{
 protected:
  Point center;
  Point edge;
  GLfloat* color;
  GLfloat* fillcolor;
  bool tofill;
 public:
  Circle();
  ~Circle();
  void setCenter(Point center);
  void setEdge(Point edge);
  void setColor(float r, float g, float b);
  void setFillColor(float r, float g, float b);
  void useEdgeColor();
  void filled();
  Point getCenter();
  Point getEdge();
  int getRadius();
  void drawCircle();
  void plotSymmetry(GLint x, GLint y, GLint xcent, GLint ycent);
  bool isFilled();
  void fillCircle(); 
};

class Ellipse 
{
 protected:
  Point center;
  Point corner;
  GLfloat* color;
  GLfloat* fillcolor;
  bool tofill;
  Matrix rotation;
 public:
  Ellipse();
  ~Ellipse();
  void setCenter(Point center);
  void setCorner(Point corner);
  void setRotation(Matrix rotation);
  void setColor(float r, float g, float b);
  void setFillColor(float r, float g, float b);
  void useEdgeColor();
  void filled();
  Point getCenter();
  Point getCorner();
  long getXradius();
  long getYradius();
  void drawEllipse();
  void plotSymmetry(GLint x, GLint y, GLint xcent, GLint ycent);
  bool isFilled();
  void fillSymmetry(GLint x, GLint y, GLint xcent, GLint ycent);
  void fillEllipse(); 
};

#endif
