#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <windows.h>

typedef struct carta
{
	struct carta* anterior;
	
	unsigned int color:1;
	unsigned int palo:3; //en ASCII Corazon = 3, Diamante = 4, Trébol = 5, Pica = 6
	unsigned int numero:4; //1-13 con 1 = As, 11 = Jack, 12 = Queen, 13 = King. En  ASCII: A = 65, J = 74, Q = 81, K = 75, 0 al 9 = 48 al 57
	unsigned int oculto:1; //1 carta oculta, 0 carta revelada
	unsigned int fila:5; //se usa solo para mazos que esten en las columnas (1-19)
	
	struct carta* siguiente;
} Carta;

typedef struct
{
	Carta* tope;
	Carta* base;
} Mazo;

//funcion principal
void tp_final();
//funciones secundarias
void generar_mazo(Mazo* mazo);
void mezclar_mazo(Mazo* mazo);
void imprimir_mazo(Mazo* mazo); //usado para DEBUG
void distribuir_cartas(Mazo* M, Mazo* M_, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G);
void imprimir_tablero(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G);
void imprimir_tablero_(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G); //imprime a color. creado una segunda version para DEBUGGING
void imprimir_carta(Carta* carta); //las cartas se dividen graficamente en tres partes: arriba, medio y abajo. Esta funcion imprime la parte de arriba
void imprimir_carta_(Carta* carta); //Esat funcion imprime la parte media
void imprimir_carta__(Carta* carta); //Esat funcion imprime la parte baja
void mover_cartas_entre_columnas(Mazo* mazoOrigen, Mazo* mazoDestino, int fila);
void mover_carta_pila_ordenada(Mazo* mazoOrigen, Mazo* mazoDestino, int fila); //si seingresa fila como -1, la funcion asume que se mueve desde el monticulo desordenado
void mover_carta_a_columnas(Mazo* mazoOrigen, Mazo* mazoDestino);
void mover_tope_carta(Mazo* origen, Mazo* destino);
void movimiento_rapido(Mazo* origen, Mazo* P, Mazo* R, Mazo* S, Mazo* T, int fila); //se envia -1 si el mazo origen no es una de las columnas
void prompt(Mazo* M, Mazo* M_,Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G, int* salida);
void chequar_victoria(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G, int* salida);
int detectar_indice_mazo(char caracter);
void terminar_memoria_insuficiente();

