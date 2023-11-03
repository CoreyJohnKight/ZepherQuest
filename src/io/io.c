#include "io/io.h"

#include "io/read.h"

void io(void *pvParam)
{
    xTaskCreatePinnedToCore(&io_read_task, "Reading Task", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL, MY_CORE);

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