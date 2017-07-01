#include <GL/glut.h>
#include "points.h"
#include "conics.h"
#include <math.h>
#include <iostream>
#include "matrix.h"

using namespace std;

Circle::Circle()
{
  GLfloat* color = new GLfloat[3];
  this->color = color;
  GLfloat* fillcolor = new GLfloat[3];
  fillcolor[0] = 0.0;
  fillcolor[1] = 0.0;
  fillcolor[3] = 0.0;
  this->fillcolor = fillcolor;
  this->tofill = false;
}

Circle::~Circle()
{
  delete[] color;
  delete[] fillcolor;
}

void Circle::setCenter(Point center)
{
  this->center = center;
}

void Circle::setEdge(Point edge)
{
  this->edge = edge;
}

void Circle::setColor(float r, float g, float b)
{
  this->color[0] = r;
  this->color[1] = g;
  this->color[2] = b;
}

void Circle::setFillColor(float r, float g, float b)
{
  this->fillcolor[0] = r;
  this->fillcolor[1] = g;
  this->fillcolor[2] = b;
}

void Circle::useEdgeColor()
{
  this->fillcolor[0] = this->color[0];
  this->fillcolor[1] = this->color[1];
  this->fillcolor[2] = this->color[2];
}

void Circle::filled()
{
  this->tofill = true;
}

Point Circle::getCenter()
{
  return this->center;
}

Point Circle::getEdge()
{
  return this->edge;
}

int Circle::getRadius()
{
  GLint dx = this->edge.getX() - this->center.getX();
  GLint dy = (-this->edge.getY())-(-this->center.getY());
  if(dx < 0)
    {
      dx *= -1;
    }
  if(dy <0)
    {
      dy *= -1;
    }
  return sqrt((dx*dx)+(dy*dy));
}

void Circle::drawCircle()
{
  glColor3f(this->color[0], this->color[1], this->color[2]);

  GLint radius = this->getRadius();
  GLint xc = this->center.getX();
  GLint yc = this->center.getY();

  int p = 1 - radius;

  glVertex2i(xc, yc-radius);
  glVertex2i(xc+radius, yc);
  glVertex2i(xc, yc+radius);
  glVertex2i(xc-radius, yc);
  
  GLint x = 0;
  GLint y = -radius;
  
  while(x <= -y)
    {
      x++;
      if(p < 0.0)
	{
	  p += 2*x + 1;
	}
      else
	{
	  y++;
	  p += 2*x + 1 + 2*y;
	}
      this->plotSymmetry(x,y,xc,yc);
    }
  if(this->isFilled())
    {
      this->fillCircle();
    }
}

void Circle::plotSymmetry(GLint x, GLint y, GLint xcent, GLint ycent)
{
  glVertex2i(xcent+x,ycent+y);
  glVertex2i(xcent+y,ycent+x);
  glVertex2i(xcent+y,ycent-x);
  glVertex2i(xcent+x,ycent-y);
  glVertex2i(xcent-x,ycent-y);
  glVertex2i(xcent-y,ycent-x);
  glVertex2i(xcent-y,ycent+x);
  glVertex2i(xcent-x,ycent+y);
}

bool Circle::isFilled()
{
  return this->tofill;
}

void Circle::fillCircle()
{
  glColor3f(this->fillcolor[0], this->fillcolor[1], this->fillcolor[2]);
  
  GLint r = this->getRadius();
  GLint xc = this->center.getX();
  GLint yc = this->center.getY();
  
  for(int i = -r+1; i < r; i++)
    {
      int x = sqrt((r*r) - (i*i));
      for(int j = -x; j <= x; j++)
	{
	  glVertex2i(xc+j, yc+i);
	}
    }
}

Ellipse::Ellipse()
{
  GLfloat* color = new GLfloat[3];
  this->color = color;
  GLfloat* fillcolor = new GLfloat[3];
  fillcolor[0] = 0.0;
  fillcolor[1] = 0.0;
  fillcolor[3] = 0.0;
  this->fillcolor = fillcolor;
  this->tofill = false;
  this->rotation = Matrix(3,3);
  this->rotation.setIdentity();
}

Ellipse::~Ellipse()
{
  delete[] color;
  delete[] fillcolor;
}

void Ellipse::setCenter(Point center)
{
  this->center = center;
}

void Ellipse::setCorner(Point corner)
{
  this->corner = corner;
}

void Ellipse::setRotation(Matrix rotation)
{
  
  Matrix rot = rotation * this->rotation;
  this->rotation = rot;
}

void Ellipse::setColor(float r, float g, float b)
{
  this->color[0] = r;
  this->color[1] = g;
  this->color[2] = b;
}

void Ellipse::setFillColor(float r, float g, float b)
{
  this->fillcolor[0] = r;
  this->fillcolor[1] = g;
  this->fillcolor[2] = b;
}

