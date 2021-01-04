#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef struct rank {
	int pontos;
	char nome[30], dificuldade[8];
} trank;

void showtab(int campo[][15], int tammaximo);
void construircampo(int tammaximo, int qntbombas, int campo[][15]);
void printcampo (int campo[][15], int tammaximo);
void abrirzero(int campo[][15], int posicao1, int posicao2, int tammaximo, int *numcasas, int *pontuacao);
void novoabrirzero(int campo[][15], int tammaximo, int linha, int coluna, int *numerocasas, int *pontuacao);

int main (void) {

  setlocale(LC_ALL, "Portuguese");
	int campo[15][15], tammaximo, qntbombas;
	int numero, dificuldade;
	int posicao1, posicao2, numerocasas=0, pontuacao=0, ganhou;
	int aux, i;
  FILE *ranking;
	trank rank[11];
	int posnovojogador=0, posicaorelativa=0;
	char auxc='a', straux[50];


	srand(time(0)); //Essa é a 'seed' para o número aleatório, pois sem ela os números 'aleatórios' não mudarão. Com a seed no tempo, a cada intervalo de tempo (provavelmente a cada segundo) novos números aleatórios são gerados, e assim o tabuleiro será realmente aleatório.

  do{
    aux=1;
    ganhou=1;


		//Verifica quantas pessoas já estão escritas no rank
		ranking = fopen("ranking.txt", "r");
		fseek(ranking, 0, SEEK_SET);
		while(auxc != EOF){
			auxc = fgetc(ranking);
			if(auxc == '\n')
				posnovojogador++;
		}
		fclose(ranking);
		
		//Passa os jogadores já registrados para um vetor
		fopen("ranking.txt", "r");
		rewind(ranking);		
		for(i=1; i<=posnovojogador; i++){
			fscanf(ranking, " %s %s %d", rank[i].nome, rank[i].dificuldade, &rank[i].pontos);
		}		
		fclose(ranking);

		//Mais pra frente, vai ser feita uma verificação no arquivo do ranking para ver se o novo jogador é o jogador de número 11, se for, ele ou vai substituir o de pontuação menor ou vai ser descartado e vai ser falado que ele não conseguiu entrar no "top 10", assim, podemos ter certeza que o vetor rank[] nunca terá mais de 11 elementos, sendo o elemento 0 o novo jogador (volátil) e os outros 10 serão preenchidos usando o arquivo.

		system("clear");
    	printf("------------------- CAMPO MINADO ---------------- \n\n");
      printf("0 - Como jogar\n");
    	printf("1 - Jogar\n");
    	printf("2 - Créditos\n");
    	printf("3 - Ranking\n");
      printf("4 - Sair\n");
    	printf("\n");
    	printf("\nEscolha a opção desejada: ");
    	scanf(" %d", &numero);

    	switch (numero)
      {
        case 0:
      		system("clear");
      		printf("Carregando Regras...\n");
      		printf("-------------------------------------------------------------------------------\n");
      		printf("--------------------------------COMO JOGAR-------------------------------------\n");
      		printf("-------------------------------------------------------------------------------\n");
      		printf("\n");
      		printf("O jogo Campo Minado consiste em um tabuleiro dividido em casas cujo conteúdo\na princípio é secreto. Para jogar, escolha uma casa para revelar seu conteúdo,\nque pode ser:\n");
          printf("\n");
          printf("1) uma mina (representada pelo número 9) que explode ao ser revelada,\nterminando o jogo. Evite as minas a todo custo!\n");
          printf("\n");
          printf("2) um número de 0 a 8, indicando quantas minas existem nas casas adjacentes\nao número em questão. Por exemplo, se uma casa aberta for '3', significa que\ntrês das casas ao redor dela são minas, então cuidado!\nUse os números a seu favor para descobrir onde estão as minas.\n");
          printf("\n");
          printf("Para ganhar o jogo, abra todas as casas de 0 a 8 sem pisar em nenhuma mina.\nBoa sorte!\n");
          printf("\n");
          printf("Pressione qualquer tecla para voltar ao menu principal.\n ");
          printf("\n");
  
					getchar();
					getchar();
          //Como não há system("pause"), deve-se usar getchar, porém como há um scanf antes, o buffer do teclado precisa ser limpo com um getchar "extra" antes de realmente usá-lo.

      		aux=0;
      		break;

          
    		case 1:
        	system("clear");
        	printf("Carregando opções...\n");
        	printf("---------------------------------------------- \n");
        	printf("1 - Fácil \n");
        	printf("2 - Médio \n");
        	printf("3 - Difícil \n");
        	printf("\n");
        	printf("\nEscolha a opção desejada: ");
        	scanf(" %d", &dificuldade);
          
        	//Define o nível de dificuldade do jogo
        	switch (dificuldade){
        		case 1:
            	printf("Dificuldade definida como Fácil!\n\n");
            	tammaximo = 9;
							qntbombas = 6;
							strcpy(rank[0].dificuldade, "Fácil");
            	break;
        		case 2:
            	printf("Dificuldade definida como Médio!\n\n");
            	tammaximo = 12;
							qntbombas = 15;
							strcpy(rank[0].dificuldade, "Médio");
            	break;
        		case 3:
            	printf("Dificuldade definida como Difícil!\n\n");
            	tammaximo = 15;
							qntbombas = 20;
							strcpy(rank[0].dificuldade, "Difícil");
            	break;
						default:
							printf("Opção inválida!\n");
							aux = 0;
							printf("Aperte qualquer tecla para voltar ao menu principal ");
							getchar();
							getchar();
							break;
        	}
        break;

    		case 2:
      		system("clear");
      		printf("Carregando créditos...\n");
      		printf("-------------------------------------------------------------------------------\n");
      		printf("----------------------------------CRÉDITOS-------------------------------------\n");
      		printf("-------------------------------------------------------------------------------\n");
      		printf("\n");
      		printf("Este jogo foi desenvolvido por:\n");
      		printf("\n");
      		printf("- Bruna Rafael Neira Muñoz - Matrícula número 2020003676 \n");
      		printf("\n");
      		printf("- Jennifer Camila Gonçalves - Matrícula número 2018008399 \n");
      		printf("\n");
      		printf("- Marcelo Robert Santos - Matrícula número 2020002777 \n");
      		printf("\n");
      		printf("Notas sobre o jogo: \n");
      		printf("Este jogo foi desenvolvido no ano de 2020 para a aula da Prof. Melise Maria Veiga de Paula,\n");
      		printf("docente do curso de Ciência da Computação na UNIFEI (Universidade Federal de Itajubá),\n");
      		printf("como o trabalho final da matéria de FUNDAMENTOS DA PROGRAMAÇÃO.\n");
      		printf("Tendo em vista a avaliação do aprendizado dos alunos do grupo em questão\n");
      		printf("e da fixação da matéria lecionada durante o decorrer do semestre.\n");
      		printf("\n");
      		printf("Pressione qualquer tecla para voltar ao menu principal. ");

					getchar();
					getchar();	//Como não há system("pause"), deve-se usar getchar, porém como há um scanf antes, o buffer do teclado precisa ser limpo com um getchar "extra" antes de realmente usá-lo.

      		aux=0;
      		break;
        case 3:
					system("clear");
					printf("Melhores jogadores:\n\n");
          ranking = fopen("ranking.txt", "r");
          for(i=1; i<=posnovojogador; i++){
						fgets(straux, 50, ranking);
						printf("%dº Lugar: %s", i, straux);
					}
					fclose(ranking);

          printf ("\n\nAperte qualquer tecla para voltar ao menu principal ");
          getchar();
          getchar();
          aux = 0;
          break;				
    		case 4:
      		system("clear");
      		printf("Saindo do jogo ...");
      		aux=0;
					break;
    		default:
      		printf("\nOpção INVÁLIDA\n");
					aux = 0;
					printf("Aperte qualquer tecla para voltar ao menu principal ");
					getchar();
					getchar();
  		}

  	if(aux==1){
 			construircampo(tammaximo, qntbombas, campo);
			while(ganhou==1 && numerocasas <((tammaximo*tammaximo)-qntbombas)){
    		printcampo(campo, tammaximo);
				//printf("\n%d\n%d\n", numerocasas, pontuacao); //PARA DEBUG
    		printf("\n Digite a linha e a coluna:");
    		scanf("%d %d", &posicao1, &posicao2);
    		if(posicao1 <= tammaximo && posicao1 >= 0 && posicao2 <= tammaximo && posicao2 >= 0){
      		switch(campo[posicao1-1][posicao2-1]-10){
	      		case 0:
							//showtab(campo, tammaximo);
            	//abrirzero(campo, posicao1-1, posicao2-1, tammaximo, &numerocasas, &pontuacao);

							system("clear");
							novoabrirzero(campo, tammaximo, posicao1-1, posicao2-1, &numerocasas, &pontuacao);
							
            	break;
        		case 1:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 2;
            	break;
        		case 2:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 3;
            	break;
        		case 3:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 4;
            	break;
						case 4:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 5;
            	break;
						case 5:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 6;
            	break;
						case 6:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 7;
            	break;
						case 7:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 8;
            	break;
						case 8:
            	campo[posicao1-1][posicao2-1]=campo[posicao1-1][posicao2-1]-10;
            	numerocasas++;
              pontuacao += 9;
            	break;
        		case 9:
							system("clear");
          		printf("\n================================\n");
          		printf("\t Você perdeu\n");
          		printf("================================\n\n");
							showtab(campo, tammaximo);
              printf("Sua pontuação foi: %d\n", pontuacao);
          		ganhou=0;
          		break;
      		}
    		}
				else
					printf("Esse número é inválido.");
  		}
      if(ganhou==1){
				system("clear");
				showtab(campo, tammaximo);
        printf("\nVocê ganhou!\n");
        printf("Sua pontuação foi: %d\n", pontuacao);
      }

			//Registra o novo jogador no vetor
      printf("\nDigite seu nome (sem espaços):\n");
			scanf(" %s", rank[0].nome);
			rank[0].pontos = pontuacao;
			//Define entre quais jogadores está o jogador novo (se está em 1º lugar, 2º lugar...)
			for(i=1; i<=posnovojogador; i++){
				if(rank[i].pontos > rank[0].pontos)
					posicaorelativa++;
			}	//Se a pontuação referência for maior, então o novo jogador aumenta sua posição ordinal (por ex. de 1º lugar vai para o 2º lugar)

			//Se houverem 10 jogadores e ele estiver no último lugar, é porque ele não tem pontos suficientes para entrar no top 10
			//printf("\n%d\n%d\n%d\n%d\n", posnovojogador, posicaorelativa, rank[posnovojogador].pontos, rank[posnovojogador-1].pontos); //PARA DEBUG
			if(posnovojogador == 10 && posicaorelativa == 10){
				printf("\nInfelizmente você não está entre os dez melhores jogadores...\n");
			}
			else{
				//Se a lista não estiver cheia, apenas coloca ele no lugar certo.
				if(posnovojogador < 10){
					fopen("ranking.txt", "w");
					rewind(ranking);

					//[RESOLVIDO] O if e else que estavam aqui não eram mais necessários pois o bug já foi resolvido.
					//[ANTES]: Esse if e o else em seguida são para debugar, pois ele estava printando no arquivo um jogador repetido ou sobrescrevendo um jogador que já estava registrado

					for(i=1; i<=posicaorelativa; i++){
						fprintf(ranking, "%s %s %d\n", rank[i].nome, rank[i].dificuldade, rank[i].pontos);
					}

					fprintf(ranking, "%s %s %d\n", rank[0].nome, rank[0].dificuldade, rank[0].pontos);

					for(i=posicaorelativa+1; i<=posnovojogador; i++){
						fprintf(ranking, "%s %s %d\n", rank[i].nome, rank[i].dificuldade, rank[i].pontos);
					}
					fclose(ranking);
				}

				//Se a lista estiver cheia, tem que substituir todo o arquivo mas sem o jogador com menor pontuacao, que no caso, SEMPRE vai ser o último jogador, ou seja, sempre vai ser o jogador de elemento 11 (lembrando que 0 é o novo e os jogadores entre 1 e 11 são as posições dos jogadores já registrados)
				else{
					fopen("ranking.txt", "w");
					rewind(ranking);

					for(i=1; i<=posicaorelativa; i++){
						fprintf(ranking, "%s %s %d\n", rank[i].nome, rank[i].dificuldade, rank[i].pontos);
					}

					fprintf(ranking, "%s %s %d\n", rank[0].nome, rank[0].dificuldade, rank[0].pontos);

					for(i=i; i<posnovojogador; i++){
						fprintf(ranking, "%s %s %d\n", rank[i].nome, rank[i].dificuldade, rank[i].pontos);
					}

					fclose(ranking);
				}
			}

			printf("Aperte qualquer tecla para continuar\n");
    	getchar();
    	getchar();
    }


		//Reseta as variáveis para serem usadas no menu denovo
		aux=0;
		numerocasas=0;
		pontuacao=0;
		posnovojogador=0;
		posicaorelativa=0;
		auxc='a';
	} while (numero!=4);

  return 0;
}


