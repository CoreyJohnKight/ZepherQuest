#ifndef COMMON_H
#define COMMON_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "rtos_config.h"

// Global Tasks
//=================================
extern TaskHandle_t xReadTask_handle;

// Globals Values
//=================================
extern volatile uint16_t dataValue;

#endif