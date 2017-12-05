/*
 * PointLightSource.h
 *
 *  Created on: Nov 5, 2017
 *      Author: ryanw
 */

#ifndef LIGHTORB_HPP_
#define LIGHTORB_HPP_
#include "GL/gl.h"
#include "GL/glut.h"
#include "Vector.hpp"
#include "Shape.hpp"
#include <vector>

class LightOrb: public Shape {

public:
	LightOrb(GLfloat starty, GLfloat startz, GLfloat r, GLfloat g, GLfloat b, vector<int> *lightsAvail, float speedFactor);
	~LightOrb();
	void draw();
	Vector getLightPos();
	Matrix MC; //the Model coordinate system in (X, Y, Z, 0)
	void setGLLighting();
	int lightNo;
	GLfloat speed;
	GLfloat r, g, b;
	void tick(DWORD ticks);
	vector<int> *lightsAvail;
};

#endif /* LIGHTORB_HPP_ */
