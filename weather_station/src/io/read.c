#include "io/read.h"

extern volatile u_int16_t dataValue;
extern SemaphoreHandle_t xReadingCompleteSemaphore;

static const char *TAG_READER = "data reader";

/* Reading from the field sensors.
 * This task gets woken by the HTTP server when a GET request is made.
 * It should update the global values, then pass back the semaphore.
 *
 * TODO: STUB
 * For now it is only updating a counter with each read.
 * Once the sensor hardware is configured, this should read from the sensors.
 */
void io_read_task(void *vParam)
{
    while (1)
    {
        ESP_LOGI(TAG_READER, "Going to sleep.");
        // Wait for the semaphore to be given (unblocked by /hello request)
        if (xSemaphoreTake(xReadingCompleteSemaphore, portMAX_DELAY) == pdTRUE)
        {
            // I have awoken!
            ESP_LOGI(TAG_READER, "Reading data...");
            dataValue++;

            // Done reading, give the semaphore back to signal completion
            xSemaphoreGive(xReadingCompleteSemaphore);

            ESP_LOGI(TAG_READER, "Done!");
        }
        else
        {
            ESP_LOGI(TAG_READER, "Error waiting to be woken by server.");
        }
    }
}