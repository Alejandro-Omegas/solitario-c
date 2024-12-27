#ifndef STRUCTS_H
#define STRUCTS_H
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
#endif
