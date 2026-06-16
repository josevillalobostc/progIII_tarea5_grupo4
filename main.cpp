#include "RedReactiva.h"
#include "Block.h"
#include "Blockchain.h"
#include "Blockchain.h"
#include <iostream>

using namespace std;

int main() {

cout << "Iniciando sistema de votacion blockchain.....(cargando)\n\n";

//  Instanciando subject
    CentroElectoralSubject redElectoral;

//  Instanciando las mesas observer
    MesaElectoral mesaNorte("Mesa Norte");
    MesaElectoral mesaSur("Mesa Sur");
    MesaElectoral mesaCentro("Mesa Centro");

    // Suscribir las mesas a la red
    redElectoral.attach(&mesaNorte);
    redElectoral.attach(&mesaSur);
    redElectoral.attach(&mesaCentro);

    //Obtener la Blockchain única que es singleton
    Blockchain& cadenaNacional = Blockchain::getInstance();

    //Simular la creación de votos en un nuevo bloque
    //datos ficticios 
    cout << "\n[SISTEMA] Recopilando nuevos votos...(cargando)\n";
    Block* nuevoBloque = new Block();
    nuevoBloque->votos.push_back({"ID_67677", "Candidato A"});
    nuevoBloque->votos.push_back({"ID_11111", "Candidato B"});
    nuevoBloque->votos.push_back({"ID_88888", "Candidato A"});


    cadenaNacional.addBlock(nuevoBloque);

    //Minería prueba de trabajo para sellar la urna
    cout << "\n[SISTEMA] Sellando la urna (Mineria iniciada)...\n";
    int dificultad = 3; // queremos  que el hash empiece con "000"
    cadenaNacional.mineBlock(dificultad);

    // notificamos a las demás mesas mediante el Patrón Observer
    redElectoral.notificarNuevoBloque(nuevoBloque);

    cout << "\n[SISTEMA] Auditoria final de la cadena de bloques:\n";
    cadenaNacional.isChainValid();

    cout << "\nFin de la simulacion .\n";

    return 0;
}