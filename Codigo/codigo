// C++ code
#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Configuración del control remoto IR
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Configuración del display LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Configuración del sensor de temperatura
int sensorPin = A0;

// Configuración del servo motor
int servoPin = 9;
Servo servo;

// Configuración de los leds
int ledPin1 = 8;
int ledPin2 = 10;

// Umbral de temperatura para detectar incendio
int temperaturaUmbral = 60;

// Rangos de temperatura para cada estación
int temperaturaInviernoMin = -10;
int temperaturaInviernoMax = 10;
int temperaturaPrimaveraMin = 10;
int temperaturaPrimaveraMax = 25;
int temperaturaVeranoMin = 25;
int temperaturaVeranoMax = 40;
int temperaturaOtonioMin = 10;
int temperaturaOtonioMax = 25;

void setup() {
  // Inicialización del control remoto IR
  irrecv.enableIRIn();

  // Inicialización del display LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Estacion:");

  // Inicialización del servo motor
  servo.attach(servoPin);

  // Configuración de los leds
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

-

int obtenerTemperatura() {
  // Realizar la lectura del sensor de temperatura y calcular la temperatura en grados Celsius
  int lectura = analogRead(sensorPin);
  float voltaje = lectura * 5.0 / 1024.0;
  float temperaturaCelsius = (voltaje - 0.5) * 100;

  return (int)temperaturaCelsius;
}

String obtenerEstacion(int temperatura) {
  if (temperatura >= temperaturaInviernoMin && temperatura <= temperaturaInviernoMax) {
    return "Invierno";
  } else if (temperatura >= temperaturaPrimaveraMin && temperatura <= temperaturaPrimaveraMax) {
    return "Primavera";
  } else if (temperatura >= temperaturaVeranoMin && temperatura <= temperaturaVeranoMax) {
    return "Verano";
  } else if (temperatura >= temperaturaOtonioMin && temperatura <= temperaturaOtonioMax) {
    return "Otonio";
  } else {
    return "Desconocida";
  }
}

void activarAlarma() {
  // Activar el servo motor y los leds de alarma
  servo.write(90);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);

  // Mostrar mensaje de alarma en el display LCD
  lcd.setCursor(0, 1);
  lcd.print("ALARMA!");

  delay(1000);  // Esperar 1 segundo
}

void desactivarAlarma() {
  // Desactivar el servo motor y los leds de alarma
  servo.write(0);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);

  // Borrar mensaje de alarma en el display LCD
  lcd.setCursor(0, 1);
  lcd.print("        ");
}

void activarSistemaIncendio() {
  // Aquí puedes agregar el código necesario para activar el sistema de incendio

  // Por ejemplo, encender una sirena o activar un sistema de rociadores de agua
  // Puedes agregar aquí el código específico para tu sistema de incendio
  // Asegúrate de conectar los componentes necesarios y configurarlos correctamente

  // Ejemplo: encender un led para simular la activación del sistema de incendio
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
}

void desactivarSistemaIncendio() {
  // Aquí puedes agregar el código necesario para desactivar el sistema de incendio

  // Por ejemplo, apagar la sirena o detener el sistema de rociadores de agua
  // Puedes agregar aquí el código específico para tu sistema de incendio
  // Asegúrate de detener adecuadamente los componentes activados anteriormente

  // Ejemplo: apagar el led que simula la activación del sistema de incendio
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}
