#include "common.h"

volatile uint16_t dataValue = 0;
TaskHandle_t xReadTask_handle = NULL;

SemaphoreHandle_t xReadingCompleteSemaphore = NULL;

void init_reading_complete_semaphore(void)
{
    xReadingCompleteSemaphore = xSemaphoreCreateBinary();
}