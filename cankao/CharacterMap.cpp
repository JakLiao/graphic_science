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

#include <stdlib.h>

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}
void CharMap(void)
{
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
   // glColor3f (0.0, 0.0, 0.0);      // Set line segment color to red.
	glColor3f(0.0,0.0,0.0);
	char text[] = {'a','A','b','B','c','C','d','D','e','E','f','F'};
	glRasterPos2i(20,40);
	for (int k=0;k<12;k++){
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[k]);
        //glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[k]);
	}
	glScalef(0.1,0.1,0.0);
	glRotatef(300,20.0,20.0,0.0);
	glRasterPos2i(20,40);
	for (int k=0;k<12;k++){
	    glutStrokeCharacter(GLUT_STROKE_ROMAN,text[k]);
        //glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[k]);
	}
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
    glutDisplayFunc (CharMap);       // Send graphics to display window.
    glutMainLoop ( );
    return 0;                 // Display everything and wait.
}
/*由于OPENGL ES 取消了QUAD 等的支持，所以所有多边形都得需要从三角面片来组合成。这样就需要通过GL_TRIANGLE_FAN和GL_TRIANGLE_STRIP来组织顶点，
通过画多个三角面片来组成一个需要得形状。
GL_TRIANGLE_FAN 和 GL_TRIANGLE_STRIP 就决定了不同得顶点组织方式。
GL_TRIANGLE_STRIP - OpenGL的使用将最开始的两个顶点出发，然后遍历每个顶点，这些顶点将和他的前2个顶点一起组成一个三角形。
GL_TRIANGLE_FAN - 在跳过开始的2个顶点，然后遍历每个顶点，让OpenGL将这些顶点和它前一个，以及数组的第一个顶点一起组成一个三角形。
*/
