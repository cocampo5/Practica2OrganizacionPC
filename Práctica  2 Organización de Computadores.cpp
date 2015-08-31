#include "stdafx.h"

int suma(){
	__asm{

	};
}
int main(int argc, char* argv[])
{
	int elect;
	cout << "Hola, ingrese su selección" << endl; //Son 13 opciones 
	cout << "";
	cin >> elect;
	switch (elect)
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '10':
		case '11':
		case '12':
		case '13':
		default:
			break;
	}
	return 0;
}

