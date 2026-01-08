#include <Raylib.h>
#include "bar.h"

void Bar BarMove(int dir,struct Bar &bar){
    bar.posX+=dir*100; 
    if(bar.posX<0){
        bar.posX=0;
    }
    else if(bar.posX>960){
        bar.posX=960;
    }
}
void DrawBar(struct Bar &bar,Texture2D texture){
    DrawTexture(texture,bar.posX,500,BLACK); 
}
    