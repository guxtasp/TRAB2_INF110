// INF110 - Trabalho pratico 2
//
// programa para ler, modificar e gravar uma imagem no formato PNM
//
// Autores: Andre Gustavo dos Santos			(criado em 16/06/14)
//          Andre Gustavo dos Santos			(modificado em 22/05/18)
//					Andre Gustavo dos Santos			(modificado em 13/09/21)
//					Andre Gustavo dos Santos			(modificado em 15/07/24)


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>


const int MAXALTURA  = 500;				//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 500;

using namespace std;

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA];	//a imagem propriamente dita //P2
	unsigned char imagemColorida[MAXALTURA][MAXLARGURA][3]; // P3
	unsigned char auxiliar[MAXALTURA][MAXLARGURA];       // Para imagens P2 //  // armazenar os pixels modificados, com as mesma dimensoes da imagem
	unsigned char auxiliarColorida[MAXALTURA][MAXLARGURA][3]; // Para imagens P3 //  // armazenar os pixels modificados, com as mesma dimensoes da imagem
	int largura, altura;						//dimensoes da imagem
	char tipo[4];										//tipo da imagem
	ifstream arqentrada;						//arquivo que contem a imagem original
	ofstream arqsaida;							//arquivo que contera a imagem modificada
	char comentario[200], c;				//auxiliares
	int i, j, valor;								//auxiliares

//*** LEITURA DA IMAGEM ***//
//esta parte le a imagem de um arquivo; voce pode deixar para olhar isso depois
//e iniciar a olhar o codigo a partir da linha 75 que de fato le os dados;
//a diferenca e' que le do arquivo (arqentrada) em vez de ler com cin

	// Boas-vindas ao usuário
	cout << "==================================================" << endl;
	cout << "Seja bem-vindo ao manipulador de imagens!\n\nDigite o nome do arquivo (Nao se esqueca da extensao .pnm): ";
	char nomeArquivo[100];  // Variavel para armazenamento do arquivo desejado
	cin >> nomeArquivo;  // Usuario digita o nome do arquivo

	//*** Abertura do arquivo ***//
	arqentrada.open(nomeArquivo,ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo: " << nomeArquivo << endl;
		return 0;
	}
//***************************//


//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();		//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario-
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
													//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le as dimensoes da imagem, numero de pixels da horizontal e da vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura > MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura > MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado, assumimos 255)
//****************************//


//*** Leitura dos pixels da imagem ***//
	if (strcmp(tipo, "P2") == 0) {
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++) {
				arqentrada >> valor;
				imagem[i][j] = (unsigned char)valor;
			}
	}

	else if (strcmp(tipo, "P3") == 0) {
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++)
			for(int k=0; k<3; k++){
				arqentrada >> valor;
				imagemColorida[i][j][k] = (unsigned char)valor;
			}
	}
//************************************//

	arqentrada.close();  //Fecha arquivo apos a leitura

//*** FIM DA LEITURA DA IMAGEM ***//


