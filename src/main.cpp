#include <cstdlib>
#include <ctime>

#include "igvInterfaz.h"
#include "CurvaBezier.h"

// Objetos globales
// objeto que contiene la configuraci�n y la interacci�n con la ventana de visualizaci�n
igvInterfaz interfaz;

int main(int argc, char** argv) {
	srand(time(NULL));
	// inicializa la ventana de visualizaci�n
	interfaz.inicializarVistas();
	interfaz.configura_entorno(argc, argv, 700,
			700, // tama�o de la ventana
			0,
			0, // posicion de la ventana
			"Inform�tica Gr�fica y Visualizaci�n. Trabajo curvas y superficies B�zier" // t�tulo de la ventana
			);

	// establece las funciones callbacks para la gesti�n de los eventos
	interfaz.inicializa_callbacks();

	// inicia el bucle de visualizaci�n de OpenGL
	interfaz.inicia_bucle_visualizacion();

	return (0);
}
