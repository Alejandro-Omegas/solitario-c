#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "input_user.h"

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
	
	if(strcmp(prompt, "help") == 0) //abre pantalla de ayuda ingresando "help" en minusculas
	{
		help();
		return;
	}
	
	if(strcmp(prompt, "exit") == 0) //se puede salir del juego ingresando "exit" todo en minuscula
	{
		*salida = 1;
		return;
	}
	
	if(strcmp(prompt, "restart") == 0) //para reiniciar del juego ingresando "restart" todo en minuscula
	{
		*salida = 2;
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
				if(M_->tope != NULL) movimiento_rapido(M_, P, R, S, T, -1);
			}
			else
			{				
				//despliega siguiente carta del monticulo desordenado
				if(M->tope != NULL) //el monticulo desordenado tiene aun cartas
				{
					mover_tope_carta(M, M_);
					M_->tope->oculto = 0;	
				}
				else //el monticulo desordenado no tiene cartas que sacar
				{
					while(M_->tope != NULL) //el sub-monticulo desordenado tiene aun cartas, entonces los regresa al M
					{
						mover_tope_carta(M_, M);
						M->tope->oculto = 1;
					}
					
					if(M->tope != NULL) //significa que se movio cartas de M_, i.e., hay aun cartas
					{
						mover_tope_carta(M, M_);
						M_->tope->oculto = 0;
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
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;
								case 'T': case 't':
									mover_carta_pila_ordenada(columnas[columna], T, fila);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;
								case 'R': case 'r':
									mover_carta_pila_ordenada(columnas[columna], R, fila);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;
								case 'S': case 's':
									mover_carta_pila_ordenada(columnas[columna], S, fila);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;				
							}
			
							if((prompt[4] >= 'A' && prompt[4] <= 'G') || (prompt[4] >= 'a' && prompt[4] <= 'g') )  
							{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
								//para que no intente intercambia entre cartas de la misma columna
								if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[4]))
								{
									mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[4])], fila);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
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
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;
								case 'T': case 't':
									mover_carta_pila_ordenada(columnas[columna], T, 1);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;
								case 'R': case 'r':
									mover_carta_pila_ordenada(columnas[columna], R, 1);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;
								case 'S': case 's':
									mover_carta_pila_ordenada(columnas[columna], S, 1);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
									break;				
							}
			
							if((prompt[3] >= 'A' && prompt[3] <= 'G') || (prompt[3] >= 'a' && prompt[3] <= 'g') )  
							{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
								//para que no intente intercambia entre cartas de la misma columna
								if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[3]))
								{
									mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[3])], 1);
									if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
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
								if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
								break;
							case 'T': case 't':
								mover_carta_pila_ordenada(columnas[columna], T, fila);
								if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
								break;
							case 'R': case 'r':
								mover_carta_pila_ordenada(columnas[columna], R, fila);
								if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
								break;
							case 'S': case 's':
								mover_carta_pila_ordenada(columnas[columna], S, fila);
								if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
								break;				
						}
			
						if((prompt[3] >= 'A' && prompt[3] <= 'G') || (prompt[3] >= 'a' && prompt[3] <= 'g') )  
						{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
							//para que no intente intercambia entre cartas de la misma columna
							if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[3]))
							{
								mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[3])], fila);
								if(columnas[detectar_indice_mazo(prompt[0])]->tope != NULL) columnas[detectar_indice_mazo(prompt[0])]->tope->oculto = 0;
							}	
						}
					}
				}
				else if(prompt[1] == '-') //si solo ingreso la letra de la columna como primer termino, se asume que solo querria mover el tope de su carta a otra pila de cartas
				{
					if(columnas[columna]->tope == NULL) break; //condicional de guardia
					
					switch(prompt[2])
					{
						case 'P': case 'p':
							mover_carta_pila_ordenada(columnas[columna], P, columnas[columna]->tope->fila);
							columnas[columna]->tope->oculto = 0;
							break;
						case 'T': case 't':
							mover_carta_pila_ordenada(columnas[columna], T, columnas[columna]->tope->fila);
							columnas[columna]->tope->oculto = 0;
							break;
						case 'R': case 'r':
							mover_carta_pila_ordenada(columnas[columna], R, columnas[columna]->tope->fila);
							columnas[columna]->tope->oculto = 0;
							break;
						case 'S': case 's':
							mover_carta_pila_ordenada(columnas[columna], S, columnas[columna]->tope->fila);
							columnas[columna]->tope->oculto = 0;
							break;				
					}
					
					if((prompt[2] >= 'A' && prompt[2] <= 'G') || (prompt[2] >= 'a' && prompt[2] <= 'g'))  
					{//ya no lee el numero porque es irrelevante, solo necesitamos la letra destino
						//para que no intente intercambia entre cartas de la misma columna
						if(detectar_indice_mazo(prompt[0]) != detectar_indice_mazo(prompt[2]))
						{
							mover_cartas_entre_columnas(columnas[detectar_indice_mazo(prompt[0])], columnas[detectar_indice_mazo(prompt[2])], columnas[columna]->tope->fila);
							if(columnas[detectar_indice_mazo(prompt[0])]->tope != NULL) columnas[detectar_indice_mazo(prompt[0])]->tope->oculto = 0;
						}	
					}
				}
				else if((prompt[1] >= 'A' && prompt[1] <= 'G') || (prompt[1] >= 'a' && prompt[1] <= 'g'))
				{//movimiento rapido: si ingresa BB, por ejemplo, y la carta al tope de B puede colocarse en alguno de los monticulos ordenados, se colocara, seleccionando el monticulo correcto automaticamente
					if(columnas[detectar_indice_mazo(prompt[0])]->tope != NULL &&
					   detectar_indice_mazo(prompt[0]) == detectar_indice_mazo(prompt[1]))
					{
						movimiento_rapido(columnas[detectar_indice_mazo(prompt[1])], P, R, S, T, columnas[detectar_indice_mazo(prompt[1])]->tope->fila);
						if(columnas[columna]->tope != NULL) columnas[columna]->tope->oculto = 0;
					}		
				}
			}	
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

