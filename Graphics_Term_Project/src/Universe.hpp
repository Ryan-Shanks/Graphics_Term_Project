#ifndef CWORLD_HPP
#define CWORLD_HPP

#include <GL/glew.h>
#include "Sphere.hpp"
#include "Cube.hpp"
#include "PointLightSource.hpp"
#include "Camera.hpp"
#include <iostream>
#include <list>
#include <vector>
#include "BezierCurve.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "Spaceship.hpp"

class Universe {
public:
	Camera *myCamera;
	Universe();
	~Universe();
	void draw_world(); // draw all objects in the world
	void normalizeAll();
	PointLightSource *lightSource;
	void animateSolar();
	GLint stepRotation, totalRotation, bezCurveRes; // Parameters to control the rotation and smoothness of the curve
	Spaceship getShip();
private:
	Sphere *sun, *moon, *earth; // shapes for the solar system
	BezierCurve* curve;
	PointLightSource *sunLight;
	Spaceship ship;
};

#endif
