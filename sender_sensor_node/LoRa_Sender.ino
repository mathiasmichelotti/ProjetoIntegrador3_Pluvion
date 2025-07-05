#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);

  // Inicializa o módulo LoRa na frequência 915 MHz
  while (!LoRa.begin(915E6)) {
    Serial.println("❌ Erro ao iniciar LoRa. Tentando novamente...");
    delay(2000);
  }

  Serial.println("📡 LoRa emissor iniciado com sucesso!");
}

void loop() {
  // ===========================
  // 🔥 Simulação de Dados 🔥
  // ===========================
  // Aqui estamos simulando a leitura de um sensor
  // Quando for instalar o sensor real, substitua esse trecho
  // por algo como: temperatura = dht.readTemperature();
  float temperatura = random(200, 300) / 10.0;  // 20.0 a 30.0 ºC
  float umidade = random(400, 600) / 10.0;      // 40.0 a 60.0 %

  // ===========================
  // 📄 Monta os dados no formato Line Protocol do InfluxDB
  // ===========================
  String payload = "temperatura,host=esp32_node value=" + String(temperatura) + "\n";
  payload += "umidade,host=esp32_node value=" + String(umidade);

  // ===========================
  // 📡 Envia via LoRa
  // ===========================
  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();

  Serial.print("📤 Enviado via LoRa:\n");
  Serial.println(payload);

  delay(5000);  // Aguarda 5 segundos antes de enviar novamente
}
