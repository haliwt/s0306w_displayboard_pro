/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SMG_POWER_Pin GPIO_PIN_1
#define SMG_POWER_GPIO_Port GPIOA

#define TM1639_STB_Pin GPIO_PIN_4
#define TM1639_STB_GPIO_Port GPIOA

#define M1639_DIO_Pin GPIO_PIN_5
#define M1639_DIO_GPIO_Port GPIOA

#define TM1639_SCLK_Pin GPIO_PIN_6
#define TM1639_SCLK_GPIO_Port GPIOA


#define TIME_LED_EN_Pin GPIO_PIN_14
#define TIME_LED_EN_GPIO_Port GPIOB



#define PLASMA_LED_EN_Pin GPIO_PIN_8
#define PLASMA_LED_EN_GPIO_Port GPIOA

#define DRY_LED_EN_Pin GPIO_PIN_9
#define DRY_LED_EN_GPIO_Port GPIOA

#define WIFI_LED_EN_Pin GPIO_PIN_6
#define WIFI_LED_EN_GPIO_Port GPIOC

//FAN GPIO


#define MOUSE_LED_Pin                 GPIO_PIN_15
#define MOUSE_LED_GPIO_Port            GPIOB



#if 0
//KEY GPIO

#define AI_KEY_Pin 					        GPIO_PIN_10
#define WIFI_KEY_GPIO_Port 			        GPIOB

#define DRY_KEY_Pin                         GPIO_PIN_2
#define DRY_KEY_GPIO_Port                   GPIOB

#define POWER_KEY_Pin                       GPIO_PIN_7
#define POWER_KEY_GPIO_Port                 GPIOC

#define MODEL_KEY_Pin                       GPIO_PIN_10
#define MODEL_KEY_GPIO_Port                 GPIOA

#define DEC_KEY_Pin                         GPIO_PIN_11
#define DEC_KEY_GPIO_Port                   GPIOA

#define ADD_KEY_Pin                         GPIO_PIN_12
#define ADD_KEY_GPIO_Port                   GPIOA

#define PLASMA_KEY_Pin 					     GPIO_PIN_1
#define PLASMA_KEY_GPIO_Port 			     GPIOB


#define MOUSE_KEY_Pin 					        GPIO_PIN_0
#define MOUSE_KEY_GPIO_Port 				        GPIOB
#endif 

//KEY INPUT GPIO

#define MOUSE_KEY_Pin                       GPIO_PIN_0  //? 
#define MOUSE_KEY_GPIO_Port                 GPIOB
#define MOUSE_KEY_EXTI_IRQn                 EXTI0_1_IRQn

#define PLASMA_KEY_Pin                      GPIO_PIN_1
#define PLASMA_KEY_GPIO_Port                GPIOB
#define PLASMA_KEY_EXTI_IRQn                EXTI0_1_IRQn

#define DRY_KEY_Pin                         GPIO_PIN_2
#define DRY_KEY_GPIO_Port                   GPIOB
#define DRY_KEY_EXTI_IRQn                   EXTI2_3_IRQn


#define AI_KEY_Pin                          GPIO_PIN_10 // ? 
#define AI_KEY_GPIO_Port                    GPIOB
#define AI_KEY_EXTI_IRQn                    EXTI4_15_IRQn



#define POWER_KEY_Pin                       GPIO_PIN_7
#define POWER_KEY_GPIO_Port                 GPIOC
#define POWER_KEY_EXTI_IRQn                 EXTI4_15_IRQn


#define MODEL_KEY_Pin                       GPIO_PIN_10
#define MODEL_KEY_GPIO_Port                 GPIOA
#define MODEL_KEY_EXTI_IRQn                 EXTI4_15_IRQn

#define DEC_KEY_Pin                         GPIO_PIN_11
#define DEC_KEY_GPIO_Port                   GPIOA
#define DEC_KEY_EXTI_IRQn                   EXTI4_15_IRQn

#define ADD_KEY_Pin                         GPIO_PIN_12
#define ADD_KEY_GPIO_Port                   GPIOA
#define ADD_KEY_EXTI_IRQn                   EXTI4_15_IRQn






#define TOUCH_KEY_IC_1_Pin                  		GPIO_PIN_13
#define TOUCK_KEY_IC_1_GPIO_Port              		GPIOC

#define TOUCH_KEY_IC_2_Pin                   GPIO_PIN_14
#define TOUCK_KEY_IC_2_GPIO_Port             GPIOC





//#define AI_KEY_Pin GPIO_PIN_10
//#define WIFI_KEY_GPIO_Port GPIOB

//LED OF KEY GPIO
#define LED_POWER_Pin                           GPIO_PIN_12
#define LED_POWER_GPIO_Port                     GPIOB




/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
