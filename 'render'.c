#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "'render'.h"

void imprimir_tablero(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G)
{	
	int fila, x;
	Carta* pilas[7] = { A->base, B->base, C->base, D->base, E->base, F->base, G->base, }; //para imprimir las pilas de abajo para arriba
		                         
	printf("        M  \t\t  P     R     S     T\n");
	imprimir_carta(M->tope); printf(" ");
	imprimir_carta(M_->tope); printf("\t\t");
	imprimir_carta(P->tope); printf(" ");
	imprimir_carta(R->tope); printf(" ");
	imprimir_carta(S->tope); printf(" ");
	imprimir_carta(T->tope); printf("\n\n");
	
	printf("     A     B     C     D     E     F     G\n");
	for(fila = 1; fila <= 13; fila++)
	{
		printf("%2d ", fila);
		imprimir_carta(pilas[0]); printf(" ");
		imprimir_carta(pilas[1]); printf(" ");
		imprimir_carta(pilas[2]); printf(" ");
		imprimir_carta(pilas[3]); printf(" ");
		imprimir_carta(pilas[4]); printf(" ");
		imprimir_carta(pilas[5]); printf(" ");
		imprimir_carta(pilas[6]);
		printf(" %2d\n", fila);
		
		for(x = 0; x < 7; x++)
		{
			if(pilas[x] != NULL)
			{
				pilas[x] = pilas[x]->anterior;
			}
		}
	}
	printf("\n");
}

//imprime a color
void imprimir_tablero_(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G)
{	
	int fila, columna, x;
	Carta* pilas[7] = { A->base, B->base, C->base, D->base, E->base, F->base, G->base, }; //para imprimir las pilas de abajo para arriba
	Mazo* columnas[7] = { A, B, C, D, E, F, G }; //para dibujar la carta del tope completa
	//banderas utilizadas para determinar si se deben dibujar o no las partes media y baja de las cartas tope de las columnas
	Carta* band_[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL }; 
	Carta* band__[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL }; 
	                  
	printf("        M  \t\t  P     R     S     T\n");
	imprimir_carta(M->tope); printf("\033[42m "); //\033[42m pinta el fondo de verde
	imprimir_carta(M_->tope); printf("\033[42m\t\t");
	imprimir_carta(P->tope); printf("\033[42m ");
	imprimir_carta(R->tope); printf("\033[42m ");
	imprimir_carta(S->tope); printf("\033[42m ");
	imprimir_carta(T->tope); printf("\n");
	imprimir_carta_(M->tope); printf("\033[42m ");
	imprimir_carta_(M_->tope); printf("\033[42m\t\t");
	imprimir_carta_(P->tope); printf("\033[42m ");
	imprimir_carta_(R->tope); printf("\033[42m ");
	imprimir_carta_(S->tope); printf("\033[42m ");
	imprimir_carta_(T->tope); printf("\n");
	imprimir_carta__(M->tope); printf("\033[42m ");
	imprimir_carta__(M_->tope); printf("\033[42m\t\t");
	imprimir_carta__(P->tope); printf("\033[42m ");
	imprimir_carta__(R->tope); printf("\033[42m ");
	imprimir_carta__(S->tope); printf("\033[42m ");
	imprimir_carta__(T->tope); printf("\n\n");
	
	printf("\033[42m     A     B     C     D     E     F     G\n");
	
	for(fila = 1; fila <= 19; fila++)
	{
		printf("%2d ", fila);
		
		for(columna = 0; columna < 7; columna++)
		{
			if(band_[columna] != NULL)
			{
				imprimir_carta_(band_[columna]);
				band__[columna] = band_[columna]; //levanamos la bandera para dibujar la parte inferior del tope
				band_[columna] = NULL;
			}
			else if(band__[columna] != NULL)
			{
				imprimir_carta__(band__[columna]);
				band__[columna] = NULL;
			}
			else
			{
				imprimir_carta(pilas[columna]);
			}
			
			printf("\033[42m ");	
		}

		printf("\033[42m%2d\n", fila);
		
		for(x = 0; x < 7; x++)
		{
			if(pilas[x] != NULL)
			{
				if(pilas[x]->anterior == NULL) band_[x] = pilas[x]; //al llegar a nulo despues del cambio, se asume que estamos al tope, por lo que se levanta la bandera de esa columna para dibujar la parte media y se guarda una copia de la carta tope, porque necesitamos datos de ella para dibujar
				pilas[x] = pilas[x]->anterior;
			}
		}
	}
	printf("\n");
}

