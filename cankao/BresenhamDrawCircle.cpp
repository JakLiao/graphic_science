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
    glClearColor(0.0, 1.0, 0.0, 0.0);  // Set display-window color to white.
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

class screenPt
{
private:
    GLint x,y;
public:
    screenPt(){
        x = y =0;
    }
    void setCoords(GLint xCoordValue,GLint yCoordValue){
        x = xCoordValue;
        y = yCoordValue;
    }

    GLint getx() const
    {
        return x;
    }
    GLint gety() const
    {
        return y;
    }
    void incrementx()
    {
        x ++;
    }
    void decrementy()
    {
        y--;
    }
};

void setPixel(GLint xCoord,GLint yCoord)
{
    glBegin(GL_POINTS);
        glVertex2i(xCoord,yCoord);
    glEnd();
    //glFlush();
}

void circleMidpoint(GLint xc,GLint yc,GLint radius)
{
    glColor3f(1.0,0.0,0.0);
    screenPt circPt;
    GLint p = 1 - radius;

    circPt.setCoords(0,radius);

    void circlePlotPoints(GLint,GLint,screenPt);

    circlePlotPoints(xc,yc,circPt);

    while(circPt.getx()< circPt.gety())
    {
        circPt.incrementx();
        if (p<0){
            p += 2*circPt.getx() + 1;
        }
        else{
            circPt.decrementy();
            p += 2*(circPt.getx() - circPt.gety()) + 1;
        }
        circlePlotPoints(xc,yc,circPt);
    }
}

void circleBresham(GLint xc,GLint yc,GLint radius)
{
    glColor3f(1.0,0.0,0.0);
    screenPt circPt;
    //GLint p = 1 - radius;

    circPt.setCoords(0,radius);

    void circlePlotPoints(GLint,GLint,screenPt);

    circlePlotPoints(xc,yc,circPt);

    while(circPt.getx()< circPt.gety())
    {
        GLint x1,x2,y1,y2;
        circPt.incrementx();
        x1 = circPt.getx();
        y1 = circPt.gety();
        x2 = circPt.getx();
        y2 = circPt.gety()-1;
        //if ((x1*x1+y1*y1-radius*radius)<(x2*x2+y2*y2-radius*radius)){

        //}
        if (fabs(x1*x1+y1*y1-radius*radius)>fabs(x2*x2+y2*y2-radius*radius)){
            circPt.decrementy();
           // p += 2*(circPt.getx() - circPt.gety()) + 1;
        }
        circlePlotPoints(xc,yc,circPt);
    }
}

void circlePlotPoints(GLint xc,GLint yc,screenPt circPt)
{
    setPixel(xc + circPt.getx(),yc + circPt.gety());
    setPixel(xc - circPt.getx(),yc + circPt.gety());
    setPixel(xc + circPt.getx(),yc - circPt.gety());
    setPixel(xc - circPt.getx(),yc - circPt.gety());
    setPixel(xc + circPt.gety(),yc + circPt.getx());
    setPixel(xc - circPt.gety(),yc + circPt.getx());
    setPixel(xc + circPt.gety(),yc - circPt.getx());
    setPixel(xc - circPt.gety(),yc - circPt.getx());
}

void pointsFun(void)
{
    glPointSize(3.0);
    glEnable(GL_POINT_SMOOTH);
    glClear(GL_COLOR_BUFFER_BIT);
    circleBresham(100,100,30);
    glFlush();
}

int main (int argc, char** argv)
{

    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (400, 300);      // Set display-window width and height.
    glutCreateWindow ("An Example OpenGL Program"); // Create display window.

	init();                           // Execute initialization procedure.
    glutDisplayFunc (pointsFun);       // Send graphics to display window.
    glutMainLoop ( );// Send graphics to display window.                  // Display everything and wait.
	return 0;
}

