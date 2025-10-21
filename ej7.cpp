// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

using lli = long long int;

const string SI = "SI";
const string NO = "NO";

struct tTarea{
    bool periodica;
    lli periodo;
    lli inicio;
    lli finalizacion;
};

bool operator<(const tTarea& a, const tTarea& b){
    return a.inicio < b.inicio;
}

bool resuelveCaso() {
    lli N, M, T;
    if(!(cin>>N)) return false;
    cin >> M >> T;

    PriorityQueue<tTarea> pq;
    lli inicio, finalizacion, periodo;

    // Leemos sin periodo
    for(int i = 0; i < N;i++){
        cin >> inicio >> finalizacion;
        pq.push({false, 0, inicio, finalizacion});
    }

    // Leemos con periodo
    for(int i = 0; i < M;i++){
        cin >> inicio >> finalizacion >> periodo;
        pq.push({true, periodo, inicio, finalizacion});
    }

    lli tiempoPasado = 0;
    bool superpuesto = false;
    tTarea tarea;

    while((tiempoPasado <= T) && !pq.empty() && (!superpuesto)){
        tarea = pq.top(); pq.pop();

        if(tarea.inicio < tiempoPasado) {
            superpuesto = true;
        }

        else{
            tiempoPasado = tarea.finalizacion;

            if(tarea.periodica){
                tarea.inicio+=tarea.periodo;
                tarea.finalizacion+=tarea.periodo;
                pq.push(tarea);
            }
        }
    }

    if(superpuesto){
        cout << SI << "\n";
    }
    else cout << NO << "\n";


    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entrada7.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}