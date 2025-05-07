/*
 * bsp_message.c
 *
 *  Created on: 2025年2月19日
 *      Author: Administrator
 */
#include "bsp.h"

static void rx_answer_data_form_mainboard(uint8_t *pdata);


/******************************************************************************
*
*Function Name:void send_cmd_ack_hanlder(void)
*Funcion: handle of tall process
*Input Ref:
*Return Ref:
*
******************************************************************************/
void send_cmd_ack_hanlder(void)
{

   switch(gpro_t.send_ack_cmd){

    case ack_null:


    break;

    case check_ack_power_on:


         
     
          if(gpro_t.receive_copy_cmd == 0x01){
             gpro_t.receive_copy_cmd =0;
             gpro_t.send_ack_cmd = 0;

          }
          else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
             gpro_t.gTimer_again_send_power_on_off =0;
             SendData_PowerOnOff(1);
          }

        

    case check_ack_power_off:

         if(gpro_t.receive_copy_cmd == ack_ok_off){
             gpro_t.receive_copy_cmd =0;
             gpro_t.send_ack_cmd = 0;

          }
          else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
               gpro_t.gTimer_again_send_power_on_off =0;
               SendData_PowerOnOff(0);
           }
             
      

    break;

    case check_ack_ptc_on:

//       if(gpro_t.receive_copy_cmd == ack_ok_on){
//			gpro_t.receive_copy_cmd =0;
//			 gpro_t.send_ack_cmd = 0;
//
//    	}
//    	else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
//			  gpro_t.gTimer_again_send_power_on_off =0;
//			  SendData_Set_Command(dry_cmd,0x01); // link wifi of command .
//    	}


     break;

    case check_ack_ptc_off:

//       if(gpro_t.receive_copy_cmd == 2){
//    	   gpro_t.receive_copy_cmd =0;
//    	   gpro_t.send_ack_cmd = 0;
//
//    	}
//    	else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
//    		gpro_t.gTimer_again_send_power_on_off =0;
//    		SendData_Set_Command(dry_cmd,0x0); // link wifi of command .
//    	}


     break;
     

    case check_ack_plasma_on:



        if(gpro_t.receive_copy_cmd == 0x01){
    			gpro_t.receive_copy_cmd =0;
    			 gpro_t.send_ack_cmd = 0;
        }
        else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
    			  gpro_t.gTimer_again_send_power_on_off =0;
    			  SendData_Set_Command(plasma_cmd,0x01); // link wifi of command .
        }
        break;

    case check_ack_plasma_off:

        if(gpro_t.receive_copy_cmd == 2){
    			gpro_t.receive_copy_cmd =0;
    			 gpro_t.send_ack_cmd = 0;
        }
        else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
    			  gpro_t.gTimer_again_send_power_on_off =0;
    			  SendData_Set_Command(plasma_cmd,0x0); // link wifi of command .
       

     }
    break;

    case check_ack_mouse_on:

            if(gpro_t.receive_copy_cmd == 1){
        			gpro_t.receive_copy_cmd =0;
        			 gpro_t.send_ack_cmd = 0;
            }
            else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
        			  gpro_t.gTimer_again_send_power_on_off =0;
        			  SendData_Set_Command(mouse_cmd,0x01); // link wifi of command .
            }
     break;

    case check_ack_mouse_off:
            if(gpro_t.receive_copy_cmd == 2){
        			gpro_t.receive_copy_cmd =0;
        			 gpro_t.send_ack_cmd = 0;
            }
            else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
        			  gpro_t.gTimer_again_send_power_on_off =0;
        			  SendData_Set_Command(mouse_cmd,0x0); // link wifi of command .        
            }
    break;
  
    case check_ack_ai_on: 
        

            if(gpro_t.receive_copy_cmd == 1){
        			gpro_t.receive_copy_cmd =0;
        			 gpro_t.send_ack_cmd = 0;        
            }
            else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
        			  gpro_t.gTimer_again_send_power_on_off =0;
        			  SendData_Set_Command(ai_cmd,0x01); // link wifi of command .
            }
   break;

   case check_ack_ai_off:
                if(gpro_t.receive_copy_cmd ==2){
            			gpro_t.receive_copy_cmd =0;
            			 gpro_t.send_ack_cmd = 0;   
                }
                else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
            			  gpro_t.gTimer_again_send_power_on_off =0;
            			  SendData_Set_Command(ai_cmd,0x0); // link wifi of command .
                }
     break;
           
    case check_ack_dry_notice_on:
     
//                if(gpro_t.receive_copy_cmd == 1){
//            			gpro_t.receive_copy_cmd =0;
//            			 gpro_t.send_ack_cmd = 0;   
//                }
//                else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
//            			  gpro_t.gTimer_again_send_power_on_off =0;
//            			  SendData_Set_Command(dry_notice_cmd,0x01); // link wifi of command .
//                }
      break;

      case check_ack_dry_notice_off:
