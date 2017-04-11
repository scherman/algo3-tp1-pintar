#include <iostream>
#include <list>
#include <array>
int BTPintar(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar);
int BTPintarMejorado(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar);
int pintarDinamico(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar, int ***calculados);
int pintarDinamicoBU(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar);


class Contador
{
    public:
        static int valor; // declares the static member variable
    };
int Contador::valor = 0; // defines the static member variable (we'll discuss this line below)


void imprimirResumen(int input[], int n, int resBT, int resBTMejorado, int resDinamicaTD, int cantSolucionesBT, int cantSolucionesBTMejorado, int cantSolucionesDinamicaTD) {
    std::cout << "[ ";
    for(int i=0; i < n; ++i) std::cout << input[i] << " ";
    std::cout << "] | Rta: " << resBT << "(BT) vs " << resBTMejorado << "(BT+) vs " << resDinamicaTD << "(dinTD), cantSolucionesCalculadas: ";
    std::cout << cantSolucionesBT << "(BT) vs " << cantSolucionesBTMejorado << "(BT+) vs " << cantSolucionesDinamicaTD << "(dinTD)" << std::endl;
}

int min3(int a, int b, int c) {
    return std::min(std::min (a,b),c);
}

void imprimirSolucion(int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar) {
    std::cout << "Solucion " << Contador::valor++ << ": SP=" << sinPintar.size();
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
    int n = 8;

//    int arr[n] = {8,7,6,5,4,3,2,1};
//    int arr[n] = {0,20000000, 5, -111 ,10,15};
//    int arr[n] = {1,2,3,4,5,6,7,8};
    int arr[n] = {0, 7, 1, 2, 2, 1, 5, 0};
//    int arr[n] = {3, 11, 0, 1 ,3, 5, 2, 4, 1, 0, 9,3};
    std::list<int> rojas1;
    std::list<int> azules1;
    std::list<int> sinPintar1;
    int res1 = BTPintar(arr, 0, n-1, rojas1, azules1, sinPintar1);
    int cantSoluciones1 = Contador::valor;

    Contador::valor = 0;

    std::list<int> rojas2;
    std::list<int> azules2;
    std::list<int> sinPintar2;
    int minSinPintar2 = n;
    int res2 = BTPintarMejorado(arr, 0, n-1, rojas2, azules2, sinPintar2, minSinPintar2);
    int cantSoluciones2 = Contador::valor;


    Contador::valor = 0;

    std::list<int> rojas3;
    std::list<int> azules3;
    std::list<int> sinPintar3;
    int minSinPintar3 = n;



    int ***calculados = new int**[n+1];
    for(int k = 0; k < n+1; ++k) {
        calculados[k] = new int*[n+1];
        for(int r = 0; r < n+1; ++r) {
            calculados[k][r] = new int[n+1];
            for(int a = 0; a < n+1; ++a) {
                calculados[k][r][a] = -1;
            }
        }
    }

    int res3 = pintarDinamico(arr, 0, n, rojas3, azules3, sinPintar3, minSinPintar3, calculados);
    int cantSoluciones3 = Contador::valor;
//
    imprimirResumen(arr, n, res1, res2, res3, cantSoluciones1, cantSoluciones2, cantSoluciones3);
//
//    for(int r =0; r < n; r++){
//        for(int a = 0; a < n; a++){
//            std::cout << calculados[12][r][a] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl;
//    for(int r =0; r < n; r++){
//        for(int a = 0; a < n; a++){
//            std::cout << calculados[0][r][a] << " ";
//        }
//        std::cout << std::endl;
//    }

    Contador::valor = 0;

//    std::list<int> rojas4;
//    std::list<int> azules4;
//    std::list<int> sinPintar4;
//    int minSinPintar4 = n;
//    int res4 = pintarDinamicoBU(arr, 0, n, rojas4, azules4, sinPintar4, minSinPintar4);
//    int cantSoluciones4 = Contador::valor;

    return 0;

}

