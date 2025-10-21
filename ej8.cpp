// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
#include <vector>
using namespace std;

bool resuelveCaso() {
    int N = 0;
    if(!(cin>>N)) return false;
    int A, B;
    cin >> A >> B;

    PriorityQueue<int, greater<int>> pilasGrandes;
    PriorityQueue<int, greater<int>> pilasPeq;
    vector<int> pilasGrandesUsadas;
    vector<int> pilasPeqUsadas;

    int duracion;
    for(int i = 0;i<A;i++){
        cin >> duracion;
        pilasGrandes.push({duracion});
    }

    for(int i = 0; i<B;i++){
        cin >> duracion;
        pilasPeq.push({duracion});
    }

    int pilaG = 0;
    int pilaP = 0;
    int i = 0; // Para iterar los drones
    int suma = 0;

    // Mientras sigan habiendo pilas
    while(!pilasGrandes.empty() && !pilasPeq.empty()){

        suma = 0;
        i = 0;

        // Cargamos cada dron mientras aun haya una pila de cada tipo
        while(i < N && (!pilasGrandes.empty() && !pilasPeq.empty())){
            pilaG = pilasGrandes.top(); pilasGrandes.pop();
            pilaP = pilasPeq.top(); pilasPeq.pop();

            if(pilaG > pilaP) {
                suma+=pilaP;
                pilasGrandesUsadas.push_back(pilaG - pilaP);
            }  
            else if(pilaG < pilaP) {
                suma+=pilaG;
                pilasPeqUsadas.push_back(pilaP - pilaG);
            }
            else suma+=pilaG;

            i++;
        }

        cout << suma << " ";

        // Colocamos las pilas con carga en las cajas
        for(int k = 0; k<pilasGrandesUsadas.size();k++){
            pilasGrandes.push(pilasGrandesUsadas[k]);
        }
        for(int k = 0; k<pilasPeqUsadas.size();k++){
            pilasPeq.push(pilasPeqUsadas[k]);
        }

        pilasGrandesUsadas.clear();
        pilasPeqUsadas.clear();
    }

    cout << "\n";


    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entrada8.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}