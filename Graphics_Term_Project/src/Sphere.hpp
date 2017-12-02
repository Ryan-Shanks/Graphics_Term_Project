/*
 * Sphere.hpp
 *
 *  Created on: Nov 5, 2017
 *      Author: ryanw
 */

#ifndef SPHERE_HPP_
#define SPHERE_HPP_
#include "Shape.hpp"
#include "RGBpixmap.h"

class Sphere: public Shape{
private:
	bool solid, useTexture;
	GLfloat r, g, b;
	RGBpixmap tex;
	int texName;
	GLUquadric *quad;
public:
	Sphere(bool solid, GLfloat r, GLfloat g, GLfloat b);
	Sphere(std::string texture, int uniqueTexName);
	virtual ~Sphere();
	void draw();
};

#endif /* SPHERE_HPP_ */