void Ellipse::useEdgeColor()
{
  this->fillcolor[0] = this->color[0];
  this->fillcolor[1] = this->color[1];
  this->fillcolor[2] = this->color[2];
}
 
void Ellipse::filled()
{
  this->tofill = true;
}

Point Ellipse::getCenter()
{
  return this->center;
}

Point Ellipse::getCorner()
{
  return this->corner;
}

long Ellipse::getXradius()
{
  long dx = this->center.getX() - this->corner.getX();
  if(dx < 0)
    {
      dx *= -1;
    }
  return dx;
}

long Ellipse::getYradius()
{
  long dy = (-this->center.getY()) - (-this->corner.getY());
  if(dy < 0)
    {
      dy *= -1;
    }
  return dy;
}

void Ellipse::drawEllipse()
{
  glColor3f(this->color[0], this->color[1], this->color[2]);

  long rx = this->getXradius();
  long ry = this->getYradius();
  long xc = this->center.getX();
  long yc = this->center.getY();

  long rx2 = rx*rx;
  long ry2 = ry*ry;

  long x = 0;
  long y = -ry;

  this->plotSymmetry(x, y, xc, yc);

  double p1 = rx2 - rx2*ry + 0.25*rx2;

  while((2*ry2*x) <= (2*rx2*-y))
    {
      x++;
      if(p1 < 0)
	{
	  p1 += 2*ry2*x + ry2;
	}
      else
	{
	  y++;
	  p1 += 2*ry2*x + 2*rx2*y + ry2;
	}
      plotSymmetry(x, y, xc, yc);
    }

  double p2 = ry2*((x+0.5)*(x+0.5)) + rx2*((-y-1)*(-y-1)) - rx2*ry2;

  while(y != 0)
    {
      y++;
      if(p2 > 0)
  	{
  	  p2 += 2*rx2*y + rx2;
  	}
      else
  	{
  	  x++;
  	  p2 += 2*ry2*x + 2*rx2*y + rx2;
  	}
      plotSymmetry(x, y, xc, yc);
    }
  if(this->isFilled())
    {
      this->fillEllipse();
    }
}

void Ellipse::plotSymmetry(GLint x, GLint y, GLint xcent, GLint ycent)
{
  Point p1(xcent+x, ycent+y, 1.0);
  Point p2(xcent+x, ycent-y, 1.0);
  Point p3(xcent-x, ycent+y, 1.0);
  Point p4(xcent-x, ycent-y, 1.0);

  Point rotP1 = this->rotation * p1;
  Point rotP2 = this->rotation * p2;
  Point rotP3 = this->rotation * p3;
  Point rotP4 = this->rotation * p4;

  glVertex2i(rotP1.getX(), rotP1.getY());
  glVertex2i(rotP2.getX(), rotP2.getY());
  glVertex2i(rotP3.getX(), rotP3.getY());
  glVertex2i(rotP4.getX(), rotP4.getY());

}

bool Ellipse::isFilled()
{
  return this->tofill;
}

void Ellipse::fillSymmetry(GLint x, GLint y, GLint xcent, GLint ycent)
{
  for(int i = -x+1; i < x; i++)
    {
      Point p1(xcent+i, ycent+y, 1.0);
      Point p2(xcent+i, ycent-y, 1.0);
      
      Point rotP1 = this->rotation * p1;
      Point rotP2 = this->rotation * p2;
      
      glVertex2i(rotP1.getX(), rotP1.getY());
      glVertex2i(rotP2.getX(), rotP2.getY());
    }
}

void Ellipse::fillEllipse()
{
  glColor3f(this->fillcolor[0], this->fillcolor[1], this->fillcolor[2]);
  
  long rx = this->getXradius();
  long ry = this->getYradius();
  long xc = this->center.getX();
  long yc = this->center.getY();

  long rx2 = rx*rx;
  long ry2 = ry*ry;

  long x = 0;
  long y = -ry;

  this->plotSymmetry(x, y, xc, yc);

  double p1 = rx2 - rx2*ry + 0.25*rx2;

  while((2*ry2*x) <= (2*rx2*-y))
    {
      x++;
      if(p1 < 0)
	{
	  p1 += 2*ry2*x + ry2;
	}
      else
	{
	  y++;
	  p1 += 2*ry2*x + 2*rx2*y + ry2;
	}
      fillSymmetry(x, y, xc, yc);
    }

  double p2 = ry2*((x+0.5)*(x+0.5)) + rx2*((-y-1)*(-y-1)) - rx2*ry2;

  while(y != 0)
    {
      y++;
      if(p2 > 0)
  	{
  	  p2 += 2*rx2*y + rx2;
  	}
      else
  	{
  	  x++;
  	  p2 += 2*ry2*x + 2*rx2*y + rx2;
  	}
      fillSymmetry(x, y, xc, yc);
    }
}
