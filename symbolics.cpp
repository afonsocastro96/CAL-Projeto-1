//
// Created by João Silva on 25/04/2015.
//

#include <string>
#include <math.h>

using namespace std;

long double stringToDouble(string d) {
    long double parteDecimal = 0;
    int parteInteira = 0;
    int contador = 0;
    int digit = 0;
    double ret;
    bool negativo = false;

    if (d[0] == '-') {
        negativo = true;
        digit++;
    }

    while (d[digit] != '.') {
        parteInteira *= 10;
        parteInteira += d[digit] - 48; //Conversoes ASCII -> decimal
        digit++;
    }

    digit++;

    while (digit < d.size()) {
        parteDecimal *= 10;
        parteDecimal += d[digit] - 48; //Conversoes ASCII -> decimal
        contador++;
        digit++;
    }

    parteDecimal /= pow(10, contador);

    ret = parteInteira + parteDecimal;
    if (negativo) {
        ret = -ret;
    }

    return ret;
}

