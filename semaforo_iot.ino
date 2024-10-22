// Definir pines para los LEDs del semáforo 1 (Vía 1)
const int red1 = 2;
const int yellow1 = 3;
const int green1 = 4;

// Definir pines para los LEDs del semáforo 2 (Vía 2)
const int red2 = 5;
const int yellow2 = 6;
const int green2 = 7;

// Pines para los botones
const int startButton = 8;
const int stopButton = 9;

// Variable para controlar el estado del semáforo
bool isRunning = false;

void setup() {
  // Configurar los pines como salida
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);
  
  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
  
  // Configurar los pines de los botones como entrada con resistencias pull-up internas
  pinMode(startButton, INPUT_PULLUP);
  pinMode(stopButton, INPUT_PULLUP);
}

void loop() {
  // Leer el estado de los botones
  bool startPressed = digitalRead(startButton) == LOW; // Botón de inicio presionado
  bool stopPressed = digitalRead(stopButton) == LOW;   // Botón de parada presionado

  // Iniciar el ciclo del semáforo si se presiona el botón de inicio
  if (startPressed) {
    isRunning = true;
  }

  // Detener el ciclo del semáforo si se presiona el botón de parada
  if (stopPressed) {
    isRunning = false;
    apagarSemaforos(); // Apagar todos los LEDs cuando se detiene el ciclo
  }

  // Ejecutar el ciclo del semáforo si está en funcionamiento
  if (isRunning) {
    // Semáforo 1 en verde, Semáforo 2 en rojo
    digitalWrite(green1, HIGH);
    digitalWrite(red2, HIGH);
    esperar(5000); // Mantener 5 segundos y verificar si se presiona el botón de parada

    // Semáforo 1 en amarillo
    digitalWrite(green1, LOW);
    digitalWrite(yellow1, HIGH);
    esperar(2000); // Mantener 2 segundos y verificar si se presiona el botón de parada

    // Semáforo 1 en rojo, Semáforo 2 en verde
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, LOW);
    digitalWrite(green2, HIGH);
    esperar(5000); // Mantener 5 segundos y verificar si se presiona el botón de parada

    // Semáforo 2 en amarillo
    digitalWrite(green2, LOW);
    digitalWrite(yellow2, HIGH);
    esperar(2000); // Mantener 2 segundos y verificar si se presiona el botón de parada

    // Semáforo 2 en rojo
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, HIGH);
    digitalWrite(red1, LOW);
  }
}

// Función para apagar todos los LEDs
void apagarSemaforos() {
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
}

// Función para esperar un tiempo específico y verificar si se presiona el botón de parada
void esperar(int milisegundos) {
  int tiempoInicio = millis();
  while (millis() - tiempoInicio < milisegundos) {
    // Si el botón de parada se presiona, detener el ciclo
    if (digitalRead(stopButton) == LOW) {
      isRunning = false;
      apagarSemaforos();
      break; // Salir del bucle de espera
    }
  }
}
