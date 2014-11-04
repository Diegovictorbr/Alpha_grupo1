//---------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

//#include "Cifrador.h"
#include "Decifrador.h"
#include "Alpha.h"

#define DIREITA 0 
#define ESQUERDA 1

#define _8BIT 0
#define _64BIT 1

/*static unsigned int RCon[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000,
                                0x10000000, 0x20000000, 0x40000000, 0x80000000,
                                0x1b000000, 0x36000000}; //See Section 5.2 & 4.2
*/
//const int  Nr = 10;
//---------------------------------------------------------------------------


using namespace std;

 Decifrador::Decifrador(int numIteracoes, bool erase)
{
  Nr = numIteracoes;
  apagarOriginal = erase;
}

void Decifrador::setIterations(int n){
  Nr = n;
}
//---------------------------------------------------------------------------

void  Decifrador::decifrar(const char *senha, const char* confirmationWord, const char* inputFile, const char *outputFile, int mode, int size)
{
FILE *fr,*fw;
char *nomeEntrada, *nomeSaida;
register int i,j;//,Nr;
unsigned char msg[16],car;
unsigned char L_anterior[8],R_anterior[8],L[8],R[8],temporario[8];
unsigned char K[16];
unsigned char s[8];
unsigned char XK[12][16];   //chave extendida

//VERIFICA TAMANHO DA CHAVE
if(strlen(senha)<16){
	cout << "Tamanho da chave deve ser de 16 caracteres! Erro!";
    return;
}

//VERIFICA SE AS CHAVES CONFEREM
if (strcmp(senha,confirmationWord)!=0){
	cout << "Confirmacao da chave nao confere! Erro!";
    return;
}

//ALOCA MEMORIA PARA NOMEENTRADA
nomeEntrada=(char*)malloc(strlen(inputFile)+10);

//COPIA NOME ARQUIVO ENTRADA EM NOMEENTRADA
for (i=0;i<(int)strlen(inputFile);i++)nomeEntrada[i]=inputFile[i];
nomeEntrada[i]='\0';

//ARQUIVO COM A MENSAGEM ORIGINAL
fr=fopen(nomeEntrada,"rb");
if (!fr)
{
	cout << "Erro no arquivo de entrada! Erro!";
    free(nomeEntrada);
    return;
}

//Pegar a extensão do arquivo original
char extensao[256];
for(int k=0;k<256;k++){
	extensao[k]=fgetc(fr);
}

//ALOCA MEMORIA PARA NOMESAIDA
nomeSaida=(char*)malloc(strlen(outputFile)+10);

for (i=0;i<(int)strlen(outputFile);i++)nomeSaida[i]=outputFile[i];
nomeSaida[i]='\0';

if(!strcmp(nomeSaida,"Selecione o diretorio clicando no botao ao lado")){
	cout << "Selecione o diretorio do arquivo de saida! Erro!";
    free(nomeEntrada);
    free(nomeSaida);
    fclose(fr);
    return;
}

strcat(nomeSaida,extensao);
//VERIFICA EXISTENCIA DO ARQUIVO
//if(access(nomeSaida,00)==0){
if(file_exists(nomeSaida)){
	//f(Application->MessageBox("Arquivo de saida ja existe!\nDeseja substitui-lo?","Erro!",MB_YESNO|MB_ICONQUESTION)==IDNO){
    cout << "Arquivo de saida ja existe! Sera sobreescrito" << endl;
    /*free(nomeEntrada);
    free(nomeSaida);
    fclose(fr);
    return;*/
    //}
}

//ARQUIVO A SER DECRIPTOGRAFADO COM EXTENSAO .alpha
fw=fopen(nomeSaida,"wb");
if (!fw)
{
	cout << "Erro no arquivo de saida! Erro!";
    free(nomeEntrada);
    free(nomeSaida);
    fclose(fr);
    return;
}

cout << "Decifrando" << endl;


//Geracao das sub-chaves
for (int k=0;k<16;k++)K[k]=senha[k];

ExpandeChave(K,XK,Nr);

//frmStatus->pbStatus->Max=filelength(_fileno(fr));

car=fgetc(fr);
while(!feof(fr))
{
	//le os 16 caracteres
	for(i=0;i<16;i++){
			msg[i]=car;
      car=fgetc(fr);
	}

    //ALPHA
    //Inicializacao de L[0],R[0]
   	for (j=0;j<8;j++){
       	L_anterior[j] = msg[j];//L zero
       	R_anterior[j] = msg[j+8];//R zero
    }

    //Iteracoes do algoritmo Alpha
	for(i=0;i<Nr;i++){// versao com Nr iteracoes
        //calcula L[i]=R[i-1]^Ke[i-1]
     	for(j=0;j<8;j++){
           	L[j]=R_anterior[j]^XK[Nr-i-1][j];
        }

       	// atribui R(i-1) ao temporario ("estado")
    	for (j=0;j<8;j++){
       		temporario[j] = R_anterior[j];
       	}

       	//Decifracao, entao soma Ke ao temporario
       	for (j=0;j<8;j++){
       		temporario[j]=temporario[j]^XK[Nr-i-1][j];
       	}

	   	L_alpha2(temporario,s);

        for (j=0;j<8;j++){//chavei-a o vetor temporario para entrada na TNL
       		temporario[j]=(s[j]^XK[Nr-i-1][j+8]);//Kd[j]==K[j+8]
       	}

        //unsigned char baite[8];
       	unsigned char delta_linha[8];
        unsigned char baite;

        delta_linha [0] = temporario[7]>>4;

       	for (j=0;j<7;j++){
       		delta_linha[(j+1)] =temporario[j]>>4;
       	}

        for (j=0;j<8;j++){
		    baite = temporario[j];
			N_alpha (&baite, delta_linha[j]);
            temporario[j] = baite;
        }

        //calcula R[i]
   		for (j=0;j<8;j++){
       		R[j] = (L_anterior[j] ^ temporario[j]);
       		L_anterior[j]=L[j];
       		R_anterior[j]=R[j];
   		}
	}//fim i iteracoes Alpha


	for (j=0;j<8;j++){//faz cripto=R|L (trocado intencionalmente)
    	msg[j] = R[j];//
    	msg[j+8] = L[j];//
    }// fim do for j
    //fim ALPHA

    //escreve no arquivo de saida
    switch(size)
    {
      case _64BIT:
         write64bit(msg, fw, mode);
         break;
      default:
         write120bit(msg, fw);
         break;
    }
    //write128bit(msg, fw);

}//fim do while

fclose(fr);
fclose(fw);

if(apagarOriginal){
    remove(nomeEntrada);
}

free(nomeEntrada);
free(nomeSaida);

cout << "Decifragem concluida com exito!" << endl;

}

void Decifrador::write64bit(unsigned char* msg, FILE* fw, int modo){

  int i;
  switch(modo){
    case DIREITA: 
    for(i=0;i<8;i++){
    //if(!)
    fputc(msg[i],fw);
  }
    break;
    case ESQUERDA:
     for(i=8;i<16;i++){
    //if(!)
    fputc(msg[i],fw);
    }
    break;
  }
}

void Decifrador::write120bit(unsigned char* msg, FILE* fw){
  int i;
   for(i=1;i<16;i++){
    //if(!)
    fputc(msg[i],fw);
  }

}

void Decifrador::write128bit(unsigned char* msg, FILE* fw){
  int i;
   for(i=0;i<16;i++){
    //if(!)
    fputc(msg[i],fw);
  }

}
