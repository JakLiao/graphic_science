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
#include<math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}
void lineSegment (void)
{
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
   // glColor3f (0.0, 0.0, 0.0);      // Set line segment color to red.
	glColor3f(0.0,0.0,0.0);
	const double TWO_PI = 6.2831853;
	GLuint regHex;
	GLdouble  theta;
	GLint x,y,k;

	regHex = glGenLists(1);
	glNewList(regHex,GL_COMPILE);
        glBegin(GL_POLYGON);
            for(k=0;k<6;k++){
                theta= TWO_PI*k/6.0;
                x=50+35*cos(theta);
                y=50+35*sin(theta);
                glVertex2i(x,y);
            }
        glEnd();
    glEndList();

    glCallList(regHex);
	glFlush();
}
int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (1000, 600);      // Set display-window width and height.
    glutCreateWindow ("An Example OpenGL Program"); // Create display window.
    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (lineSegment);       // Send graphics to display window.
    glutMainLoop ( );
    return 0;                 // Display everything and wait.
}
