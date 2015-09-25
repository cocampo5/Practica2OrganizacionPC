#include "stdafx.h"

/*
Para las operaciones básicas utilizamos conjunto de instrucciones SSE y
registros xmmm
*/

void suma(){ //Recibe floatantes de 32 bits
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
void resta(){ //Recibe flotantes de 32 bits
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
void multiplicacion(){ //Recibe flotantes de 32 bits
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
void division(){ //Recibe flotantes de 32 bits
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
/*
Trigonometricas
Todo se maneja con la FPU (Floating Point Unit)
FLD: Esto carga un 32 bits a st[0], puedo pasarle de 32,64,80 bits
FSIN/FCOS: Hace el seno/coseno del almacenado en st[0]
y lo almacena en el mismo st[0]. La tangente es explícita.
FST: Almacena en una variable el st[0]
*/
void seno(){
	float i,res;
	float constante = 0.0174532925f; //Para pasar de grados a radianes
	cout << "Ingrese angulo en grados : ";
	cin >> i;
	i = i*constante;//grados a radianes
	__asm{
		
		FLD [i] 
		FSIN 
		FST [res]
	}
	cout << "Su resultado es: " << res << endl;
}
void coseno(){
	float i, res;
	float constante = 0.0174532925f;
	cout << "Ingrese angulo en grados : ";
	cin >> i;
	i = i*constante;
	__asm{
		FLD[i]
		FCOS
		FST[res]
	}
	cout << "Su resultado es: " << res << endl;
}
void tangente(){
	float i, res;
	float constante = 0.0174532925f;
	cout << "Ingrese angulo en grados : ";
	cin >> i;
	i = i*constante;
	__asm{
		FLD[i] //Cargo angulo
		FSIN //saco el seno (queda en s(0))
		FLD[i] //Cargo denuevo el angulo (el seno queda en s(1))
		FCOS //Hago el seno (queda en s(0))
		FDIVP st(1), st(0) //Divido seno entre coseno y hago pop
		FST[res]//Almaceno el resultado
	}
	cout << "Su resultado es: " << res << endl;
}
void raiz(){
	float i, res;
	cout << "Ingrese un número mayor o igual a 0 : ";
	cin >> i;
	__asm{
		FLD[i] //Cargo número
		FSQRT //saco raiz cuadrada
		FST[res]//Almaceno el resultado
	}
	cout << "Su resultado es: " << res << endl;
}
void exponente(){
	float base,res;
	int exp;
	cout << "Ingrese la base: ";
	cin >> base;
	res = base;
	cout << "Ingrese el exponente: ";
	cin >> exp;
	__asm{
		MOV ECX, [exp]
		JMP cond
		iter :
			MOVSS xmm0, [res]
			MULSS xmm0, [base]
			MOVSS [res], xmm0
			DEC ECX
		cond :
			CMP ECX, 0
			JNE iter
	}
	cout << "Su resultado es: " << res << endl;
}
void exponente_log(){
	float base, res,exp;
	cout << "Ingrese la base: ";
	cin >> base;
	cout << "Ingrese el exponente: ";
	cin >> exp;
	__asm{
		FLD[exp] //Cargo mi base
		FLD[base] //Cargo mi exponente
		FYL2X //Computo	y*log2(x) x^y
		FLD st //Copia de y*log2(x) (y0)
		FRNDINT //Redondeo a un INT (y1)
		FSUB st(1),st //Dejo solo la parte decimal
		FXCH st(1) //Swap de posiciones
		F2XM1 //Computo y0-y1 (2^(parte_decimal))
		FLD1 //Cargo un 1
		FADD //Le sumo uno a 2^(parte_decimal)
		FSCALE //Reuno parte decimal y parte entera
		FSTP st(1) //Copio lo que me interesa y pop()
		FST[res] //Guardo en la variable a mostrar
	}
	//cout << base << exp << endl;
	cout << "Su resultado es: " << res << endl;
}
void log2(){
	float i, res;
	cout << "Ingrese el número: ";
	cin >> i;
	__asm{
		FLD1
		FLD[i]
		FYL2X
		FST[res]
	}
	cout << "Su resultado es: "<< res << endl;

}
void log10(){
	float i, res,aux;
	cout << "Ingrese el número: ";
	cin >> i;
	__asm{
		FLD1
		FLD[i]
		FYL2X
		FSTP[aux]
		FLD[aux]
		FLDL2T
		FDIVP ST(1), ST(0)
		FSTP[res]
	}
	cout << "Su resultado es: " << res << endl;
}
void ealax(){
	float res, i;
	float euler = 2.7182818284590452353602874713527f;
	cout << "Ingrese un numero: ";
	cin >> i;
	__asm{
		FLD[i] //Cargo mi exponente
		FLD[euler] //Cargo mi base
		FYL2X //Computo	y*log2(x) x^y
		FLD st //Copia de y*log2(x) (y0)
		FRNDINT //Redondeo a un INT (y1)
		FSUB st(1), st //Dejo solo la parte decimal
		FXCH st(1) //Swap de posiciones
		F2XM1 //Computo y0-y1 (2^(parte_decimal))
		FLD1 //Cargo un 1
		FADD //Le sumo uno a 2^(parte_decimal)
		FSCALE //Reuno parte decimal y parte entera
		FSTP st(1) //Copio lo que me interesa y pop()
		FST[res] //Guardo en la variable a mostrar
	}
	//cout << base << exp << endl;
	cout << "Su resultado es: " << res << endl;
}
int main(int argc, char* argv[])
{
	int elect;
	cout << "Hola, tiene 13 operaciones:\n1->Suma 2->Resta 3->Multipliacion 4->Division";
	cout << "\n5->Seno 6->Coseno 7->Tangente 8->Raiz Cuadrada 9->Exponenciacion\n";
	cout << "10->Logaritmo en base 2 11->Logaritmo en base 10 12->e^x\n";
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
			seno();
			break;
		case 6:
			coseno();
			break;
		case 7:
			tangente();
			break;
		case 8:
			raiz();
			break;
		case 9:
			exponente_log();
			break;
		case 10:
			log2();
			break;
		case 11:
			log10();
			break;
		case 12:
			ealax();
			break;
		case 13:
		default:
			cout << "Hiciste una muy mala elección" << endl;
			break;
	}
	system("pause");
	return 0;
}

