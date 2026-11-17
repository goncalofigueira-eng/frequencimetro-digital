/*
           ________________________________________________________
          |  ____________________________________________________  |
          | |                                                    | |
          | |         Projeto EMI 1º ano - 1º semestre           | |
          | |               Frequencímetro V3.2                  | |
          | |                                                    | |
          | | Autores:                                           | |
          | | - Rodrigo Miguel Martins Cabral, 115216;           | |
          | | - Gonçalo Alexandre Silva Figueira, 109438;        | |
          | | - Diogo Antonio Boticário Da Silva Páscoa, 118734; | |
          | | - Tiago Jorge Martins Silva, 115154;               | |
          | | - João Pedro Correia Borges, 119337;               | |
          | |                                                    | |
          | | Placa utilizada: Arduino Uno R3;                   | |
          | |____________________________________________________| |
          |________________________________________________________|

*/

#include <LiquidCrystal_I2C.h>  // Biblioteca do Display com o módulo I2C.

LiquidCrystal_I2C lcd(39, 16, 2);  // Configuração do display.

const int pinosensor = A0;    // Pino A0 que vai fazer a leitura da tensão.
const byte interruptPin = 2;  // Pino 2 que vai fazer a leitura da frequência.

int inicio_onda = 0;
long tempofrequenciafinal = 0;  // Armazena o tempo da última medição.

// Estrutura para armazenar variáveis relacionadas à frequência.
typedef struct VARIAVEIS_FREQUENCIA {

  unsigned int frequencia = 0;  // Frequência calculada.
  const char* mensagemFrequenciaFinal = "Hz ";      //Constante que armazena o texto "Hz " que será projetado no LCD para assinalar o valor de frequência.
};

// Estrutura para armazenar variáveis relacionadas à tensão.
typedef struct VARIAVEIS_TENSAO {

  int valorinstantaneo[600];  // Array para armazenar leituras da tensão.
  int maiorvalor;           // Maior valor de tensao medida pelo arduino.
  float tensaopico;           // Tensão de pico.
  float tensaopicoreal;       // Tensão de pico real.
  float tensaorms;            // Tensão eficaz (RMS).
  float tensao_minima_frequencia;
  const char* mensagemTensaoFinal = "V ";           //Constante que armazena o texto "V " que será projetado no LCD para assinalar o valor de tensão.
};

void ONDA0V() {

  inicio_onda++;
}

// Função para calcular frequência.
void calcularFrequencia() {

  VARIAVEIS_FREQUENCIA frequenciamedida;  //Declaração de uma estrutura para armazenar variáveis relacionadas à frequência.
  frequenciamedida.frequencia = inicio_onda - 1;
  inicio_onda = 0;
  lcd.setCursor(5, 1);  // Posiciona o cursor no LCD.
  lcd.print("         ");
  lcd.setCursor(5, 1);                             //Posicionamento do Cursor.
  lcd.print((String)frequenciamedida.frequencia);  //Imprime o valor da frequencia no LCD.
  lcd.print(frequenciamedida.mensagemFrequenciaFinal);              //Imprime as unidades “Hz” no LCD.
  Serial.print("Frequencia:");                     // Imprime a mensagem indicando que o valor seguinte é a Frequência.
  Serial.print(frequenciamedida.frequencia);       // Imprime o valor da frequência medida.
  Serial.println(frequenciamedida.mensagemFrequenciaFinal);                            // Imprime a unidade de frequência (Hz).
  Serial.println();                                // Imprime uma linha em branco para melhor visualização no monitor serial.
}

