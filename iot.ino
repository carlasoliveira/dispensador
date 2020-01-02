#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = "fflwohit";
const char* password = "QK-1SFmxU_rT";
const int mqtt_port = "14638";
/*const char* ssid = "Robotica";
const char* password = "robotica";
const char* mqtt_server = "192.168.0.167";
*/
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // Começamos conectando a uma rede WiFi
  Serial.println();
  Serial.print("Conectando à");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço de IP:");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensagem chegou ao tópico:");
  Serial.print(topic);
  Serial.print(". Message: ");
  String saida;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    saida += (char)message[i];
  }
  Serial.println();
  /* Se uma mensagem for recebida no tópico esp32/saida,
  verifica se a mensagem está "ativada" ou "desativada".*/
  // Altera o estado de saída de acordo com a mensagem
  if (String(topic) == "esp32/saida") {
    Serial.print("Alterando a saída para");
    if (saida == "on") {
      Serial.println("on");
      digitalWrite(LED, 1);
    }
    else if (saida == "off") {
      Serial.println("off");
      digitalWrite(LED, 0);
    }
  }
}
void reconnect() {
  // Faz loop até sermos reconectados
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT ...");
    // Tentativa de conexão
    if (client.connect("ESP8266Client")) {
      Serial.println("conectado");
      // Subscribe
      client.subscribe("esp32/saida");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("tente novamente em 5 segundos");
      // Espera 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) {
    char temperatura[8];
    char umidade [8];
    lastMsg = now;
    dtostrf(t, 1, 2, temperatura);
    dtostrf (h, 1, 2, umidade);
    client.publish("esp32/Temperatura", temperatura);
    client.publish("esp32/Umidade", umidade);

  }
}
