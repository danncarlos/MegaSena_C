#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<locale.h>
#define clear;	system("cls");
#define flush;	fflush(stdin);
#define line;	puts("\n\n");
#define MAX 5000
#define SIZE 6

/*
	Dannylo Carlos - 2216111572
	Natan Nascimento 2216111816
	Marcelo Souza 2216100928
	Vinicius Marcos 2216108448
*/

	void count(void);		//Contador * que número x saiu.
	void sorteio_use();		//Sorteio do usuário.
	void lerarq(void);		//Lê arquivo.
	void showin(void);		//Compara apostas do usuario com do sorteio.
	void sort(void);		//Ordena Matriz duplas.
	void showunicos(void);	//15 numeros unicos que mais sairam no sorteio.
	char menu(void);		//Menu
	
	struct x{
		char nome[45], cpf[11];
		int aposta[6];
	};
	
	struct x ficha[3];
	
	
	int *sorteio, cont[60], org[MAX][SIZE], duplas[60][2];
	
	int totalsize = 18;
	//Controls
	int i, j, l;

	FILE *fa;
	int control=0;
	//Var's
	int x, last, userindex=0; wheni;
	char m;
		
main(){
	srand(time(NULL));
	local();
	sorteio = (int *) malloc(SIZE * sizeof(int));
	
	for(i=0;i<60;i++){
		cont[i] = 0;
	}
	fa = fopen("sorteio.txt", "w");
	
	for(i=0;i<MAX;i++){
		last = 1;
		for(j=0;j<6;j++){//Cartela
			x = rand()%60+1;
			sorteio[j] = x;
			for(l=0;l<j;l++){
				if(sorteio[j] == sorteio[l]){
					sorteio[j]++;
					l--;
				}	
				if(sorteio[j]>60){
					sorteio[j] = 1;
					l--;
				}
			}
			/*
			for(wheni = 0; wheni<60 ;wheni++){
				if(sorteio[j] == wheni){
					when[wheni] = 0;
				}
				else{
					when[wheni]+=1;
				}
			}*/
			fprintf(fa, "%i\n", sorteio[j]);
			//printf("\t[%i]", sorteio[j]);
		}
		count();
		//printf("\n");	
	}
	fclose(fa);
	
	fa = fopen("maximum.txt", "w");
	for(i=0;i<60;i++){
		fprintf(fa, "%i\n", cont[i]);
	}
	fclose(fa);
	
	for(i=0;i<60;i++){
		printf("\nNúmero %i = %i vezes.", i+1, cont[i]);
	}
	
	puts("\nPressione uma tecla para continuar...");
	getch();	
	
	lerarq();
	sort();
	clear;	
	for(;;){
		switch(menu()){
			case '1':
				userindex = 0;
				sorteio_use();
				break;
				case '2':
					if(control == 1){
						showin();
					}
					else{
						puts("\nNot Yet...");
						getch();
						clear;
					}
					break;
			case '3':
				showunicos();
				break;
			case '4':
				for(i=0;i<60;i++){
					printf("\nNúmero %i = %i vezes.", i+1, cont[i]);
				}
				puts("\nPressione uma tecla para continuar...");
				getch();
				clear;				
				break;
			case '7':
				clear;
				/*
				for(i=0;i<60;i++){
					if(when[i+1] == 0){
						printf("Nº %02i = saiu no ultimo sorteio.\n", i+1);
					}
					else{
						printf("Nº %02i = não sai a %i sorteios seguidos.\n", i+1, when[i+1]);
					}
				}
				puts("\nPressione uma tecla para continuar...");
				getch();
				clear;	*/
				break;
			case '0':
				puts("\nAté...");
				remove("sorteio.txt");
				remove("maximum.txt");
				getch();
				exit(1);
				break;
			default:
				clear;
				break;
		}
	}	
}

char menu(){ // menu
	puts("* Faça as apostas para liberar uma nova opção.");
	puts("\t-----Menu-----");
	puts("\t1 - Fazer apostas");
	if(control == 1){
		puts("\t2 - Verificar Sorteio");		
	}
	puts("\t3 - 15 números mais sorteados");
	puts("\t4 - Todos números sorteados");
	puts("\t0 - Sair");
	printf("\tOpção: ");
	scanf("%s", &m);
	return m;
}

count(){//Condador
	int z, w, y;
	for(z=0;z<60;z++){
		for(y=0;y<6;y++){
			if(sorteio[y]== last){
				cont[z]++;
			}	
		}	
	last++;
	}	
}

