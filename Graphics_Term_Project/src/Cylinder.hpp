/*
 * Cylinder.h
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_
#include "Shape.hpp"
#include "Matrix.hpp"

class Cylinder: public Shape {
public:
	Cylinder();
	virtual ~Cylinder();
	void draw();
private:
	GLUquadric* quad;
	Matrix matNear, matFar;
};

#endif /* CYLINDER_HPP_ */
