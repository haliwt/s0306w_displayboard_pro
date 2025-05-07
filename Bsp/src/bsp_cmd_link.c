#include "bsp.h"

// 定义宏，提高代码可读性
#define FRAME_HEADER        0xA5
#define DEVICE_NUMBER       0x02
#define FRAME_END           0xFE
#define NO_DATA             0x00
#define HAS_DATA            0x0F



volatile uint8_t transOngoingFlag; // UART传输标志
uint8_t outputBuf[MAX_BUFFER_BUF];
volatile uint8_t transferSize;
//uint8_t inputBuf[MAX_BUFFER_SIZE];


/****************************************************************************************************
 * Function Name: static void sendUartData
 * Function: 通过UART发送数据
 * Input Ref: data - 数据指针, size - 数据大小
 * Return Ref: 无
 ****************************************************************************************************/
static void sendUartData(uint8_t *data, uint8_t size) {
    if (size) {
        while (transOngoingFlag); // 等待上一次传输完成
        transOngoingFlag = 1;
        HAL_UART_Transmit_IT(&huart1, data, size);
    }
}

/****************************************************************************************************
 * Function Name: static void fillFrame
 * Function: 填充帧数据
 * Input Ref: cmd - 命令, frameType - 帧类型, data - 数据指针, dataLen - 数据长度
 * Return Ref: 无
 ****************************************************************************************************/
static void fillFrame(uint8_t cmd, uint8_t frameType, uint8_t *data, uint8_t dataLen) {
    outputBuf[0] = FRAME_HEADER;       // 帧头
    outputBuf[1] = DEVICE_NUMBER;      // 设备号
    outputBuf[2] = cmd;                // 命令
    outputBuf[3] = frameType;          // 帧类型（0x0F 表示数据类型，其他表示命令类型）

    if (frameType == HAS_DATA){       // 数据类型
        outputBuf[4] = dataLen;        // 数据长度
        for (uint8_t i = 0; i < dataLen; i++) {
            outputBuf[5 + i] = data[i]; // 填充数据
        }
        outputBuf[5 + dataLen] = FRAME_END; // 帧尾
        outputBuf[6 + dataLen] = bcc_check(outputBuf, 6 + dataLen); // 校验码
        transferSize = 7 + dataLen;    // 计算帧总长度
    } else {                           // 命令类型
        outputBuf[4] = data[0];      // 功能码
        outputBuf[5] = FRAME_END;      // 帧尾
        outputBuf[6] = bcc_check(outputBuf, 6); // 校验码
        transferSize = 7;              // 帧总长度
    }
}

/****************************************************************************************************
 * Function Name: SendData_Buzzer
 * Function: 发送蜂鸣器命令
 * Input Ref: 无
 * Return Ref: 无
 ****************************************************************************************************/
void SendData_Buzzer(void) {
    uint8_t cmd = 0x06; // 蜂鸣器命令
    uint8_t cmdData = 0x01; // 打开蜂鸣器
    fillFrame(cmd,NO_DATA,&cmdData,0);
    sendUartData(outputBuf, transferSize);
}

/****************************************************************************************************
 * Function Name: SendData_Set_Command
 * Function: 发送设置命令
 * Input Ref: cmd - 命令, cmdData - 命令数据
 * Return Ref: 无
 ****************************************************************************************************/
void SendData_Set_Command(uint8_t cmd, uint8_t cmdData) {
    fillFrame(cmd,NO_DATA,&cmdData, 0);
    sendUartData(outputBuf, transferSize);
}

/****************************************************************************************************
 * Function Name: SendData_Tx_Data
 * Function: 发送数据命令
 * Input Ref: cmd - 命令, data - 数据
 * Return Ref: 无
 ****************************************************************************************************/
void SendData_Tx_Data(uint8_t cmd, uint8_t data) {
    fillFrame(cmd, HAS_DATA, &data, 1);
    sendUartData(outputBuf, transferSize);
}

/****************************************************************************************************
 * Function Name: SendData_Temp_Data
 * Function: 发送温度数据
 * Input Ref: tdata - 温度数据
 * Return Ref: 无
 ****************************************************************************************************/
void SendData_Temp_Data(uint8_t tdata) {
    fillFrame(0x1A, HAS_DATA, &tdata, 1);
    sendUartData(outputBuf, transferSize);
}

/****************************************************************************************************
 * Function Name: SendData_ToMainboard_Data
 * Function: 发送设置温度数据
 * Input Ref: tdata - 温度数据
 * Return Ref: 无
 ****************************************************************************************************/
