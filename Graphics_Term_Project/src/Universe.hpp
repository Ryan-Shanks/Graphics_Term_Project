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

class Universe {
public:
	Camera *myCamera;
	Shape *cube; // cube to show texture mapping
	Universe();
	~Universe();
	void draw_world(); // draw all objects in the world
	void normalizeAll();
	PointLightSource *lightSource;
	void animateSolar();
	GLint stepRotation, totalRotation, bezCurveRes; // Parameters to control the rotation and smoothness of the curve
	void clearCP();
private:
	std::vector<Point*> controlPoints; // cp to generate the bezier curve
	Sphere *sun, *moon, *earth; // shapes for the solar system
	BezierCurve* curve;
	PointLightSource *sunLight;
	std::vector<Shape*> objects;
};

#endif