//*** TRATAMENTO DA IMAGEM ***//
//inicialmente sera nesta parte do codigo que voce vai trabalhar
	int opcao; //  Variavel para armazenar a opcao
	cout << endl;
	cout << "Arquivo encontrado! Vamos la?\nO que deseja fazer?\n";
	cout << "1 - Escurecer\n";
	cout << "2 - Clarear\n";
	cout << "3 - Negativar\n";
	cout << "4 - Espelhar\n";
	cout << "5 - Filtro de Prewitt\n";
	cout << "6 - Desfocar\n";
	cout << "7 - Tons de cinza\n";
	cout << "8 - Pixelizar\n";
	cout << endl;
	cout << "Digite a opcao desejada: ";
	cin >> opcao; // Usuário digita a opcao


	if (opcao == 1){
			//*** Escurece a imagem ***//
			int fator;
			cout << "Qual o fator de escurecimento (1-100)? ";
			cin >> fator;
			while (fator < 1 || fator > 100){
				cout << "Valor inválido. Certifique-se o fator esteja dentro limite \n Por favor, digite um número entre 1 e 100: " << endl;
				cin >> fator;
			}
			if (strcmp(tipo, "P2") == 0) {         // caso seja, tons de cinza
				for(i=0;i<altura;i++)                 // ACESSA A MATRIZ
					for(j=0;j<largura;j++){
						valor = (int)imagem[i][j];			//pega o valor do pixel
						valor -= fator;									//escurece o pixel
						if (valor < 0)									//se der negativo
							valor = 0;										//  deixa preto
						imagem[i][j] = (unsigned char)valor;	//modifica o pixel
					}
			}
				//*************************//
			else if (strcmp(tipo, "P3") == 0){  // caso seja, colorida
					for(i=0;i<altura;i++)
						for(j=0;j<largura;j++)
							for (int k=0; k < 3; k++){
								valor = (int)imagemColorida[i][j][k];			//pega o valor do pixel
								valor -= fator;									//escurece o pixel
								if (valor < 0)									//se der negativo
									valor = 0;										//  deixa preto (0)
								imagemColorida[i][j][k] = (unsigned char)valor;	//modifica o pixel
							}
					//*************************//
			}
	}
	else if (opcao == 2){
			int fator;
			cout << "Qual o fator de clareamento (1-100)? ";
			cin >> fator;
			while (fator < 1 || fator > 100){
				cout << "Valor inválido. Certifique-se o fator esteja dentro limite \n Por favor, digite um número entre 1 e 100: " << endl;
				cin >> fator;
			}
			//*** Clarea a imagem ***//
			if (strcmp(tipo, "P2") == 0) {
			for(i=0;i<altura;i++)
				for(j=0;j<largura;j++) {
					valor = (int)imagem[i][j];			//pega o valor do pixel
					valor += fator;									//clarea o pixel com o fator
					if (valor > 255)									//se der maior que 255
						valor = 255;										//  deixa branco
					imagem[i][j] = (unsigned char)valor;	//modifica o pixel
				}
			//*************************//
			}
			else if (strcmp(tipo, "P3") == 0) {
					for(i=0;i<altura;i++)
						for(j=0;j<largura;j++)
							for (int k=0; k < 3; k++){
								valor = (int)imagemColorida[i][j][k];			//pega o valor do pixel
								valor += fator;									//clarea o pixel
								if (valor > 255)									//se der maior que 255
									valor = 255;										//  deixa branco
								imagemColorida[i][j][k] = (unsigned char)valor;	//modifica o pixel
						}
					//*************************//
			}
}

	else if (opcao == 3){
			//*** Negativa a imagem ***//
			if (strcmp(tipo, "P2") == 0) {
			for(i=0;i<altura;i++)
				for(j=0;j<largura;j++) {
					valor = (int)imagem[i][j];			//pega o valor do pixel
					int negativo = 255 - valor;         // a variavl negativo se baseia em uma inversao simetrica (0 -> 255; 255 -> 0; 128 -> 127...)
					valor = negativo;					// atribui o valor da variavel negativo para a valor
					imagem[i][j] = (unsigned char)valor;	//modifica o pixel
				}
			//*************************//
			}


			else if (strcmp(tipo, "P3") == 0) {
			for(i=0;i<altura;i++)
				for(j=0;j<largura;j++) {
					for(int k=0; k<3; k++){
					valor = (int)imagemColorida[i][j][k];			//pega o valor do pixel
					int negativo = 255 - valor;         // a variavl negativo se baseia em uma inversao simetrica (0 -> 255; 255 -> 0; 128 -> 127...)
					valor = negativo;					// atribui o valor da variavel negativo para a valor
					imagemColorida[i][j][k] = (unsigned char)valor;	//modifica o pixel
				}
			//*************************//
			}
		}
	}

	else if(opcao == 4){
			//*** espelha a imagem ***//
			if (strcmp(tipo, "P2") == 0) {
				for(i=0;i<altura;i++)
					for(j=0;j<largura;j++) {
						auxiliar[i][j] = imagem [altura - 1 - i][j]; // atribui a ultima linha da matriz principal para a primeira desta matriz auxiliar
					}



				for(i=0;i<altura;i++)
					for(j=0;j<largura;j++) {
						imagem[i][j] = auxiliar[i][j]; // atribui as linhas da matriz auxiliar
					}
			//*************************//
			}

			else if (strcmp(tipo, "P3") == 0) {
				for(i=0;i<altura;i++)
					for(j=0;j<largura;j++)
						for(int k=0; k<3; k++){
						auxiliarColorida[i][j][k] = imagemColorida[altura - 1 - i][j][k]; // atribui a ultima linha da matriz principal para a primeira desta matriz auxiliar
					}



				for(i=0;i<altura;i++)
					for(j=0;j<largura;j++)
						for(int k = 0; k < 3; k++){
						imagemColorida[i][j][k] = auxiliarColorida[i][j][k]; // atribui as linhas da matriz auxiliar
					}
			//*************************//
			}
		}

	else if(opcao == 5){
			//*** aplicar filtro de prewitt na imagem ***//
			if (strcmp(tipo, "P2") == 0) {

				for(i=1;i<altura-1;i++)  // (-1 e 1) para nao acessar os pixels que ficam na borda    (TIRA LINHA 0 E A ULTIMA)
					for(j=1;j<largura-1;j++) { // (-1) para nao acessar os pixels que ficam na borda   (TIRA COLUNA 0 E A ULTIMA)
						int somagx = 0;  // irá gerar cada for, pois é resultado de um soma "ponderada" do pixel e seus vizinhos
						int somagy = 0;
						somagx =
							imagem[i-1][j-1]*1 + imagem[i-1][j]*0 + imagem[i-1][j+1]*(-1) +
							imagem[i][j-1]*1 + imagem[i][j]*0     + imagem[i][j+1]*(-1) +   // calcula os vizinhos no gx
							imagem[i+1][j-1]*1 + imagem[i+1][j]*0 + imagem[i+1][j+1]*(-1);

						somagy =
								imagem[i-1][j-1] * 1 + imagem[i-1][j] * 1 + imagem[i-1][j+1] * 1 +
								imagem[i  ][j-1] * 0 + imagem[i  ][j] * 0 + imagem[i  ][j+1] * 0 +              // calcula os vizinhos no gy
								imagem[i+1][j-1] * (-1) + imagem[i+1][j] * (-1) + imagem[i+1][j+1] * (-1);

						int magnitude =  sqrt(((somagx)*(somagx))+((somagy)*(somagy))); // int pra nao haver numero como ponto flutuante para nao dar problema no char
						if(magnitude > 255){  // caso magnitude > 255, atribui = 255
							magnitude = 255;
						}
						if(magnitude < 0)
							magnitude = 0;
						auxiliar[i][j] = (unsigned char) magnitude;
					}


					// pega as bordas da original para a auxiliar -> para depois passar todos os pixel para a modificada final E NAO FICAR 0
						for(int i = 0; i < altura; i++) {
							auxiliar[i][0] = imagem[i][0];              // [1ª]COLUNA 0- EXCLUIDA
							auxiliar[i][largura - 1] = imagem[i][largura - 1];  // ULTIMA COLUNA DA LINHA I
						}
						for(int j = 0; j < largura; j++) {
							auxiliar[0][j] = imagem[0][j];               // [1ª] LINHA 0 - EXCLUIDA
							auxiliar[altura - 1][j] = imagem[altura - 1][j];    // ULTIMA LINHA DA COLUNA
						}
						for(i=0;i<altura;i++)
							for(j=0;j<largura;j++) {
								imagem[i][j] = auxiliar[i][j]; // atribui as linhas da matriz auxiliar
							}
					}


			else if (strcmp(tipo, "P3") == 0) {

				for(i=1;i<altura-1;i++)  // (-1 e 1) para nao acessar os pixels que ficam na borda    (TIRA LINHA 0 E A ULTIMA)
					for(j=1;j<largura-1;j++) // (-1) para nao acessar os pixels que ficam na borda   (TIRA COLUNA 0 E A ULTIMA)
						for(int k = 0; k < 3; k++){
						int somagx = 0;  // irá gerar cada for, pois é resultado de um soma "ponderada" do pixel e seus vizinhos
						int somagy = 0;
						somagx =
							imagemColorida[i-1][j-1][k]*1 + imagemColorida[i-1][j][k]*0 + imagemColorida[i-1][j+1][k]*(-1) +
							imagemColorida[i][j-1][k]*1 + imagemColorida[i][j][k]*0     + imagemColorida[i][j+1][k]*(-1) +   // calcula os vizinhos no gx
							imagemColorida[i+1][j-1][k]*1 + imagemColorida[i+1][j][k]*0 + imagemColorida[i+1][j+1][k]*(-1);

						somagy =
								imagemColorida[i-1][j-1][k] * 1 + imagemColorida[i-1][j][k] * 1 + imagemColorida[i-1][j+1][k] * 1 +
								imagemColorida[i  ][j-1][k] * 0 + imagemColorida[i  ][j][k] * 0 + imagemColorida[i  ][j+1][k] * 0 +              // calcula os vizinhos no gy
								imagemColorida[i+1][j-1][k] * (-1) + imagemColorida[i+1][j][k] * (-1) + imagemColorida[i+1][j+1][k] * (-1);

						int magnitude =  sqrt(((somagx)*(somagx))+((somagy)*(somagy))); // int pra nao haver numero como ponto flutuante para nao dar problema no char
						if(magnitude > 255){  // caso magnitude > 250, atribui = 250
							magnitude = 255;
						}
						if(magnitude < 0)
							magnitude = 0;

						auxiliarColorida[i][j][k] = (unsigned char) magnitude;
					}


					// pega as bordas da original para a auxiliar -> para depois passar todos os pixel para a modificada final E NAO FICAR 0
						for(int i = 0; i < altura; i++)
							for(int k = 0; k < 3; k++){
								auxiliarColorida[i][0][k] = imagemColorida[i][0][k];              // [1ª]COLUNA 0- EXCLUIDA
								auxiliarColorida[i][largura - 1][k] = imagemColorida[i][largura - 1][k];  // ULTIMA COLUNA DA LINHA I
						}
						for(int j = 0; j < largura; j++)
							for(int k = 0; k < 3; k++){
								auxiliarColorida[0][j][k] = imagemColorida[0][j][k];               // [1ª] LINHA 0 - EXCLUIDA
								auxiliarColorida[altura - 1][j][k] = imagemColorida[altura - 1][j][k];    // ULTIMA LINHA DA COLUNA
						}
						for(i=0;i<altura;i++)
							for(j=0;j<largura;j++)
								for(int k = 0; k < 3; k++){
									imagemColorida[i][j][k] = auxiliarColorida[i][j][k]; // atribui as linhas da matriz auxiliar
								}
							}
				}
	else if(opcao == 6){
			//*** desfoque gaussiana na imagem ***//
			if (strcmp(tipo, "P2") == 0) {
				int somapeso = 16; // soma dos pesoas para a desfoque gaussiana
				for(i=1;i<altura-1;i++)  // (-1 e 1) para nao acessar os pixels que ficam na borda    (TIRA LINHA 0 E A ULTIMA)
					for(j=1;j<largura-1;j++) { // (-1) para nao acessar os pixels que ficam na borda   (TIRA COLUNA 0 E A ULTIMA)
						int soma = 0;
						soma=
							imagem[i-1][j-1]*1+ imagem[i-1][j]*2+ imagem[i-1][j+1]*1+
							imagem[i][j-1]*2 + imagem[i][j]*4    + imagem[i][j+1]*2 +   // soma os vizinhos
							imagem[i+1][j-1]*1 + imagem[i+1][j]*2+ imagem[i+1][j+1]*1;
						int media = soma / somapeso;

						if(media > 255){  // caso media > 250, atribui = 250
							media = 255;
						}
						auxiliar[i][j] = (unsigned char) media;
					}


					// pega as bordas da original para a auxiliar -> para depois passar todos os pixel para a modificada final E NAO FICAR 0
						for(int i = 0; i < altura; i++) {
							auxiliar[i][0] = imagem[i][0];              // [1ª]COLUNA 0- EXCLUIDA
							auxiliar[i][largura - 1] = imagem[i][largura - 1];  // ULTIMA COLUNA DA LINHA I
						}
						for(int j = 0; j < largura; j++) {
							auxiliar[0][j] = imagem[0][j];               // [1ª] LINHA 0 - EXCLUIDA
							auxiliar[altura - 1][j] = imagem[altura - 1][j];    // ULTIMA LINHA DA COLUNA
						}
						for(i=0;i<altura;i++)
							for(j=0;j<largura;j++) {
								imagem[i][j] = auxiliar[i][j]; // atribui as linhas da matriz auxiliar
							}
						}

						else if (strcmp(tipo, "P3") == 0) {
							int somapeso = 16; // soma dos pesoas para a desfoque gaussiana
							for(i=1;i<altura-1;i++)  // (-1 e 1) para nao acessar os pixels que ficam na borda    (TIRA LINHA 0 E A ULTIMA)
								for(j=1;j<largura-1;j++)
									for(int k = 0; k<3; k++){ // (-1) para nao acessar os pixels que ficam na borda   (TIRA COLUNA 0 E A ULTIMA)
									int soma = 0;
									soma=
										imagemColorida[i-1][j-1][k]*1+ imagemColorida[i-1][j][k]*2+ imagemColorida[i-1][j+1][k]*1+
										imagemColorida[i][j-1][k]*2 + imagemColorida[i][j][k]*4    + imagemColorida[i][j+1][k]*2 +   // soma os vizinhos
										imagemColorida[i+1][j-1][k]*1 + imagemColorida[i+1][j][k]*2+ imagemColorida[i+1][j+1][k]*1;
									int media = soma / somapeso;

									if(media > 255){  // caso media > 250, atribui = 250
										media = 255;
									}
									auxiliarColorida[i][j][k] = (unsigned char) media;
								}


								// pega as bordas da original para a auxiliar -> para depois passar todos os pixel para a modificada final E NAO FICAR 0
									for(int i = 0; i < altura; i++)
										for(int k = 0; k<3; k++){
										auxiliarColorida[i][0][k] = imagemColorida[i][0][k];              // [1ª]COLUNA 0- EXCLUIDA
										auxiliarColorida[i][largura - 1][k] = imagemColorida[i][largura - 1][k];  // ULTIMA COLUNA DA LINHA I
									}
									for(int j = 0; j < largura; j++)
										for(int k = 0; k<3; k++){
											auxiliarColorida[0][j][k] = imagemColorida[0][j][k];               // [1ª] LINHA 0 - EXCLUIDA
											auxiliarColorida[altura - 1][j][k] = imagemColorida[altura - 1][j][k];    // ULTIMA LINHA DA COLUNA
									}
									for(i=0;i<altura;i++)
										for(j=0;j<largura;j++)
											for(int k = 0; k<3; k++){
											imagemColorida[i][j][k] = auxiliarColorida[i][j][k]; // atribui as linhas da matriz auxiliar
										}
									}
					}

		else if(opcao == 7){
			if (strcmp(tipo, "P3") == 0) { // verifica se a imagem é do tipo 3, ou seja, se é colorida
				// aplica a conversao da escala rgb para cinza em cada pixel
				for(i=0;i<altura;i++)
					for(j=0;j<largura;j++){
								unsigned char red = imagemColorida[i][j][0];  // obtem os componentes do rgb do pixel atual para seguir o calculo de cinza
								unsigned char green = imagemColorida[i][j][1];
								unsigned char blue = imagemColorida[i][j][2];

								int gray = (int)(0.29*red + 0.59*green + 0.11*blue); // calcula a escala  cinza com os valores do rgb

								// garante que o valor da escala seja dentro do intervalo [0,255]
								if(gray > 255)
									gray = 255;
								if(gray < 0)
									gray = 0;

								imagemColorida[i][j][0] = (unsigned char) gray;  // atribui o valor cinza para cada indice respectivo do rgb
								imagemColorida[i][j][1] = (unsigned char) gray;	// mantendo o formato p3
								imagemColorida[i][j][2] = (unsigned char) gray;
							}
			}
			// caso a imagem não seja colorida, exibe mensagem e encerra a execução do programa
			else{
				cout << "Infelizmente essa funcionalidade apenas se aplica a imagens coloridas";
				return 0;
			}

		}


		else if(opcao == 8){
			//*** pixelizar imagem ***//
			// a pixelização reduz os detalhes da imagem substituindo blocos (ex: 4x4 pixels) pela média de cor desses blocos, trazendo o aspecto de borrado.
			int bloco;
			cout << "Digite o tamanho do bloco para pixelizar (ex: 4): ";
			cin >> bloco; // armazena  o tamanho do bloco, aplicando-se tanto a altura, quanto a largura, com um bloco baseado em [N X N]
			// Valida enquanto o valor for invalido
			while(bloco <= 0 || bloco > altura || bloco >largura){
				cout << "Tamanho invalido! Certifique-se o tamanho seja menor que a altura e a largura \n";
				cout << "Por favor, digite um valor valido: ";
				cin >> bloco;
			}

			if (strcmp(tipo, "P2") == 0) {

				for(i=0; i<altura;i+=bloco){ 			// criar os blocos e percorer ele em altura em altura do bloco, no qual a 1ª iteracao sera (0,0) (4,0)..., de tal maneeira que forma bloco na vertical
						for(j=0;j<largura;j+=bloco) {  // da mesma maneira, (0,0)(0,4)... (4,0)(4,4).... de tal maneeira que forma bloco na horizontal

							int somaPixel = 0; // acumulador de soma do pixels
							int quantPixel = 0; // somador de pixels para media

							// soma dos pixels
							for(int x=i; x < i + bloco && x < altura; x++){  // ira percorer cada pixel dentro do bloco atual, evitando passar
							// ultrapaasr o limite da imagem, ex: vai que é uma imagem impar, e fique apenas um elemento, para nao passar do limite
								for(int y=j; y < j + bloco && y < largura; y++){
										somaPixel+= (int) imagem[x][y]; // pega os valores de cada pixel
										quantPixel++; // somador para media de pixel , importante para casos que o bloco nao seja N x N, ou seja, um quadrado, exemplo:2x2, 2x1
									}
								}
									int media = somaPixel / quantPixel;
									if (media > 255) // para caso a media se a media utrapasar 250, fique = 250
										media = 255;

								for(int x=i; x < i + bloco && x < altura; x++){
									for(int y=j; y < j + bloco && y < largura; y++){
										auxiliar[x][y] = (unsigned char) media;   // passando a media para os pixels do bloco
									}
								}
							}
						}

							for(i=0;i<altura;i++)
							for(j=0;j<largura;j++) {
								imagem[i][j] = auxiliar[i][j]; // atribui as linhas da matriz auxiliar para principal
							}
						}

						else if (strcmp(tipo, "P3") == 0) {

							for(i=0; i<altura;i+=bloco){ 			// criar os blocos e percorer ele em altura em altura do bloco, no qual a 1ª iteracao sera (0,0) (4,0)..., de tal maneeira que forma bloco na vertical
									for(j=0;j<largura;j+=bloco) {  // da mesma maneira, (0,0)(0,4)... (4,0)(4,4).... de tal maneeira que forma bloco na horizontal

										int somaPixel[3] = {0,0,0}; // acumulador para somar os valores de cada canal de cor (R, G, B)
											// por se tratar de uma imagem colorida (matriz tridimensional), cada pixel possui três valores: vermelho, verde e azul
											// inic o vetor com zero para garantir que não haja lixo de memória e que as somas comecem corretamente
										int quantPixel = 0;

										// soma dos pixels
										for(int x=i; x < i + bloco && x < altura; x++){  // ira percorer cada pixel dentro do bloco atual, evitando passar
										// ultrapaasr o limite da imagem, ex: vai que é uma imagem impar, e fique apenas um elemento, para nao passar do limite
											for(int y=j; y < j + bloco && y < largura; y++){
													for(int k = 0; k<3; k++){
															somaPixel[k]+= (int) imagemColorida[x][y][k]; // pega os valores de cada pixel
														}
													quantPixel++; // somador para caso que o bloco nao seja 4x4, exemplo 2x2, 2x1
											}
										}

												int media[3];
												for(int k=0; k<3; k++){
													media[k] = somaPixel[k]/quantPixel;
													if (media[k] > 255) // para caso a media se a media utrapasar 250, fique = 255
														media[k] = 255;
													if (media[k] < 0)
														media[k] =0;
												}
												for(int x=i; x < i + bloco && x < altura; x++){
													for(int y=j; y < j + bloco && y < largura; y++){
														for(int k=0; k<3; k++){
													auxiliarColorida[x][y][k] = (unsigned char) media[k];   // passando a media para os pixels do bloco
												}
											}
										}
									}
								}

										for(i=0;i<altura;i++){
										for(j=0;j<largura;j++){
										for(int k=0; k<3; k++) {
											imagemColorida[i][j][k] = auxiliarColorida[i][j][k]; // atribui as linhas da matriz auxiliar para principal
										}
									}
								}
							}
						}
	cout <<endl;
	cout << "==================================================" << endl;
	cout << "==================PROCESSANDO...==================" << endl;
	cout << "==================================================" << endl;
	cout <<endl;