void SendData_ToMainboard_Data(uint8_t cmd,uint8_t tdata,uint8_t datalen) 
{
    fillFrame(cmd, HAS_DATA, &tdata, datalen);
    sendUartData(outputBuf, (7+datalen));
}

/****************************************************************************************************
 * Function Name: SendData_PowerOnOff
 * Function: 发送电源开关命令
 * Input Ref: index - 电源状态 (0: 关, 1: 开)
 * Return Ref: 无
 ****************************************************************************************************/
void SendData_PowerOnOff(uint8_t index) {
    fillFrame(0x01,NO_DATA,&index,0);
    sendUartData(outputBuf, transferSize);
}

/****************************************************************************************************
 * Function Name: HAL_UART_TxCpltCallback
 * Function: UART发送完成回调函数
 * Input Ref: UART_HandleTypeDef 指针
 * Return Ref: 无
 ****************************************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        transOngoingFlag = 0; // 清除传输标志
    }
}


#if 0
// 定义宏，提高代码可读性
#define FRAME_HEADER 				0xA5  //display  board 
#define DEVICE_NUMBER 				0x02  // 0x2 --the second display board
#define FRAME_END 					0xFE
#define NO_DATA 					0x00
#define HAS_DATA 					0x0F





volatile  uint8_t transOngoingFlag; //interrupt Transmit flag bit , 1---stop,0--run

static void sendUartData(uint8_t *data, uint8_t size);
uint8_t outputBuf[8];
//static uint8_t transferSize;
uint8_t inputBuf[MAX_BUFFER_SIZE];

volatile uint8_t transferSize;


//#if 0

/****************************************************************************************************
**
* Function Name: static void sendUartData(uint8_t *data, uint8_t size)
* Function: Send data via UART
* Input Ref: data - data to send, size - size of data
* Return Ref: NO
*
****************************************************************************************************/
static void sendUartData(uint8_t *data, uint8_t size)
{
    if (size) {
        while (transOngoingFlag); // Wait until the previous transmission is complete
        transOngoingFlag = 1;
        HAL_UART_Transmit_IT(&huart1, data, size);
    }
}

/*********************************************************
 * 
 * Function Name:void SendData_Buzzer(void)
 * Function: 
 * Input Ref:NO
 * Return Ref:NO
 * 
*********************************************************/
void SendData_Buzzer(void)
{
	
    outputBuf[0]=FRAME_HEADER; //display board head = 0xA5
	outputBuf[1]= DEVICE_NUMBER; //display device Number:is 0x01
	outputBuf[2]=0x06; // command type = 0x06 ->buzzer sound open or not
	outputBuf[3]=0x01; // command order -> 01 - buzzer sound done, 00- don't buzzer sound 
	outputBuf[4]=NO_DATA; // data is length: 00 ->don't data 
	outputBuf[5]=FRAME_END; // frame of end code -> 0xFE.
	
	outputBuf[6] = bcc_check(outputBuf,6);
	transferSize=7;
	sendUartData(outputBuf, transferSize);
	
//	if(transferSize)
//	{
//		while(transOngoingFlag);
//		transOngoingFlag=1;
//		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
//	}
	
}
/*********************************************************
 * 
 * Function Name:void SendData_Set_Command(uint8_t cmd,uint8_t cmddata)
 * Function: 
 * Input Ref:cmd- command , dmddata-> command of mode .
 * Return Ref:NO
 * 
*********************************************************/
void SendData_Set_Command(uint8_t cmd,uint8_t cmddata)

{
	outputBuf[0]=FRAME_HEADER; //display board head = 0xA5
	outputBuf[1]= DEVICE_NUMBER; //second display device Number:is 0x02
	outputBuf[2]= cmd; // command type = 0x06 ->buzzer sound open or not
	outputBuf[3]= cmddata; // command order -> 01 - buzzer sound done, 00- don't buzzer sound 
	outputBuf[4]=NO_DATA; // data is length: 00 ->don't data 
	outputBuf[5]=FRAME_END; // frame of end code -> 0xFE.
    outputBuf[6] = bcc_check(outputBuf,6);


     transferSize=7;
    sendUartData(outputBuf, transferSize);
	
}

/*********************************************************
 * 
 * Function Name:void SendData_Tx_Data(uint8_t dcmd,uint8_t ddata)
 * Function: 
 * Input Ref:cmd- command , dmddata-> command of mode .
 * Return Ref:NO
 * 
*********************************************************/
void SendData_Tx_Data(uint8_t dcmd,uint8_t ddata)