//                if(gpro_t.receive_copy_cmd == 2){
//            			gpro_t.receive_copy_cmd =0;
//            			 gpro_t.send_ack_cmd = 0;   
//                }
//                else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
//            			  gpro_t.gTimer_again_send_power_on_off =0;
//            			  SendData_Set_Command(dry_notice_cmd,0x0); // link wifi of command .
//                }
          
    break;

    


    case check_ack_buzzer:

        if(gpro_t.receive_copy_cmd == 1){
            gpro_t.receive_copy_cmd =0;
            gpro_t.send_ack_cmd = 0;

        }
        else if(gpro_t.receive_copy_cmd != 0 && gpro_t.gTimer_again_send_power_on_off >1){
            gpro_t.gTimer_again_send_power_on_off =0;
            SendData_Set_Command(ack_with_buzzer,0x01); //buzzer sound command .

        }

    break;



  }

}
/******************************************************************************
*
*Function Name:void receive_data_from_mainboard(uint8_t *pdata,uint8_t len)
*Funcion: handle of tall process
*Input Ref:
*Return Ref:
*
******************************************************************************/
void receive_data_from_mainboard(uint8_t *pdata)
{
    

    switch(pdata[2]){

     case 0:


     break;

     case  power_cmd:
           if(pdata[3] == 0x00){ //power on

            if(pdata[4]== 0x01){
			run_t.gPower_On = power_on;
            run_t.gRunCommand_label =RUN_NULL;
            //gpro_t.receive_copy_cmd = 1;
            power_on_handler();
            
           }
           else{ //power off

            run_t.gPower_On = power_off;
            run_t.gRunCommand_label =RUN_NULL;
            //gpro_t.receive_copy_cmd = 2;
           // power_off_handler();
           
           }
          }

     break;

     case dry_cmd: //PTC打开关闭指令
       
     if(pdata[3] == 0x00){

	   if(pdata[4]== 0x01){

            run_t.gDry =1 ;//&& run_t.gPlasma ==1  && run_t.gUltransonic==1
            gpro_t.g_manual_shutoff_dry_flag = 0;
        }
        else if(pdata[4] == 0x0){

            gpro_t.g_manual_shutoff_dry_flag = 0;
            run_t.gDry =0;
          

        }
    	}
     break;

     case plasma_cmd: //PLASMA 打开关闭指令

		if(pdata[3] == 0x00){
		
			if(pdata[4]== 0x01){
	          
	        run_t.gPlasma =1;


	        }
	        else if(pdata[4] == 0x0){
	          
	         run_t.gPlasma =0;

	        }
		}

     break;


      case mouse_cmd: //ultrasonic  打开关闭指令

        
	   if(pdata[3] == 0x00){
		   
		   if(pdata[4]== 0x01){
	           
	           run_t.gMouse = 1;

	        }
	        else { //close
	         run_t.gMouse = 0;
	        }

		}


     break;

	 case wifi_cmd:


	if(pdata[3] == 0x00){

		if(pdata[4]== 0x01){

		run_t.wifi_led_fast_blink=1;
		run_t.wifi_connect_state_flag = wifi_connect_null;
		run_t.gTimer_wifi_connect_counter =0; //120s counte start

		}
		else if(pdata[4] == 0x0){ //close

		}


	}


	 break;




      case temp_warning: //temperature of high warning.

		if(pdata[3] == 0x00){
			
			if(pdata[4]== 0x01){

	            run_t.ptc_warning = 1;
	            //run_t.setup_timer_timing_item =  PTC_WARNING; //ptc warning
	           

	            run_t.gDry =0;
	            SendData_Set_Command(0x22,0x0); //close ptc ,but don't buzzer sound .

	        }
	        else if(pdata[4] == 0x0){ //close

	           run_t.ptc_warning = 0;


	        }

	    }

      break;

      case 0x09: //fan of default of warning.

         if(pdata[3] == 0x01){  //warning

            run_t.fan_warning = 1;

           run_t.gDry =0;
           SendData_Set_Command(0x22,0x0); //0x22:PTC notice close .

        }
        else if(pdata[3] == 0x0){ //close

           run_t.fan_warning = 0;


        }


      break;

	


     //接收的是数据

      case temp_hum_data: //温度,湿度数据
        if(pdata[3]==0x0F){
        if(pdata[4] == 0x02){ //数据,two 
            
            run_t.gReal_humtemp[0] = pdata[5] ;//gpro_t.humidity_real_value = pdata[5];
           
             run_t.gReal_humtemp[1] = pdata[6];

        }
        else if(pdata[4] == 0x01){ //数据,one



        }
        }
      break;

      case 0x1B: //湿度数据

        if(pdata[2] == 0x0F){ //数据


        }
      break;

      case beijing_times_data: //表示时间：小时，分，秒

        if(pdata[4] == 0x03){ //数据,has three data

            if(pdata[5] < 24){ //WT.EDIT 2024.11.23

            run_t.display_beijing_time_flag= 1;
          
          run_t.works_dispTime_hours= pdata[5];// run_t.dispTime_hours  =  pdata[5];
          run_t.works_dispTime_minutes =pdata[6];//run_t.dispTime_minutes = pdata[6];
          run_t.gTimes_time_seconds =  pdata[7];//run_t.gTimer_disp_time_seconds =  pdata[7];
           }


        }
      break;

	  case wifi_connect_data: //notice is command
	  	
        if(pdata[3]==0x00){ // 0xF is explain is data don't command.
	    if(pdata[4] == 0x01){   //only 
	  
           
			 run_t.wifi_connect_state_flag = wifi_connect_success;
	         run_t.wifi_led_fast_blink=0;
			  
	  
			}
			else{ //close
	  
			   run_t.wifi_connect_state_flag = wifi_connect_null;
	            run_t.wifi_led_fast_blink=0;
			    run_t.display_beijing_time_flag =0;
	  
			}
	    }
  
	  break;


	  case timer_time_sync:

	      

          

	  break;

	  case 0x22: //Command ,set temperature compare dht11 result open or close

	    if(pdata[3] == 0x01){ //command

            

        }
		else if(pdata[3] == 0x01){ //


		}

	  break;

	  

        case 0x1D: //表示日期： 年，月，日

        if(pdata[2] == 0x0F){ //数据



        }
      break;

	  case 0x2A: //main board set temperature value 
	  
          
		  if(pdata[3] == 0x0F){
		  
			if(pdata[4]== 0x01){ // one only data 

		  
				
			gpro_t.set_up_temperature_value =pdata[5];//warning
	  
			 gpro_t.g_manual_shutoff_dry_flag = 0 ;//  allow open dry function
             gpro_t.set_temp_value_success=1;//
             //run_t.set_temperature_special_flag=1;
             run_t.gTimer_key_temp_timing=0;

			   run_t.set_temperature_decade_value = gpro_t.set_up_temperature_value / 10 ;
               run_t.set_temperature_unit_value  =gpro_t.set_up_temperature_value % 10; //

              // TM1639_Write_2bit_SetUp_TempData(run_t.set_temperature_decade_value,run_t.set_temperature_unit_value,0);
				
	  
			 

				}
		  	}
	break;

	case mainboard_set_timer_value:

	     if(pdata[3] == 0x0F){
		  
			if(pdata[4]== 0x01){ // one only data 

		      gpro_t.set_timer_timing_doing_value = 1;
			  run_t.gTimer_key_timing = 0;
              run_t.gTimer_smg_blink_times =0;
			  gpro_t.set_timer_first_smg_blink_flag=0;
				
			 run_t.temporary_timer_dispTime_hours=pdata[5];
	  
			 	 run_t.hours_two_decade_bit    = run_t.temporary_timer_dispTime_hours / 10;
    			run_t.hours_two_unit_bit      = run_t.temporary_timer_dispTime_hours % 10;
   				 run_t.minutes_one_decade_bit  = 0;
    			run_t.minutes_one_unit_bit    = 0;
				
	  
			 

				}
		  	}

	break;

     case copy_cmd: // copy send cmd acknowlege
          rx_answer_data_form_mainboard(pdata);

     break;

     }

 }


