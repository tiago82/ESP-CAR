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
  RFID::addCardFunction(0xA8560943, funcao2); // Associa o cartão 0xA8560943 à função funcao2
  RFID::addCardTwoFunctions(0x104A4913,  funcao2,  funcao3); // possibilidade de um cartao alternar entre duas funcoes. 
}

void loop() {
  RFID::checkRFIDPresent(mfrc522); // Verifica a presença de um cartão RFID e executa a função associada, se houver
}
