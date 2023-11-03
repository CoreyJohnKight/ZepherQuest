#include "io/read.h"

extern volatile u_int16_t dataValue;

void io_read_task(void *vParam)
{
    while (1)
    {
        // Sleep until woken
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // I have awoken!
        printf("CORE: Reading data...\n");
        dataValue++;

        printf("CORE: Done! Going to sleep.\n");
    }
}