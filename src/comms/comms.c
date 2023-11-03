#include "comms/comms.h"
#include "common.h"
#include "comms/soft_ap.h"
#include "comms/server.h"

void comms(void *pvParam)
{
    static httpd_handle_t server = NULL;

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // printf("START AP -----------------------------------------\n");
    // vTaskDelay(200 / portTICK_PERIOD_MS);
    // wifi_init_softap();

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("START STA -----------------------------------------\n");
    wifi_init_sta();

    printf("\n\nStarting Server...\n");
    server = start_webserver();
    if (server == NULL)
    {
        printf("ERROR\n");
        return;
    }

    while (1)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
