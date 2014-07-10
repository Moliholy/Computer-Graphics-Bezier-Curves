/*
 * CurvaBezier.cpp
 *
 *  Created on: 06/11/2012
 *      Author: Molina
 */

#include "CurvaBezier.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "igvPunto3D.h"

using namespace std;

CurvaBezier::CurvaBezier() {
	t = 0;
	incremento = 0.00001;
	n = 2;
	puntos = NULL;
}

CurvaBezier::CurvaBezier(uint n, igvPunto3D puntos[]) {
	t = 0;
	incremento = 0.00001;
	this->n = n;
	this->puntos = puntos;
}

CurvaBezier::CurvaBezier(const CurvaBezier& c) {
	incremento = c.incremento;
	n = c.n;
	t = c.t;
	puntos = new igvPunto3D[n + 1];
	for (uint i = 0; i <= n; i++)
		puntos[i] = c.puntos[i];
}

CurvaBezier::CurvaBezier(uint n) {
	t = 0;
	incremento = 0.00001;
	this->n = n;
	//generamos los puntos normalizados aleatoriamente
	puntos = new igvPunto3D[n + 1];
	for (uint i = 0; i <= n; i++)
		puntos[i] = igvPunto3D(doubleAleatorio(), doubleAleatorio(),
				doubleAleatorio());
}

CurvaBezier::CurvaBezier(uint n, double factorEscala, ulong numPuntos) {
	t = 0;
	this->n = n;
	//generamos los puntos normalizados aleatoriamente
	puntos = new igvPunto3D[n + 1];
	for (uint i = 0; i <= n; i++)
		puntos[i] = igvPunto3D(doubleAleatorio(), doubleAleatorio(),
				doubleAleatorio());
	setEscala(factorEscala);
	incremento = 1.0 / numPuntos;
}

CurvaBezier::~CurvaBezier() {
	delete[] puntos;
}

unsigned long CurvaBezier::numeroCombinatorio(uint a, uint b) {
	return factorial(a) / (factorial(b) * factorial(a - b));
}

unsigned long CurvaBezier::factorial(uint a) {
	if (a == 0)
		return 1L;
	ulong resultado = 1L;
	for (uint i = 2; i <= a; i++)
		resultado *= i;
	return resultado;
}

uint CurvaBezier::getOrden() const {
	return n - 1;
}

igvPunto3D & CurvaBezier::getInicio() {
	return puntos[0];
}

igvPunto3D & CurvaBezier::getFinal() {
	return puntos[n];
}

/**
 * Genera un double entre -1 y 1
 */
double CurvaBezier::doubleAleatorio() {
	double retorno = ((double) rand() * pow(-1, 1 + (rand() % 2))) / RAND_MAX;
	return retorno;
}

igvPunto3D CurvaBezier::next() {
	t += incremento;
	return valorActual();
}

bool CurvaBezier::hasNext() const {
	return t + incremento <= 1.0;
}

igvPunto3D CurvaBezier::valorActual() {
	igvPunto3D punto(0, 0, 0);
	for (uint i = 0; i <= n; i++) {
		double valor = numeroCombinatorio(n, i) * pow(t, i) * pow(1 - t, n - i);
		punto += puntos[i] * valor;
	}
	return punto;
}

void CurvaBezier::reiniciar() {
	t = 0;
}

ulong CurvaBezier::getNumPuntos() const {
	return (ulong) (1L / incremento);
}

void CurvaBezier::setNumPuntos(ulong num) {
	incremento = 1.0 / num;
}

void CurvaBezier::setEscala(double factor) {
	for (uint i = 0; i <= n; ++i)
		puntos[i] = puntos[i] * factor;
}

CurvaBezier& CurvaBezier::operator =(const CurvaBezier& c) {
	incremento = c.incremento;
	n = c.n;
	t = c.t;
	puntos = new igvPunto3D[n + 1];
	for (uint i = 0; i <= n; i++)
		puntos[i] = c.puntos[i];
	return *this;
}

igvPunto3D * CurvaBezier::getPuntosControl() const {
	return puntos;
}
