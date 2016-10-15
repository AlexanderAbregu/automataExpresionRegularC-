#include <iostream>
#include <cstdlib>

// Para isdigit: http://www.cplusplus.com/reference/cctype/
#include <cctype>

using namespace std;

/* 
 * Se utiliza enum class porque al ser mas "fuertemente tipado", se evitaran posibles errores,
 * Mas informacion: http://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum
*/
	enum class Estado { INICIANDO, Q1, Q2, ENTERO, REAL, NOSIRVE };
	
	Estado reconocerElNumero ( const string& stringEntrada );
	
int main () {
	cout << "Automata reconoce numeros enteros y reales" << endl;
	
	string stringEntrada;
	cin >> stringEntrada;
	
	Estado ultimoEstado = reconocerElNumero( stringEntrada );
	
	if ( ultimoEstado == Estado::ENTERO ){
		cout << "Ingresaste un entero" << endl;
	} else if ( ultimoEstado == Estado::REAL ){
		cout << "Ingresaste un nº con coma " << endl;
	} else {
		cout << "No funciona e.e " << endl;
	}
	
	cout << endl;
	system("pause");
	system("cls");
	
	int salir = 0;
	
	cout << "Desea salir? \n 0 - SI \n 1 a 9 - NO" << endl;
	cin >> salir;
	
	if( salir ){
		main();
	} else {
		cout << "Adios!" << endl;
	}
	
	return 0;
}

Estado reconocerElNumero( const string& stringEntrada ){
	unsigned int posicion = 0;
	
	Estado actual = Estado::INICIANDO;
	
	bool stringRechazado = false;
	while( !stringRechazado && ( posicion < stringEntrada.length() ) ){
		char caracterActual = stringEntrada[posicion];
		
		switch ( actual ) {
			case Estado::INICIANDO:
				if( isdigit( caracterActual ) ){
					// Si es un digito cambio el estado del automata a ENTERO
					actual = Estado::ENTERO;
				} else if ( caracterActual == '+' || caracterActual == '-' ){
					// Si empieza el numero con + o - 
					actual = Estado::Q1;
				} else if ( caracterActual == '.' ) {
					// Si empieza el numero con un " . " significa que es un decimal
					actual = Estado::Q2;
				} else {
					// Si pone un caracter diferente a un numero o "+" o "-" o "."
					stringRechazado = true;
				}
				break;
			case Estado::Q1:
				if( isdigit( caracterActual ) ){
					// Si es un digito cambio el estado del automata a ENTERO
					actual = Estado::ENTERO;
				} else if ( caracterActual == '.' ) {
					// Si empieza el numero con un " . " significa que es un decimal
					actual = Estado::Q2;
				} else {
					// Si pone un caracter diferente a un numero "."
					stringRechazado = true;
				}
				break;
			case Estado::Q2:
				if( isdigit( caracterActual ) ){
					// Si es un digito cambio el estado del automata a ENTERO
					actual = Estado::REAL;
				} else {
					// Si pone un caracter diferente a un numero o un " . "
					stringRechazado = true;
				}
				break;
			case Estado::ENTERO:
				if( isdigit( caracterActual ) ){
					// Si es un digito cambio el estado del automata a ENTERO
					actual = Estado::ENTERO;
				} else if ( caracterActual == '.' ) {
					// Si empieza el numero con un " . " significa que es un decimal
					actual = Estado::Q2;
				} else {
					// Si pone un caracter diferente a un numero o "."
					stringRechazado = true;
				}
				break;
			case Estado::REAL:
				if( isdigit( caracterActual ) ){
					// Si es un digito cambio el estado del automata a REAL
					actual = Estado::REAL;
				} else {
					// Si pone un caracter diferente a un numero 
					stringRechazado = true;
				}
				break; 
		}
		// Evitamos el loop infinito XD
		posicion++;
	}
	
	if ( stringRechazado ) {
		return Estado::NOSIRVE;
	} else {
		return actual;
	}
}