{
	outputBuf[0]=FRAME_HEADER; //display board head = 0xA5
	outputBuf[1]= DEVICE_NUMBER; //display device Number:is 0x01
	outputBuf[2]= dcmd; // command 
	outputBuf[3]= 0x0f; //  0x0f -> is data 
	outputBuf[4]=0x01; // data is length: only one word of data.
    outputBuf[5]=ddata; // receive of data
    outputBuf[6]=FRAME_END; // frame of end code -> 0xFE.
    outputBuf[7] = bcc_check(outputBuf,7);


	transferSize=8;
	sendUartData(outputBuf, transferSize);
		
	
}
/*********************************************************
 * 
 * Function Name:
 * Function:
 * Input Ref:NO
 * Return Ref:NO
 * 
*********************************************************/
void SendData_Temp_Data(uint8_t tdata)
{

    outputBuf[0]=FRAME_HEADER; //display board head = 0xA5
	outputBuf[1]= DEVICE_NUMBER; //display device Number:is 0x01
	outputBuf[2]=0x1A; // command type = 0x1A -> temperature of value 
	outputBuf[3]=0x0f; // command order -> 0x0f -> is data , don't order.
	outputBuf[4]=0x01; // data is length: 00 ->don't data 
	outputBuf[5]=tdata; // frame of end code -> 0xFE.
	outputBuf[6]=FRAME_END; // frame of end code -> 0xFE.
    outputBuf[7] = bcc_check(outputBuf,7);
		
	transferSize=8;
	sendUartData(outputBuf, transferSize);
}

/*********************************************************
 * 
 * Function Name:
 * Function:
 * Input Ref:NO
 * Return Ref:NO
 * 
*********************************************************/
void SendData_ToMainboard_Data(uint8_t tdata)
{

    outputBuf[0]=FRAME_HEADER; //display board head = 0xA5
	outputBuf[1]= DEVICE_NUMBER; //display device Number:is 0x02
	outputBuf[2]=0x2A; // command type = 0x1A -> temperature of value 
	outputBuf[3]=0x0f; // command order -> 0x0f -> is data , don't order.
	//don't receive data//outputBuf[4]=0x01; // data is length: 00 ->don't data 
	outputBuf[4]=tdata; // frame of end code -> 0xFE.
	outputBuf[5]=FRAME_END; // frame of end code -> 0xFE.
    outputBuf[6] = bcc_check(outputBuf,6);
		
	transferSize=7;
	sendUartData(outputBuf, transferSize);
		

}

/****************************************************************************************************
    * Function Name: SendData_PowerOnOff
    * Function: 发送电源开关命令
    * Input Ref: 电源状态 (index)
****************************************************************************************************/
void SendData_PowerOnOff(uint8_t index) 
{
	 //crc=0x55;
		outputBuf[0]=FRAME_HEADER; //display board head = 0xA5
		outputBuf[1]= DEVICE_NUMBER; //display device Number: No:01 maybe is No:02.
		outputBuf[2] =0x01; //command power or off
		outputBuf[3]=index; // command order -> 01 - power on , 00- power off
		outputBuf[4]=NO_DATA; // data is length: 00 ->don't data
		outputBuf[5]=FRAME_END; // frame of end code -> 0xFE.

		outputBuf[6] = bcc_check(outputBuf,6);
		transferSize=7;
		sendUartData(outputBuf, transferSize);

	//	if(transferSize)
	//	{
	//		while(transOngoingFlag);
	//		transOngoingFlag=1;
	//		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	//	}
}

/****************************************************************************************************
    * Function Name: SendWifiData_Answer_Cmd
    * Function: 发送 WiFi 应答命令
    * Input Ref: 命令 (cmd) 和数据 (data)
****************************************************************************************************/
void SendWifiData_Answer_Cmd(uint8_t cmd, uint8_t frameType) 
{
  
}
void SendData_Buzzer_Has_Ack(void)
{

    
}

/****************************************************************************************************
    * Function Name: HAL_UART_TxCpltCallback
    * Function: UART 发送完成回调函数
    * Input Ref: UART_HandleTypeDef 指针
****************************************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) 
{
    if (huart->Instance == USART1) {
        transOngoingFlag = 0; // 清除传输标志
    }
}

#endif 

#if 0

/****************************************************************************************************
**
*Function Name:static void selectLight(uint8_t index)
*Function: UART2 transmit interrupt process ---4D 58 4C 53 32 30 32 
*Input Ref: LED number 
*Return Ref:NO
*
****************************************************************************************************/
void SendData_PowerOnOff(uint8_t index)
{
	
   //crc=0x55;
	outputBuf[0]=0xA5; //display board head = 0xA5
	outputBuf[1]= 0x01; //display device Number:is 0x01
	outputBuf[2]=0x01; // command type = 0x01 ->power on or power off 
	outputBuf[3]=index; // command order -> 01 - power on , 00- power off
	outputBuf[4]=0x00; // data is length: 00 ->don't data 
	outputBuf[5]=0xFE; // frame of end code -> 0xFE.
	
	outputBuf[6] = bcc_check(outputBuf,6);
	transferSize=7;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}
