#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


#define POWER_BIT_0	        (1 << 0)
#define MODE_BIT_1	        (1 << 1)
#define DEC_BIT_2           (1 << 2)
#define ADD_BIT_3           (1 << 3)

#define MOUSE_BIT_4           (1 << 4)
#define PLASMA_BIT_5        (1 << 5)
#define DRY_BIT_6           (1<< 6)
#define AI_BIT_7            ( 1<< 7)

#define MODE_LONG_KEY_8         (1 << 8)
#define DECODER_BIT_9          (1<< 9)




/***********************************************************************************************************
											函数声明
***********************************************************************************************************/
static void vTaskRunPro(void *pvParameters);
static void vTaskDecoderPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);



/* 创建任务通信机制 */
//static void AppObjCreate(void);


/***********************************************************************************************************
											变量声明
***********************************************************************************************************/
static TaskHandle_t xHandleTaskRunPro = NULL;
static TaskHandle_t xHandleTaskDecoderPro= NULL;
static TaskHandle_t xHandleTaskStart = NULL;

//static QueueHandle_t xQueue1 = NULL;
//static QueueHandle_t xQueue2 = NULL;
//static QueueHandle_t xQueue3 = NULL;



///#define QUEUE_LENGTH            1                   /* 队列支持的消息个数 */
///#define QUEUE_ITEM_SIZE         sizeof(uint32_t)    /* 队列中每条消息的大小 */
//#define SEMAPHORE_BINARY_LENGTH 1                   /* 二值信号量的有效长度 */
//#define QUEUESET_LENGTH         ((2 * QUEUE_LENGTH) + SEMAPHORE_BINARY_LENGTH)  /* 队列集支持的消息个数 */



typedef struct Msg
{
	
	uint8_t  usData[12];
    uint8_t  ucMessageID;
    uint8_t  rx_data_counter;
    uint8_t  disp_rx_cmd_done_flag;
    uint8_t  bcc_check_code;
    volatile uint8_t ulid;
 
}MSG_T;

MSG_T   gl_tMsg; /* 定义丢�个结构体用于消息队列 */
uint8_t ucKeyCode;
uint8_t uckey_number;
uint8_t key_power_flag,decoder_flag ;
uint8_t check_code;
/**********************************************************************************************************
*	凄1�7 敄1�7 各1�7: vTaskTaskUserIF
*	功能说明: 接口消息处理〄1�7
*	彄1�7    叄1�7: pvParameters 是在创建该任务时传��的形参
*	迄1�7 囄1�7 倄1�7: 旄1�7
*   伄1�7 兄1�7 纄1�7: 1  (数��越小优先级越低，这个跟uCOS相反)
**********************************************************************************************************/
void freeRTOS_Handler(void)
{
     /* 创建任务 */
	  AppTaskCreate();
	  
	  /* 创建任务通信机制 */
	 //  AppObjCreate();
	  
	  /* 启动调度，开始执行任劄1�7 */
	   vTaskStartScheduler();


}

/**********************************************************************************************************
*   FunctionName: static void vTaskRunPro(void *pvParameters)
*	功能说明: 使用函数xTaskNotifyWait接收任务vTaskTaskUserIF发送的事件标志位设置
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 1  

*   priority : 1  (数priority is 2,number is large priority is large值越低，这个跟uCOS相反)
**********************************************************************************************************/
static void vTaskDecoderPro(void *pvParameters)
{
    BaseType_t xResult;
	//const TickType_t xMaxBlockTime = pdMS_TO_TICKS(500); /* 设置最大等待时间为30ms */
	uint32_t ulValue;
	

    while(1)
    {


	xResult = xTaskNotifyWait(0x00000000,
								  0xFFFFFFFF,     /* Reset the notification value to 0 on */
								&ulValue,        /* 保存ulNotifiedValue到变量ulValue中 */
								portMAX_DELAY);//portMAX_DELAY);  /* 阻塞时间30ms，释放CUP控制权,给其它任务执行的权限*/

		if( xResult == pdPASS )
		{
			/* 接收到消息，检测那个位被按下 */

			if((ulValue & DECODER_BIT_9) != 0){

			   
				gl_tMsg.disp_rx_cmd_done_flag = 0;

				check_code =  bcc_check(gl_tMsg.usData,gl_tMsg.ulid);

				if(check_code == gl_tMsg.bcc_check_code ){

				receive_data_from_mainboard(gl_tMsg.usData);
				}
			    
			}

		}


    }

 }
