#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define PATH "C:\\Users\\pastre-windows\\Dropbox\\PUCPR\\2017\\Segundo Semestre\\Estrutura de Dados\\Ima\\PacoteImagens1\\07.ppm"
#define PATH "C:\\Temp\\10.ppm"
#define FORMATO "P6"
#define ERRO -1
#define FALSE 0
#define TRUE 1
#define FUNDO '0'
#define NAO_FUNDO ' '
#define VISITADO 1


typedef struct pixel_{
    int x, y;
    struct  pixel_ * next;
} PIXEL;

//Inicia a pilha
void init_pilha(PIXEL *);
//Empurra um elemento na pilha, retornando o cabecalho
PIXEL * push(PIXEL  * , int, int, int *) ;
//Puxa um elemento da pilha, retornando cabecalho
PIXEL * pop(PIXEL * , int * , int *, int *);

//Inicializa os valores
unsigned char * * init_val (int *, int *);

//Conta as imagens na tela
int conta_imagens(unsigned char * *, int, int, PIXEL *, int *);

//Funcao recursiva que analiza a vizinhanca
int anal_viz(unsigned char * *, int, int, int, int, PIXEL *, int);
//Analiza a vizinhanca


int main() {
	unsigned char * * matriz = NULL;
	int wdt, hgt, lin, col, cont = 0;
	//Topo da pilha
	PIXEL * topo;
	matriz = init_val(&wdt, &hgt);

	init_pilha(topo);

	printf("A imagem possui %d objetos\n\n", conta_imagens(matriz, wdt, hgt, topo, &cont));

    system("PAUSE");
	return 0;
}

//Inicializa a largura e a altura da imagem, retornando a matriz populada com fundo e nao-fundo
unsigned char * * init_val( int * width, int * height) {
	int i = 0, j, k, wdt, hgt, num_linhas = 0, max_cor, pos_pxl = 0, lin = 0, col = 0;
	FILE * fp = NULL;
	char linha[200], r_fundo, b_fundo, g_fundo, r_teste, g_teste, b_teste;
	unsigned char * * matriz;
	char * bora;

	unsigned char c;

	fp = fopen(PATH, "rb");

	if (fp == NULL) {
		printf("DEU BO");
		return 0;
	}
	do {
		c = (unsigned char)fgetc(fp);
		if (c != '\n') {
			linha[i] = c;
			i++;
		}
		else {
			linha[i] = '\0';
			switch (num_linhas) {
			case 0:
				if (strcmp(FORMATO, linha) != 0) {
					printf("DEU BO NO FORMATO");
					return ERRO;
				}
				break;
			case 1:
				hgt = atoi(strtok(linha, " "));
				wdt = atoi(strtok(NULL, " "));
				matriz = (unsigned char * *)malloc(sizeof(unsigned char *) *  wdt);
				for (i = 0; i < wdt; i++)
					matriz[i] = (unsigned char *)malloc(sizeof(unsigned char) * hgt);
				break;
			case 2:
				max_cor = atoi(linha);
				break;
			}
			num_linhas++;
			i = 0;
		}
	} while (num_linhas < 3);


	for (lin = 0; lin < wdt; lin++) {
		for (col = 0; col < hgt; col++) {
			if ((lin == 0) && (col == 0)) {
				fscanf(fp, "%c%c%c", &r_fundo, &g_fundo, &b_fundo);
				matriz[0][0] = FUNDO;
			}
			else
				fscanf(fp, "%c%c%c", &r_teste, &g_teste, &b_teste);

			if ((r_fundo != r_teste) || (g_fundo != g_teste) || (b_fundo != b_teste))
				matriz[lin][col] = NAO_FUNDO;
			else
				matriz[lin][col] = FUNDO;
		}
	}
	matriz[0][0] = FUNDO;

	*width = wdt;
	*height = hgt;
	return matriz;
}

//Retorna a quantidade de imagens dentro da imagem passada
int conta_imagens(unsigned char * * matriz, int wdt, int hgt, PIXEL * topo, int * cont){
    int i, j, k = 0;
    for(i = 0; i < wdt; i++)
    for(j = 0; j < hgt; j++){
        if(matriz[i][j] != matriz[0][0] && matriz[i][j] != VISITADO){
            k += anal_viz(matriz, i, j, wdt, hgt, topo, cont);

        }
    }

    return k;
}

//Recursiva que empilha pixels proximos
int anal_viz(unsigned char * * matriz, int x, int y, int wdt, int hgt, PIXEL * topo, int * cont){
    matriz[x][y] =  VISITADO;
    int  newX,  newY;
    if(y != hgt -1)
        if((matriz[x][y + 1] != VISITADO) && (matriz[x][y + 1]  != FUNDO) && (y + 1 < hgt))
            topo = push(topo, x, y + 1, cont);

    if(x != wdt -1)
        if((matriz[x + 1][y] != VISITADO) && (matriz[x + 1][y]  != FUNDO )&& (x + 1 < wdt))
           topo =  push(topo, x + 1, y, cont);

    if(y != 0)
        if((matriz[x][y - 1] != VISITADO) && (matriz[x][y - 1]  != FUNDO) && (y - 1 > -1))
          topo =   push(topo, x, y - 1, cont);

    if(x != 0)
        if((matriz[x - 1][y] != VISITADO) && (matriz[x - 1][y]  != FUNDO) && (x - 1 > -1))
           topo =  push(topo, x - 1, y, cont);


    //printf("CONT: %d\n", cont);
    if(*cont == 0)
        return 1;

    else{
          //  printf("Pppo");
        topo =  pop(topo, cont, &newX, &newY);
        return anal_viz(matriz, newX, newY, wdt, hgt, topo, cont);
    }
}


//FUNCOES DA PILHA
void init_pilha(PIXEL * head){
    head = NULL;
}

PIXEL * push(PIXEL* topo, int xPos, int yPos, int * cont) {
    PIXEL * novo  = (PIXEL * )malloc(sizeof(PIXEL));
  //  printf("Pushed (%d, %d)\n", xPos, yPos );
    novo ->x = xPos;
    novo ->y = yPos;

    novo -> next = topo;
    topo = novo;

    *cont += 1;
    return topo;
}

PIXEL * pop(PIXEL * topo, int * cont, int * dataX, int * dataY){
    PIXEL * to_free = topo;
    *dataX = topo -> x;
    *dataY = topo -> y;
   // printf("Popped (%d, %d)\n\n", *dataX, *dataY );
    topo = topo ->next;
    free(to_free);
    * cont -= 1;
    return topo;
}
