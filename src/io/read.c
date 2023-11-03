#include "io/read.h"

void io_read_task(void *vParam)
{
    while (1)
    {
        printf("CORE: Reading data...\n");
        // TODO: Read & Update

        printf("CORE: Done! Going to sleep.\n");
        vTaskSuspend(NULL);
    }
}