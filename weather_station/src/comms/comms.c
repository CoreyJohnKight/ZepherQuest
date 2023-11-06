#include "comms/comms.h"
#include "comms/comms_common.h"
#include "comms/soft_ap.h"
#include "comms/server.h"

static const char *TAG_COMMS = "Comms Main";

/* This is the main task pinned to the Comms core. All communications based
 * tasks are generated from here, and this acts as the cores own main().
 */
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

    // TODO: For future use.
    //  wifi_init_softap();

    ESP_LOGI(TAG_COMMS, "START STA -----------------------------------------");
    wifi_init_sta();

    ESP_LOGI(TAG_COMMS, "Starting Server...");
    server = start_webserver();
    if (server == NULL)
    {
        ESP_LOGI(TAG_COMMS, "SERVER WAS NULL");
        return;
    }

    // TODO:
    while (1)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
