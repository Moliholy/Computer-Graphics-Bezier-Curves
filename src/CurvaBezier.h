/*
 * CurvaBezier.h
 *
 *  Created on: 06/11/2012
 *      Author: Molina
 */

#ifndef CURVABEZIER_H_
#define CURVABEZIER_H_
#include "igvPunto3D.h"

typedef unsigned long ulong;
typedef unsigned int uint;

class CurvaBezier {
protected:
	double incremento;
	//numero de puntos de control que forman la curva Bézier
	uint n;
	//valor actual de t en la fórmula de las curvas Bézier
	double t;
	igvPunto3D* puntos;
	static ulong numeroCombinatorio(uint a, uint b);
	static ulong factorial(uint a);
public:
	static double doubleAleatorio();
	CurvaBezier();
	CurvaBezier(uint n, double factorEscala, ulong numPuntos);
	CurvaBezier(uint n, igvPunto3D puntos[]);
	CurvaBezier(uint n);
	CurvaBezier(const CurvaBezier& c);
	virtual ~CurvaBezier();
	uint getOrden() const;
	igvPunto3D& getInicio();
	igvPunto3D& getFinal();
	igvPunto3D next();
	bool hasNext() const;
	igvPunto3D valorActual();
	void reiniciar();
	ulong getNumPuntos() const;
	void setNumPuntos(ulong num);
	void setEscala(double factor);
	CurvaBezier& operator=(const CurvaBezier& c);
	igvPunto3D* getPuntosControl() const;

	double getIncremento() const {
		return incremento;
	}

	uint getN() const {
		return n;
	}

	igvPunto3D* getPuntos() const {
		return puntos;
	}

	double getT() const {
		return t;
	}
};

#endif /* CURVABEZIER_H_ */
