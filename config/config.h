#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hardware/spi.h"

// === LoRa parameters ===
typedef struct {
    uint32_t rf_freq;
    uint8_t  tx_power;
    uint8_t  modulation;
    uint8_t  lora_sf;
    uint8_t  band_width;
    uint8_t  code_rate;
    uint8_t  payload_size;
} radio_config_t;


typedef enum {
    RADIO_TYPE_SX1280 = 0,
    RADIO_TYPE_RFM9X = 1
} radio_type_t;

// === Task Timings ===
typedef struct {
    uint32_t housekeeping_interval_ms;
    uint32_t can_poll_interval_ms;
    uint32_t radio_tx_interval_ms;
    radio_type_t radio_type;
} sys_config_t;

extern sys_config_t sys_config;

// === Pin Configuration ===
typedef struct {
    // SPI Bus and Chip Select
    spi_inst_t *spi_bus0;
    spi_inst_t *spi_bus1;
    uint32_t cs_lora;
    uint32_t cs_can;

    // SPI pins
    uint32_t spi_sck0;
    uint32_t spi_mosi0;
    uint32_t spi_miso0;
    uint32_t spi_sck1;
    uint32_t spi_mosi1;
    uint32_t spi_miso1;

    // LoRa specific
    uint32_t lora_reset;
    uint32_t lora_busy;
    uint32_t lora_dio1;

    // I2C
    uint32_t i2c_sda;
    uint32_t i2c_scl;

    // can config
    uint32_t rst_can;
    uint32_t int_can;

} pin_config_t;

// Global configuration instances
extern pin_config_t pin_config;
extern sys_config_t sys_config;

radio_config_t get_active_radio_config(void);
void config_load_defaults(void);
void set_active_radio_config(const radio_config_t* new_cfg);

#ifdef __cplusplus
}
#endif

#endif
