#include "common.h"

#include "comms/comms.h"
#include "io/io.h"

extern SemaphoreHandle_t xReadingCompleteSemaphore;

static const char *TAG_MAIN = "APP MAIN";

void app_main()
{
    init_reading_complete_semaphore();

    // Initialize the semaphore
    if (xReadingCompleteSemaphore)
    {
        ESP_LOGI(TAG_MAIN, "Initializing CORE tasks");

        // Pin the main tasks to each core
        xTaskCreatePinnedToCore(&comms, "Comms Main", config_STACK_DEFAULT * 4, NULL, configMAX_PRIORITIES - 1, NULL, APP_CPU_NUM);
        xTaskCreatePinnedToCore(&io, "Sensor Main", config_STACK_DEFAULT, NULL, configMAX_PRIORITIES - 2, NULL, PRO_CPU_NUM);
    }
    else
    {
        ESP_LOGI(TAG_MAIN, "Initialization error");
    }
}