int BTPintar(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar) {
    if (desde > hasta) {
        imprimirSolucion(hasta, rojas, azules, sinPintar);
        return sinPintar.size();
    } else {
        int actual = problema[desde];

        // Llamada al hijo izquierdo (si es válido): pinto 'actual' de rojo
        int minIzq = hasta;
        if (rojas.empty() || rojas.back() < actual) {
            rojas.push_back(actual);
            minIzq = BTPintar(problema, desde + 1, hasta, rojas, azules, sinPintar);
            rojas.pop_back();
        }

        // Llamada al hijo medio (si es válido): pinto 'actual' de azul
        int minMed = hasta;
        if (azules.empty() || azules.back() > actual) {
            azules.push_back(actual);
            minMed = BTPintar(problema, desde + 1, hasta, rojas, azules, sinPintar);
            azules.pop_back();
        }

        // Llamada al hijo derecho: dejo 'actual' sin pintar
        int minDer = hasta;
        sinPintar.push_back(actual);
        minDer = BTPintar(problema, desde + 1, hasta, rojas, azules, sinPintar);
        sinPintar.pop_back();

        return min3(minIzq, minMed, minDer);
    }
}

int BTPintarMejorado(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar) {
    if (sinPintar.size() >= minSinPintar) return hasta;
    if (desde > hasta) {
        imprimirSolucion(hasta, rojas, azules, sinPintar);
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


int pintarDinamico(int problema[], int desde, int hasta, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar, int ***calculados) {
    int longSubproblema = hasta - desde;
    if (sinPintar.size() >= minSinPintar) return hasta;
    if (longSubproblema == 0) {
        imprimirSolucion(hasta, rojas, azules, sinPintar);
        if (sinPintar.size() < minSinPintar) minSinPintar = sinPintar.size();
        calculados[longSubproblema][rojas.size()][azules.size()] = sinPintar.size();
        return sinPintar.size();
    } else {
        // Si lo calcule antes, lo devuelvo
        if (calculados[longSubproblema][rojas.size()][azules.size()] != -1) calculados[longSubproblema][rojas.size()][azules.size()];

        int primerElemento = problema[desde];

        // Llamada al hijo izquierdo (si es válido): pinto 'primerElemento' de rojo
        int minIzq = hasta;
        if (rojas.empty() || rojas.back() < primerElemento) {
            rojas.push_back(primerElemento);
            minIzq = pintarDinamico(problema, desde + 1, hasta, rojas, azules, sinPintar, minSinPintar, calculados);
            rojas.pop_back();
        }

        // Llamada al hijo medio (si es válido): pinto 'primerElemento' de azul
        int minMed = hasta;
        if (azules.empty() || azules.back() > primerElemento) {
            azules.push_back(primerElemento);
            minMed = pintarDinamico(problema, desde + 1, hasta, rojas, azules, sinPintar, minSinPintar, calculados);
            azules.pop_back();
        }

        // Llamada al hijo derecho: dejo 'primerElemento' sin pintar
        int minDer = hasta;
        sinPintar.push_back(primerElemento);
        minDer = pintarDinamico(problema, desde + 1, hasta, rojas, azules, sinPintar, minSinPintar, calculados);
        sinPintar.pop_back();

        // Guardo lo calculado
        calculados[longSubproblema][rojas.size()][azules.size()] = min3(minIzq, minMed, minDer);
//        std::cout << "Guardando m[" << desde << "][" << rojas.size() << "][" << azules.size() << "]=" << min3(minIzq, minMed, minDer) << std::endl;
        return min3(minIzq, minMed, minDer);
    }
}


///*
// * Si #problema = 5:
// * CB: #x = 0: (resolví 5 elementos)
// *          0 1 2 3 4 5
// *        0 5 4 3 2 1 0
// *        1 4 3 2 1 0 -
// *        2 3 2 1 0 - -
// *        3 2 1 0 - - -
// *        4 1 0 - - - -
// *        5 0 - - - - -
// * si #x = 1: (resolví 4 elementos)
// *          0     ...                 #r                           #r+1 .. 5
// *        0
// *        ...
// *        #a              min(f(n1, n2, sinUno(x),r,a)+1)      n1=f(sinUno(x),masUno(r),a)
// *        #a+1              n2=f(sinUno(x),r,masUno(a))
// *        ...
// *        5
//  * si #x = 5: (resolví 0 elementos)
// *                        #a=0                               1
// *        #r=0   min(n1, n2, f(sinUno(x),r,a)+1)      n1=f(sinUno(x),masUno(r),a)
//          1      n2=f(sinUno(x),r,masUno(a))
// *        ...
// *        5
// *
// *obs: para calcular m[i,j] necesio tener m[i+1, j], m[i, j+1]
// *     para calcular m[i-1, j+1] necesito tener m[i, j+1], y m[i-1, j+2]
// *     => Estoy calculando 2 veces m[i, j+1]!
//*/
////f(x + {m}, r, a) = min(f(x, r, a)+1,
////                       f(x, r + {m}, a) si ultimo(r) < m o vacio(r), |x| sino,
////                       f(x, r, a + {m}) si ultimo(r) > m o vacio(a), |x| sino)
////f(vacio, r, a) = |r| + |a|
//int pintarDinamico(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar, int ***calculados) {
//    if (desde > longitud) {
//        imprimirSolucion(longitud, rojas, azules, sinPintar);
//        return sinPintar.size();
//    } else {
//        // Si lo calcule antes, lo devuelvo
////        if (calculados[desde][rojas.size()][azules.size()] != -1) return calculados[desde][rojas.size()][azules.size()];
//
//        int actual = problema[desde];
//
//        // Llamada al hijo izquierdo (si es válido): pinto 'actual' de rojo
//        int minIzq = longitud;
//        if (rojas.empty() || rojas.back() < actual) {
//            rojas.push_back(actual);
//            minIzq = pintarDinamico(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar, calculados);
//            rojas.pop_back();
//        }
//
//        // Llamada al hijo medio (si es válido): pinto 'actual' de azul
//        int minMed = longitud;
//        if (azules.empty() || azules.back() > actual) {
//            azules.push_back(actual);
//            minMed = pintarDinamico(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar, calculados);
//            azules.pop_back();
//        }
//
//        // Llamada al hijo derecho: dejo 'actual' sin pintar
//        int minDer = longitud;
//        sinPintar.push_back(actual);
//        minDer = pintarDinamico(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar, calculados);
//        sinPintar.pop_back();
//
//        // Guardo lo calculado
////        std::cout << "Guardando m[" << desde << "][" << rojas.size() << "][" << azules.size() << "]=" << min3(minIzq, minMed, minDer) << std::endl;
////        calculados[desde][rojas.size()][azules.size()] = min3(minIzq, minMed, minDer);
//        return  min3(minIzq, minMed, minDer);
//    }
//}

int pintarDinamicoBU(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar) {
    int calculados[longitud+1][longitud+1][longitud+1];

    // Inicializo caso base (k=0)
    for(int r = 0; r < longitud + 1; ++r){
        for(int a = 0; a < longitud + 1; ++a){
            calculados[0][r][a] = longitud;
        }
    }
    calculados[0][0][0] = 0;

    // Paso inductivo
    for (int k = 1; k < longitud + 1; ++k) {
        for (int r = 0; r < longitud; ++r) {
            for (int a = 0; a < longitud; ++a) {
                calculados[k][r][a] = r + a > longitud || calculados[k-1][r][a] + 1 > longitud? longitud : calculados[k-1][r][a] + 1;
//                std::cout << (rojas.empty() || problema[k-1]) << " entonces calculados[" << k << "][" << r+1 << "][" << a << "] = " << calculados[k][r][a] - 1 << std::endl;
                calculados[k][r+1][a] = rojas.empty() || problema[k-1] > rojas.back() ? calculados[k][r][a] - 1 : longitud;
//                std::cout << (azules.empty() || problema[k-1]) << " entonces calculados[" << k << "][" << r << "][" << a+1 << "] = " << calculados[k][r][a] - 1 << std::endl;
                calculados[k][r][a+1] = azules.empty() || problema[k-1] < azules.back() ? calculados[k][r][a] - 1 : longitud;
            }
        }
    }

    for(int r = 0; r < longitud + 1; ++r){
        for(int a = 0; a < longitud + 1; ++a){
            std::cout << calculados[1][r][a] << " ";
        }
        std::cout << std::endl;
    }

    // Busco solucion en k=longitud
    int min = longitud;
    for(int r = 0; r < longitud + 1; ++r){
        for(int a = 0; a < longitud + 1; ++a){
            min = std::min(min, calculados[longitud][r][a]);
        }
    }
    std::cout << "min: " <<  min << std::endl;
    return min;



//    for(int r = 0; r < longitud + 1; ++r){
//        for(int a = 0; a < longitud + 1; ++a){
//            std::cout << calculados[0][r][a] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl;
//
//    for(int r = 0; r < longitud + 1; ++r){
//        for(int a = 0; a < longitud + 1; ++a){
//            std::cout << calculados[1][r][a] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    for(int k=1; k < longitud+1; k++){
//        for(int r = longitud; r >= 0; r--){
//            for(int a = longitud; a >= 0 ; a--){
//                calculados[k][r][a] = longitud - r - a >= 0 ? longitud - r - a : longitud;
//            }
//        }
//    }
}