#include <GL/glui.h>
#include "sgp.h"
#include <iostream>
#include "points.h"
#include "edge.h"
#include "polygon.h"
#include "conics.h"
#include "matrix.h"
#include <cmath>
#include <vector>

using namespace std;

void init()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, 200.0, 0.0, 150.0);

  glClear(GL_COLOR_BUFFER_BIT);
}

void idle()
{
  if(step < 1.0)
    {
      glutSetWindow(glutWindow);
      glutPostRedisplay();
    }
  step += stepSize;
}

void transformation() 
{
  // CREATES MATRICES AND APPLIES THEM TO OBJECT
  translation.setIdentity();
  scaling.setIdentity();
  rotation.setIdentity();
  shearing.setIdentity();
  transform.setIdentity();

  translation[0][2] = xtrans;
  translation[1][2] = -ytrans;
  
  scaling[0][0] = xscale;
  scaling[1][1] = yscale;
  
  rotation[0][0] = cos(theta);
  rotation[0][1] = -sin(theta);
  rotation[1][0] = sin(theta);
  rotation[1][1] = cos(theta);

  if(object == 0 && lineVector.size() > 0) // line
    {      
      Edge* lineTrans = lineVector.back();

      xf = (lineTrans->getEnd().getX() + lineTrans->getStart().getX())/2;
      yf = (lineTrans->getEnd().getY() + lineTrans->getStart().getY())/2;

      scaling[0][2] = xf - scaling[0][0]*xf;
      scaling[1][2] = yf - scaling[1][1]*yf;

      rotation[0][2] = xf*(1-cos(theta)) + yf*sin(theta);
      rotation[1][2] = yf*(1-cos(theta)) - xf*sin(theta);

      transform = rotation * scaling * translation;
      
      Point newStart = transform * lineTrans->getStart();
      Point newEnd = transform * lineTrans->getEnd();
      lineTrans->setStart(newStart);
      lineTrans->setEnd(newEnd);
    }
  else if(object == 1 && polyVector.size() > 0) // polygon
    {
      Polygon* polyTrans = polyVector.back();
      Point center = polyTrans->getCentroid();
      xf = center.getX();
      yf = center.getY();

      scaling[0][2] = xf - scaling[0][0]*xf;
      scaling[1][2] = yf - scaling[1][1]*yf;

      rotation[0][2] = xf*(1-cos(theta)) + yf*sin(theta);
      rotation[1][2] = yf*(1-cos(theta)) - xf*sin(theta);

      cout << xshear << ',' << yshear << endl;
      if(sheardirection == 0) // x
	{
	  shearing[0][1] = xshear;
	  shearing[0][2] = -xshear * yf;
	}
      else if(sheardirection == 1) // y
	{
	  shearing[1][0] = yshear;
	  shearing[1][2] = -yshear * xf;
	}

      transform = shearing * rotation * scaling * translation;
            
      vector<Edge*> polyEdges = polyTrans->getEdges();
      for(int i = 0; i < polyTrans->numEdges(); i++)
	{
	  Edge* curE = polyEdges[i];
	  Point newVertex = transform * curE->getStart();
	  curE->setStart(newVertex);
	  newVertex = transform * curE->getEnd();
	  curE->setEnd(newVertex);
	}
    }
  else if(object == 2 && circleVector.size() > 0) // circle
    {
      Circle* circTrans = circleVector.back();
     
      xf = circTrans->getCenter().getX();
      yf = circTrans->getCenter().getY();

      scaling[1][1] = xscale;
      scaling[0][2] = xf - scaling[0][0]*xf;
      scaling[1][2] = yf - scaling[1][1]*yf;

      transform = scaling * translation;
            
      Point newCenter = translation * circTrans->getCenter();
      Point newEdge = transform * circTrans->getEdge();
      circTrans->setCenter(newCenter);
      circTrans->setEdge(newEdge);
    }
  else if(object == 3 && ellipseVector.size() > 0) // ellipse
    {
      Ellipse* ellipTrans = ellipseVector.back();
      
      xf = ellipTrans->getCenter().getX();
      yf = ellipTrans->getCenter().getY();

      scaling[0][2] = xf - scaling[0][0]*xf;
      scaling[1][2] = yf - scaling[1][1]*yf;
						
      rotation[0][2] = xf*(1-cos(theta)) + yf*sin(theta);
      rotation[1][2] = yf*(1-cos(theta)) - xf*sin(theta);
      
      transform = scaling * translation; 
      
      Point newCenter = translation * ellipTrans->getCenter();
      Point newEdge = transform * ellipTrans->getCorner();
      ellipTrans->setCenter(newCenter);
      ellipTrans->setCorner(newEdge);
      ellipTrans->setRotation(rotation);
    }
}

