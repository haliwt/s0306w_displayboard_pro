#include "bsp.h"


#define DOUBLEDOT       0x80// seg_h

#define POWER_KEYLED    (seg_g + seg_h)

#define POWERLED        (seg_g+ seg_h)
#define MODELED         (seg_c+seg_d+seg_e+seg_f+seg_g+seg_h)

#define TEMPLED         (seg_f+ seg_g +seg_h)  //temperature and humidity 
#define FANLED          (seg_g + seg_h)
#define STERLED         (seg_g + seg_h)
#define DRYLED          (seg_g + seg_h)
#define AILED           (seg_g + seg_h)

#define TIMESLED        (seg_f)
#define TIMESLED_OFF    (seg_g+seg_h)

#define HOUR_LOW          (seg_b + seg_c )  //"H"
#define HOUR_HIGH         (seg_e+seg_f +seg_g)

#define T_Symbol_Low       (seg_a+seg_b+seg_c)  //'T'
#define T_Symbol_High      (0)

#define E_Symbol_Low     	 (seg_a+seg_d)  //'E'
#define E_Symbol_High    	 (seg_e+seg_f+seg_g)

#define OFFLED           0

#define SYMBOL_A       0x01

uint8_t led_on_flag;
uint8_t led_off_flag;
uint8_t breath_flag=0;
uint16_t Mode =0;
#if 0
const unsigned char segNumber[]={
	
     
		 seg_a+seg_b+seg_c+seg_d+seg_e+seg_f,        		// char "0"  0x00
		 seg_b+seg_c,                           			// char "1"  0x01
		 seg_a+seg_b+seg_d+seg_e+seg_g,              		// char "2"  0x02
		 seg_a+seg_b+seg_c+seg_d+seg_g,               		// char "3"  0x03
		 seg_b+seg_c+seg_f+seg_g,                   	    // char "4"  0x04
		 seg_a+seg_c+seg_d+seg_f+seg_g,              		// char "5"  0x05
		 seg_a+seg_c+seg_d+seg_e+seg_f+seg_g,              	// char "6"  0x06
		 seg_a+seg_b+seg_c+seg_f,                    		// char "7"  0x07
		 seg_a+seg_b+seg_c+seg_d+seg_e+seg_f+seg_g,  		// char "8"  0x08
		 seg_a+seg_b+seg_c+seg_d+seg_f+seg_g,        		// char "9"  0x09
		 seg_a+seg_b+seg_c+seg_e+seg_f+seg_g,               // char "A"  0x0A
		 seg_c+seg_d+seg_e+seg_f+seg_g,                     // char "b"  0x0B
		 seg_a+seg_d+seg_e+seg_f,							// char "C"  0X0C
		 seg_b+seg_c+seg_d+seg_e+seg_g,						// char "d"  0x0D
		 seg_a+seg_d+seg_e+seg_f+seg_g,                     // char "E"  0X0E
		 seg_a+seg_e+seg_f+seg_g,                           // char "F"  0X0F
         0                                      			// char "NLL"  0x16
                                               
                                             
};
#endif 
const unsigned char segNumber_Low[]={
 
         seg_a+seg_b+seg_c+seg_d,        		// char "0"  0x00
		 seg_b+seg_c,                           // char "1"  0x01
		 seg_a+seg_b+seg_d,              		// char "2"  0x02
		 seg_a+seg_b+seg_c+seg_d,               // char "3"  0x03
		 seg_b+seg_c,                   	    // char "4"  0x04
		 seg_a+seg_c+seg_d,              		// char "5"  0x05
		 seg_a+seg_c+seg_d,              	    // char "6"  0x06
		 seg_a+seg_b+seg_c,                    	// char "7"  0x07
		 seg_a+seg_b+seg_c+seg_d,  		        // char "8"  0x08
		 seg_a+seg_b+seg_c+seg_d,        		// char "9"  0x09
		 seg_a+seg_b+seg_c,                     // char "A"  0x0A
		 seg_c+seg_d,                           // char "b"  0x0B
		 seg_d,									// char "c"  0X0C
		 0,										// char "r"  0x0D
		 seg_a+seg_d,                           // char "E"  0X0E
		 seg_a,                                 // char "F"  0X0F
         0                                      // char "NLL"  0x10
         
};

