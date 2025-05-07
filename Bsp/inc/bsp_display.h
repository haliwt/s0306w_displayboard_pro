#ifndef __BSP_DISPLAY_H_
#define __BSP_DISPLAY_H_

#include "main.h"

void Display_DHT11_Value(void);

//void DisplaySMG_LED(void);




void Display_Timing(uint8_t hours,uint8_t minutes);


void Display_Error_Digital(uint8_t errnumbers,uint8_t sel);



void Display_TimeColon_Blink_Fun(void);

void Warning_Error_Numbers_Fun(void);



#endif 
