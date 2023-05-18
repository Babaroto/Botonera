// Librería para controlar el display de 7 segmentos

#include <SevSeg.h>

// Pines de los botones y LEDs
const int numButtons = 8;
const int player1Buttons[numButtons] = {2, 3, 4, 5, 6, 7, 8, 9};
const int player2Buttons[numButtons] = {10, 11, 12, 13, A0, A1, A2, A3};

const int player1LEDs[numButtons] = {A4, A5, A6, A7, A8, A9, A10, A11};
const int player2LEDs[numButtons] = {A12, A13, A14, A15, 16, 17, 18, 19};

// Variables para almacenar los puntajes

int player1Score = 0;
int player2Score = 0;

// Configuración del display de 7 segmentos

SevSeg sevseg;

void setup() {
  // Inicialización del display de 7 segmentos
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, 4, player1Score, player2Score);

  // Configuración de los pines de los botones y LEDs
  for (int i = 0; i < numButtons; i++) {
    pinMode(player1Buttons[i], INPUT_PULLUP);
    pinMode(player2Buttons[i], INPUT_PULLUP);

    pinMode(player1LEDs[i], OUTPUT);
    pinMode(player2LEDs[i], OUTPUT);
  }
}

void loop() {
  // Generar índices de botones aleatorios para cada jugador
  int player1Index = random(0, numButtons);
  int player2Index = random(0, numButtons);

  // Encender los LEDs correspondientes a los botones seleccionados
  digitalWrite(player1LEDs[player1Index], HIGH);
  digitalWrite(player2LEDs[player2Index], HIGH);

  // Mostrar los índices de los botones seleccionados en el display de 7 segmentos
  sevseg.setNumber(0, player1Index);
  sevseg.setNumber(1, player2Index);

  // Esperar a que los jugadores presionen los botones
  while (digitalRead(player1Buttons[player1Index]) == HIGH || digitalRead(player2Buttons[player2Index]) == HIGH) {
    // Esperar
  }

  // Apagar los LEDs
  digitalWrite(player1LEDs[player1Index], LOW);
  digitalWrite(player2LEDs[player2Index], LOW);

  // Incrementar el puntaje del jugador correspondiente
  player1Score++;
  player2Score++;

  // Actualizar el display de 7 segmentos con los nuevos puntajes
  sevseg.setNumber(player1Score, 1);
  sevseg.setNumber(player2Score, 0);

  delay(1000);
}
