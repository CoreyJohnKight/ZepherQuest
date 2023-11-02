#include "comms/comms.h"
#include "common.h"
#include "comms/soft_ap.h"

void comms(void *pvParam)
{

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
    // ESP_LOGI(TAG_AP, "ESP_WIFI_MODE_AP");
    // wifi_init_softap();

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("START STA -----------------------------------------\n");
    ESP_LOGI(TAG_STA, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    while (1)
    {
        printf("msg\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
