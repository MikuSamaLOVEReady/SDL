//
//  judgeLogic.h
//  LittleBee
//
//  Created by 罗瑞笛 on 2019/2/26.
//  Copyright © 2019年 罗瑞笛. All rights reserved.
//

#ifndef judgeLogic_h
#define judgeLogic_h

#include <stdio.h>
#include <stdbool.h>
#include  <SDL2/SDL.h>
#include "initialize.h"

void input(void );
bool update( void );
void rend_bullet (void);
void flyway(void); //子弹飞行函数
void score (void );
void countpos ( int key ); // 子弹位置记录
bool collision ( SDL_Rect *arrbulet , int *arrD );
void rend_enemybullet ( void );
bool nextbullet ( void);


#endif /* judgeLogic_h */
