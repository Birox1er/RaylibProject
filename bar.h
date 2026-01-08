#ifndef BAR_H /* L'écriture ici présente n'est pas universelle */
#define BAR_H
#include <Raylib.h>
struct Bar{
float posX; 
};
 void DrawBar(struct Bar *bar,struct Rectangle rect,Texture2D texture){
     Vector2 vector;
     vector.x=bar->posX;
     vector.y=500;
    DrawTextureRec(texture,rect,vector,WHITE); 
};
 void BarMove(int dir,struct Bar *bar){
    bar->posX+=dir*6; 
    if(bar->posX<0){
        bar->posX=0;
    }
    else if(bar->posX>760){
        bar->posX=760;
    }
};
struct Rectangle GetBarRectangle(){
    struct Rectangle rect;
        rect.x=0;
        rect.y=0;
        rect.width=64;
        rect.height=64;
    return rect;
};
#endif