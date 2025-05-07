#ifndef __BSP_KEY_H_
#define __BSP_KEY_H_
#include "main.h"


#define TOUCH_KEY_IC_1_VALUE()      HAL_GPIO_ReadPin(GPIOC,TOUCH_KEY_IC_1_Pin)
#define TOUCH_KEY_IC_2_VALUE()      HAL_GPIO_ReadPin(GPIOC,TOUCH_KEY_IC_2_Pin)



#define POWER_KEY_VALUE()            HAL_GPIO_ReadPin(GPIOC ,POWER_KEY_Pin)
#define MODEL_KEY_VALUE()            HAL_GPIO_ReadPin(GPIOA,MODEL_KEY_Pin)
#define DEC_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOA,DEC_KEY_Pin)
#define ADD_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOA,ADD_KEY_Pin)


#define MOUSE_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,MOUSE_KEY_Pin)
#define PLASMA_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,PLASMA_KEY_Pin)
#define DRY_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,DRY_KEY_Pin)
#define WIFI_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,AI_KEY_Pin)





#define		_KEY_ALL_OFF				 0XFF

//normal times be pressed key
#define		_KEY_TRG_1_POWER     		0x01  //WK_UP
#define		_KEY_TRG_2_MODE     		0x02  //??????--???
#define		_KEY_TRG_3_DEC     			0x04  //????
#define		_KEY_TRG_4_ADD     			0x08

#define		_KEY_TRG_5_FAN     			0x10  //WK_UP
#define		_KEY_TRG_6_STER     		0x20  //??????--???
#define		_KEY_TRG_7_DRY    			0x40   //????
#define		_KEY_TRG_8_AI     			0x80




// combination of buttons 
#define		_KEY_TRG_1_WINDTI   			0x11   //?????
#define		_KEY_TRG_2_WINDTI   			0x12   //?????
#define		_KEY_TRG_3_WINDTI   			0x14   //?????
#define		_KEY_TRG_4_WINDTI   			0x18   //?????

//long times be pressed
#define		_KEY_CONT_1_POWER     	     0x81    //??????--???
#define		_KEY_CONT_2_MODE   		     0x82    //??????--???
#define		_KEY_CONT_3_DEC    	         0x84    //?????? ?????
#define		_KEY_CONT_4_ADD     	     0x88    //??? --?????

#define		_KEY_CONT_5_FAN     		 0x90
#define		_KEY_CONT_6_STER     		 0xA0
#define     _KEY_CONT_7_DRY              0XC0 
#define     _KEY_CONT_8_DRY              0X100 




#define		_KEY_CONT_1     	    0x81    //?????
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88

#define		_KEY_COM_1    		    0x91
#define		_KEY_COM_2    		    0x92
#define		_KEY_COM_3    		    0x94
#define		_KEY_COM_4    		    0x98

#define HIGH_LEVEL                   1  /* ����ԭ��ͼ��ƣ�KEY1����ʱ����Ϊ�͵�ƽ��������������Ϊ0 */


typedef enum{

	 DRY_ON = 0x40,
	 DRY_OFF = 0x41,

     DRY_ON_NO_BUZZER = 0x90,
	 DRY_OFF_NO_BUZZER = 0x91,

	 PLASMA_ON = 0x20,
	 PLASMA_OFF = 0x21,
     PLASM_ON_NO_BUZZER = 0xA0,
     PLASM_OFF_NO_BUZZER = 0xA1,

     

	 FAN_LEVEL_MIN =0x10,
	 MOUSE_RUN = 0x11,
	 FAN_LEVEL_MAX_NO_SOUND = 0x12,
	 MOUSE_STOP = 0x13,
	 

     AI_MODE_ON = 0x30,   //EDIT 2023.09.13 new Add
     AI_MODE_OFF =0x31

}works_t;



typedef enum
{

 
 KEY_UP ,
 KEY_DOWN ,

}KEYState_TypeDef;

typedef enum{

   POWER_KEY_ID = 0x01,
   MODEL_KEY_ID = 0x02,
   DEC_KEY_ID = 0x04,
   ADD_KEY_ID = 0x08,

   FAN_KEY_ID = 0x10,
   PLASMA_KEY_ID = 0x20,
   DRY_KEY_ID = 0x40,
   AI_KEY_ID =0x80,
   MODE_LONG_KEY_ID = 0x82
  
}key_item_t;

typedef enum{
	TIMER_TIMING_DONOT_VALUE,
	TIMER_TIMING_ITEM ,
	set_timer_timing_item,
	


}set_timer_state;



//typedef enum{
//
//   NO_AI_MODE,
//   AI_MODE,
//
//
//}ai_mode_state;

typedef enum{
   wifi_connect_null,
   wifi_connect_success
}wifi_state_connect;




typedef  struct  _state_
{
 unsigned char        read;
 unsigned char        buffer;
  unsigned long       value;
 unsigned char        off_time;
 unsigned long        on_time;

 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;



uint8_t KEY_Scan(void);


uint8_t KEY_Normal_Scan(uint8_t mode);

//void SplitDispose_Key(uint8_t value);

void Set_TimerTiming_Number_Value(void);

void disp_smg_blink_set_tempeature_value(void);


void set_timer_fun_led_blink(void);





#endif 


