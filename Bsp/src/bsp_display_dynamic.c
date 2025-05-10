#include "bsp.h"



void (*single_ai_fun)(uint8_t cmd);
void (*single_add_fun)(void);
void (*single_buzzer_fun)(void);
void (*sendAi_usart_fun)(uint8_t senddat);
void (*dispose_key)(uint8_t dsdat);
void (*display_fan_speed_value)(uint8_t fan_level);





//static void DisplayPanel_DHT11_Value(void);

static void Display_Works_Time_Fun(void);
static void WorksTime_DonotDisplay_Fun(void);
static void Timer_Timing_Donot_Display(void);

//static void Smg_DisplayFan_Level_Value_Fun(uint8_t fan_level);


//
//void Smg_DisplayFan_Speed_Level_Init(void)
//{
//      Smg_DisplayFan_Leve(Smg_DisplayFan_Level_Value_Fun);
//
//}



/******************************************************************************
*
*Function Name:void Single_RunCmd(void)
*Funcion: handle of receive by usart data
*
*
******************************************************************************/
#if 0
static void DisplayPanel_DHT11_Value(void)
{
  if(run_t.first_power_on_times==1){
      run_t.first_power_on_times++;
       Display_DHT11_Value();
  
  }
  if(run_t.gTimer_display_dht11 > 9){
	    run_t.gTimer_display_dht11=0;
       	Display_DHT11_Value();
        compare_temp_value();
     
	}
}
#endif 

/*******************************************************
	*
	*Function Name: static void RunLocal_Dht11_Data_Process(void)
	*Function : display pannel display conetent
	*
	*
	*
*******************************************************/
void RunLocal_Dht11_Data_Process(void)
{

  if(run_t.gTimer_display_dht11 > 9 && (gpro_t.set_timer_timing_doing_value==0||gpro_t.set_timer_timing_doing_value==3)){
	    run_t.gTimer_display_dht11=0;
       	Display_DHT11_Value();
       
     
	}

}




void Led_Panel_OnOff(void)
{
	Panel_Led_OnOff_Function() ;
}
/*******************************************************
	*
	*Function Name: static void RunLocal_Dht11_Data_Process(void)
	*Function : display pannel display conetent
	*
	*
	*
*******************************************************/
#if 0
void Display_SetTemperature_Value(void)
{
    static uint8_t temp_over_flag,set_temp_over_flag;	
    if(gpro_t.set_temp_value_success ==1 && run_t.gTimer_temp_delay >60){
               run_t.gTimer_temp_delay =0;
		 
		 // disp_smg_blink_set_tempeature_value= run_t.set_temperature_decade_value*10+ run_t.set_temperature_unit_value;
		  if(gpro_t.set_up_temperature_value <= run_t.gReal_humtemp[1] || run_t.gReal_humtemp[1] >39){//envirment temperature
	  
				run_t.gDry = 0;
                set_temp_over_flag= 1;
		        SendData_Set_Command(DRY_OFF_NO_BUZZER);//0x91 ->PTC turn off
			    
			    
                
		  }
		  else if((gpro_t.set_up_temperature_value -3) >= run_t.gReal_humtemp[1]){

                run_t.gDry = 1;
                SendData_Set_Command(DRY_ON_NO_BUZZER);//0x90 -> //PTC turn On
           }
	  
	    
	}
    else if( gpro_t.set_temp_value_success ==0){ //no define set up temperature value 
		if(run_t.gReal_humtemp[1] >39 && run_t.gTimer_temp_delay >9){//envirment temperature
			run_t.gTimer_temp_delay =0;
			run_t.gDry = 0;
			temp_over_flag=1; //the first times temperature over 39 degree.
			SendData_Set_Command(DRY_OFF_NO_BUZZER);

		}
        else if(run_t.gReal_humtemp[1] < 38 &&  run_t.gTimer_temp_delay >12 && temp_over_flag ==1){
			run_t.gTimer_temp_delay =0;
			
			run_t.gDry = 1;
			SendData_Set_Command(DRY_ON_NO_BUZZER); //PTC turn On

        }
             
      }
			    
  }

#endif 

