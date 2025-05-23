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

