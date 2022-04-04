#include "game.h"

int main() {
    auto juego = new game();
    juego->jugar();
    delete juego;
    return 0;
}