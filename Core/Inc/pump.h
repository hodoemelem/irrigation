/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : pump.h
  * @brief          : Header for pump.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#ifndef __PUMP_H
#define __PUMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


#define MAX_PUMPS 1          // Number of pumps in the system

#define PUMP_ON_DELAY  2500 //ms
#define PUMP_OFF_DELAY 30000//ms  //14400000

//jqc-3ff-s-z relay is active low
#define PUMP_RELAY_ON GPIO_PIN_RESET
#define PUMP_RELAY_OFF GPIO_PIN_SET

void irrigation_init(void);
void irrigation_run(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __PUMP_H */
