// C++ code
#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremote.h>

#define Tecla_1 0xEF10BF00
#define Tecla_2 0xEE11BF00


// Configuración del control remoto IR
int IR = 11; // Pin digital al que está conectado el receptor IR

// Configuración del display LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Configuración del sensor de temperatura
int sensorPin = A0;

// Configuración del servo motor
int servoPin = 9;
Servo servo;

// Configuración de los leds
int LED = 13;
int LED2 = 12;

// Umbral de temperatura para detectar incendio
int temperaturaUmbral = 60;

// Rangos de temperatura para cada estación
int temperaturaInviernoMin = -20;
int temperaturaInviernoMax = 10;
int temperaturaPrimaveraMin = 25;
int temperaturaPrimaveraMax = 35;
int temperaturaVeranoMin = 35;
int temperaturaVeranoMax = 50;
int temperaturaOtonioMin = 10;
int temperaturaOtonioMax = 25;

// Estado del sistema de incendios
bool sistemaIncendioActivo = false;

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR, DISABLE_LED_FEEDBACK);
  // Iniciar la recepción de señales IR

  // Inicialización del display LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Estacion:");

  // Inicialización del servo motor
  servo.attach(servoPin);

  // Configuración de los leds
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop()
{
  // Lectura de temperatura
  float temperatura = obtenerTemperatura();

  // Mostrar temperatura en el display LCD
  lcd.setCursor(6, 0);
  lcd.print(temperatura);

  // Determinar estación del año
  String estacion = obtenerEstacion(temperatura);

  // Mostrar estación del año en el display LCD
  lcd.setCursor(10, 1);
  lcd.print(estacion);

  // Verificar si se ha detectado un incendio
  if (temperatura > temperaturaUmbral)
  {
    activarAlarma();
  }
  else
  {
    desactivarAlarma();
  }

  if (IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    if (IrReceiver.decodedIRData.decodedRawData == Tecla_1)
    {
      activarSistemaIncendio();
    }
    else if (IrReceiver.decodedIRData.decodedRawData == Tecla_2)
    {
      desactivarSistemaIncendio();
    }

    IrReceiver.resume();
  }
}

int obtenerTemperatura()
{
  // Realizar la lectura del sensor de temperatura y calcular la temperatura en grados Celsius
  int lectura = analogRead(sensorPin);
  float voltaje = lectura * 5.0 / 1024.0;
  float temperaturaCelsius = (voltaje - 0.5) * 100;
  float temperatura = ( lectura * (500.0 / 1023.0) ) - 50.0;

  return temperatura;
}

String obtenerEstacion(float temperatura)
{
  if (temperatura >= temperaturaInviernoMin && temperatura <= temperaturaInviernoMax)
  {
    return "Invierno";
  }
  else if (temperatura >= temperaturaPrimaveraMin && temperatura <= temperaturaPrimaveraMax)
  {
    return "Primavera";
  }
  else if (temperatura >= temperaturaVeranoMin && temperatura <= temperaturaVeranoMax)
  {
    return "Verano";
  }
  else if (temperatura >= temperaturaOtonioMin && temperatura <= temperaturaOtonioMax)
  {
    return "Otonio";
  }
  else
  {
    return "Desconocida";
  }
}

void activarAlarma()
{
  // Activar el servo motor y los leds de alarma
  servo.write(90);
  digitalWrite(LED, HIGH);
  digitalWrite(LED2, HIGH);

  // Mostrar mensaje de alarma en el display LCD
  lcd.setCursor(0, 1);
  lcd.print("ALARMA!");

  delay(1000); // Esperar 1 segundo
}

void desactivarAlarma()
{
  // Desactivar el servo motor y los leds de alarma
  servo.write(0);
  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);

  // Borrar mensaje de alarma en el display LCD
  lcd.setCursor(0, 1);
  lcd.print("        ");
}

void activarSistemaIncendio()
{
  digitalWrite(LED, HIGH);
  digitalWrite(LED2, HIGH);

  lcd.display();
  sistemaIncendioActivo = true;
}

void desactivarSistemaIncendio()
{
  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);

  lcd.noDisplay();
  sistemaIncendioActivo = false;
  
}

