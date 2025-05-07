#ifndef __BSP_DISPLAY_DYNAMIC_H
#define __BSP_DISPLAY_DYNAMIC_H
#include "main.h"

typedef enum {
   
    RUN_POWER_ON=0x01,
	RUN_POWER_OFF,
    UPDATE_DATA,
    SPECIAL_DISP,
    POWER_OFF_PROCESS,
    RUN_WIFI_NORMAL_POWER_ON,
    RUN_NULL

}power_on_state_t;

extern void (*single_ai_fun)(uint8_t cmd);
extern void (*single_add_fun)(void);
extern void (*sendAi_usart_fun)(uint8_t senddat);
extern void (*dispose_key)(uint8_t dsdat);
extern void (*display_fan_speed_value)(uint8_t fan_level);

void Scan_KeyMode(void);
void Single_RunCmd(void);

void Smg_DisplayFan_Speed_Level_Init(void);

void RunReference_Fun(void);

void Single_AI_RunCmd(void (*singlaieHandler)(uint8_t dat));

void Single_Add_RunCmd(void(*addHandler)(void));

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void));

void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat));

void SplitDispose_Key_RunCmd(void(*keyHandler)(uint8_t dat));

//void Smg_DisplayFan_Leve(void(*fandisplayHandler)(uint8_t fan_level));

//void Display_SetTemperature_Value(void);

void Display_SmgTiming_Value(void);

void Led_Panel_OnOff(void);

void RunLocal_Dht11_Data_Process(void);




#endif 