void drawLine()
{
  int size = lineVector.size();
  for(int i = 0; i < size; i++)
    {
      glBegin(GL_POINTS);
      lineVector[i]->drawEdge();
      glEnd();
    }
}

void drawShape()
{
  int size = polyVector.size();
  for(int i = 0; i < size; i++)
    {
      glBegin(GL_POINTS);
      polyVector[i]->drawPolygon();
      glEnd();
    }
}

void drawCircle()
{
  int size = circleVector.size();
  for(int i = 0; i < size; i++)
    {
      glBegin(GL_POINTS);
      circleVector[i]->drawCircle();
      glEnd();
    }
}

void drawEllipse()
{
  int size = ellipseVector.size();
  for(int i = 0; i < size; i++)
    {
      glBegin(GL_POINTS);
      ellipseVector[i]->drawEllipse();
      glEnd();
    }
}

void drawMorph()
{
  int size = morphVector.size();
  for(int i = 0; i < size; i++)
    {
      glBegin(GL_POINTS);
      morphVector[i]->drawEdge();
      glEnd();
    }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glPointSize(1.0);
  gluOrtho2D(0.0, widthWin, heightWin, 0.0);
  
  if(morphGo == true) // morphing
    {
      vector<Edge*> orig = polyVector.back()->getEdges();
      for(int i = 0; i < (int) morphVector.size(); i++)
	{
	  point.setX(orig[i]->getStart().getX() + step * (morphVector[i]->getStart().getX() - orig[i]->getStart().getX()));
	  point.setY(orig[i]->getStart().getY() + step * (morphVector[i]->getStart().getY() - orig[i]->getStart().getY()));
	  orig[i]->setStart(point);

	  point.setX(orig[i]->getEnd().getX() + step * (morphVector[i]->getEnd().getX() - orig[i]->getEnd().getX()));
	  point.setY(orig[i]->getEnd().getY() + step * (morphVector[i]->getEnd().getY() - orig[i]->getEnd().getY()));
	  orig[i]->setEnd(point);
	}
      poly->setEdges(orig);
      if(orig.back()->getEnd().getY() == morphVector.back()->getEnd().getY())
	{
	  morphGo = false;
	  morphVector.clear();
	}
    }
  if(lineVector.size() > 0) // line
    {
      drawLine();
    }
  if(polyVector.size() > 0) // polygon
    {
      drawShape();
    }
  if(circleVector.size() > 0) // circle
    {
      drawCircle();
    }
  if(ellipseVector.size() > 0) // ellipse
    {
      drawEllipse();
    }

  glutSwapBuffers();
  glFlush();
}  

void morphDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glPointSize(1.0);
  gluOrtho2D(0.0, widthWin, heightWin, 0.0);

  if(morphVector.size() > 0)
    {
      drawMorph();
    }

  glutSwapBuffers();
  glFlush();
}


void reshape(int width, int height)
{
  widthWin = width;
  heightWin = height;

  GLUI_Master.auto_set_viewport();

  glViewport(0, 0, (GLsizei) width, (GLsizei) height);

  glClear(GL_COLOR_BUFFER_BIT);
  
  glutPostRedisplay();
}

void morphMouse(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startP == false)
    {
      point.setX(x);
      point.setY(y);
      polyEdge = new Edge;
      polyEdge->setStart(point);
      morphPoly = new Polygon;
      morphPoly->setStart(point);
      morphnumverts = 1;
      startP = true;
      cout << "Number of vertices needed: " << polyVector.back()->getNumVerts() << " Current number of vertices: " << morphnumverts << endl;
    }
  else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startP == true)
    {
      point.setX(x);
      point.setY(y);
      polyEdge->setEnd(point);
      morphPoly->addEdge(polyEdge);
      morphVector.push_back(polyEdge);
      polyEdge = new Edge;
      polyEdge->setStart(point);
      morphnumverts++;
      cout << "Number of vertices needed: " << polyVector.back()->getNumVerts() << " Current number of vertices: " << morphnumverts << endl;
    }
  else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && startP == true)
    {
      morphPoly->setEnd(point);
      polyEdge->setEnd(morphPoly->getStart());
      morphVector.push_back(polyEdge);
      startP = false;
      morphPoly->setColor(0.0, 0.0, 0.0);
      cout << "Number of vertices needed: " << polyVector.back()->getNumVerts() << " Current number of vertices: " << morphnumverts << endl;
    }
  else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && startP == false)
    {
      if(morphnumverts == polyVector.back()->getNumVerts() && morphPoly->simpleCheck())
	{
	  morphGo = true;
	  glutHideWindow();
	  glutSetWindow(glutWindow);
	  glutIdleFunc(idle);
	}
      else
	{
	  morphVector.clear();
	}
    }
  glutPostRedisplay();
}

