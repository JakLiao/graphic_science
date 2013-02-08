#include"stdlib.h"
#include"graphics.h"
#include"conio.h"
#include"stdio.h"
#include"math.h"
#include"time.h"

int sign(int val)
{
    if(val < 0) return -1;
    if(val == 0) return 0;
    else return 1;
}

void Bresenham(int x1,int y1,int x2,int y2,int value)
{
    int sign();
    int x,y,s1,s2,increx,increy,temp,interchange;
    int e,i;
    x=x1;
    y=y1;
    s1=sign(x2-x1);
    s2=sign(y2-y1);
    increx=abs(x2-x1);
    increy=abs(y2-y1);
    if(increy>increx)
    {
        temp=increx;
        increx=increy;
        increy=temp;
        interchange=1;
    }
    else interchange=0;
    e=2*increy-increx;
    for(i=1; i<=increx; i++)
    {
        putpixel(x,y,value);
        if(e>=0)
        {
            if(interchange==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-2*increx;
        }
        if(interchange==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+2*increx;
    }
}


int main()
{
    int gdriver=DETECT,gmode;
    initgraph(&gdriver,&gmode," ");
    cleardevice();

    time_t t;
    srand((unsigned) time(&t));//产生随机数种子

    int x1,y1,x2,y2,value;
     value=3;//画笔颜色
    x1=random(500);
    y1=random(500);
    x2=random(500);
    y2=random(500);
    printf("x1=%d y1=%d x2=%d y2=%d",x1,y1,x2,y2);
    Bresenham(x1,y1,x2,y2,value);
    getch();
    closegraph();
    return 0;
}
