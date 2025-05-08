/*
 * bsp_key_app.h
 *
 *  Created on: 2025年2月19日
 *      Author: Administrator
 */

#ifndef __BSP_KEY_APP_H_
#define __BSP_KEY_APP_H_
#include "main.h"


typedef struct{

  uint8_t key_wifi_flag;
  uint8_t key_power_flag;
  uint8_t key_mode_flag;
  uint8_t key_dec_flag;
  uint8_t key_add_flag;
  uint8_t key_plasma_flag;
  uint8_t key_dry_flag;
  uint8_t key_mouse_flag;


}KEY_T_TYPEDEF;

extern KEY_T_TYPEDEF key_t;

void process_keys(void) ;



#endif /* BSP_INC_BSP_KEY_APP_H_ */
