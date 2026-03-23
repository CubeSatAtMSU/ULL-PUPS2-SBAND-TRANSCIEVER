// sx1280_wrapper.cpp
// Thin C-callable wrapper around the C++ SX1280 object

#include "SX1280.h"
#include <cstring>
#include "config.h"

// Instantiate the SX1280 object with pins for NSS, RESET, BUSY, DIO1
static SX1280 radio;

extern "C" {

#include <stdint.h>
#include <stdbool.h>

bool sx1280_init() {
    return radio.Init();
}

void sx1280_tx(const char* msg, uint16_t len) {
    radio.TxPacket((uint8_t*)msg, len);
}

bool sx1280_wait_tx_done(void) {
    return radio.WaitForIRQ_TxDone();
}

void sx1280_reset(void) {
    radio.Reset_SX1280();
}

// New wrapper functions for configuration
void sx1280_set_frequency(uint32_t freq_hz) {
    radio.ConfigureFrequency(freq_hz);
}

void sx1280_set_power(uint8_t power_dbm) {
    radio.ConfigurePower(static_cast<int8_t>(power_dbm));
}

void sx1280_set_modulation(uint8_t packetType) {
    radio.ConfigureModulation(packetType);
}

void sx1280_set_modulation_params(uint8_t sf, uint8_t bw, uint8_t cr) {
    radio.ConfigureModulationParams(sf, bw, cr);
}

}
