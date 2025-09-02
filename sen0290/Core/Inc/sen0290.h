/*
 * SEN0290.h
 *
 *  Created on: Aug 27, 2025
 *      Author: My PC
 */

#ifndef INC_SEN0290_H_
#define INC_SEN0290_H_


#include "main.h"
#include "stm32f4xx_hal_i2c.h"
#include <stdio.h>
#include <string.h>

#define Device_Address (0x0003<<1)
#define Preset_Default 0x003c
#define Calib_RCO 0x003d
#define SEN0290_Distance_Register 0x0007
#define Interrupt_Source 0x0003

typedef struct
{
	I2C_HandleTypeDef *I2C_Handle;
	UART_HandleTypeDef *UART_Handle;
	uint8_t SEN0290_Distance_Value;
	uint8_t Interrupt_Message[40];
}SEN0290_t;

void Assign_SEN0290_I2C_Handler(I2C_HandleTypeDef *hi2c);
uint8_t Wait_SEN0290_Until_Ready(void);
uint8_t Register_Default_Command(void);
uint8_t Read_SEN0290_Distance_Register(void);
uint8_t Read_SEN0290_Interrupt_Source(void);
uint8_t Interpret_SEN0290_Interrupt(uint8_t irq);

#endif /* INC_SEN0290_H_ */
