/* Profundidade primeiro */  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 21
#define MAX 100

struct FL
{
	char from[BUFFER]; /* de        	   */
	char to[BUFFER];   /* para      	   */
	int distance;  /* distancia 	   */	
	char skip;	   /* usado no retorno */
};

struct stack
{
	char from[BUFFER]; 
	char to[BUFFER];   
	int distance;  	
};

struct FL flight[MAX]; /* matrix de estrutura do banco de dados */	
struct stack bt_stack[MAX]; /* Pilha de retorno */
int f_pos = 0; /* numero de entradas do bd dos voos */
int find_pos = 0; /* indices de pesquisa no bd dos voos */
int tos = 0; /* posição pilha */

void help();
void setup();
void assert_flight(char *from, char *to, int distance);
int match(char *from, char *to);
int find(char *from, char *anywhere);
void push(char *from, char *to, int dist);
void pop(char *from, char *to, int *dist);
void isFlight(char *from, char *to);
void route(char *to);

int main(int argc, char *argv[])
{
	setup();
	if(argc == 2 && !strcmp(argv[1], "--help"))
		help(argv[0]);

	char from[BUFFER];
	char to[BUFFER];
	
	printf("De: ");
	gets(from);
	printf("Para: ");
	gets(to);
	isFlight(from, to);
	route(to);
	return 0;	
}

void help(char *program)
{
	register int i;
	printf("Uso: %s <from> <to>\n\n", program);
	printf("Temos esses vôos:\n");
	for(i = 0; i < f_pos; i++)
	{
		printf("%s para %s %d KM\n", 
			   flight[i].from, flight[i].to, flight[i].distance);
	}

	exit(EXIT_SUCCESS);
}

void setup()
{
	assert_flight("New York",   "Chicago"    ,   1000);
	assert_flight("Chicago" ,   "Denver"     ,   1000);
	assert_flight("New York",   "Toronto"    ,    800);
	assert_flight("New York",   "Denver"     ,   1900);		
	assert_flight("Toronto" ,   "Calgary"    ,   1500);		
	assert_flight("Toronto" ,   "Los Angeles",   1800);		
	assert_flight("Toronto" ,   "Chicago"    ,    500);		
	assert_flight("Denver"  ,   "Urbana"     ,   1000);		
	assert_flight("Denver"  ,   "Houston"    ,   1500);		
	assert_flight("Houston" ,   "Los Angeles",   1500);		
	assert_flight("Denver"  ,   "Los Angeles",   1000);
}

/* coloca os fatos no bd */
void assert_flight(char *from, char *to, int distance)
{
	if(f_pos < MAX)
	{
		strcpy(flight[f_pos].from, from);
		strcpy(flight[f_pos].to, to);
		flight[f_pos].distance = distance;
		flight[f_pos].skip = 0;
		f_pos++;
	}
	else printf("Banco de dados cheio.\n");
}

/* Se há o vôo entre from e to, então devolve a distância do
 * vôo, caso contrário devolve 0 */
int match(char *from, char *to)
{
	register int t;
	for(t = f_pos-1; t > -1; t--)
		if((!strcmp(flight[t].from, from)) &&
			(!strcmp(flight[t].to, to)))
			return flight[t].distance;
	return 0;
}

/* dado from, encontre anywhere */
int find(char *from, char *anywhere)
{
	for(find_pos = 0; find_pos < f_pos; find_pos++)
		if((!strcmp(flight[find_pos].from, from)) &&
			(!flight[find_pos].skip))
		{
			strcpy(anywhere, flight[find_pos].to);
			flight[find_pos].skip = 1;
			return flight[find_pos].distance;
		}
	return 0;
}

/* rotinas de pilhas */
void push(char *from, char *to, int dist)
{
	if(tos < MAX)
	{
		strcpy(bt_stack[tos].from, from);
		strcpy(bt_stack[tos].to, to);
		bt_stack[tos].distance = dist;
		tos++;
	}
	else printf("Pilha cheia!\n");
}

void pop(char *from, char *to, int *dist)
{
	if(tos > 0)
	{
		tos--;
		strcpy(from, bt_stack[tos].from);
		strcpy(to, bt_stack[tos].to);
		*dist = bt_stack[tos].distance;
	}
	else printf("Pilha vazia!\n");
}

/* rotina principal: Determina se há 
 * uma rota entre from e to */
void isFlight(char *from, char *to)
{
	int d, dist;
	char anywhere[21];

	/* ve no destino */
	if(d=match(from, to))
	{
		push(from, to, d);
		return;
	}
	
	/* tenta outra conexao */
	if(dist=find(from, anywhere))
	{
		push(from, to, dist);
		isFlight(anywhere, to);
	}

	else if(tos > 0)
	{
		/* retorna */
		pop(from, to, &dist);
		isFlight(from, to);
	}
}

/* Mostra a rota e a distancia total */
void route(char *to)
{
	int dist, t;
	for(dist = 0, t=0; t < tos; t++)
	{
		printf("%s para ", bt_stack[t].from);
		dist += bt_stack[t].distance;
	}
	printf("%s\n", to);
	printf("A distancia é %d\n", dist);
}
