#include "freertos/task_radio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drivers/radio/peripheral_lora1280.h"
#include "drivers/radio/radio_hal.h"
#include <string.h>
#include <stdio.h>
#include "core/message_queue.h"
#include "config.h"
#include "debug.h"

#define RADIO_TASK_STACK_SIZE 512
#define RADIO_TASK_PRIORITY   (tskIDLE_PRIORITY + 2)

static void radio_task(void *pvParameters) {

    bool ok = radio_hal_init();
    DEBUG_INFO("[RADIO_INIT] radio_hal_init returned: %s\n", ok ? "OK" : "FAIL");

    uint32_t last_freq = 0;
    uint8_t last_power = 0;
    uint8_t last_mod = 0;
    uint32_t last_bw = 0;
    uint8_t last_sf = 0;
    uint8_t last_cr = 0;

    for (;;) {
        radio_message_t msg;

        if (message_queue_receive(&msg)) {

            switch (msg.type) {
                case RADIO_MSG_CONFIGURE:
                    printf("[RADIO] CONFIGURE message received.\n");

                    // Build updated config
                    radio_config_t new_cfg = get_active_radio_config();
                    new_cfg.rf_freq = msg.body.config.frequency_hz;
                    new_cfg.tx_power = msg.body.config.power_dbm;
                    new_cfg.modulation = msg.body.config.modulation;
                    new_cfg.band_width = msg.body.config.bandwidth_hz;
                    new_cfg.lora_sf = msg.body.config.spreading_factor;
                    new_cfg.code_rate = msg.body.config.coding_rate;

                    // Save back to active config
                    set_active_radio_config(&new_cfg);

                    // Re-initialize hardware with new config
                    bool ok = radio_hal_init();
                    DEBUG_INFO("[RADIO_INIT] radio_hal_init returned after CONFIGURE: %s\n", ok ? "OK" : "FAIL");


                    break;

                case RADIO_MSG_SEND_DATA:
                    printf("[RADIO] TX binary (%d bytes): ", msg.body.payload.length);
                    for (int i = 0; i < msg.body.payload.length; i++) {
                        printf("%02X ", msg.body.payload.data[i]);
                    }
                    printf("\n");

                    {
                        uint8_t header[4] = {0xFF, 0xFF, 0x00, 0x00};

                        uint8_t tx_buf[256];
                        size_t total_len = 0;

                        memcpy(tx_buf, header, 4);
                        memcpy(tx_buf + 4, msg.body.payload.data, msg.body.payload.length);
                        total_len = msg.body.payload.length + 4;

                        printf("[RADIO] Transmitting %zu bytes with RadioHead header.\n", total_len);
                        // Check if radio is configured yet
//                        if (last_freq == 0) {
 //                           printf("[RADIO] ERROR: Radio parameters not configured yet. Cannot transmit.\n");
  //                      } else {
                            radio_hal_transmit(tx_buf, total_len);
   //                     }
                    }
                    break;

                default:
                    printf("[RADIO] Unknown message type: %d\n", msg.type);
                    break;
            }
        } else {
            printf("[Radio Task] No message received\n");
        }

        vTaskDelay(pdMS_TO_TICKS(sys_config.radio_tx_interval_ms));
    }
}

void launch_radio_task(void) {
    xTaskCreate(
        radio_task,
        "RadioTask",
        RADIO_TASK_STACK_SIZE,
        NULL,
        RADIO_TASK_PRIORITY,
        NULL
    );
}