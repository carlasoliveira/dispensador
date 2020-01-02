#include <NTPClient.h> //Biblioteca do NTP.
#include <WiFi.h> //Biblioteca do WiFi.
#define led 22
//-------- Configurações de Wi-fi-----------
const char* ssid = "Carla";
const char* password = "c34601016";
//-------- Configurações de relógio on-line-----------
WiFiUDP udp;
NTPClient ntp(udp, "a.ntp.br", -3 * 3600, 60000);//Cria um objeto "NTP" com as configurações.
NTPClient ntp(udp, "200.20.186.94", -3 * 3600, 60000);//Cria um objeto "NTP" com as configurações.
//200.20.186.75
//200.20.186.94

String horario;            // Variável que armazenara a hora

void setup()
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);      // Define o pino como saída.
  digitalWrite(led, 0);      // Apaga o LED.
  WiFi.begin(ssid, password);
  delay(2000);               // Espera a conexão.
  ntp.begin();               // Inicia o NTP.
  ntp.forceUpdate();         // Força o Update.
}
void loop()
{
  //Armazena na variável HORA, o horário atual.
  horario = ntp.getFormattedTime();
  Serial.println(horario);     // Escreve a hora no monitor serial.
  if (horario == "03:31:30")
  { // Ao atingir o período definido
    digitalWrite(led, 1);   // O LED Acende
  }
  if (horario == "16:55:30")
  { // Ao atingir o período definido
    digitalWrite(led, 0);   // O LED Apaga
  }
  delay(1000);              // Espera 1 segundo.
}
