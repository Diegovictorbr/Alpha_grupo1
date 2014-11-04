//---------------------------------------------------------------------------
#ifndef CifrarH
#define CifrarH
//---------------------------------------------------------------------------
#include "Utils.h"
#include "Aleatorizacao.h"
//---------------------------------------------------------------------------

class Cifrador
{
private:
	int Nr; //numero de iteracoes
	bool apagarOriginal;
	Aleatorizacao* gerardorAleatorio;
	unsigned char* read64bit(FILE *fr);
	unsigned char* read128bit(FILE *fr);
	unsigned char* read120bit(FILE *fr);

public:		// User declarations
	 Cifrador(int numIteracoes = ITER_10, bool erase = false);
	 void  cifrar(const char* senha, const char* confirmationWord, const char* inputFile, const char* outputFile);
	 void setIterations(int n);
	 ~Cifrador();
};
//---------------------------------------------------------------------------
//extern Cifrador *frmCifrar;
//---------------------------------------------------------------------------
#endif
