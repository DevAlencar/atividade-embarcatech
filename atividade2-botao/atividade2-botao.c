#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_AZUL 11
#define LED_VERMELHO 12
#define LED_VERDE 13
#define BOTAO 5

volatile bool leds_ativos = false;

// Desliga o LED verde
int64_t apagar_led_verde(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0);
    leds_ativos = false;
    return 0;
}

// Desliga o LED vermelho
int64_t apagar_led_vermelho(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0);
    add_alarm_in_ms(3000, apagar_led_verde, NULL, false);
    return 0;
}

// Desliga o LED azul
int64_t apagar_led_azul(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0);
    add_alarm_in_ms(3000, apagar_led_vermelho, NULL, false);
    return 0;
}

// Aciona todos os LEDs ao pressionar o botão
void acionar_leds(uint gpio, uint32_t events) {
    if (!leds_ativos) {
        leds_ativos = true;
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 1);
        add_alarm_in_ms(3000, apagar_led_azul, NULL, false);
    }
}

// Implementação do debounce do botão
bool debounce() {
    sleep_ms(50);
    return gpio_get(BOTAO) == 0;
}

int main() {
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);
    
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &acionar_leds);
    
    while (1) {
        sleep_ms(100);
    }
}
