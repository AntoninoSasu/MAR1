// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct tPaciente{
    string nombre;
    int gravedad;
    int orden;
};

bool operator<(const tPaciente& a, const tPaciente& b){
    return a.gravedad > b.gravedad ||
        (a.gravedad == b.gravedad && a.orden < b.orden);
}

bool resuelveCaso() {
    int N = 0;
    cin >> N;
    if(N == 0) return false;    

    PriorityQueue<tPaciente> pq;

    string nombre;
    char evento;
    int gravedad = 0;

    tPaciente paciente;

    for(int i = 0;i<N;i++){
        cin >> evento;

        if(evento == 'I'){
            cin >> nombre >> gravedad;
            pq.push({nombre, gravedad, i});
        }
        else{
            paciente = pq.top(); pq.pop();
            cout << paciente .nombre << "\n";
        }
    }

    cout << "---\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entrada5.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}