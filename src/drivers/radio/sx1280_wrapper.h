#ifndef SX1280_WRAPPER_H
#define SX1280_WRAPPER_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the SX1280 radio with the specified parameters.
 * Returns true on success.
 */
bool sx1280_init(void);

/**
 * Transmit a raw buffer over LoRa.
 */
void sx1280_tx(const char* msg, uint16_t len);

/**
 * Wait for TX_DONE interrupt from the radio.
 * Returns true if TX completed successfully.
 */
bool sx1280_wait_tx_done(void);

/**
 * Issue a software reset to the radio.
 */
void sx1280_reset(void);

/**
 * New configuration functions
 */

void sx1280_set_frequency(uint32_t freq_hz);
void sx1280_set_power(uint8_t power_dbm);
void sx1280_set_modulation(uint8_t packetType);
void sx1280_set_modulation_params(uint8_t sf, uint8_t bw, uint8_t cr);

#ifdef __cplusplus
}
#endif

#endif // SX1280_WRAPPER_H
