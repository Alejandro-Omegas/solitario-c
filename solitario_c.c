#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "solitario_c.h"
#include "card_moves.h"
#include "'render'.h"
#include "deck_functions.h"
#include "input_user.h"

void solitario_c()
{
	system("COLOR 2F"); //para color de fondo verde (2) con color de letras blanco brillante (F)
	
	int salida;
	
	do
	{
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
		
	    salida = 0; //bandera de salida: 0 = continua juego, 1 = termina juego, 2 = reiniciar juego
		
		//funciones pre-juego
		generar_mazo(&M);
		mezclar_mazo(&M);
		distribuir_cartas(&M, &M_, &A, &B, &C, &D, &E, &F, &G);
		
		//juego
		while(salida  == 0)
		{
			system("CLS");
			imprimir_tablero_(&M, &M_, &P, &R, &S, &T, &A, &B, &C, &D, &E, &F, &G);
			prompt(&M, &M_, &P, &R, &S, &T, &A, &B, &C, &D, &E, &F, &G, &salida);
			chequar_victoria(&M, &M_, &P, &R, &S, &T, &A, &B, &C, &D, &E, &F, &G, &salida);
		}
		
		nuke(&M, &M_, &P, &R, &S, &T, &A, &B, &C, &D, &E, &F, &G); //libera toda la memoria de los mazos
	}
	while(salida == 2);

	system("PAUSE");
}

//termina el programa en caso de error por insuficiente memoria
void terminar_memoria_insuficiente()
{
	printf("Memoria insuficiente..."); getchar();
	exit(1);
}

//libera memoria de todos los mazos y cartas
void nuke(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G)
{
	Mazo* mazos[13] = { M, M_, P, R, S, T, A, B, C, D, E, F, G };
	Carta* cartaABorrar;
	int x;
	
	for(x = 0; x < 13; x++)
	{
		while(mazos[x]->tope != NULL)
		{
			cartaABorrar = mazos[x]->tope;
			mazos[x]->tope = mazos[x]->tope->siguiente;
			free(cartaABorrar);
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

//pantalla mostrada al ingresar "help" en el prompt
void help()
{
	system("CLS");
	printf("Los mazos estan nombrados con diferentes letras:\n");
	printf("- M es el monticulo desordenado (arriba a la izquierda)\n");
	printf("- P, R, S y T son los monticulos ordenados, los cuales estan vacios al inicio del juego (arriba a la derecha)\n");
	printf("- A, B, C, D, E, F y G son monticulos ordenados en columnas, donde inicialmente solo las cartas al tope estan reveladas\n\n");
	printf("El objetivo es ir moviendo las cartas bajo ciertas reglas, de manera a colocarlas todas en los monticulos ordenados (P, R, S y T) de manera que cada monticulo contenga solo cartas del mismo palo y ordenados de menor a mayor (con el As al fondo y el King al tope)\n\n");
	printf(" Reglas\n");
	printf(" ------\n");
	printf("En cada movimiento puedes realizar una de estas acciones:\n");
	printf("- Puedes colocar la carta de M a su costado boca arriba, una encima de otra. Si se acaban las cartas del mazo, puedes colocar de vuelta el mazo boca abajo, para asi revelar de a uno las cartas otra vez\n");
	printf("- Puedes mover la carta al tope de entre las cartas reveladas de M o del tope de algunas de las columnas (A, B, C, D, E, F, G) a unos de los monticulos P, R, S y T, siempre que cumpla con lo siguiente;\n");
	printf(" -> Si el monticulo P, R, S, T esta vacio, puedes mover la carta ahi si su valor es As\n");
	printf(" -> Si el monticulo P, R, S, T tiene alguna carta, puedes mover la carta si el palo es el mismo y su valor es +1 mayor al que esta en su tope. Por ejemplo, si en el monticulo R la carta al tope es 3 de picas, entonces solo puedes mover encima un 4 de picas\n");
	printf("- Puedes mover una carta desde M, o P, R, S, T al tope de algunas de las columnas (A, B, C, D, E, F, G) bajo la regla que la carta a mover debe de ser de un color opuesto al que esta al tope de la columna, y su valor debe ser uno menos que la carta que ya esta en el tope; Ejemplo: La columna F tiene una carta roja con valor 5 en su tope, por lo que solo puedes mover a ella un 4 negro\n");
	printf("- Puedes hacer este mismo movimiento anterior entre diferentes columnas. Por ejemplo; puedes mover un 5 negro al tope de la columna A hacia el 6 rojo que la columna G tiene en su tope\n");
	printf("- Este mismo movimiento puedes hacerlo con varias cartas a la vez, siempre que las cartas a mover sigan el orden de colores alternantes y valores decrecientes; Ejemplo: digamos que en la columna A tenemos en la columna 5 negro, 4 rojo y 3 negro, siendo esta ultima la carta en su tope. Nosotros podemos mover todas estas cartas en conjunto hacia otra columna siempre que esa columna tenga un 6 rojo. Si teniamos 5 negro, 4 rojo y 2 rojo, entonces no lo podriamos mover en conjunto, porque el 4 rojo y el 2 rojo no cumplen con la condicion de numeros consecutivos descendiente y colores alternantes\n");
	printf("- Cuando mueves una carta del tope de una de las columnas, la carta oculta abajo suyo, debe ser volteada boca-arriba.\n\n");
	printf(" Valores\n");
	printf(" -------\n");
	printf("Los valores de las cartas son igual al numero que tiene impreso, salvo el caso del As (A) que vale 1, Jack (J) que vale 11, Queen (Q) que vale 12 y King (K) que vale 13\n\n");
	printf(" Controles\n");
	printf(" ---------\n");
	printf("Ingresa las letras de dos mazos separados por un guion (-) y presiona ENTER para intentar mover la carta del mazo asociado a la primera letra, hacia el mazo asociado a la segunda letra. Ejemplo: \"a-b\" intentara mover la carta al tope de A hacia el tope de B\n");
	printf("Puedes intentar mover la carta del tope de un M o de una\n de las columnas (A, B, C, D, E, F, G) hacia P, R, S, T ingresando la letra origen dos veces. Ejemplo: ingresando \"gg\" intentara ubicar la carta al tope de G hacia el tope correcto de alguno de los monticulos P, R, S o T\n");
	printf("Puedes intentar mover un conjunto de cartas de una columna ingresando la letra de la columna origen, el numero de fila de la carta a mover, seguida de un guion (-) y la letra destino. Ejemplo: \"e3-a\" intentara mover un conjunto de cartas de E, desde su tope hasta la carta en la fila 3, hacia el tope de la columna A\n");
	printf("Puedes ver la siguiente carta del tope de M ingresando \"m\"\n");
	printf("Cabe mencionar, que el prompt reconoce tanto mayusculas como minusculas para estos controles\n\n");
	printf(" Miscelaneas\n");
	printf(" -----------\n");
	printf("Puedes ingresar estos otros comandos, seguido de ENTER:\n");
	printf("\"exit\" - Termina el juego\n");
	printf("\"restart\" - Reinicia el juego\n");
	printf("\"help\" - Muestra esta pantalla de ayuda\n\n");
	fputs("Disenhado y programado por Alejandro Daniel, Arriola Bareiro\n", stdout);
	system("PAUSE");
}
