#include "freertos/task_radio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drivers/radio/peripheral_lora1280.h"
#include "hardware/gpio.h"
#include "drivers/radio/radio_hal.h"
#include <string.h>
#include <stdio.h>
#include "core/message_queue.h"
#include "config.h"
#include "debug.h"
#include "task_rx.h"
#include "task_irq.h"

void isr_test_task(void *pvParameters)
{
    printf("[ISR_TEST] Starting ISR test task...\n");

    vTaskDelay(pdMS_TO_TICKS(8000)); // Delay for 8 seconds to allow other tasks to initialize

    printf("[ISR_TEST] Triggering ISR...\n");
    
    radio_isr_callback(RF_DIO1, GPIO_IRQ_EDGE_RISE);

    vTaskDelete(NULL); // Delete the task after testing
}

void launch_isr_test_task(void) {
    xTaskCreate(
        isr_test_task,
        "ISR_TEST",
        512,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL
    );
}