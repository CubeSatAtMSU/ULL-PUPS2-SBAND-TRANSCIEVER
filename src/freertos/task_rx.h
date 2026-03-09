#ifndef TASK_RX_H
#define TASK_RX_H

#include "FreeRTOS.h"
#include "task.h"

void rx_tasks(void);

void launch_rx_task(void);

extern TaskHandle_t rxTaskHandle;

#endif // INIT_TASKS_H
