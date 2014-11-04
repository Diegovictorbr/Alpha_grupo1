#include <iostream> 
#include "Aleatorizacao.h"

#define CONGRUENCIA 1

#define _8BIT 0
#define _64BIT 1

#define DIREITA 0 
#define ESQUERDA 1
//teste2
 

 using namespace std;

Aleatorizacao::Aleatorizacao(){
	primeiro = 1;
	

}

unsigned char* Aleatorizacao::inserirAleatorizacao(unsigned char* msg, int modo, int size){

	unsigned char* mensagem = NULL;
	unsigned char* msgAleatoria = NULL;

	msgAleatoria = gerarMensagemAleatoria(size); //ok

	switch(modo){

		case DIREITA: mensagem = merge(msg, msgAleatoria, size);
		break;
		case ESQUERDA: mensagem = merge(msgAleatoria, msg, size);
		break;
		default:
		cout << "Caiu no Default" << endl;
	}

	delete[] msgAleatoria;

	return mensagem;
}

unsigned char* Aleatorizacao::merge(unsigned char* msgEsquerda, unsigned char* msgDireita, int size){

	int i;
	unsigned char* mensagem = new unsigned char[16];
	for(i=0;i<16;i++) mensagem[i]=' ';
	switch(size){

		case _64BIT:
		for(i=0; i<8; i++){
			mensagem[i] = msgEsquerda[i];
			mensagem[i+8] = msgDireita[i];
		}
		break;
		case _8BIT: 
		mensagem[0]= *msgEsquerda;
	//	printf("%c",mensagem[0] );
		for(i=1; i<16; i++){
			mensagem[i] = msgDireita[i-1];
			//printf("%c",mensagem[i] );
		}
		//printf("\n");
		break;
		default:
		cout << "Caiu no Default" << endl;
	}
	return mensagem;
}


unsigned char* Aleatorizacao::gerarMensagemAleatoria(int size){


		long long int* msg = NULL;
		int* msg8bit = NULL;// = new long long int(64);
		unsigned char* msgAleatoria = NULL; //= new unsigned char[8];

		
		gerarNumeroPseudoAleatorio(CONGRUENCIA);

		switch(size){

			case _64BIT:
				//printf("%lld\n", ultimoNumeroGerado);
			msg = converterInteiroPara64Bit(ultimoNumeroGerado);
			//print64Bit(msg64Bit);
			msgAleatoria = converter64BitParaUnsignedChar(msg);
			//printMensagem(msgAleatoria);
			
			break;
			case _8BIT:
			//printf("%lld\n", ultimoNumeroGerado);
			msg8bit = converterInteiroPara8Bit(ultimoNumeroGerado);
			//print8Bit(msg8bit);
			msgAleatoria = converter8BitParaUnsignedChar(msg8bit);
			//printMensagem8bit(msgAleatoria);
			
			break;
			default:
			cout << "Caiu no Default" << endl;

		}

		
		return msgAleatoria;

}

void Aleatorizacao::gerarNumeroPseudoAleatorio(int modo){

	switch(modo){
		case CONGRUENCIA: congruenciaLinear(3247, 10000 , 21, 11);
		break;
	}

}


//Gera sequencia de numeros pseudo-aleatorios utilizando o metodo de congurencia linear
void Aleatorizacao::congruenciaLinear(int s, int m, int a, int c){

	if(primeiro == 1) {
		primeiro = 0;
		ultimoNumeroGerado = (a*s + c)%m;
	}else 
		ultimoNumeroGerado = (a*ultimoNumeroGerado +c)%m;


}




long long int* Aleatorizacao::converterInteiroPara64Bit(long long int numero){

	long long int* inteiro64Bit= new long long int[64];
	long long int i;

	for(i=0; i<64; i++){

		long long int shiftRight =  numero >> i;
    	inteiro64Bit[i] = shiftRight & 1;

	}
	return inteiro64Bit;

}

 unsigned char* Aleatorizacao::converter64BitParaUnsignedChar(long long int* inteiro64Bit){

	unsigned char* msgAleatoria = new unsigned char[8];

	int i;

	for(i=0; i<8; i++){

		msgAleatoria[i] = 	inteiro64Bit[i + 7] << 7 |
                  		  	inteiro64Bit[i + 6] << 6 |
                 		  	inteiro64Bit[i + 5] << 5 |
                  			inteiro64Bit[i + 4] << 4 |
                  			inteiro64Bit[i + 3] << 3 |
                  			inteiro64Bit[i + 2] << 2 |
                  			inteiro64Bit[i + 1] << 1 |
                  				inteiro64Bit[i] << 0;

         //printf("caracter %d: %c\n", i, msgAleatoria[i]);
	}

	return msgAleatoria;

}

int* Aleatorizacao::converterInteiroPara8Bit(int numero){

	int* inteiro8Bit= new int[8];
	int i;

	for(i=0; i<8; i++){

		int shiftRight =  numero >> i;
    	inteiro8Bit[i] = shiftRight & 1;

	}
	return inteiro8Bit;

}

 unsigned char* Aleatorizacao::converter8BitParaUnsignedChar(int* inteiro8Bit){

	unsigned char* msgAleatoria;

	

		*msgAleatoria = 	inteiro8Bit[7] << 7 |
                  		  	inteiro8Bit[6] << 6 |
                 		  	inteiro8Bit[5] << 5 |
                  			inteiro8Bit[4] << 4 |
                  			inteiro8Bit[3] << 3 |
                  			inteiro8Bit[2] << 2 |
                  			inteiro8Bit[1] << 1 |
                  				inteiro8Bit[0] << 0;

         //printf("caracter %d: %c\n", i, msgAleatoria[i]);

	return msgAleatoria;

}



void Aleatorizacao::print64Bit(long long int* msg){

	int i;

	for (i = 63; i>=0; i--)
			printf("%lld",  msg[i]); 

	printf("\n"); 


}


void Aleatorizacao::print8Bit( int* msg){

	int i;

	for (i = 7; i>=0; i--)
			printf("%d",  msg[i]); 

	printf("\n"); 


}

void Aleatorizacao::printMensagem(unsigned char* msg){

	int i;

	for (i = 8; i>=0; i--)
			printf("%c",  msg[i]); 

	printf("\n"); 
}

void Aleatorizacao::printMensagem8bit(unsigned char* msg){

				printf("%s",  msg); 

	printf("\n"); 
}

