// 太阳、地球和月亮光照模型
#include <gl/glut.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600

int finish_without_update = 0;
int bool_check_fps =0;
float check_fps;//帧数
char buffer[50];
int nt;//控制动画速度

static GLfloat sunangle = 0.0f; //旋转角度
static GLfloat earthangle = 0.0f;

float g_fps( void (*func)(void), int n_frame )//获取当前帧数
{
    clock_t start, finish;//开始和终止时刻
    int i;
    float fps;//帧数

    printf( "Performing benchmark, please wait:" );//显示提示
    start = clock();//获取开始时刻
    for( i=0; i<n_frame; i++ )
    {
        func();
    }
    printf( "done\n" );//计算完成
    finish = clock();//获取结束时间

    fps = (float)(n_frame)/(finish-start)*CLOCKS_PER_SEC;//计算帧数
    return fps;//返回帧数
}

void selectFont(int size, int charset, const char* face)//设置显示的字体
{
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
                              charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void mod_speed(int speed)
{
    nt = speed;
}

void drawCNString(char* str)//在画面上写字，包括中文和英文
{
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    /*
    计算字符的个数
    如果是双字节字符的（比如中文字符），两个字节才算一个字符
    否则一个字节算一个字符
    */
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    // 将混合字符转化为宽字符
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // 逐个输出字符
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // 回收所有临时资源
    free(wstring);
    glDeleteLists(list, 1);
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_SMOOTH);//设置颜色填充方式：平滑方式
    glEnable(GL_LIGHT0);//开启第0号光源
    glEnable(GL_LIGHTING);//打开光照处理功能
    glEnable(GL_DEPTH_TEST);//激活深度测试，以隐藏被遮挡面
    nt=200; //控制帧数
}

void reshape(int width, int height)// 创建透视效果视图
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);//视角、高宽比、最近可视距离、最远可视距离
//    gluPerspective(75.0f, (GLfloat)width/(GLfloat)height, 1.0f, 400000000);
    glMatrixMode(GL_MODELVIEW);//指定当前操作模型视图矩阵堆栈
    glLoadIdentity();//重置模型视图矩阵
    gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);//前三个参数表示了观察点的位置，中间三个参数表示了观察目标的位置，最后三个参数代表从(0,0,0)到 (x,y,z)的直线，它表示了观察者认为的“上”方向
}
void drawString()
{
    selectFont(20, GB2312_CHARSET, "楷体_GB2312");//设置字体
    glColor3f(1.0f, 0.0f, 0.0f);//设置颜色
    glRasterPos2f(-10, -10);//设置位置
    drawCNString("Author:廖浩杰");//设置字符串内容
    glRasterPos2f(-9, -12);
    if(!bool_check_fps)//初始化时显示提示
    {
        drawCNString("Press \'F\' to show FPS");
    }
    else
    {
        drawCNString("FPS: ");
        //printf( "source: %e  buffer: '%s'\n", check_fps, buffer );
        glRasterPos2f(-12, -12);
        drawCNString(buffer);//显示
    }
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓冲区

    reshape(WIDTH,HEIGHT);

    drawString();//显示文字

    // 定义太阳光源，它是一种白色的光源
    GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);//
    glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);//表示各种光线照射到该材质上，经过很多次反射后最终遗留在环境中的光线强度（颜色）强度
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);//表示光线照射到该材质上，经过漫反射后形成的光线强度（颜色）
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//表示光线照射到该材质上，经过镜面反射后形成的光线强度（颜色）

    // 定义太阳的材质并绘制太阳

    GLfloat sun_mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_diffuse[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_shininess = 0.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT,   sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  sun_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  sun_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);//镜面指数，取值范围是0到128。该值越小，表示材质越粗糙

    glutSolidSphere(2.5f, nt, nt);//第一个参数表示球体的半径，后两个参数代表了“面”的数目

    // 定义地球的材质并绘制地球

    GLfloat earth_mat_ambient[] = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat earth_mat_diffuse[] = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat earth_mat_shininess = 30.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT,   earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  earth_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  earth_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);

    glRotatef(sunangle, 0.0f, 1.0f, 0.0f); //绕y轴逆时针旋转
    glTranslatef(8.0f, 0.0f, 0.0f);//将图形沿x轴向移动
    glRotatef(23.0f, 0.0f, 0.0f, 1.0f); //地球
    glutSolidSphere(1.0f, nt, nt);//画地球
    glRotatef(-23.0f, 0.0f, 0.0f, 1.0f); //地球
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f); //地球

    // 定义月亮的材质并绘制月亮

    GLfloat moon_mat_ambient[]   = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat moon_mat_diffuse[]   = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat moon_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat moon_mat_emission[] = {0.25,0.25,0.25,1.0};
    GLfloat moon_mat_shininess   = 30.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT,    moon_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    moon_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   moon_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   moon_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, moon_mat_shininess);

    glRotatef(earthangle, 0.0f, 1.0f, 0.0f); //绕y轴逆时针旋转
    glTranslatef(1.5f, 0.0f, 0.0f);//将图形沿x轴向移动
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f); //月亮
    glutSolidSphere(0.2f, nt, nt);

    if( finish_without_update )
        glFinish();
    else
        glutSwapBuffers();//交换双缓存
}

void Idle(void)//空闲时调用的函数
{
    //sleep(8);
    sunangle += 0.1f;//太阳加一个角度
    earthangle += 0.9f;//月亮加一个角度
    if( sunangle >= 360.0f )
        sunangle = 0.0f;
    if( earthangle >= 360.0f )
        earthangle = 0.0f;
    myDisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)//Esc 键退出程序
    {
    case 27:
        exit(0);
        break;
    case 'F':
    case 'f':
        finish_without_update = 1;
        check_fps = g_fps( myDisplay, 100);//计算帧数
        finish_without_update = 0;
        printf("%f fps\n", check_fps);
        _gcvt( check_fps, 8, buffer );//double 型转字符串型
        //printf("%s",buffer);
        bool_check_fps = 1;//标记已经计算过fps
        break;
    case '1':
        mod_speed(50);//调节动画速度
        break;
    case '2':
        mod_speed(200);
        break;
    case '3':
        mod_speed(600);
        break;
    default:
        break;
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//使用双缓存模式
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Sun Earth Mon Model");
    init();
    glutDisplayFunc(myDisplay);
    //glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Idle);
    glutMainLoop();
    return 0;
}
