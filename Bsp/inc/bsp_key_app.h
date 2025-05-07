/*
 * bsp_key_app.h
 *
 *  Created on: 2025年2月19日
 *      Author: Administrator
 */

#ifndef BSP_INC_BSP_KEY_APP_H_
#define BSP_INC_BSP_KEY_APP_H_
#include "main.h"

typedef struct {

	uint8_t key_power_flag;
	uint8_t key_mode_flag;
	uint8_t key_dec_flag;
	uint8_t key_add_flag;
	uint8_t key_wifi_flag;
	uint8_t key_dry_flag;
	uint8_t key_plasma_flag;
	uint8_t key_mouse_flag;


}key_id_state;

extern key_id_state key_t;


/* 按键FIFO用到变量 */
#define KEY_FIFO_SIZE	1
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];		/* 键值缓冲区 */
	uint8_t Read;					/* 缓冲区读指针1 */
	uint8_t Write;					/* 缓冲区写指针 */
	uint8_t Read2;					/* 缓冲区读指针2 */
}KEY_FIFO_T;

typedef enum
{
	KEY_NONE = 0,			/* 0 表示按键事件 */

	KEY_POWER_DOWN,				/* POWER KEY 键按下 */
	KEY_MODE_DOWN,				/* MODE 键按下 */
	KEY_DEC_DOWN,				/* 3键按下 */
    KEY_ADD_DOWN,				/* 4键按下 */
    KEY_AI_DOWN,				/* 5键按下 */
    KEY_DRY_DOWN,				/* 6键按下 */
	KEY_PLASMA_DOWN,				/* 7键按下 */
	KEY_MOUSE_DOWN,				/* 8键按下 */


}KEY_ENUM;


void bsp_KeyScan(void);


uint8_t bsp_GetKey(void);


void bsp_ClearKey(void);


#endif /* BSP_INC_BSP_KEY_APP_H_ */
