#ifndef __BSP_LED_H_
#define __BSP_LED_H_
#include "main.h"


#define LED_POWER_TOGGLE()            HAL_GPIO_TogglePin(LED_POWER_GPIO_Port, LED_POWER_Pin)
#define LED_POWER_ON()				  HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin,GPIO_PIN_SET)
#define LED_POWER_OFF()            	  HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin,GPIO_PIN_RESET)



#if 0
#define LED_WIFI_ON()			  HAL_GPIO_WritePin(WIFI_LED_EN_GPIO_Port , WIFI_LED_EN_Pin,GPIO_PIN_SET)
#define LED_WIFI_OFF()    	      HAL_GPIO_WritePin(WIFI_LED_EN_GPIO_Port , WIFI_LED_EN_Pin,GPIO_PIN_RESET)
#define LED_WIFI_TOGGLE()         HAL_GPIO_TogglePin(WIFI_LED_EN_GPIO_Port, WIFI_LED_EN_Pin)
#else 
// 寄存器方式控制 LED
#define LED_WIFI_ON()             (WIFI_LED_EN_GPIO_Port->BSRR = WIFI_LED_EN_Pin)
#define LED_WIFI_OFF()            (WIFI_LED_EN_GPIO_Port->BRR = WIFI_LED_EN_Pin)
#define LED_WIFI_TOGGLE()         (WIFI_LED_EN_GPIO_Port->ODR ^= WIFI_LED_EN_Pin)
#endif 


#define LED_DRY_ON()			  HAL_GPIO_WritePin(DRY_LED_EN_GPIO_Port, DRY_LED_EN_Pin,GPIO_PIN_SET)
#define LED_DRY_OFF()             HAL_GPIO_WritePin(DRY_LED_EN_GPIO_Port, DRY_LED_EN_Pin,GPIO_PIN_RESET)

#define LED_TIME_ON()			   HAL_GPIO_WritePin(TIME_LED_EN_GPIO_Port, TIME_LED_EN_Pin ,GPIO_PIN_SET)
#define LED_TIME_OFF()             HAL_GPIO_WritePin(TIME_LED_EN_GPIO_Port, TIME_LED_EN_Pin ,GPIO_PIN_RESET)

#define LED_PLASMA_ON()				HAL_GPIO_WritePin(PLASMA_LED_EN_GPIO_Port, PLASMA_LED_EN_Pin,GPIO_PIN_SET)
#define LED_PLASMA_OFF()            HAL_GPIO_WritePin(PLASMA_LED_EN_GPIO_Port, PLASMA_LED_EN_Pin,GPIO_PIN_RESET)


#define LED_MOUSE_ON()  			HAL_GPIO_WritePin(GPIOB, MOUSE_LED_Pin,GPIO_PIN_SET)
#define LED_MOUSE_OFF()				HAL_GPIO_WritePin(GPIOB, MOUSE_LED_Pin,GPIO_PIN_RESET)


//control SMG supply power 
#define SMG_POWER_ON()				HAL_GPIO_WritePin(SMG_POWER_GPIO_Port , SMG_POWER_Pin,GPIO_PIN_SET)
#define SMG_POWER_OFF()             HAL_GPIO_WritePin(SMG_POWER_GPIO_Port , SMG_POWER_Pin,GPIO_PIN_RESET)







extern void (*panel_led_fun)(void);

void Panel_Led_OnOff_RunCmd(void (*panelledHandler)(void));

//void KeyLed_Power_On(void);


//void ALL_LED_Off(void);

void Panel_Led_OnOff_Function(void);

void AI_Auto_Stop(void);
void Breath_Led(void);

void Power_Off_Led_Off(void);


void Power_ON_Led(void);





#endif 
