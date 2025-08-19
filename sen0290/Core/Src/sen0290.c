/*
 * sen0290.c
 *
 *  Created on: Aug 19, 2025
 *      Author: My PC
 */


#include "sen0290.h"


//volatile int8_t AS3935IsrTrig = 0;

extern sen0290_t sen0290;

void Wait_sen0290_Until_Ready(void){
	HAL_I2C_IsDeviceReady(sen0290.i2c_Handle, Device_Address, 3, HAL_MAX_DELAY);
}

void Register_Default_Command(void){
	sen0290.Direct_Command = 0x96;
	HAL_I2C_Mem_Write(sen0290.i2c_Handle, Device_Address, Preset_Default, sizeof(Preset_Default), &sen0290.Direct_Command,  sizeof(sen0290.Direct_Command), HAL_MAX_DELAY);
	HAL_I2C_Mem_Write(sen0290.i2c_Handle, Device_Address, Calib_RCO, sizeof(Calib_RCO), &sen0290.Direct_Command,  sizeof(sen0290.Direct_Command), HAL_MAX_DELAY);
}

uint8_t Get_Interrupt_Source(void){
	HAL_I2C_Mem_Read(sen0290.i2c_Handle, Device_Address, Interrupt_Address, sizeof(Interrupt_Address), sen0290.Interrupt_Source, sizeof(sen0290.Interrupt_Source), HAL_MAX_DELAY);

	if(0x08 == *sen0290.Interrupt_Source){
	    return 1;                    // lightning caused interrupt
	}

	else if(0x04 == *sen0290.Interrupt_Source){
	    return 2;                    // disturber detected
	}
	else if(0x01 == *sen0290.Interrupt_Source){
	    return 3;                    // Noise level too high
	}
	else{
	    return 0;
	}                    // interrupt result not expected
}


