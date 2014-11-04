#ifndef AleatorizacaoH
#define AleatorizacaoH

class Aleatorizacao{

	
	public:
	 Aleatorizacao();

	long long int ultimoNumeroGerado;
	int primeiro;
	
	/*Chama um método de geracão de aleatórios passando os paramentros necessarios*/
	unsigned char* gerarMensagemAleatoria(int size);
	
	/*Junta a sequencia aleatoria e a mensagem*/
	unsigned char* inserirAleatorizacao(unsigned char* msg, int modo, int size);

	unsigned char* merge(unsigned char* msgEsquerda, unsigned char* msgDireita, int size);

	

	void gerarNumeroPseudoAleatorio(int modo);

    /* Para gerar uma sequencia de numeros aleatorios pelo metodo de congruencia linear é
    necessário definir a semente(s), o módulo (m), o multiplicador(a) e o incremento(c). */
	void congruenciaLinear(int s, int m, int a, int c);


	/*converte numero inteiro para vetor int com este numero inteiro em bits*/
	long long int* converterInteiroPara64Bit(long long int numero);

	unsigned char* converter64BitParaUnsignedChar(long long int* inteiro64Bit);

	int* converterInteiroPara8Bit(int numero);

	unsigned char* converter8BitParaUnsignedChar(int* inteiro8Bit);


	void print64Bit(long long int* msg);

	void print8Bit( int* msg);

	void printMensagem(unsigned char* msg);
	void printMensagem8bit(unsigned char* msg);

};

#endif