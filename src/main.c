#include "common.h"

#include "comms/comms.h"
#include "io/io.h"

void app_main()
{
    // Pin the main tasks to each core
    xTaskCreatePinnedToCore(&comms, "Comms Main", config_STACK_DEFAULT, NULL, configMAX_PRIORITIES - 1, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(&io, "Sensor Main", config_STACK_DEFAULT, NULL, configMAX_PRIORITIES - 2, NULL, PRO_CPU_NUM);
}
