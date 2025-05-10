#include "bsp.h"


/***********************************************************
*
*
*
*
*
***********************************************************/
#if 0
uint8_t KEY_Scan(void)
{
  uint8_t  reval = 0;
  key_t.read = _KEY_ALL_OFF; //0xFF 


    if(WIFI_KEY_VALUE() ==1 ) //WIFI_KEY_ID = 0x80
	{
		key_t.read &= ~0x80; // 0x1f & 0x7F =  0x7F
	}
    else if(MOUSE_KEY_VALUE()   ==1 ) //FAN_KEY_ID = 0x10
	{
		  key_t.read &= ~0x10; // 0xFf & 0xEF =  0xEF
	}
	else if(PLASMA_KEY_VALUE()   ==1 ) //PLASMA_KEY_ID = 0x20
	{
		  key_t.read &= ~0x20; // 0xFf & 0xDF =  0xDF
	}
	else if(DRY_KEY_VALUE()  ==1 ) //DRY_KEY_ID = 0x40
	{
		  key_t.read &= ~0x40; // 0xFf & 0xBF =  0xBF
	}

	
	
   
    switch(key_t.state )
	{
		case start:
		{
			if(key_t.read != _KEY_ALL_OFF)
			{
				key_t.buffer   = key_t.read; //??:key.buffer = 0xFE  POWER KEY 
				key_t.state    = first;
				key_t.on_time  = 0;
				key_t.off_time = 0;
            
                
			}
			break;
		}
		case first:
		{
			if(key_t.read == key_t.buffer) //  short  key be down ->continunce be pressed key
			{
				if(++key_t.on_time>35 )//25 //10000  0.5us
				{
					//run_t.power_times++;
                    key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0xFE ^ 0xFF = 0x01
					key_t.on_time = 0;                      //key .value = 0xEF ^ 0XFF = 0X10
                    key_t.state   = second;
                   
                    
				}
			  
			}
			else
			{
				key_t.state   = start;
			}
			break;
		}
		case second:
		{
			if(key_t.read == key_t.buffer) //long key key if be pressed down 
			{
				if(++key_t.on_time>70000)// 80000 long key be down
				{
				    key_t.value = key_t.value|0x80; //key.value = 0x02 | 0x80  =0x82
                    key_t.on_time = 0;
					key_t.state   = finish;
	               
				}
					
			}
			else if(key_t.read == _KEY_ALL_OFF)  // loose hand 
			{
					if(++key_t.off_time> 0) //20//30 don't holding key dithering
					{
						key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
						key_t.state   = finish; // loose hand
					}
			}
		   
			break;
		}
		case finish:
		{
		
			reval = key_t.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81

			key_t.state   = end;
         
			break;
		}
		case end:
		{
			if(key_t.read == _KEY_ALL_OFF)
			{
				if(++key_t.off_time>0)//5//10//50 //100
				{
					key_t.state   = start;
                  
				}
			}
			break;
		}
		default:
		{
			key_t.state   = start;
         
			break;
		}
	}
	return  reval;


}

#endif 

/****************************************************************
	*
	*Function Name :void Set_Timing_Temperature_Number_Value(void)
	*Function : set timer timing how many ?
	*Input Parameters :NO
	*Retrurn Parameter :NO
	*
*****************************************************************/
void Set_TimerTiming_Number_Value(void)
{
  static uint8_t default_numbers =0xff;
   if(gpro_t.set_timer_timing_doing_value==1){
   //set timer timing value 
    if(run_t.gTimer_key_timing > 3){
		run_t.gTimer_key_timing =0;		
		gpro_t.set_timer_timing_doing_value ++ ;
	    run_t.gTimer_timer_timing_counter=0;
	
	 }

    }

    if(gpro_t.set_timer_timing_doing_value==2){
    	gpro_t.set_timer_timing_doing_value++;
		if(run_t.temporary_timer_dispTime_hours >0 ){
			gpro_t.set_timer_timing_value_success  = TIMER_SUCCESS;
			run_t.gTimer_timer_timing_counter = 0;

			run_t.timer_dispTime_hours = run_t.temporary_timer_dispTime_hours ;
			if(default_numbers != gpro_t.input_numbers_flag){
				default_numbers = gpro_t.input_numbers_flag;
			     run_t.timer_dispTime_minutes = 0;

			}

			Display_Timing(run_t.timer_dispTime_hours,run_t.timer_dispTime_minutes);


		}
		else{

			gpro_t.set_timer_timing_value_success  = 0;



		}


    }
}

