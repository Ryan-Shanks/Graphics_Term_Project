/*
 * Cone.h
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#ifndef CONE_HPP_
#define CONE_HPP_
#include "Shape.hpp"

class Cone: public Shape{
public:
	Cone();
	void draw();
	virtual ~Cone();
private:
	GLUquadric* quad;
	Matrix matFar;

};

#endif /* CONE_HPP_ */
