#include "common.h"

#include "comms/comms.h"
#include "io/io.h"

extern SemaphoreHandle_t xReadingCompleteSemaphore;
static const char *TAG_MAIN = "APP MAIN";

void exit_program();

// MAIN
void app_main()
{
    // Create the read semaphore
    init_reading_complete_semaphore();

    if (xReadingCompleteSemaphore)
    {
        ESP_LOGI(TAG_MAIN, "Initializing CORE tasks");

        // Pin the main tasks to each core

        BaseType_t commsTaskResult = xTaskCreatePinnedToCore(&comms, "Comms Main", config_STACK_DEFAULT * 4, NULL, configMAX_PRIORITIES - 1, NULL, APP_CPU_NUM);
        if (!commsTaskResult)
        {
            // End the program if task creation
            ESP_LOGI(TAG_MAIN, "Initialization error - comms task was not created");
            exit_program();
        }

        BaseType_t ioTaskResult = xTaskCreatePinnedToCore(&io, "Sensor Main", config_STACK_DEFAULT, NULL, configMAX_PRIORITIES - 2, NULL, PRO_CPU_NUM);
        if (!ioTaskResult)
        {
            // End the program if task creation
            ESP_LOGI(TAG_MAIN, "Initialization error - IO task was not created");
            exit_program();
        }
    }
    else
    {
        // End the program if the semaphore failed
        ESP_LOGI(TAG_MAIN, "Initialization error - Semaphore was null");
        exit_program();
    }
}

void exit_program()
{
    // Restart the ESP device to exit the program
    esp_restart();
}