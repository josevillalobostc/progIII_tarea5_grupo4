#pragma once
#include "Block.h"
#include <filesystem>
#include <forward_list>
#include <iostream>
#include <string>
#include <vector>

class Blockchain {
private:
  Blockchain() {
    Block *genesis = new Block();
    genesis->ind = 0;
    genesis->previous_hash = "0000000000000000";
    genesis->nonce = 0;
    genesis->current_hash = genesis->calculateHash();
    bloques.push_back(genesis);
  }

public:
  Blockchain(const Blockchain &) = delete;
  Blockchain &operator=(const Blockchain &) = delete;
  static Blockchain &getInstance() {
    static Blockchain instance;
    return instance;
  }
  std::vector<Block *> bloques;
  bool isChainValid() {
    for (size_t i = 1; i < bloques.size(); i++) {
      Block *actual   = bloques[i];
      Block *anterior = bloques[i - 1];

      if (actual->current_hash != actual->calculateHash()) {
        std::cout << "[INVALIDO] Bloque " << actual->ind
                  << ": el hash fue alterado.\n";
        return false;
      }

      if (actual->previous_hash != anterior->current_hash) {
        std::cout << "[INVALIDO] Bloque " << actual->ind
                  << ": el enlace con el bloque anterior está roto.\n";
        return false;
      }
    }
    std::cout << "[VALIDA] La cadena de bloques es integra.\n";
    return true;
  }

  void mineBlock(int dificultad) {
    if (bloques.empty()) return;

    Block *bloque = bloques.back();
    std::string prefijo(dificultad, '0');

    std::cout << "[MINANDO] Buscando hash que empiece con \""
              << prefijo << "\"...\n";

    bloque->nonce = 0;
    bloque->current_hash = bloque->calculateHash();

    while (bloque->current_hash.substr(0, dificultad) != prefijo) {
      bloque->nonce++;
      bloque->current_hash = bloque->calculateHash();
    }

    std::cout << "[MINADO!] Nonce encontrado: " << bloque->nonce << "\n";
    std::cout << "[HASH]    " << bloque->current_hash << "\n";
  }

  void addBlock(Block *newBlock) {
    if (newBlock == nullptr) return;

    Block *ultimo = bloques.back();
    newBlock->ind           = (int)bloques.size();
    newBlock->previous_hash = ultimo->current_hash;
    newBlock->nonce         = 0;
    newBlock->current_hash  = newBlock->calculateHash();
    bloques.push_back(newBlock);
    std::cout << "[BLOQUE AÑADIDO] Indice: " << newBlock->ind
              << " | Hash: " << newBlock->current_hash << "\n";
  }
};
