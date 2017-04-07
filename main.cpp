#include <iostream>
#include <list>
#include <array>
int BTPintar(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules);
int BTPintarMejorado(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar);


class Contador
{
    public:
        static int valor; // declares the static member variable
    };
int Contador::valor = 0; // defines the static member variable (we'll discuss this line below)


void imprimirResumen(int input[], int n, int resBT, int resBTMejorado, int cantSolucionesBT, int cantSolucionesBTMejorado) {
    std::cout << "[ ";
    for(int i=0; i < n; ++i) std::cout << input[i] << " ";
    std::cout << "] | Rta: " << resBT << "(BT) vs " << resBTMejorado << "(BT+), cantSolucionesCalculadas: ";
    std::cout << cantSolucionesBT << "(BT) vs " << cantSolucionesBTMejorado << "(BT+)" << std::endl;
}

int min3(int a, int b, int c) {
    return std::min(std::min (a,b),c);
}



void imprimirSolucion(int longitud, std::list<int> &rojas, std::list<int> &azules) {
    std::cout << "Solucion " << Contador::valor++ << ": min=" << longitud - (int) rojas.size() - (int) azules.size();
    std::cout << " | rojas=[ ";
    for (auto v : rojas)
        std::cout << v << " ";
    std::cout << "], azules=[ ";
    for (auto v : azules) {
        std::cout << v << " ";
    }
    std::cout << "]" << std::endl;
}

void imprimirSolucion2(int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar) {
    std::cout << "Solucion " << Contador::valor++ << ": min=" << longitud - (int) rojas.size() - (int) azules.size();
    std::cout << " | rojas=[ ";
    for (auto v : rojas)
        std::cout << v << " ";
    std::cout << "], azules=[ ";
    for (auto v : azules) {
        std::cout << v << " ";
    }
    std::cout << "], sinPintar=[ ";
    for (auto v : sinPintar) {
        std::cout << v << " ";
    }
    std::cout << "]" << std::endl;

}


int main() {
    int n = 12;

//    int arr[n] = {8,7,6,5,4,3,2,1};
    int arr[n] = {0,20000000, 5, -111 ,10,15};
//    int arr[n] = {1,2,3,4,5,6,7,8};
//    int arr[n] = {0, 7, 1, 2, 2, 1, 5, 0};
//    int arr[n] = {3, 11, 0, 1 ,3, 5, 2, 4, 1, 0, 9,3};
    std::list<int> rojas1;
    std::list<int> azules1;
    int res1 = BTPintar(arr, 0, n, rojas1, azules1);
    int cantSoluciones1 = Contador::valor;

    Contador::valor = 0;

    std::list<int> rojas2;
    std::list<int> azules2;
    std::list<int> sinPintar2;
    int minSinPintar2;
    int res2 = BTPintarMejorado(arr, 0, n, rojas2, azules2, sinPintar2, minSinPintar2);
    int cantSoluciones2 = Contador::valor;

    imprimirResumen(arr, n, res1, res2, cantSoluciones1, cantSoluciones2);
    return 0;

}

int BTPintar(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules) {
    if (desde == hasta) {
        imprimirSolucion(hasta,rojas,azules);
        return hasta - (int) rojas.size() - (int) azules.size();
    } else {
        int actual = problema[desde];

        // Llamada al hijo izquierdo (si es válido): pinto 'actual' de rojo
        int minIzq = hasta;
        if (rojas.empty() || rojas.back() < actual) {
            rojas.push_back(actual);
            minIzq = BTPintar(problema, desde + 1, hasta, rojas, azules);
            rojas.pop_back();
        }

        // Llamada al hijo medio (si es válido): pinto 'actual' de azul
        int minMed = hasta;
        if (azules.empty() || azules.back() > actual) {
            azules.push_back(actual);
            minMed = BTPintar(problema, desde + 1, hasta, rojas, azules);
            azules.pop_back();
        }

        // Llamada al hijo derecho: dejo 'actual' sin pintar
        int minDer = 0;
        minDer = BTPintar(problema, desde + 1, hasta, rojas, azules);
//        std::cout << "Nivel " << desde << ": min(" << minIzq << "," << minMed << "," << minDer << ")=" << min3(minIzq, minMed, minDer) << std::endl;
        return min3(minIzq, minMed, minDer);
    }
}

int BTPintarMejorado(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar) {
    if (sinPintar.size() >= minSinPintar) return hasta;
    if (desde == hasta) {
        imprimirSolucion2(hasta,rojas,azules, sinPintar);
        if (sinPintar.size() < minSinPintar) minSinPintar = sinPintar.size();
        return sinPintar.size();
    } else {
        int actual = problema[desde];

        // Llamada al hijo izquierdo (si es válido): pinto 'actual' de rojo
        int minIzq = hasta;
        if (rojas.empty() || rojas.back() < actual) {
            rojas.push_back(actual);
            minIzq = BTPintarMejorado(problema, desde + 1, hasta, rojas, azules, sinPintar, minSinPintar);
            rojas.pop_back();
        }

        // Llamada al hijo medio (si es válido): pinto 'actual' de azul
        int minMed = hasta;
        if (azules.empty() || azules.back() > actual) {
            azules.push_back(actual);
            minMed = BTPintarMejorado(problema, desde + 1, hasta, rojas, azules, sinPintar, minSinPintar);
            azules.pop_back();
        }

        // Llamada al hijo derecho: dejo 'actual' sin pintar
        int minDer = hasta;
        sinPintar.push_back(actual);
        minDer = BTPintarMejorado(problema, desde + 1, hasta, rojas, azules, sinPintar, minSinPintar);
        sinPintar.pop_back();

        return min3(minIzq, minMed, minDer);
    }
}