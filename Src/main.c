/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gothrough.h"
#include "gray.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void Servo(void);
void Servo_Control(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4, uint16_t pwm5, uint16_t pwm6);
void Servo_AIControl();
void _DATA();
int tim_sign = 0;
unsigned char addr_f = 0, addr_r = 0, addr_l = 0;
uint8_t send[20] = "qrcode";
int HEX(uint8_t x,uint8_t y);
static int Claw_x_1 = 0, Claw_y_1 = 0, Claw_x_2 = 0, Claw_y_2 = 0, Material_x_1 = 0, Material_y_1 = 0, Material_x_2 = 0, Material_y_2 = 0;
uint8_t RxByte_1, RxByte_2;
static uint8_t color_1[10], color_2[10];
static uint8_t RxBuff_1[24], RxBuff_2[24]; //Prevent data errors caused by too few thresholds
static uint8_t Claw_1[24], Claw_2[24]; //Claw coordinates
static uint8_t Material_1[24], Material_2[24]; //block coordinates
uint16_t Rx_Count_1, Rx_Count_2;

static uint8_t pwm1_change = 0, pwm2_change = 0, pwm3_change = 0, pwm4_change = 0, pwm5_change = 0, pwm6_change = 0;
static uint8_t pwm1_standard = 0, pwm2_standard = 0, pwm3_standard = 0, pwm4_standard = 0, pwm5_standard = 0, pwm6_standard = 0;
void Servo_Move_4()
{
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm1_standard);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm2_standard);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm3_standard);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pwm4_standard);
//	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
//	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
}
void Servo_Move_2()
{
//	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, pwm5_standard);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, pwm6_standard);
//	HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
}
//It can only move to a specific angle (it can complete the action in the form of group)
void Servo_Control_4(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4)
{
	while(pwm1_standard !=pwm1 && pwm2_standard != pwm2 && pwm3_standard != pwm3 && pwm4_standard != pwm4)
	{
		Servo_Move_4();
		HAL_Delay_ms(200);
		if(pwm1_standard < pwm1) pwm1_standard++;
		else if(pwm1_standard > pwm1) pwm1_standard--;
		if(pwm2_standard < pwm2) pwm2_standard++;
		else if(pwm2_standard > pwm2) pwm2_standard--;
		if(pwm3_standard < pwm3) pwm3_standard++;
		else if(pwm3_standard > pwm3) pwm3_standard--;
		if(pwm4_standard < pwm4) pwm4_standard++;
		else if(pwm4_standard > pwm4) pwm4_standard--;
	}
}
void Servo_Control_2(uint16_t pwm5, uint16_t pwm6)
{
	while(pwm5_standard != pwm5 && pwm6_standard != pwm6)
	{
		Servo_Move_2();
		HAL_Delay_ms(200);
		if(pwm5_standard < pwm5) pwm5_standard++;
		else if(pwm5_standard > pwm5) pwm5_standard--;
		if(pwm6_standard < pwm6) pwm6_standard++;
		else if(pwm6_standard > pwm6) pwm6_standard--;

	}
}
//if(pwm2++) pwm3--;  else if(pwm2--) pwm3++;
//Used in combination with the coordinates sent back by the camera

