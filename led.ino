#define amarelo 23//Define o LED ao pino 23
#define azul 22
#define botaoAmarelo 33 //Define o botão ao pino 22
#define botaoAzul 32

void setup() {
  Serial.begin(115200);//Inicia a comunicação serial.
  pinMode(amarelo, OUTPUT);//Define o pino como saida.
  pinMode(azul, OUTPUT);
  pinMode(botaoAmarelo, INPUT_PULLUP);
  pinMode(botaoAzul, INPUT_PULLUP);
}

int aAmarelo = 1;
int aAzul = 1;

void loop() {
  digitalWrite(amarelo, aAmarelo);
  digitalWrite(azul, aAzul);
  int estadoBAmarelo = digitalRead(botaoAmarelo);
  int estadoBAzul = digitalRead(botaoAzul);

  Serial.println(estadoBAmarelo);
  //Serial.println(estadoBAzul);

  if(estadoBAmarelo == LOW) {
    aAmarelo = 0;
    digitalWrite(amarelo, aAmarelo);
    Serial.println("apagou");
  }
  if(estadoBAzul == LOW) {
    aAzul = 0;
    digitalWrite(azul, aAzul);
    Serial.println("apagou");
  }

}
