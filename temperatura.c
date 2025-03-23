#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/pio.h"

#include "inc/ssd1306.h"
#include "ws2818b.pio.h"

// Configurações de pinos e constantes
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15
#define LED_PIN 7
#define LED_COUNT 25

// Tipos e estruturas
typedef struct {
    uint8_t G, R, B;
} npLED_t;

// Variáveis globais
npLED_t leds[LED_COUNT];
PIO np_pio;
uint sm;
float leituras[5] = {0};

// Prototipagem de funções
void npInit(uint pin);
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b);
void npClear(void);
void npWrite(void);
void atualizarLeituras(float novaLeitura);
void atualizarLEDS(void);
void configurarDisplay(void);
void atualizarDisplay(float temperatura);

// Funções da matriz de LEDs
void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, false);

    if (sm < 0) {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true);
    }

    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);
    npClear();
}

void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

void npClear(void) {
    for (uint i = 0; i < LED_COUNT; ++i) {
        npSetLED(i, 0, 0, 0);
    }
}

void npWrite(void) {
    for (uint i = 0; i < LED_COUNT; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}

// Função principal
int main(void) {
    stdio_init_all();
    npInit(LED_PIN);
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    const float conversion = 3.3f / (1 << 12);

    while (true) {
        float temperaturaMedia = 0.0f;

        for (int i = 0; i < 10; i++) {
            uint16_t raw = adc_read();
            float voltage = raw * conversion;
            float temperature = 27 - (voltage - 0.706f) / 0.001721f;
            temperaturaMedia += temperature / 10.0f;
        }

        printf("Temperatura: %.2f C\n", temperaturaMedia);

        atualizarLeituras(temperaturaMedia);
        configurarDisplay();
        atualizarDisplay(temperaturaMedia);
        atualizarLEDS();

        sleep_ms(3000);
        npClear();
    }

    return 0;
}

// Funções auxiliares
void atualizarLeituras(float novaLeitura) {
    for (int i = 4; i > 0; i--) {
        leituras[i] = leituras[i - 1];
    }
    leituras[0] = novaLeitura;
}

void atualizarLEDS(void) {
    npClear();
    for (int i = 0; i < 5; i++) {
        float temp = leituras[i];

        if (temp > 20 && temp <= 25) {
            npSetLED(4 - i, 120, 0, 0);
        }
        if (temp > 25 && temp <= 30) {
            npSetLED(4 - i, 120, 0, 0);
            npSetLED(5 + i, 120, 0, 0);
        }
        if (temp > 30 && temp <= 35) {
            npSetLED(4 - i, 120, 0, 0);
            npSetLED(5 + i, 120, 0, 0);
            npSetLED(14 - i, 120, 0, 0);
        }
        if (temp > 35 && temp <= 40) {
            npSetLED(4 - i, 120, 0, 0);
            npSetLED(5 + i, 120, 0, 0);
            npSetLED(14 - i, 120, 0, 0);
            npSetLED(15 + i, 120, 0, 0);
        }
        if (temp > 45) {
            npSetLED(4 - i, 120, 0, 0);
            npSetLED(5 + i, 120, 0, 0);
            npSetLED(14 - i, 120, 0, 0);
            npSetLED(15 + i, 120, 0, 0);
            npSetLED(24 - i, 120, 0, 0);
        }
    }
    npWrite();
}

void configurarDisplay(void) {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    ssd1306_init();
}

void atualizarDisplay(float temperatura) {
    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);

    char temperature_str[20];
    sprintf(temperature_str, "Temp: %.2f C", temperatura);

    char statusAgua[20] = "";
    if (temperatura > 30) {
        strcpy(statusAgua, "AGUA LIGADA");
    }

    char *text[] = {
        temperature_str,
        "",
        statusAgua
    };

    int y = 16;
    for (uint i = 0; i < count_of(text); i++) {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }

    render_on_display(ssd, &frame_area);
}
