#import <string.h>
#import <stdlib.h>
#import <stdio.h>

typedef struct asd{
	char cod;
	float media;
	char flag;
	struct asd * next;	
} CURSO;

CURSO * push(CURSO* topo, char  cod, float media) {
    CURSO * novo  = (CURSO * )malloc(sizeof(CURSO));
    novo ->cod = cod;
    novo ->media = media;
    novo -> next = topo;
    topo = novo;

    return topo;
}

CURSO * pop(CURSO * topo){
    CURSO * to_free = topo;
 //  printf("Popped (%d, %d)\n\n", *dataX, *dataY );
 
    topo = topo ->next;
    free(to_free);
    return topo;
}
void init(CURSO * head){
    head = NULL;
}

int printList(CURSO * l){
	
}
int ex4(){
	CURSO * topo;
	init(topo);
	topo = push(topo, 'a', 9.96);
	topo = 	push(topo, 'b', 1.12);
	topo = 	push(topo, 'c', 9.6);
	topo = 	push(topo, 'd', 6.36);
	topo = 	push(topo, 'e', 4.12);
	printf("OPA");
	printList(topo);
}


int calcula_pi(float altura){
	char sexo;
	printf("Vc e:\n 1) (H)omem\n 2) (M)ulher?\n");
	
	scanf("%c", &sexo);
	fflush(stdin);
	if(sexo == '1' || sexo == 'H' || sexo == 'h'){
		printf("Seu PI vale %f\n", (72.7 * altura) - 58);
	}else{
		printf("Seu PI vale %f\n", (62.1 * altura) - 44.7);
	}
	
	return 5;
}
int calcula_imc(float altura){
	float peso;
	char opc;
	printf("Quanto vc pesa?\n");
	scanf("%f", &peso);
	fflush(stdin);
	float imc = peso / (altura * altura);
	printf("Seu IMC vale % f\nGostaria de saber seu Grau de Obesidade por apenas mais 2 reais? (S/n)\n", imc);
	scanf("%c", &opc);
	fflush(stdin);
	if(opc != 's' && opc != 'S')
		return 5;
	
	if(imc < 18.4){
		printf("Seu Grau de Obesidade e Abaixo do Peso");
	}
	else if(imc < 24.9){
		printf("Seu Grau de Obesidade e Peso normal ");
	}
	else if(imc < 29.9){
		printf("Seu Grau de Obesidade e Sobrepeso");
	}
	else if(imc < 34.9){
		printf("Seu Grau de Obesidade e Obesidade Grau I");
	}
	else if(imc < 39.9){
		printf("Seu Grau de Obesidade e Obesidade Grau II");
	}
	else if(imc > 40){
		printf("Seu Grau de Obesidade e Obesidade Grau III");
	}
	printf("\n");
	return 7;
}
int ex3(){
	int calcIMC = 0; int calcIMCPlus = 0; int calcPI = 0;
	while (1){
		char opc;
		printf("Bem vindo ao sistema de consultas do quiosque ! Entre a consulta desejada: \n1) PI\n2)IMC\n3)Fechar o dia\n"); 
		scanf("%c", &opc);
		fflush(stdin);
		float altura;
		if(opc == '1'){
			printf("Qual a sua altura? \n");
			scanf("%f", &altura);
			fflush(stdin);
			calcPI ++;
			calcula_pi(altura);
		}
		else if (opc == '2'){
			printf("Qual a sua altura? \n");
			scanf("%f", &altura);
			fflush(stdin);
			if(calcula_imc(altura) == 7)
				calcIMCPlus ++;
			else
				calcIMC ++;
		}else if(opc == '3'){
			break;
		}
	}
	float montante = (calcIMC + calcPI) * 5 + calcIMCPlus * 7;
	printf("RESULTADO DO DIA: %f\nConsultas ao IMC: %d\t Consultas ao IMC + Grau de Obesidade: %d\tConsultas ao PI: %d\n", montante, calcIMC, calcIMCPlus, calcPI);
}

int ex2(int * * matriz){
	if(matriz == 0){	//Inicialize a matriz, usar null inves de 0
		matriz = (int * * ) malloc(2 * sizeof(int *));
		int i, j;
		for (i = 0; i < 2; i++){
			matriz[i] = (int *) malloc(4 * sizeof(int ));
		}
		printf("Por favor, inicialize a matriz: \n");
		for(i = 0; i < 2; i ++){
			for(j = 0; j < 4; j++){
				int toAppend = 0;
				printf("Valor para linha %d coluna %d: ", i, j);
				scanf("%d", &toAppend);
				matriz[i][j] = toAppend;
			}
		}
	}
	
	int search;
	printf("Entre com o valor que deseja buscar. Entre com -1 para sair: ");
	scanf("%d", &search);
	if(search == -1)
		return 0;
	int i, j;
	for(i = 0; i < 2; i ++){
			for(j = 0; j < 4; j++){
				if(matriz[i][j] == search){
					printf("Encontrei o valor que vc busca! Esta na linha %d e coluna %d\n", i, j);
					return 	ex2(matriz); 
				}			
		}
	}
	
	printf("Nao pude encontrar este valor na matriz :( \n");
	return 	ex2(matriz);
}

int ex1(){
	char  frase[500];
	printf("Entre sua frase: ");
	scanf("\n %s", &frase);
	
	if(strlen(frase) == 0){
		printf("FRASE INVALIDA");
		return 0;
	}
	
	char  contrario [500] ;
	strcpy(contrario, frase);
	printf("CONTRAIO %s\n", contrario);
	int i, j = 0;
	
	for(i = strlen(frase); i >=0; i--){
		if (frase[i] == '\0')
			continue;
		contrario[j] = frase[i]  ;
		j++;
	}
	contrario[i] = '\0';
	printf("RESP: %s\n", contrario);
	
	return 0;
}


int main(){
	ex4();
}
