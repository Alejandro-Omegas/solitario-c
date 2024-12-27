#ifndef SOLITARIO_C_H
#define SOLITARIO_C_H
//structs
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
void solitario_c();
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
void nuke(Mazo* M, Mazo* M_, Mazo* P, Mazo* R, Mazo* S, Mazo* T, Mazo* A, Mazo* B, Mazo* C, Mazo* D, Mazo* E, Mazo* F, Mazo* G); //para liberar la memoria de todas las cartas tras terminar el juego
void help();
void terminar_memoria_insuficiente();
#endif