//Função para construir o campo, a base do jogo
void construircampo(int tammaximo, int qntbombas, int campo[][15]){
	int i, linha, coluna;
	int blinha, bcoluna;

	//Inicializar todos os valores como 0
	for(linha=0;linha<tammaximo;linha++){
		for(coluna=0;coluna<tammaximo;coluna++){
			campo[linha][coluna] = 0;
		}
	}

	//Gera bombas aleatórias
	for(i=0;i<qntbombas;i++){
		blinha = rand()%tammaximo;
		bcoluna = rand()%tammaximo;
		campo[blinha][bcoluna] = 9;
	}

	//Colocar os números em volta
	for(linha=0;linha<tammaximo;linha++){
		for(coluna=0;coluna<tammaximo;coluna++){
			if(campo[linha][coluna]>9)
				campo[linha][coluna] = 9;
			if(campo[linha][coluna] == 9){
				if(linha != tammaximo-1){
					campo[linha+1][coluna] = campo[linha+1][coluna] + 1;			//baixo
					if(coluna != tammaximo-1)
						campo[linha+1][coluna+1] = campo[linha+1][coluna+1] + 1;			//baixo-direita
					if(coluna != 0)
						campo[linha+1][coluna-1] = campo[linha+1][coluna-1] + 1;			//baixo-esquerda
				}
				if(linha != 0){
					campo[linha-1][coluna] = campo[linha-1][coluna] + 1;			//cima
					if(coluna != tammaximo-1)
						campo[linha-1][coluna+1] = campo[linha-1][coluna+1] + 1;			//cima-direita
					if(coluna != 0)
						campo[linha-1][coluna-1] = campo[linha-1][coluna-1] + 1;			//cima-esquerda
				}
				if(coluna != tammaximo-1)
					campo[linha][coluna+1] = campo[linha][coluna+1] + 1;			//direita
				if(coluna != 0)
					campo[linha][coluna-1] = campo[linha][coluna-1] + 1;			//esquerda
			}
		}
	}
	//Nessa função anterior, deve haver as restrições, senão o programa tenta definir valores para um elemento que não existe no vetor (por exemplo campo[-1][-1] ou campo[13][13]).

	//Esconde os valores
	for(linha=0;linha<tammaximo;linha++){
		for(coluna=0;coluna<tammaximo;coluna++){
			if(campo[linha][coluna]>9)
				campo[linha][coluna] = 9;
			campo[linha][coluna] = campo[linha][coluna] + 10;
		}
	}


	//A partir daqui, todos os valores serão dez a mais que o valor real; caso na hora de printar o valor do campo seja maior que 10 (em primeiro caso, todos os valores), será impresso apenas um '- '. Quando o usuário escolher uma casa para abrir, simplesmente se subtrai o valor daquela casa por 10; se a casa[linha][coluna] - 10 for igual à 9, então é uma bomba, e o usuário perdeu, senão, será exibido o valor real daquela casa.
}


