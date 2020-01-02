#define amarelo 23//Define o LED ao pino 23
#define azul 22
#define botaoAmarelo 33 //Define o botão ao pino 22
#define botaoAzul 32

#define buzzer 12
int freq = 2000;
int channel = 0;
int resolution = 8;

#include <NTPClient.h> //Biblioteca do NTP.
#include <WiFi.h> //Biblioteca do WiFi.

//-------- Configurações de Wi-fi-----------
const char* ssid = "Aquarius";
const char* password = "capivara";

//-------- Configurações de relógio on-line-----------
WiFiUDP udp;
NTPClient ntp(udp, "200.20.186.75", -3 * 3600, 60000);//Cria um objeto "NTP" com as configurações.
/*
  200.20.186.75
  200.20.186.94
  a.st1.ntp.br  200.160.7.186 e 2001:12ff:0:7::186
  b.st1.ntp.br  201.49.148.135
  c.st1.ntp.br  200.186.125.195
  d.st1.ntp.br  200.20.186.76
  a.ntp.br  200.160.0.8 e 2001:12ff::8
  b.ntp.br  200.189.40.8
  c.ntp.br  200.192.232.8
  gps.ntp.br  200.160.7.193 e 2001:12ff:0:7::193
*/
/*
  NTPClient: Função que configura o fuso horário
  ntp: Armazena os valores configurados;
  udp:Estabelece uma comunicação entre o ESP32 e um cliente externo, no caso desse exemplo, o NTP.
  a.st1.ntp.br: Endereço on-line utilizado na coleta da hora correta no servidor.
  -3 : Fuso brasileiro segundo o Meridiano de Greenwich.
  3600 : Multiplica pelo fuso formatando a leitura em segundos.
  60000: Intervalo entre cada atualização (1 minuto)
*/

String horario; // Variável que armazenara a hora

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);                                 // Aguarda meio segundo
    Serial.println("Conectando ao WiFi..");     // Conectando
  }
  Serial.println("Conectado"); // Conectado
  
  delay(2000);               // Espera a conexão.
  ntp.begin();               // Inicia o NTP.
  ntp.forceUpdate();         // Força o Update.

  ledcSetup(channel, freq, resolution);
  ledcAttachPin(buzzer, channel);

  pinMode(amarelo, OUTPUT);//Define o pino como saida.
  pinMode(azul, OUTPUT);
  pinMode(botaoAmarelo, INPUT_PULLUP);
  pinMode(botaoAzul, INPUT_PULLUP);
}

int aAmarelo = 1;
int aAzul = 1;

void loop() {

  //Armazena na variável HORA, o horário atual.
  horario = ntp.getFormattedTime();

  int estadoBAmarelo = digitalRead(botaoAmarelo);
  int estadoBAzul = digitalRead(botaoAzul);

  Serial.println(horario);     // Escreve a hora no monitor serial.
  if (horario == "03:29:35") {
    // Ao atingir o período definido
    digitalWrite(amarelo, aAmarelo);
    delay(500);
    ledcWriteTone(channel, 2000);
    delay(5000);
    ledcWriteTone(channel, 0);
  }

  if (horario == "14:10:00") {
    digitalWrite(azul, aAzul);   // O LED Acende
    delay(500);
    ledcWriteTone(channel, 2000);
    delay(5000);
    ledcWriteTone(channel, 0);
  }
  delay(1000);


  if (estadoBAmarelo == LOW) {
    aAmarelo = 0;
    digitalWrite(amarelo, aAmarelo);
    Serial.println("apagou");
  }
  if (estadoBAzul == LOW) {
    aAzul = 0;
    digitalWrite(azul, aAzul);
    Serial.println("apagou");
  }
}
