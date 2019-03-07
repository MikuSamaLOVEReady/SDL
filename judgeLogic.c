//
//  judgeLogic.c
//  LittleBee
//
//  Created by 罗瑞笛 on 2019/2/26.
//  Copyright © 2019年 罗瑞笛. All rights reserved.
//

#include "judgeLogic.h"
#include  <stdio.h>
#include  <SDL2/SDL.h>
#include  <SDL2_image/SDL_image.h>

int direction = 'X';
extern bool end;
extern SDL_Rect Beepos;

//子弹运用
extern SDL_Rect bulletpos;
extern SDL_Rect bulletsize ;

extern SDL_Renderer* render;

extern SDL_Texture* forbullet;
extern SDL_Rect sco ;




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
}

bool update( void )
{
    switch ( direction )
    {
        case 1://左
            Beepos.x =  Beepos.x - 64 ;
            Beepos.y = 640 ;
            Beepos.w = 64 ;
            Beepos.h = 64 ;
            direction = 'X';
            break;
            
        case 2://右
            Beepos.x =  Beepos.x + 64 ;
            Beepos.y = 640 ;
            Beepos.w = 64 ;
            Beepos.h = 64 ;
            direction = 'X';
            break;
        case 5:
            bulletpos.x = Beepos.x ;//假如每次记录一个位置放到数组里。
            bulletpos.y = 576;// 640-64
            bulletpos.w = 64;
            bulletpos.h = 64;
            direction = 'X';
            break;

    }
    
    return true;
    
    /*敌人的子弹的位置没和 Bee 重叠时 可以返回ture
    if()
     {
     
     
     }
    return true;
    else
    {
     
     end = true;
     return false;
     
     }
     
    */
}

void flayway()
{
     bulletpos.y = bulletpos.y -64 ;// 每次都要减少
}
void rend_bullet ( void )//这个函数来循环 渲染子弹位置
{
    
    flayway();
    SDL_RenderCopy(render,forbullet, NULL , &bulletpos);//
    score (); // 调整渲染区域
    //SDL_RenderCopy(render, 文字, NULL, NULL );//
    SDL_RenderSetViewport( render , NULL );//调回原来的 大小
    
    
}

