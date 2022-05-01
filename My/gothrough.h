/*
 * gothrough.h
 *
 *  Created on: Mar 9, 2022
 *      Author: CY
 */

#ifndef CY_GOTHROUGH_H_
#define CY_GOTHROUGH_H_
#include"stm32f4xx_hal.h"

void forward();
void retreat();
void translational();
void right();
void left();
void stop();
void pwm_Achieve(uint8_t pwm);
void pwm(uint8_t pwm);
#endif /* CY_GOTHROUGH_H_ */