const unsigned char segNumber_High[]={
         seg_e+seg_f,        		     // char "0"  0x00
		 0,//seg_b+seg_c,                // char "1"  0x01
		 seg_e+seg_g,              		 // char "2"  0x02
		 seg_g,                    		// char "3"  0x03
		 seg_f+seg_g,                    // char "4"  0x04
		 seg_f+seg_g,              		 // char "5"  0x05
		 seg_e+seg_f+seg_g,              // char "6"  0x06
		 0,                    		 	// char "7"  0x07
		 seg_e+seg_f+seg_g,  		     // char "8"  0x08
		 seg_f+seg_g,        		     // char "9"  0x09
		 seg_e+seg_f+seg_g,              // char "A"  0x0A
		 seg_e+seg_f+seg_g,              // char "b"  0x0B
		 seg_e+seg_f,					 // char "c"  0X0C
		 seg_e+seg_g,					 // char "r"  0x0D
		 seg_e+seg_f+seg_g,              // char "E"  0X0E
		 seg_e+seg_f+seg_g,              // char "F"  0X0F
         0                               // char "NLL"  0x16

};

const unsigned char segNumber_Low_4bit[]={
 
         seg_a+seg_b+seg_c+seg_d,        		// char "0"  0x00
		 seg_b+seg_c,                           // char "1"  0x01
		 seg_a+seg_b+seg_d,              		// char "2"  0x02
		 seg_a+seg_b+seg_c+seg_d,               // char "3"  0x03
		 seg_b+seg_c,                   	    // char "4"  0x04
		 seg_a+seg_c+seg_d,              		// char "5"  0x05
		 seg_a+seg_c+seg_d,              	    // char "6"  0x06
		 seg_a+seg_b+seg_c,                    	// char "7"  0x07
		 seg_a+seg_b+seg_c+seg_d,  		        // char "8"  0x08
		 seg_a+seg_b+seg_c+seg_d,        		// char "9"  0x09
		 seg_a+seg_b+seg_c,                     // char "A"  0x0A
		 seg_c+seg_d,                           // char "b"  0x0B
		 seg_d,									// char "c"  0X0C
		 0,										// char "r"  0x0D
		 seg_a+seg_d,                           // char "E"  0X0E
		 seg_a,                                 // char "F"  0X0F
         0                                      // char "NLL"  0x10
         
};

const unsigned char segNumber_High_4bit[]={
         seg_e+seg_f,        		     // char "0"  0x00
		 0,//seg_b+seg_c,                // char "1"  0x01
		 seg_e+seg_g,              		 // char "2"  0x02
		 seg_g,                    		// char "3"  0x03
		 seg_f+seg_g,                    // char "4"  0x04
		 seg_f+seg_g,              		 // char "5"  0x05
		 seg_e+seg_f+seg_g,              // char "6"  0x06
		 0,                    		 	// char "7"  0x07
		 seg_e+seg_f+seg_g,  		     // char "8"  0x08
		 seg_f+seg_g,        		     // char "9"  0x09
		 seg_e+seg_f+seg_g,              // char "A"  0x0A
		 seg_e+seg_f+seg_g,              // char "b"  0x0B
		 seg_e+seg_f,					 // char "c"  0X0C
		 seg_e+seg_g,					 // char "r"  0x0D
		 seg_e+seg_f+seg_g,              // char "E"  0X0E
		 seg_e+seg_f+seg_g,              // char "F"  0X0F
         0                               // char "NLL"  0x16

};



static void TM1639_Start(void);
static void TM1639_Stop(void);
static void TM1639_Write_OneByte(uint8_t data);
void Bdelay_us(uint16_t t);

//static void Send_Command(uint8_t com);
//static void Delay_I2C(uint8_t t);


//static void Delay_I2C(uint8_t t)
//{
//  uint16_t j;
//	for(j=0;j<t;j++)
//	{
//       for(int i = 0; i <50; i++)//better for(int i = 0; i < 40; i++)    //for(int i = 0; i < 20; i++)    
//        {
//            __asm("NOP");//等待1个指令周期，系统主频24M
//           
//        }
//	}
//}


