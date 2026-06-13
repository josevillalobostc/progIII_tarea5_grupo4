#pragma once
#include "Block.h"
#include <filesystem>
#include <forward_list>

class Blockchain {
private:
  Blockchain() {}

public:
  Blockchain(const Blockchain &) = delete;
  Blockchain &operator=(const Blockchain &) = delete;
  static Blockchain &getInstance() {
    static Blockchain instance;
    return instance;
  }
  std::vector<Block *> bloques;
  bool isChainValid() {}
  void mineBlock(int dificultad) {}
  void addBlock(Block *newBlock) {}
};
