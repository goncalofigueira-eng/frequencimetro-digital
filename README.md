# Frequencímetro Digital

Repositório dedicado ao projeto académico desenvolvido no âmbito da unidade curricular de Projeto Temático em Programação Aplicada da Licenciatura em Eletrónica e Mecânica Industrial na ESTGA / Universidade de Aveiro.

---

## Autoria e Enquadramento
* **Curso**: Licenciatura em Eletrónica e Mecânica Industrial
* **Autor**: Gonçalo Figueira
* **Ano Letivo**: 2023/2024 (1.º Semestre)
* **Classificação**: 12 valores

---

## O que Aprendi e Competências Desenvolvidas
Este projeto permitiu-me consolidar e aplicar conhecimentos práticos fundamentais nas áreas de eletrónica e programação aplicada:
* **Programação em C/C++ para Microcontroladores**: Aprofundei a lógica de programação na IDE do Arduino e a estruturação de código modular através de funções e variáveis otimizadas.
* **Gestão de Interrupções Externas**: Aprendi a utilizar interrupções (`attachInterrupt`) para detetar transições de sinal em tempo real, garantindo uma contagem rigorosa de impulsos e ciclos.
* **Condicionamento de Sinais**: Compreendi como proteger o microcontrolador utilizando divisores de tensão resistivos e díodos para retificação de meia onda, viabilizando a leitura segura de sinais analógicos.
* **Ajuste Matemático (Regressão Cúbica)**: Apliquei métodos matemáticos e ferramentas como o GeoGebra para o tratamento de dados e correção das leituras de tensão analógica, otimizando a precisão do sistema.
* **Utilização de Instrumentação de Laboratório**: Ganhei autonomia no manuseamento de equipamentos de medida essenciais, como multímetros digitais, osciloscópios e geradores de sinais para testes e validação.

---

## Especificações Técnicas do Sistema
* **Microcontrolador**: Arduino Uno R3 (ATmega328P)
* **Capacidade de Medição**: 
  * **Frequência**: 0 Hz a 30 kHz (compatível com sinais quadrados, sinusoidais e triangulares)
  * **Tensão**: 0 a $7,5\,\text{V}_{RMS}$ ($\approx 10\,\text{V}_p$)
* **Interface de Visualização**: Display LCD 16x2 com módulo I2C e Monitor Série
* **Condicionamento de Entrada**: Divisor de tensão resistivo ($12\,\text{k}\Omega$) e retificação de meia onda (Díodo 1N4004)

---

## Estrutura do Repositório
* `Relatorio_Final.pdf`: Documentação técnica completa do projeto.
* `Codigo/`: Ficheiros fonte em C++ utilizados no Arduino Uno.
* `Esquemas/`: Esquemas elétricos e simulações.
