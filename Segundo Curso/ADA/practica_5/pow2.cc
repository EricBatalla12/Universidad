#include <iostream>
#include <cmath>
using namespace std;

unsigned long pasos = 0;

unsigned long pow2_1(unsigned);
unsigned long pow2_2(unsigned);
unsigned long pow2_3(unsigned);

// coste : \Theta (n). Depende directamente del valor de n
unsigned long pow2_1(unsigned num)
{
	unsigned long result = 1;
	
	for (int i = 0; i < num; i++)
	{
		pasos++;
		result = result * 2;
	}
	return result;
}
// coste : \Theta (log n). El tama�o del problema se va dividiendo entre 2S
unsigned long pow2_2(unsigned num)
{
	//Caso base
	if (num == 0) return 1;
	unsigned long divide = pow2_2(num / 2);
	//Si es par se multiplica normal 8/2 --> 4/2 ...
	if (num % 2 == 0)
	{
		pasos++;
		return divide * divide;
	}
	else //Si es impar hay que multiplicarlo x2, 7/2 --> 3 (se pierde 1) 3/2 --> 1.
	{
		pasos++;
		return 2 * divide * divide;
	}
}
//coste: \Theta(n^2). Se hacen el cuadrado de pasos respecto al tama�o del problema
unsigned long pow2_3(unsigned num)
{
	unsigned long result = 1;
	for (int i = 0; i < num; i++)
	{
		unsigned long iterador = result; //Esto permite 2^n, antes he probado sin esto y ser�a n^2, con ambos bucles llegando hasta < num.
		for (int j = 0; j < iterador; j++)
		{
			pasos++;
			result++;
		}
	}
	return result;
}

int main()
{
	//Tabla
	printf("i\tesperado\tpow2_1\tpow2_2\tpow2_3\n");
	
	for (unsigned i = 0; i < 20; i++)
	{
		unsigned long pasos1, pasos2, pasos3;
		unsigned long res1, res2, res3;

		unsigned esperado = pow(2, i);

		//Pasos pow2_1()
		pasos = 0; 
		res1 = pow2_1(i);
		pasos1 = pasos;

		if (res1 != esperado)
		{
			printf("NO SE HA OBTENIDO EL RESULTADO ESPERADO, SALIENDO DEL PROGRAMA");
			break;
		}
			

		//Pasos pow2_2()
		pasos = 0;
		res2 = pow2_2(i);
		pasos2 = pasos;

		if (res2 != esperado)
		{
			printf("NO SE HA OBTENIDO EL RESULTADO ESPERADO, SALIENDO DEL PROGRAMA");
			break;
		}

		//Pasos pow2_3()
		pasos = 0;
		res3 = pow2_3(i);
		pasos3 = pasos;

		if (res3 != esperado)
		{
			printf("NO SE HA OBTENIDO EL RESULTADO ESPERADO, SALIENDO DEL PROGRAMA");
			break;
		}

		printf("%u\t%u\t\t%lu\t%lu\t%lu\n", i, esperado, pasos1, pasos2, pasos3);
	}


}