/*****************************************************
 * 
 * Function Name: static void TM1639_Start(void)
 * 
 * 
******************************************************/
static void TM1639_Start(void)
{
  TM1639_STB_SetLow();
	
}
static void TM1639_Stop(void)
{
   TM1639_STB_SetHigh();

}

static void TM1639_Write_OneByte(uint8_t data)
{
	uint8_t i; 
	
	for(i=0;i<8;i++){
		
	TM1639_CLK_SetLow();
	 if(data & 0x01){
	     TM1639_DIO_SetHigh();
		   //HAL_Delay(5); //5ms
	 }
	 else{
	     TM1639_DIO_SetLow();
		  // HAL_Delay(5); //5ms
	 
	 }
	
    //Delay_I2C(150); // 这个延时式，显示4为，时间，像数码管流水灯式的显示。
	 
	 TM1639_CLK_SetHigh();
	 data >>=1;//
	
   //  data = data >> 1;   //LSB is the first send 
    // TM1639_CLK_SetHigh();
     
   }
// HAL_Delay(2);
// TM1639_CLK_SetLow();
// TM1639_DIO_SetLow();
}


/*******************************************************************************************************
    *
    *Function Name:void TM1640_Write_4Bit_Data(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit)
    *Function :Smg display times hour minute
    *Input Ref: onebit ,twobit hours ,threebit fourbit minute,sl -select "H" or "numbers"
    *Return Ref: NO
    *
********************************************************************************************************/
void TM1639_Write_4Bit_Time(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit,uint8_t sl)
{

	
	 TM1639_STB_SetLow();
	 TM1639_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1639_STB_SetHigh();
    
    TM1639_STB_SetLow();
     TM1639_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1639_STB_SetHigh();
    // ai_ico_fast_blink();
	 
    //digital 1
     TM1639_Start();
     TM1639_Write_OneByte(0xC8);//0xC0H->GRID_1->BIT_1
    if(sl ==0)
         TM1639_Write_OneByte(segNumber_Low_4bit[onebit]);//display "10"
     else{
	 	   
            TM1639_Write_OneByte(segNumber_Low_4bit[0x10]);//display "10"
	 	  
	 }
     TM1639_Stop();
    // ai_ico_fast_blink();

	 TM1639_Start();
     TM1639_Write_OneByte(0XC9);//0xC1H->GRID_1->BIT_1
     if(sl ==0){
         TM1639_Write_OneByte(segNumber_High_4bit[onebit]);//display "01"
     }
     else {
	 	     TM1639_Write_OneByte(segNumber_High_4bit[0x10]);//display "10"
     }
     TM1639_Stop();
    
     // ai_ico_fast_blink();
     //dighital 2
   
     TM1639_Start();
     TM1639_Write_OneByte(0xCA);//0xC1H->GRID_2->BIT_2
     if(sl==0){
         TM1639_Write_OneByte(segNumber_Low_4bit[twobit]);//display "2 :"
     }
     else {
	 	  
     	  TM1639_Write_OneByte(segNumber_Low_4bit[0x10]);
     }
     TM1639_Stop();
  

	TM1639_Start();

    TM1639_Write_OneByte(0xCB);//0xC1H->GRID_2->BIT_2
     if(gpro_t.g_time_disp_colon_flag==1){
         TM1639_Write_OneByte(segNumber_High_4bit[twobit]|seg_h);//WT.EDIT 2025.03.10
   
     }
     else {
      
        TM1639_Write_OneByte(segNumber_High_4bit[twobit]); //WT.EDIT 2025.03.10
	 }
	 
    TM1639_Stop();
	 
 
     //digital 3 
     //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCC);//0xC2H->GRID_3->BIT_3
    if(sl==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_Low_4bit[threebit]);//display ""

    }
    else{
        TM1639_Write_OneByte(segNumber_Low_4bit[0x10]);
     }
    TM1639_Stop();
  
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCD);//0xC2H->GRID_3->BIT_3
    if(gpro_t.g_time_disp_colon_flag==1){
	    TM1639_Write_OneByte(segNumber_High_4bit[threebit]|seg_h);//display ""

	}//TM1639_Write_OneByte(OFFLED);//display "NULL"
    else TM1639_Write_OneByte(segNumber_High_4bit[threebit]); //WT.EDIT 2025.03.10
	
    TM1639_Stop();
	
   
    //digital 4
	//minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCE);//0xC2H->GRID_4
    if(sl==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_Low_4bit[fourbit]);//display ""

    }
    else TM1639_Write_OneByte(segNumber_Low_4bit[0x10]);
    TM1639_Stop();
  
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCF);//0xC2H->GRID_4
    if(sl==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_High_4bit[fourbit]);//display ""

    }
    else TM1639_Write_OneByte(segNumber_High_4bit[0x10]);
    TM1639_Stop();
     //open diplay
    TM1639_Start();
    TM1639_Write_OneByte(OpenDispTM1639|0x8f);//0xC2H->GRID3->BIT_3
    TM1639_Stop();
 
    
}
/*******************************************************************************************************
    *
    *Function Name:void TM1640_Write_4Bit_Data(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit)
    *Function :Smg display fan of speed "F1 01 or F2 02"
    *Input Ref: fan_level is fan speed 1 or fan speed 2 
    *Return Ref: NO
    *
********************************************************************************************************/
void TM1639_Write_4Bit_Time_sync_close(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit,uint8_t sl)
{

    TM1639_STB_SetLow();
	 TM1639_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1639_STB_SetHigh();
    
    TM1639_STB_SetLow();
     TM1639_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1639_STB_SetHigh();
    // ai_ico_fast_blink();



//digital 1
     TM1639_Start();
     TM1639_Write_OneByte(0xC8);//0xC0H->GRID_1->BIT_1
    if(sl ==0)
         TM1639_Write_OneByte(segNumber_Low_4bit[onebit]);//display "10"
     else{
	 	   
            TM1639_Write_OneByte(0x00);//display "10"
	 	  
	 }
     TM1639_Stop();
    // ai_ico_fast_blink();

	 TM1639_Start();
     TM1639_Write_OneByte(0XC9);//0xC1H->GRID_1->BIT_1
     if(sl ==0){
         TM1639_Write_OneByte(segNumber_High_4bit[onebit]);//display "01"
     }
     else {
	 	     TM1639_Write_OneByte(0x00);//display "10"
     }
     TM1639_Stop();
    
    //  ai_ico_fast_blink();
     //dighital 2
   
     TM1639_Start();
     TM1639_Write_OneByte(0xCA);//0xC1H->GRID_2->BIT_2
     if(sl==0){
         TM1639_Write_OneByte(segNumber_Low_4bit[twobit]);//display "2 :"
     }
     else {
	 	  
     	  TM1639_Write_OneByte(0x00);
     }
     TM1639_Stop();


	TM1639_Start();

    TM1639_Write_OneByte(0xCB);//0xC1H->GRID_2->BIT_2
     if(sl==0){
         TM1639_Write_OneByte(segNumber_High_4bit[twobit]|seg_h);//display "2 :"
   
     }
     else {
      
        TM1639_Write_OneByte(0x00);
	 }
	 
    TM1639_Stop();
	 
  
     //digital 3 
     //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCC);//0xC2H->GRID_3->BIT_3
    if(sl==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_Low_4bit[threebit]);//display ""

    }
    else{
        TM1639_Write_OneByte(0x00);
     }
    TM1639_Stop();
   
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCD);//0xC2H->GRID_3->BIT_3
    if(sl==0){
	    TM1639_Write_OneByte(segNumber_High_4bit[threebit]|seg_h);//display ""

	}//TM1639_Write_OneByte(OFFLED);//display "NULL"
    else TM1639_Write_OneByte(0x00);
	
    TM1639_Stop();
	
  
    //digital 4
	//minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCE);//0xC2H->GRID_4
    if(sl==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_Low_4bit[fourbit]);//display ""

    }
    else TM1639_Write_OneByte(0x00);
    TM1639_Stop();
    
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCF);//0xC2H->GRID_4
    if(sl==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_High_4bit[fourbit]|seg_h);//display ""

    }
    else TM1639_Write_OneByte(0x00);
    TM1639_Stop();

    //open diplay
    TM1639_Start();
    TM1639_Write_OneByte(OpenDispTM1639|0x8f);//0xC2H->GRID3->BIT_3
    TM1639_Stop();
  


}

