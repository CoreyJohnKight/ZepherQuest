#include "io/io.h"

#include "io/read.h"
extern TaskHandle_t xReadTask_handle;

void io(void *pvParam)
{
    xTaskCreatePinnedToCore(&io_read_task, "Reading Task", config_STACK_DEFAULT, NULL, configMAX_PRIORITIES - 1, &xReadTask_handle, MY_CORE);

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