//*** FIM DO TRATAMENTO DA IMAGEM ***//


//*** GRAVACAO DA IMAGEM ***//
//esta parte grava a imagem em um arquivo; voce pode deixar para entender isso depois
//a diferenca e' que escreve no arquivo (arqsaida) em vez de escrever com cout

	//*** Grava a nova imagem ***//


	cout << "Processada com sucesso! Vamos gravar? \nDigite o nome do novo arquivo modificado (Nao se esqueca da extensao .pnm): ";
	char nomeArquivoFinal[100];  // Variavel para armazenamento do nome do arquivo modificado
	cin >> nomeArquivoFinal;  // Usuario digita o nome do arquivo

	arqsaida.open(nomeArquivoFinal,ios::out);	//Cria um arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar "<< nomeArquivoFinal << "\n";
		return 0;
	}

	arqsaida << tipo << endl;							//tipo
	arqsaida << "# TP2-INF110, by GSP\n";	//comentario
	arqsaida << largura << " " << altura <<endl;	//dimensoes
	arqsaida << " " << 255 << endl;				//maior valor
	if(strcmp(tipo, "P2") == 0){  // tons de cinza
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++)
				arqsaida << (int)imagem[i][j] << endl;	//pixels
	}
	else if (strcmp(tipo, "P3") == 0){
		for(i=0;i<altura;i++){
			for(j=0;j<largura;j++){
				arqsaida << (int)imagemColorida[i][j][0] << endl;	//pixels R
				arqsaida << (int)imagemColorida[i][j][1] << endl;	//pixels G
				arqsaida << (int)imagemColorida[i][j][2] << endl;	//pixels B
			}
		}
	}

	arqsaida.close();		//fecha o arquivo
	//***************************//

	cout <<endl;
	cout << "==================================================" << endl;
	cout << "=============Imagem salva com sucesso!============"<<endl;
	cout << "==================================================" << endl;

//*** FIM DA GRAVACAO DA IMAGEM ***//

	return 0;
}
