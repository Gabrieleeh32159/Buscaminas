//
// Created by Usuario on 28/12/2021.
//

#ifndef BUSCAMINAS_GAME_H
#define BUSCAMINAS_GAME_H
#include <iostream>
#include <ctime>
#include <vector>
#define MINA -1
#define SIN_MOSTRAR -2
#define BORDE -3

using namespace std;

class game {
private:
    int alto;
    int ancho;
    int **tablero_lleno;
    int **tablero_a_mostrar;
    bool lose = false;
    bool win = false;
    int casillas_reveladas = 0;
    void establecer_dimensiones();
    void minar();
    void asignar_numeros();
    void revelar_posicion();
    void mostrar_posicion(int i, int j);
    void encontrar_mina();
public:
    game();
    void jugar();
    virtual ~game();
};

#endif //BUSCAMINAS_GAME_H
