ifndef PROJECTILE_H /* L'écriture ici présente n'est pas universelle */
#define PROJECTILE_H
#include <Raylib.h>

struct Shot{
float posX; 
float posY;
bool isActive; 
};
 void DrawShot(struct Shot *shot,Texture2D texture)
{
     Vector2 vector;
     vector.x=shot->posX;
     vector.y=shot->posY;
    DrawTextureRec(texture,rect,vector,WHITE); 
};
 void BallMove(vector2 dir,struct Shot *shot)
{
    shot->posY+=dir.y*6; 
};
void ShotHit(Vector2 dir,Shot* shot)
{
    shots->remove()
}
Shot Shoot(float posX){
    struct Shot shot;
    shot.posX=posX;
    shot.posY=75;
    shot.isActive=true;
    return shot;
}

#endif