//Exibe o tabuleiro com a verificação de se o campo está escondido ou não.
void printcampo (int campo[][15], int tammaximo)
{
	int i, linha, coluna;

	system("clear");

	//Esse primeiro for printa o número das colunas
	printf("\n\n    ");
	for(i=0; i<tammaximo; i ++)
    {
		printf("%d ", i+1);
		if(i<9 && tammaximo>9) //Ajusta o espaçamento dependendo do tabuleiro
			printf(" ");
	}
	printf("\n\n");

	//Esse segundo for printa o número das linhas
	for(linha=0;linha<tammaximo;linha++){
		printf("%d  ", linha+1);
		if(linha<9) //Ajusta o espaçamento dependendo do tabuleiro
			printf(" ");
		//Esse terceiro for printa os elementos
		for(coluna=0;coluna<tammaximo;coluna++){
			if(campo[linha][coluna]>=10)
				printf("- ");
       else
				printf("%d ", campo[linha][coluna]);
			if(tammaximo>9) //Ajusta o espaçamento dependendo do tabuleiro
				printf(" ");
			if(coluna == tammaximo-1)
				printf("\n");
		}
	}
}


//Função para mostrar todo o tabuleiro quando o jogador perder, mostrando os valores
//para chamar a função, use showtab(campo, tammaximo);
void showtab(int campo[][15], int tammaximo)
{
	int linha, coluna, i;
	printf("\n\n    ");

	//Esse primeiro for printa o número das colunas
	for(i=0; i<tammaximo; i++){
		printf("%d ", i+1);
		if(i<9 && tammaximo>9) //Ajusta o espaçamento dependendo do tabuleiro
			printf(" ");
	}
	printf("\n\n");

	//Esse segundo for printa o número das linhas
	for(linha=0;linha<tammaximo;linha++){
		printf("%d  ", linha+1);
		if(linha<9)
			printf(" ");
		//Esse terceiro for printa os elementos
		for(coluna=0;coluna<tammaximo;coluna++){
			//Se o campo não foi aberto ainda, será aberto agora:
			if(campo[linha][coluna]>9)
				campo[linha][coluna] = campo[linha][coluna] - 10;
			//Se for 0 printa '-', se não for, printa o elemento
			if(campo[linha][coluna] == 0)
				printf("- ");
			else
				printf("%d ", campo[linha][coluna]);
			if(tammaximo>9)	//Ajusta o espaçamento dependendo do tabuleiro
				printf(" ");
			if(coluna == tammaximo-1)
				printf("\n");
		}
	}
	printf("\n");
}

