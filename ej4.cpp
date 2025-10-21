// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct tRegistro{
    int identificador;
    int periodo;
    int tiempo;
};

bool operator<(const tRegistro& a, const tRegistro& b){
    return a.tiempo < b.tiempo ||
        (a.tiempo == b.tiempo && a.identificador < b.identificador);
}

bool resuelveCaso() {
    int N = 0;
    cin >> N;

    if (!N) return false;

    PriorityQueue<tRegistro> pq;

    int identificador = 0;
    int periodo = 0;

    for(int i = 0; i<N;i++){
        cin >> identificador >> periodo;

        pq.push({identificador, periodo, periodo});
    }

    int numEnvios = 0;
    cin >> numEnvios;

    tRegistro registro;
    for(int i = 0; i < numEnvios; i++){
        registro = pq.top(); pq.pop();

        cout << registro.identificador << "\n";

        registro.tiempo += registro.periodo;

        pq.push(registro);
    }

    cout << "---\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entrada4.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}