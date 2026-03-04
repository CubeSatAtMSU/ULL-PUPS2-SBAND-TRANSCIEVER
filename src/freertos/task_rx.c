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

#define RX_BUFFER_SIZE 255

void rx_task(void *params)
{
    static uint8_t rx_buf[RX_BUFFER_SIZE];
    static uint16_t rx_len = 0;

    memset(rx_buf, 0, sizeof(rx_buf));
    lora1280_start_receive(rx_buf, &rx_len);

    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (lora1280_poll_receive_done())
        {
            printf("[RX] Packet received (%u bytes): ", rx_len);
            for (uint16_t i = 0; i < rx_len; i++)
            {
                printf("%02X ", rx_buf[i]);
            }
            printf("\n");

            printf("[RX] ASCII: ");
            for (uint16_t i = 0; i < rx_len; i++)
            {
                char c = (char)rx_buf[i];
                printf("%c", (c >= 32 && c <= 126) ? c : '.');
            }
            printf("\n");
        }
    }
}