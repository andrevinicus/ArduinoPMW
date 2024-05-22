# Controle de Velocidade de Motor com Arduino e PWM

## Introdução

Este projeto demonstra como controlar a velocidade de um motor DC utilizando um Arduino e PWM (Pulse Width Modulation). O PWM permite controlar a potência fornecida ao motor variando a largura dos pulsos, proporcionando um controle eficiente e suave da velocidade do motor.

## Componentes Necessários

- 1 Arduino Nano
- 1 Motor 
- 1 Resistor
- 1 Bateria de 5 V
- 1 Botão 
- 1 Resistor de 10kΩ (para o pull-up do botão)
- Fios de conexão
- Protobord
- Protoboard

## Esquemático

Aqui está o esquemático do projeto:

![image](https://github.com/andrevinicus/ArduinoPMW/assets/102330781/a4c97e6a-6f79-453d-b69b-c3a334d19085)


### Conexões:

- **Botão:**
  - Um lado do botão conectado ao pino 2 do Arduino
  - O outro lado do botão conectado ao GND através de um resistor de 10kΩ
  - O lado do botão conectado ao pino 2 também conectado ao 5V
  
- **Motor e Transistor:**
  - Um dos polos do motor foi conectado ao OUT1 do l293D e o outro lado ao OUT2
  - Emissor do transistor conectado ao GND

## Código Fonte

```cpp
#include <Arduino.h>

const int buttonPin = 2; // Pino ao qual o botão está conectado
const int motorPin = 9; // Pino ao qual o motor está conectado

int buttonState = 0; // Estado atual do botão
int lastButtonState = 0; // Último estado do botão
int currentStep = 0; // Passo atual do algoritmo

// Valores de PWM a serem escritos no pino do motor (começando de 0 e aumentando)
const int pwmValues[] = {0, 64, 127, 191, 255};
const int numSteps = sizeof(pwmValues) / sizeof(pwmValues[0]);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up
  pinMode(motorPin, OUTPUT); // Configura o pino do motor como saída
}

void loop() {
  buttonState = digitalRead(buttonPin); // Lê o estado do botão

  // Verifica se houve uma mudança no estado do botão
  if (buttonState != lastButtonState) {
    // Se o botão foi solto (mudou de LOW para HIGH)
    if (buttonState == HIGH) {
      // Avança para o próximo passo do algoritmo
      currentStep++;
      if (currentStep >= numSteps) {
        currentStep = 0; // Reinicia o passo se ultrapassar o número de passos
      }

      // Escreve o valor PWM no pino do motor
      analogWrite(motorPin, pwmValues[currentStep]);
    }

    // Pequeno delay para debouncing do botão
    delay(50);
  }

  // Atualiza o último estado do botão
  lastButtonState = buttonState;
}
