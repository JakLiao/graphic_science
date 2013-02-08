#include <iostream>
#include <fstream>
#include <cmath>
#include "windows.h"
#include "GL/glut.h"
#include "glaux.h"
using namespace std;

//数据声明================================================================================================
#define MAX 70000
#define max_num 99999999

#define LEFT 1
#define RIGHT 2
#define SMALL 3
#define LARGE 4

GLfloat make_s_l=2.0;

int m,n;
int specialkey;
GLfloat max_x=-max_num,min_x=max_num,max_y=-max_num,min_y=max_num,max_z=-max_num,min_z=max_num;

struct point
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat dx;
    GLfloat dy;
    GLfloat dz;
    int num;
};
struct triangle
{
    int p1;
    int p2;
    int p3;
    GLfloat dx;
    GLfloat dy;
    GLfloat dz;
};
point ma[MAX];
triangle na[MAX];

GLfloat xrot=0.0,yrot=0.0,zrot=0.0;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };// 环境光参数
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };// 漫射光参数
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };// 光源位置


//函数声明===============================================================================================
int LoadGLTextures();
AUX_RGBImageRec *LoadBMP(char *Filename);
void render();
void reshape(int w,int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void createGLUTMenus();
void MenusEvents(int option);
void gl_Init();

//主函数==================================================================================================
/*int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH  | GLUT_RGB |GLUT_DOUBLE  );
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bunny");
    gl_Init();
    //glClearColor(0.0, 0.0, 0.0, 0.0); //背景颜色，默认为黑色
    glutDisplayFunc(render);
    //glutIdleFunc(render);             //让程序空闲时调用render
    //glutReshapeFunc(reshape);
    //glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    createGLUTMenus();
    glutMainLoop();
    return 0;
}*/


void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotated(xrot,1.0,0.0,0.0);
    glRotated(yrot,0.0,1.0,0.0);
    glRotated(zrot,0.0,0.0,1.0);


    //glColor3f(0.0F, 1.0F, 0.0F);//设置光照颜色效果没用

    int i;
    for(i=1;i<=n;i++)
    {
        glBegin(GL_TRIANGLES);//开始画三角形
        glNormal3f(ma[na[i].p1].dx,ma[na[i].p1].dy,ma[na[i].p1].dz);//第一点
        glVertex3f(ma[na[i].p1].x,ma[na[i].p1].y,ma[na[i].p1].z);
        glNormal3f(ma[na[i].p2].dx,ma[na[i].p2].dy,ma[na[i].p2].dz);//第二点
        glVertex3f(ma[na[i].p2].x,ma[na[i].p2].y,ma[na[i].p2].z);
        glNormal3f(ma[na[i].p3].dx,ma[na[i].p3].dy,ma[na[i].p3].dz);//第三点
        glVertex3f(ma[na[i].p3].x,ma[na[i].p3].y,ma[na[i].p3].z);
        glEnd();              //三角形绘制结束
    }

    glFlush();
    glutSwapBuffers();
}

void reshape(int w,int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(min_x*make_s_l, max_x*make_s_l, min_y*make_s_l, max_y*make_s_l, min_z*make_s_l, max_z*make_s_l);
}

void keyboard(unsigned char key, int x, int y)
{
    int mod;
    switch(key)
    {
    case 'q':
    case 'Q':
        xrot = 0.0f;
        yrot = -10.0f;
        zrot = 0.0f;
        glutPostRedisplay();
        break;
    case 'e':
    case 'E':
        xrot = 0.0f;
        yrot = 10.0f;
        zrot = 0.0f;
        glutPostRedisplay();
        break;
    case 'a':
    case 'A':
        xrot = -10.0f;
        yrot = 0.0f;
        zrot = 0.0f;
        glutPostRedisplay();
        break;
    case 'd':
    case 'D':
        xrot = 10.0;
        yrot = 0.0f;
        zrot = 0.0f;
        glutPostRedisplay();
        break;
    case 'w':
    case 'W':
        xrot = 0.0f;
        yrot = 0.0f;
        zrot = -10.0f;
        glutPostRedisplay();
        break;
    case 's':
    case 'S':
        xrot = 0.0f;
        yrot = 0.0f;
        zrot = 10.0f;
        glutPostRedisplay();
        break;
    case 'r':                 //组合键的使用
        {
            mod = glutGetModifiers();
            if (mod == GLUT_ACTIVE_ALT)
            {
                xrot = 0.0f;
                yrot = 0.0f;
                zrot = 10.0f;
                glutPostRedisplay();
            }
            break;
        }
    case 'o':                 //如何使用？？？
        {
            mod = glutGetModifiers();
            if (mod == (GLUT_ACTIVE_CTRL|GLUT_ACTIVE_ALT))
            {
                xrot = 0.0f;
                yrot = 0.0f;
                zrot = 10.0f;
                glutPostRedisplay();
            }
            break;
        }
    }
}

