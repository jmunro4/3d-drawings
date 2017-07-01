#include <GL/glui.h>
#include "edge.h"
#include "points.h"
#include <iostream>

using namespace std;

Edge::Edge(Point startPoint, Point endPoint, GLfloat* color)
{
  this->startPoint = startPoint;
  this->endPoint = endPoint;
  this->color = color;
}

Edge::Edge()
{
  GLfloat* color = new GLfloat[3];
  this->color = color;
}

Edge::~Edge()
{
  delete[] color;
}

Point Edge::getStart()
{
  return this->startPoint;
}

Point Edge::getEnd()
{
  return this->endPoint;
}

void Edge::setStart(Point start)
{
  this->startPoint = start;
}

void Edge::setEnd(Point end)
{
  this->endPoint = end;
}

void Edge::setColor(float r, float g, float b)
{
  this->color[0] = r;
  this->color[1] = g;
  this->color[2] = b;
}

void Edge::getColor()
{
  cout << '(' << color[0] << ',' << color[1] << ',' << color[2] << ')' << endl;
}
                                           

void Edge::drawEdge()
{
  glColor3f(this->color[0], this->color[1], this->color[2]);

  GLint dx = this->endPoint.getX() - this->startPoint.getX();
  GLint dy = (-this->endPoint.getY())-(-this->startPoint.getY());

  GLfloat m = float(dy)/float(dx);

  if(dx < 0)
    {
      dx *= -1;
    }
  if(dy < 0)
    {
      dy *= -1;
    }

  GLint x;
  GLint y;
  GLint p;

  GLint xi = this->startPoint.getX();
  GLint xf = this->endPoint.getX();
  GLint yi = this->startPoint.getY();
  GLint yf = this->endPoint.getY();

  if(m < 1 && m > 0)
    {
      if(this->startPoint.getX() > this->endPoint.getX())
	{
	  x = xf;
	  y = yf;
	  xf = xi;
	}
      else
	{
	  x = xi;
	  y = yi;
	}     
      glVertex2i(x,y);
      
      p = 2*dy - dx;

      while(x < xf)
	{
	  x++;
	  if(p < 0)
	    {
	      p += 2*dy;
	    }
	  else
	    {
	      y--;
	      p += (2*dy - 2*dx);
	    }
	  glVertex2i(x,y);
	}
    }
  else if(m > 1)
    {
      if(this->startPoint.getX() > this->endPoint.getX())
	{
	  x = xf;
	  y = yf;
	  yf = yi;
	}
      else
	{
	  x = xi;
	  y = yi;
	}     

      glVertex2i(x,y);
      
      p = 2*dx - dy;

      while(y > yf)
	{
	  y--;
	  if(p < 0)
	    {
	      p += 2*dx;
	    }
	  else
	    {
	      x++;
	      p += (2*dx - 2*dy);
	    }
	  glVertex2i(x,y);
	}
    }
  if(m < 0 && m > -1)
    {
      if(this->startPoint.getX() < this->endPoint.getX())
	{
	  x = xf;
	  y = yf;
	  xf = xi;
	}
      else
	{
	  x = xi;
	  y = yi;
	}     
      glVertex2i(x,y);
      
      p = 2*dy - dx;

      while(x > xf)
	{
	  x--;
	  if(p < 0)
	    {
	      p += 2*dy;
	    }
	  else
	    {
	      y--;
	      p += (2*dy - 2*dx);
	    }
	  glVertex2i(x,y);
	}
    }
  else if(m < -1)
    {
      if(this->startPoint.getX() > this->endPoint.getX())
	{
	  x = xf;
	  y = yf;
	  yf = yi;
	}
      else
	{
	  x = xi;
	  y = yi;
	}     

      glVertex2i(x,y);
      
      p = 2*dx - dy;

      while(y < yf)
	{
	  y++;
	  if(p < 0)
	    {
	      p += 2*dx;
	    }
	  else
	    {
	      x++;
	      p += (2*dx - 2*dy);
	    }
	  glVertex2i(x,y);
	}
    }
  else if(dx == 0)
    {
      if(yf > yi)
	{
	  y = yi;
	  x = xi;
	}
      else
	{
	  y = yf;
	  x = xf;
	  yf = yi;
	}
      glVertex2i(x,y);
      while(y < yf)
	{
	  y++;
	  glVertex2i(x,y);
	}
    }
  else if(dy == 0)
    {
      if(xf > xi)
	{
	  x = xi;
	  y = yi;
	}
      else
	{
	  x = xf;
	  y = yf;
	  xf = xi;
	}
      glVertex2i(x,y);
      while(x < xf)
	{
	  x++;
	  glVertex2i(x,y);
	}
    }
}
