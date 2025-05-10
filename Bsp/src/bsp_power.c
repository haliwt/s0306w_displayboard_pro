#include "bsp.h"

RUN_T run_t;



uint8_t power_on_off_flag;

void Power_Off(void);


/**********************************************************************
*
*Functin Name: void Display_DHT11_Value(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Power_Off(void)
{
    Smg_AllOff();
    SMG_POWER_OFF()	;
	run_t.gPlasma=0;
	run_t.gDry=0;
	run_t.gMouse =0;
	//run_t.gWifi_led = 0;
			
}


/**********************************************************************
*
*Functin Name: void Receive_ManiBoard_Cmd(uint8_t cmd)
*Function :  wifi recieve data
*Input Ref:  receive wifi send order
*Return Ref: NO
*
**********************************************************************/
void Power_On_Fun(void)
{
                
   static uint8_t hour_decade,hour_unit,minutes_one,minutes_two;

  
   if(gpro_t.smartphone_app_timer_power_on_flag == 0){
		run_t.gPlasma=1;
		run_t.gDry =1;
        run_t.gMouse = 1;
		run_t.ai_model_flag =ai_mode;

   	}
    else{

	    run_t.ai_model_flag =ai_mode;

	}

  


    run_t.time_led_flag=1;
	Power_ON_Led();

	run_t.fan_warning=0;
	run_t.ptc_warning=0;
 
	
    run_t.gTimer_timer_timing_counter=0;
    gpro_t.set_timer_timing_value_success =0 ;
    gpro_t.set_temp_value_success = 0;
   
	run_t.timer_dispTime_hours =0;
	run_t.timer_dispTime_minutes=0;
		
        

	  hour_decade=0;
	  hour_unit=0;
    
	  minutes_one = 0;
      minutes_two = 0;
	  
	   SMG_POWER_ON(); //WT.EDIT 2023.03.02
      


	  run_t.hours_two_unit_bit = hour_unit;
	  run_t.minutes_one_decade_bit =  minutes_one;
      
	 TM1639_Write_4Bit_Time(hour_decade,run_t.hours_two_unit_bit,run_t.minutes_one_decade_bit,minutes_two,0);
     //Display_DHT11_Value(); //WT.EIDT 2025.05.10
    
}


/************************************************************************
	*
	*Function Name: static void Power_Off_Fun(void)
	*
	*
	*
	*
************************************************************************/
void Power_Off_Fun(void)
{
	
 
		run_t.gPlasma=0;
		run_t.gDry =0;
		run_t.gMouse = 0;
		
       

  
} 


