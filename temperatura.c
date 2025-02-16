#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

int main()
{
    stdio_init_all();  

    //Inicializa o pino 12 para controlar o LED
    const uint LED_PIN = 12;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    //determina o intervalo de viragem em milisegundos
    uint32_t intervaloDeViragem = 5000;
    //determina o o momento em que o LED vai ligar indicando o momento da viragem com base no tempo absoluto (timer)
    absolute_time_t proximaViragem = delayed_by_ms(get_absolute_time(), intervaloDeViragem);
    bool led_ligado = false;
    //configura o ADC
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    const float conversion = 3.3f / (1<<12);
    while(true){
        if (time_reached(proximaViragem))
        {
            led_ligado = true;
            gpio_put(LED_PIN, led_ligado);
            sleep_ms(500);
            led_ligado = false;
            gpio_put(LED_PIN, led_ligado);
            proximaViragem = delayed_by_ms(get_absolute_time(), intervaloDeViragem);
        }
        sleep_ms(50);
        float temperaturaMedia = 0.0;
        for (int i = 0; i < 100; i++)
        {
            uint16_t raw = adc_read();
            //divide a voltagem maxima do ADC em uma entrada de 3.3v para um valor de 12 bits, basicamente a quantidade máxima de itens possíveis em uma faixa de 4096 (12 bits)
            float voltage = raw * conversion;
            //Ponto importante, converte a voltagem em temperatura (RP2040 datasheet)
            float temperature = 27 - (voltage - 0.706)/0.001721;
            temperaturaMedia += temperature/100;
        }
        printf("Temperatura: %.2f C", temperaturaMedia);

        // Formata a string com a temperatura média
        char temperature_str[20];
        sprintf(temperature_str, "Temp: %.2f C\n", temperaturaMedia);
        // Inicialização do i2c
        i2c_init(i2c1, ssd1306_i2c_clock * 1000);
        gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
        gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
        gpio_pull_up(I2C_SDA);
        gpio_pull_up(I2C_SCL);

        // Processo de inicialização completo do OLED SSD1306
        ssd1306_init();

        // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
        struct render_area frame_area = {
            start_column : 0,
            end_column : ssd1306_width - 1,
            start_page : 0,
            end_page : ssd1306_n_pages - 1
        };

        calculate_render_area_buffer_length(&frame_area);

        // zera o display inteiro
        uint8_t ssd[ssd1306_buffer_length];
        memset(ssd, 0, ssd1306_buffer_length);
        render_on_display(ssd, &frame_area);

        restart:

        // Parte do código para exibir a mensagem no display 
        char statusAgua[20] ={};
        //Se a temperatura media for maior que 30 graus a mensagem AGUA LIGADA é exibida
        if (temperaturaMedia>30)
        {
            strcpy(statusAgua, "AGUA LIGADA");
        }
        //Exibe as mensagens informadas
        char *text[] = {
            temperature_str,
            "",
            statusAgua,
        };

        int y = 16;
        for (uint i = 0; i < count_of(text); i++)
        {
            ssd1306_draw_string(ssd, 5, y, text[i]);
            y += 8;
        }
        render_on_display(ssd, &frame_area);
        sleep_ms(1500);
    }
    
}