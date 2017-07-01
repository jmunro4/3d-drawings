#include <GL/glui.h>
#include "points.h"
#include "edge.h" 
#include "polygon.h"
#include "conics.h"
#include <vector>
#include "matrix.h"

using namespace std;

#ifndef SGP_H
#define SGP_H

int widthWin = 900;
int heightWin = 900;
int glutWindow;
int morphWin;

Matrix translation(3,3);
float xtrans = 0;
float ytrans = 0;
Matrix scaling(3,3);
float xscale = 1.0;
float yscale = 1.0;
float xf = 0;
float yf = 0;
Matrix rotation(3,3);
GLfloat theta = 0;
Matrix shearing(3,3);
int sheardirection;
float xshear = 0;
float yshear = 0;

Matrix transform(3,3);

Point point;
bool startL = false;
bool startP = false;
bool startC = false;
bool startE = false;

Edge* line;
Edge* polyEdge;
Polygon* poly;
Circle* circle;
Ellipse* ellipse;
Polygon* morphPoly;

vector<Edge*> lineVector;
vector<Polygon*> polyVector;
vector<Circle*> circleVector;
vector<Ellipse*> ellipseVector;

vector<Edge*> morphVector;

// animation //
float step = 0.0;
float stepSize = 0.025;
bool morphing = false;
int morphnumverts = 0;
bool morphGo = false;


// GLUI //

// Object
int object;

// Color
GLfloat rEdge = 0;
GLfloat *rEpoint = &rEdge;
GLfloat gEdge = 0;
GLfloat *gEpoint = &gEdge;
GLfloat bEdge = 0;
GLfloat *bEpoint = &bEdge;

// Fill
int filled; // checked = 1
int sameColor;
GLfloat rFill = 0;
GLfloat *rFpoint = &rFill;
GLfloat gFill = 0;
GLfloat *gFpoint = &gFill;
GLfloat bFill = 0;
GLfloat *bFpoint = &bFill;

// Transformation

GLfloat *thetapoint = &theta;
float *xscalepoint = &xscale;
float *yscalepoint = &yscale;
float *xtranspoint = &xtrans;
float *ytranspoint = &ytrans;
float *xshearpoint = &xshear;
float *yshearpoint = &yshear;

#endif
