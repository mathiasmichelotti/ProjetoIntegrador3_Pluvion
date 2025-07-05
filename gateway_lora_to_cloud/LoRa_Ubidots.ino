#include <WiFi.h>
#include <HTTPClient.h>
#include <LoRa.h>

// =============================
// Configurações da Rede Wi-Fi
// =============================
const char* ssid = "SEU_SSID";         // Substitua pelo seu SSID
const char* password = "SUA_SENHA";    // Substitua pela sua senha

// =============================
// Configurações do InfluxDB
// =============================
const char* influx_url = "https://us-east-1-1.aws.cloud2.influxdata.com";
const char* org = "UFSM"; // Nome da organização
const char* bucket = "estacao_meteorologica"; // Nome do bucket
const char* token = "xmlCVqD3CLpA_PNvENaiRpzYJVS_oCFJtgaa_i-4xpMpVhV3B-ekEbvavGL4xqwgQBHNVZ4UnOSPkTpAAI6oHA==";

// =============================
// Função para conectar ao Wi-Fi
// =============================
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
    Serial.println("\n✅ Wi-Fi conectado!");
  } else {
    Serial.println("\n❌ Falha ao conectar no Wi-Fi.");
  }
}

void setup() {
  Serial.begin(115200);

  // Conectar ao Wi-Fi
  conectarWiFi();

  // Inicializar LoRa
  while (!LoRa.begin(915E6)) {
    Serial.println("❌ Erro ao iniciar LoRa. Tentando novamente...");
    delay(2000);
  }

  Serial.println("📡 LoRa receptor iniciado com sucesso!");
}

void loop() {
  conectarWiFi(); // Garante Wi-Fi conectado

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String dadoRecebido = "";
    while (LoRa.available()) {
      dadoRecebido += (char)LoRa.read();
    }

    Serial.print("📥 Recebido via LoRa:\n");
    Serial.println(dadoRecebido);

    // =============================
    // Enviar dados ao InfluxDB
    // =============================
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String postUrl = String(influx_url) + "/api/v2/write?org=" + org + "&bucket=" + bucket + "&precision=s";

      http.begin(postUrl);
      http.addHeader("Authorization", "Token " + String(token));
      http.addHeader("Content-Type", "text/plain");

      int httpResponseCode = http.POST(dadoRecebido);

      if (httpResponseCode > 0) {
        Serial.print("✅ Dados enviados ao InfluxDB. Código: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("❌ Erro na requisição HTTP: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("⚠️ Wi-Fi desconectado! Não foi possível enviar.");
    }
  }

  delay(500); // Pequena pausa para evitar sobrecarga
}
