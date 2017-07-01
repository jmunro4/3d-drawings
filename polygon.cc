#include <GL/glut.h>
#include "edge.h"
#include "polygon.h"
#include "points.h"
#include <vector>
#include <iostream>

using namespace std;

Polygon::Polygon()
{
  GLfloat* color = new GLfloat[3];
  this->color = color;

  GLfloat* fillcolor = new GLfloat[3];
  this->fillcolor = fillcolor;

  vector<Edge*> edges;
  this->edges = edges;

  this->numE = 0;
  this->tofill = false;
}

Polygon::~Polygon()
{
  delete[] this->color;
  delete[] this->fillcolor;
  int size = this->edges.size();
  for(int i = 0; i < size; i++)
    {
      delete this->edges[i];
    }
  this->edges.clear();
}

Point Polygon::getStart()
{
  return this->startPoly;
}

Point Polygon::getEnd()
{
  return this->endPoly;
}
 
void Polygon::setStart(Point start)
{
  this->startPoly = start;
}

void Polygon::setEnd(Point end)
{
  this->endPoly = end;
  Edge* finE = new Edge(this->startPoly, this->endPoly, this->color);
  this->addEdge(finE);
}

Point Polygon::getCentroid()
{
  int size = this->edges.size();
  float centx = 0;
  float centy = 0;
  for(int i = 0; i < size; i++)
    {
      centx += this->edges[i]->getStart().getX();
      centx += this->edges[i]->getEnd().getX();
      centy += this->edges[i]->getStart().getY();
      centy += this->edges[i]->getEnd().getY();
    }
  centx /= 2*size;
  centy /= 2*size;
  return Point((int) centx, (int) centy);
}

int Polygon::getNumVerts()
{
  return this->edges.size();
}

void Polygon::filled()
{
  this->tofill = true;
}

void Polygon::addEdge(Edge* edge)
{
  this->edges.push_back(edge);
  this->numE++;
}

int Polygon::numEdges()
{
  return this->numE;
}

vector<Edge*> Polygon::getEdges()
{
  return this->edges;
}

void Polygon::setEdges(vector<Edge*> edges)
{
  this->edges.clear();
  this->edges = edges;
}

void Polygon::setColor(float r, float g, float b)
{
  this->color[0] = r;
  this->color[1] = g;
  this->color[2] = b;
}

void Polygon::setFillColor(float r, float g, float b)
{
  this->fillcolor[0] = r;
  this->fillcolor[1] = g;
  this->fillcolor[2] = b;
}

void Polygon::useEdgeColor()
{
  this->fillcolor[0] = this->color[0];
  this->fillcolor[1] = this->color[1];
  this->fillcolor[2] = this->color[2];
}

void Polygon::drawPolygon()
{
  glColor3f(this->color[0], this->color[1], this->color[2]);

  for(int i = 0; i < this->numE; i++)
    {
      this->edges[i]->setColor(this->color[0], this->color[1], this->color[2]);
      this->edges[i]->drawEdge();
    }
  if(this->isFilled())
    {
      this->fillPolygon();
    }
}

bool Polygon::isFilled()
{
  return this->tofill;
}

bool Polygon::simpleCheck()
{
  int size = this->edges.size();
  for(int i = 0; i < size; i++)
    {
      Edge* curE = this->edges[i];
      for(int j = 0; j < size; j++)
	{
	  /*http://stackoverflow.com/a/563275 eqns from here, and comments on this answer*/
	  Edge* checkE = this->edges[j];
	  float ax = curE->getStart().getX();
	  float ay = curE->getStart().getY();
	  float bx = curE->getEnd().getX();
	  float by = curE->getEnd().getY();
	  float cx = checkE->getStart().getX();
	  float cy = checkE->getStart().getY();
	  float dx = checkE->getEnd().getX();
	  float dy = checkE->getEnd().getY();
	  float num1 = ((ax-cx)*(ay-by))+((ay-cy)*(bx-ax));
	  float denom1 = ((dx-cx)*(ay-by))+((dy-cy)*(bx-ax));
	  float num2 = ((cx-ax)*(cy-dy))+((cy-ay)*(dx-cx));
	  float denom2 = ((bx-ax)*(cy-dy))+((by-ay)*(dx-cx));
	  
	  if(denom1 != 0.0 && denom2 != 0.0) // parallel
	    {
	      if((num1/denom1) < 1.0 && (num1/denom1) > 0.0) // 1&0 are endpoints
		{
		  if((num2/denom2) < 1.0 && (num2/denom2) > 0.0)
		    {
		      return false;
		    }
		}
	    }
	}
    }
  return true;
}

