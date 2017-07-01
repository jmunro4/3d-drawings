Jonathan Munro

Files submitted:
sgp.cc/.h
points.cc/.h
edge.cc/.h
conics.cc/.h
debug.txt
readme.txt

The project is contained in sgp.cc, every other part contains objects
that are necissary for the program to run. Everything can be compilled
with the command 'make all'.

---sgp---
To compile: make sgp
To run: ./sgp
Description:
This program creates a GL display in which various objects can be drawn. The
object that you want to draw is chosen in the side bar and the options are:
-Line: Left click in two different positions on the screen to create a line
between those locations.
-Polygon: Left click in any position on the screen to place a vertex of the 
polygon. Right click to draw the polygon.
-Circle: Left click first in the location of the center of the circle and then
left click again at the distance for the edge of the circle.
-Ellipse: Left click first for the center of the ellipse. The next left click
indicates the max height and max width of the ellipse.
The button marked 'Clear' cleans the screen. The color of the object can be 
set using the color drop down menu. The sliders indicate the intensity of the
color. The fill menu works the same way with an option to have a fill and the
option to use the same color as the object line. The transformation menu has
functionality for translation, scaling, rotation, and shearing. Translation
is set by clicking on the x or y translator and dragging the mouse to represent
the displacement in that direction. Scaling is set by entering a number from 
-100 to 100 in the boxes labeled x and y. Rotation is set by the slider which
represents 360 degrees. Shearing is set in a similar manner as rotation, but 
first the direction of shear is set in the two button option of x and y. The 
transformations that apply to the active object are activated by clicking the 
'Apply' button. Transformations that are legal for each object are:
-Line: translation, rotation, scaling.
-Polygon: translation, rotation, scaling, shearing.
-Circle: translation, scaling.
-Ellipse: translation, scaling, rotation.
To use polymorphing draw a polygon into the main window, when the "Polymorph" 
button is pressed another window will appear. Drawing a second polygon in this
window in the same manner of drawing a normal polygon, then clicking the right
mouse button a second time (after the initial right click to finish the polygon)
to start the morphing. The polygon in the first window will only morph into the
second polygon if they have the same number of vertices and the second polygon
is simple. Otherwise the second polygon will clear and it is posible to redraw
the second polygon. If the shape is valid the morphing window will hide. Do 
not attempt to use polymorphing twice in one session.
To exit use the 'x' in the upper right hand of either (includeing the morphing
window) window.

Known issues:
- Technically draw line has no functionallity for drawing any line with a 
slope of 1 or -1. 
- Polymorphing breaks apart the shape and reforms it
- Filled Ellipses are slightly transparent when rotated
- Overlaps for the fill
- Polygon fill doesn't actually work
