#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#include "dynamicDS.h"

/*
    La clase Dynamic_Structures se ha definido exclusivamente con
    métodos estáticos, ya que se ha concebido como una clase utilitaria.
    Adicionalmente, dado que Dynamic_Structures es un template, es
    necesario hacer uso de sus métodos establecienco el "meta-parámetro"
    en cada una de sus respectivas llamadas.
*/

int main(void) {


    DS<int>* G1;

    cout << "nodo que no apunta a nada" << endl;



    Dynamic_Structures<int>::create(&G1, GRAPH);

    cout << "OK\n";

    cout << "Probando inserción en grafo... ";

    Dynamic_Structures<int>::InsertadorEstructuralG(&G1, "01N", "San Salvador", 0);

    Dynamic_Structures<int>::InsertadorEstructuralG(&G1, "02N", "La Libertad", 0);

    Dynamic_Structures<int>::InsertadorEstructuralG(&G1, "03N", "San Miguel", 0);

    Dynamic_Structures<int>::InsertadorEstructuralG(&G1, "04N", "Chalatenango", 0);

    Dynamic_Structures<int>::InsertadorEstructuralG(&G1, "05N", "La Union", 0);

    Dynamic_Structures<int>::InsertadorEstructuralG(&G1, "0102N", "Col Escalon", 0);

    Dynamic_Structures<int>::InsertadorEstructuralG(&G1, "06N", "Sonsonate", 0);





    delete G1;

    return 0;
};



// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