int main()
{
	tp_final();

	return 0;
}

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
	
	printf("     A     B     C     D     E     F     G\n");
	for(fila = 1; fila <= 15; fila++)
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
	
	Carta* nroColumnas[7] = { A->base, B->base, C->base, D->base, E->base, F->base, G->base };
	
	//numerando las cartas de las columnas para facilitar funciones ingresadas por el usuario
	for(x = 1; x <= 7; x++) //1 al 7 porque la columna mas larga inicial solo llega a siete cartas
	{
		for(y = x - 1; y < 7; y++)
		{
			if(nroColumnas[y] != NULL)
			{
				nroColumnas[y]->fila = x;
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
			nuevaCarta->oculto = 0; //revelado
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
			if(numero == 58) printf("%2d %s%s[%c10]%s\n", n, coloresTexto[scout->color], coloresFondoTexto[scout->oculto], scout->palo, textoDefecto); //para el caso que sea 10
			else printf("%2d %s%s[%c%2c]%s\n", n, coloresTexto[scout->color], coloresFondoTexto[scout->oculto], scout->palo, numero, textoDefecto);
		}
		else //carta oculta
		{
			printf("%2d %s%s[   ]%s\n", n, coloresTexto[1], coloresFondoTexto[scout->oculto], textoDefecto);
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
		if(numero == 58) printf("%s%s[%c10]%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], carta->palo, textoDefecto); //para el caso que sea 10
		else printf("%s%s[%c%2c]%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], carta->palo, numero, textoDefecto);
	}
	else //carta oculta
	{
		printf("%s%s[   ]%s", coloresTexto[1], coloresFondoTexto[carta->oculto], textoDefecto);
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
		printf("     ");
		return; 
	}
	
	if(carta->oculto == 0) //carta revelada
	{
		printf("%s%s[   ]%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], textoDefecto);
	}
	else //carta oculta
	{
		printf("%s%s[   ]%s", coloresTexto[1], coloresFondoTexto[carta->oculto], textoDefecto);
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
		if(numero == 58) printf("%s%s[10%c]%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], carta->palo, textoDefecto); //para el caso que sea 10
		else printf("%s%s[%-2c%c]%s", coloresTexto[carta->color], coloresFondoTexto[carta->oculto], numero, carta->palo, textoDefecto);
	}
	else //carta oculta
	{
		printf("%s%s[   ]%s", coloresTexto[1], coloresFondoTexto[carta->oculto], textoDefecto);
	}
}

void terminar_memoria_insuficiente()
{
	printf("Memoria insuficiente..."); getchar();
	exit(1);
}

void tp_final()
{
	//SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN );
	system("COLOR 2F"); //para color de fondo verde (2) con color de letras blanco brillante (F)
	srand(time(NULL));

	Mazo M, M_; //monticulo desordenado. El M_ sera donde se coloquen las cartas de M conforme se revelen
	Mazo P, R, S, T; //monticulos ordenados
	Mazo A, B, C, D, E, F, G; //las columnas
	
	//Inicializar mazos
	M.tope = NULL; M.base = NULL;
	M_.tope = NULL; M_.base = NULL;
	P.tope = NULL; P.base = NULL;
	R.tope = NULL; R.base = NULL;
	S.tope = NULL; S.base = NULL;
	T.tope = NULL; T.base = NULL;
	A.tope = NULL; A.base = NULL;
	B.tope = NULL; B.base = NULL;
	C.tope = NULL; C.base = NULL;
	D.tope = NULL; D.base = NULL;
	E.tope = NULL; E.base = NULL;
	F.tope = NULL; F.base = NULL;
	G.tope = NULL; G.base = NULL;
	
	int salida = 0; //bandera de salida
	
	generar_mazo(&M);
	mezclar_mazo(&M);
	distribuir_cartas(&M, &M_, &A, &B, &C, &D, &E, &F, &G);
	
	while(salida  == 0)
	{
		system("CLS");
		imprimir_tablero_(&M, &M_, &P, &R, &S, &T, &A, &B, &C, &D, &E, &F, &G);
		prompt(&M, &M_, &P, &R, &S, &T, &A, &B, &C, &D, &E, &F, &G, &salida);
		chequar_victoria(&M, &M_, &P, &R, &S, &T, &A, &B, &C, &D, &E, &F, &G, &salida);
	}
	
	//nuke();
	system("PAUSE");
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
		//	printf("Base: %p [%c%2d]", mazoOrigen->base, mazoOrigen->base->palo, mazoOrigen->base->numero); getchar(); //DEBUG	
		}

		return;
	}
}

void mover_carta_pila_ordenada(Mazo* mazoOrigen, Mazo* mazoDestino, int fila)
{
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

void prompt(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G, int* salida)
{
	char prompt[8];
	int columna = -1, fila = -1;
	Mazo* columnas[7] = { A, B, C, D, E, F, G };
	Mazo* ordenados[4] = { P, R, S, T };

	printf(">> ");
	
	if(fgets(prompt, sizeof(prompt), stdin)) //ingresa comando y limpia el buffer de fgets en caso que haya quedado datos de entrada a leer
	{
        char *p;
        
		if(p = strchr(prompt, '\n')) 
		{//check exist newline
            *p = 0;
        } 
		else 
		{
            scanf("%*[^\n]");scanf("%*c");//clear upto newline
        }
    }
	
	if(strcmp(prompt, "exit") == 0) //se puede salir del juego ingresando "exit" todo en minuscula
	{
		*salida = 1;
		return;
	}
	
	switch(prompt[0])
	{
		//del monticulo desordenado a los monticulos ordenados o a las pilas
		case 'M': case 'm':
			if(prompt[1] == '-')
			{
				switch(prompt[2])
				{
					case 'P': case 'p':
						mover_carta_pila_ordenada(M_, P, -1);
						break;
					case 'T': case 't':
						mover_carta_pila_ordenada(M_, T, -1);
						break;
					case 'R': case 'r':
						mover_carta_pila_ordenada(M_, R, -1);
						break;
					case 'S': case 's':
						mover_carta_pila_ordenada(M_, S, -1);
						break;				
				}

				if((prompt[2] >= 'A' && prompt[2] <= 'G') || (prompt[2] >= 'a' && prompt[2] <= 'g') )  
				{//aqui ya no se chequea el numero porque no es necesario. Ex. si quiero mover de M a G8, no es necesario ingresar "M-G8", con ingresar "M-G" es suficiente, porque de cualquier manera solo puede mover la carta al tope de G	
					columna = detectar_indice_mazo(prompt[2]);
					mover_carta_a_columnas(M_, columnas[columna]);
				}
			}
			else if(prompt[1] == 'M' || prompt[1] == 'm')
			{
				movimiento_rapido(M_, P, R, S, T, -1);
			}
			else
			{				
				//despliega siguiente carta del monticulo desordenado
				if(M->tope != NULL) //el monticulo desordenado tiene aun cartas
				{
					mover_tope_carta(M, M_);	
				}
				else //el monticulo desordenado no tiene cartas que sacar
				{
					while(M_->tope != NULL) //el sub-monticulo desordenado tiene aun cartas, entonces los regresa al M
					{
						mover_tope_carta(M_, M);
					}
					
					if(M->tope != NULL) //significa que se movio cartas de M_, i.e., hay aun cartas
					{
						mover_tope_carta(M, M_);
					}	
				}
			}
			break;
		//de los monticulos ordenados a las pilas
		case 'P': case 'p':
		case 'T': case 't':
		case 'R': case 'r':
		case 'S': case 's':
			if(prompt[1] == '-')
			{
				if((prompt[2] >= 'A' && prompt[2] <= 'G') || (prompt[2] >= 'a' && prompt[2] <= 'g') )  
				{//aqui ya no se chequea el numero porque no es necesario. Ex. si quiero mover de P a G8, no es necesario ingresar "P-G8", con ingresar "P-G" es suficiente, porque de cualquier manera solo puede mover la carta al tope de G			
					columna = detectar_indice_mazo(prompt[2]);
					mover_carta_a_columnas(ordenados[detectar_indice_mazo(prompt[0])], columnas[columna]);
				}
			}
			break;
		//de las pilas a los monticulos ordenados y a otras pilas
		default: 
			if((prompt[0] >= 'A' && prompt[0] <= 'G') || (prompt[0] >= 'a' && prompt[0] <= 'g') )  
			{
				columna = detectar_indice_mazo(prompt[0]);
				
				if(prompt[1] == '1')
				{
					if(prompt[2] >= '0' && prompt[2] <= '9') //si ingreso A10 al A19 por ejemplo
					{
						fila = 10 + (int)prompt[2] - 48; //0 al 9 = 48 al 57 en ASCII
						
						if(prompt[3] == '-')
						{
							switch(prompt[4])
							{
								case 'P': case 'p':
									mover_carta_pila_ordenada(columnas[columna], P, fila);
									break;
								case 'T': case 't':
									mover_carta_pila_ordenada(columnas[columna], T, fila);
									break;
								case 'R': case 'r':
									mover_carta_pila_ordenada(columnas[columna], R, fila);
									break;
								case 'S': case 's':
									mover_carta_pila_ordenada(columnas[columna], S, fila);
									break;				
							}
			
							if((prompt[4] >= 'A' && prompt[4] <= 'G') || (prompt[4] >= 'a' && prompt[4] <= 'g') )  
							{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
								//para que no intente intercambia entre cartas de la misma columna
								if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[4]))
								{
									mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[4])], fila);
								}	
							}
						}
					}
					else
					{
						if(prompt[2] == '-')
						{
							switch(prompt[3])
							{
								case 'P': case 'p':
									mover_carta_pila_ordenada(columnas[columna], P, 1);
									break;
								case 'T': case 't':
									mover_carta_pila_ordenada(columnas[columna], T, 1);
									break;
								case 'R': case 'r':
									mover_carta_pila_ordenada(columnas[columna], R, 1);
									break;
								case 'S': case 's':
									mover_carta_pila_ordenada(columnas[columna], S, 1);
									break;				
							}
			
							if((prompt[3] >= 'A' && prompt[3] <= 'G') || (prompt[3] >= 'a' && prompt[3] <= 'g') )  
							{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
								//para que no intente intercambia entre cartas de la misma columna
								if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[3]))
								{
									mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[3])], 1);
								}	
							}
						}
					}
				} //A2 al A9, por ejemplo
				else if(prompt[1] >= '2' && prompt[1] <= '9')
				{
					fila = (int)prompt[1] - 48; //0 al 9 = 48 al 57 en ASCII
					
					if(prompt[2] == '-')
					{
						switch(prompt[3])
						{
							case 'P': case 'p':
								mover_carta_pila_ordenada(columnas[columna], P, fila);
								break;
							case 'T': case 't':
								mover_carta_pila_ordenada(columnas[columna], T, fila);
								break;
							case 'R': case 'r':
								mover_carta_pila_ordenada(columnas[columna], R, fila);
								break;
							case 'S': case 's':
								mover_carta_pila_ordenada(columnas[columna], S, fila);
								break;				
						}
			
						if((prompt[3] >= 'A' && prompt[3] <= 'G') || (prompt[3] >= 'a' && prompt[3] <= 'g') )  
						{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
							//para que no intente intercambia entre cartas de la misma columna
							if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[3]))
							{
								mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[3])], fila);
							}	
						}
					}
				}
				else if(prompt[1] == '-') //si solo ingreso la letra de la columna como primer termino, se asume que solo querria mover el tope de su carta a otra pila de cartas
				{
					switch(prompt[2])
					{
						case 'P': case 'p':
							mover_carta_pila_ordenada(columnas[columna], P, columnas[columna]->tope->fila);
							break;
						case 'T': case 't':
							mover_carta_pila_ordenada(columnas[columna], T, columnas[columna]->tope->fila);
							break;
						case 'R': case 'r':
							mover_carta_pila_ordenada(columnas[columna], R, columnas[columna]->tope->fila);
							break;
						case 'S': case 's':
							mover_carta_pila_ordenada(columnas[columna], S, columnas[columna]->tope->fila);
							break;				
					}
					
					if((prompt[2] >= 'A' && prompt[2] <= 'G') || (prompt[2] >= 'a' && prompt[2] <= 'g'))  
					{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
						//para que no intente intercambia entre cartas de la misma columna
						if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[2]))
						{
							mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[2])], columnas[columna]->tope->fila);
						}	
					}
				}
				else if((prompt[1] >= 'A' && prompt[1] <= 'G') || (prompt[1] >= 'a' && prompt[1] <= 'g'))
				{//movimiento rapido: si ingresa BB, por ejemplo, y la carta al tope de B puede colocarse en alguno de los monticulos ordenados, se colocara, seleccionando el monticulo correcto automaticamente
					if(detectar_indice_mazo(prompt[0]) == detectar_indice_mazo(prompt[1]))
					{
						movimiento_rapido(columnas[detectar_indice_mazo(prompt[1])], P, R, S, T, columnas[detectar_indice_mazo(prompt[1])]->tope->fila);
					}		
				}
			}	
	}
}

