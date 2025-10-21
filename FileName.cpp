// Antonino Sasu y Miguel Angel Molina

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include "PriorityQueue.h"
using namespace std;

//Definicion del tipo de las baterias
/*
    Para las baterias iniciales vamos a usar una cola de prioridad de menor a mayor, esto lo hacemos porque las baterias que primero se van
    a quedar sin carga son las que tienen un carga mas peque�a y las que vamos a tener que reemplazar primero

    Para las de repuesto vamos a usar una cola normal, ya que segun el enunciado estas baterias se escogen segun el orden que se da en el input
    para luego colocarlas en las baterias activas

*/


struct bateria {
    //Definicion del tipo de las baterias
    int id; //identificador
    int carga; //carga de la bateria
    //otro/s campo/s
    int tiempo;
    //definicion del operador de comparacion
};

// ordenamos de menor a mayor segun la carga, y son iguales escogemos el de menor id
// (el que se mostro antes en el input segun las normas del enunciado)
bool operator<(const bateria& a, const bateria& b) {
    return a.carga < b.carga ||
        (a.carga == b.carga && a.id < b.id);
}

bool resuelveCaso() {
    int B;
    cin >> B;
    if (!cin)
        return false;

    int carga = 0;
    PriorityQueue<bateria> baterias;

    //Lee las B baterias y almacenalas en una estructura llamada baterias
    for (int i = 0; i < B; i++) {
        cin >> carga;

        // el coste del push en una pq es de O(logN) con N == numero de elemetos de la pq
        //las baterias iniciales comienzan en tiempo 0
        baterias.push({ i + 1, carga, 0});
    }

    //Lee las R baterias de repuesto y almacenalas en una estructura llamada repuestos
    int R = 0;
    cin >> R;

    queue<bateria> repuesto;
    for (int i = 0; i < R; i++) {
        cin >> carga;

        // el coste de push en una cola normal es de O(1), ya que solo se a�ade al final del contenedor sin 
        // inlfuencia del numero de elementos que tiene
        // luego se actualiza el tiempo de las de repuesto
        repuesto.push({ i + 1 + B, carga, 0});
    }

    int Z, T;
    cin >> Z >> T;

    //Escribe el algoritmo para resover el problema

    int tiempo = 0;
    bateria bat;
    bool repuestoVacio = false;


    // El coste de baterias.empty es de O(1) porque solo es una comprobacion
    // En el peor caso el numero de iteraciones maximo (acotado) de este bucle es el numero de baterias inciales
    // mas el numero de baterias de repuesto, ya que cuando hayamos agotado todas el bucle siempre acabare
    // es decir O(B+R)

    //Luego dentro no hay ningun otro bucle y la operacion con el mayor coste es pop y push con coste O(logN), luego el coste del 
    // algoritmo es de O((B+R)*logN) para N = numero de elemetos de la pq (numero de baterias)
    while (tiempo < T && !baterias.empty()) {
        // el coste de baterias.top es de O(1) ya que solo miras el elemento del frente del heap de minimos
        // el coste de baterias.pop es de O(logN) para N == numero de elementos de la pq
        bat = baterias.top(); baterias.pop();

        // Actualizamos el tiempo, nos basamos en la diferencia del tiempo actual con la que se puso la bateria
        // y luego a�adimos el tiempo indicado de la carga
        tiempo = tiempo - bat.tiempo + bat.carga;

        // Se descarga la bateria
        bat.carga -= Z;

        // Si ya no tiene carga le buscamos una de repuesto
        if (bat.carga <= 0) {
            // Si hay de repuesto lo quitamos de la cola y lo metemos en las baterias activas, con la carga 
            // actualizada en base al tiempo actual (cuando se quedo a cero la anterior)
            if (!repuesto.empty()) {
                bat = repuesto.front(); repuesto.pop();
                bat.tiempo = tiempo;
                baterias.push(bat);
            }
            // Si no hay mas de repuesto, lo marcamos para la salida y vamos al siguiente
            // que se hace en la salida como (size == B)

        }
        // Si no la metemos otra vez en la cola con la carga disminuida
        else {
            // Y actualizamos la bateria en base al tiempo actual
            bat.tiempo = tiempo;
            baterias.push(bat);
        }

    }
 
    if (baterias.empty()) {
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    }
   else {
        if (baterias.size() == B) {
            cout << "CORRECTO\n";
        }
        else {

            cout << "FALLO EN EL SISTEMA\n";

            //Imprimir las baterias
            while (!baterias.empty()) {
                cout << baterias.top().id << " " << baterias.top().carga + baterias.top().tiempo << "\n";
            }

        }
    }
 

   //Analiza el coste de forma justificada
    /*
        Hemos analizado el coste de cada operacion y el coste de los bucle y hemos concluido
        que el coste del algoritmo es de O((B+R)*logN) para N == numero de baterias en la pq
        Hay mas explicaciones de los costes en la parte que hemos hecho el algoritmo
    */
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
