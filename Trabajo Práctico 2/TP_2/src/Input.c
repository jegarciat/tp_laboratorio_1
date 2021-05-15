
#include "Input.h"

int utn_getEntero(char mensaje[], char mensajeError[], int minimo, int maximo)
{
	int numero;

	printf("%s", mensaje);
	scanf("%d", &numero);

	while(numero < minimo || numero > maximo)
	{
		printf("%s", mensajeError);
		scanf("%d", &numero);
	}
	return numero;
}

float utn_getFloat(char mensaje[], char mensajeError[], float minimo, float maximo)
{
	float numero;

	printf("%s", mensaje);
	scanf("%f", &numero);

	while(numero < minimo || numero > maximo)
	{
		printf("%s", mensajeError);
		scanf("%f", &numero);
	}
	return numero;
}

char utn_getChar(char mensaje[])
{
	char letra;

	printf("%s", mensaje);
	fflush(stdin);
	scanf("%c", &letra);

	return letra;
}

void utn_getString(char mensaje[], char input[])
{
    printf("%s",mensaje);
    fflush(stdin);
    gets(input);
}


int getInt(char mensaje[])
{
    int numero;
    printf("%s", mensaje);
    scanf("%d",&numero);
    return numero;
}

char Confirmar(char confirmarMensaje[])
{
    char confirmar;

    do
    {
		printf("%s", confirmarMensaje);
		fflush(stdin);
		scanf("%c", &confirmar);
		confirmar = tolower(confirmar);

    } while (confirmar != 's' && confirmar != 'n');

    return confirmar;
}
