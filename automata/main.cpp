#include <iostream>
// Se incluye para utilizar cin y cout: http://www.cplusplus.com/reference/iostream/
#include <cstdlib>
#include <cctype>
// Lo utiliza la funcion isdigit: http://www.cplusplus.com/reference/cctype/

using namespace std;

/* 
 * Se utiliza enum class porque al ser mas "fuertemente tipado", se evitaran posibles errores,
 * Mas informacion: http://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum
*/
	enum class EstadoAutomata { INICIO, NUMERO, MAYUSCULA, MINUSCULA, MAL };	
	EstadoAutomata probarContrasenna ( const string& stringEntrada);
	
int main () {
	cout << "Automata validador de contraseñas \n\n Ingrese la password: ";
	
	string stringEntrada;
	cin >> stringEntrada;
	
	EstadoAutomata ultimoEstado = probarContrasenna( stringEntrada );
	
	if ( ultimoEstado == EstadoAutomata::MINUSCULA ){
		cout << "Ingresaste una password valida" << endl;
	} else {
		cout << "No funciona e.e " << endl;
	}
	
	cout << endl;
	system("pause");
	system("cls");
	main();
	
	return 0;
}

/*
 *  La expresion regular en la que se basa el automata para funcionar es: /(([0-9]{1,})([A-Z]{1,})([a-z]{1,})){1,}/
 *  Fue testeada en la siguiente pagina: http://regexr.com/
 *  Funciono en los siguientes casos: 11AAa, 123ABCabc, 11AAaa, 111AAAaaa, 0Aa, 0Aa0Aa
 */
EstadoAutomata probarContrasenna ( const string& stringEngrada ){
	// Empezare leyendo desde el caracter 0 de la contraseña.
	 unsigned int posicionCaracter = 0;
	 
	 // Establezco el estado del automata como INICIO.
	 EstadoAutomata estadoActual = EstadoAutomata::INICIO;
	 
	 // Reviso caracter por caracter siempre que el automata no tenga el estado de "MAL" o hasta que lea todos los caracteres.
	 while( ( estadoActual != EstadoAutomata::MAL ) && ( posicionCaracter < stringEngrada.length() ) ){
		 // Establezco el caracter que estoy por leer.
		 char caracterActual = stringEngrada[posicionCaracter];
		 
		 // Por cada caracter voy a revisar el caracter y el estado del automata.
		 switch ( estadoActual ){
			case EstadoAutomata::INICIO:
				// Si el automata esta en estado "INICIO" y el primer caracter es un numero, entonces cambio el estado a numero. Cualquier otro caracter seria erroneo.
				if( isdigit ( caracterActual ) ){
					estadoActual = EstadoAutomata::NUMERO;
				} else {
					estadoActual = EstadoAutomata::MAL;
				}
				break;
			case EstadoAutomata::NUMERO:
				// El automata en estado "NUMERO" va a esperar un numero o una letra Mayuscula. Cualquier otro caracter seria erroneo.
				if ( isupper ( caracterActual ) ){
					estadoActual = EstadoAutomata::MAYUSCULA;
				} else if ( isdigit ( caracterActual ) ){
					estadoActual = EstadoAutomata::NUMERO;
				} else {
					estadoActual = EstadoAutomata::MAL;
				}
				break;
			case EstadoAutomata::MAYUSCULA:
				// El automata en estado "MAYUSCULA" va a esperar una letra Mayuscula o una letra minuscula. Cualquier otro caracter seria erroneo.
				if ( islower ( caracterActual ) ){
					estadoActual = EstadoAutomata::MINUSCULA;
				} else if ( isupper ( caracterActual ) ){
					estadoActual = EstadoAutomata::MAYUSCULA;
				} else {
					estadoActual = EstadoAutomata::MAL;
				}
				break;
			case EstadoAutomata::MINUSCULA:
				// El automata en estado "MINUSCULA" va a esperar una letra Minuscula o un numero. Cualquier otro caracter seria erroneo.
				if ( isdigit ( caracterActual ) ){
					estadoActual = EstadoAutomata::NUMERO;
				} else if ( islower ( caracterActual ) ){
					estadoActual = EstadoAutomata::MINUSCULA;
				} else {
					estadoActual = EstadoAutomata::MAL;
				}
				break;
		 }
		 // Vamos aumentando de posicion para leer el siguiente caracter de la contraseña
		posicionCaracter++;
	 }
	 
	 // Retornamos el estado actual del automata
	 return estadoActual;
}