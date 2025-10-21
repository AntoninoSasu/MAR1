// Antonino Sasu y Miguel Ángel Molina

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

using lli = long long int;

lli calcularEsfuerzo(PriorityQueue<lli>& pq){
    lli esfuerzo = 0;
    lli suma = 0;
    lli num1, num2;

    while(pq.size() > 1){
        num1 = pq.top(); pq.pop();
        num2 = pq.top(); pq.pop();

        suma = num1 + num2;

        esfuerzo += suma;

        pq.push(suma);
    }

    return esfuerzo;

}

bool resuelveCaso() {
    int N = 0;
    cin >> N;
    if(N == 0) return false;

    PriorityQueue<lli> pq;
    lli numero = 0;

    for(int i = 0; i < N; i++){
        cin >> numero;
        pq.push(numero);
    }

    lli esfuerzo = calcularEsfuerzo(pq);

    cout << esfuerzo << "\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("entrada3.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
      
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}