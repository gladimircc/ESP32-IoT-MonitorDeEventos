#include <WiFi.h>
#include <HTTPClient.h>

#define BOTAO 2
#define LED   10

const char* ssid = "MINHA REDE";
const char* password = "senhadarede";
const char* urlContador = "http://192.168.8.11:3000/incrementar"; // Use o IP da máquina que está rodando o server.js
bool ultimoEstadoBotao = HIGH;
bool estadoLed = false;
unsigned long tempoUltimoClique = 0; // Armazena o tempo (em ms) do último clique válido.
const long delayDebounce = 150;      // Tempo de espera para considerar um novo clique.

void setup() {
  Serial.begin(115200);
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n WiFi conectado!");
  Serial.print("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  bool estadoAtualBotao = digitalRead(BOTAO);  // Lê o estado atual do botão.

  // HIGH -> LOW = botão foi pressionado.
  if (estadoAtualBotao == LOW && ultimoEstadoBotao == HIGH) { 
    // Verifica se já passou tempo suficiente desde o último clique válido.
    if ((millis() - tempoUltimoClique) > delayDebounce) {
      // Se passou tempo suficiente, o clique é válido
      Serial.println("Botão pressionado (clique válido)");

      // Inverte o estado do LED (se estava ligado, desliga; se desligado, liga).
      estadoLed = !estadoLed;
      digitalWrite(LED, estadoLed);
      Serial.println(estadoLed ? "💡 LED ligado" : "💤 LED desligado");

      // Envia a requisição POST para o servidor
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(urlContador);
        int httpCode = http.POST(""); // Envia POST vazio

        if (httpCode == 200) { // Servidor respondeu com "OK"
          String resposta = http.getString();
          Serial.println("Resposta do Servidor: " + resposta);
        } else {
          // Imprime o código de erro para ajudar na depuração.
          Serial.printf("Falha na requisição HTTP. Código: %d\n", httpCode);
        }
        http.end();
      } else {
        Serial.println("WiFi desconectado");
      }
      
      // Atualiza o tempo do último clique válido para o momento atual.
      tempoUltimoClique = millis();
    }
  }
  // Atualiza o último estado conhecido do botão.
  ultimoEstadoBotao = estadoAtualBotao;
}