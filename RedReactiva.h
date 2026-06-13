#pragma once
#include "Blockchain.h"
#include <vector>

struct MesaElectoralObserver {
  virtual void update(Block *nuevoBloque) = 0;
  virtual ~MesaElectoralObserver() = default;
};

class MesaElectoral : public MesaElectoralObserver {
private:
  Blockchain *blockchain;

public:
  void update(Block *nuevoBloque) override {}
};

class CentroElectoralSubject {
  std::vector<MesaElectoral *> mesasRegistradas;

public:
  void attach(MesaElectoral *mesa) {}
  void notificarNuevoBloque(Block *b) {}
};
