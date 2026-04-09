#ifndef TASK_RX_H
#define TASK_RX_H

#include "FreeRTOS.h"
#include "task.h"

void rx_tasks(void);

void launch_rx_task(void);

void task_serial(void);

void launch_serial_task(void);

extern TaskHandle_t rxTaskHandle;
extern uint8_t rx_buf[255];
extern uint16_t rx_len;

#endif // INIT_TASKS_H
