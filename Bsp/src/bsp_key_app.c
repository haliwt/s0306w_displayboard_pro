/*
 * bsp_key_app.c
 *
 *  Created on: 2025年2月19日
 *      Author: Administrator
 */

#include "bsp.h"

key_id_state key_t;
uint8_t keyvalue;
//static KEY_T s_tBtn[KEY_COUNT];
 KEY_FIFO_T s_tKey;		/* 按键FIFO变量,结构体 */

static void bsp_PutKey(uint8_t _KeyCode);
/* 按键扫描 */
void bsp_KeyScan(void)
{

	

	if(POWER_KEY_VALUE()  ==KEY_DOWN){

		keyvalue = KEY_POWER_DOWN;
		bsp_PutKey(keyvalue);
		key_t.key_power_flag =1;
		
	 }
	 else if( MODEL_KEY_VALUE() ==KEY_DOWN){
         if(run_t.gPower_On == power_on){
         key_t.key_mode_flag = 1;
		 keyvalue = KEY_MODE_DOWN;
		 bsp_PutKey(keyvalue);
        }

	  }
	   else if(DEC_KEY_VALUE() == KEY_DOWN){
           if(run_t.gPower_On == power_on){
           key_t.key_dec_flag =1;
		   keyvalue = KEY_DEC_DOWN;
		    bsp_PutKey(keyvalue);
            }
	     }
	     else if(ADD_KEY_VALUE() ==KEY_DOWN){
             if(run_t.gPower_On == power_on){
              key_t.key_add_flag =1;
	    	 keyvalue = KEY_ADD_DOWN;
	    	 bsp_PutKey(keyvalue);
                }


	    }
	     else if(WIFI_KEY_VALUE()==KEY_DOWN){
             if(run_t.gPower_On == power_on){
            	 key_t.key_wifi_flag= 1;
    	    	 keyvalue = KEY_AI_DOWN;
    	    	 bsp_PutKey(keyvalue);
             }

	     }
	     else if(PLASMA_KEY_VALUE()==KEY_DOWN){
              if(run_t.gPower_On == power_on){
            	  key_t.key_plasma_flag =1;
	    	 keyvalue = KEY_PLASMA_DOWN;
	    	  bsp_PutKey(keyvalue);
                }
	     }
	     else if(DRY_KEY_VALUE()==KEY_DOWN){
             if(run_t.gPower_On == power_on){
            	 key_t.key_dry_flag =1;
	    	 keyvalue = KEY_DRY_DOWN;
	    	 bsp_PutKey(keyvalue);
                }

	     }
	     else if(MOUSE_KEY_VALUE() == KEY_DOWN){
             if(run_t.gPower_On == power_on){
            	 key_t.key_mouse_flag =1;
	    	 keyvalue = KEY_MOUSE_DOWN;
	    	 bsp_PutKey(keyvalue);
                }

	     }


}
/**********************************************************************************************************
*	函 数 名: bsp_PutKey
*	功能说明: 将1个键值压入按键FIFO缓冲区。可用于模拟一个按键。
*	形    参:  _KeyCode : 按键代码
*	返 回 值: 无
**********************************************************************************************************/
static void bsp_PutKey(uint8_t _KeyCode)
{
	s_tKey.Buf[0] = _KeyCode;

//	if (++s_tKey.Write  >= KEY_FIFO_SIZE)
//	{
//		s_tKey.Write = 0;
//	}
}

/**********************************************************************************************************
*	函 数 名: bsp_GetKey
*	功能说明: 从按键FIFO缓冲区读取一个键值。
*	形    参:  无
*	返 回 值: 按键代码
**********************************************************************************************************/
// 定义一个函数，用于获取按键值
uint8_t bsp_GetKey(void)
{
	uint8_t ret; // 定义一个变量用于存储返回的按键值

    // 检查读指针和写指针是否相等
	if (s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[0];

//		if (++s_tKey.Read >= KEY_FIFO_SIZE)
//		{
//			s_tKey.Read = 0;
//		}
		return ret;
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_ClearKey
*	功能说明: 清空按键FIFO缓冲区
*	形    参：无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
void bsp_ClearKey(void)
{
	 s_tKey.Write = s_tKey.Read;
}