void imprimir_mazo(Mazo* mazo) //usado para DEBUG
{
	Carta* scout = mazo->tope;
	char palo;
	char numero;   
	                          //Rojo       Negro        Reset
	char* coloresTexto[] = { "\033[31m", "\033[30m", "\033[39m"  };
	                             //Blanco      Amarillo     Reset
	char* coloresFondoTexto[] = { "\033[47m", "\033[43m",  "\033[49m" };
	char* textoDefecto = "\033[0m"; //para que el estilo, color de fondo de texto y color texto vuelvan a sus valores default
	int n = 1; //DEBUG
	//ASCII: A = 65, J = 74, Q = 81, K = 75, 0 al 9 = 48 al 57
	while(scout != NULL)
	{
		switch(scout->numero)
		{
			case 1: numero = 65; break; //A
			case 11: numero = 74; break; //J
			case 12: numero = 81; break; //Q
			case 13: numero = 75; break; //K
			default: numero = scout->numero + 48; //2-10 en ASCII
		}
		
		if(scout->oculto == 0) //carta revelada
		{
			if(numero == 58) printf("%2d %s%s|%c10|%s\n", n, coloresTexto[scout->color], coloresFondoTexto[scout->oculto], scout->palo, textoDefecto); //para el caso que sea 10
			else printf("%2d %s%s|%c%2c|%s\n", n, coloresTexto[scout->color], coloresFondoTexto[scout->oculto], scout->palo, numero, textoDefecto);
		}
		else //carta oculta
		{
			printf("%2d %s%s|   |%s\n", n, coloresTexto[1], coloresFondoTexto[scout->oculto], textoDefecto);
		}

		scout = scout->siguiente;
		n++;
	}
	
	printf("\n");
}

void imprimir_carta(Carta* carta)
{	                          //Rojo       Negro        Reset
	char* coloresTexto[] = { "\033[31m", "\033[30m", "\033[39m"  };
	                             //Blanco      Amarillo     Reset
	char* coloresFondoTexto[] = { "\033[47m", "\033[43m",  "\033[49m" };
	char* textoDefecto = "\033[0m"; //para que el estilo, color de fondo de texto y color texto vuelvan a sus valores default
	
	int numero;
	
	if(carta == NULL) //en caso de carta nula, solo imprimimos espacios representando casilla vacia
	{
		printf("     ");
		return; 
	}
	
	switch(carta->numero)
	{
		case 1: numero = 65; break; //A
		case 11: numero = 74; break; //J
		case 12: numero = 81; break; //Q
		case 13: numero = 75; break; //K
		default: numero = carta->numero + 48; //2-10 en ASCII
	}
	
	if(carta->oculto == 0) //carta revelada
	{
		if(numero == 58) printf("%s%s|%c10|%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], carta->palo, textoDefecto); //para el caso que sea 10
		else printf("%s%s|%c%2c|%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], carta->palo, numero, textoDefecto);
	}
	else //carta oculta
	{
		printf("%s%s|%c%c%c|%s", coloresTexto[1], coloresFondoTexto[carta->oculto], 176, 176, 176, textoDefecto);
	}
}

void imprimir_carta_(Carta* carta)
{	                          //Rojo       Negro        Reset
	char* coloresTexto[] = { "\033[31m", "\033[30m", "\033[39m"  };
	                             //Blanco      Amarillo     Reset
	char* coloresFondoTexto[] = { "\033[47m", "\033[43m",  "\033[49m" };
	char* textoDefecto = "\033[0m"; //para que el estilo, color de fondo de texto y color texto vuelvan a sus valores default
	
	int numero;
	
	if(carta == NULL) //en caso de carta nula, solo imprimimos espacios representando casilla vacia
	{
		printf("\033[42m     ");
		return; 
	}
	
	if(carta->oculto == 0) //carta revelada
	{
		printf("%s%s|   |%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], textoDefecto);
	}
	else //carta oculta
	{
		printf("%s%s|%c%c%c|%s", coloresTexto[1], coloresFondoTexto[carta->oculto], 176, 176, 176, textoDefecto);
	}
}

void imprimir_carta__(Carta* carta)
{	                          //Rojo       Negro        Reset
	char* coloresTexto[] = { "\033[31m", "\033[30m", "\033[39m"  };
	                             //Blanco      Amarillo     Reset
	char* coloresFondoTexto[] = { "\033[47m", "\033[43m",  "\033[49m" };
	char* textoDefecto = "\033[0m"; //para que el estilo, color de fondo de texto y color texto vuelvan a sus valores default
	
	int numero;
	
	if(carta == NULL) //en caso de carta nula, solo imprimimos espacios representando casilla vacia
	{
		printf("\033[42m     ");
		return; 
	}
	
	switch(carta->numero)
	{
		case 1: numero = 65; break; //A
		case 11: numero = 74; break; //J
		case 12: numero = 81; break; //Q
		case 13: numero = 75; break; //K
		default: numero = carta->numero + 48; //2-10 en ASCII
	}
	
	if(carta->oculto == 0) //carta revelada
	{
		if(numero == 58) printf("%s%s|10%c|%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], carta->palo, textoDefecto); //para el caso que sea 10
		else printf("%s%s|%-2c%c|%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], numero, carta->palo, textoDefecto);
	}
	else //carta oculta
	{
		printf("%s%s|%c%c%c|%s", coloresTexto[1], coloresFondoTexto[carta->oculto], 176, 176, 176, textoDefecto);
	}
}

