#pragma once
#include <cmath>
#include <string>
#include <vector>

struct Voto {
  std::string id;
  std::string opcion;
};

class Block {
public:
  int ind;
  unsigned int nonce = 0;
  std::string previous_hash;
  std::string current_hash;
  std::vector<Voto> votos;

  std::string calculateHash() {
    std::string input = "";
    std::string hashed = "0000000000000000";
    unsigned int hash_state = 2166136u;
    unsigned int unique = ((ind ^ nonce) * 295102) % 37;
    for (Voto voto : votos) {
      input += voto.id;
      input += voto.opcion;
    }
    input += std::to_string(unique);

    for (char c : input) {
      hash_state = hash_state ^ (unsigned char)c;
      hash_state *= 169212;
    }

    unsigned int temp_state = hash_state;

    while (input.length() < 16) {
      temp_state = temp_state ^ 31112;
      input += (char)((temp_state) % 95 + 33);
    }

    for (size_t i = 0; i < input.size(); i++) {
      hash_state = (hash_state ^ (unsigned int) input[i]) * 241;
      hashed[i % 16] = (char)(input[i] * (61127 ^ hash_state) % 95 + 33);
    }
    return hashed;
  }
};
