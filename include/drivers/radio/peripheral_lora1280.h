#ifndef PERIPHERAL_LORA1280_H
#define PERIPHERAL_LORA1280_H

#include <stdint.h>
#include <stdbool.h>
#include "drivers/radio/sx1280_wrapper.h"
#include "config.h"

bool lora1280_init(void);
bool lora1280_transmit(const uint8_t *data, uint8_t len);

#endif