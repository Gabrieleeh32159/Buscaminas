//
// Created by Usuario on 28/12/2021.
//

#include "game.h"

void mostrar_tablero(int** tablero, int ancho, int alto) {
    system("cls");
    cout << " " << "\t";
    for (int i = 0 ; i < ancho ; i++){
        cout << i+1 << "\t";
    }
    cout << "\n";
    cout << "\n";
    for (int i=1; i < alto+1; i++){
        cout << i << "\t";
        for(int j=1 ; j < ancho+1; j++){
            int valor = tablero[i][j];
            string muestra;
            switch(valor){
                case SIN_MOSTRAR: muestra = '-';
                    break;
                case MINA: muestra = 'M';
                    break;
                default: muestra = to_string(valor);
            }
            cout << muestra + "\t";
        }
        cout << "\n";
        cout << "\n";
    }
}


game::game(){
    //Dimensiones
    this->establecer_dimensiones();

    //Crear tablero_lleno vacío
    tablero_lleno = new int*[alto + 2];
    for (int i  = 0; i < alto+2; i++){
        tablero_lleno[i] = new int[ancho + 2];
    }

    for(int i = 0; i < alto+2 ; i++){
        for (int j = 0 ; j < ancho+2; j++){
            tablero_lleno[i][j] = BORDE;
        }
    }
    //Establecer las ubicaciones de las minas
    this->minar();
    //rellenar numeros
    this->asignar_numeros();

    //Crear el tablero a mostrar vacío
    tablero_a_mostrar = new int*[alto + 2];
    for (int i  = 0; i < alto+2; i++){
        tablero_a_mostrar[i] = new int[ancho + 2];
    }

    for(int i = 0; i < alto+2 ; i++){
        for (int j = 0 ; j < ancho+2; j++){
            tablero_a_mostrar[i][j] = SIN_MOSTRAR;
        }
    }
}

void game::establecer_dimensiones() {
    //limpiar consola
    system("cls");
    //Pedir dimensiones del tablero_lleno
    bool correcto = true;
    do{
        cout << "Ingrese el alto del tablero: "; cin >> alto;
        cout << "Ingrese el ancho del tablero: "; cin >> ancho;
        if (!(alto >= 8 && alto <= 30 && ancho >= 8 && ancho <= 30)){
            correcto = false;
            cout << "Dimensiones ingresadas incorrectas!" << endl;
            cout << "Recordar que el ancho y alto deben estar entre 8 y 30." << endl;
        } else {
            correcto = true;
        }
    }while(!correcto);
}

void game::minar() {
    //semilla generadora de numero aleatorio
    srand(time (NULL));

    //cantidad de minas
    int numero_minas = (alto * ancho) / 5;

    //minar
    int minas_colocadas = 0;
    while(minas_colocadas < numero_minas){
        int x = rand()%alto + 1;
        int y = rand()%ancho + 1;
        int valor = tablero_lleno[x][y];
        if (valor == BORDE){
            tablero_lleno[x][y] = MINA;
            minas_colocadas++;
        }
    }
}

void game::asignar_numeros() {
    for(int i=1; i < alto+1; i++){
        for(int j=1; j < ancho+1; j++){
            if (tablero_lleno[i][j] != MINA){
                int suma = 0;
                for(int m=0; m<3; m++){
                    for(int n=0 ; n < 3; n++){
                        if (tablero_lleno[i + n - 1][j + m - 1] == MINA){
                            suma++;
                        }
                    }
                }
                tablero_lleno[i][j] = suma;
            }
        }
    }
}

game::~game() {
    for (int i  = 0; i < alto+2; i++){
        delete tablero_lleno[i];
    }
    delete tablero_lleno;
    alto = 0;
    ancho = 0;
    cout << "Juego terminado" << endl;
}

void game::jugar() {
    while(!win && !lose){
        system("cls");
        mostrar_tablero(tablero_a_mostrar, ancho, alto);
        cout << "[1] Revelar posicion" << endl;
        cout << "[2] Marcar como mina encontrada" << endl;
        int opcion;
        do{
            cout << "Opcion: "; cin >> opcion;
        }while(opcion != 1 && opcion != 2);
        switch(opcion){
            case 1:
                this->revelar_posicion();
                break;
            case 2:
                this->encontrar_mina();
                break;
        }
    }
}

void game::revelar_posicion() {
    int x, y;
    cout << "Ingrese la posicion en X a revelar: "; cin >> x;
    cout << "Ingrese la posicion en Y a revelar: "; cin >> y;
    if (tablero_lleno[y][x] == MINA){
        system("cls");
        mostrar_tablero(tablero_lleno, ancho, alto);
        cout << "Ingrese la posicion en X a revelar: " << x << endl;
        cout << "Ingrese la posicion en Y a revelar: " << y << endl;
        cout << "¡MINA PISADA, PERDISTE!" << endl;
        lose = true;
    } else {
        mostrar_posicion(y, x);
    }
    if (casillas_reveladas == (alto*ancho)*4/5){
        cout << "¡FELICIDADES, SOBREVIVISTE AL TEEMO ASQUEROSO!" << endl;
        win = true;
    }
}

void game::encontrar_mina() {
    int x, y;
    cout << "Ingrese la posicion en X de la mina: "; cin >> x;
    cout << "Ingrese la posicion en Y de la mina: "; cin >> y;
    if (tablero_lleno[y][x] == MINA){
        cout << "Encontraste una mina!" << endl;
        tablero_a_mostrar[y][x] = MINA;
    } else {
        system("cls");
        mostrar_tablero(tablero_lleno, ancho, alto);
        cout << "Ingrese la posicion en X a revelar: " << x << endl;
        cout << "Ingrese la posicion en Y a revelar: " << y << endl;
        cout << "UY! NO LO ERA!" << endl;
        lose = true;
    }
}

void game::mostrar_posicion(int i, int j) {
    if (tablero_a_mostrar[i][j] == SIN_MOSTRAR){
        tablero_a_mostrar[i][j] = tablero_lleno[i][j];
        if (tablero_lleno[i][j] != BORDE ){
            casillas_reveladas++;
        }

        if (tablero_lleno[i][j] == 0){
            for(int m=-1; m < 2; m++){
                for(int n=-1 ; n < 2; n++){
                    if (m != 0 || n != 0){
                        this->mostrar_posicion(i+m, j+n);
                    }
                }
            }
        }
    }
}
