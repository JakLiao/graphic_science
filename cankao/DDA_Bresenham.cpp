/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

int round(const float a)
{
	return (int)(a+0.5);
}

void lineDDA(int x0,int y0,int xEnd,int yEnd)
{
    glColor3f(0.0,0.0,1.0);
    glPointSize(3.0f);
	int dx = xEnd - x0;
	int dy = yEnd - y0;
	int steps,k;
	float xIncrement,yIncrement,x = x0,y = y0;

	if(fabs (dx) > fabs(dy))
		steps = fabs(dy);
	else
		steps = fabs(dx);
	xIncrement = (float)(dx)/(float)(steps);
	yIncrement = (float)(dy)/(float)(steps);

	glBegin(GL_POINTS);
	glVertex2i(round(x),round(y));
	glEnd();
	glFlush();
	for (k=0;k<steps;k++)
	{
		x += xIncrement;
		y += yIncrement;
		glBegin(GL_POINTS);
		glVertex2i(round(x),round(y));
		glEnd();
		glFlush();
	}
}

void lineBres(int x0,int y0,int xEnd,int yEnd)
{
    glColor3f(1.0,0.0,0.0);
    glPointSize(3.0f);
	int dx = fabs(xEnd - x0);
	int dy = fabs(yEnd - y0);
	int p = 2*dy-dy;
	int twoDy = 2*dy,twoDyMinusDx = 2*(dy - dx);
	int x,y;

	if (x0>xEnd)
	{
	    x = xEnd;
	    y = yEnd;
	    xEnd = x0;
	}
	else
	{
	    x = x0;
	    y = y0;
	}

	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();

	while(x < xEnd)
	{
	    x++;
	    if (p < 0)
            p += twoDy;
        else
        {
            y++;
            p += twoDyMinusDx;
        }
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
        glFlush();
	}
}

void pointFun()
{
	int x0 = 0,y0 = 0,xEnd = 100,yEnd = 100;
	//scanf("%d%d%d%d",&x0,&y0,&xEnd,&yEnd);
	lineDDA(x0,y0+1,xEnd,yEnd);
	lineBres(x0+1,y0,xEnd,yEnd);
}

int main (int argc, char** argv)
{

    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (800, 600);      // Set display-window width and height.
    //glutFullScreen();
    glutCreateWindow ("An Example OpenGL Program"); // Create display window.
	init();                           // Execute initialization procedure.
    glutDisplayFunc (pointFun);       // Send graphics to display window.
    glutMainLoop ( );// Send graphics to display window.                  // Display everything and wait.
	return 0;
}
