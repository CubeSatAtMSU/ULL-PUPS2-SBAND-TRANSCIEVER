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
#include "task_rx.h"

void task_serial(void *params)
{
    DEBUG_INFO("[SERIAL] Starting Serial task...\n");
    while(1) {
        int ch = getchar_timeout_us(0);
        if (ch >= 0) {
            if (ch == 's' || ch == 'S') {
                DEBUG_INFO("[SERIAL] Recieved from serial \n");
            }
        }
    }
    }

void launch_serial_task(void)
{
    xTaskCreate(
        task_serial,
        "Serial Task",
        512,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}