/******************************************************************************
* 
* Function Name: static void Timer_Timing_Donot_Display(void)
* Function :function of pointer 
* Input Ref:NO
* Return Ref:NO
* 
*******************************************************************************/
static void Display_Works_Time_Fun(void)
{
     static uint8_t works_timing_flag,alternate_flag;

	 if(run_t.ptc_warning ==0 && run_t.fan_warning ==0){
     if(run_t.gTimes_time_seconds > 59 ){
            run_t.gTimes_time_seconds=0;
            works_timing_flag =1;
			run_t.works_dispTime_minutes++; //1 minute 
		
            run_t.send_app_wokes_minutes_two++;
			if(run_t.works_dispTime_minutes> 59){ //1 hour
			run_t.works_dispTime_minutes=0;
			run_t.works_dispTime_hours++;
			if(run_t.works_dispTime_hours > 99){ //WT.edit times over 99hours 2023.09.20
			run_t.works_dispTime_hours =0;
			}
        
            }

     	}
       
	       if(works_timing_flag==1){
	          works_timing_flag=0;
			 
			 Display_Timing(run_t.works_dispTime_hours,run_t.works_dispTime_minutes);
		  
	        }
		    
        }
		else{

		    if(run_t.gTimer_error_digital < 60){//10ms * 51= 510

		      
               if(alternate_flag ==0){
			   	  
                     
			     if(run_t.ptc_warning ==1){
                 
					Display_Error_Digital(0x01,0);
			     }
				 else {
			        if(run_t.fan_warning ==1){

					  
                      Display_Error_Digital(0x02,0);

			        }

				 }
			    

               }
			   else{

			      alternate_flag=2;
				   if(run_t.ptc_warning ==1 && run_t.fan_warning ==1){

					     Display_Error_Digital(0x02,0);

				   	}
				    else  if(run_t.ptc_warning ==1 && run_t.fan_warning ==0){
                       
					    Display_Error_Digital(0x01,0);
			        }
					else  if(run_t.ptc_warning ==0 && run_t.fan_warning ==1){
                       
					    Display_Error_Digital(0x02,0);
			        }


			   }
			   

		   }
		   else if(run_t.gTimer_error_digital > 59 && run_t.gTimer_error_digital  < 121 ){
		   		alternate_flag++;
 				Display_Error_Digital(0x10,1);
 				if(alternate_flag==2 ||alternate_flag>2 )alternate_flag=0;
		   }
		    else if(run_t.gTimer_error_digital > 119){

			  run_t.gTimer_error_digital=0;


			 }

		}



}

/****************************************************************
 * 
 * Function Name: static void Timer_Timing_Donot_Display(void)
 * Function :function of pointer 
 * Input Ref:NO
 *
 * 
*****************************************************************/
static void Timer_Timing_Donot_Display(void)
{
  if(run_t.gTimer_timer_timing_counter > 59 && gpro_t.set_timer_timing_value_success==TIMER_SUCCESS){
    run_t.gTimer_timer_timing_counter =0;
    run_t.timer_dispTime_minutes -- ;

    if(run_t.timer_dispTime_minutes <  0 ){

    run_t.timer_dispTime_hours -- ;
    run_t.timer_dispTime_minutes =59;
    }



    if(run_t.timer_dispTime_hours <0){ 
    run_t.gTimer_timer_timing_counter = 57 ;
    run_t.timer_dispTime_hours=0;
    run_t.timer_dispTime_minutes=0;
    power_off_run_handler();

    }
			
  }

}

/****************************************************************
 * 
 * Function Name: static void WorksTime_DonotDisplay_Fun(void)
 * Function :function of pointer 
 * 
 *
 * 
****************************************************************/
static void WorksTime_DonotDisplay_Fun(void)
{
//send to APP works times every minute onece
   if(run_t.gTimes_time_seconds > 59 &&  gpro_t.set_timer_timing_value_success ==TIMER_SUCCESS ){
		   run_t.gTimes_time_seconds=0;
		 
		   run_t.works_dispTime_minutes++; //1 minute 
		
		   run_t.send_app_wokes_minutes_two++;
		   if(run_t.works_dispTime_minutes> 59){ //1 hour
		   run_t.works_dispTime_minutes=0;
		   run_t.works_dispTime_hours++;
		   if(run_t.works_dispTime_hours > 24){
		   run_t.works_dispTime_hours =0;
		   }
	       }
  }
}
#if 0
static void Smg_DisplayFan_Level_Value_Fun(uint8_t fan_level)
{

    static uint8_t fan_max=0xff,fan_min=0xff;

    if(fan_level ==fan_speed_max){
    
    if(fan_max != run_t.fan_key_max){
       fan_max = run_t.fan_key_max;
      SendData_Set_Command(MOUSE_RUN);

     }
   }
   else{

       if(fan_min != run_t.fan_key_min){
          fan_min = run_t.fan_key_min;
          SendData_Set_Command(FAN_LEVEL_MIN);
   
        }
   }
    
    TM1639_Write_4Bit_Fan_Level(fan_level);
    if(run_t.gTimer_display_fan_level > 2){
        run_t.gTimer_display_fan_level=0;
        gpro_t.gmouse =0;
        Display_Timing(run_t.timer_dispTime_hours,run_t.timer_dispTime_minutes);

    }
 

}

