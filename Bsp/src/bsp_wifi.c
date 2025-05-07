#include "bsp.h"

static void  wifi_ico_fast_blink(void);


void wifi_connect_state_fun(uint8_t data)
{

    static uint8_t wifi_led_blink;
	switch(data){
    
    case 0x01:

        if(run_t.gTimer_wifi_connect_counter <120){
           
            LED_WIFI_TOGGLE() ;
            osDelay(50);
        }
        else{
            run_t.wifi_led_fast_blink =0;
           
        }



    break;

    case 0:
    if(run_t.wifi_connect_state_flag == wifi_connect_null){

	   if(gpro_t.gTimer_wifi_led_blink > 1){
	    gpro_t.gTimer_wifi_led_blink =0;

	      wifi_led_blink = wifi_led_blink ^ 0x01;
	      if(wifi_led_blink ==1){
	   	     LED_WIFI_ON() ;
	       }
		   else{
             LED_WIFI_OFF();

		   }
	   }
    }
    else{
        LED_WIFI_ON();
    }

    break;




    }

}



static void  wifi_ico_fast_blink(void)
{

   static uint8_t ai_led_blink;
    if(gpro_t.set_timer_timing_doing_value==1 || gpro_t.set_timer_timing_doing_value==3){
    if(run_t.gTimer_smg_blink_times > 100){

        run_t.gTimer_smg_blink_times=0;
        ai_led_blink ++;

        if(ai_led_blink ==1){
        
              LED_WIFI_ON();
         }
          else{
            ai_led_blink =0;
            LED_WIFI_OFF();
       
           }
          
       }
  }

}

