#include "freertos/task_radio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drivers/radio/peripheral_lora1280.h"
#include "drivers/radio/radio_hal.h"
#include "pico/stdlib.h"
#include <string.h>
#include <stdio.h>
#include "core/message_queue.h"
#include "config.h"
#include "debug.h"
#include "task_rx.h"

void task_serial(void *params)
{
    (void)params;
    DEBUG_INFO("[SERIAL] Starting Serial task...\n");
    while (1)
    {
        int ch = getchar_timeout_us(0);

        if (ch >= 0)
        {
            if (ch == 's' || ch == 'S')
            {
                if (getchar_timeout_us(100000) == ' ')
                {
                    DEBUG_INFO("[SERIAL] Recieved from serial \n");
                    char buf[64];
                    int i = 0;
                    int len;

                    while (i < sizeof(buf) - 1)
                    {
                        int ch = getchar_timeout_us(100000); // 100ms per-char timeout
                        if (ch == PICO_ERROR_TIMEOUT)
                            break;
                        if (ch == '\n' || ch == '\r')
                            len = i;
                        break; // end of message
                        buf[i++] = (char)ch;
                    }
                    buf[i] = '\0';

                    // Now buf contains your message string
                    printf("Received message: %s\n", buf);

                    radio_message_t msg;
                    msg.type = RADIO_MSG_SEND_DATA;
                    msg.body.payload.length = sizeof(buf);
                    memcpy(msg.body.payload.data, buf, sizeof(buf));
                    message_queue_send(&msg);
                }

                else
                {
                    DEBUG_INFO("[SERIAL] Unrecognized command: %c\n", ch);
                }
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
        NULL);
}
