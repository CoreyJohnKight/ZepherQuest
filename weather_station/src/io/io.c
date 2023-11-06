#include "io/io.h"

#include "io/read.h"
extern TaskHandle_t xReadTask_handle;

/* This is the main task pinned to the IO core. All gpio based
 * tasks are generated from here, and this acts as the cores own main().
 */
void io(void *pvParam)
{
    // Start the read task
    xTaskCreatePinnedToCore(&io_read_task, "Reading Task", config_STACK_DEFAULT, NULL, configMAX_PRIORITIES - 1, &xReadTask_handle, MY_CORE);

    // Blink the onborad LED to show that tasks are timing correctley
    gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    int delay = 500;
    char pin_state = 0;
    while (1)
    {
        pin_state = !pin_state;
        gpio_set_level(GPIO_NUM_2, pin_state);
        vTaskDelay(delay / portTICK_PERIOD_MS);
    }
}