void sorteio_use(){//aposta de usuario
	int l1;
	for(i=0; i<3; i++){
		clear;
		userindex+=1;
		printf("\t[%i]", userindex);
		printf("\nDigite seu nome: ");
		flush;
		gets(ficha[i].nome);
		printf("\nDigite seu CPF: ");
		flush;
		gets(ficha[i].cpf);		
		int l;
		for(l=0; l<6; l++){
			printf("\nDigite sua aposta %i: ", l+1);
			scanf("%i", &ficha[i].aposta[l]);
			if(ficha[i].aposta[l]<=0 || ficha[i].aposta[l]>60){
				l--;	
			}
			for(l1=0;l1<l;l1++){
				if(ficha[i].aposta[l1] == ficha[i].aposta[l]){
					l--;
				}	
			}
		}	 
	}
	clear;
	control = 1;
}//func


showin(){//Resultado dos usuário's
	int l, c, cuser, cont;
	for(i=0;i<3;i++){
		for(l=0;l<MAX;l++){
			cont = 0;
			for(c=0;c<SIZE;c++){
				for(cuser=0;cuser<SIZE;cuser++){
					if(ficha[i].aposta[cuser] == org[l][c]){
						cont++;
					}
				}
			}
			printf("Parabéns %s, você acertou %i números! Sorteio[%i]\n", ficha[i].nome, cont, l+1);	
		}
	}
	puts("\nPressione uma tecla para continuar...");
	getch();
	clear;
	
}

sort(){//Organiza a Matriz
	int lin, col;
	int temp, temp2, j;
	
	for(j=0;j<60;j++){//Ordena todos os números sorteados
		for(lin=j+1;lin<60;lin++){
			for(col=1;col<2;col++){
				if(duplas[lin][col] > duplas[j][col]){
					//Atribui os elementos da linha a 2 var's.
					temp	= duplas[j][col];
					temp2	= duplas[j][col-1];
					
					//
					duplas[j][col]	= duplas[lin][col];
					duplas[j][col-1]= duplas[lin][col-1];
					
					//
					duplas[lin][col]	= temp;		
					duplas[lin][col-1]	= temp2;
					
				}
			}
		}		
	}
	for(j=0;j<15;j++){//Ordena os 15 + sorteados
		for(lin=j+1;lin<15;lin++){
			for(col=0;col<1;col++){
				if(duplas[lin][col] < duplas[j][col]){
					//Atribui os elementos da linha a 2 var's.
					temp	= duplas[j][col];
					temp2	= duplas[j][col+1];
					//
					duplas[j][col]	= duplas[lin][col];
					duplas[j][col+1]= duplas[lin][col+1];
					//
					duplas[lin][col]	= temp;		
					duplas[lin][col+1]	= temp2;
									
				}
			}
		}
	}
	/*
	for(lin=0;lin<60;lin++){
		for(col=0;col<2;col++){
			printf("[%i]", duplas[lin][col]);
		}
		printf("\n");
	}
	*/
}

showunicos(){//15 números mais sorteados
	int l, c;
	//printf("\n\nNº\tQuant.\n");
	for(l=0;l<15;l++){
		for(c=0;c<2;c++){
			printf("Número %i = ", duplas[l][c]);
			c++;
			printf("%i vezes", duplas[l][c]);
		}
		printf("\n");
	}
	puts("\nPressione uma tecla para continuar...");
	getch();
	clear;
}

lerarq(){ // ler aquivo
	int lin, col;
	fa = fopen("sorteio.txt", "r");
	if(fa == NULL){
		puts("\nErro na abertura.");
		puts("Programa sera finalizado. ");
		getch();
		exit(1);
	}// if verificação de erro
	for(lin=0;lin<MAX;lin++){
		for(col=0;col<SIZE;col++){
			fscanf(fa, "%i\n", &org[lin][col]);
		}
	}
	
	puts("\n");
	fclose(fa);	
		
	fa = fopen("maximum.txt", "r");
	for(lin=0;lin<60;lin++){
		for(col=1;col<2;col++){
			fscanf(fa, "%i\n", &duplas[lin][col]);
		}
		for(col=0;col<1;col++){
			duplas[lin][col] = lin+1;
		}
	}
	fclose(fa);
		
}

void local(void){
	setlocale(LC_ALL, "Portuguese");
}
