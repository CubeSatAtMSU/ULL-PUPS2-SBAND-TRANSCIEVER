/* 
*
* File:         task_rx.c
*
* Purpose :     Task to handle receiving signal. When the IRQ service is triggered, 
*               the task will be notified and will read the received data from the 
*               radio module's buffer. This data is stored in the rx_buf and its
*               length is stored in rx_len.  
*
*/

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

void rx_task(void *params)
{
    DEBUG_INFO("[RX] Starting RX task...\n");
    uint8_t rx_buf[RX_BUFFER_SIZE];
    uint16_t rx_len = 0;

    memset(rx_buf, 0, sizeof(rx_buf));              // memset may be redundant, look into later. 
    sx1280_start_receive(rx_buf, &rx_len);

    while (1)
    {   
        
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);    // Function waits here until called by the interrupt service in task_irq.c
        DEBUG_INFO("[IRQ] DIO2 interrupt received\n");

        if (sx1280_poll_receive_done())             // Calling sx1280_poll_receive_done stores data in rx_len and rx_buf
        {
            DEBUG_INFO("[RX] Packet received (%u bytes): ", rx_len);
            for (uint16_t i = 0; i < rx_len; i++)
            {
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

        vTaskDelay(pdMS_TO_TICKS(100));*/
    // Mark OLD

    // Mark New

    // SetDioIrqParams(IRQ_TX_DONE, IRQ_RX_DONE);
    // sx1280_start_receive(RX_BUFFER_SIZE, RX_BUFFER_LENGTH);
    // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // if (lora1280_poll_receive_done())
    //  {
    //      printf("[RX] Packet received (%u bytes): ", rx_len);
    //      for (uint16_t i = 0; i < rx_len; i++)
    //      {
    //          printf("%02X ", rx_buf[i]);
    //      }
    //      printf("\n");

    //     printf("[RX] ASCII: ");
    //     for (uint16_t i = 0; i < rx_len; i++)
    //     {
    //         char c = (char)rx_buf[i];
    //         printf("%c", (c >= 32 && c <= 126) ? c : '.');
    //     }
    //     printf("\n");
    // }
    // DEBUG_INFO("[RX] Notification received \n");
}

/*void rx_task(void *params) {
    DEBUG_INFO("[RX] RX task started (stub)\n");
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}*/
void launch_rx_task(void)
{
    xTaskCreate(
        rx_task,
        "RX",
        512,
        NULL,
        tskIDLE_PRIORITY,
        &rxTaskHandle);
}