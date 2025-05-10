/*
 * bsp_key_app.c
 *
 *  Created on: 2025年2月19日
 *      Author: Administrator
 */

#include "bsp.h"


KEY_T_TYPEDEF key_t;

//void key_add_fun(void);

//void key_dec_fun(void);



typedef struct {
    uint8_t *flag;
    uint8_t threshold;
    void (*onPress)(void);
} KeyHandler;

void handle_key(KeyHandler *handler) 
{
    if (*(handler->flag) == 1) {
        *(handler->flag) += 1;

        if (handler->threshold > 0 && *(handler->flag) > handler->threshold) {
            *(handler->flag) = 80; // 特殊情况处理
        }

        if (handler->onPress) {
            handler->onPress();
        }
    }
}




/**********************************************************************************************************
*	函 数 名: bsp_PutKey
*	功能说明: 将1个键值压入按键FIFO缓冲区。可用于模拟一个按键。
*	形    参:  _KeyCode : 按键代码
*	返 回 值: 无
**********************************************************************************************************/
void sendCommandAndAck(uint8_t cmd, uint8_t value, uint8_t ackType) {
    SendData_Set_Command(cmd, value);
    osDelay(5);
    gpro_t.send_ack_cmd = ackType;
    gpro_t.gTimer_again_send_power_on_off = 0;
}

/**********************************************************************************************************
*	函 数 名: void power_key_handler(void) 
*	功能说明: 从按键FIFO缓冲区读取一个键值。
*	形    参:  无
*	返 回 值: 按键代码
**********************************************************************************************************/
void power_key_handler(void) 
{
    if(run_t.gPower_On == power_off){
        SendData_PowerOnOff(1); // power on
    } else {
        SendData_PowerOnOff(0); // power off
    }
    osDelay(10);
}


/**********************************************************************************************************
*	函 数 名: void plasma_key_handler(void) 
*	功能说明: 从按键FIFO缓冲区读取一个键值。
*	形    参:  无
*	返 回 值: 按键代码
**********************************************************************************************************/
void plasma_key_handler(void) 
{
    if(gpro_t.set_timer_timing_doing_value==0 ||gpro_t.set_timer_timing_doing_value==3){
        if(run_t.gPlasma == 1){
            run_t.gPlasma = 0;
            SendData_Set_Command(plasma_cmd, 0x00);
            LED_PLASMA_OFF();
            gpro_t.send_ack_cmd = check_ack_plasma_off;
        } else {
            run_t.gPlasma = 1;
            SendData_Set_Command(plasma_cmd, 0x01);
            LED_PLASMA_ON();
            gpro_t.send_ack_cmd = check_ack_plasma_on;
        }
        gpro_t.gTimer_again_send_power_on_off = 0;
    }
}

void dry_key_handler(void) 
{
    if(gpro_t.set_timer_timing_doing_value == 0 || gpro_t.set_timer_timing_doing_value == 3) {
        if(run_t.gDry == 0) {
            sendCommandAndAck(dry_cmd, 0x01, check_ack_ptc_on);
            run_t.gDry = 1;
            gpro_t.g_manual_shutoff_dry_flag = 0;
            LED_DRY_ON();
        } else {
            sendCommandAndAck(dry_cmd, 0x00, check_ack_ptc_off);
            run_t.gDry = 0;
            gpro_t.g_manual_shutoff_dry_flag = 1; // 手动关闭后不再自动开启
            LED_DRY_OFF();
        }
    }
}

void mouse_key_handler(void) 
{
    if(gpro_t.set_timer_timing_doing_value == 0 || gpro_t.set_timer_timing_doing_value == 3) {
        if(run_t.gMouse == 0) {
            // 开启 Mouse 功能
            SendData_Set_Command(mouse_cmd, 0x01);
            osDelay(5);
            run_t.gMouse = 1;
            LED_MOUSE_ON();
            gpro_t.send_ack_cmd = check_ack_mouse_on;  // 假设有对应的反馈类型
            gpro_t.gTimer_again_send_power_on_off = 0;

        } else if(run_t.gMouse == 1) {
            // 关闭 Mouse 功能
            SendData_Set_Command(mouse_cmd, 0x00);
            osDelay(5);
            run_t.gMouse = 0;
            LED_MOUSE_OFF();
            gpro_t.send_ack_cmd = check_ack_mouse_off;  // 假设有对应的反馈类型
            gpro_t.gTimer_again_send_power_on_off = 0;
        }
    }
}

void key_add_fun(void)
{
    if(run_t.ptc_warning != 0) return;

    run_t.gTimer_time_colon = 0;

    switch(gpro_t.set_timer_timing_doing_value)
    {

	    case 3:
		case 0:  // 设置温度增加
            SendData_Buzzer();
            set_temperature_value(+1);
            break;

        case 1:  // 设置定时增加（每次加60分钟）
           // SendData_Buzzer();
            run_t.gTimer_key_timing = 0;

            adjust_timer_minutes(1);  // 固定每次加60分钟
            break;
    }
}


void key_dec_fun(void)
{
    if(run_t.ptc_warning != 0) return;

    switch(gpro_t.set_timer_timing_doing_value)
    {

        case 3:
		case 0:  // 设置温度减少
            SendData_Buzzer();
            set_temperature_value(-1);
            break;

        case 1:  // 设置定时减少（每次减60分钟）
            //SendData_Buzzer();
            run_t.gTimer_key_timing = 0;

            adjust_timer_minutes(-1);  // 固定每次减60分钟
            break;
    }
}

// 类似地定义 dry_key_handler, add_key_handler, dec_key_handler 等



/*
*********************************************************************************************************
*	函 数 名: void process_keys(void) 
*	功能说明:
*	形    参：无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
void process_keys(void) 
{
    // 处理WiFi键
    if(WIFI_KEY_VALUE() == KEY_DOWN && key_t.key_wifi_flag < 60 && run_t.gPower_On == power_on) {
        key_t.key_wifi_flag++;
        if(key_t.key_wifi_flag > 30) {
            key_t.key_wifi_flag = 80;
            SendData_Buzzer();
			osDelay(5);
        }
    }

	//mode_key_handler() ;

    // 定义所有按键处理器
    KeyHandler handlers[] = {
        { &key_t.key_power_flag, 0, power_key_handler },
       // { &key_t.key_mode_flag, 0, mode_key_handler },
        { &key_t.key_dec_flag, 0, key_dec_fun },
        { &key_t.key_add_flag, 0, key_add_fun },
        { &key_t.key_plasma_flag, 0, plasma_key_handler },
        { &key_t.key_dry_flag, 0, dry_key_handler },
        { &key_t.key_mouse_flag, 0, mouse_key_handler },
    };

    // 循环处理每个按键
    for (int i = 0; i < sizeof(handlers)/sizeof(handlers[0]); i++) {
        handle_key(&handlers[i]);
    }
}



