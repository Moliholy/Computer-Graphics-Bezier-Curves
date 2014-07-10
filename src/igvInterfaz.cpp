#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"
#include "CurvaBezier.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
// ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() :
		escena(), curva(5 + rand() % 4, FACTOR_ESCALA, 1000) {
	alto_ventana = 500;
	ancho_ventana = 500;
	escena.setCurva(&curva);
}

igvInterfaz::~igvInterfaz() {
}

// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
// crear cámaras
	interfaz.camara.set(IGV_PARALELA,
			igvPunto3D(3.0 * FACTOR_ESCALA, 2.0 * FACTOR_ESCALA,
					4.0 * FACTOR_ESCALA), igvPunto3D(0, 0, 0),
			igvPunto3D(0, 1.0, 0), -1 * 3, 1 * 3, -1 * 3, 1 * 3, -1 * 3, 200);
	camara.znear = camara.P0[2] - 1;
}

void igvInterfaz::configura_entorno(int argc, char** argv, int _ancho_ventana,
		int _alto_ventana, int _pos_X, int _pos_Y, string _titulo) {
// inicialización de las variables de la interfaz
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

// inicialización de la ventana de visualización
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicializarVistas() {
	igvInterfaz::vistas[0][0] = igvPunto3D(3, 2, 4); //perspectiva
	igvInterfaz::vistas[1][0] = igvPunto3D(0, 0, 6); //perfil
	igvInterfaz::vistas[2][0] = igvPunto3D(6, 0, 0); //alzado
	igvInterfaz::vistas[3][0] = igvPunto3D(0, 6, 0); //planta

	igvInterfaz::vistas[0][1] = igvInterfaz::vistas[1][1] =
			igvInterfaz::vistas[2][1] = igvPunto3D(0, 1, 0);
	igvInterfaz::vistas[3][1] = igvPunto3D(1, 0, 0);
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	igvPunto3D punto;
	switch (key) {
	case 'p': // cambia el tipo de proyección de paralela a perspectiva y viceversa
	case 'P':
		//hay que tocar los parametros de la camara con su metodo set() y luego llamar al método aplicar()
		if (interfaz.camara.tipo == IGV_FRUSTUM
				|| interfaz.camara.tipo == IGV_PARALELA)
			//este es el que hay que retocar para poner perspectiva paralela
			interfaz.camara.set(IGV_PERSPECTIVA, vistas[modo_vista][0],
					interfaz.camara.r, interfaz.camara.V,
					interfaz.camara.angulo, 1, 1 * 3, 1 * -3);
		else
			interfaz.camara.set(IGV_PARALELA, vistas[modo_vista][0],
					interfaz.camara.r, interfaz.camara.V, interfaz.camara.xwmin,
					interfaz.camara.xwmax, interfaz.camara.ywmin,
					interfaz.camara.ywmax, -3, 200);
		interfaz.camara.aplicar();
		break;
	case 'x': // aqui entran las curvas Bézier
		if (interfaz.curva.hasNext()) {
			punto = interfaz.curva.next();
			interfaz.camara.set(IGV_PERSPECTIVA, punto, interfaz.camara.r,
					interfaz.camara.V, interfaz.camara.angulo, 1, 1 * 3,
					1 * -3);
			//cout << punto.toString() << endl;
		} else {
			cout << "REINICIANDO" << endl;
			interfaz.curva.reiniciar();
		}
		interfaz.camara.aplicar();
		break;
	case 'v': // cambia la posición de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
	case 'V':
		modo_vista = (modo_vista + 1) % 4;
		interfaz.camara.set(vistas[modo_vista][0], interfaz.camara.r,
				vistas[modo_vista][1]);
		interfaz.camara.aplicar();
		break;
	case '+': // zoom in
		interfaz.camara.zoom(0.95);
		interfaz.camara.aplicar();
		break;
	case '-': // zoom out
		interfaz.camara.zoom(1.05);
		interfaz.camara.aplicar();
		break;
	case 'c': // incrementar la distancia del plano cercano
		interfaz.camara.znear += 0.2;
		interfaz.camara.aplicar();
		break;
	case 'C': // decrementar la distancia del plano cercano
		interfaz.camara.znear -= 0.2;
		interfaz.camara.aplicar();
		break;
	case '9': // cambiar a formato 16:9 con deformación
		modoPanoramico = !modoPanoramico;
		set_glutDisplayFunc();
		break;
	case '4': // cambiar a formato 4 viewports
		if (numViewports == 1)
			numViewports = 4;
		else
			numViewports = 1;
		set_glutDisplayFunc();
		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
	case 'E':
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
// dimensiona el viewport al nuevo ancho y alto de la ventana
// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

// se establece el viewport
	//ponemos los parámetros para el viewport
	int x0, y0, ancho, alto;
	if (modoPanoramico) {
		x0 = 0;
		y0 = (interfaz.get_alto_ventana()
				- interfaz.get_ancho_ventana() * 9 / 16) / 2;
		ancho = interfaz.get_ancho_ventana();
		alto = interfaz.get_ancho_ventana() * 9 / 16;
	} else {
		x0 = y0 = 0;
		ancho = interfaz.get_alto_ventana();
		alto = interfaz.get_alto_ventana();
	}
	//establecemos los viewports que correspondan
	if (numViewports == 1)
		glViewport(x0, y0, ancho, alto);
	else if (numViewports == 4) {
		glViewport(x0, y0, ancho / 2, alto / 2);
		interfaz.camara.set(vistas[2][0], interfaz.camara.r, vistas[2][1]);
		interfaz.camara.aplicar();
		interfaz.escena.visualizar();

		glViewport(x0, y0 + alto / 2, ancho / 2, alto / 2);
		interfaz.camara.set(vistas[0][0], interfaz.camara.r, vistas[0][1]);
		interfaz.camara.aplicar();
		interfaz.escena.visualizar();

		glViewport(x0 + ancho / 2, y0 + alto / 2, ancho / 2, alto / 2);
		interfaz.camara.set(vistas[3][0], interfaz.camara.r, vistas[3][1]);
		interfaz.camara.aplicar();
		interfaz.escena.visualizar();

		glViewport(x0 + ancho / 2, y0, ancho / 2, alto / 2);
		interfaz.camara.set(vistas[1][0], interfaz.camara.r, vistas[1][1]);
		interfaz.camara.aplicar();
	}

//visualiza la escena
	interfaz.escena.visualizar();

// refresca la ventana
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}

//inicialización de los atributos estáticos de la clase
int igvInterfaz::modo_vista = 0;
int igvInterfaz::numViewports = 1;
igvPunto3D igvInterfaz::vistas[4][2];
bool igvInterfaz::modoPanoramico = false;