/*******************************************************************************************************
    *
    *Function Name:void TM1640_Write_4Bit_Data(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit)
    *Function :Smg display fan of speed "F1 01 or F2 02"
    *Input Ref: fan_level is fan speed 1 or fan speed 2 
    *Return Ref: NO
    *
********************************************************************************************************/
#if 0
void TM1639_Write_4Bit_Fan_Level(uint8_t fan_level)
{

	
	 TM1639_STB_SetLow();
	 TM1639_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1639_STB_SetHigh();
    
    TM1639_STB_SetLow();
     TM1639_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1639_STB_SetHigh();

	 
    //digital 1
     TM1639_Start();
     TM1639_Write_OneByte(0xC8);//0xC0H->GRID_1->BIT_1
  
      TM1639_Write_OneByte(segNumber_Low[0x0f]);//display "F"

     TM1639_Stop();

	 TM1639_Start();
     TM1639_Write_OneByte(0XC9);//0xC1H->GRID_1->BIT_1
    
     TM1639_Write_OneByte(segNumber_High[0x0f]);//display "F"
  
     TM1639_Stop();
    
      
     //dighital 2
   
     TM1639_Start();
     TM1639_Write_OneByte(0xCA);//0xC1H->GRID_2->BIT_2
     if(fan_level==0){ //fan_speed_max
         TM1639_Write_OneByte(segNumber_Low[0x02]);//display "2 :"
     }
     else {
	 	TM1639_Write_OneByte(segNumber_Low[0x01]);//display "1 :" _>fan_speed_min,
     }
     TM1639_Stop();
   

	TM1639_Start();

    TM1639_Write_OneByte(0xCB);//0xC1H->GRID_2->BIT_2
     if(fan_level==0){
         TM1639_Write_OneByte(segNumber_High[0x02]|seg_h);//display "2 :"
   
     }
     else {
      
       TM1639_Write_OneByte(segNumber_High[0x01]|seg_h);//display "1 :" _>fan_speed_min,
	 }
	 
    TM1639_Stop();
	 
   
     //digital 3 
     //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCC);//0xC2H->GRID_3->BIT_3
  
	TM1639_Write_OneByte(segNumber_Low[0]);//display "0"

    TM1639_Stop();
    
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCD);//0xC2H->GRID_3->BIT_3
   
	TM1639_Write_OneByte(segNumber_High[0]|seg_h);//display "0"
	
    TM1639_Stop();
	
    //digital 4
	//minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCE);//0xC2H->GRID_4
    if(fan_level==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_Low[0x02]);//display "2"

    }
    else{
        TM1639_Write_OneByte(segNumber_Low[0x01]);//display "1"
     }
    TM1639_Stop();
    
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCF);//0xC2H->GRID_4
    if(fan_level==0){//TM1639_Write_OneByte(OFFLED);//display "NULL"
	    TM1639_Write_OneByte(segNumber_High[0x02]|seg_h);//display "2"

    }
    else{
        TM1639_Write_OneByte(segNumber_High[0x01]|seg_h);//display "1"
     }
    TM1639_Stop();

    //open diplay
    TM1639_Start();
    TM1639_Write_OneByte(OpenDispTM1639|0x8f);//0xC2H->GRID3->BIT_3
    TM1639_Stop();
    
}
#endif 
/*************************************************************************
*
*Function Name:void SmgBlink_Colon_Function(uint8_t twobit,uint8_t threebit,uint8_t sel)
*Function :display smg of colon ":" blink 
*Input Ref:
*
*
*************************************************************************/
void SmgBlink_Colon_Function(uint8_t twobit,uint8_t threebit,uint8_t sel)
{


   


	TM1639_Start();

    TM1639_Write_OneByte(0xCB);//0xC1H->GRID_2->BIT_2
  
     if(sel==0){

        TM1639_Write_OneByte(segNumber_High[twobit]|seg_h); 
      }
	  else {

	      TM1639_Write_OneByte(segNumber_High[twobit]);	 
     }

	 
    TM1639_Stop();


	   //minute 
    TM1639_Start();
    TM1639_Write_OneByte(0xCD);//0xC2H->GRID_3->BIT_3
    if(sel==0){
	    TM1639_Write_OneByte(segNumber_High[threebit]|seg_h);//display ""

	}//TM1639_Write_OneByte(OFFLED);//display "NULL"
    else TM1639_Write_OneByte(segNumber_High[threebit]);
	
    TM1639_Stop();


   
    


}

