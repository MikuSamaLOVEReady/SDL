//
// 渲染文字阶段
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

int count =1;


SDL_Window* window ;

SDL_Surface* surface;

SDL_Surface* textsurface;

//文字
TTF_Font * font = NULL ;
SDL_Texture * font_texture ;

SDL_Renderer* render;// 双渲染测试
//记分版
SDL_Rect sco;




int main(int argc, const char * argv[]) {
    
    SDL_Init ( SDL_INIT_VIDEO ) ;
    TTF_Init() ; // 初始化
   
    window = SDL_CreateWindow("test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              500,
                              500,
                              SDL_WINDOW_SHOWN
                              );
    
    render = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("lazy.ttf", 18); //打开文字
    
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
       
    }
    SDL_Color textColor = {0 , 0 , 0}; //文字颜色
    
    sco.x = 50; //  下一个640
    sco.y = 50;
    sco.w = 128;
    sco.h = 64;
  
    //文字surface
    textsurface = TTF_RenderText_Solid( font,"1fgagafgahhahaerh" , textColor);// 这步比较特殊 原来从图片 现在从这个函数？？创建surface
   // TTF_RenderText_Solid(<#TTF_Font *font#>, <#const char *text#>, <#SDL_Color fg#>)
  
    font_texture  = SDL_CreateTextureFromSurface( render, textsurface );
    

    
    
    SDL_Event event;
    bool end = false;
  
    
    
  
    
while ( !end )
{
    while ( SDL_PollEvent( &event ) != 0 )
    {
        if( event.type == SDL_QUIT ) // SDL_Quit()
        {
            end = true ;
        }
        else if ( event.type == SDL_KEYDOWN ) // 试试else
        {
            /*
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    <#statements#>//
                    break;
                case SDLK_RIGHT:
                    <#statements#>//
                    break;
                    
                default:
                    break;
            }
             */
        }
       
        //SDL_UpdateTexture(texture, &rect, <#const void *pixels#>, <#int pitch#>); 暂时不会
    }
    
    SDL_RenderSetViewport( render , NULL) ;
    SDL_RenderCopy(render, font_texture , NULL , &sco );
    SDL_RenderPresent( render );
    SDL_Delay(160);

 
}


    return 0;
}


/*
双渲染器测试--失败
 
 一个窗口里应该不能同时渲染
 
 记分版 图片？  还是view port
 
 
 
 SDL_SetRenderDrawColor( render, 255, 255, 255, 0 );
 
 
 SDL_RenderSetViewport( render , &rect_view) ;// 选定 render 的范围 局部渲染
 
 SDL_RenderCopy(render, texture_render2 , NULL , NULL );
 
 
 
 SDL_RenderCopy(render, texture , NULL , NULL );
 
 */

