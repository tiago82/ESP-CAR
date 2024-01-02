/*
  Projeto: Funções RFID
  Descrição:  Essa biblioteca facilita para associar cartões RFID a funções específicas.
  Autor: tiago82
  Data de Criação: 2023
  Última Atualização: 2024/01/01
  Versão: 2.0
*/

#ifndef RFID_FUNCTIONS_H
#define RFID_FUNCTIONS_H

#include <MFRC522.h>

namespace RFID {
  typedef void (*FunctionPtr)();

  // Estrutura para associar um ID de cartão a duas funções
  struct CardFunction {
    uint32_t cardId;
    FunctionPtr function1;
    FunctionPtr function2;
  };


  void addCardFunction( uint32_t cardId, FunctionPtr function);
  void addCardTwoFunctions( uint32_t cardId, FunctionPtr function1, FunctionPtr function2);
  void checkRFIDPresent(MFRC522& mfrc522);
}

#endif // RFID_FUNCTIONS_H
