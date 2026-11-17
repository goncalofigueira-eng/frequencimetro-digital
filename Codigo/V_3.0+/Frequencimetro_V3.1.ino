/*
  Projeto EMI 1º ano - 1º semestre
  Frequencímetro V3.0
  Autores:
- Rodrigo Miguel Martins Cabral, 125216; 
- Gonçalo Alexandre Silva Figueira, 109438; 
- Diogo Antonio Boticário Da Silva Pascoa, 118734; 
- Tiago Jorge Martins Silva, 115154; 
- João Pedro Correia Borges, 119337;
  Placa utilizada: Arduino Uno R3;
*/

#include <LiquidCrystal_I2C.h>     // Biblioteca do Display com o módulo I2C
LiquidCrystal_I2C lcd(39, 16, 2);  // Configuração do display

int pinosensor = A0;          // Pino A0 que vai fazer a leitura da tensão
const byte interruptPin = 2;  // Pino 2 que vai fazer a leitura da frequência

float contador = 0;            // Contador de interrupções
long tempofrequenciafinal = 0;               // Armazena o tempo da última medição
float frequencia = 0;          // Frequência calculada

int valorinstantanea[625];     // Array para armazenar leituras da tensão
float maiorvalor;
float tensaopico;              // Tensão de pico
float tensaorms = 0;           // Tensão RMS

void FREQUENCIA() {
  contador++;                  // Contador que incrementa a cada interrupção
}

// Função para calcular frequência 
void calcularFrequencia() {
  frequencia = contador / 2;  // Calcula a frequência
  contador = 0;               // Reinicia o contador
  lcd.setCursor(5, 1);     //Posicionamento do Cursor
  lcd.print((String)frequencia);     //Imprime o valor da frequencia no LCD
  lcd.print("Hz ");    //Imprime as unidades “Hz” no LCD
}

// Função para calcular tensão 
void calcularTensao() {
  for (int i = 0; i < 625; i++) {
    valorinstantanea[i] = analogRead(pinosensor);  //Faz leituras da tensão
    delay(2); // Espera 2 milissegundos 
  }

  for (int i = 0; i < 625; i++) {
    if (maiorvalor < valorinstantanea[i]) {
      maiorvalor = valorinstantanea[i];  // Identifica o maior valor lido
    }
  }

  tensaopico = ((maiorvalor * 10) / 1024) * 1.11;  // Calcula a tensão de pico
  tensaorms = tensaopico / 1.4;                   // Calcula a tensão RMS

  lcd.setCursor(5, 0); //Posiciona o cursor no LCD
  lcd.print((String)tensaorms); // Imprime o valor da tensao RMS
  lcd.print("V "); // Imprime as unidades de voltagem, V

  maiorvalor = 0;  // Reinicia a variável do maior valor
}

void setup() {
  Serial.begin(9600);
  lcd.setBacklight(HIGH);
  lcd.init();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vrms:");
  lcd.setCursor(0, 1);
  lcd.print("Freq:");

  pinMode(pinosensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), FREQUENCIA, CHANGE);  // Configuração da interrupção
}

void loop() {
  if (millis() - tempofrequenciafinal >= 1000) {
    detachInterrupt(digitalPinToInterrupt(interruptPin));  // Temporariamente desativa a interrupção para nao interferir nas leituras 

    calcularFrequencia();  // Chama a função para calcular a frequência
    calcularTensao();      // Chama a função para calcular a tensão

    attachInterrupt(digitalPinToInterrupt(interruptPin), FREQUENCIA, CHANGE);  // Reativa a interrupção
    tempofrequenciafinal = millis();  // Atualiza o tempo da última medição
}
}