#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main()
{
    // Configure the GPIO pin for the LED
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_2); // GPIO 2 (NodeMCU-32S onboard LED)
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    int delay = 500;
    while (1)
    {
        // Turn the LED on
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(delay / portTICK_PERIOD_MS); // Delay for 1 second

        // Turn the LED off
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(delay / portTICK_PERIOD_MS); // Delay for 1 second
    }
}