void movimiento_rapido(Mazo* origen, Mazo* P, Mazo* R, Mazo* S, Mazo* T, int fila)
{
	int existePalo = 0, x;
	Mazo* ordenadas_[4] = { P, R, S, T };
	
	//revisa los topes de los monticulos ordenados, si encuentra uno valido donde colocar la carta del monticulo desordenado, la coloca, y no encuentra un monticulo con un palo, la bandera se mantiene igual, la cual es usada en el siguiente if
	for(x = 0; x < 4; x++)
	{
		if(ordenadas_[x]->tope != NULL)
		{
			if(ordenadas_[x]->tope->palo == origen->tope->palo)
			{
				if(ordenadas_[x]->tope->numero == origen->tope->numero - 1)
				{
					mover_carta_pila_ordenada(origen, ordenadas_[x], fila);
					return;
				}
				
				existePalo = 1;
				break;
			}
		}
	}
	
	//si el palo no existe entre los monticulos ordenados, se coloca la carta en el primer monticulo vacio, siempre que sea una carta valida (As)
	if(!existePalo)
	{
		for(x = 0; x < 4; x++)
		{
			if(ordenadas_[x]->tope == NULL)
			{
				mover_carta_pila_ordenada(origen, ordenadas_[x], fila);
				return;
			}
		}
	}
}

void chequar_victoria(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G, int* salida)
{
	if(P->tope == NULL || R->tope == NULL || S->tope == NULL || T->tope == NULL)
	{
		return;
	}
	
	if(P->tope->numero == 13 && R->tope->numero == 13 && S->tope->numero == 13 && T->tope->numero == 13)
	{
		system("CLS");
		imprimir_tablero_(M, M_, P, R, S, T, A, B, C, D, E, F, G);
		printf("You win!\n");
		*salida = 1;
	}
}

int detectar_indice_mazo(char caracter)
{
	if(caracter >= 'A' && caracter <= 'G')
	{
		return (int)caracter - 65;//A-G es 65-71 en ASCII	
	}
	
	if(caracter >= 'a' && caracter <= 'g')
	{
		return (int)caracter - 97;//a-g es 97-103 en ASCII	
	}

	if(caracter == 'P' || caracter == 'p') return 0;
	if(caracter == 'R' || caracter == 'r') return 1;
	if(caracter == 'S' || caracter == 's') return 2;
	if(caracter == 'T' || caracter == 't') return 3;
	
	return -1;
}
