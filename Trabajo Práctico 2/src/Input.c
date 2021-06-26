#include "Input.h"

/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en string.
 *        un máximo de ' longitud - 1' caracteres .
 * \param string Puntero al espacio de memoria donde se copiara el string obtenido.
 * \param limite Es el tamaño del string.
 * \return [0] En caso de exito, si se obtuvo un string - [-1] en caso de error.
 *
 */
static int utn_myGets(char* cadena, int limite);

/**
 * \brief Verifica si la cadena recibida es solo letras
 * \param cadena Puntero al string a ser analizado
 * \return [1] Si es solo letras y espácios - [0] Si no lo es
* 		  [-1] Si hubo un error en los parámetros
 */
static int utn_SoloLetras(char* cadena);

/**
 * \brief Verifica si la cadena ingresada es numérica
 * \param cadena Puntero a la cadena a ser analizada
 * \return [1] Si es número - [0] Si no lo es
 * 		  [-1] Si hubo un error en los parámetros
 */

static int utn_esNumerico(char* cadena, int limite);

/**
 * \brief Verifica si la cadena ingresada es numerica y la convierte en una variable tipo int
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return [0] Si se obtiene un numero entero - [-1] En caso de error
 *
 */
static int getInt(int* pResultado);

/**
 * \brief Verifica si la cadena ingresada es un flotante
 * \param cadena Puntero a la cadena a ser analizada
 * \return [1] Si es un flotante - [0] Si no lo es
 * 		  [-1] Si hubo un error en los parámetros
 */

static int utn_esFloat(char* cadena, int limite);

/**
 * \brief Verifica si la cadena ingresada es flotante y la convierte en un variable tipo float.
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return [0] Si se obtiene un flotante - [-1] En caso de error
 *
 */
static int getFloat(float* pResultado);

// DESARROLLO DE LAS FUNCIONES

static int utn_myGets(char* cadena, int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(cadena != NULL && limite > 0)
	{
		fflush(stdin);
		if(fgets(bufferString, sizeof(bufferString), stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString, sizeof(bufferString))-1] == '\n')
			{
				(bufferString[strnlen(bufferString, sizeof(bufferString))-1] = '\0');
			}

			if(strnlen(bufferString, sizeof(bufferString)) <= limite)
			{
				strncpy(cadena, bufferString, limite);
				retorno = 0;
			}
		}
	}
	return retorno;
}

//FUNCIONES PARA OBTENER UN TEXTO DE SOLO LETRAS

static int utn_SoloLetras(char* cadena)
{
	int i;
	int retorno = -1;
	int longitud = strlen(cadena);

	if(cadena != NULL && longitud > 0)
	{
		retorno = TRUE;

		for(i = 0; i < longitud; i++)
		{
			if((cadena[i] != ' ') && (cadena[i] < 'a' || cadena[i] > 'z') && (cadena[i] < 'A' || cadena[i] > 'Z'))
			{
				retorno = FALSE; //No es solo letras
				break;
			}
		}
	}

	return retorno;
}

int utn_getString(char* input, char* mensaje, char* mensajeError, int longitud, int reintentos)
{
	int retorno = -1;
    char bufferString[4096];

    if(input != NULL && mensaje != NULL && mensajeError != NULL && longitud > 0 && reintentos >= 0)
    {
        do
        {
        	printf("%s", mensaje);

            if((utn_myGets(bufferString, longitud) == 0) && (utn_SoloLetras(bufferString) != FALSE) && bufferString[0] != ' ' && bufferString[0] != '\0')
            {
            	AcomodarString(bufferString);
                strncpy(input, bufferString, longitud);
                retorno = 0;
                break;
            }

            if(reintentos != 0)
            {
				printf("%s", mensajeError);
            }
			reintentos--;

        } while(reintentos >= 0);
    }

    return retorno;
}

int AcomodarString(char* cadena)
{
	int i;
	int retorno = -1;
	int longitud = strlen(cadena);

	if(cadena != NULL)
	{
		strlwr(cadena);
		cadena[0] = toupper(cadena[0]);

		for(i = 0; i < longitud; i++)
		{
			if(isspace(cadena[i]))
			{
				cadena[i + 1] = toupper(cadena[i + 1]);
				retorno = 0;
			}
		}
	}

	return retorno;
}

int Confirmar(char* respuesta, char* confirmarMensaje)
{
    char confirmar;
    int retorno = -1;

    if(respuesta != NULL && confirmarMensaje != NULL)
    {
		do
		{
			printf("%s", confirmarMensaje);
			fflush(stdin);
			scanf("%c", &confirmar);

			if(utn_SoloLetras(&confirmar) == 0)
			{
				confirmar = tolower(confirmar);
			}

		} while (confirmar != 's' && confirmar != 'n');

		retorno = 0;
    }

    *respuesta = confirmar;

    return retorno;
}

