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
#include "Cylinder.hpp"
#include "Camera.hpp"

class Spaceship: public Shape {
public:
	Spaceship();
	virtual ~Spaceship();
	void draw();
	void up();
	void down();
	void left();
	void right();
	void tick();
private:
	Prism *leftWing, *rightWing;
	Cylinder *body;
	Cone *nose;
	GLfloat vy,vz;
};

#endif /* SPACESHIP_HPP_ */
