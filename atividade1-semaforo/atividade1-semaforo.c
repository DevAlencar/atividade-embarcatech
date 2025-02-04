#include "pico/stdlib.h"
#include "stdio.h"

// Definição dos GPIOs para o LED RGB
#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

// Temporização em milissegundos
#define TEMPO_TRANSICAO 3000  // 3 segundos
#define TEMPO_IMPRESSAO 1000 // 1 segundo

// Estados do semáforo
typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} estado_semaforo_t;

// Estado atual do semáforo
estado_semaforo_t estado_atual = VERMELHO;

// Função de callback para mudança de estado
bool repeating_timer_callback(struct repeating_timer *t) {
    switch (estado_atual) {
        case VERMELHO:
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_AMARELO, 1);
            estado_atual = AMARELO;
            break;
        case AMARELO:
            gpio_put(LED_AMARELO, 0);
            gpio_put(LED_VERDE, 1);
            estado_atual = VERDE;
            break;
        case VERDE:
            gpio_put(LED_VERDE, 0);
            gpio_put(LED_VERMELHO, 1);
            estado_atual = VERMELHO;
            break;
    }
    return true; // Continue chamando o timer
}

int main() {
    // Inicializa os GPIOs
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicializa o LED no estado vermelho
    gpio_put(LED_VERMELHO, 1);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Inicializa a comunicação serial
    stdio_init_all();

    // Configura o temporizador repetitivo
    struct repeating_timer timer;
    add_repeating_timer_ms(TEMPO_TRANSICAO, repeating_timer_callback, NULL, &timer);

    while (true) {
        // Imprime o estado atual na serial a cada 1 segundo
        switch (estado_atual) {
            case VERMELHO:
                printf("Semáforo está VERMELHO\n");
                break;
            case AMARELO:
                printf("Semáforo está AMARELO\n");
                break;
            case VERDE:
                printf("Semáforo está VERDE\n");
                break;
        }
        sleep_ms(TEMPO_IMPRESSAO);
    }
}