void gluiControlCB(int controlID)
{
  if(controlID == 2) // clear
    {
      lineVector.clear();
      polyVector.clear();
      circleVector.clear();
      ellipseVector.clear();

      glClear(GL_COLOR_BUFFER_BIT);
    }
  else if(controlID == 3)
    {
      // Call transformation
      transformation();
      xtrans = 0;
      ytrans = 0;
      glClear(GL_COLOR_BUFFER_BIT);
    }
  else if(controlID == 4)
    {
      morphing = true;
      morphWin = glutCreateWindow("Morphing");
      init();
      glutDisplayFunc(morphDisplay);
      glutMouseFunc(morphMouse);
    }

  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
  if(object == 0) // line
    {
      if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startL == false)
	{
	  point.setX(x);
	  point.setY(y);
	  line = new Edge;
	  line->setStart(point);
	  startL = true;
	}
      else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startL == true)
	{
	  point.setX(x);
	  point.setY(y);
	  line->setEnd(point);
	  startL = false;
	  line->setColor(rEdge, gEdge, bEdge);
	  lineVector.push_back(line);
	}
    }
  else if(object == 1) // polygon
    {
      if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startP == false)
	{
	  point.setX(x); // coords x
	  point.setY(y); // coords y
	  polyEdge = new Edge; // new line
	  polyEdge->setStart(point); // start line
	  poly = new Polygon;
	  poly->setStart(point);
	  startP = true;
	}
      else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startP == true)
	{
	  point.setX(x);
	  point.setY(y);
	  polyEdge->setEnd(point);
	  poly->addEdge(polyEdge);
	  polyEdge = new Edge;
	  polyEdge->setStart(point);	  
	}
      else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && startP == true)
	{
	  poly->setEnd(point);
	  delete polyEdge;
	  startP = false;
	  poly->setColor(rEdge, gEdge, bEdge);
	  if(filled == 1)
	    {
	      poly->filled();
	      if(sameColor == 1)
		{
		  poly->useEdgeColor();
		}
	      else
		{
		  poly->setFillColor(rFill, gFill, bFill);
		}
	    }
	  if(poly->simpleCheck())
	    {
	      polyVector.push_back(poly);
	    }
	}
    }
  else if(object == 2) // circle
    {
      if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startC == false)
	{
	  point.setX(x);
	  point.setY(y);
	  circle = new Circle;
	  circle->setCenter(point);
	  startC = true;
	}
      else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startC == true)
	{
	  point.setX(x);
	  point.setY(y);
	  circle->setEdge(point);
	  startC = false;
	  circle->setColor(rEdge, gEdge, bEdge);
	  if(filled == 1)
	    {
	      circle->filled();
	      if(sameColor == 1)
		{
		  circle->useEdgeColor();
		}
	      else
		{
		  circle->setFillColor(rFill, gFill, bFill);
		}
	    }
	  circleVector.push_back(circle);
	}
    }
  else if(object == 3) // ellipse
    {
      if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startE == false)
	{
	  point.setX(x);
	  point.setY(y);
	  ellipse = new Ellipse;
	  ellipse->setCenter(point);
	  startE = true;
	}
      else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startE == true)
	{
	  point.setX(x);
	  point.setY(y);
	  ellipse->setCorner(point);
	  startE = false;
	  ellipse->setColor(rEdge, gEdge, bEdge);
	  if(filled == 1)
	    {
	      ellipse->filled();
	      if(sameColor == 1)
		{
		  ellipse->useEdgeColor();
		}
	      else
		{
		  ellipse->setFillColor(rFill, gFill, bFill);
		}
	    }
	  ellipseVector.push_back(ellipse);
	}
    }
  glutPostRedisplay();
}



