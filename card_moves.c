#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "card_moves.h"

void mover_tope_carta(Mazo* origen, Mazo* destino)
{
	Carta* cartaAMover = origen->tope;

	//si origen esta vacio
	if(origen->tope == NULL) return;
	
	//si destino esta vacio
	if(destino->tope == NULL || destino->base == NULL)
	{
		origen->tope = origen->tope->siguiente;
		destino->tope = cartaAMover;
		destino->base = cartaAMover;
		cartaAMover->siguiente = NULL;
	}
	else //si destino tiene alguna carta
	{
		origen->tope = origen->tope->siguiente;
		cartaAMover->siguiente = destino->tope; 
		destino->tope->anterior = cartaAMover;
		cartaAMover->anterior = NULL;
		destino->tope = cartaAMover;
	}
	
	//revisar si origen quedo vacio, de lo contrario el nuevo tope debe tener que actualizar "anterior" como NULL
	if(origen->tope == NULL) origen->base = NULL;
	else origen->tope->anterior = NULL;
}


void mover_cartas_entre_columnas(Mazo* mazoOrigen, Mazo* mazoDestino, int fila)
{
	if(fila < 1 || fila > 19) return; //fila invalida
	
	if(mazoOrigen->tope == NULL) return; //mazo origen vacio

	//si la fila ingresada por el usuario coincide con la fila de la carta al tope de esa columna, entonces se mueve solo el tope
	if(mazoOrigen->tope->fila == fila)
	{
		mover_carta_a_columnas(mazoOrigen, mazoDestino);
		return;
	}

	//si la fila ingresada es menor, entonces el usuario busca mover un conjunto de cartas
	if(mazoOrigen->tope->fila > fila)
	{
		Carta* scout = mazoOrigen->tope;
		
		while(scout->fila > fila)
		{
			//verifica que las cartas del conjunto seleccionado sigan el orden correcto en numero y colores alternantes
			if(scout->numero == scout->siguiente->numero - 1 &&
			   scout->color != scout->siguiente->color)
			{
				scout = scout->siguiente;
			}
			else //si falla, no hay moviento que hacer
			{
				return;
			}
		}

		//realizando el cambio 
		//si el destino tiene alguna carta
		if(mazoDestino->tope == NULL || //caso que el destino este vacio o..
		   (scout->numero == mazoDestino->tope->numero - 1 && //..tiene carta y cumple las condiciones
		   scout->color != mazoDestino->tope->color))
		{ 
			Carta* auxTopeOrigen = mazoOrigen->tope, * auxTopeDestino = mazoDestino->tope;
		
			if(scout->siguiente != NULL) //seteando nuevo tope del origen (y base si el nuevo tope en NULL)
			{
				mazoOrigen->tope = scout->siguiente;
				mazoOrigen->tope->anterior = NULL;
			}
			else
			{
				mazoOrigen->tope = NULL; mazoOrigen->base = NULL;
			}

			//seteando nuevo tope de destino 
			mazoDestino->tope = auxTopeOrigen;
			scout->siguiente = auxTopeDestino;
			
			if(auxTopeDestino != NULL) 
			{
				auxTopeDestino->anterior = scout;
				
				//actualizamos los valores de fila de las cartas movidas
				auxTopeDestino = auxTopeDestino->anterior;	
				
				while(auxTopeDestino != NULL)
				{	
					auxTopeDestino->fila = auxTopeDestino->siguiente->fila + 1;
					auxTopeDestino = auxTopeDestino->anterior;
				}
			}
			else
			{
				mazoDestino->base = scout;
				
				//numeramos, como destino estaba vacio, empieza desde 1
				scout->fila = 1;
				scout= scout->anterior;
				
				while(scout != NULL)
				{
					scout->fila = scout->fila + 1;
					scout = scout->anterior;
				}
			}
		}

		return;
	}
}

void mover_carta_pila_ordenada(Mazo* mazoOrigen, Mazo* mazoDestino, int fila)
{
	if(mazoOrigen->tope == NULL) return; //si origen esta vacio
	
	//si se recibe fila como -1 entonces es para mover desde el monticulo desordenado
	if(fila == -1)
	{//El M que muestra el juego es en realidad M_, por lo que si la carta que movimos es la unica que M_ posee, este despues se mostrara como vacia, pero eso no significa que M este vacio
		if(mazoDestino->tope == NULL) //caso el mazo ordenado este vacio
		{
			if(mazoOrigen->tope->numero == 1)
			{
				mover_tope_carta(mazoOrigen, mazoDestino);
			}
		}
		else //caso el mazo ordenado ya tenga una carta
		{	
			if(mazoOrigen->tope->numero == mazoDestino->tope->numero + 1 &&
			   mazoOrigen->tope->palo == mazoDestino->tope->palo)
			{
				mover_tope_carta(mazoOrigen, mazoDestino);	
			}
		}
		
		return;
	}

	//si fila no es -1, se asume que el mazo origen es una de las columnas
	if(mazoOrigen->tope->fila == fila) 
	{
		if(mazoDestino->tope == NULL) //caso el mazo ordenado este vacio
		{
			if(mazoOrigen->tope->numero == 1)
			{ 
				mover_tope_carta(mazoOrigen, mazoDestino);
			}
		}
		else //caso el mazo ordenado ya tenga una carta
		{	
			if(mazoOrigen->tope->numero == mazoDestino->tope->numero + 1 &&
			   mazoOrigen->tope->palo == mazoDestino->tope->palo)
			{
				mover_tope_carta(mazoOrigen, mazoDestino);
			}
		}
	}
}

void mover_carta_a_columnas(Mazo* mazoOrigen, Mazo* mazoDestino)
{
	//si origen esta vacio
	if(mazoOrigen->tope == NULL) return;
	
	//si destino esta vacio
	if(mazoDestino->tope == NULL || mazoDestino->base == NULL)
	{
		if(mazoOrigen->tope->numero == 13)
		{
			mover_tope_carta(mazoOrigen, mazoDestino);
			mazoDestino->tope->fila = 1;
		}
		
		return;
	}
	
	//si destino no esta vacio
	if(mazoDestino->tope->numero == mazoOrigen->tope->numero + 1 &&
	   mazoDestino->tope->color != mazoOrigen->tope->color)
	{
		mover_tope_carta(mazoOrigen, mazoDestino);
		mazoDestino->tope->fila = mazoDestino->tope->siguiente->fila + 1;
		return;
	}
}


void movimiento_rapido(Mazo* origen, Mazo* P, Mazo* R, Mazo* S, Mazo* T, int fila)
{
	int x;
	Mazo* ordenadas_[4] = { P, R, S, T };
	
	//si origen esta vacio
	if(origen->tope == NULL) return;
	
	//revisa los topes de los monticulos ordenados, si encuentra uno valido donde colocar la carta del monticulo desordenado, la coloca, y no encuentra un monticulo con un palo, la bandera se mantiene igual, la cual es usada en el siguiente if
	for(x = 0; x < 4; x++)
	{
		if(ordenadas_[x]->tope != NULL)
		{
			if(ordenadas_[x]->tope->palo == origen->tope->palo)
			{
				mover_carta_pila_ordenada(origen, ordenadas_[x], fila);
				return;
			}
		}
	}
	
	//si el palo no existe entre los monticulos ordenados, se coloca la carta en el primer monticulo vacio, siempre que sea una carta valida (As)
	for(x = 0; x < 4; x++)
	{
		if(ordenadas_[x]->tope == NULL)
		{
			mover_carta_pila_ordenada(origen, ordenadas_[x], fila);
		}
	}
}


