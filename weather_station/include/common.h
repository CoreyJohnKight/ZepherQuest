#ifndef COMMON_H
#define COMMON_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "rtos_config.h"
#include "freertos/semphr.h"
#include "esp_log.h"

// Global Tasks
//=================================
extern TaskHandle_t xReadTask_handle;

// Globals Values
//=================================
extern volatile uint16_t dataValue;

// Global Semaphores
//=================================
extern SemaphoreHandle_t xReadingCompleteSemaphore;

// Global Functions
//=================================
void init_reading_complete_semaphore(void);

#endif