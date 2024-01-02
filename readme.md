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
- `MFRC522& mfrc522`: Referência para o objeto MFRC522.
- `uint32_t cardId`: Identificador único do cartão RFID.
- `FunctionPtr function`: Ponteiro para a função a ser associada ao cartão.

### `checkRFIDPresent`

Verifica se um cartão RFID está presente e executa as funções associadas, alternando entre elas.

**Parâmetros:**
- `MFRC522& mfrc522`: Referência para o objeto MFRC522.

## Exemplo de Aplicação

```cpp
#include "RFID_Functions.h"

// Funções a serem associadas aos cartões
void funcaoExemplo1() {
  // Implementação da função 1
}

void funcaoExemplo2() {
  // Implementação da função 2
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  // Exemplo de associação de cartão a uma função
  RFID::addCardFunction(mfrc522, 0x12345678, funcaoExemplo1);
  
  // Exemplo de associação de cartão a duas funções
  RFID::CardFunction cardFunction;
  cardFunction.cardId = 0x87654321;
  cardFunction.function1 = funcaoExemplo2;
  cardFunction.function2 = funcaoExemplo1;
  RFID::addCardFunction(mfrc522, cardFunction);
}

void loop() {
  // Verifica se um cartão RFID está presente e executa as funções associadas
  RFID::checkRFIDPresent(mfrc522);

  // Restante do código...
}