/*******************************************************************************************************
    *
*Function Name:void TM1639rite_2bit_HumData(uint8_t onebit,uint8_t twobit)
*Function :Smg display humidity of value digital 3 ->digital 4 ->dp4 %
*Input Ref: onebit,twobit  value
*Return Ref: NO
    *
********************************************************************************************************/
void TM1639_Write_2bit_HumData(uint8_t onebit,uint8_t twobit)
{


     TM1639_STB_SetLow();
	 TM1639_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1639_STB_SetHigh();
    
    TM1639_STB_SetLow();
     TM1639_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1639_STB_SetHigh();


//digital 3 
     //minute 
    TM1639_Start();
    TM1639_Write_OneByte(AddrC4H);//0xC2H->GRID_3->BIT_3
     TM1639_Write_OneByte(segNumber_Low[onebit]);//display ""
     TM1639_Stop();
    
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(AddrC5H);//0xC2H->GRID_3->BIT_3
  
	 TM1639_Write_OneByte(segNumber_High[onebit]);//display ""

	
    TM1639_Stop();
	
    //digital 4
	//minute 
    TM1639_Start();
    TM1639_Write_OneByte(AddrC6H);//0xC2H->GRID_4
   
	TM1639_Write_OneByte(segNumber_Low[twobit]);//display ""
    TM1639_Stop();
    
    //minute 
    TM1639_Start();
    TM1639_Write_OneByte(AddrC7H);//0xC2H->GRID_4

	TM1639_Write_OneByte(segNumber_High[twobit]|seg_h);//display ""

   

    TM1639_Stop();

	


    //open diplay
    TM1639_Start();
    TM1639_Write_OneByte(OpenDispTM1639|0x8f);//0xC2H->GRID3->BIT_3
    TM1639_Stop();

}
     
	
    

