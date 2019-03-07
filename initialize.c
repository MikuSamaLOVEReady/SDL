//
//  initialize.c
//  LittleBee
//
//  Created by 罗瑞笛 on 2019/2/26.
//  Copyright © 2019年 罗瑞笛. All rights reserved.
//

#include "initialize.h"
#include  <stdio.h>
#include  <SDL2/SDL.h>
#include  <SDL2_image/SDL_image.h>

 // #include  <SDL2_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 704 // 11X 64
#define WINDOW_HEIGHT 704// 11X 64

int counter = 1;


//game window
SDL_Window* window =NULL;



// 图像们
SDL_Surface* background = NULL ;
SDL_Surface* Bee = NULL;
SDL_Surface* bullet = NULL ;


//文字(暂时没法解决。)
//TTF_Font *Font = NULL ;
//SDL_Texture* forFont = NULL;


SDL_Texture* forbackground = NULL;
SDL_Texture* forBee = NULL;
SDL_Texture* forbullet = NULL;

//小蜜蜂
SDL_Rect Beesize ;
SDL_Rect Beepos ;
//子弹
SDL_Rect bulletsize ;
SDL_Rect bulletpos;
//记分版
SDL_Rect sco;


SDL_Renderer* render = NULL ;




void init ( void )
{   //初始化。。。
    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    //
    else
    {
    //初始化 窗口
     window = SDL_CreateWindow("little Bee",
                       SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH,
                       WINDOW_HEIGHT,
                       SDL_WINDOW_SHOWN
                       );
        
        //字体加载
        //暂时无法解决
        //Font = TTF_OpenFont("lazy.ttf", 10);
       //SDL_Color textcolor = { 0 , 0 , 0 };
        
        
        // 初始化一下 图形中蜜蜂的位置
        Beesize.x = 64;
        Beesize.y = 0;
        Beesize.w = 64;
        Beesize.h = 64;
        
        //初始化 出现的位置
        Beepos.x = 320 ;
        Beepos.y = 640 ;
        Beepos.w = 64 ;
        Beepos.h = 64 ;
        
        //子弹大小
        bulletsize.x = 0;
        bulletsize.y = 0;
        bulletsize.w = 64;
        bulletsize.h = 64;
        
        //记分版在右上角 需要文字 score 
        sco.x = 576; //  下一个640
        sco.y = 0;
        sco.w = 128;
        sco.h = 64;
        
        

       
        
       //初始化 渲染器
        render = SDL_CreateRenderer( window , -1, SDL_RENDERER_ACCELERATED);
        
        //surface 加载
        background = IMG_Load("space.jpg");  // 必须从 surface上r提取到 texture ？
        Bee = IMG_Load("bee.png"); //
        bullet = IMG_Load("bullet.png");
        
        //colorkey
        // SDL_SetColorKey(<#SDL_Surface *surface#>, <#int flag#>, <#Uint32 key#>)
        SDL_SetColorKey( bullet , SDL_TRUE , SDL_MapRGB(bullet -> format , 6, 25, 107) );
        
        
        //纹理加载(背景 蜜蜂 子弹 ）
        forbackground = SDL_CreateTextureFromSurface( render , background);
        forBee = SDL_CreateTextureFromSurface( render , Bee );
        forbullet = SDL_CreateTextureFromSurface( render , bullet);
        
        
        
        
        //小蜜蜂初始化完成了。
        SDL_RenderCopy(render, forbackground, NULL , NULL );
        SDL_RenderCopy(render, forBee, &Beesize , &Beepos);
        SDL_RenderPresent( render );
        
    }
    
}

void animation ( void )
{
    if( counter == 1  )
    {
       Beesize.x = 64;
       Beesize.y = 0;
       Beesize.w = 64;
       Beesize.h = 64;
    }
    if( counter == 2 )
    {
        Beesize.x = 128;
        Beesize.y = 0;
        Beesize.w = 64;
        Beesize.h = 64;
    }
    if( counter == 3 )
    {
        Beesize.x = 0;
        Beesize.y = 0;
        Beesize.w = 64;
        Beesize.h = 64;
    }
    counter++;
    if( counter == 4 )
    {
        counter  = 0;
    }
    
    
}


void  rendpart ( void )//这个函数 实现 动画效果 同时 应该在 更新完新位置之后调用
{
    
    SDL_RenderClear(render);
    SDL_RenderCopy(render, forbackground, NULL , NULL );
    SDL_RenderCopy(render, forBee, &Beesize , &Beepos); //这个函数 要实现Bee 的动画效果 同时
    
}


// 创建一个函数 读取 当前 小蜜蜂的位置
// 但是子弹位置 是

//
