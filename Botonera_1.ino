#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_MCP23X17.h>

Adafruit_7segment matrix = Adafruit_7segment();
Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;

const int numButtons = 8;
const int player1Buttons[numButtons] = {0, 1, 2, 3, 4, 5, 6, 7};
const int player2Buttons[numButtons] = {8, 9, 10, 11, 12, 13, 14, 15};

int player1Score = 0;
int player2Score = 0;

void setup() {
  matrix.begin(0x70);  // Inicializar el display de 7 segmentos
  matrix.setBrightness(7); // Ajustar el brillo del display

  mcp1.begin_I2C(0); // Inicializar el convertidor MCP23017 para los botones del jugador 1
  mcp2.begin_I2C(1); // Inicializar el convertidor MCP23017 para los botones del jugador 2

  for (int i = 0; i < numButtons; i++) {
    mcp1.pinMode(player1Buttons[i], INPUT_PULLUP); // Configurar los pines de los botones del jugador 1 como entrada con resistencias pull-up internas en el convertidor MCP23017
    mcp2.pinMode(player2Buttons[i], INPUT_PULLUP); // Configurar los pines de los botones del jugador 2 como entrada con resistencias pull-up internas en el convertidor MCP23017
  }
}

void loop() {
  // Obtener un índice de botón aleatorio para cada jugador
  int player1ButtonIndex = random(numButtons);
  int player2ButtonIndex = random(numButtons);

  // Encender los LEDs de los botones correspondientes
  mcp1.digitalWrite(player1Buttons[player1ButtonIndex], LOW);
  mcp2.digitalWrite(player2Buttons[player2ButtonIndex], LOW);

  // Mostrar los índices de los botones en el display de 7 segmentos
  matrix.print(player1ButtonIndex);
  matrix.writeDigitNum(1, player2ButtonIndex);
  matrix.writeDisplay();

  // Esperar a que los jugadores presionen los botones correspondientes
  while (!mcp1.digitalRead(player1Buttons[player1ButtonIndex]) || !mcp2.digitalRead(player2Buttons[player2ButtonIndex])) {}

  // Apagar los LEDs de los botones
  mcp1.digitalWrite(player1Buttons[player1ButtonIndex], HIGH);
  mcp2.digitalWrite(player2Buttons[player2ButtonIndex], HIGH);

  // Incrementar el puntaje del jugador correspondiente
  if (mcp1.digitalRead(player1Buttons[player1ButtonIndex])) {
    player1Score++;
  }

  if (mcp2.digitalRead(player2Buttons[player2ButtonIndex])) {
    player2Score++;
  }

  // Mostrar el puntaje en el display de 7 segmentos
  matrix.print(player1Score);
  matrix.writeDigitNum(1, player2Score);
  matrix.writeDisplay();

  // Esperar un breve tiempo antes de mostrar el próximo cambio de botones
  delay(1000);
}
