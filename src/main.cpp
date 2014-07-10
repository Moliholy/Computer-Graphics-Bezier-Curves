#include <cstdlib>
#include <ctime>

#include "igvInterfaz.h"
#include "CurvaBezier.h"

// Objetos globales
// objeto que contiene la configuración y la interacción con la ventana de visualización
igvInterfaz interfaz;

int main(int argc, char** argv) {
	srand(time(NULL));
	// inicializa la ventana de visualización
	interfaz.inicializarVistas();
	interfaz.configura_entorno(argc, argv, 700,
			700, // tamaño de la ventana
			0,
			0, // posicion de la ventana
			"Informática Gráfica y Visualización. Trabajo curvas y superficies Bézier" // título de la ventana
			);

	// establece las funciones callbacks para la gestión de los eventos
	interfaz.inicializa_callbacks();

	// inicia el bucle de visualización de OpenGL
	interfaz.inicia_bucle_visualizacion();

	return (0);
}
