/*
 * SEN0290.c
 *
 *  Created on: Aug 27, 2025
 *      Author: John Carlo Carbonel
 *      Steps on DFROBOT Library
 *      1. Reset by writing Preset_Default = 0x3C with 0x96
 *      2. Manual calibration
 *      	a. Set outdoors/indoor location of sensor
 *      	b. Enable or disable disturber
 *      	c. Set interrupt source
 *      	d. Set capacitance
 *      	e. Print Calibration complete
 */

#include "SEN0290.h"

extern SEN0290_t SEN0290;

void Assign_SEN0290_I2C_Handler(I2C_HandleTypeDef *hi2c)
{
	SEN0290.I2C_Handle = hi2c;
}

void Assign_SEN0290_UART_Handler(UART_HandleTypeDef *hUART)
{
	SEN0290.UART_Handle = hUART;
}

uint8_t Wait_SEN0290_Until_Ready(void)
{
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(SEN0290.I2C_Handle, Device_Address, 3, HAL_MAX_DELAY);

    if (ret == HAL_OK)
    {
    	return 8;
    }
    return 0;
}

uint8_t Register_Default_Command(void)
{
	uint8_t Direct_Command = 0x96;
	HAL_I2C_Mem_Write(SEN0290.I2C_Handle, Device_Address, Preset_Default, 1, &Direct_Command, 1, HAL_MAX_DELAY);

	HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(SEN0290.I2C_Handle, Device_Address, Calib_RCO, 1, &Direct_Command, 1, HAL_MAX_DELAY);

	if (ret == HAL_OK)
	{
		return 9;
	}
	 return 0;
}


uint8_t Read_SEN0290_Distance_Register(void)
{
	HAL_I2C_Mem_Read(SEN0290.I2C_Handle, Device_Address, SEN0290_Distance_Register, 1, &SEN0290.SEN0290_Distance_Value, 1, HAL_MAX_DELAY);
	return SEN0290.SEN0290_Distance_Value;
}

uint8_t Read_SEN0290_Interrupt_Source(void)
{
	HAL_I2C_Mem_Read(SEN0290.I2C_Handle, Device_Address, Interrupt_Source, 1, &SEN0290.SEN0290_Distance_Value, 1, HAL_MAX_DELAY);
	return SEN0290.SEN0290_Distance_Value;
}

uint8_t Interpret_SEN0290_Interrupt(void)
{
	uint8_t irq;
	irq = Read_SEN0290_Interrupt_Source();
	sprintf((char *)SEN0290.Interrupt_Message, "Interrupt Source: %d\r\n", irq);
	HAL_UART_Transmit(SEN0290.UART_Handle, SEN0290.Interrupt_Message, strlen((char *)SEN0290.Interrupt_Message), HAL_MAX_DELAY);
	HAL_Delay(100);
	if (irq == 1)
	{
		sprintf((char *)SEN0290.Interrupt_Message, "Noise level too high!\r\n");
		HAL_UART_Transmit(SEN0290.UART_Handle, SEN0290.Interrupt_Message, strlen((char *)SEN0290.Interrupt_Message), HAL_MAX_DELAY);
		HAL_Delay(100);
	}
	else if (irq == 4)
	{
		sprintf((char *)SEN0290.Interrupt_Message, "Disturber detected!\r\n");
		HAL_UART_Transmit(SEN0290.UART_Handle, SEN0290.Interrupt_Message, strlen((char *)SEN0290.Interrupt_Message), HAL_MAX_DELAY);
		HAL_Delay(100);
	}
	else if (irq == 8)
	{
		sprintf((char *)SEN0290.Interrupt_Message, "Lightning Interrupt!\r\n");
		HAL_UART_Transmit(SEN0290.UART_Handle, SEN0290.Interrupt_Message, strlen((char *)SEN0290.Interrupt_Message), HAL_MAX_DELAY);
		HAL_Delay(100);
	}


	return 0;
}