void set_timer_fun_led_blink(void)
{
   static uint8_t time_smg_blink;
 
   if(gpro_t.set_timer_timing_doing_value==1){
   	

     if(gpro_t.gTimer_4bitsmg_blink_times  > 300){// //180ms
       gpro_t.gTimer_4bitsmg_blink_times =0;

       time_smg_blink = time_smg_blink ^ 0x01;

  
       TM1639_Write_4Bit_Time_sync_close(run_t.hours_two_decade_bit,run_t.hours_two_unit_bit, run_t.minutes_one_decade_bit,run_t.minutes_one_unit_bit,time_smg_blink) ; 
    
       
    
   }

   }
  
}



/****************************************************************
	*
	*Function Name :void disp_smg_blink_set_tempeature_value(void)
	*Function : set timer timing how many ?
	*Input Parameters :NO
	*Retrurn Parameter :NO
	*
*****************************************************************/
void disp_smg_blink_set_tempeature_value(void)
{
     static uint8_t counter_times;
	  //waiting for 4 s 
	  if(run_t.gTimer_key_temp_timing > 1 && run_t.set_temperature_special_flag ==1 && (gpro_t.set_timer_timing_doing_value==0 || gpro_t.set_timer_timing_doing_value==3)){
			
			
			run_t.set_temperature_special_flag =2;
			run_t.gTimer_set_temp_times =0; //couter time of smg blink timing 

	 }
	 //temperature of smg of LED blink .
	  if(run_t.set_temperature_special_flag ==2 && (gpro_t.set_timer_timing_doing_value==0 ||gpro_t.set_timer_timing_doing_value==3)){
	  	
	  	 
		  if(run_t.gTimer_set_temp_times  > 0  && run_t.set_temperature_special_flag !=0xff){ // 15ms * 4 =60ms
                 run_t.gTimer_set_temp_times=0;
                 counter_times++ ;  
// cancel display temperature SMG number led blink function.
//                 every_times ++;
//          if(every_times ==1){
//               
//		        TM1639_Write_2bit_SetUp_TempData(run_t.set_temperature_decade_value,run_t.set_temperature_unit_value,1);
//          }
//		  else{
//		  	   every_times=0;
			  TM1639_Write_2bit_SetUp_TempData(run_t.set_temperature_decade_value,run_t.set_temperature_unit_value,0);

		  }
       


           if(counter_times > 1){
			 
           		counter_times=0;
          
			 gpro_t.set_temp_value_success=1;
			 
	         run_t.set_temperature_special_flag =0xff;
			  run_t.gTimer_temp_delay = 70; //at once shut down ptc  funciton
			  run_t.gTimer_display_dht11 = 90;
		
			  
			//  SendData_Tx_Data(0x11,gpro_t.set_up_temperature_value);
			  TM1639_Write_2bit_SetUp_TempData(run_t.set_temperature_decade_value,run_t.set_temperature_unit_value,0);
             
			  Display_DHT11_Value();
             
			   SendData_ToMainboard_Data(0x2A,gpro_t.set_up_temperature_value,0x01); //WT.EDIT 2025.05.06
    		   osDelay(5);
			   compare_temp_value();
			  // send_data =1;
			  
              
             }
	     }

//     if(send_data < 3 && send_data > 0){
//	 	send_data ++;
//
//	   SendData_ToMainboard_Data(0x2A,gpro_t.set_up_temperature_value,0x01); //WT.EDIT 2025.05.06
//	   osDelay(5);
//
//	 }
}


