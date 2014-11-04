
#include <iostream>

#include "Cifrador.h"
#include "Decifrador.h"

using namespace std;

int main(int argc, char **argv)
{
	if(argc < 5)
	{
		std::cout << "Numero de parametros errado!!!" << std::endl;
		return -1;
	}

	Cifrador cif;
	Decifrador decif;

	cif.cifrar(argv[1], argv[2], argv[3], argv[4], 0, 0);

	std::cout << "Vamo que vamo, hein!" << std::endl;

	decif.decifrar(argv[1], argv[2], argv[4], "ninja", 0, 0);

	return 0;
}