vector<Edge*> Polygon::orderEdges()
{
  vector<Edge*> copy (this->edges);
  vector<Edge*> ordered;
  
  while(copy.size() > 0)
    {
      Edge* maximum = copy.front();
      int ymax = max(copy.front()->getStart().getY(), copy.front()->getEnd().getY());
      int xmax;
      if(ymax == copy.front()->getStart().getY())
	{
	  xmax = copy.front()->getStart().getX();
	}
      else
	{
	  xmax = copy.front()->getEnd().getX();
	}
      int maxindex = 0;
      for(int i = 1; i < (int) copy.size(); i++)
	{
	  if((copy[i]->getStart().getY() - copy[i]->getEnd().getX()) == 0)
	    {
	      int curymax = max(copy[i]->getStart().getY(), copy[i]->getEnd().getY());
	      int curxmax;
	      if(curymax == copy[i]->getStart().getY())
		{
		  curxmax = copy[i]->getStart().getX();
		}
	      else
		{
		  curxmax = copy[i]->getEnd().getX();
		}

	      if(curymax > ymax)
		{
		  maximum = copy[i];
		  ymax = curymax;
		  maxindex = i;
		}
	      else if(curymax == ymax)
		{
		  if(curxmax > xmax)
 		    {
		      maximum = copy[i];
		      xmax = curxmax;
		      maxindex = i;
		    }
		}
	    }
	}
      ordered.push_back(maximum);
      copy.erase(copy.begin()+maxindex);
    }
  return ordered;
}

int Polygon::getXint(Edge* edge, int* count)
{
  int xl = edge->getEnd().getX();
  int xu = edge->getEnd().getX();
  int yl = edge->getEnd().getY();
  int yu = edge->getEnd().getY();
  if(edge->getStart().getY() < edge->getEnd().getY())
    {
      xl = edge->getStart().getX();
      xu = edge->getEnd().getX();
      yl = edge->getStart().getY();
      yu = edge->getEnd().getY();
    }
  
  int xsc = xl;
  
  count += 2*(xl-xu);
  if(*count >= (yl-yu))
    {
      xsc += 1;
      count -= 2*(xl-xu);
    }
  return xsc;
}

void Polygon::fillPolygon() // this code hurt me too
{
  glColor3f(this->fillcolor[0], this->fillcolor[1], this->fillcolor[2]);
  
  vector<Edge*> ordered = this->orderEdges();
  vector<Edge*> active;
  active.push_back(ordered.back());
  ordered.pop_back();
  active.push_back(ordered.back());
  ordered.pop_back();
  
  int counterl = 0;
  int counterr = 0;
  
  //scanline
  for(int i = min(active.front()->getStart().getY(), active.front()->getEnd().getY()); i < max(ordered.front()->getStart().getY(), ordered.front()->getEnd().getY()); i++)
    {
      // replacing the edges
      if(i == max(active.front()->getStart().getY(), active.front()->getEnd().getY()))
	{
	  active.erase(active.begin());
	  active.insert(active.begin(), ordered.front());
	  ordered.erase(ordered.begin());
	}
      if(i == max(active.back()->getStart().getY(), active.back()->getEnd().getY()))
	{
	  active.erase(active.end());
	  active.insert(active.end(), ordered.front());
	  ordered.erase(ordered.begin());
	}
      int xl = this->getXint(active.front(), &counterl);
      int xr = this->getXint(active.back(), &counterr);
      for(int j = xl+1; j < xr; j++)
	{
	  glVertex2i(j, i);
	}
      
    }
}
