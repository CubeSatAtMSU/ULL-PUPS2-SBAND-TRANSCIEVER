#include "bus_config.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>

void init_spi() {
    printf("[SPI_INIT] setting up spi0\n");
    spi_init(SPI_BUS0, 1000000);
    gpio_set_function(SPI_SCK_PIN0, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN0, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN0, GPIO_FUNC_SPI);

    printf("[SPI_INIT] setting up spi1\n");
    spi_init(SPI_BUS1, 1000000);
    gpio_set_function(SPI_SCK_PIN1, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN1, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN1, GPIO_FUNC_SPI);
}
