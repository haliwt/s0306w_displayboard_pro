#ifndef __BSP_SMG_H__
#define __BSP_SMG_H__
#include "main.h"


//IO��������
#define TM1640_DIN_IO_IN()    {GPIOB->MODER&=0XFCFFFFFF;GPIOB->MODER|=0<<24;}  //0x00 input mode
#define TM1640_DIN_IO_OUT()   {GPIOB->MODER&=0XFCFFFFFF;GPIOB->MODER|=1<<24;}   //0x01 output  mode 


#define TM1639_STB_PIN                GPIO_PIN_4
#define TM1639_DIO_PIN                GPIO_PIN_5
#define TM1639_CLK_PIN                GPIO_PIN_6
#define TM1639_GPIO                   GPIOA  

#define TM1639_CLK_SetHigh()            HAL_GPIO_WritePin(TM1639_GPIO,TM1639_CLK_PIN,GPIO_PIN_SET)    // ����ߵ�ƽ
#define TM1639_CLK_SetLow()             HAL_GPIO_WritePin(TM1639_GPIO,TM1639_CLK_PIN,GPIO_PIN_RESET)  // ����͵�ƽ

#define TM1639_DIO_SetHigh()            HAL_GPIO_WritePin(TM1639_GPIO,TM1639_DIO_PIN,GPIO_PIN_SET)    // ����ߵ�ƽ
#define TM1639_DIO_SetLow()             HAL_GPIO_WritePin(TM1639_GPIO,TM1639_DIO_PIN,GPIO_PIN_RESET)    // output low level

#define TM1639_STB_SetHigh()            HAL_GPIO_WritePin(TM1639_GPIO,TM1639_STB_PIN,GPIO_PIN_SET)
#define TM1639_STB_SetLow()             HAL_GPIO_WritePin(TM1639_GPIO,TM1639_STB_PIN,GPIO_PIN_RESET)



//extern volatile uint8_t DispData[3];//??LED??
#define		BitSET(x,y)		x|=(1<<y)				//?1
#define		BitCLR(x,y)		x&=~(1<<y)				//?0


		
#define DisplayReg           0x40// to write display register 
 
#define AddrFixed 	         0x44// 
#define AddrAutoAdd         0x40 

  
 
#define OpenDispTM1639          0x88// 
#define CloseDispTM1639		    0x80// 


 
 //Display Address 
#define AddrC0H  		0xC0//??00H
#define AddrC1H  		0xC1//??01H

#define AddrC2H  		0xC2//??02H
#define AddrC3H  		0xC3//??03H
//digital 3
#define AddrC4H  		0xC4//??03H
#define AddrC5H  		0xC5//??03H
//digital 4
#define AddrC6H  		0xC6//??00H
#define AddrC7H  		0xC7//??01H


//Humidity SMG address
#define AddrC8H  		0xC8//??02H
#define AddrC9H  		0xC9//??03H

#define AddrCAH  		0xCA//??03H
#define AddrCBH  		0xCB//??03H

//temperature SMG address
#define AddrCCH         0xCC//??0CH
#define AddrCDH         0xCD//??0DH

#define AddrCEH         0xCE//??0CH
#define AddrCFH         0xCF//??0DH



#define Set1_16TM1640           0X88

#define Set14_16TM1640 		    0X8F//??????? 14/16 

//Low Bit    
#define   seg_a  0x01      //SEG0   //seg_e = 0x10  
#define   seg_b  0x02      //SEG1 , //seg_f = 0x20
#define   seg_c  0x04      //SEG2 , //seg_g = 0x40
#define   seg_d  0x08      //SEG3 , //seg_d = 0x08

//High BIT
#define   seg_e  0x01      //SEG4 , //seg_c = 0x04
#define   seg_f  0x02      //SEG5   //seg_a = 0x01
#define   seg_g  0x04      //SEG6   //seg_b = 0x02 
#define   seg_h  0x08      //SEG7 -> ":"









void TM1639_Write_4Bit_Time(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit,uint8_t sl);
void TM1639_Write_2bit_TempData(uint8_t onebit,uint8_t twobit);
void TM1639_Write_2bit_HumData(uint8_t onebit,uint8_t twobit);
void TM1639_Write_4Bit_TemperatureData(uint8_t threebit,uint8_t fourbit);

void TM1639_Write_4Bit_TimerData(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit,uint8_t sl);

void TM1639_Write_2bit_SetUp_TempData(uint8_t onebit,uint8_t twobit,uint8_t sel);


void SmgBlink_Colon_Function(uint8_t onebit,uint8_t twobit,uint8_t sel);

//void TM1639_Write_4Bit_Fan_Level(uint8_t fan_level);
void Smg_AllOff(void);

void TM1639_Write_4Bit_Time_sync_close(uint8_t onebit,uint8_t twobit,uint8_t threebit,uint8_t fourbit,uint8_t sl);


#endif 

