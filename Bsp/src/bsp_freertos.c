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



///#define QUEUE_LENGTH            1                   /* 队列支持的消息个�? */
///#define QUEUE_ITEM_SIZE         sizeof(uint32_t)    /* 队列中每条消息的大小 */
//#define SEMAPHORE_BINARY_LENGTH 1                   /* 二�?�信号量的有效长�? */
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
*	�?1�?7 �?1�?7 �?1�?7: vTaskTaskUserIF
*	功能说明: 接口消息处理�?1�?7
*	�?1�?7    �?1�?7: pvParameters 是在创建该任务时传��的形参
*	�?1�?7 �?1�?7 �?1�?7: �?1�?7
*   �?1�?7 �?1�?7 �?1�?7: 1  (数��越小优先级越低，这个跟uCOS相反)
**********************************************************************************************************/
void freeRTOS_Handler(void)
{
     /* 创建任务 */
	  AppTaskCreate();
	  
	  /* 创建任务通信机制 */
	 //  AppObjCreate();
	  
	  /* 启动调度，开始执行任�?1�?7 */
	   vTaskStartScheduler();


}

/**********************************************************************************************************
*   FunctionName: static void vTaskRunPro(void *pvParameters)
*	功能说明: 使用函数xTaskNotifyWait接收任务vTaskTaskUserIF发�?�的事件标志位设�?
*	�?    �?: pvParameters 是在创建该任务时传�?�的形参
*	�? �? �?: �?
*   �? �? �?: 1  

*   priority : 1  (数priority is 2,number is large priority is large值越低，这个跟uCOS相反)
**********************************************************************************************************/
static void vTaskDecoderPro(void *pvParameters)
{
    BaseType_t xResult;
	//const TickType_t xMaxBlockTime = pdMS_TO_TICKS(500); /* 设置�?大等待时间为30ms */
	uint32_t ulValue;
	

    while(1)
    {


	xResult = xTaskNotifyWait(0x00000000,
								  0xFFFFFFFF,     /* Reset the notification value to 0 on */
								&ulValue,        /* 保存ulNotifiedValue到变量ulValue�? */
								portMAX_DELAY);//portMAX_DELAY);  /* 阻塞时间30ms，释放CUP控制�?,给其它任务执行的权限*/

		if( xResult == pdPASS )
		{
			/* 接收到消息，�?测那个位被按�? */

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
*   priority: 2  (数�?�越小优先级越低，这个跟uCOS相反)
**********************************************************************************************************/
static void vTaskRunPro(void *pvParameters)
{

	//BaseType_t xResult;
	//const TickType_t xMaxBlockTime = pdMS_TO_TICKS(10); /* 设置�?大等待时间为30ms */
	//uint32_t ulValue;
	static uint8_t power_on_theFirst_times;
    
	
    while(1)
    {

    //mode_key_handler() ;
	process_keys() ;

	if(run_t.gPower_On == power_on){

      if(key_t.key_wifi_flag==80){
           
        SendData_Set_Command(wifi_cmd,0x01);
        osDelay(5);
        key_t.key_wifi_flag =0;
	

       }
	   else if(gpro_t.mode_key_shot_flag ==1){
	   	    gpro_t.mode_key_shot_flag++;
           // SendData_Buzzer();
            //osDelay(DEBOUNCE_DELAY_MS);
            mode_key_short_fun();
	   	}
    
	   power_on_run_handler();
     
       Display_TimeColon_Blink_Fun();
	   RunLocal_Dht11_Data_Process();
       set_timer_fun_led_blink();
       wifi_connect_state_fun();
	   compare_temp_value();
	 
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
*	Input Ref: pvParameters 是在创建该任务时传�?�的形参
*	Return Ref:
*priority: 3  (数�?�越小优先级越低，这个跟uCOS相反)
*
**********************************************************************************************************/
static void vTaskStart(void *pvParameters)
{
	BaseType_t xResult;
    //const TickType_t xMaxBlockTime = pdMS_TO_TICKS(1000); /* 设置�?大等待时间为30ms */
	uint32_t ulValue;
    static  uint8_t power_on_times;

    while(1)
    {
      
      //bsp_KeyScan();



       xResult = xTaskNotifyWait(0x00000000,      
						           0xFFFFFFFF,      
						          &ulValue,        /* 保存ulNotifiedValue到变量ulValue�? */
								  portMAX_DELAY);  /* �?大允许延迟时�? */
        if( xResult == pdPASS ){
		    
            /* 接收到消息，�?测那个位被按�? */
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
            else if((ulValue & MODE_BIT_1 ) != 0){   /* 接收到消息，�?测那个位被按�? */
            	 if(run_t.gPower_On == power_on){
                    key_t.key_mode_flag = 1;
                    key_t.key_wifi_flag =0;
                    gpro_t.mode_Key_long_counter=0;

            	  }
               
             }
            else if((ulValue & DEC_BIT_2 ) != 0){
            	  if(run_t.gPower_On == power_on){
                  key_t.key_dec_flag =1;
                  key_t.key_wifi_flag =0;
            
                }
               
            }
            else if((ulValue & ADD_BIT_3 ) != 0){   /* 接收到消息，�?测那个位被按�? */
            	 if(run_t.gPower_On == power_on){
					 key_t.key_add_flag =1;
					 key_t.key_wifi_flag =0;
            	                  
            	  }


            }
            else if((ulValue & PLASMA_BIT_5 ) != 0){   /* 接收到消息，�?测那个位被按�? */
            	  if(run_t.gPower_On == power_on){
                    key_t.key_plasma_flag =1;
                    key_t.key_wifi_flag =0;
            	                
            	    }
            }
            else if((ulValue & DRY_BIT_6 ) != 0){   /* 接收到消息，�?测那个位被按�? */
            	   if(run_t.gPower_On == power_on){
                    key_t.key_dry_flag =1;
                    key_t.key_wifi_flag =0;
            	               
            	  }
             }
            else if((ulValue & MOUSE_BIT_4 ) != 0){   /* 接收到消息，�?测那个位被按�? */
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
                 "vTaskDecoderPro",  		/* 任务�?1�?7    */
                 128,         		/* stack大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 2,           		/* 任务优先�?1�?7 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskDecoderPro); /* 任务句柄  */

  xTaskCreate( vTaskRunPro,    		/* 任务函数  */
                 "vTaskRunPro",  		/* 任务�?1�?7    */
                 128,         		/* stack大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 1,           		/* 任务优先�?1�?7 数��越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskRunPro); /* 任务句柄  */
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务�?1�?7    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 3,              		/* 任务优先�?1�?7 数��越小优先级越低，这个跟uCOS相反 */
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
                                    eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
                                    &xHigherPriorityTaskWoken);

                /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
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
        eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
        &xHigherPriorityTaskWoken);


        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);


        }
            
     //  ENABLE_INT();
   break;

   case MODEL_KEY_Pin:
      #if 0
      if(WIFI_KEY_VALUE() == KEY_DOWN){
             xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
               AI_BIT_7,     /* 设置目标任务事件标志位bit0  */
               eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
               &xHigherPriorityTaskWoken);

        /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);


      }
        #endif 
       if(MODEL_KEY_VALUE() == KEY_DOWN){
        if(run_t.gPower_On == power_on){
        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
               MODE_BIT_1,     /* 设置目标任务事件标志位bit0  */
               eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
               &xHigherPriorityTaskWoken);

        /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
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
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
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
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
         portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
  
   break;

     case DRY_KEY_Pin:
   
        if(DRY_KEY_VALUE() == KEY_DOWN){

       if(run_t.gPower_On == power_on){
        xTaskNotifyFromISR(xHandleTaskStart,  /* 目标任务 */
                DRY_BIT_6,     /* 设置目标任务事件标志位bit0  */
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
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
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
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
                eSetBits,  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志�? */
                &xHigherPriorityTaskWoken);
   
         /* 如果xHigherPriorityTaskWoken = pdTRUE，那么�??出中断后切到当前�?高优先级任务执行 */
         portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
         }
    ///    ENABLE_INT();
   break;
        
    }
}















