// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include "unordered_map"
#include "queue"
using namespace std;

struct tTema{
    string nombre;
    int citas;
    int orden;
};

bool operator<(const tTema& a, const tTema& b){
    return a.citas > b.citas ||
        (a.citas == b.citas && a.orden > b.orden);
}

bool resuelveCaso() {
    int N = 0;
    if(!(cin>>N)) return false;

    IndexPQ<tTema> pq(N);
    unordered_map<string, tTema> temas;

    string caso;
    string nombre;
    int num = 0;
    int orden = 0;
    for(int i = 0;i<N;i++){
        cin >> caso;

        if(caso == "C"){
            cin >> nombre >> num;
            if(temas.count(nombre) == 0){
                temas.insert({nombre, {nombre, num, orden}});
                pq.push(orden, {nombre, num, orden});
            }
            else{
                pq.update(temas[nombre].orden, {nombre, temas[nombre].citas + num, orden});
            }
            orden++;

        }
        else if(caso == "E"){
            cin >> nombre >> num;
            pq.update(temas[nombre].orden, {nombre, temas[nombre].citas - num, temas[nombre].orden});
        }
        else{ 
            int k = 0;
            queue<pair<int, tTema>> cola;
            tTema tema;
            int elem = 0;
            while(!pq.empty() && k < 3 && (pq.top().prioridad.citas > 0)){
                elem = pq.top().elem;
                tema = pq.top().prioridad; 
                pq.pop();

                cout << k+1 << " " << tema.nombre << "\n";
                cola.push({elem, tema});
                k++;
            }

            while(!cola.empty()){
                elem = cola.front().first;
                tema = cola.front().second; 
                cola.pop();

                pq.push(elem, tema);
            }
        }
    }

    cout << "---\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entrada9.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}