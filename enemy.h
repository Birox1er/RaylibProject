#ifndef ENEMY_H /* L'écriture ici présente n'est pas universelle */
#define ENEMY_H
#include <Raylib.h>
#include <stdio.h>

struct Enemy{
    int HP;
    int ID;
    int dir;
    int isActive;
    float speed;
    float posX;
    float posY;
    struct Rectangle rect;
    struct Rectangle hitbox;
    Texture2D tex;
};
struct Rectangle GetEnemyRectangle(){
    struct Rectangle rect;
        rect.x=0;
        rect.y=0;
        rect.width=32;
        rect.height=32;
    return rect;
};
struct Enemy CreateEnemy(int hp,int ID,float posX,float posY){
    struct Enemy newEnemy;
    newEnemy.HP=hp;
    newEnemy.ID=ID;
    newEnemy.isActive=1;
    newEnemy.dir=-1;
    newEnemy.speed=3;
    newEnemy.posX=posX;
    newEnemy.posY=posY;
    newEnemy.hitbox=(Rectangle){0,0,32,32};
    newEnemy.rect=GetEnemyRectangle();
    switch(hp)
    {
     case 1:
        newEnemy.tex=LoadTexture("newAssetPack/popsicle_c6.png");
        break;
     case 2:
        newEnemy.tex=LoadTexture("newAssetPack/popsicle_c12.png");
        break;
    }
    return newEnemy;
};
void EnemyMove(struct Enemy *currentEnemy)
{
    currentEnemy->posX+=currentEnemy->dir*currentEnemy->speed; 
    currentEnemy->hitbox.x=currentEnemy->posX;
    currentEnemy->hitbox.y=currentEnemy->posY;
    if(currentEnemy->posX<0||currentEnemy->posX>928){
        currentEnemy->dir=-currentEnemy->dir;
    }
};
void EnemyDraw(struct Enemy *enemy)
{
     Vector2 vector;
     vector.x=enemy->posX;
     vector.y=enemy->posY;
    DrawTextureRec(enemy->tex,enemy->rect,vector,WHITE); 
    DrawRectangleLines(enemy->hitbox.x,enemy->hitbox.y,enemy->hitbox.width,enemy->hitbox.height,BLUE);
};
void LoseHP(struct Enemy *enemy)
{
    enemy->HP--;
    if(enemy->HP<=0)
    {
        enemy->isActive=0;
        printf("IT DIED!!!");
    }
}
    
#endif