#endif 

/******************************************************************************
*
*Function Name:static void Setup_Timer_Times(void)
*Funcion:display setup timer times  //__asm("NOP");//等待1个指令周期，系统主频24M
*Iinput Ref:NO
*Return Ref:NO
*
******************************************************************************/
void Display_SmgTiming_Value(void)
{
   switch(gpro_t.set_timer_timing_value_success){

	   case TIMER_SUCCESS:

	   
			   if(run_t.gTimer_timer_timing_counter > 59){
			    run_t.gTimer_timer_timing_counter =0;
			
				run_t.timer_dispTime_minutes -- ;
			
			    if(run_t.timer_dispTime_minutes <  0 ){
					 
				   run_t.timer_dispTime_hours -- ;
				   run_t.timer_dispTime_minutes =59;
		         }

				
				
				 if(run_t.timer_dispTime_hours < 0 ){
				 
					run_t.gTimer_timer_timing_counter = 57 ;
					run_t.timer_dispTime_hours=0;
					run_t.timer_dispTime_minutes=0;
		             
			        gpro_t.send_ack_cmd = check_ack_power_off;//ack_power_off;
					gpro_t.gTimer_again_send_power_on_off =0;
					SendData_PowerOnOff(0);//power off
					
			      }
		}

        Display_Timing(run_t.timer_dispTime_hours,run_t.timer_dispTime_minutes);
        WorksTime_DonotDisplay_Fun();
        
	    break;

		case TIMER_NORMAL_TIMING: //NO_AI_MODE by timer timing  auto be changed AI_MODE
			
    
          if(run_t.gTimes_time_seconds > 59){
    		   run_t.gTimes_time_seconds=0;
    		 
    		   run_t.works_dispTime_minutes++; //1 minute 
    		
    		   run_t.send_app_wokes_minutes_two++;
    		   if(run_t.works_dispTime_minutes> 59){ //1 hour
    		   run_t.works_dispTime_minutes=0;
    		   run_t.works_dispTime_hours++;
    		   if(run_t.works_dispTime_hours > 24){
    		        run_t.works_dispTime_hours =0;
    		   }
    	      }
           }
  
            Display_Timing(run_t.works_dispTime_hours,run_t.works_dispTime_minutes);
            Display_Works_Time_Fun();
            Timer_Timing_Donot_Display();
			break;

	   	}
}

//  	}
//    else{


//           if(run_t.gTimes_time_seconds > 59){
//    		   run_t.gTimes_time_seconds=0;
//    		 
//    		   run_t.works_dispTime_minutes++; //1 minute 
//    		
//    		   run_t.send_app_wokes_minutes_two++;
//    		   if(run_t.works_dispTime_minutes> 59){ //1 hour
//    		   run_t.works_dispTime_minutes=0;
//    		   run_t.works_dispTime_hours++;
//    		   if(run_t.works_dispTime_hours > 24){
//    		        run_t.works_dispTime_hours =0;
//    		   }
//    	      }
//           }
//  
//         Display_Timing(run_t.works_dispTime_hours,run_t.works_dispTime_minutes);
//         Timer_Timing_Donot_Display();

//  }
  






/****************************************************************
 * 
 * Function Name:
 * Function :function of pointer 
 * 
 * 
****************************************************************/
void Single_Add_RunCmd(void(*addHandler)(void))
{
    single_add_fun = addHandler;   

}

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void))
{
	single_buzzer_fun = buzzerHandler;

}
void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat))
{
    sendAi_usart_fun = sendaiHandler;

}

void SplitDispose_Key_RunCmd(void(*keyHandler)(uint8_t dat))
{

  dispose_key = keyHandler;

}

//void Smg_DisplayFan_Leve(void(*fandisplayHandler)(uint8_t fan_level))
//{
//   display_fan_speed_value = fandisplayHandler;

//}




