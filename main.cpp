#include <iostream>
#include <list>
#include <array>
int BTPintar(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar);
int BTPintarMejorado(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar);
int pintarDinamicoBU(int problema[], int hasta);
int pintarDinamicoTD(int problema[], int longitud);
int pintarDinamicoTDEnPosicion(int longOriginal, int longSubproblema, int ultimoRojo, int ultimoAzul, int ***m);

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

void imprimirNivel(int nivel, int ***calculados, int n) {
    std::cout << std::endl;
    for(int r =0; r < n; r++){
        for(int a = 0; a < n; a++){
            std::cout << calculados[nivel][r][a] << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    int n = 200;
//    int ar20[n] = {10, 3, 10, 11, 10, 4, 11, 10};
//    int arr[n] = {1,2,3,4,5,6,7,8};

//    int arr[n] = {8,7,6,5,4,3,2,1};
//    int arr[n] = {0,20000000, 5, -111 ,10,15};
//    int arr[n] = {0, 7, 1, 2, 2, 1, 5, 0};
//    int arr[n] = {3, 11, 0, 1 ,3, 5, 2, 4, 1, 0, 9,3};

//    int arr[n] = {9, 7, 8, 5, 6, 6}; // t1 ok
//    int arr[n] = {1, 3, 2, 5, 4, 4}; // t2 ok
//    int arr[n] = {1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14, 17, 16, 19, 18, 18}; // t3 ok
//      int arr[n] = {1,3,2,5,4,7,6,9,8,11,10,13,12,15,14,17,16,19,18,21,20,23,22,25,24,27,26,29,28,31,30,33,32,35,34,37,36,39,38,41,40,43,42,45,44,47,46,49,48,51,50,53,52,55,54,57,56,59,58,61,60,63,62,65,64,67,66,69,68,71,70,73,72,75,74,77,76,79,78,81,80,83,82,85,84,87,86,89,88,91,90,93,92,95,94,97,96,99,98,101,100,103,102,105,104,107,106,109,108,111,110,113,112,115,114,117,116,119,118,121,120,123,122,125,124,127,126,129,128,131,130,133,132,135,134,137,136,139,138,141,140,143,142,145,144,147,146,149,148,151,150,153,152,155,154,157,156,159,158,161,160,163,162,165,164,167,166,169,168,171,170,173,172,175,174,177,176,179,178,181,180,183,182,185,184,187,186,189,188,191,190,193,192,195,194,197,196,199,198,198}; //t4 ok
//    int arr[n] = {9, 3, 2, 11, 8, 10, 8, 5, 10, 2, 4}; // t5 ok
//    int arr[n] = {6, 11, 2, 5, 3, 2, 3, 12, 1, 3, 8}; //t6 ok
//    int arr[n] = {3, 7, 8, 1, 10, 2, 11, 10, 4, 11, 10}; //t7 ok
//    int arr[n] = {7, 7, 10, 12, 7, 3, 11 ,7 ,10, 10, 7}; //t8 ok
//    int arr[n] = {10 ,5 ,12, 7 ,9 ,12 ,7 ,3 ,10 ,9, 10}; //t9 ok
//      int arr[n] = {2, 10, 8, 5 ,3 ,7 ,7 ,7 ,5 ,12 ,11}; // t10 ok
//      int arr[n] = {4 ,7 ,7 ,3 ,10 ,3 ,10 ,8 ,10 ,1 ,11 }; // t11 ok
//      int arr[n] = {5, 8, 5 ,6 ,12 ,6 ,1 ,8 ,5 ,11 ,3 }; // t12 ok
//      int arr[n] = {1 ,11 ,10 ,1 ,1 ,12 ,9 ,4 ,12 ,11 ,5}; // t13 ok
//      int arr[n] = {1 ,5 ,10 ,1 ,8 ,9 ,3, 6 ,2 ,8 ,5 }; // t14 ok
// int arr[n] = {59,89,46,23,96,31,4,90,74,17,68,96,49,4,31,80,44,36,40,93,13,93,14,26,82,75,1,81,97,79,93,56,92,30,7,83,38,52,67,34,64,50,68,44,88,35,59,26,66,85,76,17,37,17,38,63,7,24,35,78,77,22,66,29,31,92,29,82,83,80,10,57,38,13,24,49,3,89,74,100,9,40,53,99,34,46,97,96,7,43,55,43,13,45,17,66,17,95,62,82,19,93,20,51,32,17,98,80,37,63,75,18,96,51,75,40,35,5,88,39,53,82,78,84,98,81,38,2,42,61,9,87,43,53,85,6,37,86,41,17,99,56,33,37,8,80,21,6,16,58,7,52,64,90,71,41,57,59,29,15,100,13,13,42,27,80,11,13,10,85,31,15,49,42,41,72,15,13,34,42,18,9,16,15,31,30,55,81,99,9,83,52,2,39,88,79,57,43,29,94}; // t15 ok
//int arr[n] = {78,19,44,34,53,59,20,30,45,85,96,42,60,70,54,27,72,69,18,18,23,31,74,45,95,45,57,88,80,29,32,72,66,96,77,63,75,76,82,77,53,70,59,47,78,39,54,4,87,89,7,19,19,78,86,81,99,56,45,36,81,13,69,60,3,10,93,70,94,7,21,12,92,47,75,53,98,90,71,83,24,17,72,75,5,29,32,67,65,58,57,43,68,56,52,76,93,93,55,47,20,8,100,60,84,51,2,39,15,33,78,40,12,47,57,67,49,64,48,92,19,46,95,33,75,51,28,80,92,51,84,46,46,17,63,43,33,86,62,31,78,55,45,27,21,26,87,46,17,51,100,51,46,23,74,58,89,87,4,77,55,35,85,72,3,97,21,83,2,19,82,58,16,42,72,31,7,71,81,10,2,89,66,35,69,64,94,5,46,23,72,33,83,79,32,89,69,72,12,75} ; // t16 ok
//    int arr[n] = {59,99,45,20,64,98,37,98,57,82,3,84,89,37,47,61,53,64,5,86,98,5,24,10,34,57,100,15,20,68,33,51,56,58,30,46,51,79,25,34,4,42,33,47,94,51,66,38,53,93,70,94,45,65,34,86,12,87,14,88,42,31,65,79,25,70,17,79,39,40,34,99,29,46,98,8,27,80,43,52,60,23,25,74,54,75,58,78,7,4,35,31,66,57,78,56,59,66,88,60,45,6,70,71,12,12,96,40,91,63,89,61,62,87,66,30,78,99,57,46,45,96,3,1,8,81,24,2,27,79,1,37,27,88,7,2,78,25,20,72,69,15,24,28,10,5,44,71,60,76,86,86,30,71,49,49,56,37,58,41,20,38,1,18,55,91,95,16,2,85,69,42,51,42,48,76,85,1,3,24,7,86,23,95,42,91,19,43,62,37,56,46,11,67,61,31,2,62,72,9}; // t17
//    int arr[n] = {20,22,28,23,18,50,57,98,59,40,36,9,94,21,88,10,88,99,100,87,29,29,68,31,88,91,14,53,35,33,17,67,60,64,14,14,61,80,4,98,31,10,22,84,14,12,4,50,41,67,39,14,56,98,89,6,47,31,71,49,21,32,64,27,68,49,6,85,10,55,9,29,77,21,89,4,65,94,15,22,91,16,31,56,31,35,4,22,17,86,43,18,90,93,59,78,38,83,3,79,65,6,42,60,85,73,52,7,51,38,3,79,47,76,76,59,64,1,46,22,83,64,99,74,13,15,79,77,92,94,93,23,30,61,37,77,62,80,23,22,54,77,5,59,80,73,22,25,26,21,78,78,45,88,49,12,37,78,9,80,68,73,46,20,23,31,29,77,39,19,56,2,74,88,100,59,40,41,15,22,38,22,100,39,3,53,37,92,28,62,43,48,59,23,63,72,66,76,94,33}; //t18 ok
//    int arr[n] = {72,47,1,76,1,35,64,73,55,82,52,96,8,64,57,37,18,52,19,71,84,35,65,36,51,40,81,32,14,99,27,38,99,3,47,26,91,5,80,24,31,65,2,15,79,25,95,52,52,92,80,45,55,92,41,6,13,68,42,79,74,10,64,28,25,11,61,81,76,52,56,36,9,39,55,95,44,96,79,5,18,53,100,69,42,95,11,37,25,49,18,70,50,91,92,25,23,4,41,75,87,70,81,3,25,36,95,67,74,42,9,54,64,43,88,92,2,44,77,12,77,8,23,87,60,79,60,25,58,82,40,14,29,24,66,22,82,55,27,2,90,87,92,97,73,62,13,54,50,37,28,13,90,66,59,78,55,64,39,33,62,26,100,49,79,60,96,89,28,36,24,42,25,59,60,89,54,1,24,48,55,79,44,36,85,99,83,35,4,22,87,16,31,56,43,1,85,25,99,55}; //t19 ok
    int arr[n] = {45,39,34,24,99,91,85,98,93,18,6,5,9,90,72,72,58,82,15,5,95,38,60,50,94,11,84,27,60,45,57,67,23,32,44,82,85,25,5,22,74,80,4,40,100,25,79,64,71,53,80,10,97,27,77,22,12,26,50,78,98,75,25,72,31,3,69,69,67,20,71,21,34,47,37,47,96,48,100,95,99,60,96,98,48,55,96,71,99,89,44,87,29,78,60,35,33,63,2,69,65,3,10,76,65,5,67,51,26,94,94,84,88,9,51,48,81,41,49,43,69,8,13,18,57,65,93,53,71,31,65,23,56,65,60,89,63,87,9,4,22,1,7,51,60,61,97,76,38,93,51,8,46,57,49,7,52,22,43,7,89,32,71,86,73,50,50,32,58,96,9,35,6,5,60,19,36,71,10,89,54,96,57,66,56,83,57,60,1,35,23,55,26,66,89,39,95,82,25,4}; // t20 ok
    int res = pintarDinamicoBU(arr, n);
    std::cout << "Rta: " << res << std::endl;
//    std::list<int> rojas1;
//    std::list<int> azules1;
//    std::list<int> sinPintar1;
//    int res1 = BTPintar(arr, 0, n, rojas1, azules1, sinPintar1);
//    int cantSoluciones1 = Contador::valor;
//
//    Contador::valor = 0;
//
//    std::list<int> rojas2;
//    std::list<int> azules2;
//    std::list<int> sinPintar2;
//    int minSinPintar2 = n;
//    int res2 = BTPintarMejorado(arr, 0, n, rojas2, azules2, sinPintar2, minSinPintar2);
//    int cantSoluciones2 = Contador::valor;
//
//
//    Contador::valor = 0;
////
//    std::list<int> rojas3;
//    std::list<int> azules3;
//    std::list<int> sinPintar3;
//    int minSinPintar3 = n;
//
////
////
//    int ***calculados = new int**[n+1];
//    for(int k = 0; k < n+1; ++k) {
//        calculados[k] = new int*[n+1];
//        for(int r = 0; r < n+1; ++r) {
//            calculados[k][r] = new int[n+1];
//            for(int a = 0; a < n+1; ++a) {
//                calculados[k][r][a] = -1;
//            }
//        }
//    }
//
//    int res3 = pintarDinamico(arr, 0, n, rojas3, azules3, sinPintar3, minSinPintar3, calculados);
//    std::cout << "rta:" << res3 << std::endl;
//    int cantSoluciones3 = Contador::valor;
//
//    imprimirResumen(arr, n, res1, res2, res3, cantSoluciones1, cantSoluciones2, cantSoluciones3);
////
//
//    for (int i = 0; i < n + 1; ++i) {
//        imprimirNivel(i, calculados, n);
//    }
//
//    Contador::valor = 0;

//    std::list<int> rojas4;
//    std::list<int> azules4;
//    std::list<int> sinPintar4;
//    int minSinPintar4 = n;
//    int res4 = pintarDinamicoBU(arr, 0, n, rojas4, azules4, sinPintar4, minSinPintar4);
//    int cantSoluciones4 = Contador::valor;

    return 0;

}

int BTPintar(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar) {
    int longSubproblema = longitud - desde;
    if (longSubproblema == 0) {
        imprimirSolucion(longitud, rojas, azules, sinPintar);
        return sinPintar.size();
    } else {
        int primerElem = problema[desde];

        // Llamada al hijo izquierdo (si es válido): pinto 'primerElem' de rojo
        int minRamaR = longitud;
        if (rojas.empty() || rojas.back() < primerElem) {
            rojas.push_back(primerElem);
            minRamaR = BTPintar(problema, desde + 1, longitud, rojas, azules, sinPintar);
                rojas.pop_back();
        }

        // Llamada al hijo medio (si es válido): pinto 'primerElem' de azul
        int minRamaA = longitud;
        if (azules.empty() || azules.back() > primerElem) {
            azules.push_back(primerElem);
            minRamaA = BTPintar(problema, desde + 1, longitud, rojas, azules, sinPintar);
            azules.pop_back();
        }

        // Llamada al hijo derecho: dejo 'primerElem' sin pintar
        int minRamaSP = longitud;
        sinPintar.push_back(primerElem);
        minRamaSP = BTPintar(problema, desde + 1, longitud, rojas, azules, sinPintar);
        sinPintar.pop_back();

        return min3(minRamaR, minRamaA, minRamaSP);
    }
}

int BTPintarMejorado(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar) {
    int longSubproblema = longitud - desde;
    if (sinPintar.size() >= minSinPintar) return longitud;
    if (longSubproblema == 0) {
        imprimirSolucion(longitud, rojas, azules, sinPintar);
        if (sinPintar.size() < minSinPintar) minSinPintar = sinPintar.size();
        return sinPintar.size();
    } else {
        int actual = problema[desde];

        // Llamada al hijo izquierdo (si es válido): pinto 'actual' de rojo
        int minRamaR = longitud;
        if (rojas.empty() || rojas.back() < actual) {
            rojas.push_back(actual);
            minRamaR = BTPintarMejorado(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar);
            rojas.pop_back();
        }

        // Llamada al hijo medio (si es válido): pinto 'actual' de azul
        int minRamaA = longitud;
        if (azules.empty() || azules.back() > actual) {
            azules.push_back(actual);
            minRamaA = BTPintarMejorado(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar);
            azules.pop_back();
        }

        // Llamada al hijo derecho: dejo 'actual' sin pintar
        int minRamaSP = longitud;
        sinPintar.push_back(actual);
        minRamaSP = BTPintarMejorado(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar);
        sinPintar.pop_back();

        return min3(minRamaR, minRamaA, minRamaSP);
    }
}

int pintarDinamicoBU(int problema[], int longitud) {

    int ***m= new int**[longitud+1];
    for(int k = 0; k < longitud+1; ++k) {
        m[k] = new int*[longitud+1];
        for(int r = 0; r < longitud+1; ++r) {
            m[k][r] = new int[longitud+1];
            for(int a = 0; a < longitud+1; ++a) {
                m[k][r][a] = -1;
            }
        }
    }

    // Caso base
    m[0][0][0] = 0;

    /*
     * i: "Nros. de elemento" (i.e hasta indice+1)
     * r: "Nro de elemento del ultimo rojo que pinte"
     * a: "Nro de elemento del ultimo azul que pinte"
     */
    for (int i = 1; i < longitud + 1; ++i) {
//        std::cout << "Nivel " << i << std::endl;
        /* Completo anteriormente calculados e invalido :
         *       0   1  i-1   i   n
         * 0     x   x   x   -1  -1
         * 1     x   x   x   -1  -1
         * i-1   x   x   x   -1  -1
         * i    -1  -1  -1    x  -1
         * n    -1  -1  -1   -1  -1
         */
        for (int r = 0; r < i; ++r) {
            for (int a = 0; a < i; ++a) {
                m[i][r][a] = std::min(m[i-1][r][a] + 1, longitud);
            }
        }
        m[i][i][i] = longitud;

        /* Completo columna derecha:
         *       0   1  i-1   i   n
         * 0     x   x   x    x  -1
         * 1     x   x   x    x  -1
         * i-1   x   x   x    x  -1
         * i    -1  -1  -1    x  -1
         * n    -1  -1  -1   -1  -1
         */
        for (int a = 0; a < i; ++a) {
            int min = m[i-1][0][a];
            for (int r = 1; r < i; ++r) {
                if (m[i - 1][r][a] < min && problema[r-1] < problema[i-1]) min = m[i - 1][r][a];
            }
            m[i][i][a] = min;
        }


        /* Completo columna derecha:
         *       0   1  i-1   i   n
         * 0     x   x   x    x  -1
         * 1     x   x   x    x  -1
         * i-1   x   x   x    x  -1
         * i     x   x   x    x  -1
         * n    -1  -1  -1   -1  -1
         */
        for (int r = 0; r < i; ++r) {
            int min = m[i-1][r][0];
            for (int a = 1; a < i; ++a) {
                if (m[i - 1][r][a] < min && problema[a-1] > problema[i-1]) min = m[i - 1][r][a];
            }
            m[i][r][i] = min;
        }

//        for (int a = 0; a < longitud + 1; ++a) {
//            for (int r = 0; r < longitud + 1; ++r) {
//                std:: cout << m[i][r][a] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
    }

    int min = longitud;
//    for (int i = 0; i < longitud + 1; ++i) {
//        int minI = std::min(m[longitud][longitud][i], m[longitud][i][longitud]);
//        if (minI < min) min = minI;
//    }

    for (int a = 0; a < longitud + 1; ++a) {
        for (int r = 0; r < longitud + 1; ++r) {
            if (m[longitud][a][r] < min) min = m[longitud][a][r];
        }
    }
    return min;
}

int pintarDinamicoTDEnPosicion(int longOriginal, int longSubproblema, int ultimoRojo, int ultimoAzul, int ***m){
    if (m[longSubproblema][ultimoRojo][ultimoAzul] != -1) return m[longSubproblema][ultimoRojo][ultimoAzul];
    if (longSubproblema == 0) {
        // Caso base: f(0, 0, 0) = 0
        return 0;
    } else {
        int min = longOriginal;
        if (r == a) {
            // Caso 1 (pinté de rojo y de azul al último): es inválido, entonces devuelvo el máximo.  
            min = longOriginal;
        } else if (r == i && a < i) {
            // Caso 2 (pinté de rojo al último): me fijo cual es el último rojo anterior al cual lo puedo enganchar y me da el óptimo.
            for (int k=0; k < i; k++) {
                int minConRojoActual = f(longOriginal, longSubproblema - 1, k, ultimoAzul, m);
                min = std::min(min, minConRojoActual);
            }
        } else if (r < i && a == i) {
            // Caso 3 (pinté de azul al último): me fijo cual es el último azul anterior al cual lo puedo enganchar y me da el óptimo.
            for (int k=0; k < i; k++) {
                int minConAzulActual = f(longOriginal, longSubproblema - 1, ultimoRojo, k, m);
                min = std::min(min, minConAzulActual);
            }
        } else if (r < i && a < i) {
            // Caso 4 (no pinté el último elemento): devuelvo el resultado óptimo sin ese elemnto + 1 (por el nuevo que no pinté)
            min = f(longOriginal, longSubproblema - 1, ultimoRojo, ultimoAzul, m) + 1;
        }
        
        // Guardo resultado calculado para esta posicion
        m[longSubproblema][ultimoRojo][ultimoAzul] = min;
        
        return m[longSubproblema][ultimoRojo][ultimoAzul];
    }
}

int pintarDinamicoTD(int problema[], int longitud) {
    int ***calculados = new int**[longitud+1];
    for(int i = 0; i < longitud+1; ++i) {
    calculados[i] = new int*[longitud+1];
        for(int r = 0; r < longitud+1; ++r) {
        calculados[i][r] = new int[n+1];
            for(int a = 0; a < longitud+1; ++a) {
                calculados[i][r][a] = -1;
            }
        }
    }
}

//int pintarDinamico(int problema[], int desde, int longitud, std::list<int> &rojas, std::list<int> &azules, std::list<int> &sinPintar, int &minSinPintar, int ***calculados) {
//    // print
//    std::cout << "rojas: [ ";
//    for (std::list<int>::iterator it=rojas.begin(); it != rojas.end(); ++it) std::cout << *it << " ";
//    std::cout << "], ";
//    std::cout << "azules: [ ";
//    for (std::list<int>::iterator it=azules.begin(); it != azules.end(); ++it) std::cout << *it << " ";
//    std::cout << "], ";
//    std::cout << "sp: [ ";
//    for (std::list<int>::iterator it=sinPintar.begin(); it != sinPintar.end(); ++it) std::cout << *it << " ";
//    std::cout << "]" << std::endl;
//
//
//    int longSubproblema = longitud - desde;
////    // Poda
////    if (sinPintar.size() >= minSinPintar) {
////        calculados[longSubproblema][rojas.size()][azules.size()] = longitud;
////        return longitud;
////    }
//    if (longSubproblema == 0) {
//        imprimirSolucion(longitud, rojas, azules, sinPintar);
////        if (sinPintar.size() < minSinPintar) minSinPintar = sinPintar.size();
//        calculados[longSubproblema][rojas.size()][azules.size()] = (int) sinPintar.size();
//        return (int) sinPintar.size();
//    } else {
//        // Si lo calcule antes, lo devuelvo
//        if (calculados[longSubproblema][rojas.size()][azules.size()] != -1) return calculados[longSubproblema][rojas.size()][azules.size()];
//
//        int primerElemento = problema[desde];
//
//        // Opcion 1: pinto 'primerElemento' de rojo (si rojo sigue siendo decreciente)
//        int minRamaRojo = longitud;
//        if (rojas.empty() || rojas.back() < primerElemento) {
//            rojas.push_back(primerElemento);
//            minRamaRojo = pintarDinamico(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar, calculados);
//            rojas.pop_back();
//        }
//
//        // Opcion 2: pinto 'primerElemento' de azul (si azul sigue siendo decreciente)
//        int minRamaAzul = longitud;
//        if (azules.empty() || azules.back() > primerElemento) {
//            azules.push_back(primerElemento);
//            minRamaAzul = pintarDinamico(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar, calculados);
//            azules.pop_back();
//        }
//
//        // Opcion 3: dejo 'primerElemento' sin pintar
//        int minRamaSP = longitud;
//        sinPintar.push_back(primerElemento);
//        minRamaSP = pintarDinamico(problema, desde + 1, longitud, rojas, azules, sinPintar, minSinPintar, calculados);
//        sinPintar.pop_back();
//
//        // Guardo lo calculado
//        calculados[longSubproblema][rojas.size()][azules.size()] = min3(minRamaRojo, minRamaAzul, minRamaSP);
//        std::cout << "Guardando m[" << desde << "][" << rojas.size() << "][" << azules.size() << "]=" << min3(minRamaRojo, minRamaAzul, minRamaSP) << std::endl;
//        return min3(minRamaRojo, minRamaAzul, minRamaSP);
//    }
//}