/*
void abrirzero(int campo[][15], int linhai, int colunai, int tammaximo, int *numcasas, int *pontuacao){
  int i, j, k;
	int pararc=0, pararl=0, parark=0;
  //Abre as casas ao redor da posição escolhida


	//Para baixo e direita
	for(i=linhai; pararl == 0; i++){

		for(j=colunai; pararc == 0; j++){

			for(k=i; parark == 0; k++){
				if(campo[k][j] >= 10){
					campo[k][j] -= 10;
					(*numcasas)++;
					(*pontuacao)++;
          
				}
				if(k == tammaximo-1)
					parark = 1;
				if(campo[k][j] < 10 && campo[k][j] > 0)
					parark = 1;
			}

			parark = 0;
			if(j == tammaximo-1)
				pararc = 1;
			if(campo[i][j] > 0 && campo[i][j] < 10)
				pararc = 1;
		}

		parark = 0;
		pararc = 0;
		if(i == tammaximo-1)
			pararl = 1;
		if(campo[i+1][colunai] > 0 && campo[i+1][colunai] != 10){
			pararl = 1;
    }
	}

	pararl = 0;
	pararc = 0;
	parark = 0;
	//Para baixo e esquerda
	for(i=linhai; pararl == 0; i++){

		for(j=colunai; pararc == 0; j--){

			for(k=i; parark == 0; k++){
				if(campo[k][j] >= 10){
					campo[k][j] -= 10;
					(*numcasas)++;
          (*pontuacao)++;
				}
				if(k == tammaximo-1)
					parark = 1;
				if(campo[k][j] < 10 && campo[k][j] > 0)
					parark = 1;
			}

			parark = 0;
			if(j == 0)
				pararc = 1;
			if(campo[i][j] > 0 && campo[i][j] < 10)
				pararc = 1;
		}

		parark = 0;
		pararc = 0;
		if(i == tammaximo-1)
			pararl = 1;
		if(campo[i+1][colunai] > 0 && campo[i+1][colunai] != 10)
			pararl = 1;
	}

	pararl = 0;
	pararc = 0;
	parark = 0;
	//Para cima e direita
	for(i=linhai; pararl == 0; i--){

		for(j=colunai; pararc == 0; j++){

			for(k=i; parark == 0; k--){
				if(campo[k][j] >= 10){
					campo[k][j] -= 10;
					(*numcasas)++;
          (*pontuacao)++;
				}
				if(k == 0)
					parark = 1;
				if(campo[k][j] < 10 && campo[k][j] > 0)
					parark = 1;
			}

			parark = 0;
			if(j == tammaximo-1)
				pararc = 1;
			if(campo[i][j] > 0 && campo[i][j] < 10)
				pararc = 1;
		}

		parark = 0;
		pararc = 0;
		if(i == 0)
			pararl = 1;
		if(campo[i-1][colunai] > 0 && campo[i-1][colunai] != 10)
			pararl = 1;
	}

	pararl = 0;
	pararc = 0;
	parark = 0;
	//Para cima e direita
	for(i=linhai; pararl == 0; i--){

		for(j=colunai; pararc == 0; j--){

			for(k=i; parark == 0; k--){
				if(campo[k][j] >= 10){
					campo[k][j] -= 10;
					(*numcasas)++;
          (*pontuacao)++;
				}
				if(k == 0)
					parark = 1;
				if(campo[k][j] < 10 && campo[k][j] > 0)
					parark = 1;
			}

			parark = 0;
			if(j == 0)
				pararc = 1;
			if(campo[i][j] > 0 && campo[i][j] < 10)
				pararc = 1;
		}

		parark = 0;
		pararc = 0;
		if(i == 0)
			pararl = 1;
		if(campo[i-1][colunai] > 0 && campo[i-1][colunai] != 10)
			pararl = 1;
	}
}*/


