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
bool collision2( SDL_Rect arrEnemyBullet, SDL_Rect nowbee );
void rend_enemybullet ( void );
bool nextbullet ( void);
int randomnumber (void);
extern bool end;
extern SDL_Rect Beepos;
extern int pos[99];

#endif /* judgeLogic_h */