void Servo_AIControl()
{
	if(Material_2[0] != 0 || Material_1[0] != 0){
//		&& (pwm1_standard < 45 && pwm2_standard < 90 && pwm3_standard < 90)
		if(((Claw_x_1-Material_x_1) == 20) && ((Claw_x_2-Material_x_2) == 20))
			pwm3_change++;

		if(Claw_x_1 <Material_x_1 && Claw_x_2 < Material_x_2)
			pwm1_change++;
	}
	Servo_Control(pwm1_change, pwm2_change, pwm3_change, pwm4_change, pwm5_change, pwm6_change);
}
//after send "qrcode"
void Color()
{
	if(color_1[2] == color_2[2])
	{
		if((color_1[2]== 0x12) || (color_1[2]== 0x13) || (color_1[2]== 0x32))
		{
			color_1[0] = color_1[2];
			HAL_UART_Transmit_IT(&huart3, color_1, 1);
			HAL_UART_Transmit_IT(&huart6, color_1, 1);
		}
		else
		{
//			HAL_UART_Transmit_IT(huart, pData, Size);
		}
	}
}
//coordinate HEX->DEC
void _DATA(){

	if(Claw_1[0]){
		Claw_x_1 = HEX(Claw_1[2],Claw_1[3]);
		Claw_y_1 = HEX(Claw_1[6],Claw_1[7]);
		Claw_1[0] = 0;
	}
	if(Claw_2[0]){
		Claw_x_2 = HEX(Claw_2[2],Claw_2[3]);
		Claw_y_2 = HEX(Claw_2[6],Claw_2[7]);
		Claw_2[0] = 0;
	}
	if(Material_1[0]){
		Material_x_1 = HEX(Material_1[2],Material_1[3]);
		Material_y_1 = HEX(Material_1[6],Material_1[7]);
		Material_1[0] = 0;
	}
	if(Material_2[0]){
		Material_x_2 = HEX(Material_2[2],Material_2[3]);
		Material_y_2 = HEX(Material_2[6],Material_2[7]);
		Material_2[0] = 0;
	}
}
//Because hexadecimal here is sent in the form of one byte, it can be used directly
int HEX(uint8_t x,uint8_t y){
	int result;
//	int t, k, p;
//	t = x/10;
//	switch(t){
//		case 'A':t = 10;
//		case 'B':t = 11;
//		case 'C':t = 12;
//		case 'D':t = 13;
//		case 'E':t = 14;
//		case 'F':t = 15;
//		default:break;
//	}
//	k = x%10;
//	p = y/100;
//	(k+(t*10))
	result = x+(y*256);
	return result;
}
void HAL_Delay_ms(uint16_t nms)	   //量程0-2000ms
{
		__HAL_TIM_SetCounter(&htim4, 0);//htim4

		__HAL_TIM_ENABLE(&htim4);

		while(__HAL_TIM_GetCounter(&htim4) < (5 * nms));//
		/* Disable the Peripheral */
		__HAL_TIM_DISABLE(&htim4);
}
void front_move(uint16_t pos, uint16_t dat)
{
	if(Gray_F() == 1 && Gray_L() == 1)
	{
		if(pos)
			forward();
		else
			retreat();
		HAL_Delay(200);
		while(dat)
		{
			if(Gray_F() == 1)
			{
				dat--;
				HAL_Delay(200);
			}
		}
		stop();
	}
}
//void back_move(uint16_t dat)
//{
//	if(Gray_F() == 1 && Gray_L() == 1)
//	{
//		retreat();
//		HAL_Delay(200);
//		while(dat)
//		{
//			if(Gray_F() == 1)
//			{
//				dat--;
//				HAL_Delay_ms(200);
//			}
//		}
//		stop();
//	}
//}
void left_move(uint16_t pos, uint16_t dat)
{
	if(Gray_F() == 1 && Gray_L() == 1)
	{
		if(pos)
			left();
		else
			right();
		HAL_Delay_ms(200);
		tim_sign = 2;
		while(dat)
		{
			if(Gray_L())
			{
				dat--;
				HAL_Delay_ms(200);
			}
		}
		stop();
		tim_sign = 0;
	}
}
//void right_move(uint16_t dat)
//{
//	if(Gray_F() == 1 && Gray_L() == 1)
//	{
//		right();
//		HAL_Delay(200);
//		tim_sign = 2;
//		while(dat)
//		{
//			if(Gray_L()){
//				dat--;
//				HAL_Delay(200);
//			}
//		}
//		stop();
//		tim_sign = 0;
//	}
//}
void right_move_all()
{
	if(Gray_F() == 1 && Gray_L() == 1)
	{
		right();
		HAL_Delay(200);
		tim_sign = 2;
		if(Gray_F())
			HAL_Delay(200);
		stop();
		tim_sign = 0;
	}
}
void round_move()
{
	stop();
}

