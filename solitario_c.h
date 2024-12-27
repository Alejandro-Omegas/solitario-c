#ifndef SOLITARIO_C_H
#define SOLITARIO_C_H
#include "structs.h"
//funcion principal
void solitario_c();
//funciones secundarias
void chequar_victoria(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G, int* salida);
void nuke(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G); //para liberar la memoria de todas las cartas tras terminar el juego
void help();
void terminar_memoria_insuficiente();
#endif

