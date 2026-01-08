#include<Raylib.h>
#include <stddef.h>
#include <stdio.h>
#include "bar.h"
#include "shot.h"
#include "score.h"
#include "enemy.h"

const int screenWidth = 960;
const int screenHeight = 540;
struct Shot shots[3]={0};
struct Enemy enemies[5]={0};
int score[10]={0};
int shotCooldDown=30;
int frameSinceLastShot=30;
int gameState=1;
int firstFrame=0;
int GetFirstEmptyShot()
{
    for(int i=0;i<10;++i)
    {
        if(shots[i].isActive==0)
        {
            return i;
        }
    }
    return 0;
 }
    
int main()
{
    InitWindow(screenWidth,screenHeight,"game");
    Rectangle playerRect= GetBarRectangle();
    struct Bar newBar;
    newBar.posX=480;
    Texture2D playerTex=LoadTexture("newAssetPack/Destroyed.png");
    SetTextureWrap(playerTex,2); 
    //SaveNewScore(777);
    SetTargetFPS(60); 
    int deadEnemies=0;
    for(int i=0;i<10;++i)
    {
        shots[i]=CreateShot(i);
        printf("%d is active %d at %f %f \n",i,shots[i].ID,shots[i].posX,shots[i].posY);
    }
    for(int i=0;i<15;i++)
    {
        if(i%5==2)
        {    
            enemies[i]  =CreateEnemy(2,i,120+144*(i%5),120+120*(i/5));
        }
        else
        {
            enemies[i]=CreateEnemy(1,i,120+144*(i%5),120+120*(i/5));
        }
    }
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        if(gameState==0)//main menu
        {
        }
        else if(gameState==1)//Game
        {
            
            if(IsKeyDown(KEY_D)|| IsKeyDown(KEY_RIGHT))
            {
                BarMove(1,&newBar);
            }
            if(IsKeyDown(KEY_A)|| IsKeyDown(KEY_LEFT))
            {
                BarMove(-1,&newBar);   
            }
            if(frameSinceLastShot>=shotCooldDown){
                
                if(IsKeyDown(KEY_SPACE))
                {
                    int currentShotSlot=GetFirstEmptyShot();;
                    Shoot(&shots[currentShotSlot],newBar.posX);       
                    frameSinceLastShot=0;
                }
            }
            else
            {
                frameSinceLastShot++;
            }
            for(int i=0;i<10;i++)
            {
                if(shots[i].isActive==1)
                {
                    ShotMove(&shots[i]);
                    DrawShot(&shots[i]);
                    for(int j=0;j<5;j++)
                    {
                        bool collision= CheckCollisionRecs(shots[i].hitbox,enemies[j].hitbox);
                         printf("%d\n" ,enemies[j].isActive);
                      if(collision==1&&enemies[j].isActive)
                      {

                        ShotHit(&shots[i]);
                        LoseHP(&enemies[j]);
                        break;
                                                    
                      }
                    }                 
                }
            }
            for(int i=0;i<5;i++)
            {
                if(enemies[i].HP>0)
                {
                    EnemyMove(&enemies[i]);
                    EnemyDraw(&enemies[i]);
                }
                else 
                {
                    deadEnemies++;
                }
                if(deadEnemies==sizeof(enemies)/sizeof(enemies[0]))
                {
                    gameState=2;
                    firstFrame=0;
                }
            }
            DrawBar(&newBar,playerRect,playerTex);
            
                 
       }
        else if(gameState==2)//scoreBoard
        {

        }
        EndDrawing(); 

    }
    CloseWindow();
    return 0;
}