/*******************************************************************************************************
    *
*Function Name:void TM1640_Write_2bit_TempData(uint8_t onebit,uint8_t twobit)
*Function :Smg display temprature of value GRID1,GRID2->DP2
*Input Ref: onebit,twobit  value
*Return Ref: NO
    *
********************************************************************************************************/
void TM1639_Write_2bit_TempData(uint8_t onebit,uint8_t twobit)
{
	 TM1639_STB_SetLow();
	 TM1639_Write_OneByte(0X40);//To Address of fixed reg 0x44
	 TM1639_STB_SetHigh();
    
    TM1639_STB_SetLow();
     TM1639_Write_OneByte(0X44);//To Address of fixed reg 0x44
     TM1639_STB_SetHigh();

	 
    //digital 1
     TM1639_Start();
     TM1639_Write_OneByte(0xC0);//0xC0H->GRID_1->BIT_1

     TM1639_Write_OneByte(segNumber_Low[onebit]);//display "10"
   
     TM1639_Stop();

	 TM1639_Start();
     TM1639_Write_OneByte(0XC1);//0xC1H->GRID_1->BIT_1
  
      TM1639_Write_OneByte(segNumber_High[onebit]);//display "01"
    
     TM1639_Stop();
    
      
     //dighital 2
   
     TM1639_Start();
     TM1639_Write_OneByte(AddrC2H);//0xC1H->GRID_2->BIT_2
    
     TM1639_Write_OneByte(segNumber_Low[twobit]);//display "2 :"
     
     TM1639_Stop();
   

	TM1639_Start();

     TM1639_Write_OneByte(AddrC3H);//0xC1H->GRID_2->BIT_2
   
     TM1639_Write_OneByte(segNumber_High[twobit]|seg_h);//TM1639_Write_OneByte(segNumber_High[twobit]|0x80|seg_h);//display "2 :"
   
  
     TM1639_Stop();


	  //open diplay
    TM1639_Start();
    TM1639_Write_OneByte(OpenDispTM1639|0x8f);//
    TM1639_Stop();


}



	


