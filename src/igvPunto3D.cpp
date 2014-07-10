#include <stdio.h>
#include <math.h>

#include "igvPunto3D.h"
#include <sstream>
using namespace std;

// Constructores
igvPunto3D::igvPunto3D() {
	c[X] = c[Y] = c[Z] = 0.0;
}

igvPunto3D::igvPunto3D(const double& x, const double& y, const double& z) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}

// Constructor de copia
igvPunto3D::igvPunto3D(const igvPunto3D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
}

// Operador de asignacion
igvPunto3D& igvPunto3D::operator =(const igvPunto3D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	return (*this);
}

int igvPunto3D::operator ==(const igvPunto3D& p) {
	return ((fabs(c[X] - p[X]) < IGV_EPSILON)
			&& (fabs(c[Y] - p[Y]) < IGV_EPSILON)
			&& (fabs(c[Z] - p[Z]) < IGV_EPSILON));
}

int igvPunto3D::operator !=(const igvPunto3D& p) {
	return ((fabs(c[X] - p[X]) >= IGV_EPSILON)
			|| (fabs(c[Y] - p[Y]) >= IGV_EPSILON)
			|| (fabs(c[Z] - p[Z]) >= IGV_EPSILON));
}

// Destructor
igvPunto3D::~igvPunto3D() {
}

// Operadores

void igvPunto3D::set(const double& x, const double& y, const double& z) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}

//TODO mirar esto
igvPunto3D igvPunto3D::operator *(double d) {
	double vector[3] = { c[0] * d, c[1] * d, c[2] * d };
	return igvPunto3D(vector[0], vector[1], vector[2]);
}

igvPunto3D& igvPunto3D::operator +=(const igvPunto3D& p) {
	for (int i = 0; i < NUM_COORDENADAS; ++i)
		c[i] += p.c[i];
	return *this;
}

std::string igvPunto3D::toString() {
	stringstream cadena;
	cadena << "[" << c[0] << ", " << c[1] << ", " << c[2] << "]";
	return cadena.str();
}

const double* igvPunto3D::getCoordenadas() const {
	return c;
}
