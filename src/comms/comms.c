#include "comms/comms.h"
#include "common.h"

void comms(void *pvParam)
{

    while (1)
    {
        printf("msg\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
