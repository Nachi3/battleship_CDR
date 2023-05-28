#ifndef DERRIBOS_H
#define DERRIBOS_H

#include <iostream>
#include <cstdlib>
#include <string>

const int SIZE_TABLE = 15;

class Derribos {

private:
    static const int PORTAAVIONES_SIZE = 5;
    static const int BUQUE_SIZE = 4;
    static const int SUBMARINO_SIZE = 3;
    static const int LANCHA_SIZE = 1;

    static const int SIZE_TABLE = 15;

    static const int PORTAAVIONES_NUM = 1*PORTAAVIONES_SIZE;
    static const int BUQUE_NUM = 2*BUQUE_SIZE;
    static const int SUBMARINO_NUM = 2*SUBMARINO_SIZE;
    static const int LANCHAS_NUM = 3*LANCHA_SIZE;

public:
    char derribo[SIZE_TABLE][SIZE_TABLE];
    int portaaviones_hundidos = 0;
    int buques_hundidos = 0;
    int submarinos_hundidos = 0;
    int lanchas_hundidos = 0;

    Derribos();

    char agregar(int position_x, int position_y, char ship);
    void imprimir();
    void imprimir_barcos_hundidos();
    int getPortaavionesNum();
    int getBuquesNum();
    int getSubmarinosNum();
    int getLanchasNum();
    int getPortaavionesSize();
    int getBuquesSize();
    int getSubmarinosSize();
    int getLanchasSize();
};

#endif
