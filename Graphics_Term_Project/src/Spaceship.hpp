/*
 * SpaceShip.hpp
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_
#include "Shape.hpp"
#include "Cone.hpp"
#include "Prism.hpp"
#include "BezierCurve.hpp"
#include "Camera.hpp"

class Spaceship: public Shape {
public:
	Spaceship();
	virtual ~Spaceship();
	void draw();
	void vert(char);
	void horiz(char);
	void tick(DWORD ticks);
private:
	Prism *leftUpperWing, *rightUpperWing, *leftLowerWing, *rightLowerWing;
	BezierCurve *body;
	GLfloat vy,vz;
};

#endif /* SPACESHIP_HPP_ */