/**********************************************************************************************************
*	Function Name: static void vTaskRunPro(void *pvParameters)
*	Function: 
*	Input Ref: pvParameters 是在创建该任务时传��的形参
*	Return Ref:
*   priority: 2  (数值越小优先级越低，这个跟uCOS相反)
**********************************************************************************************************/
static void vTaskRunPro(void *pvParameters)
{

	//BaseType_t xResult;
	//const TickType_t xMaxBlockTime = pdMS_TO_TICKS(10); /* 设置最大等待时间为30ms */
	//uint32_t ulValue;
	static uint8_t power_on_theFirst_times;
    
	
    while(1)
    {
     //wifi_key 
     if(WIFI_KEY_VALUE() == KEY_DOWN &&   key_t.key_wifi_flag <60 && run_t.gPower_On == power_on){
        	key_t.key_wifi_flag++; 
        
         if(key_t.key_wifi_flag >30){
          key_t.key_wifi_flag=80;
          run_t.wifi_led_fast_blink=1;
          run_t.wifi_connect_state_flag = wifi_connect_null;
          run_t.gTimer_wifi_connect_counter =0; //120s counte start
          SendData_Buzzer();        
         }
   
        }
	
      if(key_t.key_power_flag ==1){ //&& POWER_KEY_VALUE() ==KEY_UP){
			key_t.key_power_flag ++;

			    if(run_t.gPower_On == power_off){
		
					  SendData_PowerOnOff(1);//power on
					  osDelay(10);
				}
				else{
		
					SendData_PowerOnOff(0);//power off
				    osDelay(10);

				}
			}
			else if(key_t.key_mode_flag ==1){ //&& MODEL_KEY_VALUE()==KEY_UP){
				 key_t.key_mode_flag ++;
				 SendData_Buzzer();//SendData_Buzzer_Has_Ack();
	             osDelay(5);
				mode_key_fun();
			}
			else if(key_t.key_dec_flag ==1){// && DEC_KEY_VALUE()==KEY_UP){
				 key_t.key_dec_flag ++;
				//SendData_Buzzer();//SendData_Buzzer_Has_Ack();
				gpro_t.send_ack_cmd = check_ack_buzzer;
				gpro_t.gTimer_again_send_power_on_off =0;
				key_dec_fun();
			}
			else if(key_t.key_add_flag ==1){ // && ADD_KEY_VALUE()==KEY_UP){
				 key_t.key_add_flag ++;
				// SendData_Buzzer();//SendData_Buzzer_Has_Ack();
				gpro_t.send_ack_cmd = check_ack_buzzer;
				gpro_t.gTimer_again_send_power_on_off =0;
				key_add_fun();
			}
			else if(key_t.key_plasma_flag ==1){// && PLASMA_KEY_VALUE()==KEY_UP){
				 key_t.key_plasma_flag ++;

             if(gpro_t.set_timer_timing_doing_value==0 ||gpro_t.set_timer_timing_doing_value==3){
				 if(run_t.gPlasma == 1){
        			 run_t.gPlasma = 0;
                     SendData_Set_Command(plasma_cmd,0x0); //
        			 LED_PLASMA_OFF();
					gpro_t.send_ack_cmd = check_ack_plasma_off;
				     gpro_t.gTimer_again_send_power_on_off =0;
        			 
        		 }
        		 else{
        			 run_t.gPlasma = 1;

                     SendData_Set_Command(plasma_cmd,0x01); //
        			 LED_PLASMA_ON();
					  gpro_t.send_ack_cmd = check_ack_plasma_on;
				     gpro_t.gTimer_again_send_power_on_off =0;
        			
        	     }
                }

			}
			else if(key_t.key_dry_flag ==1){ // && DRY_KEY_VALUE()==KEY_UP){
				 key_t.key_dry_flag ++;

             if(gpro_t.set_timer_timing_doing_value==0 || gpro_t.set_timer_timing_doing_value==3){
				 if(run_t.gDry ==0){
                   SendData_Set_Command(dry_cmd,0x01); //
                    osDelay(5);
        		   run_t.gDry =1;
                   gpro_t.g_manual_shutoff_dry_flag = 0;
        		   LED_DRY_ON();
        		   gpro_t.send_ack_cmd = check_ack_ptc_on;
        		   gpro_t.gTimer_again_send_power_on_off =0;
        		   
        	   }
        	   else{
                   SendData_Set_Command(dry_cmd,0x00); //
                    osDelay(5);
        		   run_t.gDry = 0;
                   gpro_t.g_manual_shutoff_dry_flag = 1; //if gpro_t.g_manual_shutoff_dry_flag ==1,don't again open dry function.
        		   LED_DRY_OFF();
        		   gpro_t.send_ack_cmd = check_ack_ptc_off;
        		   gpro_t.gTimer_again_send_power_on_off =0;
        		  
        	   }
                }
				
			}
			else if(key_t.key_mouse_flag ==1){
				 key_t.key_mouse_flag ++;
                if(gpro_t.set_timer_timing_doing_value==0 || gpro_t.set_timer_timing_doing_value==3){
				 if(run_t.gMouse ==0){
        		   
                   SendData_Set_Command(mouse_cmd,0x01); //
                   osDelay(5);
                   run_t.gMouse =1;
        		   LED_MOUSE_ON();
        		
                   
        		   
				   }
        	      else if(run_t.gMouse ==1){
        		   
                   SendData_Set_Command(mouse_cmd,0x00); //
                    osDelay(5);
                   run_t.gMouse = 0;
        		   LED_MOUSE_OFF();
        		 
                   }
                  
        		   
				}
			    
			}

	if(run_t.gPower_On == power_on){

     if(key_t.key_wifi_flag==80){
           
        SendData_Set_Command(wifi_cmd,0x01);
        osDelay(10);
        key_t.key_wifi_flag =0;
	

       }
	   power_on_run_handler();
     
       Display_TimeColon_Blink_Fun();
	   RunLocal_Dht11_Data_Process();
       set_timer_fun_led_blink();
       wifi_connect_state_fun(run_t.wifi_led_fast_blink);
       if(power_on_theFirst_times < 10 && (gpro_t.set_timer_timing_doing_value==0 || gpro_t.set_timer_timing_doing_value==3)){
         power_on_theFirst_times ++;
         Display_DHT11_Value();

       }
     
       works_run_two_hours_handler();

      }
      else if(run_t.gPower_On == power_off){

          power_off_run_handler();

       }

   
      send_cmd_ack_hanlder();

	  vTaskDelay(20);
     

       } //wihile(1) ---end
  }
