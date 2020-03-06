#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

void disp(void);
void ellipsePlotPoints (int, int, int, int);

void init (void)
{
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glMatrixMode (GL_PROJECTION);
        gluOrtho2D (0.0, 200.0, 0.0, 200.0);
}

void setPixel (GLint xCoord, GLint yCoord)
{
        glBegin (GL_POINTS);
                glVertex2i (xCoord, yCoord);
        glEnd ( );
}

void ellipseMidpoint (int xCenter, int yCenter, int xrad, int yrad)
{
	int xrad2 = xrad * xrad;
	int yrad2 = yrad * yrad;
	int dxrad = 2 * xrad2;
	int dyrad = 2 * yrad2;
	int p;
	int x = 0;
	int y = yrad;
	int px = 0;
	int py = dxrad * y;
	
	ellipsePlotPoints (xCenter, yCenter, x, y);

	p = round (yrad2 - (xrad2 * yrad) + (0.25 * xrad2));
	while (px < py) {
		x++;
		px = px + dyrad;
		if (p < 0)
			p = p + yrad2 + px;
		else {
			y--;
			py = py - dxrad;
			p = p + yrad2 + px - py;
		}
		ellipsePlotPoints (xCenter, yCenter, x, y);
	}
	p = round (yrad2 * (x+0.5) * (x+0.5) + xrad2 * (y-1) * (y-1) - xrad2 * yrad2);
	while (y > 0) {
		y--;
		py = py - dxrad;
		if (p > 0)
			p = p + xrad2 - py;
		else {
			x++;
			px = px + dyrad;
			p = p + xrad2 - py + px;
		}
		ellipsePlotPoints (xCenter, yCenter, x, y);
	}
}

void disp(void)
{
        glClear (GL_COLOR_BUFFER_BIT);
        glColor3f (1.0f, 0.99f, 0.0f);

        glBegin(GL_LINES);
        ellipseMidpoint(100, 100, 50, 20);
        glFlush();
}

void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);
}

int main (int argc, char** argv)
{
        glutInit (&argc, argv);
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition (200, 150);
        glutInitWindowSize (800, 800);
        glutCreateWindow ("Mid point ellipse program");

        init ( );
        glutDisplayFunc (disp);
        glutMainLoop ( );
}