void novoabrirzero(int campo[][15], int tammaximo, int linha, int coluna, int *numerocasas, int *pontuacao){

//Pré-funcionalidades. Primeiro e óbvio ele vai abrir a casa que ele está atualmente, e com isso aumenta o número de casas abertas e a pontuação do jogador. Depois disso ele printa o campo esperando um tempo em segundos apenas para visualização do que está ocorrendo, mas não é necessário (para melhor visualização use 0.5 ou 0.4)
campo[linha][coluna] -= 10;
(*numerocasas)++;
(*pontuacao)++;
printcampo(campo, tammaximo);
//printf("\n%d\n%d\n", *numerocasas, *pontuacao); //PARA DEBUG
system("sleep 0.3"); //Função para dar um delay no console, em segundos. (porém essa funciona se colocar décimo de segundo, ao contrário da função sleep() da biblioteca unistd.h)

//Aqui é possível perceber a validação dos dados antes de ir para qualquer lado.
//Para o efetivo funcionamento da função é assim: se a casa ao lado é um 10, ele pula para aquela casa e refaz toda a função, se não for 10, mas estiver fechada, ele abre a casa sem entrar na função novamente e aumenta as outras variáveis (numcasas e pontuacao), se estiver entre 0 e 9 não acontece nada, é ignorado.
//Como a função é recursiva, ele vai abrir a casa até a beira do tabuleiro depois verificar o próximo lado da casa anterior até a beira novamente; daí vai para a casa anterior e olha o próximo lado, e faz isso até que as casas estejam rodeadas pelos limites (a beira do tabuleiro ou um número entre 0 e 9).
//Infelizmente é necessário fazer um switch para cada vez que abrir uma casa diferente de 0 para que a pontuação seja consistente, deixando o código bem mais longo (poderia ser feito em uma função separada?)

if(coluna != 0){
if(campo[linha][coluna-1] == 10){ //Esquerda
	novoabrirzero(campo, tammaximo, linha, coluna-1, numerocasas, pontuacao);
}
else{
	if(campo[linha][coluna-1] > 10){
		campo[linha][coluna-1] -= 10;
		(*numerocasas)++;
		switch(campo[linha][coluna-1]){
			case 1:
				(*pontuacao) += 2;
				break;
			case 2:
				(*pontuacao) += 3;
				break;
			case 3:
				(*pontuacao) += 4;
				break;
		}
		//Para abrir a "diagonal interna", se abrir uma casa à esquerda e a casa de cima for um número diferente de 0, ele abre a diagonal cima-esquerda da casa inicial e depois a baixo-esquerda
		if(linha != 0 && coluna != 0){ //Não pode estar no canto
			if(campo[linha-1][coluna] != 0 && campo[linha-1][coluna] != 10){ //Se o elemento de cima for um número != 0
				if(campo[linha-1][coluna-1] > 10){ //Se a diagonal for um número > 0 escondido,
					campo[linha-1][coluna-1] -= 10; //Abre ele e aumenta a pontuação
					(*numerocasas)++;
					switch(campo[linha-1][coluna-1]){
						case 1:
							(*pontuacao) += 2;
							break;
						case 2:
							(*pontuacao) += 3;
							break;
						case 3:
							(*pontuacao) += 4;
							break;
					}
				}
				else //Se não for um número escondido, e sim um 0 escondido, passa a função para ele
					if(campo[linha-1][coluna-1] == 10)
						novoabrirzero(campo, tammaximo, linha-1, coluna-1, numerocasas, pontuacao);
			}
		}
		//Faz o mesmo para baixo-esquerda
		if(linha != tammaximo-1 && coluna != 0){
			if(campo[linha+1][coluna] != 0 && campo[linha+1][coluna] != 10){
				if(campo[linha+1][coluna-1] > 10){
					campo[linha+1][coluna-1] -= 10;
					(*numerocasas)++;
					switch(campo[linha+1][coluna-1]){
						case 1:
							(*pontuacao) += 2;
							break;
						case 2:
							(*pontuacao) += 3;
							break;
						case 3:
							(*pontuacao) += 4;
							break;
					}
				}
				else
					if(campo[linha+1][coluna-1] == 10)
						novoabrirzero(campo, tammaximo, linha+1, coluna-1, numerocasas, pontuacao);
			}
		}
	}
}
/*
Esse é o motivo pelo qual nessa função o maior número que se pode encontrar é 3. 0 é 0 mesmo, n é um número diferente de 0, x é o número que estamos interessados e b é uma possível bomba.
Perceba que n *nunca* vai ser uma bomba, portanto, o maior número que x pode assumir é 3.
n n n b
0 0 x b
n n n b
*/
}


if(coluna != tammaximo-1){
if(campo[linha][coluna+1] == 10){ //Direita
	novoabrirzero(campo, tammaximo, linha, coluna+1, numerocasas, pontuacao);
}
else{
	if(campo[linha][coluna+1] > 10){
		campo[linha][coluna+1] -= 10;
		(*numerocasas)++;
		switch(campo[linha][coluna+1]){
			case 1:
				(*pontuacao) += 2;
				break;
			case 2:
				(*pontuacao) += 3;
				break;
			case 3:
				(*pontuacao) += 4;
				break;
		}
		//Agora, para abrir as diagonais internas da cima-direita e baixo-direita.
		if(linha != 0 && coluna != tammaximo-1){ //Não pode estar no canto
			if(campo[linha-1][coluna] != 0 && campo[linha-1][coluna] != 10){ //Se o elemento de cima for um número != 0
				if(campo[linha-1][coluna+1] > 10){ //Se a diagonal for um número > 0 escondido,
					campo[linha-1][coluna+1] -= 10; //Abre ele e aumenta a pontuação
					(*numerocasas)++;
					switch(campo[linha-1][coluna+1]){
						case 1:
							(*pontuacao) += 2;
							break;
						case 2:
							(*pontuacao) += 3;
							break;
						case 3:
							(*pontuacao) += 4;
							break;
					}
				}
				else //Se não for um número escondido, e sim um 0 escondido, passa a função para ele
					if(campo[linha-1][coluna+1] == 10)
						novoabrirzero(campo, tammaximo, linha-1, coluna+1, numerocasas, pontuacao);
			}
		}
		//Faz o mesmo para baixo-esquerda
		if(linha != tammaximo-1 && coluna != tammaximo-1){
			if(campo[linha+1][coluna] != 0 && campo[linha+1][coluna] != 10){
				if(campo[linha+1][coluna+1] > 10){
					campo[linha+1][coluna+1] -= 10;
					(*numerocasas)++;
					switch(campo[linha+1][coluna+1]){
						case 1:
							(*pontuacao) += 2;
							break;
						case 2:
							(*pontuacao) += 3;
							break;
						case 3:
							(*pontuacao) += 4;
							break;
					}
				}
				else
					if(campo[linha+1][coluna+1] == 10)
						novoabrirzero(campo, tammaximo, linha+1, coluna+1, numerocasas, pontuacao);
			}
		}
	}
}
}


if(linha != 0){
if(campo[linha-1][coluna] == 10){ //Cima
	novoabrirzero(campo, tammaximo, linha-1, coluna, numerocasas, pontuacao);
}
else{
	if(campo[linha-1][coluna] > 10){
		campo[linha-1][coluna] -= 10;
		(*numerocasas)++;
		switch(campo[linha-1][coluna]){
			case 1:
				(*pontuacao) += 2;
				break;
			case 2:
				(*pontuacao) += 3;
				break;
			case 3:
				(*pontuacao) += 4;
				break;
		}
	}
}
}


if(linha != tammaximo-1){
if(campo[linha+1][coluna] == 10){ //Baixo
	novoabrirzero(campo, tammaximo, linha+1, coluna, numerocasas, pontuacao);
}
else{
	if(campo[linha+1][coluna] > 10){
		campo[linha+1][coluna] -= 10;
		(*numerocasas)++;
		switch(campo[linha+1][coluna]){
			case 1:
				(*pontuacao) += 2;
				break;
			case 2:
				(*pontuacao) += 3;
				break;
			case 3:
				(*pontuacao) += 4;
				break;
		}
	}
}
}
return;
}