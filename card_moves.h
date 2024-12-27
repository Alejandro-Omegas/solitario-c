#ifndef CARD_MOVES_H
#define CARD_MOVES_H
#include "structs.h"
void mover_cartas_entre_columnas(Mazo* mazoOrigen, Mazo* mazoDestino, int fila);
void mover_carta_pila_ordenada(Mazo* mazoOrigen, Mazo* mazoDestino, int fila); //si seingresa fila como -1, la funcion asume que se mueve desde el monticulo desordenado
void mover_carta_a_columnas(Mazo* mazoOrigen, Mazo* mazoDestino);
void mover_tope_carta(Mazo* origen, Mazo* destino);
void movimiento_rapido(Mazo* origen, Mazo* P, Mazo* R, Mazo* S, Mazo* T, int fila); //se envia -1 si el mazo origen no es una de las columnas
#endif
