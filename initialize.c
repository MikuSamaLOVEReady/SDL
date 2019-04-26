//
//  initialize.c
//  LittleBee
//
//  Created by 罗瑞笛 on 2019/2/26.
//  Copyright © 2019年 罗瑞笛. All rights reserved.
//
#include "judgeLogic.h"
#include "initialize.h"
#include  <stdio.h>
#include  <stdbool.h>
#include  <SDL2/SDL.h>
#include  <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

 // #include  <SDL2_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 704 // 11X 64
#define WINDOW_HEIGHT 704// 11X 64

int counter = 1;
//extern bool socre;
extern int count ;
extern int fenshu;
int enemynumber = 1;
int pos[99];
bool direct = true ;
//总共七个分数
char *word0 ="Score:0";
char *word1 ="Score:1";
char *word2 ="Score:2";
char *word3 ="Score:3";
char *word4 ="Score:4";
char *word5 ="Score:5";
char *word6 ="Score:6";
char *word7 ="Score:7";

//第六个 【5】
//存不存在字符串数组？
//game window
SDL_Window* window =NULL;

// 颜色
SDL_Color textColor ;


// 图像们
SDL_Surface* background = NULL ;
SDL_Surface* Bee = NULL;
SDL_Surface* bullet = NULL ;
SDL_Surface* enemybullet = NULL ; //敌人子弹
SDL_Surface* dragon = NULL ;

//文字surface
SDL_Surface* TextSurface = NULL ;
SDL_Surface* TextSurface1 = NULL ;
SDL_Surface* TextSurface2 = NULL ;
SDL_Surface* TextSurface3 = NULL ;
SDL_Surface* TextSurface4 = NULL ;
SDL_Surface* TextSurface5 = NULL ;
SDL_Surface* TextSurface6 = NULL ;
SDL_Surface* TextSurface7 = NULL ;




//文字
TTF_Font *Font = NULL ;
SDL_Texture* forFont = NULL;


SDL_Texture* forbackground = NULL;
SDL_Texture* forBee = NULL;
SDL_Texture* forbullet = NULL;

SDL_Texture* fortext = NULL ;
SDL_Texture* fortext1 = NULL ;
SDL_Texture* fortext2 = NULL ;
SDL_Texture* fortext3 = NULL ;
SDL_Texture* fortext4 = NULL ;
SDL_Texture* fortext5 = NULL ;
SDL_Texture* fortext6 = NULL ;
SDL_Texture* fortext7 = NULL ;

SDL_Texture* fordragon = NULL ;
SDL_Texture* forenemybullet = NULL ;//敌人子弹


//小蜜蜂
SDL_Rect Beesize ;
SDL_Rect Beepos ;
//子弹
SDL_Rect bulletsize ;
SDL_Rect bulletpos;
//记分版
SDL_Rect sco;
//敌人位置
SDL_Rect enemysize ;
SDL_Rect enemy ;
//d
//SDL_Rect buseize;
SDL_Rect pos_bulletEnemy;//敌人子弹出现的位置



SDL_Renderer* render = NULL ;


