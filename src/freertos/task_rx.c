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

#define RX_BUFFER_SIZE 255
#define RX_BUFFER_LENGTH 255

TaskHandle_t rxTaskHandle = NULL;

void rx_task(void *params) {
    DEBUG_INFO("[RX] Starting RX task...\n");
    static uint8_t rx_buf[RX_BUFFER_SIZE];
    static uint16_t rx_len = 0;

    //memset(rx_buf, 0, sizeof(rx_buf));
    //lora1280_start_receive(rx_buf, &rx_len);

    while (1) {

        printf("[IRQ] DIO2 interrupt received\n");
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        if (sx1280_poll_receive_done()) {
            sx1280_start_receive(rx_buf, &rx_len); // Start next receive immediately
            printf("rx_len = %u\n", rx_len);

            rx_len = 17; // Temporary fix to force correct print length

            DEBUG_INFO("[RX] Packet received (%u bytes): ", rx_len);
            for (uint16_t i = 0; i < rx_len; i++) {
                DEBUG_INFO("%02X ", rx_buf[i]);
            }
            DEBUG_INFO("\n");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    /*while (1)
    {
        /*memset(rx_buf, 0, sizeof(rx_buf));
        rx_len=0;
        sx1280_start_receive(rx_buf, &rx_len);

        if (sx1280_poll_receive_done()) {
            DEBUG_INFO("[RX] Packet received (%u bytes): ", rx_len);
            for (uint16_t i = 0; i < rx_len; i++) {
                DEBUG_INFO("%02X ", rx_buf[i]);
            }
            DEBUG_INFO("\n");
        }

        vTaskDelay(pdMS_TO_TICKS(100));*/ //Mark OLD

        //Mark New
        


        //SetDioIrqParams(IRQ_TX_DONE, IRQ_RX_DONE);
        //sx1280_start_receive(RX_BUFFER_SIZE, RX_BUFFER_LENGTH);
        //ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        //if (lora1280_poll_receive_done())
        // {
        //     printf("[RX] Packet received (%u bytes): ", rx_len);
        //     for (uint16_t i = 0; i < rx_len; i++)
        //     {
        //         printf("%02X ", rx_buf[i]);
        //     }
        //     printf("\n");

        //     printf("[RX] ASCII: ");
        //     for (uint16_t i = 0; i < rx_len; i++)
        //     {
        //         char c = (char)rx_buf[i];
        //         printf("%c", (c >= 32 && c <= 126) ? c : '.');
        //     }
        //     printf("\n");
        // }
        //DEBUG_INFO("[RX] Notification received \n");
}


/*void rx_task(void *params) {
    DEBUG_INFO("[RX] RX task started (stub)\n");
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}*/
void launch_rx_task(void) {
    xTaskCreate(
        rx_task,
        "RX",
        512,
        NULL,
        tskIDLE_PRIORITY,
        &rxTaskHandle
    );
}