/*
  Projeto: Funções RFID
  Descrição:  Essa biblioteca facilita para associar cartões RFID a funções específicas.
  Autor: tiago82
  Data de Criação: 2023
  Última Atualização: 2024/01/01
  Versão: 2.0
*/

#include <SPI.h>
#include <MFRC522.h>
#include "rfid_functions.h"

// Restante do seu código...


#include "rfid_functions.h"
#include <Arduino.h>

namespace RFID {
  // Array dinâmico para armazenar as associações de cartões e funções
  CardFunction* cardFunctions = nullptr;
  int numCardFunctions = 0;


  void addCardFunction( uint32_t cardId, FunctionPtr function) {
    // Realoca o array para comportar mais uma associação de cartão e função
    cardFunctions = (CardFunction*)realloc(cardFunctions, (numCardFunctions + 1) * sizeof(CardFunction));
    cardFunctions[numCardFunctions] = {cardId, function, function};
    numCardFunctions++;
}

void addCardTwoFunctions( uint32_t cardId, FunctionPtr function1, FunctionPtr function2) {
    // Realoca o array para comportar mais uma associação de cartão e funções
    cardFunctions = (CardFunction*)realloc(cardFunctions, (numCardFunctions + 1) * sizeof(CardFunction));
    cardFunctions[numCardFunctions] = {cardId, function1, function2};
    numCardFunctions++;
}

  bool isFunction1Active = false;

  void checkRFIDPresent(MFRC522& mfrc522) {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      uint32_t cardId = *(uint32_t*)mfrc522.uid.uidByte;

      // Procura no array pela correspondência entre o cardId e a função associada
      for (int i = 0; i < numCardFunctions; i++) {
        if (cardFunctions[i].cardId == cardId) {


            if (!isFunction1Active) {
              // Executa a função, caso encontrada
              cardFunctions[i].function1();
              isFunction1Active = true;
            } else {
              // Executa a função 2
              cardFunctions[i].function2();
              isFunction1Active = false;
            }

          break; // Sai do loop após encontrar a função correspondente
        }
      }

      Serial.print(F("Cartão detectado com ID: 0x"));
      Serial.print(cardId, HEX);
      Serial.println();
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }

}
