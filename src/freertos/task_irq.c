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




void irq_task(uint gpio, uint32_t events)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (gpio_get(RF_DIO1))
    {
        vTaskNotifyGiveFromISR(rxTaskHandle, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

