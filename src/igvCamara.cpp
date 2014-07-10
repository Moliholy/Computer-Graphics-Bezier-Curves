#include <GL/glut.h>
#include <math.h>

#include "igvCamara.h"
#include <iostream>

// Metodos constructores

igvCamara::igvCamara() {
	ywmax = 0;
	ywmin = 0;
	xwmax = 0;
	xwmin = 0;
	tipo = IGV_PARALELA;
	znear = -1;
	raspecto = 0;
	zfar = 0;
	angulo = 60;
}

igvCamara::~igvCamara() {
}

igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r,
		igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;
	ywmax = 0;
	ywmin = 0;
	xwmax = 0;
	xwmin = 0;
	znear = -1;
	raspecto = 0;
	zfar = 0;
	angulo = 60;
	tipo = _tipo;
}

// Metodos publicos 
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;
}
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r,
		igvPunto3D _V, double _xwmin, double _xwmax, double _ywmin,
		double _ywmax, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	xwmin = _xwmin;
	xwmax = _xwmax;
	ywmin = _ywmin;
	ywmax = _ywmax;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r,
		igvPunto3D _V, double _angulo, double _raspecto, double _znear,
		double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	angulo = _angulo;
	raspecto = _raspecto;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::aplicar(void) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (tipo == IGV_PARALELA) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_FRUSTUM) {
		glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_PERSPECTIVA) {
		gluPerspective(angulo, raspecto, znear, zfar);
	}

	znear = P0[2] - 1000;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z]);
}

void igvCamara::zoom(double factor) {
	xwmin *= (GLdouble) factor;
	xwmax *= (GLdouble) factor;
	ywmin *= (GLdouble) factor;
	ywmax *= (GLdouble) factor;
	angulo = std::min((GLdouble) (angulo * factor), (GLdouble) 175);
}
