#include"stdlib.h"
#include"graphics.h"
#include"conio.h"
#include"stdio.h"
#include"memory.h"

//50,100 80,230 100,270 140,160 180,50 240,65 270,120 330,230 380,230 430,150

double t[7]={0,0.15,0.35,0.5,0.65,0.85,1};
double B[10][10];
double P[10][2];

void DrawLine()
{

    int i;
    for(i=0;i<(sizeof(t)/sizeof(double)-1);i++)
    {

        line(P[i][0],P[i][1],P[i+1][0],P[i+1][1]);//连接求出的各点
    }
}

void Bezier(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y, int p3x, int p3y )
{

    int i;
    for(i=0;i<sizeof(t)/sizeof(double);i++)
    {
        P[i][0]=B[i][0]*p0x+B[i][1]*p1x+B[i][2]*p2x+B[i][3]*p3x;//横坐标
        P[i][1]=B[i][0]*p0y+B[i][1]*p1y+B[i][2]*p2y+B[i][3]*p3y;//纵坐标
    }
    DrawLine();//连线
}

int main()
{
    int gdriver=DETECT,gmode;
    initgraph(&gdriver,&gmode," ");
    cleardevice();
    int i;

    memset(B,0,sizeof(B));//初始化数组全为0
    memset(P,0,sizeof(P));
    for(i=0;i<sizeof(t)/sizeof(double);i++)
    {
        B[i][0]=(1-t[i])*(1-t[i])*(1-t[i]);
        B[i][1]=3*t[i]*(1-t[i])*(1-t[i]);
        B[i][2]=3*t[i]*t[i]*(1-t[i]);
        B[i][3]=t[i]*t[i]*t[i];
    }
    /*for(i=0;i<7;i++)
    {
        for(j=0;j<4;j++)
        {
            printf("%f ",B[i][j]);
        }
        printf("\n");
    }*/                                 //输出B矩阵
    Bezier(50,100, 80,230, 100,270 ,140,160);
    Bezier(140,160, 180,50, 240,65, 270,120);
    Bezier(270,120, 330,230, 380,230, 430,150);
    /*for(i=0;i<7;i++)
    {
        for(j=0;j<2;j++)
        {
            printf("%f ",P[i][j]);
        }
        printf("\n");
    }*/                                 //输出P矩阵
    getch();
    closegraph();
    return 0;
}
