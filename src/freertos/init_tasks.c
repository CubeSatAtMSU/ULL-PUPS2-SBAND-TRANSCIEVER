#include "init_tasks.h"
#include "freertos/task_radio.h"
#include "freertos/task_can.h"
#include "freertos/task_housekeeping.h"
#include "freertos/task_rx.h"

void init_tasks(void) {
    launch_radio_task();
    launch_can_task();
    launch_housekeeping_task();
    launch_rx_task();
    launch_serial_task();

}