//FUNCIONES PARA OBTENER UN NUMERO ENTERO

static int utn_esNumerico(char* cadena, int limite)
{
	int retorno;
	int i;
	retorno = -1;

	if(cadena != NULL && limite > 0)
	{
		retorno = TRUE;

		for(i = 0; i < limite && cadena[i] != '\0'; i++)
		{
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}

			if(cadena[i] < '0' || cadena[i] > '9')
			{
				retorno = FALSE;
			}
		}
	}

	return retorno;
}

static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL && utn_myGets(buffer, sizeof(buffer)) == 0 && utn_esNumerico(buffer, sizeof(buffer)) == TRUE && buffer[0] != ' ')
	{
		*pResultado = atoi(buffer);
		retorno = 0;
	}

	return retorno;
}

int utn_getNumEntero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int bufferInt;
	int retorno;
	retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}

            if(reintentos != 0)
            {
				printf("%s", mensajeError);
            }
            reintentos--;

		} while(reintentos >= 0);
	}

	return retorno;
}

int utn_getNumEnteroV2(int* pResultado, char* mensaje, char* mensajeError, int minimo, int reintentos)
{
	int bufferInt;
	int retorno;
	retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt) == 0 && bufferInt >= minimo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}

			if(reintentos != 0)
			{
				printf("%s", mensajeError);
			}
			reintentos--;

		} while(reintentos >= 0);
	}

	return retorno;
}

//SIN REINTENTOS
int utn_getNumInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo)
{
	int bufferInt;
	int retorno;
	retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}

			printf("%s", mensajeError);

		} while(retorno == -1);
	}

	return retorno;
}

//SIN MAXIMO
int utn_getNumIntSM(int* pResultado, char* mensaje, char* mensajeError, int minimo)
{
	int bufferInt;
	int retorno;
	retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt) == 0 && bufferInt >= minimo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}

			printf("%s", mensajeError);

		} while(retorno == -1);
	}

	return retorno;
}

//FUNCIONES PARA OBTENER UN NÚMERO FLOAT

static int utn_esFloat(char* cadena, int limite)
{
	int retorno = -1;
	int contadorPuntos = 0;
	int i;

	if(cadena != NULL && limite > 0)
	{
		retorno = TRUE;

		for(i = 0; i < limite && cadena[i] != '\0'; i++)
		{
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}

			if(cadena[i] < '0' || cadena[i] > '9')
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = FALSE;
					break;
				}
			}
		}
	}

	return retorno;
}

static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL && utn_myGets(buffer, sizeof(buffer)) == 0 && utn_esFloat(buffer, sizeof(buffer)) == TRUE && buffer[0] != ' ')
	{
		*pResultado = atof(buffer);
		retorno = 0;
	}

	return retorno;
}

int utn_getFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	float bufferFloat;
	int retorno;
	retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(getFloat(&bufferFloat) == 0 && bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}

			if(reintentos != 0)
			{
				printf("%s", mensajeError);
			}
			reintentos--;

		} while(reintentos >= 0);
	}

	return retorno;
}

//FUNCIONES PARA OBTENER UN ALFANUMÉRICO

/**
 * \brief Verifica si el valor recibido contiene solo letras y números
 * \param str Array con la cadena a ser analizada
 * \return [1] Si son solo letras, espacios y números - [0] Si no lo son
 *        [-1] En caso de error en los parámetros
 *
 */

static int utn_esAlfaNumerico(char* str, int limite)
{
	int i;
	int retorno;
	retorno = -1;

	if(str != NULL && limite > 0)
	{
		retorno = TRUE;

		for(i = 0; i < limite && str[i] != '\0'; i++)
		{
			if((str[0] != ' ') && str[0] != '\n' && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') && (str[i] < '0' || str[i] > '9'))
			{
				retorno = FALSE;
				break;
			}
		}
	}

	return retorno;
}

int utn_getAlfaNumerico(char* input, char* mensaje, char* mensajeError, int longitud, int reintentos)
{
	int retorno = -1;
    char bufferString[4096];

    if(input != NULL && mensaje != NULL && mensajeError != NULL && longitud > 0 && reintentos >= 0)
    {
        do
        {
        	printf("%s", mensaje);

            if((utn_myGets(bufferString, longitud) == 0) && (utn_esAlfaNumerico(bufferString, sizeof(bufferString)) != FALSE))
            {
                strncpy(input, bufferString, longitud);
                retorno = 0;
                break;
            }

			if(reintentos != 0)
			{
				printf("%s", mensajeError);
			}
			reintentos--;

        } while(reintentos >= 0);
    }

    return retorno;
}

