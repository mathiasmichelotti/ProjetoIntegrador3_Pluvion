#include <WiFi.h>
#include <HTTPClient.h>

// ==== CONFIGURAÇÕES Wi-Fi ====
const char* ssid = "SEU_WIFI";         // Troque pelo seu Wi-Fi
const char* password = "SUA_SENHA";   // Troque pela sua senha

// ==== CONFIGURAÇÕES UBIDOTS ====
String token = "BBUS-l0pk5p1D3LdkI108Ge3Tman5EXdfzg";  // Seu token
String deviceLabel = "esp32_lora";      // Nome do dispositivo no Ubidots
String variableLabel = "temperatura";   // Nome da variável a ser criada

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
}

void loop() {
  float temperatura = random(200, 300) / 10.0;  // Simula entre 20.0 e 30.0

  enviaParaUbidots(temperatura);
  delay(5000); // Espera 5 segundos
}

void enviaParaUbidots(float valor) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "http://industrial.api.ubidots.com/api/v1.6/devices/" + deviceLabel;
    String json = "{\"" + variableLabel + "\":" + String(valor, 1) + "}";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Auth-Token", token);

    int httpResponseCode = http.POST(json);

    Serial.println("Enviando: " + json);
    Serial.print("Resposta HTTP: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("Wi-Fi desconectado.");
  }
}
