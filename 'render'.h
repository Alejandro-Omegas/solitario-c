#ifndef RENDER_H
#define RENDER_H
#include "structs.h"
void imprimir_tablero(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G);
void imprimir_tablero_(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G); //imprime a color. creado una segunda version para DEBUGGING
void imprimir_carta(Carta* carta); //las cartas se dividen graficamente en tres partes: arriba, medio y abajo. Esta funcion imprime la parte de arriba
void imprimir_carta_(Carta* carta); //Esat funcion imprime la parte media
void imprimir_carta__(Carta* carta); //Esat funcion imprime la parte baja
void imprimir_mazo(Mazo* mazo); //usado para DEBUG
#endif