void mouse(int button, int state, int x, int y)
{
    specialkey=glutGetModifiers();
    if((state == GLUT_DOWN)&&(specialkey == GLUT_ACTIVE_ALT))
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            xrot = 0.0f;
            yrot = 0.0f;
            zrot = 10.0f;
            glutPostRedisplay();
        }
    }
}

void createGLUTMenus()
{
    int menu,submenu;

    submenu = glutCreateMenu(MenusEvents);
    glutAddMenuEntry("smaller",SMALL);
    glutAddMenuEntry("larger",LARGE);

    menu = glutCreateMenu(MenusEvents);
    glutAddMenuEntry("rotate_left",LEFT);
    glutAddMenuEntry("rotate_right",RIGHT);
    glutAddSubMenu("S_L",submenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MenusEvents(int option)
{
    switch(option)
    {
    case LEFT:
        xrot = 0.0f;
        yrot = -45.0f;
        zrot = 0.0f;
        glutPostRedisplay();
        break;
    case RIGHT:
        xrot = 0.0f;
        yrot = 45.0f;
        zrot = 0.0f;
        glutPostRedisplay();
        break;
    case LARGE:
        if(make_s_l>=1.6)make_s_l=make_s_l-0.1;
        else cout<<"已经是可缩放的最大形态了！"<<endl;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(min_x*make_s_l, max_x*make_s_l, min_y*make_s_l, max_y*make_s_l, min_z*make_s_l, max_z*make_s_l);
        glutPostRedisplay();
        break;
    case SMALL:
        if(make_s_l<=2.4)make_s_l=make_s_l+0.1;
        else cout<<"已经是可缩放的最小形态了！"<<endl;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(min_x*make_s_l, max_x*make_s_l, min_y*make_s_l, max_y*make_s_l, min_z*make_s_l, max_z*make_s_l);
        glutPostRedisplay();
    }
}

void gl_Init()
{


    glShadeModel(GL_SMOOTH);                        // 启用阴影平滑


    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);             // 设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);             // 设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);            // 设置光源位置
    glEnable(GL_LIGHT1);                            // 启用一号光源

    int i;
    //ifstream sin("bunny.vt");
   // sin>>m>>n;
    for(i=0;i<m;i++)
    {
       // sin>>ma[i].x>>ma[i].y>>ma[i].z;
        ma[i].dx=0.0;
        ma[i].dy=0.0;
        ma[i].dz=0.0;
        ma[i].num=0;
        if(ma[i].x < min_x)min_x = ma[i].x;
        if(ma[i].x > max_x)max_x = ma[i].x;
        if(ma[i].y < min_y)min_y = ma[i].y;
        if(ma[i].y > max_y)max_y = ma[i].y;
        if(ma[i].z < min_z)min_z = ma[i].z;
        if(ma[i].z > max_z)max_z = ma[i].z;
    }
    //cout<<ma[m-1].dx<<" "<<ma[m-1].dy<<" "<<ma[m-1].dz<<endl;
    for(i=1;i<=n;i++)
    {
      //  sin>>na[i].p1>>na[i].p2>>na[i].p3;
        GLfloat a1,b1,c1,a2,b2,c2;
        a1=ma[na[i].p2].x-ma[na[i].p1].x;
        b1=ma[na[i].p2].y-ma[na[i].p1].y;
        c1=ma[na[i].p2].z-ma[na[i].p1].z;
        a2=ma[na[i].p2].x-ma[na[i].p3].x;
        b2=ma[na[i].p2].y-ma[na[i].p3].y;
        c2=ma[na[i].p2].z-ma[na[i].p3].z;
        na[i].dx=b1*c2-b2*c1;
        na[i].dy=c1*a2-a1*c2;
        na[i].dz=a1*b2-a2*b1;
        ma[na[i].p1].num++;
        ma[na[i].p1].dx+=na[i].dx;
        ma[na[i].p1].dy+=na[i].dy;
        ma[na[i].p1].dz+=na[i].dz;
        ma[na[i].p2].num++;
        ma[na[i].p2].dx+=na[i].dx;
        ma[na[i].p2].dy+=na[i].dy;
        ma[na[i].p2].dz+=na[i].dz;
        ma[na[i].p3].num++;
        ma[na[i].p3].dx+=na[i].dx;
        ma[na[i].p3].dy+=na[i].dy;
        ma[na[i].p3].dz+=na[i].dz;
    }
    //cout<<na[n].p1<<" "<<na[n].p2<<" "<<na[n].p3<<endl;
    for(i=0;i<m;i++)
    {
        ma[i].dx=ma[i].dx/ma[i].num;
        ma[i].dy=ma[i].dy/ma[i].num;
        ma[i].dz=ma[i].dz/ma[i].num;
        GLfloat d=sqrt(ma[i].dx*ma[i].dx+ma[i].dy*ma[i].dy+ma[i].dz*ma[i].dz);
        ma[i].dx=ma[i].dx/d;
        ma[i].dy=ma[i].dy/d;
        ma[i].dz=ma[i].dz/d;
    }
}
