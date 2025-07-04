#include <WiFi.h>
#include <HTTPClient.h>
#include <LoRa.h>

// Credenciais Wi-Fi
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";

// Token da API (ex.: Ubidots ou outro)
const char* token = "SEU_TOKEN_API";

// Nome do dispositivo na nuvem
const char* device_label = "esp32_gateway";

// URL da API (ex.: Ubidots, Firebase, InfluxDB, etc.)
const char* serverName = "http://industrial.api.ubidots.com/api/v1.6/devices/";

void conectarWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  int tentativas = 0;

  while (WiFi.status() != WL_CONNECTED && tentativas < 10) {
    delay(1000);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi conectado!");
  } else {
    Serial.println("\nFalha ao conectar no Wi-Fi.");
  }
}

void setup() {
  Serial.begin(115200);

  // Conectar ao Wi-Fi
  conectarWiFi();

  // Inicializar LoRa
  while (!LoRa.begin(915E6)) {
    Serial.println("Erro ao iniciar LoRa. Tentando novamente...");
    delay(2000);
  }

  Serial.println("LoRa receptor iniciado com sucesso!");
}

void loop() {
  conectarWiFi(); // Garante Wi-Fi conectado

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String dadoRecebido = "";
    while (LoRa.available()) {
      dadoRecebido += (char)LoRa.read();
    }

    Serial.print("Recebido via LoRa: ");
    Serial.println(dadoRecebido);

    // Enviar para a nuvem
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(serverName) + device_label;

      http.begin(url);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-Auth-Token", token);

      int httpResponseCode = http.POST(dadoRecebido);

      if (httpResponseCode > 0) {
        Serial.print("Resposta da API: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Erro na requisição HTTP: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("Wi-Fi desconectado! Não foi possível enviar.");
    }
  }

  delay(500); // Pequena pausa para evitar sobrecarga
}
