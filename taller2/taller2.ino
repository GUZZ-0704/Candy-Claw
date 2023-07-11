#include <Servo.h>
// Pines del joystick
const int pinX = A0;
const int pinY = A1;
const int pinMotorVertical1 = 2;  // Pin de control 1 del motor vertical
const int pinMotorVertical2 = 3;  // Pin de control 2 del motor vertical
const int pinMotorFondo1 = 4;
const int pinMotorFondo2 = 5;
const int pinMotorHorizontal1 = 6;
const int pinMotorHorizontal2 = 7;
const int pinBotonDown = 8;

Servo servoVertical;
bool movimientosHabilitados = true;
bool botonPresionado = false;


void setup() {
  pinMode(pinMotorVertical1, OUTPUT); // Configura el pin del motor vertical 1 como salida
  pinMode(pinMotorVertical2, OUTPUT); // Configura el pin del motor vertical 2 como salida
  pinMode(pinMotorFondo1, OUTPUT);
  pinMode(pinMotorFondo2, OUTPUT);
  pinMode(pinMotorHorizontal1, OUTPUT);
  pinMode(pinMotorHorizontal2, OUTPUT);
  pinMode(pinBotonDown, INPUT_PULLUP);
  servoVertical.attach(9);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);
  int sensorVal = digitalRead(pinBotonDown);

  if (movimientosHabilitados) {
    movimientoXyYJoystick(xValue, yValue);
  }

  if (sensorVal == LOW && !botonPresionado) {
    logicaBoton();
  }
}



void movimientoXyYJoystick(int xValue, int yValue) {
  if (xValue > 630) {
    // Mover motor horizontal hacia un lado
    digitalWrite(pinMotorFondo1, HIGH);
    digitalWrite(pinMotorFondo2, LOW);
    Serial.println("xMayor");
  } else if (xValue < 405) {
    // Mover motor horizontal hacia el otro lado
    digitalWrite(pinMotorFondo1, LOW);
    digitalWrite(pinMotorFondo2, HIGH);
    Serial.println("xMenor");
  } else {
    // Detener motor horizontal si no hay movimiento en el eje X
    digitalWrite(pinMotorFondo1, LOW);
    digitalWrite(pinMotorFondo2, LOW);
  }


  if (yValue > 680) {
    // Mover motor horizontal hacia un lado

    digitalWrite(pinMotorHorizontal1, LOW);
    digitalWrite(pinMotorHorizontal2, HIGH);
    Serial.println("yMayor");
  }  else if (yValue < 355) {

    // Mover motor horizontal hacia el otro lado
    digitalWrite(pinMotorHorizontal1, HIGH);
    digitalWrite(pinMotorHorizontal2, LOW);
    Serial.println("yMenor");
  } else {
    // Detener motor horizontal si no hay movimiento en el eje X
    digitalWrite(pinMotorHorizontal1, LOW);
    digitalWrite(pinMotorHorizontal2, LOW);
  }
}



void bajarVertical(int distancia) {
  int tiempoDuracion = distancia * 1000; // Ajusta la escala de tiempo según corresponda

  // Activa el motor vertical para bajar
  digitalWrite(pinMotorVertical1, HIGH);
  digitalWrite(pinMotorVertical2, LOW);

  // Espera el tiempo de duración para bajar la distancia
  delay(tiempoDuracion);

  // Detiene el motor vertical
  digitalWrite(pinMotorVertical1, LOW);
  digitalWrite(pinMotorVertical2, LOW);
}



void subirVertical(int distancia) {
  int tiempoDuracion = distancia * 1000; // Ajusta la escala de tiempo según corresponda

  // Activa el motor vertical para subir
  digitalWrite(pinMotorVertical1, LOW);
  digitalWrite(pinMotorVertical2, HIGH);

  // Espera el tiempo de duración para subir la distancia
  delay(tiempoDuracion);

  // Detiene el motor vertical
  digitalWrite(pinMotorVertical1, LOW);
  digitalWrite(pinMotorVertical2, LOW);
}



void accionarGarra() {
  // Código para accionar la garra física utilizando el servo declarado anteriormente

  // Mueve el servo a la posición de apretar la garra
  servoVertical.write(180);  // Ajusta el ángulo según corresponda

  // Espera un tiempo para que la garra se cierre
  delay(3000);  // Ajusta el tiempo de retardo según corresponda

}



void abrirGarra() {
  // Mueve el servo a la posición de soltar la garra
  servoVertical.write(0);  // Ajusta el ángulo según corresponda

  // Espera un tiempo para que la garra se abra
  delay(3000);  // Ajusta el tiempo de retardo según corresponda
}



void logicaBoton() {
  botonPresionado = true;
  movimientosHabilitados = false;
  bajarVertical(3);
  abrirGarra();
  accionarGarra();
  subirVertical(3);
  movimientosHabilitados = true;
  botonPresionado = false;
}
