# Frequencímetro Digital ⚡[cite: 447, 450]

Repositório dedicado ao projeto académico desenvolvido no âmbito da unidade curricular de **Projeto Temático em Programação Aplicada** (ESTGA / Universidade de Aveiro)[cite: 447].

---

## 👥 Autoria e Enquadramento
* **Curso**: Licenciatura em Eletrónica e Mecânica Industrial
* **Grupo**: Gonçalo Figueira, +3
* **Ano Letivo**: 2023/2024 (1.º Semestre)

---

## 🛠️ Especificações Técnicas
* **Microcontrolador**: Arduino Uno R3 (ATmega328P)
* **Capacidade de Medição**: 
  * Frequência: 0 Hz a 30 kHz (para sinais quadrados, sinusoidais e triangulares)
  * Tensão: 0 a $7,5\,\text{V}_{RMS}$ ($\approx 10\,\text{V}_p$)
* **Interface de Visualização**: Display LCD 16x2 com módulo I2C e Monitor Série
* **Condicionamento de Entrada**: Divisor de tensão resistivo ($12\,\text{k}\Omega$) e retificação de meia onda (Díodo 1N4004)

---

## 💻 Software e Algoritmo
* Desenvolvido em **Arduino IDE** (C/C++).
* Utilização de **interrupções externas** (`attachInterrupt`) para a contagem de impulsos e ciclos de sinal em tempo real.
* Aplicação de **regressão cúbica** para correção e cálculo rigoroso da tensão real a partir da amostragem analógica.

---

## 📂 Estrutura do Repositório
* `Relatorio_Final.pdf`: Documentação técnica completa do projeto.
* `Codigo/`: Ficheiros fonte em C++ utilizados no Arduino Uno.
* `Esquemas/`: Esquema elétrico e simulações.
