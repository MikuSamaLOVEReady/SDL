//
//  judgeLogic.c
//  LittleBee
//
//  Created by 罗瑞笛 on 2019/2/26.
//  Copyright © 2019年 罗瑞笛. All rights reserved.
//

#include "judgeLogic.h"
#include <stdlib.h>//随机数
#include  <stdio.h>
#include  <SDL2/SDL.h>
#include <time.h>//用时间作为seed来产生随机数
#include  <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
int direction = 'X';
int count = -1 ;
//bool socre = false;

int fenshu = 0;
int start = 0;
int onlypos;




//文字

//子弹运用
extern SDL_Rect bulletpos;
extern SDL_Rect bulletsize ;
extern SDL_Rect pos_bulletEnemy;


extern SDL_Renderer* render;

extern SDL_Texture* forbullet;
extern SDL_Texture* forenemybullet;
extern SDL_Rect sco ;



SDL_Rect arr [99] ; //子弹所存储的数组。



void score (void )
{
    SDL_RenderSetViewport( render , &sco );//
}

 


void input (void )
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    if (state[SDL_SCANCODE_LEFT]) {
        direction = 1 ;
    }
    else if (state[SDL_SCANCODE_RIGHT]) {
        direction = 2 ;
    }
    else if (state[SDL_SCANCODE_SPACE]) {
        direction = 5 ;//为 子弹位置做准备
    }
    else if (state[SDL_SCANCODE_0]) {
        exit(0);
    }
    return;
   // SDL_UpdateTexture(  <#SDL_Texture *texture#>, <#const SDL_Rect *rect#>, <#const void *pixels#>, <#int pitch#>)
}

bool update( void )
{
    switch ( direction )
    {
        case 1://左
            if( Beepos.x > 0 )
            {
            Beepos.x =  Beepos.x - 64 ;
            Beepos.y = 640 ;
            Beepos.w = 64 ;
            Beepos.h = 64 ;
            direction = 'X';
            break;
            }
            else
            { break ;}
            
        case 2://右
            if( Beepos.x < 640 )
            {
            Beepos.x =  Beepos.x + 64 ;
            Beepos.y = 640 ;
            Beepos.w = 64 ;
            Beepos.h = 64 ;
            direction = 'X';
            break;
            }
            else
            { break ;}
        case 5:
            /*
            count ++;// 位置
            arr [count] = bulletpos.x ;
             */
            count ++;
            arr[count].x = Beepos.x ;//假如每次记录一个位置放到数组里。测试数组能否储存结构体内的数值 ；
            arr[count].y = 640;// 640-64
            arr[count].w = 64;
            arr[count].h = 64;
            direction   = 'X';
            break;
            
            
             //SDL_CreateTexture(<#SDL_Renderer *renderer#>, <#Uint32 format#>, <#int access#>, <#int w#>, <#int h#>)
            //       SDL_CreateTexture(<#SDL_Renderer *renderer#>, <#Uint32 format#>, <#int access#>, <#int w#>, int h
            
    }
    
    if( fenshu == 7  )
    {
        end = true;
        return  true ;
    }
    
    return  collision2( pos_bulletEnemy , Beepos );
    
    
   
   //碰撞测试放这。 。。
    
    
}
bool collision ( SDL_Rect arrbulet[] , int *arrD )//每次把所有子弹的位置都与敌人匹配一遍。 如果 
{
    for(int m =0 ; m <=99 ; m++)//取出每个子弹
    {
        for(int n=0 ; n <= 7 ; n++)//取出每条龙
        {
            if( arrD[n] == arrbulet[m].x && 192 == arrbulet[m].y)
            {
                arrD[n] = -10000000;//这个位置需要改变
                fenshu++;
                return true ;
            }
        }
    }
    return false;
}

bool collision2( SDL_Rect arrEnemyBullet, SDL_Rect nowbee )   //  子弹的x, y. 除此之外还有 蜜蜂当前位置/
{
    
    if ( arrEnemyBullet.x == nowbee.x && arrEnemyBullet.y == nowbee.y)
    {
        end = true;
        return true ;
    }
    else
    {
        return false;
    }
    
    
}





void flayway(int number ) // 这个因该传入一个参数   每次渲染的子弹都是单独的
{
     arr[number].y = arr[number].y -64 ;// 每次都要减少
}


void rend_bullet ( void )//这个函数来循环 渲染子弹位置
{
    
    for(int i = 0; i < 99 ; i++) // 数组大小
    {
         flayway( i );
         SDL_RenderCopy(render,forbullet, NULL , &arr[i]);
    }
    
    collision( arr , pos );
}



void flyway2( int position )//传参 ( pos[i] )  传入龙的位置
{
    
     pos_bulletEnemy.x  = position ;
     pos_bulletEnemy.y  = pos_bulletEnemy.y + 64 ;
}


void rend_enemybullet ()  // 传  每过一段时间 随机函数给出一个龙的 位置arr[i] 把他的 x 记录下来 而敌人子弹的个体y只有一个
{
    int i= randomnumber ();
    
    if ( nextbullet() || start ==0 )//start 目的是先给出一个子弹 不然初始位置为负数 nextbullet 无法启动
    {
       pos_bulletEnemy.y =192;//给定初始位置 距离top256像素点
       flyway2( pos[i] );  //选取一个龙的位置 （x坐标
       onlypos = pos [i];  //把这个位置复制给 ponly 好让后面一直是这个点做改变 不然是乱点 测试点
       start = 1 ; // 开始的调整
      
    }
    else
    {
        flyway2( onlypos );
    }
    SDL_RenderCopy(render,forenemybullet, NULL , &pos_bulletEnemy );// 倒数第二参数要规划下 最后一个参数也要改变为 flayway2 的参数
    
    // 子弹碰撞测试放这？
    
}

bool nextbullet ( void )
{
    if ( pos_bulletEnemy.y >= 704)
    {
        return true ;
    }
    else
    {
        return false ;
    }
    
}


int randomnumber ()
{
    srand( (unsigned)time(NULL ) );
    int p= rand()%6 ;
    return p;  // 随机产生一个位置
}




// 碰撞测试 在渲染子弹的位置判断。
