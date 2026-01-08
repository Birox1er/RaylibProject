//#include<Raylib.h>
#include <stddef.h>
#include <stdio.h>
#include "bar.h"
#include "shot.h"
#include "score.h"
#include "enemy.h"
//depuis que j'ai essayé d'ajouter le score le jeu crash se ferme automatiquement au endDraw() si j'utilise un draw quelconque;
const int screenWidth = 960;
const int screenHeight = 540;
const int maxEnemy = 30;
const int enemyPerLine = 10;
const int maxShot=3;
struct Shot shots[3]={0};
struct Enemy enemies[30]={0};
int scores[10]={0};
const int shotCooldDown=30;
int frameSinceLastShot;
const int ScoreUpCooldDown=45;
int frameSinceScoreUp;
int gameState=0;
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
    InitWindow(screenWidth,screenHeight,"Shoot in the dark");//litéralement vu qu'on voit rien
    InitAudioDevice();
    Music music = LoadMusicStream("ressources/Menu.wav");
    Sound impact = LoadSound("ressources/Shotgun.wav");
    Sound shoot = LoadSound("ressources/Tir.mp3");
    music.looping = true;   
    PlayMusicStream(music);
    SetMusicVolume( music,.1);
    SetSoundVolume(impact,.1);
    SetSoundVolume(shoot,.1);
    Rectangle playerRect= GetBarRectangle();
    struct Bar newBar;
    newBar.posX=480;
    Texture2D playerTex=LoadTexture("newAssetPack/Destroyed.png");
    SetTextureWrap(playerTex,2); 
    //SaveNewScore(777);//test score;
    SetTargetFPS(60); 
    int deadEnemies=0;
    int  currentScore;
    while(!WindowShouldClose())
    {
    UpdateMusicStream(music);     
    BeginDrawing();
    ClearBackground(BLACK);
        if(gameState==0)//main menu
        {
            if(IsKeyDown(KEY_ENTER))
            {
                gameState=1;
            }
            DrawText(TextFormat("Use q ( a on qwerty) and d \n or left and right arrow to move"),100,100, 30, WHITE);
            DrawText(TextFormat("Press Space to shoot"),100,200, 30, WHITE);
            DrawText(TextFormat("Try to kill all enemies \n as fast as possible."),100,250, 30, WHITE);
            DrawText(TextFormat("Press enter to play"),560,270, 30, WHITE);
        }
        else if(gameState==1)//Game
        {
            if(firstFrame==0)
            {
                frameSinceLastShot=shotCooldDown;
                frameSinceScoreUp=0; 
                currentScore=0;
                for(int i=0;i<maxShot;++i)
                {
                    shots[i]=CreateShot(i);
                }
                for(int i=0;i<maxEnemy;i++)
                {
                    if(i%5==3)
                    {    
                        enemies[i]=CreateEnemy(2,i,120+((screenWidth-120)/enemyPerLine)*(i%enemyPerLine),120+120*(i/enemyPerLine));
                    }
                    else
                    {
                        enemies[i]=CreateEnemy(1,i,120+((screenWidth-120)/enemyPerLine)*(i%enemyPerLine),120+120*(i/enemyPerLine));
                    }
                }
                firstFrame++;
            }
            deadEnemies=0;
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
                    PlaySound(shoot);
                    int currentShotSlot=GetFirstEmptyShot();;
                    Shoot(&shots[currentShotSlot],newBar.posX+32);       
                    frameSinceLastShot=0;
                }
            }
            else
            {
                frameSinceLastShot++;
            }

            for(int i=0;i<maxShot;i++)
            {
                if(shots[i].isActive==1)
                {
                    
                    ShotMove(&shots[i]);
                    DrawShot(&shots[i]);
                    for(int j=0;j<maxEnemy;j++)
                    {
                      bool collision=CheckCollisionRecs(shots[i].hitbox,enemies[j].hitbox);
                      if(collision==1&&enemies[j].isActive)
                      {
                        PlaySound(impact); 
                        ShotHit(&shots[i]);
                        LoseHP(&enemies[j]);
                        break;          
                      }
                    }                 
                }
            }
            for(int i=0;i<maxEnemy;i++)
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
            }
            if(deadEnemies>=sizeof(enemies)/sizeof(enemies[0]))
            {
                SaveNewScore(currentScore);
                gameState=2;
                firstFrame=0;
                
            }
            if(frameSinceScoreUp>=ScoreUpCooldDown)
            {
              currentScore+=5;
              frameSinceScoreUp=0;
            }
            else
            {
                frameSinceScoreUp++;
            }
            DrawText(TextFormat("score : %i",currentScore), 50,50, 15, WHITE);
            DrawBar(&newBar,playerRect,playerTex);
       }
       else if(gameState==2)//scoreBoard
       {
           if(firstFrame==0)
           {
             for(int i =0;i<10;i++)
             {
                scores[i]=LoadStorageScore(i);
             }
             firstFrame++;
           }
           if(IsKeyDown(KEY_ENTER))
            {
                gameState=1;
                firstFrame=0;
            }
            DrawText(TextFormat("0 : %i", scores[0]), 280, 130, 40, GREEN);
            for(int i =1;i<10;i++)
            {
                DrawText(TextFormat("%d: %i",i, scores[i]), 280,130+35*i, 30, WHITE);
            }
            DrawText(TextFormat("Press enter to play again"),560,270, 30, WHITE);
       }
       EndDrawing(); 
    }
    UnloadSound(shoot);
    UnloadSound(impact);
    UnloadMusicStream(music);
    CloseAudioDevice();  
    CloseWindow();
    return 0;
}