void init ( void )
{   //初始化。。。
    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    TTF_Init() ;
    //
    {
    //初始化 窗口
     window = SDL_CreateWindow("little Bee",
                       SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH,
                       WINDOW_HEIGHT,
                       SDL_WINDOW_SHOWN
                       );
        //初始化敌人子弹位置。。
        
        pos_bulletEnemy.x = -64 ;
        pos_bulletEnemy.y = -64 ;
        pos_bulletEnemy.w = 64;
        pos_bulletEnemy.h = 64;
        
    
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
        
        //敌人位置
        enemy.x = 192;
        enemy.y = 192;
        enemy.w = 64;
        enemy.h = 64;
        pos [ 0 ] = 192 ;//选取第一个敌人的位置 横坐标
        
        for (enemynumber = 1 ;enemynumber < 7 ; enemynumber++) //number is 7
        {
            pos [ enemynumber ]  = pos [ (enemynumber-1) ] + 64  ;//初始化位置
      
        }
            
        
        //敌人大小
        enemysize.x =64 ;
        enemysize.y =0  ;
        enemysize.w =64 ;
        enemysize.h =64 ;
        
        /*
        buseize.x = 32;
        buseize.y = 32;
        buseize.w = 32;
        buseize.h = 32;
        */
       
        
       //初始化 渲染器
        render = SDL_CreateRenderer( window , -1, SDL_RENDERER_ACCELERATED);
        
        //surface 加载
        background = IMG_Load("space.jpg");  // 必须从 surface上r提取到 texture ？
        Bee = IMG_Load("bee.png"); //
        bullet = IMG_Load("bullet.png");
        dragon = IMG_Load("dragon.png");
        enemybullet = IMG_Load("Sprite1.png");
        
        
        //colorkey
        // SDL_SetColorKey(<#SDL_Surface *surface#>, <#int flag#>, <#Uint32 key#>)
        SDL_SetColorKey( bullet , SDL_TRUE , SDL_MapRGB(bullet -> format , 6, 25, 107) );
        
        
        //纹理加载(背景 蜜蜂 子弹 龙 敌人子弹 ）
        forbackground = SDL_CreateTextureFromSurface( render , background);
        forBee = SDL_CreateTextureFromSurface( render , Bee );
        forbullet = SDL_CreateTextureFromSurface( render , bullet);
        fordragon = SDL_CreateTextureFromSurface( render , dragon);
        forenemybullet = SDL_CreateTextureFromSurface(render , enemybullet);
        
        
        //字体加载
        Font = TTF_OpenFont("lazy.ttf", 18);
        SDL_Color textColor = {255 , 255 , 255};
        
          TextSurface = TTF_RenderText_Solid( Font , word0, textColor);//
          TextSurface1 = TTF_RenderText_Solid( Font , word1, textColor);
          TextSurface2 = TTF_RenderText_Solid( Font , word2, textColor);
          TextSurface3 = TTF_RenderText_Solid( Font , word3, textColor);
          TextSurface4 = TTF_RenderText_Solid( Font , word4, textColor);
          TextSurface5 = TTF_RenderText_Solid( Font , word5, textColor);
          TextSurface6 = TTF_RenderText_Solid( Font , word6, textColor);
          TextSurface7 = TTF_RenderText_Solid( Font , word7, textColor);
        
        
         fortext = SDL_CreateTextureFromSurface (render,TextSurface);//  为什么每个字符被赋值过后就不能再动了？
         fortext1 = SDL_CreateTextureFromSurface (render,TextSurface1);
         fortext2 = SDL_CreateTextureFromSurface (render,TextSurface2);
         fortext3 = SDL_CreateTextureFromSurface (render,TextSurface3);
         fortext4 = SDL_CreateTextureFromSurface (render,TextSurface4);
         fortext5 = SDL_CreateTextureFromSurface (render,TextSurface5);
         fortext6 = SDL_CreateTextureFromSurface (render,TextSurface6);
         fortext7 = SDL_CreateTextureFromSurface (render,TextSurface7);
       
        
        
       //  TTF_RenderText_Solid(<#TTF_Font *font#>, <#const char *text#>, <#SDL_Color fg#>) ;//这是个const MMP
        
        //小蜜蜂初始化完成了。
        
       // SDL_RenderCopy(render, forbackground, NULL , NULL );
       // SDL_RenderCopy(render, forBee, &Beesize , &Beepos);
       // SDL_RenderPresent( render );
        
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
    //所有敌人渲染
    motion();// 调整第一个位置
   //new_pos( ); // 把每个新位置赋值
                  // 碰撞测试
    for( int i=0 ;i < enemynumber; i++ )
    {
       enemy.x = pos[i];
       SDL_RenderCopy(render , fordragon, &enemysize, &enemy);
    }
   // changescore( word );
   
    SDL_RenderSetViewport( render , &sco ) ; //限制位置右上角
    if ( fenshu == 0 )
    {
        SDL_RenderCopy(render, fortext , NULL , NULL );//渲染文字
    }
    if ( fenshu == 1 )
    {
    SDL_RenderCopy(render, fortext1 , NULL , NULL );
    }
    if ( fenshu == 2 )
    {
        SDL_RenderCopy(render, fortext2 , NULL , NULL );
    }
    if ( fenshu == 3 )
    {
        SDL_RenderCopy(render, fortext3 , NULL , NULL );
    }
    if ( fenshu == 4 )
    {
        SDL_RenderCopy(render, fortext4 , NULL , NULL );
    }
    if ( fenshu == 5 )
    {
        SDL_RenderCopy(render, fortext5 , NULL , NULL );
    }
    if ( fenshu == 6 )
    {
        SDL_RenderCopy(render, fortext6 , NULL , NULL );
    }
    
    
    SDL_RenderSetViewport( render , NULL ) ;
      //子弹数量 也是靠 函数实现
    //SDL_RenderCopy(render , fordragon, &enemysize, &enemy);//敌人渲染

    
}


void motion ( void )// 要不手动修改？
{
    if( direct )//direct true 表示所有敌人向右移动一个单位
  {
    for ( int i = 0 ; i < 7  ; i++)
         {
          pos[i] = pos[i] + 64;//向右边移动
         }
      if ( pos[ (enemynumber-1) ] == 640 )// 判断最右边的敌人有没有碰到
         {
            direct = false;
          }
      
      
      
    if ( pos[ (enemynumber-1) ] < 0 && pos[0] >= 0 )
      {
          direct= true ;
         if (pos[0]==640-fenshu*64)
         {
             direct=false ;
         }
      }
      
      else if (pos[ (enemynumber-1) ] < 0 )//如果最右边的敌人被击杀了，则立即换方向移动  // (pos[ (enemynumber-i) ] i 作为被击杀后加一 有没有办法让他s一直指着最后一个
      {
          
          direct = false;
      }
     
    
  }

   else
  {
    for ( int i = 0 ; i < 7 ; i ++)
       {
        pos[i] = pos[i] - 64;//向左移动
       }
    if ( pos[0] == 0 )// 当第一个敌人碰到最左边的时候换方向。 当第一个击中的时候 这个永远都不会为0了。。
       {
        direct = true ;
       }
 
      
      
   if(pos[0] < 0 && pos[enemynumber-1] >= 0 )
      {
           direct = false  ;
          if (pos[enemynumber-1]== 0+fenshu*64)
          {
              direct=true ;
          }
      }
      
     else if ( pos[0] < 0  )
      {
          direct= true ;
      }
      
}
    
  
}

