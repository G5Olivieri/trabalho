/* Encontra as chaves  */  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 21
#define MAX 100

struct FL
{
	char from[BUFFER]; /* de        	   */
	char to[BUFFER];   /* para      	   */
	char skip;	   /* usado no retorno */
};

struct stack
{
	char from[BUFFER]; 
	char to[BUFFER];   
};

struct FL keys[MAX]; /* matrix de estrutura do banco de dados */	
struct stack bt_stack[MAX]; /* Pilha de retorno */
int f_pos = 0; /* numero de entradas do bd dos voos */
int find_pos = 0; /* indices de pesquisa no bd dos voos */
int tos = 0; /* posição pilha */

void setup();
void assert_keys(char *from, char *to);
int match(char *from, char *to);
int find(char *from, char *anywhere);
void push(char *from, char *to);
void pop(char *from, char *to);
void isKeys(char *from, char *to);
void route();

int main(int argc, char *argv[])
{
	setup();
	char from[] = "front_door";
	char to[] = "keys";
	isKeys(from, to);
	route();
	return 0;
}

void setup()
{
	assert_keys("front_door",   "lr"      );
	assert_keys("lr"        ,   "banheiro");
	assert_keys("lr"        ,   "hall"    );
	assert_keys("hall"      ,   "bd1"     );		
	assert_keys("hall"      ,   "bd2"     );		
	assert_keys("hall"      ,   "mb"      );		
	assert_keys("lr"        ,   "cozinha" );		
	assert_keys("cozinha"   ,   "keys"    );		
}

/* coloca os fatos no bd */
void assert_keys(char *from, char *to)
{
	if(f_pos < MAX)
	{
		strcpy(keys[f_pos].from, from);
		strcpy(keys[f_pos].to, to);
		keys[f_pos].skip = 0;
		f_pos++;
	}
	else printf("Banco de dados cheio.\n");
}

/* Mostra a rota das chaves */
void route()
{
	int t = 0;
	while(t < tos)
	{
		printf("%s ", bt_stack[t].from);
		t++;	
		if(t<tos)printf("para ");
	}
	printf("\n");
}

int match(char *from, char *to)
{
	register int t;
	for(t = f_pos-1; t > -1; t--)
		if((!strcmp(keys[t].from, from)) &&
			(!strcmp(keys[t].to, to)))
			return 1;
	return 0;
}

/* dado from, encontre anywhere */
int find(char *from, char *anywhere)
{
	for(find_pos = 0; find_pos < f_pos; find_pos++)
		if((!strcmp(keys[find_pos].from, from)) &&
			(!keys[find_pos].skip))
	{
		strcpy(anywhere, keys[find_pos].to);
		keys[find_pos].skip = 1;
		return 1;
	}

	return 0;
}

/* rotina principal: Determina se há 
 * uma rota entre from e to */
void isKeys(char *from, char *to)
{
	char anywhere[BUFFER];
	if(match(from, to))
	{
		/* é a meta */
		push(from, to);
		return;
	}
	
	/* tenta outra conexao */
	if(find(from, anywhere))
	{
		push(from, to);
		isKeys(anywhere, to);
	}

	else if(tos > 0)
	{
		/* retorna */
		pop(from, to);
		isKeys(from, to);
	}
}


/* rotinas de pilhas */
void push(char *from, char *to)
{
	if(tos < MAX)
	{
		strcpy(bt_stack[tos].from, from);
		strcpy(bt_stack[tos].to, to);
		tos++;
	}
	else printf("Pilha cheia!\n");
}

void pop(char *from, char *to)
{
	if(tos > 0)
	{
		tos--;
		strcpy(from, bt_stack[tos].from);
		strcpy(to, bt_stack[tos].to);
	}
	else printf("Pilha vazia!\n");
}


