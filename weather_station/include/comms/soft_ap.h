#ifndef SOFT_AP
#define SOFT_AP

#include "comms/comms_common.h"

void wifi_event_handler(void *arg, esp_event_base_t event_base,
                        int32_t event_id, void *event_data);

void wifi_init_softap(void);
void wifi_init_sta(void);
#endif