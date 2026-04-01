/**
*
* File :        task_irq.c
* 
* Function :    Implements an interrupt service routine for the DIO2 pin.
*               When triggered, the service will notify the rx_task that 
*               a packet has been received and is ready to be read.
*/

#include "FreeRTOS.h"
#include "task.h"
#include "hardware/gpio.h"
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "debug.h"
#include "task_rx.h"
#include "task_irq.h"




void irq_task(uint gpio, uint32_t events)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (gpio_get(RF_DIO2))
    {
        vTaskNotifyGiveFromISR(rxTaskHandle, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

