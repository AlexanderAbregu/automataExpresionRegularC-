#include <iostream> // Se incluye para utilizar cin y cout: http://www.cplusplus.com/reference/iostream/
#include <cstdlib>
#include <cctype> // Lo utiliza la funcion isdigit: http://www.cplusplus.com/reference/cctype/
#include<stdlib.h> // libreria para cambia color: http://www.taringa.net/post/ciencia-educacion/11030497/Cambiar-el-color-en-consola-de-c.html

using namespace std;

/* 
 * Se utiliza enum class porque al ser mas "fuertemente tipado", se evitaran posibles errores,
 * Mas informacion: http://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum
*/
	enum class EstadoAutomata { INICIO, NUMERO, MAYUSCULA, MINUSCULA, MAL };	
	EstadoAutomata probarContrasenna ( const string& stringEntrada);
	
	void mostrarAscii( const int cantidad, const int codigo );
	
int main () {
	system ("color 0F" );
	cout << " Automata validador de contrase" << char(164) << "as \n Con la siguiente expresion regular: /(([0-9]{1,})([A-Z]{1,})([a-z]{1,})){1,}/ \n\n\tIngrese la contrase" << char(164) << "a: ";
	
	// Almaceno la contraseña.
	string stringEntrada;
	cin >> stringEntrada;
	
	cout << endl << endl;
	
	// Almaceno el estado final de la contraseña en la variable "ultimoEstado".
	EstadoAutomata ultimoEstado = probarContrasenna( stringEntrada );
	
	cout << endl << endl;
	
	// Si el ultimo estado de "ultimoEstado" es MINUSCULA significa que la contraseña esta bien escrita, caso contrario hay un error.
	if ( ultimoEstado == EstadoAutomata::MINUSCULA ){
		system ("color 0A" );
		cout << "Ingresaste una contrase" << char(164) << "a valida" << endl;
	} else {
		system ("color 0C" );
		cout << "La contrase" << char(164) << "a es invalida" << endl;
	}
	
	cout << endl;
	// Ingrese un caracter
	system("pause");
	// Limpio la consola
	system("cls");
	// Vuelvo a llamar a la funcion main
	main();
	
	return 0;
}

/*
	Para mostrar una serie de caracteres ascii extendido.
	Lo usa para escribir 9 veces el "═", en lugar de poner char(205);char(205);char(205);char(205);char(205);char(205);char(205);char(205);char(205)
	Link de los ASCII http://www.elcodigoascii.com.ar/codigos-ascii-extendidos/lineas-doble-horizontales-recuadro-grafico-dos-lineas-codigo-ascii-205.html
*/	
	void mostrarAscii( const int cantidad, const int codigo ){
		for( int x = 0; x < cantidad; x++){
			cout << char( codigo );
		}
	}

/*
 * Para mosrtar el estado en pantalla y que quede alineada a la "tabla" 
 * */
	void mostrarEstado ( EstadoAutomata estado ){
		switch ( estado ){
			case EstadoAutomata::INICIO:
				cout << " INICIO  ";
				break;
			case EstadoAutomata::NUMERO:
				cout << " NUMERO  ";
				break;
			case EstadoAutomata::MAYUSCULA:
				cout << "MAYUSCULA";
				break;
			case EstadoAutomata::MINUSCULA:
				cout << "MINUSCULA";
				break;
			case EstadoAutomata::MAL:
				cout << "   MAL   ";
				break;
		}
	}