void claw_1()
{
	Servo_Control_4(24, 25, 12, 25);
	Servo_Control_2(25, 22);
}
void claw_flod()
{
	Servo_Control_4(15, 5, 25, 5);
}
void claw_run()
{
	claw_1();
	HAL_Delay(1000);
	claw_flod();
	HAL_Delay(1000);
//	Servo_Control_2(5,5);
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 25);
}
void choosecolor()
{
	if(send[0] == 1)
		send[0] = 2;
	else
		send[0] = 1;
	for(int i = 0; i < 4; i++)
		HAL_UART_Transmit_IT(&huart6, send, 1);
	HAL_Delay_ms(20);
	while(Material_1[0] != 0)
	{
		while(Material_1[0] <240 && Material_1[0] > 103)
			claw_run();
		right_move_all();
	}
	right_move_all();
	if(addr_f == 7 || addr_f == 10)
	{
		left_move(1, 2);
		choosecolor();
	}
}
void send_sth(uint8_t *str)
{

	HAL_UART_Transmit_IT(&huart6, (uint8_t *)send, sizeof(send));
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	/* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_USART6_UART_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart6, &RxByte_2, 1);
//HAL_UART_Receive_IT(&huart2, &RxByte_2, 1);
  HAL_UART_Receive_IT(&huart3, &RxByte_2, 1);
  HAL_UART_Receive_IT(&huart1, &RxByte_1, 1);
  HAL_TIM_Base_Start(&htim2);
//  HAL_TIM_Base_Stop(&htim1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
//  Servo_Control(10,10,11,10,15,10);
//  HAL_Delay_ms(1000);

//tim 1 :24, 25, 12, 5  tim 3: 20, 10   best long
//tim 1 :15, 25, 5, 5  tim 3: 20, 10   zhe die
//  Servo_Control(25, 5, 20, 5, 10, 5);//3.2
//  stop();
//  pwm(50);
//	Servo_Control_4(7,7,7,7);
//   Servo_Control_2(20,20);
//
//	translational();
//	pwm(20);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 25);//1
////	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 10);//2
//	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 10);//3
////	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 5);//4
//	  HAL_Delay(2000);
//	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 25);
////	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 20);
//	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 20);
////	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 24);
//	  HAL_Delay(2000);
	  Servo_Control_4(20, 20, 20, 5);
	  HAL_Delay(2000);
	  Servo_Control_4(6, 6, 6, 25);
	  HAL_Delay(2000);
//	  claw_run();



//	claw_run();
////	  HAL_Delay(100);
//	  if(Gray_B())
//	  {
//		  forward();
//		  pwm(40);
//	  }
//	  else
//	  {
//		  stop();
//
//	  }
//	  Claw_1[0] = 0xac;
//	  Claw_1[2] = 0x32;
//	  Claw_1[3] = 0x01;
//      Claw_1[6] = 0x2d;
//	  Claw_1[7] = 0x00;
//	  _DATA();
//	  color_1[2] == 0x12;
//	 if(!(addr_f && addr_l && addr_r))
//	 {
//		 front_move(2);
//		 char send[] = "qrcode";
//		 for(int i = 0; i < 4; i++)
//			HAL_UART_Transmit_IT(&huart6, send, 6);
//		 left_move(1);
//	 }
//
//	 front_move(2);
//	 send[20] = "colorchoose";
//	 for(int i = 0; i < 4; i++)
//		 while(HAL_UART_Transmit_IT(&huart6, send, 10) == HAL_OK);
//	 send[0] = 1;
//	 for(int i = 0; i < 4; i++)
//		 while(HAL_UART_Transmit_IT(&huart6, send, 10) == HAL_OK);
//	 front_move(2);
//	 send[20] ='TargetBlot';
//	 for(int i = 0; i < 4; i++)
//		while(HAL_UART_Transmit_IT(&huart6, send, 10) == HAL_OK);
//	 //抓取物料A_1
//	 send[0] = 1;
//	 for(int i = 0; i < 4; i++)
//		 while(HAL_UART_Transmit_IT(&huart6, send, 10) == HAL_OK);
//	 front_move(1);
//	 send[11] = "T";
//	 for(int i = 0; i < 4; i++)
//		 while(HAL_UART_Transmit_IT(&huart6, send, 10) == HAL_OK);
//	 //抓取物料A_2
//	 front_move(1);
//	 round_move();
//	 front_move(3);
//	 send[0] = 1;
//	 for(int i = 0; i < 4; i++)
//		 while(HAL_UART_Transmit_IT(&huart6, send, 10) == HAL_OK);
//	 front_move(2);
//	 send[10] = "TargetBlot";
//	 for(int i = 0; i < 4; i++)
//		 while(HAL_UART_Transmit_IT(&huart6, send, 10) == HAL_OK);
//	 if(Material_1[1] < 200)
//		 send[0] = 2;
//
//	 //抓取物料B_1
//	 send[6] = 2;
//	 for(int i = 0; i < 4; i++)
//		HAL_UART_Transmit_IT(&huart6, send, 1);
//	 front_move(1);
//	 send[10] = "TargetBlot";
//	 for(int i = 0; i < 4; i++)
//		HAL_UART_Transmit_IT(&huart6, send, 10);
//	 //抓取物料B_2
//	 round_move();
//	 //拼接
//	 front_move(5);
//	 round_move();
////	 抓取物料C_1
////	 抓取物料C_2
////	 拼接
//	 front_move(4);
//	 right();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
}

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void TIM_EXTI()
{
	if(!(Gray_F() && Gray_B()))
		retreat();
	else if(Gray_B())
		forward();
}
void  HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)    //定时器中断回调函�?
{
	if(htim == &htim6)   //确定是定时器6产生的中�?
	{

		if(tim_sign == 2){
			stop();
			TIM_EXTI();
		}
		if(Gray_F())
			addr_f++;
		if(Gray_B())
			addr_f--;
		if(Gray_L())
		{
			if(wheel_LBB_Pin == GPIO_PIN_RESET)
				addr_r++;
			else
				addr_r--;
		}

	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
			the HAL_UART_RxCpltCallback can be implemented in the user file
   */
    if(huart->Instance == USART6){ //second camera
		int i = 0;
//		int t = 0;
//		char color_arr = 't';
		RxBuff_2[Rx_Count_2++]=RxByte_2;
		if(RxByte_2==0x0A)
		{
//			while(HAL_UART_Transmit_IT(&huart6, RxBuff_2, Rx_Count_2) == HAL_OK);
			if(RxBuff_2[0] == 0xde && RxBuff_2[1]==0x23 && RxBuff_2[10] == 0x0A){ //Get the claw coordinates
				for(i = 0;i<Rx_Count_2;i++) Claw_2[i] = RxBuff_2[i];
				_DATA();
			}
			else if(RxBuff_2[0] == 0xaC && RxBuff_2[1]==0xbe && RxBuff_2[10] == 0x0A){ //Get the block coordinates
				for(i = 0;i<Rx_Count_2;i++) Material_2[i] = RxBuff_2[i];
				_DATA();
			}
			else if(RxBuff_2[0] == 0x12 && RxBuff_2[1]==0x79 && RxBuff_2[10] == 0x0A){
				for(i = 0;i<Rx_Count_2;i++) color_2[i] = RxBuff_2[i];
			}
				Rx_Count_2=0;
		}
	/*	if(RxByte_2 == color_arr)
		{
			for(i = 0;i<(Rx_Count_2-1);i++) {color_2[t] = RxBuff_2[i]; t++;
				while(HAL_UART_Transmit_IT(&huart6, color_2, t) == HAL_OK);
				if(t>=10) t = 0;
			}

		}
	*/
		while(HAL_UART_Receive_IT(&huart6, &RxByte_2, 1)==HAL_OK);
//		if(Claw_2[0] == 0xac && Claw_2[1]==0x23 && Claw_2[10] == 0x0A )
//			HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
//			while(HAL_UART_Receive_IT(&huart6, &RxByte_2, 1)==HAL_OK);
	}
  	if(huart->Instance == USART1)  //判断是否串口1 first camera
	{
  		int i = 0;
//  		int t = 0;
//  		char color_arr = 't';
		RxBuff_1[Rx_Count_1++]=RxByte_1;
		if( RxByte_1==0x0A)
		{
//			while(HAL_UART_Transmit_IT(&huart1, RxBuff_1, Rx_Count_1) == HAL_OK);
			if(RxBuff_1[0] == 0xac && RxBuff_1[1]==0x23 && RxBuff_1[10] == 0x0A){
				for(i = 0;i<Rx_Count_1;i++) Claw_1[i] = RxBuff_1[i];
				_DATA();
//				while(HAL_UART_Transmit_IT(&huart1, Material_2, 1) == HAL_OK);
			}
			else if(RxBuff_1[0] == 0xaC && RxBuff_1[1] == 0xbe && RxBuff_1[10] == 0x0A){
				for(i = 0;i<Rx_Count_1;i++) Material_1[i] = RxBuff_1[i];
				_DATA();
			}
			else if(RxBuff_1[0] == 0x12 && RxBuff_1[1] == 0x79 && RxBuff_1[10] == 0x0A){
				for(i = 0;i<Rx_Count_1;i++) color_1[i] = RxBuff_1[i];
			}
			Rx_Count_1=0;
		}
//		/*
//		if(RxByte_2 == color_arr)
//		{
//			for(i = 0;i<(Rx_Count_1-1);i++) {color_1[t] = RxBuff_1[i]; t++;
//			if(t>=10) t = 0;
//			while(HAL_UART_Transmit_IT(&huart1, color_1, t) == HAL_OK);
//			}
//			Rx_Count_1 = 0;
//		}
//		*/
		while(HAL_UART_Receive_IT(&huart1, &RxByte_1, 1) == HAL_OK);
//		if(Claw_1[0] == 0xac && Claw_1[1]==0x23 && Claw_1[10] == 0x0A && Claw_1[2] == 0x7D)

//			HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
//			while(HAL_UART_Receive_IT(&huart1, &RxByte_1, 1)==HAL_OK);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

