#include "io/io.h"
#include "common.h"
void io(void *pvParam)
{
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