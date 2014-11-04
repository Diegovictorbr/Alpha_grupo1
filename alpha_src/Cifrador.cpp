//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "Alpha.h"
#include "Cifrador.h"
#include "Aleatorizacao.h"

#define DIREITA 0 
#define ESQUERDA 1

#define _8BIT 0
#define _64BIT 1


//---------------------------------------------------------------------------

using namespace std;

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 Cifrador::Cifrador(int numIteracoes, bool erase)
{
  Nr = numIteracoes;
  apagarOriginal = erase;
  gerardorAleatorio = new Aleatorizacao();
}

void Cifrador::setIterations(int n){
  Nr = n;
}

//---------------------------------------------------------------------------
void  Cifrador::cifrar( const char* senha, const char* confirmationWord, const char* inputFile, const char* outputFile, int mode, int size)
{
FILE *fr,*fw;
//char* nomeEntrada,*nomeSaida;
register int i,j;//,Nr;
unsigned char* msg, *msgWithoutRandom, car;
unsigned char L_anterior[8],R_anterior[8],L[8],R[8],temporario[8];
unsigned char K[16];
unsigned char s[8];
unsigned char XK[12][16];   //chave extendida



//VERIFICA TAMANHO DA CHAVE
if(strlen(senha)<16){
	cout << "Tamanho da chave deve ser de 16 caracteres! Erro!" << endl;
    return;
}


//VERIFICA SE AS CHAVES CONFEREM
if (strcmp(senha,confirmationWord)!=0){
	cout << "Confirmacao da chave nao confere! Erro!" << endl;
    return;
}



//ARQUIVO COM A MENSAGEM ORIGINAL
fr=fopen(inputFile,"rb");
if (!fr)
{
	cout << "Erro no arquivo de entrada! Erro!";
  return;
}

// -- Ate aqui, so abriu o arquivo de entrada

//Pegar a extensão do arquivo original
char *extensao;
extensao = strrchr(inputFile, '.'); //pega indice do ultimo ponto
if (!extensao) {
    cout << "Erro ao pegar extensao do arquivo!!!" << endl;
}else{
  //extensao = extensao + 1;
}



//VERIFICA EXISTENCIA DO ARQUIVO
//if(access(nomeSaida,00)==0){
if(file_exists(outputFile)){
    cout << "Arquivo de saida ja existe! Sera sobreescrito" << endl;
    //fclose(fr);
    //return;
    //}
}
//ARQUIVO A SER CRIPTOGRAFADO COM EXTENSAO .alpha
fw=fopen(outputFile,"wb");
if (!fw)
{
	cout << "Erro no arquivo de saida! Erro!" << endl;
    fclose(fr);
    return;
}

//Escreve a extensão do arquivo original em fw
for(int k=0;k<256;k++){
	fputc(extensao[k],fw);
}

cout << "Cifrando..." <<endl;

//GERAÇÃO DAS SUBCHAVES
for (register int k=0;k<16;k++) 
  K[k]=senha[k];

ExpandeChave(K,XK,Nr);


//frmStatus->pbStatus->Max=filelength(_fileno(fr));
while(!feof(fr))
{
  

    //Lê os 16 caracteres
  //  msg = new unsigned char[16];
	  //msg = read128bit(fr);

    //Lê 15 caracteres
    /**/

    //Le 8 caracteres

    switch(size)
    {
      case _64BIT:
      msgWithoutRandom = new unsigned char[8];
      msgWithoutRandom = read64bit(fr);

      msg  = new unsigned char[16];
      msg = gerardorAleatorio->inserirAleatorizacao(msgWithoutRandom, mode, _64BIT); //LINHA DO PROBLEMA*/
      break;

      default:
      msgWithoutRandom =  new unsigned char[15];
      msgWithoutRandom = read120bit(fr);

      msg =  new unsigned char[16];
      msg = gerardorAleatorio->inserirAleatorizacao(msgWithoutRandom, ESQUERDA, _8BIT);
      break;
    }

    
    

    //ALPHA
    //Inicialização de L[0],R[0]
    for (j=0;j<8;j++){
       	L_anterior[j] = msg[j];//L zero
       	R_anterior[j] = msg[j+8];//R zero
    }

    //Iterações do algoritmo Alpha
	for(i=0;i<Nr;i++){//Loop com Nr iterações

        //CÁLCULO DE L[i]
        //Calcula L[i]=R[i-1]^Ke[i-1]


        for(j=0;j<8;j++){
           L[j]=R_anterior[j]^XK[i][j];//K[j]=Ke[j]
        }

        //CÁLCULO DE R[i]
        //Atribui R_anterior ao temporário
    	for (j=0;j<8;j++){
        	temporario[j] = R_anterior[j];
        }

       	L_alpha2(temporario,s);

		for (j=0;j<8;j++){// chavei-a o vetor temporario para entrada na TNL
       		temporario[j]=(s[j]^XK[i][j+8]);//Kd[j]==K[j+8]
       	}
      
       // unsigned char baite[8];
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
    for(i=0;i<16;i++){
	  	fputc(msg[i],fw);
    }
    delete[] msgWithoutRandom;
    delete[] msg;
//frmStatus->pbStatus->StepIt();
}//fim do while
fclose(fr);
fclose(fw);
//lbCifrando->Visible=false;

if(apagarOriginal){
    remove(inputFile);
}

cout << "Cifragem concluida com exito!" <<endl;

} //fim do metodo Cifrar


bool validateKey(char* senha, char* confirmationWord){
  //VERIFICA TAMANHO DA CHAVE
  if(strlen(senha)<16){
    cout << "Tamanho da chave deve ser de 16 caracteres! Erro!" << endl;
    return false;
  }

  //VERIFICA SE AS CHAVES CONFEREM
  if (strcmp(senha,confirmationWord)!=0){
    cout << "Confirmacao da chave nao confere! Erro!" << endl;
    return false;
  }

  return true;
}

bool validateFile(){

  return true;
}

unsigned char* Cifrador::read64bit(FILE *fr){

int i;
unsigned char* msg,car;

msg= new unsigned char[8];

  for(i=0;i<8;i++) msg[i]=' ';

  for(i=0;i<8;i++){
    if(!feof(fr)){
      car=fgetc(fr);
        msg[i]=car;
        
        }
      else {
        msg[i-1]=' '; 
        break;
      }
    }

    return msg;

}

unsigned char* Cifrador::read128bit(FILE *fr){

  int i;
  unsigned char* msg,car;
 
  msg= new unsigned char[16];
  
  for(i=0;i<16;i++) msg[i]=' ';

  for(i=0;i<16;i++){
    if(!feof(fr)){
      
                car=fgetc(fr);
                  msg[i]=car;
        
      } 
      else {
        msg[i-1]=' '; 
        break;
      }
        
    }

    return msg;

}

unsigned char* Cifrador::read120bit(FILE *fr){

  int i;
  unsigned char* msg,car;
  
  msg= new unsigned char[15];
  
  for(i=0;i<15;i++) msg[i]=' ';

  for(i=0;i<15;i++){
    if(!feof(fr)){
        car=fgetc(fr);
        msg[i]=car;
        }
    else {
        msg[i-1]=' '; 
        break;
        
    }
  }

    return msg;

}

 Cifrador::~Cifrador()
{
  delete gerardorAleatorio;
}

//---------------------------------------------------------------------------
