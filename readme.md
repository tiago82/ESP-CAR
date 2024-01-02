# RFID Functions

Biblioteca para facilitar a manipulação de cartões RFID usando a biblioteca MFRC522.

## Estruturas e Tipos

### `FunctionPtr`

Tipo de ponteiro para função. Representa uma função que pode ser associada a um cartão RFID.

### `CardFunction`

Estrutura que associa um ID de cartão a duas funções.

- `uint32_t cardId`: Identificador único do cartão.
- `FunctionPtr function1`: Ponteiro para a primeira função associada ao cartão.
- `FunctionPtr function2`: Ponteiro para a segunda função associada ao cartão.

## Funções

### `addCardFunction`

Adiciona uma associação entre um cartão RFID, um ID de cartão e uma função.

**Parâmetros:**
- `uint32_t cardId`: Identificador único do cartão RFID.
- `FunctionPtr function`: Ponteiro para a função a ser associada ao cartão.

### `addCardTwoFunctions`

Adiciona uma associação entre um cartão RFID, um ID de cartão e duas funções, permitindo alternar entre elas.

**Parâmetros:**
- `uint32_t cardId`: Identificador único do cartão RFID.
- `FunctionPtr function1`: Ponteiro para a primeira função associada ao cartão.
- `FunctionPtr function2`: Ponteiro para a segunda função associada ao cartão.

### `checkRFIDPresent`

Verifica se um cartão RFID está presente e executa as funções associadas, alternando entre elas.

**Parâmetros:**
- `MFRC522& mfrc522`: Referência para o objeto MFRC522.

## Exemplo de Aplicação

```ino
#include <SPI.h>
#include <MFRC522.h>
#include "rfid_functions.h"

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Inicializa o leitor RFID com os pinos SS_PIN e RST_PIN

void funcao1() {
  Serial.println(F("Executando Função 1"));
}

void funcao2() {
  Serial.println(F("Executando Função 2"));
}

void funcao3() {
  Serial.println(F("Executando Função 3"));
}

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com a taxa de 9600 bps
  SPI.begin(); // Inicializa a biblioteca SPI para comunicação com o módulo RFID
  mfrc522.PCD_Init(); // Inicializa o módulo RFID

  Serial.println(F("Aproxime o cartão RFID para executar uma função."));

  // Adiciona associações de cartões e funções ao módulo RFID
  RFID::addCardFunction(0xA6085DE3, funcao1); // Associa o cartão 0xA6085DE3 à função funcao1
  RFID::addCardTwoFunctions(0x104A4913,  funcao2,  funcao3); // possibilidade de um cartao alternar entre duas funcoes. 
}

void loop() {
  RFID::checkRFIDPresent(mfrc522); // Verifica a presença de um cartão RFID e executa a função associada, se houver
}