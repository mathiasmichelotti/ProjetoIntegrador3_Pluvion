# 📡 Projeto ESP32 com LoRa e Envio para Nuvem (Ubidots)

Este projeto consiste em uma comunicação sem fio entre dois dispositivos ESP32 utilizando **LoRa**, onde um dispositivo (nó sensor) **lê ou simula dados de sensores** e envia para um segundo dispositivo (gateway), que por sua vez **envia os dados recebidos para a nuvem (Ubidots)** via Wi-Fi.

---

## 🧠 Objetivo

Criar um sistema IoT com as seguintes funcionalidades:

- 📶 Comunicação entre dispositivos usando **LoRa (915 MHz)**
- 🌡️ Leitura (ou simulação) de dados de sensores (temperatura, por exemplo)
- ☁️ Envio dos dados para a plataforma **Ubidots** em tempo real
- 📊 Visualização dos dados por meio de gráficos e dashboards

---

## ⚙️ Componentes Utilizados

- 2x ESP32 com módulo **LoRa SX1276/78** (como Heltec WiFi LoRa 32, TTGO, etc.)
- Antenas LoRa
- Cabo microUSB
- Plataforma de nuvem: [Ubidots](https://ubidots.com/)
- Arduino IDE

---

## 📂 Estrutura do Projeto


---

## 🚀 Como Funciona

### 🔴 Nó Sensor (ESP32 #1)
Simula a leitura de um sensor (temperatura) e envia o valor em formato **JSON via LoRa**.

```cpp
#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  if (!LoRa.begin(915E6)) {
    Serial.println("Erro ao iniciar LoRa");
    while (true);
  }
  Serial.println("LoRa emissor iniciado com sucesso!");
}

void loop() {
  float temperatura = random(200, 300) / 10.0;
  String dado = String("{\"temperatura\": ") + temperatura + "}";

  LoRa.beginPacket();
  LoRa.print(dado);
  LoRa.endPacket();

  Serial.print("Enviado via LoRa: ");
  Serial.println(dado);

  delay(5000);
}
