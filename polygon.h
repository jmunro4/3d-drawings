#include <GL/glut.h>
#include "edge.h"
#include "points.h"
#include <vector>

using namespace std;

#ifndef POLYGON_H
#define POLYGON_H

class Polygon
{
 protected:
  Point startPoly;
  Point endPoly;
  vector<Edge*> edges;
  GLfloat* color;
  GLfloat* fillcolor;
  int numE;
  bool simple;
  bool tofill;
 public:
  Polygon();
  ~Polygon();
  Point getStart();
  void setStart(Point start);
  Point getEnd();
  void setEnd(Point end);
  Point getCentroid();
  int getNumVerts();
  void filled();
  void addEdge(Edge* edge);
  int numEdges();
  vector<Edge*> getEdges();
  void setEdges(vector<Edge*> edges);
  void setColor(float r, float g, float b);
  void setFillColor(float r, float g, float b);
  void useEdgeColor();
  void drawPolygon();
  bool isFilled();
  bool simpleCheck();
  vector<Edge*> orderEdges();
  int getXint(Edge* edge, int* count);
  void fillPolygon();
};


#endif
