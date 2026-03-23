#include "drivers/radio/peripheral_lora1280.h"
#include "sx1280_wrapper.h"
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "debug.h"

bool lora1280_init() {
    return sx1280_init();
}

bool lora1280_transmit(const uint8_t *data, uint8_t len) {
    DEBUG_DEBUG("[LORA_TX] Transmitting (%d bytes): ", len);
    for (int i = 0; i < len; ++i){
        DEBUG_DEBUG("%02X ", data[i]);
    }
    DEBUG_DEBUG("\n");

    sx1280_tx(data, len);
    return sx1280_wait_tx_done();
}