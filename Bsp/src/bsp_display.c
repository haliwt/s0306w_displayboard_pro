#include "bsp.h"




//static void TimeColon_Smg_Blink_Fun(void);


/**********************************************************************
*
*Functin Name: void Display_DHT11_Value(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Display_DHT11_Value(void)
{
    
  static uint8_t hum1,hum2; 
  static uint8_t temp1,temp2;

	hum1 =  run_t.gReal_humtemp[0]/10;  //Humidity 
	hum2 =  run_t.gReal_humtemp[0]%10;

	temp1 = run_t.gReal_humtemp[1] /10;//run_t.gReal_humtemp[1]/10 ;  // temperature
	temp2 = run_t.gReal_humtemp[1] % 10;//run_t.gReal_humtemp[1]%10;

 
	TM1639_Write_2bit_TempData(temp1,temp2);
    
	TM1639_Write_2bit_HumData(hum1,hum2);
	


}  


/**********************************************************************
*
*Functin Name: void Display_Timing(uint8_t hours,uint8_t minutes)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Display_Timing(uint8_t hours,uint8_t minutes)
{ 
    static uint8_t m,q;
	m = hours /10 ;
	run_t.hours_two_unit_bit =	hours%10; 
	run_t.minutes_one_decade_bit= minutes/10 ;
	q=  minutes%10;
	TM1639_Write_4Bit_Time(m,run_t.hours_two_unit_bit,run_t.minutes_one_decade_bit,q,0) ; //timer is default 12 hours "12:00"


}

/********************************************************************************
*
*Functin Name: void Display_Error_Digital(uint8_t errnumbers,uint8_t sel)
*Function : Timer of key be pressed handle
*Input Ref:  error digital 
*Return Ref: NO
*
********************************************************************************/
void Display_Error_Digital(uint8_t errnumbers,uint8_t sel)
{ 
    static uint8_t m,q;
	m = 0x0E;
	
	run_t.hours_two_unit_bit= 0x0d;
	
	run_t.minutes_one_decade_bit= errnumbers/10;
	q=errnumbers%10;
	TM1639_Write_4Bit_Time(m,run_t.hours_two_unit_bit,run_t.minutes_one_decade_bit,q,sel) ; //timer is default 12 hours "12:00"


}

/********************************************************************************
*
*Functin Name: static void TimeColon_Smg_Blink_Fun(void)
*Function : Timer of key be pressed handle
*Input Ref:  NO
*Return Ref: NO
*
********************************************************************************/
//static void TimeColon_Smg_Blink_Fun(void)
//{
//	//if(run_t.gTimer_colon < 1){ //2
//	static uint8_t i;

//     i++ ;
//     if(i==1)
//		  SmgBlink_Colon_Function(run_t.hours_two_unit_bit ,run_t.minutes_one_decade_bit,0);
//     else{
//          i=0;
//	
//		   SmgBlink_Colon_Function(run_t.hours_two_unit_bit ,run_t.minutes_one_decade_bit,1);
//        }

//	
//}

/********************************************************************************
	*
	*Functin Name: void Display_TimeColon_Blink_Fun(void)
	*Function : 
	*Input Ref:  NO
	*Return Ref: NO
	*
********************************************************************************/
void Display_TimeColon_Blink_Fun(void)
{

  if(run_t.gTimer_time_colon >0 && (gpro_t.set_timer_timing_doing_value==0 ||gpro_t.set_timer_timing_doing_value==3)){ //200 //10*20ms=300ms

	   run_t.gTimer_time_colon =0;
       
	 	  gpro_t.g_time_disp_colon_flag = gpro_t.g_time_disp_colon_flag ^ 0x01;
	
		  SmgBlink_Colon_Function(run_t.hours_two_unit_bit,run_t.minutes_one_decade_bit,gpro_t.g_time_disp_colon_flag);
     
	}
}


void Warning_Error_Numbers_Fun(void)
{

    static uint8_t alternate_flag,times;

   if(run_t.ptc_warning ==1 ||  run_t.fan_warning ==1){



       if(run_t.ptc_warning ==1 &&   run_t.fan_warning ==1)alternate_flag =1;
       else alternate_flag =0;


		if(run_t.gTimer_error_digital < 3){//10ms * 51= 510

		      
            if(alternate_flag ==0){
			   	  
                 if(run_t.ptc_warning ==1){
                 
					Display_Error_Digital(0x01,0);
			     }
				 else if(run_t.fan_warning ==1){

					  
                      Display_Error_Digital(0x02,0);
                     

			        }

				 
			  }
			  else if(alternate_flag ==1){

			      
				   if(run_t.ptc_warning ==1 && times == 0){ // && run_t.fan_warning ==1){
                       
                    

                        Display_Error_Digital(0x01,0);

				   	}
				    else  if(run_t.fan_warning ==1 && times > 0){
                      
					    Display_Error_Digital(0x02,0);
			        }
				


			   }
			   

		   }
		   else if(run_t.gTimer_error_digital > 3 && run_t.gTimer_error_digital  < 5 ){
 				//Display_Error_Digital(0x10,1);
                if(alternate_flag ==1){
                if(times > 0)times = 0;
                else times ++;

                }
                    

                
 				
		   }
		    else if(run_t.gTimer_error_digital > 5){

			  run_t.gTimer_error_digital=0;


			 }

		}



}


