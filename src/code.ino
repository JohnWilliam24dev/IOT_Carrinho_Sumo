#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
char comando;  // char ao invés de int

const int motor_direita_f = 14;
const int motor_direita_t = 12;
const int motor_esquer_f = 25;
const int motor_esquer_t = 33;

void setup() {
  Serial.begin(9600);
  pinMode(motor_direita_f, OUTPUT);
  pinMode(motor_direita_t, OUTPUT);
  pinMode(motor_esquer_f, OUTPUT);
  pinMode(motor_esquer_t, OUTPUT);
  SerialBT.begin("Carrinho Equipe 1");
  Serial.println("Fim Setup");

  digitalWrite(motor_direita_f, LOW);
  digitalWrite(motor_direita_t, LOW);
  digitalWrite(motor_esquer_f, LOW);
  digitalWrite(motor_esquer_t, LOW);
}


  void loop() {
    if (SerialBT.available()) {
      comando = SerialBT.read();  // ex: '1', '2', ...
      Serial.print("Recebi ASCII: ");
      Serial.println((int)comando);  // debug: imprime 49,50,...

      if (comando == '1') {  // nota o apóstrofo
        digitalWrite(motor_direita_f, HIGH);
        digitalWrite(motor_direita_t, LOW);
        digitalWrite(motor_esquer_f, HIGH);
        digitalWrite(motor_esquer_t, LOW);

        Serial.println("Frente");
      } else if (comando == '2') {
        digitalWrite(motor_direita_f, LOW);
        digitalWrite(motor_direita_t, HIGH);
        digitalWrite(motor_esquer_f, LOW);
        digitalWrite(motor_esquer_t, HIGH);
        Serial.println("Trás");
      } else if (comando == '3') {
        digitalWrite(motor_direita_f, HIGH);
        digitalWrite(motor_direita_t, LOW);
        digitalWrite(motor_esquer_f, LOW);
        digitalWrite(motor_esquer_t, LOW);
        Serial.println("Esquerda");
      } else if (comando == '4') {
        digitalWrite(motor_direita_f, LOW);
        digitalWrite(motor_direita_t, LOW);
        digitalWrite(motor_esquer_f, HIGH);
        digitalWrite(motor_esquer_t, LOW);
        Serial.println("Direita");
      } else {
        digitalWrite(motor_direita_f, LOW);
        digitalWrite(motor_direita_t, LOW);
        digitalWrite(motor_esquer_f, LOW);
        digitalWrite(motor_esquer_t, LOW);
        Serial.println("parado");
      }
    }
  }
