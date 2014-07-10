#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <GL/glut.h>
#include <vector>
#include "igvPunto3D.h"
#include "CurvaBezier.h"
using namespace std;

const unsigned int FACTOR_ESCALA = 6;

class igvEscena3D {
protected:
	// Atributos
	static const int numEsferas = 50;
	bool ejes;
	igvPunto3D centros[numEsferas];
	GLfloat radios[3];
	CurvaBezier* curva;
	double* puntosControl;
public:
	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// Metodos estáticos

	// Métodos
	// método con las llamadas OpenGL para visualizar la escena
	void visualizar();

	bool get_ejes() {
		return ejes;
	}

	void set_ejes(bool _ejes) {
		ejes = _ejes;
	}

	void setCurva(CurvaBezier* curva);
};

#endif
