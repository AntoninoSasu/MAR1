// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct tCaja{
    int id;
    int tiempo;
};

bool operator<(const tCaja& a, const tCaja& b){
    return a.tiempo < b.tiempo ||
        (a.tiempo == b.tiempo && a.id < b.id);
}

bool resuelveCaso() {
    int N = 0;
    int C = 0;
    cin >> N >> C;
    if(N == 0 && C == 0) return false;

    PriorityQueue<tCaja> pq;

    int tiempoAtendido = 0;

    // Llenamos primero las cajas con los clientes
    for(int i = 0; i < N && i < C; i++){
        cin >> tiempoAtendido;
        pq.push({i+1, tiempoAtendido});
    }

    if(N > C) cout << C + 1 << "\n";
    else if(N == C) cout << pq.top().id << "\n";
    else{
        tCaja caja;
        for(int i = N; i < C;i++){
            caja = pq.top(); pq.pop();
            cin >> tiempoAtendido;
            caja.tiempo += tiempoAtendido;
            pq.push(caja);
        }

        cout << pq.top().id << "\n";
    }

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entrada6.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}