int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(widthWin, heightWin); // 600 x 500

  glutWindow = glutCreateWindow("Drawing");
  init();
  glutDisplayFunc(display);
  GLUI_Master.set_glutReshapeFunc(reshape);
  GLUI_Master.set_glutMouseFunc(mouse);
  

  /***GLUI***/
  
  GLUI* control = GLUI_Master.create_glui_subwindow(glutWindow, GLUI_SUBWINDOW_RIGHT);//"Control Window");
  control->set_main_gfx_window(glutWindow);
  
  // Object
  GLUI_Rollout* roll_obj = control->add_rollout("Object", true);
  GLUI_RadioGroup* objRadio = control->add_radiogroup_to_panel(roll_obj, &object);
  control->add_radiobutton_to_group(objRadio, "Line");
  control->add_radiobutton_to_group(objRadio, "Polygon");
  control->add_radiobutton_to_group(objRadio, "Circle");
  control->add_radiobutton_to_group(objRadio, "Ellipse");

  // Color
  GLUI_Rollout* roll_color = control->add_rollout("Color", false);

  control->add_statictext_to_panel(roll_color, "Red");
  GLUI_Scrollbar redEdge = GLUI_Scrollbar(roll_color, "Red", GLUI_SCROLL_HORIZONTAL, rEpoint);
  redEdge.set_float_limits(0.0, 1.0);

  control->add_statictext_to_panel(roll_color, "Green");
  GLUI_Scrollbar greenEdge = GLUI_Scrollbar(roll_color, "Green", GLUI_SCROLL_HORIZONTAL, gEpoint);
  greenEdge.set_float_limits(0.0, 1.0);

  control->add_statictext_to_panel(roll_color, "Blue");
  GLUI_Scrollbar blueEdge = GLUI_Scrollbar(roll_color, "Blue", GLUI_SCROLL_HORIZONTAL, bEpoint);
  blueEdge.set_float_limits(0.0, 1.0);

  // Fill
  GLUI_Rollout* roll_fill = control->add_rollout("Fill", false);
  
  control->add_checkbox_to_panel(roll_fill, "Fill", &filled);

  control->add_statictext_to_panel(roll_fill, "Red");
  GLUI_Scrollbar redFill = GLUI_Scrollbar(roll_fill, "Red", GLUI_SCROLL_HORIZONTAL, rFpoint);
  redFill.set_float_limits(0.0, 1.0);

  control->add_statictext_to_panel(roll_fill, "Green");
  GLUI_Scrollbar greenFill = GLUI_Scrollbar(roll_fill, "Green", GLUI_SCROLL_HORIZONTAL, gFpoint);
  greenFill.set_float_limits(0.0, 1.0);

  control->add_statictext_to_panel(roll_fill, "Blue");
  GLUI_Scrollbar blueFill = GLUI_Scrollbar(roll_fill, "Blue", GLUI_SCROLL_HORIZONTAL, bFpoint);
  blueFill.set_float_limits(0.0, 1.0);

  control->add_checkbox_to_panel(roll_fill, "Use Line Color", &sameColor);

  // Transformation
  GLUI_Rollout* roll_trans = control->add_rollout("Transformation", true);
  control->add_statictext_to_panel(roll_trans, "Use Object Menu to choose object");

  control->add_statictext_to_panel(roll_trans, "Translation");
  control->add_translation_to_panel(roll_trans, "x", GLUI_TRANSLATION_X, xtranspoint);
  control->add_translation_to_panel(roll_trans, "y", GLUI_TRANSLATION_Y, ytranspoint);

  control->add_statictext_to_panel(roll_trans, "Scaling Factor (x100)");
  GLUI_EditText* xscalefactor = control->add_edittext_to_panel(roll_trans, "x, circle", GLUI_EDITTEXT_FLOAT, xscalepoint);
  xscalefactor->set_float_limits(-100.0, 100.0);

  GLUI_EditText* yscalefactor = control->add_edittext_to_panel(roll_trans, "y", GLUI_EDITTEXT_FLOAT, yscalepoint);
  yscalefactor->set_float_limits(-100.0, 100.0);

  control->add_statictext_to_panel(roll_trans, "Rotation");
  GLUI_Scrollbar rotAngle = GLUI_Scrollbar(roll_trans, "Rotation", GLUI_SCROLL_HORIZONTAL, thetapoint);
  rotAngle.set_float_limits(0.0, 6.283185307);

  control->add_statictext_to_panel(roll_trans, "Shearing");
  GLUI_RadioGroup* shearRadio = control->add_radiogroup_to_panel(roll_trans, &sheardirection);
  control->add_radiobutton_to_group(shearRadio, "X");
  control->add_radiobutton_to_group(shearRadio, "Y");
  
  GLUI_EditText* xshearfactor = control->add_edittext_to_panel(roll_trans, "x", GLUI_EDITTEXT_FLOAT, xshearpoint);
  xshearfactor->set_float_limits(-5.0, 5.0);

  GLUI_EditText* yshearfactor = control->add_edittext_to_panel(roll_trans, "y", GLUI_EDITTEXT_FLOAT, yshearpoint);
  yshearfactor->set_float_limits(-5.0, 5.0);
  
  control->add_button_to_panel(roll_trans, "Apply", 3, gluiControlCB);

  control->add_button("PolyMorph", 4, gluiControlCB);

  control->add_button("Clear", 2, gluiControlCB);

  control->set_main_gfx_window(glutWindow);
  GLUI_Master.set_glutIdleFunc(NULL);

  glutMainLoop();
  
  return 0;
}
