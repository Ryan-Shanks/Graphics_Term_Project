/*
 * PointLightSource.h
 *
 *  Created on: Nov 5, 2017
 *      Author: ryanw
 */

#ifndef POINTLIGHTSOURCE_HPP_
#define POINTLIGHTSOURCE_HPP_
#include "GL/gl.h"
#include "GL/glut.h"
#include "Vector.hpp"
#include "Shape.hpp"
class PointLightSource: public Shape {

public:
	PointLightSource();
	~PointLightSource();
	void draw();
	void increment(GLfloat di, GLfloat drd, GLfloat dra);
	Vector getLightPos();
	GLfloat i, rd, ia, ra, size;
	bool on;
	Matrix MC; //the Model coordinate system in (X, Y, Z, 0)
	GLfloat s; // scale factor
	void setGLLighting();
};

#endif /* POINTLIGHTSOURCE_HPP_ */
