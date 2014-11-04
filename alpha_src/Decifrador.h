//---------------------------------------------------------------------------
#ifndef DecifrarH
#define DecifrarH
//---------------------------------------------------------------------------
#include "Utils.h"
//---------------------------------------------------------------------------

class Decifrador
{
private:
	int Nr; //numero de iteracoes
	bool apagarOriginal;
	void write64bit(unsigned char* msg, FILE* fw, int modo);
	void write120bit(unsigned char* msg, FILE* fw);
	void write128bit(unsigned char* msg, FILE* fw);

public:		// User declarations
	Decifrador(int numIteracoes = ITER_10, bool erase = false);
	void  decifrar(const char *senha, const char* confirmationWord, const char* inputFile, const char *outputFile, int mode, int size);
	void setIterations(int n);
};
//---------------------------------------------------------------------------
//extern Decifrador *frmDecifrar;
//---------------------------------------------------------------------------
#endif