/****************************************************************
	*
	*Function Name :void mode_key_handler(void) 
	*Function : 
	*Input Parameters :NO
	*Retrurn Parameter :NO
	*
*****************************************************************/
#if 0
// 按键参数宏定义
#define KEY_LONG_PRESS_THRESHOLD   30  // 长按触发阈值（30个周期=300ms）
#define KEY_SHORT_PRESS_MIN        1   // 短按最小时间（1个周期=10ms）
#define KEY_MAX_COUNTER            60  // 计数器最大值
#define DEBOUNCE_DELAY_MS          5   // 消抖延时
#define SHORT_PRESS_COOLDOWN       5   // 短按冷却时间（5个周期=50ms）

void mode_key_handler(void) 
{
    static uint8_t last_key_state = KEY_UP;
    static bool long_press_handled = false;
    static uint8_t short_press_cooldown = 0;  // 新增：短按冷却计数器
    
    //if (run_t.gPower_On != power_on) return;

    uint8_t current_key_state = MODEL_KEY_VALUE();


	 /* 按键释放处理 */
    if (current_key_state == KEY_UP && void mode_key_handler(void) ) {
        // 短按触发判断（增加冷却时间判断）
        if (!long_press_handled  &&  gpro_t.mode_Key_long_counter < KEY_LONG_PRESS_THRESHOLD ) {
            key_t.key_mode_flag ++;
            gpro_t.look_over_timer_state = 1;
		     gpro_t.mode_key_shot_flag =1;
            SendData_Buzzer();
            //osDelay(DEBOUNCE_DELAY_MS);
            //mode_key_short_fun();
			
           // short_press_cooldown = SHORT_PRESS_COOLDOWN; // 设置冷却时间
        }
        
        // 释放后重置状态
        gpro_t.mode_Key_long_counter = 0;
        long_press_handled = false;
     }
     else if (current_key_state == KEY_DOWN) { /* 按键按下处理 */
        if (gpro_t.mode_Key_long_counter < KEY_MAX_COUNTER) {
            gpro_t.mode_Key_long_counter++;
        }

        // 长按触发判断
        if (gpro_t.mode_Key_long_counter >= KEY_LONG_PRESS_THRESHOLD) {
            if (!long_press_handled) {
				key_t.key_mode_flag ++;
                SendData_Buzzer();
                osDelay(DEBOUNCE_DELAY_MS);
                mode_key_long_fun();
                long_press_handled = true;
            }
        }
    } 
   
    
    last_key_state = current_key_state;
}
#endif 

#if 0

// 按键参数宏定义
#define KEY_LONG_PRESS_THRESHOLD   30  // 长按触发阈值（30*10ms=300ms）
#define KEY_SHORT_PRESS_MIN        1   // 最小按下时间（1*10ms=10ms）
#define DEBOUNCE_DELAY_MS          5   // 消抖延时

void mode_key_handler(void) 
{
    static uint8_t last_key_state = KEY_UP;
    static bool long_press_handled = false;
    
    if (run_t.gPower_On != power_on) return;

    uint8_t current_key_state = MODEL_KEY_VALUE();
    
    /*----------- 按键按下处理 -----------*/
    if (current_key_state == KEY_DOWN) {
        // 首次按下（从释放到按下的边沿）
        if (last_key_state == KEY_UP) {
            // 立即触发短按功能
            SendData_Buzzer();
            osDelay(DEBOUNCE_DELAY_MS);
            mode_key_short_fun();
            
            // 重置长按计数器
            gpro_t.mode_Key_long_counter = 0;
            long_press_handled = false;
        }
        
        // 长按检测（持续按下时处理）
        if (gpro_t.mode_Key_long_counter < KEY_LONG_PRESS_THRESHOLD) {
            gpro_t.mode_Key_long_counter++;
        }
        
        // 长按触发
        if (gpro_t.mode_Key_long_counter >= KEY_LONG_PRESS_THRESHOLD && !long_press_handled) {
            SendData_Buzzer();
            osDelay(DEBOUNCE_DELAY_MS);
            mode_key_long_fun();
            long_press_handled = true;
        }
    } 
    /*----------- 按键释放处理 -----------*/
    else if (current_key_state == KEY_UP) {
        // 释放时重置长按状态
        gpro_t.mode_Key_long_counter = 0;
        long_press_handled = false;
    }
    
    last_key_state = current_key_state; // 更新状态
}

#endif 


