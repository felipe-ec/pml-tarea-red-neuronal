#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Nodo {
    int Cod;
    Nodo* punt;
    Nodo** conexiones;
};

Nodo* CreaNodo(int cod, int num_conexiones, Nodo* siguiente_capa) {
    Nodo* nodo = new Nodo;
    nodo->Cod = cod;
    nodo->punt = nullptr;

    if (num_conexiones > 0 && siguiente_capa != nullptr) {
        nodo->conexiones = new Nodo*[num_conexiones];
        for (int i = 0; i < num_conexiones; ++i)
            nodo->conexiones[i] = &siguiente_capa[i];
    } else {
        nodo->conexiones = nullptr;
    }

    return nodo;
}

Nodo* CreaCapa(int cantidad, int conexiones, Nodo* siguiente_capa) {
    Nodo* inicio = nullptr;
    Nodo* anterior = nullptr;

    for (int i = 0; i < cantidad; ++i) {
        Nodo* nuevo = CreaNodo(i + 1, conexiones, siguiente_capa);
        if (!inicio)
            inicio = nuevo;
        else
            anterior->punt = nuevo;
        anterior = nuevo;
    }

    return inicio;
}

Nodo* CreaCapaEntrada(int e, Nodo* siguiente) {
    return CreaCapa(e, 0, siguiente);
}

Nodo* CreaCapaSalida(int s) {
    return CreaCapa(s, 0, nullptr);
}

Nodo** CreaCapasOcultas(int m, int n, Nodo* capa_salida) {
    Nodo** capas = new Nodo*[n];
    Nodo* siguiente = capa_salida;

    for (int i = n - 1; i >= 0; --i) {
        capas[i] = CreaCapa(m, (i == n - 1 ? 0 : m), siguiente);
        siguiente = capas[i];
    }

    return capas;
}

void Recorrido(Nodo* capa) {
    Nodo* actual = capa;
    while (actual) {
        cout << actual->Cod << " ";
        actual = actual->punt;
    }
    cout << endl;
}

int main() {
    string linea;
    getline(cin, linea);
    istringstream iss(linea);

    int e, m, n, s;
    iss >> e >> m >> n >> s;

    Nodo* capa_salida = CreaCapaSalida(s);
    Nodo** capas_ocultas = CreaCapasOcultas(m, n, capa_salida);
    Nodo* capa_entrada = CreaCapaEntrada(e, capas_ocultas[0]);

    cout << "Entrada: ";
    Recorrido(capa_entrada);

    for (int i = 0; i < n; ++i) {
        cout << "CapaOculta" << (i + 1) << ": ";
        Recorrido(capas_ocultas[i]);
    }

    cout << "Salida: ";
    Recorrido(capa_salida);

    cout << (e * m * n * s) << endl;

    return 0;
}