// Função para calcular tensão.
void calcularTensao() {

  VARIAVEIS_TENSAO tensao;  //Declaração de uma estrutura para armazenar variáveis relacionadas à tensão.
  tensao.tensao_minima_frequencia = 4.66;
  for (int i = 0; i < 600; i++) {

    tensao.valorinstantaneo[i] = analogRead(pinosensor);  //Faz leituras da tensão.

    delay(2);  // Espera 2 milissegundos.
  }

  for (int i = 0; i < 600; i++) {

    tensao.maiorvalor = max(tensao.maiorvalor, tensao.valorinstantaneo[i]);  // Identifica o maior valor lido.
  }

  tensao.tensaopico = (tensao.maiorvalor * 10) / 1024;                                                                                                                        //Calcula a tensão de pico.
  tensao.tensaopicoreal = -0.0107816075962 * pow(tensao.tensaopico, 3) + 0.2596137655497 * pow(tensao.tensaopico, 2) - 1.0008593991265 * tensao.tensaopico + 5.525145958787;  //Cálculo da tensão real (tensaopicoreal) baseado na tensão de pico medida pelo Arduino (tensaopicoarduino).
  tensao.tensaorms = tensao.tensaopicoreal / sqrt(2);                                                                                                                         //Calcula a tensão RMS.

  if (tensao.maiorvalor < 1) {

    lcd.setCursor(5, 0);  // Posiciona o cursor no LCD.
    lcd.print("         ");
    lcd.setCursor(5, 0);             // Posiciona o cursor no LCD.
    lcd.print("0");                  // Imprime o valor da tensao RMS.
    lcd.print(tensao.mensagemTensaoFinal);  // Imprime as unidades de Tensão.
    Serial.print("Tensao RMS:");     // Imprime a mensagem indicando que o valor seguinte é a Tensão RMS.
    Serial.print("0");               // Imprime o valor da Tensão RMS.
    Serial.println(tensao.mensagemTensaoFinal);             // Imprime a unidade de voltagem (V).

    lcd.setCursor(5, 1);  // Posiciona o cursor no LCD.
    lcd.print("         ");
    lcd.setCursor(5, 1);  // Posiciona o cursor no LCD.
    lcd.print("V Baixa");
    Serial.print("Frequencia:");
    Serial.print("V Baixa");

  }

  else {

    lcd.setCursor(5, 0);  // Posiciona o cursor no LCD.
    lcd.print("         ");
    lcd.setCursor(5, 0);  // Posiciona o cursor no LCD.

    lcd.print((String)tensao.tensaorms);  // Imprime o valor da tensao RMS.
    lcd.print(tensao.mensagemTensaoFinal);       // Imprime as unidades de Tensão.
    Serial.print("Tensao RMS:");          // Imprime a mensagem indicando que o valor seguinte é a Tensão RMS.
    Serial.print(tensao.tensaorms);       // Imprime o valor da Tensão RMS.
    Serial.println(tensao.mensagemTensaoFinal);                  // Imprime a unidade de voltagem (V).

    if (tensao.tensaorms < tensao.tensao_minima_frequencia) {

      lcd.setCursor(5, 1);  // Posiciona o cursor no LCD.
      lcd.print("V Baixa");
      Serial.print("Frequencia:");
      Serial.print("V Baixa");
    }

    else {

      calcularFrequencia();  // Chama a função para calcular a frequencia.
    }
  }
}

// Função de Setup.
void setup() {

const char* mensagemTensaoInicial = "Vrms:";      //Constante que armazena o texto "Vrms:" que usado como mensagem inicial para a tensão no LCD.
const char* mensagemFrequenciaInicial = "Freq:";  //Constante que armazena o texto "Freq:" que usado como mensagem inicial para a frequência no LCD.

  Serial.begin(9600);  // Inicia a comunicação serial a uma taxa de 9600 bps.

  lcd.setBacklight(HIGH);                // Ativa o backlight (iluminação) do LCD.
  lcd.init();                            // Inicia o LCD.
  lcd.clear();                           // Limpa o conteúdo do LCD.
  lcd.setCursor(0, 0);                   // Posiciona o cursor na primeira linha e na primeira coluna do LCD.
  lcd.print(mensagemTensaoInicial);      // Imprime a mensagem inicial para a tensão no LCD.
  lcd.setCursor(0, 1);                   // Posiciona o cursor na primeira linha e na segunda coluna do LCD.
  lcd.print(mensagemFrequenciaInicial);  // Imprime a mensagem inicial para a frequência no LCD.

  pinMode(pinosensor, INPUT);                                            // Configura o pino do sensor como entrada.
  attachInterrupt(digitalPinToInterrupt(interruptPin), ONDA0V, RISING);  // Configuração da interrupção.
}

//Função de Loop.
void loop() {

  if (millis() - tempofrequenciafinal >= 1000) {

    detachInterrupt(digitalPinToInterrupt(interruptPin));  // Temporariamente desativa a interrupção para nao interferir nas leituras.

    calcularTensao();  // Chama a função para calcular a tensão.

    attachInterrupt(digitalPinToInterrupt(interruptPin), ONDA0V, RISING);  // Reativa a interrupção.

    tempofrequenciafinal = millis();  // Atualiza o tempo da última medição.
  }
}