/*
 *  La expresion regular en la que se basa el automata para funcionar es: /(([0-9]{1,})([A-Z]{1,})([a-z]{1,})){1,}/
 *  Fue testeada en la siguiente pagina: http://regexr.com/
 *  Funciono en los siguientes casos: 11AAa, 123ABCabc, 11AAaa, 111AAAaaa, 0Aa, 0Aa0Aa
 */
	EstadoAutomata probarContrasenna ( const string& stringEngrada ){
		// Inicio dibujando tabla.
		cout << "\t" << char(201); mostrarAscii( 9, 205 ); cout << char(203); mostrarAscii( 9, 205 ); cout <<  char(203); mostrarAscii( 9, 205 ); cout << char(187) << endl;
		
		cout << "\t" << char(186) << " ESTADO  " << char(186) << " " << char(168) << "FINAL? " << char(186) <<"  LETRA  " << char(186)  << endl;
		
		cout << "\t" << char(204); mostrarAscii( 9, 205 ); cout << char(206); mostrarAscii( 9, 205 ); cout <<  char(206); mostrarAscii( 9, 205 ); cout << char(185) << endl;
		
		
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
					cout << "\t" << char(186) << " INICIO  " << char(186) << "    X    " << char(186) << "         " << char(186)  << endl;
					
					// Si el automata esta en estado "INICIO" y el primer caracter es un numero, entonces cambio el estado a numero. Cualquier otro caracter seria erroneo.
					if( isdigit ( caracterActual ) ){
						estadoActual = EstadoAutomata::NUMERO;
					} else {
						estadoActual = EstadoAutomata::MAL;
					}
					break;
				case EstadoAutomata::NUMERO:
					cout << "\t" << char(186) << " NUMERO  " << char(186) << "    X    " << char(186) << "    " << stringEngrada[posicionCaracter-1] << "    " << char(186)  << endl;
				
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
					cout << "\t" << char(186) << "MAYUSCULA" << char(186) << "    X    " << char(186) << "    " << stringEngrada[posicionCaracter-1] << "    " << char(186)  << endl;
				
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
					if( ( posicionCaracter == stringEngrada.length() ) ) {
						cout << "\t" << char(186) << "MINUSCULA" << char(186) << "    V    " << char(186) << "    " << stringEngrada[posicionCaracter-1] << "    " << char(186)  << endl;
					} else {
						cout << "\t" << char(186) << "MINUSCULA" << char(186) << "    X    " << char(186) << "    " << stringEngrada[posicionCaracter-1] << "    " << char(186)  << endl;
					}
					
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
			
			// Si ya leyo el ultimo caracter o el estado del automata es "MAL"  Muestro el ultimo estado
			if( ( posicionCaracter == stringEngrada.length() ) || ( estadoActual == EstadoAutomata::MAL ) ) {
				cout << "\t" << char(204); mostrarAscii( 9, 205 ); cout << char(206); mostrarAscii( 9, 205 ); cout <<  char(206); mostrarAscii( 9, 205 ); cout << char(185) << endl;
				cout << "\t" << char(186); mostrarEstado( estadoActual ); cout << char(186) << "    V    " << char(186) << "    " << stringEngrada[posicionCaracter-1] << "    " << char(186)  << endl;
				cout << "\t" << char(200); mostrarAscii( 9, 205 ); cout << char(202); mostrarAscii( 9, 205 ); cout <<  char(202); mostrarAscii( 9, 205 ); cout << char(188) << endl;
			} else {
				cout << "\t" << char(204); mostrarAscii( 9, 205 ); cout << char(206); mostrarAscii( 9, 205 ); cout <<  char(206); mostrarAscii( 9, 205 ); cout << char(185) << endl;
			}
		 }
		 
		 // Retornamos el estado actual del automata
		 return estadoActual;
	}
/*
	Indicar cada estado por los que paso 
	 
	  UN EJEMPLO DE COMO PODRIA QUEDAR
			 
		╔════════════════════════════╗
		║    ESTADO     ║ ¿ FINAL ? ║      LETRA        ║
		╠═════════╬═══════╬══════════╣
		║     INICIO       ║        X       ║         C1           ║
		╠═════════╬═══════╬══════════╣
		║   NUMERO   ║        X       ║         C2            ║
		╠═════════╬═══════╬══════════╣
		║MAYUSCULA║        X       ║         C3            ║
		╠═════════╬═══════╬══════════╣
		║MINUSCULA ║        X       ║         C4            ║
		╠═════════╬═══════╬══════════╣
		║MINUSCULA ║        V       ║         C5            ║
		╚═════════╩═══════╩══════════╝
		 
*/