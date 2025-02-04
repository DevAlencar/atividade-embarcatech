# 📌 Introdução

Este repositório contém a implementação de duas atividades utilizando a placa Raspberry Pi Pico. Ambas as atividades fazem uso de LEDs e botões para simular um semáforo e um sistema de ativação temporizada de LEDs.

## 🛠️ Requisitos

- Para executar os códigos, é necessário ter:

- Raspberry Pi Pico W 2

- LEDs (Vermelho, Amarelo, Verde e Azul)

- Resistores (330Ω recomendados para os LEDs)

- Botão Push-Button

- Cabo micro-USB

- Ambiente de desenvolvimento com SDK do Pico instalado

# 🟢 Atividade 1 - Simulação de um Semáforo 🚦

## 🎯 Objetivo

Implementar um semáforo com três LEDs (Vermelho, Amarelo e Verde), alternando entre os estados automaticamente a cada 3 segundos e imprimindo o estado atual via serial (UART).

## 📌 Funcionamento

- Inicialmente, o LED Vermelho acende.

- Após 3 segundos, ele apaga e o LED Amarelo acende.

- Após 3 segundos, o LED Verde acende e o Amarelo apaga.

- Após mais 3 segundos, o LED Verde apaga e o Vermelho acende novamente.

- Esse ciclo se repete indefinidamente.

## 📜 Código-fonte

O código utiliza um temporizador repetitivo para alternar entre os estados do semáforo e imprime o estado atual a cada segundo via comunicação serial.

## 🔧 Implementação

### GPIOs utilizados:

- LED Vermelho: GPIO 11

- LED Amarelo: GPIO 12

- LED Verde: GPIO 13

### Bibliotecas Utilizadas:

- pico/stdlib.h (para manipulação dos GPIOs)

- stdio.h (para saída serial)

### Mecanismo de Temporização:

- Função add_repeating_timer_ms() para alternar os LEDs a cada 3 segundos.

# 🔴 Atividade 2 - Acionamento Temporizado de LEDs 🔵🟢

## 🎯 Objetivo

Criar um sistema onde um botão ativa três LEDs (Azul, Vermelho e Verde), os quais são desligados em sequência com intervalos de 3 segundos.

## 📌 Funcionamento

### Ao pressionar o botão:

- Todos os LEDs acendem simultaneamente.

- Após 3 segundos, o LED Azul apaga.

- Após 3 segundos, o LED Vermelho apaga.

- Após 3 segundos, o LED Verde apaga.

- O botão possui um mecanismo de debounce para evitar múltiplas ativações acidentais.

## 📜 Código-fonte

O código utiliza interrupções GPIO para detectar o pressionamento do botão e timers one-shot para desligar os LEDs após tempos programados.

## 🔧 Implementação

### GPIOs utilizados:

- LED Azul: GPIO 11

- LED Vermelho: GPIO 12

- LED Verde: GPIO 13

- Botão: GPIO 5

### Bibliotecas Utilizadas:

- pico/stdlib.h (para manipulação dos GPIOs)

- hardware/timer.h (para alarmes temporizados)

- hardware/gpio.h (para configurar o botão como entrada)

### Mecanismo de Temporização:

- Função add_alarm_in_ms() para desligar os LEDs em sequência.

- Interrupção falling-edge no botão para detectar o pressionamento.
