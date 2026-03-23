#include "FreeRTOS.h"
#include "queue.h"
#include "core/message_queue.h"
#include <stdio.h>

QueueHandle_t radio_queue;

void message_queue_init(void) {
    radio_queue = xQueueCreate(5, sizeof(radio_message_t));
}

bool message_queue_send(const radio_message_t *msg) {
    printf("[QUEUE] Sending radio message type %d\n", msg->type);
    return xQueueSend(radio_queue, msg, 0) == pdPASS;
}

bool message_queue_receive(radio_message_t *msg) {
    bool success = xQueueReceive(radio_queue, msg, portMAX_DELAY) == pdPASS;
    if (success) {
        printf("[QUEUE] Received radio message type %d\n", msg->type);
    }
    return success;
}