static void rx_answer_data_form_mainboard(uint8_t *pdata)
{
    
    switch(pdata[3]){

    case CMD_POWER : //power_on 
    if(pdata[4]==0x00){ // is command don't data.

	 if(pdata[5]==0x01){
	 	run_t.gPower_On = power_on;
        power_on_handler();
        

     }
     else{ //power offf

        run_t.gPower_On = power_off;
        run_t.power_off_flag=0;
       

     }
    }
    break;

    case ack_ptc:

    if(pdata[5]==1){

        gpro_t.receive_copy_cmd = 1;
    }
    else{
      gpro_t.receive_copy_cmd = 2;

    }



    break;

    case ack_plasma:

    if(pdata[5]==1){

        gpro_t.receive_copy_cmd = 1;
    }
    else{
      gpro_t.receive_copy_cmd = 2;

    }
    break;

    case ack_ai:

    if(pdata[5]==1){

        gpro_t.receive_copy_cmd = 1;
    }
    else{
      gpro_t.receive_copy_cmd = 2;

    }

    break;

    case ack_wifi: // link wifi command

      if(pdata[4]==0){ //0-command ,0x0f-data

	  if(pdata[5] == 0x01){  // link wifi



      }
      else if(pdata[3] == 0x0){ //don't link wifi




      }
      }

   break;


    
    
    case ack_with_buzzer:
        if(pdata[4] == 1){  //buzzer answer command

           

        }
        else{
         


        }
     break;
    }


}


/******************************************************************************
*
*Function Name:uint8_t bcc_check(const unsigned char *data, int len)
*Funcion: BCC check code
*Input Ref: data:input data, len: data of length
*Return Ref:
*
******************************************************************************/
uint8_t bcc_check(const unsigned char *data, int len)
{
    unsigned char bcc = 0;
    for (int i = 0; i < len; i++) {
        bcc ^= data[i];
    }
    return bcc;
}



