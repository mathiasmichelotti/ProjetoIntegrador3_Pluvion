#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);

  // Inicializa LoRa na frequência 915 MHz (Brasil)
  if (!LoRa.begin(915E6)) {
    Serial.println("Erro ao iniciar LoRa");
    while (true);
  }

  Serial.println("LoRa emissor iniciado com sucesso!");
}

void loop() {
  // Simula leitura de sensor (temperatura entre 20.0 e 30.0 ºC)
  float temperatura = random(200, 300) / 10.0;

  // Cria um JSON com a leitura
  String dado = String("{\"temperatura\": ") + temperatura + "}";

  // Envia via LoRa
  LoRa.beginPacket();
  LoRa.print(dado);
  LoRa.endPacket();

  Serial.print("Enviado via LoRa: ");
  Serial.println(dado);

  delay(5000);  // Aguarda 5 segundos
}
