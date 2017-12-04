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
class Spaceship: public Shape {
public:
	Spaceship();
	virtual ~Spaceship();
	void draw();
private:
	Prism *leftWing, *rightWing;
	Cylinder *body;
	Cone *nose;
};

#endif /* SPACESHIP_HPP_ */
