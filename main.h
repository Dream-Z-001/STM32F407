/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
void HAL_Delay_ms(uint16_t nms);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define gray_BC_Pin GPIO_PIN_2
#define gray_BC_GPIO_Port GPIOE
#define gray_BA_Pin GPIO_PIN_3
#define gray_BA_GPIO_Port GPIOE
#define gray_BB_Pin GPIO_PIN_4
#define gray_BB_GPIO_Port GPIOE
#define Wheel_1_Pin GPIO_PIN_0
#define Wheel_1_GPIO_Port GPIOA
#define wheel_RFB_Pin GPIO_PIN_1
#define wheel_RFB_GPIO_Port GPIOA
#define gray_FC_Pin GPIO_PIN_2
#define gray_FC_GPIO_Port GPIOA
#define gray_FB_Pin GPIO_PIN_3
#define gray_FB_GPIO_Port GPIOA
#define wheel_RFA_Pin GPIO_PIN_4
#define wheel_RFA_GPIO_Port GPIOA
#define gray_FD_Pin GPIO_PIN_5
#define gray_FD_GPIO_Port GPIOA
#define servo_5_Pin GPIO_PIN_6
#define servo_5_GPIO_Port GPIOA
#define servo_6_Pin GPIO_PIN_7
#define servo_6_GPIO_Port GPIOA
#define wheel_RBA_Pin GPIO_PIN_2
#define wheel_RBA_GPIO_Port GPIOB
#define servo_1_Pin GPIO_PIN_9
#define servo_1_GPIO_Port GPIOE
#define servo_2_Pin GPIO_PIN_11
#define servo_2_GPIO_Port GPIOE
#define servo_3_Pin GPIO_PIN_13
#define servo_3_GPIO_Port GPIOE
#define LED_2_Pin GPIO_PIN_14
#define LED_2_GPIO_Port GPIOE
#define Wheel_3_Pin GPIO_PIN_10
#define Wheel_3_GPIO_Port GPIOB
#define Wheel_4_Pin GPIO_PIN_11
#define Wheel_4_GPIO_Port GPIOB
#define wheel_LBA_Pin GPIO_PIN_12
#define wheel_LBA_GPIO_Port GPIOB
#define wheel_LBB_Pin GPIO_PIN_13
#define wheel_LBB_GPIO_Port GPIOB
#define gray_LB_Pin GPIO_PIN_14
#define gray_LB_GPIO_Port GPIOB
#define gray_LE_Pin GPIO_PIN_15
#define gray_LE_GPIO_Port GPIOB
#define gray_FE_Pin GPIO_PIN_8
#define gray_FE_GPIO_Port GPIOA
#define servo_4_Pin GPIO_PIN_11
#define servo_4_GPIO_Port GPIOA
#define gray_FA_Pin GPIO_PIN_12
#define gray_FA_GPIO_Port GPIOA
#define Wheel_2_Pin GPIO_PIN_3
#define Wheel_2_GPIO_Port GPIOB
#define wheel_RBB_Pin GPIO_PIN_4
#define wheel_RBB_GPIO_Port GPIOB
#define gray_LA_Pin GPIO_PIN_5
#define gray_LA_GPIO_Port GPIOB
#define gray_LC_Pin GPIO_PIN_6
#define gray_LC_GPIO_Port GPIOB
#define gray_LD_Pin GPIO_PIN_7
#define gray_LD_GPIO_Port GPIOB
#define wheel_LFB_Pin GPIO_PIN_8
#define wheel_LFB_GPIO_Port GPIOB
#define wheel_LFA_Pin GPIO_PIN_9
#define wheel_LFA_GPIO_Port GPIOB
#define gray_BE_Pin GPIO_PIN_0
#define gray_BE_GPIO_Port GPIOE
#define gray_BD_Pin GPIO_PIN_1
#define gray_BD_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
