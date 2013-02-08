#include"stdlib.h"
#include"graphics.h"
#include"conio.h"
#include"stdio.h"

int main()
{
    void *w;
    int driver,gmode;
    int i,j,start=0,end=180;
    driver=VGA;
    gmode=VGAMED;
    initgraph(&driver,&gmode," ");
    cleardevice();
    setbkcolor(EGA-LIGHTBLUE);
    setcolor(4);

    circle(470,230,40);//×ó³µÂÖ
    circle(590,230,40);//ÓÒ³µÂÖ
    circle(530,230,10);//½ÅÌ¤
    line(440,120,500,120);
    line(470,120,470,230);
    line(470,170,590,230);//³µ¼Ü
    line(470,230,590,230);
    line(510,190,600,190);//×ø°ü

    w=malloc(imagesize(430,120,630,270));
    getimage(430,120,630,270,w);
    for(i=430,j=0; i>0; j--,i--)
    {
        setfillstyle(EMPTY_FILL,0);
        pieslice(470+j,230,start,end,40);
        pieslice(590+j,230,start,end,40);
        start+=45;
        end+=45;
        delay(5);
        putimage(i-1,120,w,COPY_PUT);
        line(2,270,630,270);
        delay(10);
    }
    for(i=0; i<10; i++)
    {
        pieslice(40,230,start,end,40);
        pieslice(160,230,start,end,40);
        start+=45;
        end+=45;
    }
    getch();
    restorecrtmode();
    closegraph();
    return 0;
}
