#include <Arduino.h>

const int buttonPin = 2; // Pino ao qual o botão está conectado
const int motorPin = 9; // Pino ao qual o motor está conectado

int buttonState = 0; // Estado atual do botão
int lastButtonState = 0; // Último estado do botão
int currentStep = 0; // Passo atual do algoritmo

// Valores de PWM a serem escritos no pino do motor (começando de 0 e aumentando)
const int pwmValues[] = {255, 191, 127, 64, 0};
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
