#include "config.h"

// Global instances
pin_config_t pin_config;
radio_config_t sx1280_config;
radio_config_t rfm9x_config;
sys_config_t sys_config;
static radio_config_t active_radio_config;

void config_load_defaults(void) {
    sys_config.housekeeping_interval_ms = 1000;
    sys_config.can_poll_interval_ms     = 100;
    sys_config.radio_tx_interval_ms = 100;
//    sys_config.radio_type = RADIO_TYPE_RFM9X;
    sys_config.radio_type = RADIO_TYPE_SX1280;

    // SPI pins setup...
    pin_config.spi_bus0 = spi0;
    pin_config.spi_sck0 = 2;
    pin_config.spi_mosi0 = 3;
    pin_config.spi_miso0 = 4;

    pin_config.spi_bus1 = spi1;
    pin_config.spi_sck1 = 14;
    pin_config.spi_mosi1 = 15;
    pin_config.spi_miso1 = 8;

    pin_config.cs_lora = 5;
    pin_config.cs_can = 19;
    pin_config.rst_can = 18;
    pin_config.int_can = 22;

    pin_config.lora_reset = 25;
    pin_config.lora_busy  = 24;
    pin_config.lora_dio1  = 29;

    pin_config.i2c_sda = 10;
    pin_config.i2c_scl = 11;

    // Define default templates:
    sx1280_config.rf_freq      = 2390000000;
    sx1280_config.tx_power     = 10;
    sx1280_config.modulation   = 0x01;
    sx1280_config.lora_sf      = 0x70;
    sx1280_config.band_width   = 0x34;
    sx1280_config.code_rate    = 0x01;
    sx1280_config.payload_size = 64;

    rfm9x_config.rf_freq      = 915000000;
    rfm9x_config.tx_power     = 15;
    rfm9x_config.modulation   = 0x01;
    rfm9x_config.lora_sf      = 0x70;
    rfm9x_config.band_width   = 0x08;
    rfm9x_config.code_rate    = 0x01;
    rfm9x_config.payload_size = 64;

    // Initialize active config
    if (sys_config.radio_type == RADIO_TYPE_RFM9X) {
        active_radio_config = rfm9x_config;
    } else if (sys_config.radio_type == RADIO_TYPE_SX1280) {
        active_radio_config = sx1280_config;
    }
}

radio_config_t get_active_radio_config(void) {
    return active_radio_config;
}

void set_active_radio_config(const radio_config_t* new_cfg) {
    active_radio_config = *new_cfg;
}