//}

/**********************************************************************************************************
*
*	Function Name: vTaskStart
*	Function: 
*	Input Ref: pvParameters 是在创建该任务时传递的形参
*	Return Ref:
*priority: 3  (数值越小优先级越低，这个跟uCOS相反)
*
**********************************************************************************************************/
static void vTaskStart(void *pvParameters)
{
	BaseType_t xResult;
    //const TickType_t xMaxBlockTime = pdMS_TO_TICKS(1000); /* 设置最大等待时间为30ms */
	uint32_t ulValue;
    static  uint8_t power_on_times;

    while(1)
    {
      
      //bsp_KeyScan();



       xResult = xTaskNotifyWait(0x00000000,      
						           0xFFFFFFFF,      
						          &ulValue,        /* 保存ulNotifiedValue到变量ulValue中 */
								  portMAX_DELAY);  /* 最大允许延迟时间 */
        if( xResult == pdPASS ){
		    
            /* 接收到消息，检测那个位被按下 */
            if((ulValue & POWER_BIT_0 ) != 0)
            {
            if(power_on_times==0){
				power_on_times++;
									
			}
			else{
                  key_t.key_wifi_flag =0;
                  key_t.key_power_flag =1;
										
			}
                
            }
            else if((ulValue & MODE_BIT_1 ) != 0){   /* 接收到消息，检测那个位被按下 */
            	 if(run_t.gPower_On == power_on){
                    key_t.key_mode_flag = 1;
                    key_t.key_wifi_flag =0;

            	  }
               
             }
            else if((ulValue & DEC_BIT_2 ) != 0){
            	  if(run_t.gPower_On == power_on){
                  key_t.key_dec_flag =1;
                  key_t.key_wifi_flag =0;
            
                }
               
            }
            else if((ulValue & ADD_BIT_3 ) != 0){   /* 接收到消息，检测那个位被按下 */
            	 if(run_t.gPower_On == power_on){
					 key_t.key_add_flag =1;
					 key_t.key_wifi_flag =0;
            	                  
            	  }


            }
            else if((ulValue & PLASMA_BIT_5 ) != 0){   /* 接收到消息，检测那个位被按下 */
            	  if(run_t.gPower_On == power_on){
                    key_t.key_plasma_flag =1;
                    key_t.key_wifi_flag =0;
            	                
            	    }
            }
            else if((ulValue & DRY_BIT_6 ) != 0){   /* 接收到消息，检测那个位被按下 */
            	   if(run_t.gPower_On == power_on){
                    key_t.key_dry_flag =1;
                    key_t.key_wifi_flag =0;
            	               
            	  }
             }
            else if((ulValue & MOUSE_BIT_4 ) != 0){   /* 接收到消息，检测那个位被按下 */
            	 if(run_t.gPower_On == power_on){
                   
            	      key_t.key_mouse_flag =1;
                    key_t.key_wifi_flag =0;
                     }
            	                 
            }

          }
		
           
        }
}
 /**********************************************************************************************************
*	Function Name: AppTaskCreate
*	功能说明: 创建应用任务
*	Input Ref:   
*	Return Ref:
**********************************************************************************************************/
void AppTaskCreate (void)
{

  xTaskCreate( vTaskDecoderPro,    		/* 任务函数  */
                 "vTaskDecoderPro",  		/* 任务各1�7    */
                 128,         		/* stack大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 2,           		/* 任务优先纄1�7 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskDecoderPro); /* 任务句柄  */

  xTaskCreate( vTaskRunPro,    		/* 任务函数  */
                 "vTaskRunPro",  		/* 任务各1�7    */
                 128,         		/* stack大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 1,           		/* 任务优先纄1�7 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskRunPro); /* 任务句柄  */
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务各1�7    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 3,              		/* 任务优先纄1�7 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskStart );   /* 任务句柄  */
}




/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
     static uint8_t state,rx_end_flag ;
     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  

    if(huart==&huart1) // Motor Board receive data (filter)
	{

    //   DISABLE_INT();
       switch(state)
		{
		case 0:  //#0
			if(inputBuf[0] == 0x5A){  // 0x5A --main board singla
               gl_tMsg.rx_data_counter=0;
               gl_tMsg.usData[gl_tMsg.rx_data_counter] = inputBuf[0];
				state=1; //=1

             }
            else
                state=0;
		break;

       
		case 1: //#1

            if(gl_tMsg.disp_rx_cmd_done_flag ==0){
              /* 初始化结构体指针 */
               gl_tMsg.rx_data_counter++;
		     
	          gl_tMsg.usData[gl_tMsg.rx_data_counter] = inputBuf[0];
              

              if(rx_end_flag == 1){

                state = 0;
            
                gl_tMsg.ulid = gl_tMsg.rx_data_counter;
                rx_end_flag=0;

                gl_tMsg.rx_data_counter =0;

                gl_tMsg.disp_rx_cmd_done_flag = 1 ;

                gl_tMsg.bcc_check_code=inputBuf[0];

              
                xTaskNotifyFromISR(xHandleTaskDecoderPro,  /* 目标任务 */
                                    DECODER_BIT_9,     /* 设置目标任务事件标志位bit0  */
                                    eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
                                    &xHigherPriorityTaskWoken);

                /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
                  
              }

              }

              if(gl_tMsg.usData[gl_tMsg.rx_data_counter] ==0xFE && rx_end_flag == 0 &&   gl_tMsg.rx_data_counter > 4){
                     
                     rx_end_flag = 1 ;
                          
              }

        break;


			
		}

       //   ENABLE_INT();
    __HAL_UART_CLEAR_OREFLAG(&huart1);
	HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
    
   }
}


#if 0
void USART1_Cmd_Error_Handler(void)
{
   uint32_t temp;
   if(run_t.gTimer_usart_error >4){
	  	run_t.gTimer_usart_error=0;
	    
         
        __HAL_UART_CLEAR_OREFLAG(&huart1);
        temp = USART1->RDR;
		UART_Start_Receive_IT(&huart1,inputBuf,1);
       
		}
      
    
  
 }
#endif 
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{

 
   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    __HAL_GPIO_EXTI_CLEAR_RISING_IT(GPIO_Pin);
 
   switch(GPIO_Pin){

   case POWER_KEY_Pin:
       // DISABLE_INT(); //WT.EDIT 2024.08.15 modify.
        if(POWER_KEY_VALUE()  ==KEY_DOWN){

     

        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
        POWER_BIT_0,      /* 设置目标任务事件标志位bit0  */
        eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
        &xHigherPriorityTaskWoken);


        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);


        }
            
     //  ENABLE_INT();
   break;

   case MODEL_KEY_Pin:
     
//      if(WIFI_KEY_VALUE() == KEY_DOWN){
//             xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
//               AI_BIT_7,     /* 设置目标任务事件标志位bit0  */
//               eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
//               &xHigherPriorityTaskWoken);
//
//        /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
//        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//
//
//      }
       if(MODEL_KEY_VALUE() == KEY_DOWN){
        if(run_t.gPower_On == power_on){
        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
               MODE_BIT_1,     /* 设置目标任务事件标志位bit0  */
               eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
               &xHigherPriorityTaskWoken);

        /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);


       }
    
      }
   
   break;


   case DEC_KEY_Pin:
      // DISABLE_INT();
       if(DEC_KEY_VALUE() == KEY_DOWN){
        if(run_t.gPower_On == power_on){
         xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
                DEC_BIT_2,     /* 设置目标任务事件标志位bit0  */
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
         portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        }
     ///  ENABLE_INT();
   break;

   case ADD_KEY_Pin:
      ///   DISABLE_INT();
        if(ADD_KEY_VALUE() == KEY_DOWN){
        if(run_t.gPower_On == power_on){
        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
                ADD_BIT_3,     /* 设置目标任务事件标志位bit0  */
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
         portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
  
   break;

     case DRY_KEY_Pin:
   
        if(DRY_KEY_VALUE() == KEY_DOWN){

       if(run_t.gPower_On == power_on){
        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
                DRY_BIT_6,     /* 设置目标任务事件标志位bit0  */
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
         portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
   
   break;

   case PLASMA_KEY_Pin:
      ///   DISABLE_INT();
       if(PLASMA_KEY_VALUE() == KEY_DOWN){
        if(run_t.gPower_On == power_on){
        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
                PLASMA_BIT_5,     /* 设置目标任务事件标志位bit0  */
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
         portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        }
    ///    ENABLE_INT();
   break;

   case MOUSE_KEY_Pin:
      ///   DISABLE_INT();
        if(MOUSE_KEY_VALUE() == KEY_DOWN){
        if( run_t.gPower_On == power_on){
        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
                MOUSE_BIT_4,     /* 设置目标任务事件标志位bit0  */
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
         portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
         }
    ///    ENABLE_INT();
   break;
        
    }
}















