int PulseSensorPurplePin = A0;       // Cabo roxo do sensor ligado no A0;
int LED = LED_BUILTIN;               // Led embutido do arduino;
int Buzzer = 10;                      // Buzzer connected to digital pin 9 Buzzer conectado ao pino digital 9;

int Sinal;                          // Armazena os dados brutos de entrada. O valor do sinal pode variar de 0 a 1024
int FilteredSinal = 0;               // Armazena o valor do sinal filtrado
int Threshold = 800;                 // Determina qual sinal considerar como batimento e qual ignorar.
float SignalSmoothing = 0.6;         // Fator de suavização para o filtro (0.0 - 1.0)
int ContactThreshold = 100;          // Limite para detectar o contato físico

// Função de configuração:
void setup() {
  pinMode(LED, OUTPUT);              // Pino que irá piscar de acordo com os batimentos cardíacos!
  pinMode(Buzzer, OUTPUT);           // Pino conectado ao buzzer
  Serial.begin(4800);              // Configura a comunicação serial em uma determinada velocidade.
}

// Função principal:
void loop() {
  Sinal = analogRead(PulseSensorPurplePin);  // Lê o valor do sensor;
  FilteredSinal = (SignalSmoothing * Sinal) + ((1 - SignalSmoothing) * FilteredSinal);  // Aplica o filtro passa-baixas
  // Envia o valor do sinal filtrado para o Monitor dos Batimentos apenas se o limiar for atingido e houver contato físico.
  if (FilteredSinal > Threshold && Sinal > ContactThreshold) {
    digitalWrite(LED, HIGH);                   // Se o sinal filtrado for maior que o limiar e houver contato, liga o LED;
    playBuzzer();                                // Chama a função para tocar o buzzer;
    Serial.println(FilteredSinal);               // Envia o valor do sinal filtrado para o Monitor dos Batimentos;
  } else {
    digitalWrite(LED, LOW);                    // Caso contrário, desliga o LED;
    noTone(Buzzer);                             // Para de tocar o buzzer;
  }

  delay(0);
}

// Função para tocar o buzzer em uma sequência de batimentos
void playBuzzer() {
  int beats = 1;                   // Número de batimentos em sequência;
  int beatDuration = 350;          // Duração de cada batimento em milissegundos;
  int pauseDuration = 1000;         // Duração da pausa entre batimentos em milissegundos;

  for (int i = 0; i < beats; i++) {
    tone(Buzzer, 1000);            // Toca um tom de 1000Hz no buzzer;
    delay(beatDuration);

    noTone(Buzzer);                // Para de tocar o buzzer;
    delay(pauseDuration);
  }
}