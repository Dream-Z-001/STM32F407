/*
 * gray.c
 *
 *  Created on: Mar 9, 2022
 *      Author: CY
 */
#include "main.h"
int gray[5];
int choose(int array[5])
{
    for (int i = 0; i < 3; i++)
        for (int y = i + 1; y < 4; y++)
            if ((array[i] == array[y]) == 1)
                for (int z = y + 1; z < 5; z++)
                    if ((array[y] == array[z]) == 1)
                        return 1;
    return 0;
}

int Gray_B(char array[5])
{
	int k;
	array[0]= HAL_GPIO_ReadPin( gray_BA_GPIO_Port, gray_BA_Pin);
	array[1]= HAL_GPIO_ReadPin( gray_BB_GPIO_Port, gray_BB_Pin);
	array[2]= HAL_GPIO_ReadPin( gray_BC_GPIO_Port, gray_BC_Pin);
	array[3]= HAL_GPIO_ReadPin( gray_BD_GPIO_Port, gray_BD_Pin);
	array[4]= HAL_GPIO_ReadPin( gray_BE_GPIO_Port, gray_BE_Pin);
    k = choose(gray);
    return k;
}

int Gray_L(char array[5])
{
	int k;
	array[0]= HAL_GPIO_ReadPin( gray_LA_GPIO_Port, gray_LA_Pin);
	array[1]= HAL_GPIO_ReadPin( gray_LB_GPIO_Port, gray_LB_Pin);
	array[2]= HAL_GPIO_ReadPin( gray_LC_GPIO_Port, gray_LC_Pin);
	array[3]= HAL_GPIO_ReadPin( gray_LD_GPIO_Port, gray_LD_Pin);
	array[4]= HAL_GPIO_ReadPin( gray_LE_GPIO_Port, gray_LE_Pin);
    k = choose(gray);
	return k;
}

int Gray_F(char array[5])
{
	int k;
	array[0]= HAL_GPIO_ReadPin( gray_FA_GPIO_Port, gray_FA_Pin);
	array[1]= HAL_GPIO_ReadPin( gray_FB_GPIO_Port, gray_FB_Pin);
	array[2]= HAL_GPIO_ReadPin( gray_FC_GPIO_Port, gray_FC_Pin);
	array[3]= HAL_GPIO_ReadPin( gray_FD_GPIO_Port, gray_FD_Pin);
	array[4]= HAL_GPIO_ReadPin( gray_FE_GPIO_Port, gray_FE_Pin);
    k = choose(gray);
	return k;
}
