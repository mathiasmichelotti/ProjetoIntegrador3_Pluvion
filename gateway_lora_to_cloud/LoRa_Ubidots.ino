#include <WiFi.h>
#include <HTTPClient.h>
#include <LoRa.h>

// Credenciais Wi-Fi
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";

// Token Ubidots
const char* token = "BBUS-l0pk5p1D3LdkI108Ge3Tman5EXdfzg";

// ID do seu dispositivo Ubidots
const char* device_label = "esp32_gateway";

// URL do Ubidots
const char* serverName = "http://industrial.api.ubidots.com/api/v1.6/devices/";

void setup() {
  Serial.begin(115200);

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  // Inicializa LoRa
  if (!LoRa.begin(915E6)) {
    Serial.println("Erro ao iniciar LoRa");
    while (true);
  }

  Serial.println("LoRa receptor iniciado com sucesso!");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String dadoRecebido = "";
    while (LoRa.available()) {
      dadoRecebido += (char)LoRa.read();
    }

    Serial.print("Recebido via LoRa: ");
    Serial.println(dadoRecebido);

    // Envia para Ubidots
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(serverName) + device_label;

      http.begin(url);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-Auth-Token", token);

      int httpResponseCode = http.POST(dadoRecebido);

      if (httpResponseCode > 0) {
        Serial.print("Resposta Ubidots: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Erro na requisição: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("WiFi desconectado!");
    }
  }

  delay(100);
}
