// task_housekeeping.c
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "freertos/task_housekeeping.h"
#include "subsystems/housekeeping/housekeeping.h"
#include "protocols/protocol_spacecan.h"
#include "core/message_queue.h"
#include <string.h>
#include "config.h"

void housekeeping_task(void *params) {
    printf("[HOUSEKEEPING] Starting housekeeping task...\n");
    housekeeping_init();

    while (1) {
        printf("[HOUSEKEEPING] Collecting system data... every %lums\n", sys_config.housekeeping_interval_ms);

        uint8_t beacon_frame[64];
        hk_telemetry_t hk = collect_housekeeping_data();
        size_t len = protocol_spacecan_format_beacon(beacon_frame, sizeof(beacon_frame), &hk);

        radio_message_t msg;
        msg.type = RADIO_MSG_SEND_DATA;
        msg.body.payload.length = len;
        memcpy(msg.body.payload.data, beacon_frame, len);
        message_queue_send(&msg);

        printf("[SPACECAN] Beacon payload (%zu bytes): ", len);
        for (size_t i = 0; i < len; ++i) {
            printf("%02X ", beacon_frame[i]);
        }
        printf("\n");

        vTaskDelay(pdMS_TO_TICKS(sys_config.housekeeping_interval_ms));
    }
}

void launch_housekeeping_task(void) {
    xTaskCreate(
        housekeeping_task,
        "Housekeeping",
        512,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}
