/*
 * sen0290.h
 *
 *  Created on: Aug 19, 2025
 *      Author: My PC
 */

#ifndef INC_SEN0290_H_
#define INC_SEN0290_H_

#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal_i2c.h"


static const uint8_t Preset_Default = 0x3c;
static const uint8_t Calib_RCO = 0x3d;
//static uint8_t Direct_Command = 0x96;

static const uint8_t Device_Address = 0x03 << 1;
static const uint8_t Interrupt_Address = 0x03;

typedef struct{
	I2C_HandleTypeDef *i2c_Handle;
	uint8_t* Interrupt_Source;
	uint8_t Direct_Command;
}sen0290_t;



void Wait_sen0290_Until_Ready(void);

void Register_Default_Command(void);

uint8_t  Get_Interrupt_Source(void);

#endif /* INC_SEN0290_H_ */
