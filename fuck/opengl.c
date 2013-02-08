// ̫�����������������ģ��
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
float check_fps;//֡��
char buffer[50];
int nt;//���ƶ����ٶ�

static GLfloat sunangle = 0.0f; //��ת�Ƕ�
static GLfloat earthangle = 0.0f;

float g_fps( void (*func)(void), int n_frame )//��ȡ��ǰ֡��
{
    clock_t start, finish;//��ʼ����ֹʱ��
    int i;
    float fps;//֡��

    printf( "Performing benchmark, please wait:" );//��ʾ��ʾ
    start = clock();//��ȡ��ʼʱ��
    for( i=0; i<n_frame; i++ )
    {
        func();
    }
    printf( "done\n" );//�������
    finish = clock();//��ȡ����ʱ��

    fps = (float)(n_frame)/(finish-start)*CLOCKS_PER_SEC;//����֡��
    return fps;//����֡��
}

void selectFont(int size, int charset, const char* face)//������ʾ������
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

void drawCNString(char* str)//�ڻ�����д�֣��������ĺ�Ӣ��
{
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    /*
    �����ַ��ĸ���
    �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
    ����һ���ֽ���һ���ַ�
    */
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    // ������ַ�ת��Ϊ���ַ�
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // �������ַ�
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // ����������ʱ��Դ
    free(wstring);
    glDeleteLists(list, 1);
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_SMOOTH);//������ɫ��䷽ʽ��ƽ����ʽ
    glEnable(GL_LIGHT0);//������0�Ź�Դ
    glEnable(GL_LIGHTING);//�򿪹��մ�����
    glEnable(GL_DEPTH_TEST);//������Ȳ��ԣ������ر��ڵ���
    nt=200; //����֡��
}

void reshape(int width, int height)// ����͸��Ч����ͼ
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);//�ӽǡ��߿�ȡ�������Ӿ��롢��Զ���Ӿ���
//    gluPerspective(75.0f, (GLfloat)width/(GLfloat)height, 1.0f, 400000000);
    glMatrixMode(GL_MODELVIEW);//ָ����ǰ����ģ����ͼ�����ջ
    glLoadIdentity();//����ģ����ͼ����
    gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);//ǰ����������ʾ�˹۲���λ�ã��м�����������ʾ�˹۲�Ŀ���λ�ã�����������������(0,0,0)�� (x,y,z)��ֱ�ߣ�����ʾ�˹۲�����Ϊ�ġ��ϡ�����
}
void drawString()
{
    selectFont(20, GB2312_CHARSET, "����_GB2312");//��������
    glColor3f(1.0f, 0.0f, 0.0f);//������ɫ
    glRasterPos2f(-10, -10);//����λ��
    drawCNString("Author:�κƽ�");//�����ַ�������
    glRasterPos2f(-9, -12);
    if(!bool_check_fps)//��ʼ��ʱ��ʾ��ʾ
    {
        drawCNString("Press \'F\' to show FPS");
    }
    else
    {
        drawCNString("FPS: ");
        //printf( "source: %e  buffer: '%s'\n", check_fps, buffer );
        glRasterPos2f(-12, -12);
        drawCNString(buffer);//��ʾ
    }
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����Ȼ�����

    reshape(WIDTH,HEIGHT);

    drawString();//��ʾ����

    // ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
    GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);//
    glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);//��ʾ���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��ǿ��
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);//��ʾ�������䵽�ò����ϣ�������������γɵĹ���ǿ�ȣ���ɫ��
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//��ʾ�������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���ɫ��

    // ����̫���Ĳ��ʲ�����̫��

    GLfloat sun_mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_diffuse[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_mat_shininess = 0.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT,   sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  sun_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  sun_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);//����ָ����ȡֵ��Χ��0��128����ֵԽС����ʾ����Խ�ֲ�

    glutSolidSphere(2.5f, nt, nt);//��һ��������ʾ����İ뾶�����������������ˡ��桱����Ŀ

    // �������Ĳ��ʲ����Ƶ���

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

    glRotatef(sunangle, 0.0f, 1.0f, 0.0f); //��y����ʱ����ת
    glTranslatef(8.0f, 0.0f, 0.0f);//��ͼ����x�����ƶ�
    glRotatef(23.0f, 0.0f, 0.0f, 1.0f); //����
    glutSolidSphere(1.0f, nt, nt);//������
    glRotatef(-23.0f, 0.0f, 0.0f, 1.0f); //����
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f); //����

    // ���������Ĳ��ʲ���������

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

    glRotatef(earthangle, 0.0f, 1.0f, 0.0f); //��y����ʱ����ת
    glTranslatef(1.5f, 0.0f, 0.0f);//��ͼ����x�����ƶ�
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f); //����
    glutSolidSphere(0.2f, nt, nt);

    if( finish_without_update )
        glFinish();
    else
        glutSwapBuffers();//����˫����
}

void Idle(void)//����ʱ���õĺ���
{
    //sleep(8);
    sunangle += 0.1f;//̫����һ���Ƕ�
    earthangle += 0.9f;//������һ���Ƕ�
    if( sunangle >= 360.0f )
        sunangle = 0.0f;
    if( earthangle >= 360.0f )
        earthangle = 0.0f;
    myDisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)//Esc ���˳�����
    {
    case 27:
        exit(0);
        break;
    case 'F':
    case 'f':
        finish_without_update = 1;
        check_fps = g_fps( myDisplay, 100);//����֡��
        finish_without_update = 0;
        printf("%f fps\n", check_fps);
        _gcvt( check_fps, 8, buffer );//double ��ת�ַ�����
        //printf("%s",buffer);
        bool_check_fps = 1;//����Ѿ������fps
        break;
    case '1':
        mod_speed(50);//���ڶ����ٶ�
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
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//ʹ��˫����ģʽ
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
