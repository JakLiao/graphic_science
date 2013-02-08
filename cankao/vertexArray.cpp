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

void init(void)
{
  glClearColor(1.0,1.0,1.0,0.0);
  glMatrixMode(GL_MODELVIEW);//���õ�ǰ����ģʽΪ��ͼģ�;���
  glLoadIdentity();
//�����ӵ��λ�ã����ߵķ������������Ϸ���
  gluLookAt(0,0,0, 0,0,-1, 0,1,0); //������ΪĬ������
  glScalef(0.3,1.0,0.5); //���������任���ֱ�����������x��y��z�������������ӣ�������Ҫ�Լ���������
  glRotatef(45,1.0,1.0,1.0);//������ת�任���������ƣ�1��1��1������ת45��
  glMatrixMode(GL_PROJECTION);//���õ�ǰ����ģʽΪͶӰ����
  glFrustum(-4,4,-4,4,0,20);////���ó���ͶӰʱ�Ŀ��ӷ�Χ
}
 float points[8][3] = {{0,0,0},{0,0.5,0},{0.5,0,0},{0.5,0.5,0},{0,0,0.5},{0,0.5,0.5},{0.5,0,0.5},{0.5,0.5,0.5}};
 float colors[6][3] = {{0.25,0,0},{0.25,0.25,0.25},{0,0,0.25},{0.5,0.25,0},{0,0.25,0.25},{0.25,0,0.25}};

void vertexArray(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
// glColor3f(1.0,1.0,0.0);
 //glPolygonMode(GL_FRONT, GL_LINE);// ���ö���ε���ʾģʽΪ�����ģʽ��������Ҳ��Ĭ������
 glFrontFace(GL_CCW); //����ǰ������ģʽΪ��ʱ��ģʽ�� ������Ҳ��Ĭ������
 //glShadeModel(GL_SHADE_MODEL);// Ĭ�Ͼ��Ǵ˲������ɺ��ԣ�Ϊ����ȷ˵������ָ��
 /* ָ�������������ݺ���ɫ���飬���嶥�����������,���ö���������������ͼԪ*/
/*ȡ�������������ɫ����*/
void quad(GLint n1,GLint n2,GLint n3,GLint n4,GLint index);
    quad(6,2,3,7,1);
    quad(5,1,0,4,2);
    quad(7,3,1,5,3);
    quad(4,0,2,6,4);
    quad(2,0,1,3,5);
    quad(7,5,4,6,6);
glFlush();
}

void quad(GLint n1,GLint n2,GLint n3,GLint n4,GLint index)
{
    glColor3f(0.0,1.0,0.0);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0,1.0);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glColor3f(colors[index][0],colors[index][1],colors[index][2]);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
    //glColor3f(1.0,1.0,0);
    glBegin(GL_QUADS);
        glVertex3fv(points[n1]);
        glVertex3fv(points[n2]);
        glVertex3fv(points[n3]);
        glVertex3fv(points[n4]);
    glEnd();
}

int main (int argc, char** argv)
{

    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (600, 500);      // Set display-window width and height.
    glutCreateWindow ("An Example OpenGL Program"); // Create display window.
	init();                           // Execute initialization procedure.
    glutDisplayFunc (vertexArray);       // Send graphics to display window.
    glutMainLoop ( );// Send graphics to display window.                  // Display everything and wait.
	return 0;
}

