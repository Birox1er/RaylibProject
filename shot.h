#ifndef SHOT_H /* L'écriture ici présente n'est pas universelle */
#define SHOT_H
#include <Raylib.h>

struct Shot{
    int ID;
    float posX; 
    float posY;
    int isActive; 
    struct Rectangle rect;
    struct Rectangle hitbox;
    Texture2D texture;
};
struct Rectangle GetShotRectangle(){
    struct Rectangle rect;
        rect.x=0;
        rect.y=0;
        rect.width=8;
        rect.height=9;
    return rect;
};
 void DrawShot(struct Shot *shot)
{
     Vector2 vector;
     vector.x=shot->posX;
     vector.y=shot->posY;
     
    DrawTextureRec(shot->texture,shot->rect,vector,WHITE); 
    DrawRectangleLines(shot->hitbox.x,shot->hitbox.y,shot->hitbox.width,shot->hitbox.height,BLUE);
};
 void ShotMove(struct Shot *shot)
{
    shot->posY= shot->posY-6;
    shot->hitbox.y=shot->posY;    
    if(shot->posY<0)
    {
        shot->isActive=0;
    }
};
struct Shot CreateShot(int ID){
    struct Shot newShot;
    newShot.posX=-100;
    newShot.posY=-100;
    newShot.isActive=0;
    newShot.ID=ID;
    newShot.rect=GetShotRectangle();
    newShot.hitbox=(Rectangle){0,0,8,9};
    newShot.texture= LoadTexture("newAssetPack/Lazer.png");
    return newShot;
};
void Shoot(struct Shot* shot,float posX){
    struct Shot newShot;
    shot->posX=posX;
    shot->posY=500;
    shot->hitbox.x=shot->posX;
    shot->hitbox.y=shot->posY;
    shot->isActive=1;

};
void ShotHit(struct Shot *shot)
{
        shot->isActive=0;
};
#endif