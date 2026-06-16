#pragma once
#include "Blockchain.h"
#include <vector>
#include <iostream>
#include <string>

     //Interfaz del Observador
struct MesaElectoralObserver {
  virtual void update(Block *nuevoBloque) = 0;
  virtual ~MesaElectoralObserver() = default;
};

    //Nodos:Observadores)
class MesaElectoral : public MesaElectoralObserver {
private:
  std::string nombreMesa;

public:
  MesaElectoral(std::string nombre) : nombreMesa(nombre) {}

  void update(Block *nuevoBloque) override {
    std::cout << "[" << nombreMesa << "] Notificacion recibida. Analizando bloque " << nuevoBloque->ind << "...\n";
    
    //simulamos validacion 
    if (nuevoBloque->current_hash == nuevoBloque->calculateHash()) {
      std::cout << " -> [" << nombreMesa << "] Exito, el bloque fue valido. Registrando consenso .\n";
    } else {
      std::cout << " -> [" << nombreMesa << "] Alerta, el bloque es invalido o esta alterado. Rechazando .\n";
    }
  }
};

// Canal Central 
class CentroElectoralSubject {
private:
  // Utilizamos la interfaz para respetar el polimorfismo del patron observer
  std::vector<MesaElectoralObserver *> mesasRegistradas;

public:
  void attach(MesaElectoralObserver *mesa) {
    mesasRegistradas.push_back(mesa);
  }

  void notificarNuevoBloque(Block *b) {
    std::cout << "\n---------------------------------------------------------\n";
    std::cout << "[RED ELECTORAL] Transmitiendo bloque minado a " 
              << mesasRegistradas.size() << " mesas\n";
    std::cout << "-------------------------------------------------------------------\n";
    
    for (MesaElectoralObserver *mesa : mesasRegistradas) {
      mesa->update(b);
    }
  }
};