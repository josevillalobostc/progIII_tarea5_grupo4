#pragma once
#include <string>
#include <vector>

struct Voto {
  std::string id;
  std::string opcion;
};

class Block {
public:
  int ind;
  int nonce = 0;
  std::string previous_hash;
  std::string current_hash;
  std::vector<Voto> votos;

  std::string calculateHash() {}
};
