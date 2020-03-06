#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

static GLfloat theta = 0.0;
float Rg = 1, rg = 0.4, rho = 0.25 , speed = 0.01;

void DrawSpiro(float R, float r, float rho)
{
   float t = 0.0;
   float x, y, x1, y1;

   x1 = (R - r)*cos(r/R*t) + rho*cos(((R - r) / r)*t);
   y1 = (R - r)*sin(r/R*t) - rho*sin(((R - r) / r)*t);

   for (int i = 0; i < 10000; i++)
   {
      t = i * speed;
  
      x = (R - r)*cos(r/R*t) + rho*cos(((R - r) / r)*t);
      y = (R - r)*sin(r/R*t) - rho*sin(((R - r) / r)*t);

      glBegin(GL_LINE_LOOP);
         glColor3f(1.0f, 0.99f, 0.0f);
         glVertex2f(x1, y1);
         glVertex2f(x , y);
      glEnd();
      glFlush();
  
      x1 = x;
      y1 = y;
   }
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glRotatef(theta, 0.0, 0.0, 1.0);
   DrawSpiro(Rg, rg, rho);
   glutSwapBuffers();

   return ;
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 800);
   glutCreateWindow("Spirograph");
   glutDisplayFunc(display);
   glEnable(GL_DEPTH_TEST);  //Enable hidden surface removal
   glutMainLoop();
  
   exit(0);
}