void TM1639_Write_2bit_SetUp_TempData(uint8_t onebit,uint8_t twobit,uint8_t sel)
{

	
	 TM1639_STB_SetLow();
	 TM1639_Write_OneByte(DisplayReg);//To write display register 0x40
	 TM1639_STB_SetHigh();


	 TM1639_Start();
     TM1639_Write_OneByte(AddrFixed);//Add fixed reg
     TM1639_Stop();

	 
	 //digital 1
     TM1639_Start();
     TM1639_Write_OneByte(AddrC0H);//0xC4H->GRID7->BIT_1
     if(sel==0)
         TM1639_Write_OneByte(segNumber_Low[onebit]);//display ""
     else{
		TM1639_Write_OneByte(segNumber_Low[0x10]);

	 }
     TM1639_Stop();

	 TM1639_Start();
     TM1639_Write_OneByte(AddrC1H);//0xC4H->GRID7->BIT_1
     if(sel==0)
        TM1639_Write_OneByte(segNumber_High[onebit]);//display ""
     else{
		  TM1639_Write_OneByte(segNumber_High[0x10]);
	 }
     TM1639_Stop();


     //digital 2
	 TM1639_Start();
     TM1639_Write_OneByte(AddrC2H);//0xC7H->GRID8->BIT_2
     if(sel==0)
     	TM1639_Write_OneByte(segNumber_Low[twobit]);//display ""
     else{
	     TM1639_Write_OneByte(segNumber_Low[0x10]);


	 }
     TM1639_Stop();
	 
	 TM1639_Start();
     TM1639_Write_OneByte(AddrC3H);//0xC7H->GRID8->BIT_2
     if(sel==0)
     	TM1639_Write_OneByte(segNumber_High[twobit]);//WT.EDIT.2025.02.22.//TM1639_Write_OneByte(segNumber_High[twobit]|seg_h);//display ""
     else{
	    TM1639_Write_OneByte(segNumber_High[0x10]);//TM1639_Write_OneByte(segNumber_High[0x10]|seg_h);

	 }
     TM1639_Stop();

    
    //open diplay
    TM1639_Start();
    TM1639_Write_OneByte(OpenDispTM1639|0x8f);//
    TM1639_Stop();
    
}


/***************************************************************************
    *
*Function Name:void Smg_AllOff(void)
*Function :KEY OF LED 
*Input Ref: NO
*Return Ref: NO
    *
*****************************************************************************/
void Smg_AllOff(void)
{


     TM1639_STB_SetLow();
	 TM1639_Write_OneByte(DisplayReg);//To write display register 0x40
	 TM1639_STB_SetHigh();



	 TM1639_Start();
     TM1639_Write_OneByte(AddrAutoAdd);//auto Add address one mode
      TM1639_Stop();


	 
     TM1639_Write_OneByte(OFFLED);//display "0XC0"
	 TM1639_Write_OneByte(OFFLED);//display "0XC1"
	 
	 TM1639_Write_OneByte(OFFLED);//display "0XC2"
	 TM1639_Write_OneByte(OFFLED);//display "0XC3"
	 
	 TM1639_Write_OneByte(OFFLED);//display "0XC4"
	 TM1639_Write_OneByte(OFFLED);//display "0XC5"
	 
	 TM1639_Write_OneByte(OFFLED);//display "0XC6"
     TM1639_Write_OneByte(OFFLED);//display "0XC7"
     
     TM1639_Write_OneByte(OFFLED);//display "0XC8"
	 TM1639_Write_OneByte(OFFLED);//display "0XC9"
	 
	 TM1639_Write_OneByte(OFFLED);//display "0XCA"
	 TM1639_Write_OneByte(OFFLED);//display "0XCB"
	 
	 TM1639_Write_OneByte(OFFLED);//display "0XCC"
	 TM1639_Write_OneByte(OFFLED);//display "0XCD"
	 
	 TM1639_Write_OneByte(OFFLED);//display "0XCE"
     TM1639_Write_OneByte(OFFLED);//display "0XCF"

	
	


     //close diplay
    TM1639_Start();
    TM1639_Write_OneByte(CloseDispTM1639);////TM1639_Write_OneByte(OpenDispTM1639|0x80);//
    TM1639_Stop();

}



