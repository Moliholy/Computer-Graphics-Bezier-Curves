#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "CurvaBezier.h"
#include "igvInterfaz.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;
	GLfloat r[] = { 0.25, 0.5, 0.75, 1 };
	//inicializamos los centros de las esferas
	puntosControl = NULL;
	curva = NULL;
	for (int i = 0; i < numEsferas; i++) {
		centros[i] = igvPunto3D(CurvaBezier::doubleAleatorio() * FACTOR_ESCALA,
				CurvaBezier::doubleAleatorio() * FACTOR_ESCALA,
				CurvaBezier::doubleAleatorio() * FACTOR_ESCALA);
		radios[i] = r[i % 4];
	}
}

igvEscena3D::~igvEscena3D() {
	delete[] puntosControl;
}

// Metodos publicos 

void pintar_ejes(void) {
	GLfloat rojo[] = { 1, 0, 0, 1.0 };
	GLfloat verde[] = { 0, 1, 0, 1.0 };
	GLfloat azul[] = { 0, 0, 1, 1.0 };

	glBegin(GL_LINES);
	glLineWidth(1.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glVertex3f(10000, 0, 0);
	glVertex3f(-10000, 0, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glVertex3f(0, 10000, 0);
	glVertex3f(0, -10000, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glVertex3f(0, 0, 10000);
	glVertex3f(0, 0, -10000);
	glEnd();
}

void igvEscena3D::setCurva(CurvaBezier* curva) {
	this->curva = curva;
	unsigned long numPuntosControl = curva->getOrden() + 1;
	//delete[] puntosControl;
	puntosControl = new double[numPuntosControl * 3];
	igvPunto3D* puntosC = curva->getPuntos();
	for (unsigned long i = 0; i < numPuntosControl * 3; i++) {
		igvPunto3D* punto = puntosC + i;
		int pos = i;
		puntosControl[i++] = punto[pos][0];
		puntosControl[i++] = punto[pos][1];
		puntosControl[i] = punto[pos][2];
	}
}

void igvEscena3D::visualizar() {
// crear luces
	GLfloat luz0[] = { 10, 8, 9, 1 }; // luz puntual
	glLightfv(GL_LIGHT0, GL_POSITION, luz0);
	glEnable(GL_LIGHT0);

// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

// se pintan los ejes
	if (ejes)
		pintar_ejes();

	glLineWidth(3.0);
	GLfloat negro[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	if (puntosControl != NULL) {
		int numPuntos = curva->getOrden() + 1;
		glEnable(GL_MAP1_VERTEX_3);
		glMap1d(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, numPuntos, puntosControl);
		glMapGrid1d(50, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 50);
		glDisable(GL_MAP1_VERTEX_3);
	}
// se pintan los objetos de la escena
//pintamos esferas

	const int n = 3;
	GLfloat verde[] = { 0.25, 0, 0 };
	GLfloat rojo[] = { 0, 0.25, 0 };
	GLfloat azul[] = { 0, 0, 0.25 };
	GLfloat* colores[] = { verde, rojo, azul };
	for (int i = 0; i < numEsferas; i++) {
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colores[i % n]);
		glPushMatrix();
		glTranslated(centros[i][0], centros[i][1], centros[i][2]);
		glutSolidSphere(radios[i % 3], 100, 100);
		glPopMatrix();
	}
	glPopMatrix(); // restaura la matriz de modelado
}

