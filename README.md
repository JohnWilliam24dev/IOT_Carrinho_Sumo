# IOT_Carrinho_Sumo
**Documentação Detalhada do Código de Controle de Carrinho via Bluetooth**

---

## 1. Visão Geral

Este sketch Arduino (para ESP32) implementa o controle de um carrinho robótico com dois motores (direito e esquerdo) através de comandos recebidos por interface Bluetooth Serial. Os comandos são caracteres ASCII (‘1’ a ‘4’), que movem o carrinho para frente, para trás, giram à esquerda ou à direita. Qualquer outro caractere para o movimento.

---

## 2. Biblioteca Utilizada

```cpp
#include "BluetoothSerial.h"
```

* **BluetoothSerial**: biblioteca nativa do ESP32 que implementa comunicação serial via Bluetooth Classic. Permite emparelhar o dispositivo e trocar dados com um aplicativo em smartphone ou outro módulo Bluetooth.

---

## 3. Definições de Pinos

```cpp
const int motor_direita_f = 14;  // Motor direito – sentido “frente”
const int motor_direita_t = 12;  // Motor direito – sentido “trás”
const int motor_esquer_f  = 25;  // Motor esquerdo – sentido “frente”
const int motor_esquer_t  = 33;  // Motor esquerdo – sentido “trás”
```

Cada motor é controlado por dois pinos digitais:

* **\*\_f** (forward): seta para movimentar o motor em sentido horário.
* **\*\_t** (backward): seta para movimentar o motor em sentido anti-horário.

---

## 4. Variáveis de Ponto Flutuante

```cpp
BluetoothSerial SerialBT;
char comando;
```

* **SerialBT**: objeto de comunicação Bluetooth.
* **comando**: armazena o caractere recebido pela conexão Bluetooth (ex.: ‘1’, ‘2’, etc.).

---

## 5. Função `setup()`

Executada uma vez ao ligar ou resetar o ESP32.

```cpp
void setup() {
  Serial.begin(9600);                     // Inicializa porta serial USB (para debug)
  
  pinMode(motor_direita_f, OUTPUT);
  pinMode(motor_direita_t, OUTPUT);
  pinMode(motor_esquer_f,  OUTPUT);
  pinMode(motor_esquer_t,  OUTPUT);      // Configura pinos dos motores como saída
  
  SerialBT.begin("Carrinho");            // Define nome Bluetooth: “Carrinho”
  Serial.println("Fim Setup");           // Mensagem de conclusão do setup
}
```

* **Serial.begin(9600)**: taxa de 9600 bps para mensagens de debug no Monitor Serial.
* **pinMode**: configura cada pino de controle de motor como saída digital.
* **SerialBT.begin("Carrinho")**: inicializa o módulo Bluetooth com o nome “Carrinho”; ficará visível para emparelhamento.
* **Serial.println("Fim Setup")**: confirma que todas as inicializações foram feitas.

---

## 6. Função `loop()`

Executada repetidamente enquanto o dispositivo estiver ligado.

```cpp
void loop() {
  if (SerialBT.available()) {
    comando = SerialBT.read();
    Serial.print("Recebi ASCII: ");
    Serial.println((int)comando);
    
    if (comando == '1') {
      digitalWrite(motor_direita_f, HIGH);
      digitalWrite(motor_direita_t, LOW);
      digitalWrite(motor_esquer_f, HIGH);
      digitalWrite(motor_esquer_t, LOW);
      Serial.println("Frente");
    }
    else if (comando == '2') {
      digitalWrite(motor_direita_f, LOW);
      digitalWrite(motor_direita_t, HIGH);
      digitalWrite(motor_esquer_f, LOW);
      digitalWrite(motor_esquer_t, HIGH);
      Serial.println("Trás");
    }
    else if (comando == '3') {
      digitalWrite(motor_direita_f, HIGH);
      digitalWrite(motor_direita_t, LOW);
      digitalWrite(motor_esquer_f, LOW);
      digitalWrite(motor_esquer_t, LOW);
      Serial.println("Esquerda");
    }
    else if (comando == '4') {
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
```

---

## 7. Mapeamento de Comandos e Ações

| Comando | ASCII |        Ação       |                           Estado dos Pinos                          | Mensagem Serial |
| :-----: | :---: | :---------------: | :-----------------------------------------------------------------: | :-------------: |
|   ‘1’   |   49  | Mover para frente |  direita\_f=HIGH, direita\_t=LOW,<br>esquer\_f=HIGH, esquer\_t=LOW  |     “Frente”    |
|   ‘2’   |   50  |  Mover para trás  | direita\_f=LOW,  direita\_t=HIGH,<br>esquer\_f=LOW,  esquer\_t=HIGH |      “Trás”     |
|   ‘3’   |   51  |  Girar à esquerda |  direita\_f=HIGH, direita\_t=LOW,<br>esquer\_f=LOW,  esquer\_t=LOW  |    “Esquerda”   |
|   ‘4’   |   52  |  Girar à direita  |  direita\_f=LOW,  direita\_t=LOW,<br>esquer\_f=HIGH, esquer\_t=LOW  |    “Direita”    |
|  outro  |   —   |   Parar motores   |                         todos os pinos = LOW                        |     “parado”    |

---

## 8. Fluxo de Controle

1. **Emparelhamento Bluetooth**

   * Abra o app no smartphone ou use terminal BLE para conectar no nome “Carrinho”.
2. **Envio de Comando**

   * Envie o caractere ASCII correspondente (p. ex., ‘1’ para frente).
3. **Recepção e Atuação**

   * O ESP32 lê o caractere, imprime o valor ASCII no Monitor Serial e ajusta os pinos dos motores.
4. **Movimentação do Carrinho**

   * Dependendo da combinação HIGH/LOW, o driver de motor (H-bridge) coloca o motor em sentido horário ou anti-horário.
5. **Parada**

   * Caso seja recebido qualquer outro caractere, todos os pinos são colocados em LOW, imobilizando os motores.

---


## 9. Exemplo de Uso

1. Carregue o sketch no ESP32 através da IDE Arduino.
2. Abra o Monitor Serial (9600 bps) para acompanhar mensagens de debug.
3. No smartphone, conecte-se ao dispositivo Bluetooth “Carrinho”.
4. Utilize um app de terminal Bluetooth (e.g. “Serial Bluetooth Terminal”) e envie ‘1’ para avançar, ‘2’ para recuar, ‘3’/‘4’ para giros.

