// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
#include <queue>
using namespace std;

const string FALLO = "FALLO EN EL SISTEMA";
const string CORRECTO = "CORRECTO";
const string ABANDONEN = "ABANDONEN INMEDIATAMENTE LA BASE";

struct tBateria{
    int identificador;
    int carga;
};

bool operator<(const tBateria& a, const tBateria& b){
    return a.carga < b.carga ||
        (a.carga == b.carga && a.identificador < b.identificador);
}

void resolver(PriorityQueue<tBateria>& baterias, queue<tBateria>& repuestos, const int Z, const int T){
    int tiempo = 0;
    tBateria bateria;
    bool repuestoVacio = false;

    while(tiempo < T && !baterias.empty()){
        bateria = baterias.top(); baterias.pop();

        // Actualizamos el tiempo en base a la carga de la bateria y el tiempo transcurrido
        tiempo = bateria.carga;

        // Descargarla
        bateria.carga -= Z;

        // Si esta vacia la reponemos
        if(bateria.carga <= 0){
            // Si hay repuesto lo colocamos
            if(!repuestos.empty()){
                bateria = repuestos.front(); repuestos.pop();
                baterias.push(bateria);
            }
            // Si no indicamos que no estan todas las baterias funcionando 
            else{
                repuestoVacio = true;
            }
        } 
        // Si no la volvemos a colocar en la pq
        else{
            baterias.push(bateria);
        }
    }

    // Si baterias esta vacio entonces abandonamos
    if(baterias.empty()){
        cout << ABANDONEN << "\n";
    }
    // Si no estan todas funcionando (ya que no teniamos mas de repuesto)
    else if (repuestoVacio){
        cout << FALLO << "\n";
        while(!baterias.empty()){
            cout << baterias.top().identificador << " " << baterias.top().carga << "\n";
            baterias.pop();
        }
    }
    // Si no esta todo correcto
    else{
        cout << CORRECTO << "\n";
        while(!baterias.empty()){
            cout << baterias.top().identificador << " " << baterias.top().carga << "\n";
            baterias.pop();
        }
    }
}

bool resuelveCaso() {
    int B = 0;
    if(!(cin >> B )) return false;

    PriorityQueue<tBateria> baterias;

    int duracion = 0;
    for(int i = 0; i<B;i++){
        cin >> duracion;
        baterias.push({i+1, duracion});
    }

    queue<tBateria> repuesto;
    int R = 0;
    for(int i = 0;i<R;i++){
        cin >> duracion;
        repuesto.push({i+1+B, duracion});
    }

    int Z = 0;
    int T = 0;
    cin >> Z >> T;


    resolver(baterias, repuesto, Z, T);

    cout << "---\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entradaMarte.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}