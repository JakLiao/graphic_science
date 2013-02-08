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
  glMatrixMode(GL_MODELVIEW);//设置当前矩阵模式为视图模型矩阵
  glLoadIdentity();
//设置视点的位置，视线的方向和相机的向上方向
  gluLookAt(0,0,0, 0,0,-1, 0,1,0); //该设置为默认设置
  glScalef(0.3,1.0,0.5); //产生比例变换，分别设置物体在x，y，z方向上缩放因子，根据需要自己可以设置
  glRotatef(45,1.0,1.0,1.0);//产生旋转变换，让物体绕（1，1，1）轴旋转45度
  glMatrixMode(GL_PROJECTION);//设置当前矩阵模式为投影矩阵
  glFrustum(-4,4,-4,4,0,20);////设置场景投影时的可视范围
}
 float points[8][3] = {{0,0,0},{0,0.5,0},{0.5,0,0},{0.5,0.5,0},{0,0,0.5},{0,0.5,0.5},{0.5,0,0.5},{0.5,0.5,0.5}};
 float colors[6][3] = {{0.25,0,0},{0.25,0.25,0.25},{0,0,0.25},{0.5,0.25,0},{0,0.25,0.25},{0.25,0,0.25}};

void vertexArray(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
// glColor3f(1.0,1.0,0.0);
 //glPolygonMode(GL_FRONT, GL_LINE);// 设置多边形的显示模式为面填充模式，该设置也是默认设置
 glFrontFace(GL_CCW); //设置前面的面的模式为逆时针模式， 该设置也是默认设置
 //glShadeModel(GL_SHADE_MODEL);// 默认就是此参数，可忽略，为了明确说明特意指定
 /* 指定顶点数组数据和颜色数组，定义顶点的索引数组,并用顶点的索引数组绘制图元*/
/*取消顶点数组和颜色数组*/
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

