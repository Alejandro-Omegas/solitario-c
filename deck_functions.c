#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "deck_functions.h"

void distribuir_cartas(Mazo* M, Mazo* M_, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G)
{
	Mazo* columnas[7] = { A, B, C, D, E, F, G };
	int x, y;
	
	for(x = 1; x <= 7; x++)
	{
		for(y = 1; y <= x; y++)
		{
			mover_tope_carta(M, columnas[x-1]);
		}
	}

	mover_tope_carta(M, M_); //M_ sera el que muestra graficamente la carta revelada para el monticulo desordenado
	M_->tope->oculto = 0; //revelar carta del monticulo desordenado
	
	Carta* nroColumnas[7] = { A->base, B->base, C->base, D->base, E->base, F->base, G->base };
	
	//numerando las cartas de las columnas para facilitar funciones ingresadas por el usuario
	for(x = 1; x <= 7; x++) //1 al 7 porque la columna mas larga inicial solo llega a siete cartas
	{
		for(y = x - 1; y < 7; y++)
		{
			if(nroColumnas[y] != NULL)
			{
				nroColumnas[y]->fila = x;
				if(nroColumnas[y]->anterior == NULL) nroColumnas[y]->oculto = 0; //revelamos el tope de la carta
				nroColumnas[y] = nroColumnas[y]->anterior;
			}
		}
	}
}

void generar_mazo(Mazo* mazo)
{
	int color, palo, numero;
	Carta* nuevaCarta; 
			
	for(palo = 3; palo <= 6; palo++) //en ASCII Corazon = 3, Diamante = 4, Trébol = 5, Pica = 6
	{
		for(numero = 1; numero <= 13; numero++) //1-13 con 1 = As, 11 = Jack, 12 = Queen, 13 = King. En  ASCII: A = 65, J = 74, Q = 81, K = 75, 0 al 9 = 48 al 57
		{
			nuevaCarta = malloc(sizeof(Carta));
			
			if(nuevaCarta == NULL) terminar_memoria_insuficiente();
			
			nuevaCarta->color = palo <= 4 ? 0 : 1;
			nuevaCarta->palo = palo;
			nuevaCarta->numero = numero;
			nuevaCarta->oculto = 1; //oculto
			nuevaCarta->siguiente = NULL;
								
			if(mazo->tope == NULL) //si mazo esta vacio
			{
				nuevaCarta->anterior = NULL;
				mazo->tope = nuevaCarta;
				mazo->base = nuevaCarta;
			}
			else
			{
				mazo->base->siguiente = nuevaCarta;
				nuevaCarta->anterior = mazo->base;
				mazo->base = nuevaCarta;
			}
		}		
	}	
}

void mezclar_mazo(Mazo* mazo)
{
	Carta* auxMazo[52];
	Carta* auxCarta;
	int x = 0, rng;
	
	//el algoritmo llena un vector con todos los punteros del mazo y despues ordena los punteros y finalmente reconstruye la conexion de los nodos usando el arreglo
	while((mazo->tope != NULL) && (x < 52))
	{
		auxMazo[x] = mazo->tope;
		mazo->tope = mazo->tope->siguiente;
		
		x++;
	}
	
	//intercambia cartas x veces
	for(x = 0; x < 52; x++)
	{
		rng = rand() % 52;
		
		auxCarta = auxMazo[x];
		auxMazo[x] = auxMazo[rng];
		auxMazo[rng] = auxCarta;
	}
	
	//reconstruyendo nodos
	auxMazo[0]->anterior = NULL;
	auxMazo[0]->siguiente = auxMazo[1];
	
	for(x = 1; x < 51; x++)
	{
		auxMazo[x]->anterior = auxMazo[x-1];
		auxMazo[x]->siguiente = auxMazo[x+1];
	}
	
	auxMazo[51]->anterior = auxMazo[50];
	auxMazo[51]->siguiente = NULL;
	
	mazo->tope = auxMazo[0];
	mazo->base = auxMazo[51];
}