/****************************************************************************************************
**
*Function Name:void SendData_Buzzer(void)
*Function: send buzzer sound cmd.
*Input Ref: NO 
*Return Ref:NO
*
****************************************************************************************************/
void SendData_Buzzer(void)
{
	
    outputBuf[0]=0xA5; //display board head = 0xA5
	outputBuf[1]= 0x01; //display device Number:is 0x01
	outputBuf[2]=0x06; // command type = 0x06 ->buzzer sound open or not
	outputBuf[3]=0x01; // command order -> 01 - buzzer sound done, 00- don't buzzer sound 
	outputBuf[4]=0x00; // data is length: 00 ->don't data 
	outputBuf[5]=0xFE; // frame of end code -> 0xFE.
	
	outputBuf[6] = bcc_check(outputBuf,6);
	transferSize=7;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}

void SendData_Buzzer_Has_Ack(void)
{
	
    outputBuf[0]=0xA5; //display board head = 0xA5
	outputBuf[1]= 0x01; //display device Number:is 0x01
	outputBuf[2]=0x16; // command type = 0x06 ->buzzer sound open or not
	outputBuf[3]=0x01; // command order -> 01 - buzzer sound done, 00- don't buzzer sound 
	outputBuf[4]=0x00; // data is length: 00 ->don't data 
	outputBuf[5]=0xFE; // frame of end code -> 0xFE.
	
	outputBuf[6] = bcc_check(outputBuf,6);
	transferSize=7;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}

/****************************************************************************************************
**
*Function Name:void SendData_Buzzer(void)
*Function: send buzzer sound cmd.
*Input Ref: to mainboard order , data - send to main board data. 
*Return Ref:NO
*
****************************************************************************************************/
void SendData_Set_Command(uint8_t cmd,uint8_t data)
{
    outputBuf[0]=0xA5; //display board head = 0xA5
	outputBuf[1]= 0x01; //display device Number:is 0x01
	outputBuf[2]=cmd; // command type = 0x06 ->buzzer sound open or not
	outputBuf[3]= data; // command order -> 01 - buzzer sound done, 00- don't buzzer sound 
	outputBuf[4]=0x00; // data is length: 00 ->don't data 
	outputBuf[5]=0xFE; // frame of end code -> 0xFE.
    outputBuf[6] = bcc_check(outputBuf,6);


		transferSize=7;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
	
}

/*********************************************************
 * 
 * Function Name:void SendData_Temp_Data(uint8_t tdata)
 * Function:send temperature value 
 * 
*********************************************************/
void SendData_Temp_Data(uint8_t tdata)
{

    outputBuf[0]=0xA5; //display board head = 0xA5
	outputBuf[1]= 0x01; //display device Number:is 0x01
	outputBuf[2]=0x1A; // command type = 0x1A -> temperature of value 
	outputBuf[3]=0x0f; // command order -> 0x0f -> is data , don't order.
	outputBuf[4]=0x01; // data is length: 00 ->don't data 
	outputBuf[5]=tdata; // frame of end code -> 0xFE.
	outputBuf[6]=0xFE; // frame of end code -> 0xFE.
    outputBuf[7] = bcc_check(outputBuf,7);
		
		transferSize=8;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}

}


/********************************************************************************
    **
    *Function Name
    *Function : commad order , data -command type
    *Input Ref: commad order , data -command type
    *Return Ref:NO
    *
*******************************************************************************/
void SendWifiData_Answer_Cmd(uint8_t cmd ,uint8_t data)
{
        outputBuf[0]=0x5A; //display board head = 0xA5
        outputBuf[1]=0x01; //display device Number:is 0x01
        outputBuf[2]=0xFF; // answer or copy command
        outputBuf[3]= cmd; // 0x0F : is data ,don't command order.
        outputBuf[4]= data; // don't data ,onlay is command order,recieve data is 1byte .
       
        outputBuf[5] = 0xFE; //frame is end of byte.
        outputBuf[6] = bcc_check(outputBuf,6);
        
        transferSize=7;
        if(transferSize)
        {
            while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
            transOngoingFlag=1;
            HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
        }
	
}
/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}
	
}

#endif 
