#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#include <GL/glut.h>

#include "igvEscena3D.h"
#include "igvCamara.h"
#include "igvEscena3D.h"
#include "CurvaBezier.h"

using namespace std;

class igvInterfaz {
protected:
	// Atributos

	//nos indica el n�mero de viewports que tenemos (pueden ser 1 o 4)
	static int numViewports;
	//nos indica si estamos o no en modo panor�mico
	static bool modoPanoramico;
	//nos indica el modo de vista en el que estamos (axonom�trico, alzado, planta o perfil)
	static int modo_vista;
	//matriz que almacena los puntos donde colocaremos la c�mara, as� como el vector arriba correspondiente
	static igvPunto3D vistas[][2];
	int ancho_ventana; // ancho inicial de la ventana de visualizacion
	int alto_ventana;  // alto inicial de la ventana de visualizacion

	igvEscena3D escena; // escena que se visualiza en la ventana definida por igvInterfaz
	igvCamara camara; // c�mara que se utiliza para visualizar la escena
	CurvaBezier curva;
public:
	// Constructores por defecto y destructor
	igvInterfaz();
	~igvInterfaz();

	// Metodos est�ticos
	//inicializa la matriz vistas[][]
	static void inicializarVistas();
	// callbacks de eventos
	static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
	static void set_glutReshapeFunc(int w, int h); // m�todo que define la camara de vision y el viewport
												   // se llama autom�ticamente cuano se camba el tama�o de la ventana
	static void set_glutDisplayFunc(); // m�todo para visualizar la escena

	// Metodos
	// crea el mundo que se visualiza en la ventana
	void crear_mundo(void);

	// inicializa todos los par�metros para crear una ventana de visualizaci�n
	void configura_entorno(int argc, char** argv, // parametros del main
			int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualizaci�n
			int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualizaci�n
			string _titulo // t�tulo de la ventan de visualizaci�n
			);
	void inicializa_callbacks(); // inicializa todas los callbacks

	void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

	// m�todos get_ y set_ de acceso a los atributos
	int get_ancho_ventana() {
		return ancho_ventana;
	}

	int get_alto_ventana() {
		return alto_ventana;
	}

	void set_ancho_ventana(int _ancho_ventana) {
		ancho_ventana = _ancho_ventana;
	}

	void set_alto_ventana(int _alto_ventana) {
		alto_ventana = _alto_ventana;
	}
};

#endif
