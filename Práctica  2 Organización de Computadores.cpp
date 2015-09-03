#include "stdafx.h"

void suma(){
	float i, j,res;
	cout << "Ingrese el primer numero: ";
	cin >> i;
	cout << "Ingrese el segundo numero: ";
	cin >> j;
	__asm{
		MOVSS xmm0, [i]
		ADDSS xmm0,[j]
		MOVSS [res], xmm0
	};
	cout << "Su resultado es: " << res << endl;
}
void resta(){
	float i, j, res;
	cout << "Ingrese el primer numero: ";
	cin >> i;
	cout << "Ingrese el segundo numero: ";
	cin >> j;
	__asm{
		MOVSS xmm0, [i]
		SUBSS xmm0, [j]
		MOVSS[res], xmm0
	};
	cout << "Su resultado es: " << res << endl;
}
void multiplicacion(){
	float i, j, res;
	cout << "Ingrese el primer numero: ";
	cin >> i;
	cout << "Ingrese el segundo numero: ";
	cin >> j;
	__asm{
		MOVSS xmm0, [i]
		MULSS xmm0, [j]
		MOVSS[res], xmm0
	};
	cout << "Su resultado es: " << res << endl;
}
void division(){
	float i, j, res;
	cout << "Ingrese el primer numero: ";
	cin >> i;
	cout << "Ingrese el segundo numero: ";
	cin >> j;
	__asm{
		MOVSS xmm0, [i]
		DIVSS xmm0, [j]
		MOVSS[res], xmm0
	};
	cout << "Su resultado es: " << res << endl;
}
int main(int argc, char* argv[])
{
	int elect;
	cout << "Hola, tiene 13 operaciones:\n1->Suma 2->Resta 3->Multipliacion 4->Division\n";
	cout << "Ingrese su seleccion: "; //Son 13 opciones 
	cin >> elect;
	switch (elect)
	{
		case 1:
			suma();
			break;
		case 2:
			resta();
			break;
		case 3:
			multiplicacion();
			break;
		case 4:
			division();
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		default:
			cout << "Hiciste una muy mala elección" << endl;
			break;
	}
	system("pause");
	return 0;
}

