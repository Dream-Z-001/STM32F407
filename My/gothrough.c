/*
 * gothrough.c
 *
 *  Created on: Mar 9, 2022
 *      Author: CY
 */

#include "main.h"
#include "tim.h"
#include "gothrough.h"
//Wheel rotation mode in various motion states
void forward() //qianjin
{
	HAL_GPIO_WritePin(wheel_RFA_GPIO_Port, wheel_RFA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_RFB_GPIO_Port, wheel_RFB_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(wheel_LFA_GPIO_Port, wheel_LFA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LFB_GPIO_Port, wheel_LFB_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(wheel_RBA_GPIO_Port, wheel_RBA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_RBB_GPIO_Port, wheel_RBB_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(wheel_LBA_GPIO_Port, wheel_LBA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LBB_GPIO_Port, wheel_LBB_Pin, GPIO_PIN_SET);
}
void retreat()  //houtui
{
	HAL_GPIO_WritePin(wheel_RFA_GPIO_Port, wheel_RFA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_RFB_GPIO_Port, wheel_RFB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LFA_GPIO_Port, wheel_LFA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_LFB_GPIO_Port, wheel_LFB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_RBA_GPIO_Port, wheel_RBA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_RBB_GPIO_Port, wheel_RBB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LBA_GPIO_Port, wheel_LBA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_LBB_GPIO_Port, wheel_LBB_Pin, GPIO_PIN_RESET);
}
void translational()  //shunshixuanzhuan
{
	HAL_GPIO_WritePin(wheel_RFA_GPIO_Port, wheel_RFA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_RFB_GPIO_Port, wheel_RFB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LFA_GPIO_Port, wheel_LFA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LFB_GPIO_Port, wheel_LFB_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(wheel_RBA_GPIO_Port, wheel_RBA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_RBB_GPIO_Port, wheel_RBB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LBA_GPIO_Port, wheel_LBA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LBB_GPIO_Port, wheel_LBB_Pin, GPIO_PIN_SET);
}
void right() //xiangyoupingyi
{
	HAL_GPIO_WritePin(wheel_RFA_GPIO_Port, wheel_RFA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_RFB_GPIO_Port, wheel_RFB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LFA_GPIO_Port, wheel_LFA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LFB_GPIO_Port, wheel_LFB_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(wheel_RBA_GPIO_Port, wheel_RBA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_RBB_GPIO_Port, wheel_RBB_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(wheel_LBA_GPIO_Port, wheel_LBA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_LBB_GPIO_Port, wheel_LBB_Pin, GPIO_PIN_RESET);
}
void left() //xiangzuopingyi
{
	HAL_GPIO_WritePin(wheel_RFA_GPIO_Port, wheel_RFA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_RFB_GPIO_Port, wheel_RFB_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(wheel_LFA_GPIO_Port, wheel_LFA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_LFB_GPIO_Port, wheel_LFB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_RBA_GPIO_Port, wheel_RBA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(wheel_RBB_GPIO_Port, wheel_RBB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LBA_GPIO_Port, wheel_LBA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LBB_GPIO_Port, wheel_LBB_Pin, GPIO_PIN_SET);
}
void stop()
{
	HAL_GPIO_WritePin(wheel_RFA_GPIO_Port, wheel_RFA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_RFB_GPIO_Port, wheel_RFB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LFA_GPIO_Port, wheel_LFA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LFB_GPIO_Port, wheel_LFB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_RBA_GPIO_Port, wheel_RBA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_RBB_GPIO_Port, wheel_RBB_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(wheel_LBA_GPIO_Port, wheel_LBA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(wheel_LBB_GPIO_Port, wheel_LBB_Pin, GPIO_PIN_RESET);
}
void pwm_Achieve(uint8_t pwm)
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, pwm);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm);
}
void pwm(uint8_t pwm)
{
	int i = 0;
	while(i<pwm)
	{
		pwm_Achieve(i);
		HAL_Delay_ms(200);
		i++;
	}
}
